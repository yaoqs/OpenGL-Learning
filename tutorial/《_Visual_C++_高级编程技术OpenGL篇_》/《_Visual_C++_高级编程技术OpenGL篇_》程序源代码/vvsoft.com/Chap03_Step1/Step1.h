// Step1.h : main header file for the STEP1 application
//

#if !defined(AFX_STEP1_H__4D9DCF87_170C_11D2_83B2_0080C832FCF3__INCLUDED_)
#define AFX_STEP1_H__4D9DCF87_170C_11D2_83B2_0080C832FCF3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStep1App:
// See Step1.cpp for the implementation of this class
//

class CStep1App : public CWinApp
{
public:
	CStep1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStep1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP1_H__4D9DCF87_170C_11D2_83B2_0080C832FCF3__INCLUDED_)
