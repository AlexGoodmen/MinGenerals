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

// FILE: AutoDepositUpdate.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Aug 2002
//
//	Filename: 	AutoDepositUpdate.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	The meat of the auto deposit update module
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/BuildAssistant.h"
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/INI.h"
#include "Common/RandomValue.h"
#include "Common/Player.h"
#include "Common/Xfer.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AutoDepositUpdate.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Object.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Color.h"
#include "GameClient/GameText.h"
//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
AutoDepositUpdate::AutoDepositUpdate( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
	m_depositOnFrame = TheGameLogic->getFrame() + getAutoDepositUpdateModuleData()->m_depositFrame;
	m_awardInitialCaptureBonus = FALSE;
	m_initialized = FALSE;
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
AutoDepositUpdate::~AutoDepositUpdate( void )
{

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void AutoDepositUpdate::awardInitialCaptureBonus( Player *player )
{
	m_depositOnFrame = TheGameLogic->getFrame() + getAutoDepositUpdateModuleData()->m_depositFrame;
	if(!player || !m_awardInitialCaptureBonus || getAutoDepositUpdateModuleData()->m_initialCaptureBonus <= 0)
		return;

	player->getMoney()->deposit( getAutoDepositUpdateModuleData()->m_initialCaptureBonus );
	player->getScoreKeeper()->addMoneyEarned( getAutoDepositUpdateModuleData()->m_initialCaptureBonus );

	//Display cash income floating over the blacklotus
	if(getAutoDepositUpdateModuleData()->m_initialCaptureBonus > 0)
	{
		UnicodeString moneyString;
		moneyString.format( TheGameText->fetch( "GUI:AddCash" ), getAutoDepositUpdateModuleData()->m_initialCaptureBonus );
		Coord3D pos;
		pos.set( getObject()->getPosition() );
		pos.z += 10.0f; //add a little z to make it show up above the unit.
		Color color = player->getPlayerColor() | GameMakeColor( 0, 0, 0, 230 );
		TheInGameUI->addFloatingText( moneyString, &pos, color );
	}

	m_awardInitialCaptureBonus = FALSE;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
UpdateSleepTime AutoDepositUpdate::update( void )
{
/// @todo srj use SLEEPY_UPDATE here
	if( TheGameLogic->getFrame() >= m_depositOnFrame)
	{
		if (!m_initialized) {
			// Note - we have to set these in update, because during load the team is set, 
			// and we don't want to award initial bonus on load.  jba :)
			m_awardInitialCaptureBonus = TRUE;
			m_initialized = TRUE;
		}
		m_depositOnFrame = TheGameLogic->getFrame() + getAutoDepositUpdateModuleData()->m_depositFrame;
		
		if(getObject()->isNeutralControlled() || getAutoDepositUpdateModuleData()->m_depositAmount <= 0 )
			return UPDATE_SLEEP_NONE;

		// makes sure that buildings under construction do not get a bonus CCB
		if( getObject()->getConstructionPercent() != CONSTRUCTION_COMPLETE )
			return UPDATE_SLEEP_NONE;
		
		getObject()->getControllingPlayer()->getMoney()->deposit( getAutoDepositUpdateModuleData()->m_depositAmount);
		getObject()->getControllingPlayer()->getScoreKeeper()->addMoneyEarned( getAutoDepositUpdateModuleData()->m_depositAmount);
		
		//Display cash income floating over the blacklotus
		if(getAutoDepositUpdateModuleData()->m_depositAmount > 0)
		{
			UnicodeString moneyString;
			moneyString.format( TheGameText->fetch( "GUI:AddCash" ), getAutoDepositUpdateModuleData()->m_depositAmount );
			Coord3D pos;
			pos.set( getObject()->getPosition() );
			pos.z += 10.0f; //add a little z to make it show up above the unit.
			Color color = getObject()->getControllingPlayer()->getPlayerColor() | GameMakeColor( 0, 0, 0, 230 );
			TheInGameUI->addFloatingText( moneyString, &pos, color );
		}
		
	}

	return UPDATE_SLEEP_NONE;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void AutoDepositUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AutoDepositUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 2;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// deposit on frame
	xfer->xferUnsignedInt( &m_depositOnFrame );

	// award initial capture bonus
	xfer->xferBool( &m_awardInitialCaptureBonus );
	if (version>1) {
		xfer->xferBool(&m_initialized);
	}

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void AutoDepositUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
