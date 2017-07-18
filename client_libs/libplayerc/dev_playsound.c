/*
 *  libplayerc : a Player client library
 *  Copyright (C) Andrew Howard 2002-2003
 *   2017: Guilherme Marques and Alexandre Amory
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) Andrew Howard 2003
 *
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
 */
/*  playsound Proxy for libplayerc library.
 *  Structure based on the rest of libplayerc.
 */
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "playerc.h"
#include "error.h"

// Local declarations
void playerc_playsound_putmsg(playerc_playsound_t *device,
                           player_msghdr_t *header,
                           player_playsound_cmd_t *data,
                           size_t len);

// Create a new sound proxy
playerc_playsound_t *playerc_playsound_create(playerc_client_t *client, int index)
{
  playerc_playsound_t *device;

  device = malloc(sizeof(playerc_playsound_t));
  memset(device, 0, sizeof(playerc_playsound_t));
  playerc_device_init(&device->info, client, PLAYER_PLAYSOUND_CODE, index,
                      (playerc_putmsg_fn_t) playerc_playsound_putmsg);

  return device;
}

// Destroy a sound proxy
void playerc_playsound_destroy(playerc_playsound_t *device)
{
  playerc_device_term(&device->info);
  free(device);
}

// Subscribe to the sound device
int playerc_playsound_subscribe(playerc_playsound_t *device, int access)
{
  return playerc_device_subscribe(&device->info, access);
}

// Un-subscribe from the sound device
int playerc_playsound_unsubscribe(playerc_playsound_t *device)
{
  return playerc_device_unsubscribe(&device->info);
}

// Process incoming data
void playerc_playsound_putmsg(playerc_playsound_t *device, player_msghdr_t *header,
                            player_playsound_cmd_t *data, size_t len)
//                            char *data, size_t len)
//                            void *data, size_t len)
{
  /* there's no much to do in this proxy.
     check out for the dev_bumper or dev_opaque to see a not empty, but still simple example.
     basically, it checks wheter it is the expected header format and it
     transfers data from 'data' to 'device' for each datatype defined in the interface.
  */
}

// set the file to be played into the audio device
int playerc_playsound_play(playerc_playsound_t *device, char *string)
{
  player_playsound_cmd_t cmd;
  //memset(&cmd, 0, sizeof(cmd));

  //strcpy(cmd.filename,filename);
  memset(&cmd, 0, sizeof(cmd));
  cmd.string = string;
  cmd.string_count = strlen(string) + 1;   

  return playerc_client_write(device->info.client,
    &device->info, PLAYER_PLAYSOUND_CMD_VALUES,&cmd,NULL);
}
