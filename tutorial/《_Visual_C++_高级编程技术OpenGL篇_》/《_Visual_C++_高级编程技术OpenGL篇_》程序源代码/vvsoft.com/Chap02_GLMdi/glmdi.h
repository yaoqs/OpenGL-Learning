// glmdi.h : main header file for the GLMDI application
//

#if !defined(AFX_GLMDI_H__606EE8F1_E046_11D2_9DF8_0000214474ED__INCLUDED_)
#define AFX_GLMDI_H__606EE8F1_E046_11D2_9DF8_0000214474ED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGlmdiApp:
// See glmdi.cpp for the implementation of this class
//

class CGlmdiApp : public CWinApp
{
public:
	CGlmdiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlmdiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGlmdiApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLMDI_H__606EE8F1_E046_11D2_9DF8_0000214474ED__INCLUDED_)
