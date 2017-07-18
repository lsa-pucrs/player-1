/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) 2000-2003
 *     Brian Gerkey, Kasper Stoy, Richard Vaughan, & Andrew Howard
 *   2017: Guilherme Marques and Alexandre Amory
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
/********************************************************************
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 ********************************************************************/

/*
 * $Id: playsoundproxy.cc $
 */

#include "playerc++.h"

using namespace PlayerCc;

PlaySoundProxy::PlaySoundProxy(PlayerClient *aPc, uint32_t aIndex)
  : ClientProxy(aPc, aIndex),
  mDevice(NULL)
 {
  Subscribe(aIndex);
  mInfo = &(mDevice->info);
}

PlaySoundProxy::~PlaySoundProxy()
{
  Unsubscribe();
}

void PlaySoundProxy::Subscribe(uint32_t aIndex)
{
  scoped_lock_t lock(mPc->mMutex);
  mDevice = playerc_playsound_create(mClient, aIndex);
  if (NULL==mDevice)
    throw PlayerError("PlaySoundProxy::PlaySoundProxy()", "could not create");

  if (0 != playerc_playsound_subscribe(mDevice, PLAYER_OPEN_MODE))
    throw PlayerError("PlaySoundProxy::PlaySoundProxy()", "could not subscribe");
}

void PlaySoundProxy::Unsubscribe()
{
  assert(NULL!=mDevice);
  scoped_lock_t lock(mPc->mMutex);
  playerc_playsound_unsubscribe(mDevice);
  playerc_playsound_destroy(mDevice);
  mDevice = NULL;
}

void PlaySoundProxy::play(char *filename)
{
  scoped_lock_t lock(mPc->mMutex);
  if (0 != playerc_playsound_play(mDevice, filename))
    throw PlayerError("PlaySoundProxy::play()", "error playing file");
  return;
}
