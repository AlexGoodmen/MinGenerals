/*
** MinGenerals(tm)
** Copyright 2025 CommunityRTS
**
** The above copyright notice applies to additions and/or other modifications
** made to this file by CommunityRTS.
**
** This file incorporates original work covered by the following copyright and
** permission notice:
**
**		Command & Conquer Generals(tm)
**		Command & Conquer Generals Zero Hour(tm)
**		Copyright 2025 Electronic Arts Inc.
**
**		This program is free software: you can redistribute it and/or modify
**		it under the terms of the GNU General Public License as published by
**		the Free Software Foundation, either version 3 of the License, or
**		(at your option) any later version.
**
**		This program is distributed in the hope that it will be useful,
**		but WITHOUT ANY WARRANTY; without even the implied warranty of
**		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**		GNU General Public License for more details.
**
**		You should have received a copy of the GNU General Public License
**		along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: WinMain.h ////////////////////////////////////////////////////////////
//
// Header for entry point for Win32 application
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __WINMAIN_H_
#define __WINMAIN_H_

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <windows.h>

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Win32Device/GameClient/Win32Mouse.h"

// EXTERNAL ///////////////////////////////////////////////////////////////////
extern HINSTANCE ApplicationHInstance;  ///< our application instance
extern HWND ApplicationHWnd;  ///< our application window handle
extern Win32Mouse *TheWin32Mouse;  ///< global for win32 mouse only!

#endif  // end __WINMAIN_H_

