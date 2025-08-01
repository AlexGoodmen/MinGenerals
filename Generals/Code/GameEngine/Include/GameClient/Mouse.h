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

// FILE: Mouse.h //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information					         
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:    RTS3
//
// File name:  Mouse.h
//
// Created:    Michael S. Booth, January 1995
//						 Colin Day, June 2001
//
// Desc:       Basic mouse structure layout
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __MOUSE_H_
#define __MOUSE_H_

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Lib/BaseType.h"
#include "Common/SubsystemInterface.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////

// TYPE DEFINES ///////////////////////////////////////////////////////////////

enum MouseButtonState
{
	MBS_Up = 0,
	MBS_Down,
	MBS_DoubleClick,
};

#define MOUSE_MOVE_RELATIVE 0
#define MOUSE_MOVE_ABSOLUTE 1

// In frames
#define CLICK_SENSITIVITY		15

// In pixels
#define CLICK_DISTANCE_DELTA 10
#define CLICK_DISTANCE_DELTA_SQUARED (CLICK_DISTANCE_DELTA*CLICK_DISTANCE_DELTA)

//
#define MOUSE_WHEEL_DELTA		120

#define MOUSE_NONE		0x00
#define MOUSE_OK			0x01
#define MOUSE_FAILED	0x80
#define MOUSE_LOST		0xFF

#define	MOUSE_EVENT_NONE		0x00

class DisplayString;

#define MAX_2D_CURSOR_ANIM_FRAMES 21
#define MAX_2D_CURSOR_DIRECTIONS 8
// MouseIO --------------------------------------------------------------------
/** @todo this mouse structure needs to be revisited to allow for devices
with more than 3 buttons */
//-----------------------------------------------------------------------------
struct MouseIO
{

	ICoord2D pos;  ///< mouse pointer position
	UnsignedInt time;	///< The time that this message was posted.

	Int wheelPos;  /**< mouse wheel position, 0 is no event, + is up/away from
								 user while - is down/toward user */
	ICoord2D deltaPos;  ///< overall change in mouse pointer this frame

	MouseButtonState leftState;					// button state: Up, Down, DoubleClick (Which is also down)
	Int leftEvent;											// Most important event this frame
	Int leftFrame;											// last frame button state changed

	MouseButtonState rightState;
	Int rightEvent;
	Int rightFrame;

	MouseButtonState middleState;
	Int middleEvent;
	Int middleFrame;
};

class CursorInfo
{
public:
	CursorInfo();
	AsciiString		cursorName;
	AsciiString		cursorText;
	RGBAColorInt	cursorTextColor;
	RGBAColorInt	cursorTextDropColor;
	AsciiString		textureName;
	AsciiString		imageName;
	AsciiString		W3DModelName;
	AsciiString		W3DAnimName;
	Real					W3DScale;
	Bool					loop;
	ICoord2D			hotSpotPosition;
	Int						numFrames;
	Real					fps;	//frames per ms.
	Int						numDirections;	//number of directions for cursors like scrolling/panning.
};

// Mouse ----------------------------------------------------------------------
/** Class interface for working with a mouse pointing device */
//-----------------------------------------------------------------------------
class Mouse : public SubsystemInterface
{

public:  // enumerations and types

	// ----------------------------------------------------------------------------------------------
	/** If you update this enum make sure you update CursorININames[] */
	// ----------------------------------------------------------------------------------------------
	enum MouseCursor
	{
		
