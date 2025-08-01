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

#ifndef LOADBMP_HEADER
#define LOADBMP_HEADER

#include<stdlib.h>
#include<stdio.h>
#include "wstypes.h"
#include "winblows.h"


//
// Functions and data assocated with a loaded bitmap on a single window.
//
class LoadBmp
{
 public:
                  LoadBmp();
                 ~LoadBmp();
   bit8           init(char *filename,HWND hwnd);  // must call before the drawBmp
   bit8           drawBmp(void);  // call this from your WM_PAINT message

 private:
   HBITMAP        BitmapHandle_;
   HPALETTE       PalHandle_;
   HWND           WindowHandle_;
};


#endif