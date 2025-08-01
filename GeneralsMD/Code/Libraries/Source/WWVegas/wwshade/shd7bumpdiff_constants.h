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

// bump diffuse map shader constants
// Kenny Mitchell - Westwood Studios EA 2002

#ifndef SHD7BUMPDIFF_CONSTANTS_H
#define SHD7BUMPDIFF_CONSTANTS_H

// vertex shader macros

#define CV_WORLD_VIEW_PROJECTION			1

#define CV_WORLD_VIEW_PROJECTION_0		1
#define CV_WORLD_VIEW_PROJECTION_1		2
#define CV_WORLD_VIEW_PROJECTION_2		3
#define CV_WORLD_VIEW_PROJECTION_3		4

// 5-11 world view & world view inverse transpose

#define CV_WORLD								12

#define CV_WORLD_0							12
#define CV_WORLD_1							13
#define CV_WORLD_2							14
#define CV_WORLD_3							15

// 16-26 lighting constants

#define CV_BUMPINESS							27

#define CV_EYE_WORLD							28


// inputs
#define V_POSITION							v0
#define V_NORMAL								v1
#define V_DIFFUSE								v2
#define V_TEXTURE								v3
#define V_S										v4
#define V_T										v5
#define V_SxT									v6


// registers
#define HALF_ANGLE			r0
#define S_WORLD				r1
#define T_WORLD				r2
#define SxT_WORLD				r3
#define LIGHT_LOCAL			r4
#define LIGHT_0				r5
#define LIGHT_1				r6
#define LIGHT_2				r7
#define LIGHT_3				r8
#define COL						r9
#define WORLD_VERTEX			r10
#define EYE_VECTOR			r11

#define WORLD_NORMAL			r1


#define OUTPUT_REG			r0

// texture stages
#define TEX_CUBEMAP t0



#endif
