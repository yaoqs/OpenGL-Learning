///////////////////////////////////////////////////////////////////////////////
// Written by Roman Grof, Solid Graphics, 1999
// http://www.solidgraphics.com

// CreateProjectFiles.h : main header file for the CreateProjectFiles application
//

#if !defined(AFX_CreateProjectFiles_H__DF18DE84_B0C3_11D2_BE63_0008C7406223__INCLUDED_)
#define AFX_CreateProjectFiles_H__DF18DE84_B0C3_11D2_BE63_0008C7406223__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCreateProjectFilesApp:
// See CreateProjectFiles.cpp for the implementation of this class
//

class CCreateProjectFilesApp : public CWinApp
{
public:
	CCreateProjectFilesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateProjectFilesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCreateProjectFilesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CreateProjectFiles_H__DF18DE84_B0C3_11D2_BE63_0008C7406223__INCLUDED_)
