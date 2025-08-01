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

// ClientRandomValue.h
// Random number generation system
// Author: Michael S. Booth, January 1998
// Split out into separate Logic/Client/Audio headers by MDC Sept 2002

#pragma once

#ifndef _CLIENT_RANDOM_VALUE_H_
#define _CLIENT_RANDOM_VALUE_H_

#include "Lib/BaseType.h"

// do NOT use these functions directly, rather use the macros below
extern Int GetGameClientRandomValue( int lo, int hi, char *file, int line );
extern Real GetGameClientRandomValueReal( Real lo, Real hi, char *file, int line );

// use these macros to access the random value functions
#define GameClientRandomValue( lo, hi ) GetGameClientRandomValue( lo, hi, __FILE__, __LINE__ )
#define GameClientRandomValueReal( lo, hi ) GetGameClientRandomValueReal( lo, hi, __FILE__, __LINE__ )

//--------------------------------------------------------------------------------------------------------------
class CColorAlphaDialog;
class DebugWindowDialog;

/**
 * A GameClientRandomVariable represents a distribution of random values
 * from which discrete values can be retrieved.
 */
class GameClientRandomVariable
{
public:
	// NOTE: This class cannot have a constructor or destructor due to its use within unions

	/**
	 * CONSTANT represents a single, constant, value.
	 * UNIFORM represents a uniform distribution of random values.
	 * GAUSSIAN represents a normally distributed set of random values.
	 * TRIANGULAR represents a distribution of random values in the shape
	 *		of a triangle, with the peak probability midway between low and high.
	 * LOW_BIAS represents a distribution of random values with
	 *		maximum probability at low, and zero probability at high.
	 * HIGH_BIAS represents a distribution of random values with
	 *		zero probability at low, and maximum probability at high.
	 */
	enum DistributionType 
	{ 
		CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
	};

	static const char *DistributionTypeNames[]; 

	/// define the range of random values, and the distribution of values
	void setRange( Real low, Real high, DistributionType type = UNIFORM );

	Real getValue( void ) const;														///< return a value from the random distribution
	inline Real getMinimumValue( void ) const { return m_low; }
	inline Real getMaximumValue( void ) const { return m_high; }
	inline DistributionType getDistributionType( void ) const { return m_type; }
protected:
	DistributionType m_type;																		///< the kind of random distribution
	Real m_low, m_high;																					///< the range of random values

	// These two friends are for particle editing.
	friend CColorAlphaDialog;
	friend DebugWindowDialog;

};

//--------------------------------------------------------------------------------------------------------------

#endif // _CLIENT_RANDOM_VALUE_H_
