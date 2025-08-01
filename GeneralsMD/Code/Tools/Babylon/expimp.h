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

//
// expimp.h
//

#ifndef __EXPIMP_H
#define __EXPIMP_H

#include "transDB.h"
#include "Babylondlg.h"

typedef enum
{
	TR_ALL,
	TR_CHANGES,
	TR_DIALOG,
	TR_NONDIALOG,
	TR_SAMPLE,
	TR_MISSING_DIALOG,
	TR_UNVERIFIED,
	TR_UNSENT
} TrFilter;

typedef struct 
{
	TrFilter filter;
	int include_comments;
	int include_translations;

} TROPTIONS;

typedef enum
{
	GN_UNICODE,
	GN_BABYLONSTR,
} GnFormat;

typedef enum
{
	GN_USEIDS,
	GN_USEORIGINAL,
} GnUntranslated;

typedef struct 
{
	GnFormat	format;								// what file format to generate
	GnUntranslated untranslated;		// what to do with untranslated text

} GNOPTIONS;

typedef struct 
{
	int translations;
	int dialog;
	int limit;

} RPOPTIONS;


#define CSF_ID ( ('C'<<24) | ('S'<<16) | ('F'<<8) | (' ') )
#define CSF_LABEL ( ('L'<<24) | ('B'<<16) | ('L'<<8) | (' ') )
#define CSF_STRING ( ('S'<<24) | ('T'<<16) | ('R'<<8) | (' ') )
#define CSF_STRINGWITHWAVE ( ('S'<<24) | ('T'<<16) | ('R'<<8) | ('W') )
#define CSF_VERSION 3

typedef struct
{
	int id;
	int version;
	int num_labels;
	int num_strings;
	int skip;	

} CSF_HEADER_V1;

typedef struct
{
	int id;
	int version;
	int num_labels;
	int num_strings;
	int skip;	
	int langid;

} CSF_HEADER;

int ExportTranslations ( TransDB *db, const char *filename, LangID langid, TROPTIONS *options, CBabylonDlg *dlg = NULL );
int ImportTranslations ( TransDB *db, const char *filename, CBabylonDlg *dlg = NULL );
int UpdateSentTranslations ( TransDB *db, const char *filename, CBabylonDlg *dlg = NULL );
int GenerateGameFiles ( TransDB *db, const char *filename, GNOPTIONS *option, LangID *languages, CBabylonDlg *dlg = NULL );
int GenerateReport ( TransDB *db, const char *filename, RPOPTIONS *options, LangID *languages, CBabylonDlg *dlg = NULL );
void ProcessWaves ( TransDB *db, const char *filename, CBabylonDlg *dlg );
#endif