		// ***** dont forget to update CursorININames[] *****
		// ***** dont forget to update CursorININames[] *****
		// ***** dont forget to update CursorININames[] *****
		INVALID_MOUSE_CURSOR = -1,
		NONE = 0,
		FIRST_CURSOR,
		NORMAL = FIRST_CURSOR,
		ARROW,
		SCROLL,
		CROSS,
		MOVETO,
		ATTACKMOVETO,
		ATTACK_OBJECT,
		FORCE_ATTACK_OBJECT,
		FORCE_ATTACK_GROUND,
		BUILD_PLACEMENT,
		INVALID_BUILD_PLACEMENT,
		GENERIC_INVALID,
		SELECTING,
		// ***** dont forget to update CursorININames[] *****
		ENTER_FRIENDLY,
		ENTER_AGGRESSIVELY,
		SET_RALLY_POINT,
		GET_REPAIRED,
		GET_HEALED,
		DO_REPAIR,
		RESUME_CONSTRUCTION,
		CAPTUREBUILDING,
		// ***** dont forget to update CursorININames[] *****
		SNIPE_VEHICLE,
		LASER_GUIDED_MISSILES,
		TANKHUNTER_TNT_ATTACK,
		STAB_ATTACK,
		PLACE_REMOTE_CHARGE,
		// ***** dont forget to update CursorININames[] *****
		PLACE_TIMED_CHARGE,
		DEFECTOR,
#ifdef ALLOW_DEMORALIZE
		DEMORALIZE,
#endif
		DOCK,
		// ***** dont forget to update CursorININames[] *****
#ifdef ALLOW_SURRENDER
		PICK_UP_PRISONER,
		RETURN_TO_PRISON,
#endif
		FIRE_FLAME,
#ifdef ALLOW_SURRENDER
		FIRE_TRANQ_DARTS,
		FIRE_STUN_BULLETS,
#endif
		FIRE_BOMB,
		PLACE_BEACON,
		// ***** dont forget to update CursorININames[] *****
		DISGUISE_AS_VEHICLE,
		WAYPOINT,
		OUTRANGE,
		STAB_ATTACK_INVALID,
		PLACE_CHARGE_INVALID,
		HACK,
		PARTICLE_UPLINK_CANNON,


		// ***** dont forget to update CursorININames[] *****
		NUM_MOUSE_CURSORS  // keep this last

	};

	enum RedrawMode
	{

		RM_WINDOWS=0,	//default Windows cursor - very fast.
		RM_W3D,				//W3D model tied to frame rate.
		RM_POLYGON,		//alpha blended polygon tied to frame rate.
		RM_DX8,			//hardware cursor independent of frame rate.
		RM_MAX	// keep this last.
	};

	static const char *RedrawModeName[RM_MAX];

	CursorInfo m_cursorInfo[NUM_MOUSE_CURSORS];

public:

	Mouse( void );
	virtual ~Mouse( void );

	// you may need to extend these for your device
	virtual void parseIni(void);	///< parse ini settings associated with mouse (do this before init()).
	virtual void init( void );		///< init mouse, extend this functionality, do not replace
	virtual void reset( void );		///< Reset the system
	virtual void update( void );  ///< update the state of the mouse position and buttons
	virtual void initCursorResources(void)=0;	///< needed so Win32 cursors can load resources before D3D device created.

	virtual void createStreamMessages( void );  /**< given state of device, create 
																									 messages and put them on the 
																									 stream for the raw state. */
	
	virtual void draw( void );													///< draw the mouse
	virtual void setPosition( Int x, Int y );						///< set the mouse position
	virtual void setCursor( MouseCursor cursor ) = 0;		///< set mouse cursor

	virtual void capture( void ) = 0;					///< capture the mouse
	virtual void releaseCapture( void ) = 0;  ///< release mouse capture

	// access methods for the mouse data
	const MouseIO *getMouseStatus( void ) { return &m_currMouse; }							///< get current mouse status

  Int  getCursorTooltipDelay() { return m_tooltipDelay; }
  void setCursorTooltipDelay(Int delay) { m_tooltipDelay = delay; }

	void setCursorTooltip( UnicodeString tooltip, Int tooltipDelay = -1, const RGBColor *color = NULL, Real width = 1.0f );		///< set tooltip string at cursor
	void setMouseText( UnicodeString text, const RGBAColorInt *color, const RGBAColorInt *dropColor );					///< set the cursor text, *NOT* the tooltip text
	virtual void setMouseLimits( void );					///< update the limit extents the mouse can move in
	MouseCursor getMouseCursor(void) { return m_currentCursor; }	///< get the current mouse cursor image type
	virtual void setRedrawMode(RedrawMode mode)	{m_currentRedrawMode=mode;} ///<set cursor drawing method.
	virtual RedrawMode getRedrawMode(void) { return m_currentRedrawMode; } //get cursor drawing method
	virtual void setVisibility(Bool visible) { m_visible = visible; } // set visibility for load screens, etc
	inline Bool getVisibility(void) { return m_visible; } // get visibility state
	
	void drawTooltip( void );					///< draw the tooltip text
	void drawCursorText( void );			///< draw the mouse cursor text
	Int getCursorIndex( const AsciiString& name );
	void resetTooltipDelay( void );

	void mouseNotifyResolutionChange(void);

	Bool isClick(const ICoord2D *anchor, const ICoord2D *dest, UnsignedInt previousMouseClick, UnsignedInt currentMouseClick);
	
