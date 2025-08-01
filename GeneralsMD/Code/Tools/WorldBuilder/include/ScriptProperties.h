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

#if !defined(AFX_SCRIPTPROPERTIES_H__CE62125B_9FAB_4EF0_A8B5_36DD5393A2B0__INCLUDED_)
#define AFX_SCRIPTPROPERTIES_H__CE62125B_9FAB_4EF0_A8B5_36DD5393A2B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScriptProperties.h : header file
//
class Script;
/////////////////////////////////////////////////////////////////////////////
// ScriptProperties dialog

class ScriptProperties : public CPropertyPage
{
	DECLARE_DYNCREATE(ScriptProperties)

// Construction
public:
	ScriptProperties();
	~ScriptProperties();

// Dialog Data
	//{{AFX_DATA(ScriptProperties)
	enum { IDD = IDD_ScriptProperties };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(ScriptProperties)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void setScript(Script *pScript) {m_script = pScript;}
protected:
	void enableControls(void);

protected:
	Script *m_script;
	Bool	 m_updating;

protected:
	// Generated message map functions
	//{{AFX_MSG(ScriptProperties)
	afx_msg void OnChangeScriptComment();
	afx_msg void OnChangeScriptName();
	afx_msg void OnScriptActive();
	afx_msg void OnOneShot();
	afx_msg void OnEasy();
	afx_msg void OnHard();
	afx_msg void OnNormal();
	afx_msg void OnScriptSubroutine();
	afx_msg void OnEveryFrame();
	afx_msg void OnEverySecond();
	afx_msg void OnChangeSecondsEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTPROPERTIES_H__CE62125B_9FAB_4EF0_A8B5_36DD5393A2B0__INCLUDED_)
