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
 *                 Project Name : Command & Conquer                                            * 
 *                                                                                             * 
 *                     $Archive:: /Commando/Library/B64PIPE.CPP                               $* 
 *                                                                                             * 
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             * 
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             * 
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 *   Base64Pipe::Flush -- Flushes the final pending data through the pipe.                     *
 *   Base64Pipe::Put -- Processes a block of data through the pipe.                            *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include	"always.h"
#include	"b64pipe.h"
#include	"base64.h"
#include	<string.h>


/***********************************************************************************************
 * Base64Pipe::Put -- Processes a block of data through the pipe.                              *
 *                                                                                             *
 *    This will take the data submitted and either Base64 encode or decode it (as specified    *
 *    in the pipe's constructor). The nature of Base64 encoding means that the data will       *
 *    grow 30% in size when encoding and decrease by a like amount when decoding.              *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the data to be translated.                                  *
 *                                                                                             *
 *          length   -- The number of bytes to translate.                                      *
 *                                                                                             *
 * OUTPUT:  Returns with the actual number of bytes output at the far distant final end of     *
 *          the pipe chain.                                                                    *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int Base64Pipe::Put(void const * source, int slen)
{
	if (source == NULL || slen < 1) {
		return(Pipe::Put(source, slen));
	}

	int total = 0;

	char * from;
	int fromsize;
	char * to;
	int tosize;

	if (Control == ENCODE) {
		from = PBuffer;
		fromsize = sizeof(PBuffer);
		to = CBuffer;
		tosize = sizeof(CBuffer);
	} else {
		from = CBuffer;
		fromsize = sizeof(CBuffer);
		to = PBuffer;
		tosize = sizeof(PBuffer);
	}

	if (Counter > 0) {
		int len = (slen < (fromsize-Counter)) ? slen : (fromsize-Counter);
		memmove(&from[Counter], source, len);
		Counter += len;
		slen -= len;
		source = ((char *)source) + len;

		if (Counter == fromsize) {
			int outcount;
			if (Control == ENCODE) {
				outcount = Base64_Encode(from, fromsize, to, tosize);
			} else {
				outcount = Base64_Decode(from, fromsize, to, tosize);
			}
			total += Pipe::Put(to, outcount);
			Counter = 0;
		}
	}

	while (slen >= fromsize) {
		int outcount;
		if (Control == ENCODE) {
			outcount = Base64_Encode(source, fromsize, to, tosize);
		} else {
			outcount = Base64_Decode(source, fromsize, to, tosize);
		}
		source = ((char *)source) + fromsize;
		total += Pipe::Put(to, outcount);
		slen -= fromsize;
	}

	if (slen > 0) {
		memmove(from, source, slen);
		Counter = slen;
	}

	return(total);
}


/***********************************************************************************************
 * Base64Pipe::Flush -- Flushes the final pending data through the pipe.                       *
 *                                                                                             *
 *    If there is any non-processed data accumulated in the holding buffer (quite likely when  *
 *    encoding), then it will be processed and flushed out the end of the pipe.                *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the number of bytes output at the far distant final end of the pipe   *
 *          chain.                                                                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int Base64Pipe::Flush(void)
{
	int len = 0;

	if (Counter) {
		if (Control == ENCODE) {
			int chars = Base64_Encode(PBuffer, Counter, CBuffer, sizeof(CBuffer));
			len += Pipe::Put(CBuffer, chars);
		} else {
			int chars = Base64_Decode(CBuffer, Counter, PBuffer, sizeof(PBuffer));
			len += Pipe::Put(PBuffer, chars);
		}
		Counter = 0;
	}
	len += Pipe::Flush();
	return(len);
}



