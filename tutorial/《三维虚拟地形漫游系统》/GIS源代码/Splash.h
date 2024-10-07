#if !defined(AFX_SPLASH_H__65186F9E_8031_48FF_B83B_A0132B3834E1__INCLUDED_)
#define AFX_SPLASH_H__65186F9E_8031_48FF_B83B_A0132B3834E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Splash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplash window
#include "WZDBTMAP.H"

class CSplash : public CWnd
{
// Construction
public:
	CSplash();

// Attributes
public:

// Operations
public:
	void Create( UINT nID );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplash)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplash();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplash)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CWzdBitmap  m_bitmap;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASH_H__65186F9E_8031_48FF_B83B_A0132B3834E1__INCLUDED_)
