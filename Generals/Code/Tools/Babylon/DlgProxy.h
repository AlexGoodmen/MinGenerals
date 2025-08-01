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

// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__2BF3124F_3BA1_11D3_B9DA_006097B90D93__INCLUDED_)
#define AFX_DLGPROXY_H__2BF3124F_3BA1_11D3_B9DA_006097B90D93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNoxstringDlg;

/////////////////////////////////////////////////////////////////////////////
// CNoxstringDlgAutoProxy command target

class CNoxstringDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CNoxstringDlgAutoProxy)

	CNoxstringDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CNoxstringDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoxstringDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNoxstringDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CNoxstringDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CNoxstringDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CNoxstringDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__2BF3124F_3BA1_11D3_B9DA_006097B90D93__INCLUDED_)
