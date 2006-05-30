/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) 2002
 *     Brian Gerkey, Kasper Stoy, Richard Vaughan, & Andrew Howard
 *     Nik Melchior
 *
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

#ifndef _RWI_BUMPERDEVICE_H
#define _RWI_BUMPERDEVICE_H

#include <rwidevice.h>

class CRWIBumperDevice: public CRWIDevice {

public:
	CRWIBumperDevice ( ConfigFile* cf, int section);

	virtual int Setup ();
	virtual int Shutdown ();
	
	virtual void Main ();
	
private:

#ifdef USE_MOBILITY
	MobilityGeometry::PointState_var bumper_state;
#endif // USE_MOBILITY
	
	// specify which bumper set to use
	bool upper;
};

#endif // _RWI_BUMPERDEVICE_H