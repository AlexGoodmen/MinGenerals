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

//----------------------------------------------------------------------------=
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information					                  
//                Copyright(C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:    WSYS Library
//
// Module:     IO
//
// File name:  LocalFile.h
//
// Created:    4/23/01
//
//----------------------------------------------------------------------------

#pragma once

#ifndef __LOCALFILE_H
#define __LOCALFILE_H



//----------------------------------------------------------------------------
//           Includes                                                      
//----------------------------------------------------------------------------

#include "Common/File.h"

// srj sez: this was purely an experiment in optimization.
// at the present time, it doesn't appear to be a good one.
// but I am leaving the code in for now.
// if still present in 2003, please nuke.
#define NO_USE_BUFFERED_IO
#ifdef USE_BUFFERED_IO
#include <stdio.h>
#endif

//----------------------------------------------------------------------------
//           Forward References
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//           Type Defines
//----------------------------------------------------------------------------

//===============================
// LocalFile
//===============================
/**
  *	File abstraction for standard C file operators: open, close, lseek, read, write
	*/
//===============================

class LocalFile : public File
{
	MEMORY_POOL_GLUE_ABC(LocalFile)		
	private:

#ifdef USE_BUFFERED_IO
		FILE* m_file;

		enum { BUF_SIZE = 32768 };
		char m_vbuf[BUF_SIZE];	
#else
		int m_handle;											///< Local C file handle
#endif
		
	public:
		
		LocalFile();										
		//virtual				~LocalFile();


		virtual Bool	open( const Char *filename, Int access = 0 );				///< Open a file for access
		virtual void	close( void );																			///< Close the file
		virtual Int		read( void *buffer, Int bytes );										///< Read the specified number of bytes in to buffer: See File::read
		virtual Int		write( const void *buffer, Int bytes );							///< Write the specified number of bytes from the buffer: See File::write
		virtual Int		seek( Int new_pos, seekMode mode = CURRENT );				///< Set file position: See File::seek
		virtual void	nextLine(Char *buf = NULL, Int bufSize = 0);				///< moves file position to after the next new-line
		virtual Bool	scanInt(Int &newInt);																///< return what gets read in as an integer at the current file position.
		virtual Bool	scanReal(Real &newReal);														///< return what gets read in as a float at the current file position.
		virtual	Bool	scanString(AsciiString &newString);									///< return what gets read in as a string at the current file position.
		/**
			Allocate a buffer large enough to hold entire file, read 
			the entire file into the buffer, then close the file.
			the buffer is owned by the caller, who is responsible
			for freeing is (via delete[]). This is a Good Thing to
			use because it minimizes memory copies for BIG files.
		*/
		virtual char* readEntireAndClose();
		virtual File* convertToRAMFile();

};




//----------------------------------------------------------------------------
//           Inlining                                                       
//----------------------------------------------------------------------------


#endif // __LOCALFILE_H
