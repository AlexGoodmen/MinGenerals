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

// FILE: INICommandButton.cpp /////////////////////////////////////////////////////////////////////
// Author: Colin Day, March 2002
// Desc:   Command buttons are the atomic units we can configure into command sets to then
//				 display in the context sensitive user interface
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "GameClient/ControlBar.h"

//-------------------------------------------------------------------------------------------------
/** Parse a command button */
//-------------------------------------------------------------------------------------------------
void INI::parseCommandButtonDefinition( INI *ini )
{
	ControlBar::parseCommandButtonDefinition(ini);
}

//-------------------------------------------------------------------------------------------------
/** Parse a command button */
//-------------------------------------------------------------------------------------------------
void ControlBar::parseCommandButtonDefinition( INI *ini )
{
	// read the name
	AsciiString name = ini->getNextToken();

	// find existing item if present
	CommandButton *button = TheControlBar->findNonConstCommandButton( name );
	if( button == NULL )
	{
		// allocate a new item
		button = TheControlBar->newCommandButton( name );
		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES) 
		{
			button->markAsOverride();
		}
	}  // end if
	else if( ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES )
	{
		DEBUG_CRASH(( "[LINE: %d in '%s'] Duplicate commandbutton %s found!", ini->getLineNum(), ini->getFilename().str(), name.str() ));
	}
	else
	{
		button = TheControlBar->newCommandButtonOverride( button );
	}

	// parse the ini definition
	ini->initFromINI( button, button->getFieldParse() );

}  // end parseCommandButtonDefinition


