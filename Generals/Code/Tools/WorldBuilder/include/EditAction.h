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

#if !defined(AFX_EditAction_H__64465BA2_AD81_4EFD_BAB4_93F66C90ECD1__INCLUDED_)
#define AFX_EditAction_H__64465BA2_AD81_4EFD_BAB4_93F66C90ECD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditAction.h : header file
//


class ScriptAction;
class SidesList;

/////////////////////////////////////////////////////////////////////////////
// EditAction dialog

class EditAction : public CDialog
{
// Construction
public:
	EditAction(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EditAction)
	enum { IDD = IDD_ScriptAction };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditAction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	void setAction(ScriptAction *pAction) {m_action = pAction;}

protected:
	void formatScriptActionText(Int parmNdx);
protected:
	ScriptAction *m_action;
	Bool			m_updating;
	Bool			m_modifiedTextColor;
	CRichEditCtrl m_myEditCtrl;
	CHARRANGE m_curLinkChrg;
	Int				m_curEditParameter;

protected:

	// Generated message map functions
	//{{AFX_MSG(EditAction)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeScriptActionType();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EditAction_H__64465BA2_AD81_4EFD_BAB4_93F66C90ECD1__INCLUDED_)
