// MyDlgOpenGL.h : main header file for the MYDLGOPENGL application
//

#if !defined(AFX_MYDLGOPENGL_H__778DC4F6_4619_4A56_9A9E_2F3AFB310B03__INCLUDED_)
#define AFX_MYDLGOPENGL_H__778DC4F6_4619_4A56_9A9E_2F3AFB310B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyDlgOpenGLApp:
// See MyDlgOpenGL.cpp for the implementation of this class
//

class CMyDlgOpenGLApp : public CWinApp
{
public:
	CMyDlgOpenGLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgOpenGLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyDlgOpenGLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLGOPENGL_H__778DC4F6_4619_4A56_9A9E_2F3AFB310B03__INCLUDED_)
