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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Westwood Library                                             *
 *                                                                                             *
 *                     $Archive:: /G/wwlib/hashcalc.h                                         $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 4/02/99 11:59a                                              $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#ifndef HASHCALC_H
#define HASHCALC_H


/*
** HashCalculatorClass
** The hash calculator is used to abstract the process of computing a hash 
** value for an object.  Also, when dealing with floating point values, you
** may need to have a fudge factor and therefore have several valid hash
** values for a particular object (generated by adding and subtracting an
** epsilon to the number(s)).  This class lets you define any number
** of hash values.  This class is used by the UniqueArrayClass and the HashTableClass 
** templates.  Basically, you give one of these to the UniqueArrayClass at 
** construction time.  It will call the Num_Hash_Bits function in order to 
** properly allocate its hash table.  Then, for each object you pass into the 
** Add function, it  will call Compute_Hash, then it will loop through 
** Num_Hash_Values, calling Get_Hash_Value for each index and see if the object 
** is found in the indicated slot.  Also, when it is checking to see if it has 
** the object you "Added", the Items_Match function is called.  This again 
** allows you to do epsilon tests.  Make sense?  
*/
template <class T> class HashCalculatorClass
{
public:
	virtual bool	Items_Match(const T & a, const T & b) = 0;
	virtual void	Compute_Hash(const T & item) = 0;
	virtual int		Num_Hash_Bits(void) = 0;
	virtual int		Num_Hash_Values(void) = 0;
	virtual int		Get_Hash_Value(int index = 0) = 0;
};



#endif
