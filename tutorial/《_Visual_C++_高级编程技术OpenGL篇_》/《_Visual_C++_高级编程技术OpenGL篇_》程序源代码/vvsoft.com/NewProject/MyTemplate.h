//********************************************
// MyTemplate.h
// Application
//********************************************
// Created :
// Modified
//********************************************
#include "MyTemplatedoc.h"

/*
#if !defined(AFX_MyTemplate_H__06A35629_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
#define AFX_MyTemplate_H__06A35629_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_
*/
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyTemplateApp:
// See MyTemplate.cpp for the implementation of this class
//

class CMyTemplateApp : public CWinApp
{
public:
	CMyTemplateApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTemplateApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyTemplateApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_MyTemplate_H__06A35629_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)


