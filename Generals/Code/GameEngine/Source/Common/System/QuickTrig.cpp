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

// FILE: QuickTrig.cpp ////////////////////////////////////////////////////////////////////////////////
// Author: Mark Lorenzen (adapted by srj)
// Desc:   fast trig
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/QuickTrig.h"

// GLOBALS ////////////////////////////////////////////////////////////////////////////////////////

Real TheQuickSinTable[] =
{
   0.00000f, 0.01237f, 0.02473f, 0.03710f, 0.04945f, 0.06180f, 0.07414f, 0.08647f,
   0.09879f, 0.11109f, 0.12337f, 0.13563f, 0.14788f, 0.16010f, 0.17229f, 0.18446f,
   0.19661f, 0.20872f, 0.22080f, 0.23284f, 0.24485f, 0.25683f, 0.26876f, 0.28065f,
   0.29250f, 0.30431f, 0.31607f, 0.32778f, 0.33944f, 0.35104f, 0.36260f, 0.37410f,
   0.38554f, 0.39692f, 0.40824f, 0.41950f, 0.43070f, 0.44183f, 0.45289f, 0.46388f,
   0.47480f, 0.48565f, 0.49643f, 0.50712f, 0.51774f, 0.52829f, 0.53875f, 0.54913f,
   0.55942f, 0.56963f, 0.57975f, 0.58978f, 0.59973f, 0.60958f, 0.61934f, 0.62900f,
   0.63857f, 0.64804f, 0.65741f, 0.66668f, 0.67584f, 0.68491f, 0.69387f, 0.70272f,
   0.71147f, 0.72010f, 0.72863f, 0.73705f, 0.74535f, 0.75354f, 0.76161f, 0.76957f,
   0.77741f, 0.78513f, 0.79273f, 0.80020f, 0.80756f, 0.81479f, 0.82190f, 0.82888f,
   0.83574f, 0.84247f, 0.84907f, 0.85554f, 0.86187f, 0.86808f, 0.87415f, 0.88009f,
   0.88590f, 0.89157f, 0.89710f, 0.90250f, 0.90775f, 0.91287f, 0.91785f, 0.92269f,
   0.92739f, 0.93195f, 0.93636f, 0.94063f, 0.94476f, 0.94874f, 0.95257f, 0.95626f,
   0.95981f, 0.96321f, 0.96646f, 0.96956f, 0.97251f, 0.97532f, 0.97798f, 0.98048f,
   0.98284f, 0.98505f, 0.98710f, 0.98901f, 0.99076f, 0.99236f, 0.99381f, 0.99511f,
   0.99625f, 0.99725f, 0.99809f, 0.99878f, 0.99931f, 0.99969f, 0.99992f, 1.00000f,
   0.99992f
};

Real TheQuickTanTable[] =
{
   0.00000f, 0.00787f, 0.01575f, 0.02363f, 0.03151f, 0.03939f, 0.04728f, 0.05517f,
   0.06308f, 0.07099f, 0.07890f, 0.08683f, 0.09477f, 0.10272f, 0.11068f, 0.11866f,
   0.12666f, 0.13466f, 0.14269f, 0.15073f, 0.15880f, 0.16688f, 0.17498f, 0.18311f,
   0.19126f, 0.19943f, 0.20763f, 0.21586f, 0.22412f, 0.23240f, 0.24071f, 0.24906f,
   0.25744f, 0.26585f, 0.27430f, 0.28279f, 0.29131f, 0.29987f, 0.30847f, 0.31712f,
   0.32581f, 0.33454f, 0.34332f, 0.35214f, 0.36102f, 0.36994f, 0.37892f, 0.38795f,
   0.39704f, 0.40618f, 0.41539f, 0.42465f, 0.43398f, 0.44337f, 0.45282f, 0.46234f,
   0.47194f, 0.48160f, 0.49134f, 0.50115f, 0.51104f, 0.52101f, 0.53106f, 0.54120f,
   0.55143f, 0.56174f, 0.57214f, 0.58264f, 0.59324f, 0.60393f, 0.61473f, 0.62563f,
   0.63664f, 0.64777f, 0.65900f, 0.67035f, 0.68183f, 0.69342f, 0.70515f, 0.71700f,
   0.72899f, 0.74112f, 0.75339f, 0.76581f, 0.77838f, 0.79110f, 0.80398f, 0.81703f,
   0.83025f, 0.84363f, 0.85720f, 0.87096f, 0.88490f, 0.89904f, 0.91338f, 0.92793f,
   0.94269f, 0.95767f, 0.97288f, 0.98833f, 1.00401f, 1.01995f, 1.03615f, 1.05261f,
   1.06935f, 1.08637f, 1.10368f, 1.12130f, 1.13924f, 1.15749f, 1.17609f, 1.19503f,
   1.21433f, 1.23400f, 1.25406f, 1.27452f, 1.29540f, 1.31670f, 1.33845f, 1.36067f,
   1.38336f, 1.40656f, 1.43027f, 1.45453f, 1.47935f, 1.50475f, 1.53076f, 1.55741f,
   1.58471f
};

// yes, Real. No, really.
Real TheQuickSinTableCount = sizeof(TheQuickSinTable) / sizeof(Real);
Real TheQuickTanTableCount = sizeof(TheQuickTanTable) / sizeof(Real);

