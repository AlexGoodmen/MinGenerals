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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: SkirmishBattleHonors.cpp
// Author: Matthew D. Campbell, April 2002
// Description: Saving/Loading of skirmish battle honors info
///////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "Common/UserPreferences.h"
#include "Common/SkirmishBattleHonors.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/QuotedPrintable.h"
#include "Common/MultiplayerSettings.h"
#include "GameClient/MapUtil.h"

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE TYPES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE DATA ///////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC DATA ////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// SkirmishBattleHonors base class 
//-----------------------------------------------------------------------------

SkirmishBattleHonors::SkirmishBattleHonors()
{
	load("SkirmishStats.ini");
}

SkirmishBattleHonors::~SkirmishBattleHonors()
{
}

void SkirmishBattleHonors::setWins(Int val)
{
	setInt("Wins", val);
}

Int SkirmishBattleHonors::getWins(void) const
{
	return getInt("Wins", 0);
}

void SkirmishBattleHonors::setLosses(Int val)
{
	setInt("Losses", val);
}

Int SkirmishBattleHonors::getLosses(void) const
{
	return getInt("Losses", 0);
}

void SkirmishBattleHonors::setWinStreak(Int val)
{
	setInt("WinStreak", val);
}

Int SkirmishBattleHonors::getWinStreak(void) const
{
	return getInt("WinStreak", 0);
}

void SkirmishBattleHonors::setBestWinStreak(Int val)
{
	setInt("BestWinStreak", val);
}

Int SkirmishBattleHonors::getBestWinStreak(void) const
{
	return getInt("BestWinStreak", 0);
}

void SkirmishBattleHonors::setChallengeMedals(Int val)
{
	setInt("Challenge", val);
}

Int SkirmishBattleHonors::getChallengeMedals(void) const
{
	return getInt("Challenge", 0);
}

void SkirmishBattleHonors::setBuiltSCUD(void)
{
	setBool("SCUD", TRUE);
}

Bool SkirmishBattleHonors::builtSCUD(void) const
{
	return getBool("SCUD", FALSE);
}

void SkirmishBattleHonors::setBuiltParticleCannon(void)
{
	setBool("PPC", TRUE);
}

Bool SkirmishBattleHonors::builtParticleCannon(void) const
{
	return getBool("PPC", FALSE);
}

void SkirmishBattleHonors::setBuiltNuke(void)
{
	setBool("Nuke", TRUE);
}

Bool SkirmishBattleHonors::builtNuke(void) const
{
	return getBool("Nuke", FALSE);
}

void SkirmishBattleHonors::setHonors(Int which)
{
	Int honors = getInt("Honors", 0);
	setInt("Honors", honors | which);
}

Int SkirmishBattleHonors::getHonors(void) const
{
	return getInt("Honors", 0);
}

void SkirmishBattleHonors::setEnduranceMedal(AsciiString mapName, Int difficulty, int numAIs)
{
	AsciiString key;
	key.format("%s_%d", mapName.str(), difficulty);
	setInt(key, numAIs);
}

Int SkirmishBattleHonors::getEnduranceMedal(AsciiString mapName, Int difficulty) const
{
	AsciiString key;
	key.format("%s_%d", mapName.str(), difficulty);
	return getInt(key, 0);
}

void SkirmishBattleHonors::setLastGeneral(AsciiString val)
{
	setAsciiString("LastHouse", val);
}

AsciiString SkirmishBattleHonors::getLastGeneral(void) const
{
	return getAsciiString("LastHouse", AsciiString::TheEmptyString);
}

void SkirmishBattleHonors::setNumGamesLoyal(Int val)
{
	setInt("LoyalGames", val);
}

Int SkirmishBattleHonors::getNumGamesLoyal(void) const
{
	return getInt("LoyalGames", 0);
}

