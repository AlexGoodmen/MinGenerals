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

// FILE: INIControlBarScheme.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Apr 2002
//
//	Filename: 	INIControlBarScheme.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	Parse a control Bar Scheme
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

#include "Common/INI.h"
#include "GameClient/ControlBar.h"
#include "GameClient/ControlBarScheme.h"
//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Parse a ControlBarScheme button */
//-------------------------------------------------------------------------------------------------
void INI::parseControlBarSchemeDefinition( INI *ini )
{
	AsciiString name;
	ControlBarSchemeManager *CBSchemeManager;
	ControlBarScheme *CBScheme;

	// read the name
	const char* c = ini->getNextToken();
	name.set( c );	

	// find existing item if present
	CBSchemeManager = TheControlBar->getControlBarSchemeManager();
	DEBUG_ASSERTCRASH( CBSchemeManager, ("parseControlBarSchemeDefinition: Unable to Get CBSchemeManager\n") );
	if( !CBSchemeManager )
		return;

	// If we have a previously allocated control bar, this will return a cleared out pointer to it so we
	// can overwrite it	
	CBScheme = CBSchemeManager->newControlBarScheme( name );

	// sanity
	DEBUG_ASSERTCRASH( CBScheme, ("parseControlBarSchemeDefinition: Unable to allocate Scheme '%s'\n", name.str()) );

	// parse the ini definition
	ini->initFromINI( CBScheme, CBSchemeManager->getFieldParse() );

}  // end parseCommandButtonDefinition


