// 3D0214.h : main header file for the 3D0214 application
//

#if !defined(AFX_3D0214_H__AC0C933F_B118_430A_A8D5_9B40390AC0EE__INCLUDED_)
#define AFX_3D0214_H__AC0C933F_B118_430A_A8D5_9B40390AC0EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy3D0214App:
// See 3D0214.cpp for the implementation of this class
//

class CMy3D0214App : public CWinApp
{
public:
	CMy3D0214App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3D0214App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy3D0214App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3D0214_H__AC0C933F_B118_430A_A8D5_9B40390AC0EE__INCLUDED_)
