//********************************************
// Tool.h
// Application
//********************************************
// feigz@ox.ios.ac.cn
// Created :
// Modified
//********************************************
#include "tooldoc.h"

/*
#if !defined(AFX_TOOL_H__06A35629_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
#define AFX_TOOL_H__06A35629_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_
*/
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CToolApp:
// See Tool.cpp for the implementation of this class
//

class CToolApp : public CWinApp
{
public:
	CToolApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CToolApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_TOOL_H__06A35629_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)