	AsciiString m_tooltipFontName;		///< tooltip font
	Int m_tooltipFontSize;						///< tooltip font
	Bool m_tooltipFontIsBold;					///< tooltip font
	Bool m_tooltipAnimateBackground;	///< animate the background with the text
	Int m_tooltipFillTime;						///< milliseconds to animate tooltip
	Int m_tooltipDelayTime;						///< milliseconds to wait before showing tooltip
	Real m_tooltipWidth;							///< default tooltip width in screen width %
	Real m_lastTooltipWidth;
	RGBAColorInt m_tooltipColorText;
	RGBAColorInt m_tooltipColorHighlight;
	RGBAColorInt m_tooltipColorShadow;
	RGBAColorInt m_tooltipColorBackground;
	RGBAColorInt m_tooltipColorBorder;
	RedrawMode	m_currentRedrawMode;	///< mouse cursor drawing method
	Bool m_useTooltipAltTextColor;		///< draw tooltip text with house colors?
	Bool m_useTooltipAltBackColor;		///< draw tooltip backgrounds with house colors?
	Bool m_adjustTooltipAltColor;			///< adjust house colors (darker/brighter) for tooltips?
	Bool m_orthoCamera;								///< use an ortho camera for 3D cursors?
	Real m_orthoZoom;									///< uniform zoom to apply to 3D cursors when using ortho cameras
	UnsignedInt m_dragTolerance;
	UnsignedInt m_dragTolerance3D;
	UnsignedInt m_dragToleranceMS;
	

protected:

	/// you must implement getting a buffered mouse event from you device here
	virtual UnsignedByte getMouseEvent( MouseIO *result, Bool flush ) = 0;

	//-----------------------------------------------------------------------------------------------

	// internal methods
	void updateMouseData( );													///< update the mouse with the current device data
	void processMouseEvent( Int eventToProcess );			///< combine mouse events into final data
	void checkForDrag( void );												///< check for mouse drag
	void moveMouse( Int x, Int y, Int relOrAbs );			///< move mouse by delta or absolute

	//---------------------------------------------------------------------------
	// internal mouse data members

	UnsignedByte m_numButtons;  ///< number of buttons on this mouse
	UnsignedByte m_numAxes;			///< number of axes this mouse has
	Bool m_forceFeedback;				///< set to TRUE if mouse supprots force feedback

	UnicodeString m_tooltipString;	///< tooltip text
	DisplayString *m_tooltipDisplayString; ///< tooltipDisplayString
	Bool m_displayTooltip;  /**< when the mouse has been still long enough this will be
													set to TRUE indicating it's Ok to fire off a tooltip */
	Bool m_isTooltipEmpty;

	enum { NUM_MOUSE_EVENTS = 256 };
	MouseIO m_mouseEvents[ NUM_MOUSE_EVENTS ];  ///< for event list
	MouseIO m_currMouse;												///< for current mouse data
	MouseIO m_prevMouse;												///< for previous mouse data

	Int m_minX;							///< mouse is locked to this region
	Int m_maxX;							///< mouse is locked to this region
	Int m_minY;							///< mouse is locked to this region
	Int m_maxY;							///< mouse is locked to this region

	UnsignedInt m_inputFrame;				///< frame input was gathered on
	UnsignedInt m_deadInputFrame;		///< Frame which last input occured

	Bool m_inputMovesAbsolute;			/**< if TRUE, when processing mouse position
																	chanages the movement will be done treating
																	the	coords as ABSOLUTE positions and NOT
																	relative coordinate changes */

	Bool m_visible;	// visibility status
	
	MouseCursor m_currentCursor;		///< current mouse cursor

	DisplayString *m_cursorTextDisplayString;		///< text to display on the cursor (if specified)
	RGBAColorInt m_cursorTextColor;							///< color of the cursor text
	RGBAColorInt m_cursorTextDropColor;					///< color of the cursor text drop shadow

  Int m_tooltipDelay;                                ///< millisecond delay for tooltips

	Int m_highlightPos;
	UnsignedInt m_highlightUpdateStart;
	UnsignedInt m_stillTime;
	RGBAColorInt m_tooltipTextColor;
	RGBAColorInt m_tooltipBackColor;

	Int m_eventsThisFrame;

};  // end class Mouse

// INLINING ///////////////////////////////////////////////////////////////////

// EXTERNALS //////////////////////////////////////////////////////////////////
extern Mouse *TheMouse;  ///< extern mouse singleton definition

#endif // _MOUSE_H_
