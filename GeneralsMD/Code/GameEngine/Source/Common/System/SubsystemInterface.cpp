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

// FILE: SubsystemInterface.cpp 
// ----------------------------------------------------------------------------
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/SubsystemInterface.h"
#include "Common/Xfer.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#ifdef DUMP_PERF_STATS
#include "GameLogic/GameLogic.h"
#include "Common/PerfTimer.h"

Real SubsystemInterface::s_msConsumed = 0;
#endif

//-----------------------------------------------------------------------------
SubsystemInterface::SubsystemInterface()
#ifdef DUMP_PERF_STATS
:m_curDrawTime(0),
m_startDrawTimeConsumed(0),
m_startTimeConsumed(0),
m_curUpdateTime(0),
m_dumpUpdate(false),
m_dumpDraw(false)
#endif
{
	if (TheSubsystemList) {
		TheSubsystemList->addSubsystem(this);
	}
}


SubsystemInterface::~SubsystemInterface()
{
	if (TheSubsystemList) {
		TheSubsystemList->removeSubsystem(this);
	}
}

#ifdef DUMP_PERF_STATS
static const Real MIN_TIME_THRESHOLD = 0.0002f; // .2 msec. [8/13/2003]
void SubsystemInterface::UPDATE(void) 
{
	__int64 startTime64;
	__int64 endTime64,freq64;
	GetPrecisionTimerTicksPerSec(&freq64);
	GetPrecisionTimer(&startTime64);
	m_startTimeConsumed = s_msConsumed;
	update();
	GetPrecisionTimer(&endTime64);
	m_curUpdateTime = ((double)(endTime64-startTime64))/((double)(freq64));
	Real subTime = s_msConsumed - m_startTimeConsumed;
	if (m_name.isEmpty()) return;
	if (m_curUpdateTime>MIN_TIME_THRESHOLD) {
		m_dumpUpdate = true;
	}
	if (m_curUpdateTime > MIN_TIME_THRESHOLD/10.0f) {
		//DLOG(Debug::Format("Subsys %s total time %.2f, subTime %.2f, net time %.2f\n", 
		//	m_name.str(), m_curUpdateTime*1000, subTime*1000, (m_curUpdateTime-subTime)*1000	));

		m_curUpdateTime -= subTime;
		s_msConsumed += m_curUpdateTime;
	} else {
		m_curUpdateTime = 0;
	}

}																
void SubsystemInterface::DRAW(void) 
{
	__int64 startTime64;
	__int64 endTime64,freq64;
	GetPrecisionTimerTicksPerSec(&freq64);
	GetPrecisionTimer(&startTime64);
	m_startDrawTimeConsumed = s_msConsumed;
	draw();
	GetPrecisionTimer(&endTime64);
	m_curDrawTime = ((double)(endTime64-startTime64))/((double)(freq64));
	Real subTime = s_msConsumed - m_startDrawTimeConsumed;
	if (m_name.isEmpty()) return;
	if (m_curDrawTime>MIN_TIME_THRESHOLD) {
		m_dumpDraw = true;
	}
	if (m_curDrawTime > MIN_TIME_THRESHOLD/10.0f) {
		//DLOG(Debug::Format("Subsys %s total time %.2f, subTime %.2f, net time %.2f\n", 
		//	m_name.str(), m_curUpdateTime*1000, subTime*1000, (m_curUpdateTime-subTime)*1000	));

		m_curDrawTime -= subTime;
		s_msConsumed += m_curDrawTime;
	} else {
		m_curDrawTime = 0;
	}

}
#endif


//-----------------------------------------------------------------------------
SubsystemInterfaceList::SubsystemInterfaceList()
{
}

//-----------------------------------------------------------------------------
SubsystemInterfaceList::~SubsystemInterfaceList()
{
	DEBUG_ASSERTCRASH(m_subsystems.empty(), ("not empty"));
	shutdownAll();
}

//-----------------------------------------------------------------------------
void SubsystemInterfaceList::addSubsystem(SubsystemInterface* sys)
{
#ifdef DUMP_PERF_STATS
	m_allSubsystems.push_back(sys);
#endif
}
//-----------------------------------------------------------------------------
void SubsystemInterfaceList::removeSubsystem(SubsystemInterface* sys)
{
#ifdef DUMP_PERF_STATS
	for (SubsystemList::iterator it = m_allSubsystems.begin(); it != m_subsystems.end(); ++it)
	{	 
		if ( (*it) == sys) {
			m_allSubsystems.erase(it);
			break;
		}
	}
#endif
}
//-----------------------------------------------------------------------------
void SubsystemInterfaceList::initSubsystem(SubsystemInterface* sys, const char* path1, const char* path2, const char* dirpath, Xfer *pXfer, AsciiString name)
{
	sys->setName(name);
	sys->init();

	INI ini;
	if (path1)
		ini.load(path1, INI_LOAD_OVERWRITE, pXfer );
	if (path2)
		ini.load(path2, INI_LOAD_OVERWRITE, pXfer );
	if (dirpath)
		ini.loadDirectory(dirpath, TRUE, INI_LOAD_OVERWRITE, pXfer );

	m_subsystems.push_back(sys);
}

//-----------------------------------------------------------------------------
void SubsystemInterfaceList::postProcessLoadAll()
{
	for (SubsystemList::iterator it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
	{
		(*it)->postProcessLoad();
	}
}

//-----------------------------------------------------------------------------
void SubsystemInterfaceList::resetAll()
{
//	for (SubsystemList::iterator it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
	for (SubsystemList::reverse_iterator it = m_subsystems.rbegin(); it != m_subsystems.rend(); ++it)
	{
		(*it)->reset();
	}
}

//-----------------------------------------------------------------------------
void SubsystemInterfaceList::shutdownAll()
{
	// must go in reverse order!
	for (SubsystemList::reverse_iterator it = m_subsystems.rbegin(); it != m_subsystems.rend(); ++it)
	{
		SubsystemInterface* sys = *it;
		delete sys;
	}
	m_subsystems.clear();
}

#ifdef DUMP_PERF_STATS
//-----------------------------------------------------------------------------
AsciiString SubsystemInterfaceList::dumpTimesForAll()
{

	AsciiString buffer;
	buffer = "ALL SUBSYSTEMS:\n";
	//buffer.format("\nSUBSYSTEMS: total time %.2f MS\n", 
	//	SubsystemInterface::getTotalTime()*1000.0f);
	Real misc = 0;
	Real total = 0;
	SubsystemInterface::clearTotalTime();
	for (SubsystemList::reverse_iterator it = m_allSubsystems.rbegin(); it != m_allSubsystems.rend(); ++it)
	{
		SubsystemInterface* sys = *it;
		total += sys->getUpdateTime();
		if (sys->doDumpUpdate()) {
			AsciiString curLine;
			curLine.format("  Time %02.2f MS update() %s \n", sys->getUpdateTime()*1000.0f, sys->getName().str());
			buffer.concat(curLine);
		}	else {
			misc += sys->getUpdateTime();
		}
		total += sys->getDrawTime();
		if (sys->doDumpDraw()) {
			AsciiString curLine;
			curLine.format("  Time %02.2f MS  draw () %s \n", sys->getDrawTime()*1000.0f, sys->getName().str());
			buffer.concat(curLine);
		}	else {
			misc += sys->getDrawTime();
		}
	}
	AsciiString tmp;
	tmp.format("TOTAL %.2f MS, Misc time %.2f MS\n", total*1000.0f, misc*1000.0f);
	buffer.concat(tmp);
	return buffer;
}
#endif