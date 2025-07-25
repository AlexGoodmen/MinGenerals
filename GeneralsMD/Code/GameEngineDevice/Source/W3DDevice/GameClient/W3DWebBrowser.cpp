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

////// W3DWebBrowser.cpp ///////////////
// July 2002 Bryan Cleveland

#include "W3DDevice/GameClient/W3DWebBrowser.h"
#include "WW3D2/Texture.h"
#include "WW3D2/TextureLoader.h"
#include "WW3D2/SurfaceClass.h"
#include "GameClient/Image.h"
#include "GameClient/GameWindow.h"
#include "vector2i.h"
#include <d3dx8.h>
#include "WW3D2/dx8wrapper.h"
#include "WW3D2/dx8WebBrowser.h"

W3DWebBrowser::W3DWebBrowser() : WebBrowser() {
}

Bool W3DWebBrowser::createBrowserWindow(char *tag, GameWindow *win) 
{

	WinInstanceData *winData = win->winGetInstanceData();
	AsciiString windowName = winData->m_decoratedNameString;

	Int x, y, w, h;

	win->winGetSize(&w, &h);
	win->winGetScreenPosition(&x, &y);

	WebBrowserURL *url = findURL( AsciiString(tag) );

	if (url == NULL) {
		DEBUG_LOG(("W3DWebBrowser::createBrowserWindow - couldn't find URL for page %s\n", tag));
		return FALSE;
	}

	CComQIPtr<IDispatch> idisp(m_dispatch);
	if (m_dispatch == NULL)
	{
		return FALSE;
	}

	DX8WebBrowser::CreateBrowser(windowName.str(), url->m_url.str(), x, y, w, h, 0, BROWSEROPTION_SCROLLBARS | BROWSEROPTION_3DBORDER, (LPDISPATCH)this);

	return TRUE;
}

void W3DWebBrowser::closeBrowserWindow(GameWindow *win) 
{
	DX8WebBrowser::DestroyBrowser(win->winGetInstanceData()->m_decoratedNameString.str());
}
