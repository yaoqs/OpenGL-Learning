#if !defined(AFX_DLGSETSCENE_H__DABB9D0C_4FBF_43D9_AED4_E4617C05EA5A__INCLUDED_)
#define AFX_DLGSETSCENE_H__DABB9D0C_4FBF_43D9_AED4_E4617C05EA5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetScene.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetScene dialog
#include "MainFrm.h"
#include "3D0214Doc.h"
#include "3D0214View.h"

class CDlgSetScene : public CDialog
{
// Construction
public:
	CDlgSetScene(CWnd* pParent = NULL);   // standard constructor
	void SetExaggerationFactor(double factor);   //¥π÷±¿≠…Ï

// Dialog Data
	//{{AFX_DATA(CDlgSetScene)
	enum { IDD = IDD_DLD_SET_SCENE };
	double	m_edit_exaggerationFactor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetScene)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetScene)
	afx_msg void OnButtonExaggerationfactor();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETSCENE_H__DABB9D0C_4FBF_43D9_AED4_E4617C05EA5A__INCLUDED_)
