#if !defined(AFX_DLGBASEHEIGHT_H__FB09CB35_A762_487A_AE53_D067996CE8D6__INCLUDED_)
#define AFX_DLGBASEHEIGHT_H__FB09CB35_A762_487A_AE53_D067996CE8D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBaseHeight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBaseHeight dialog
#include "MainFrm.h"
#include "3D0214Doc.h"
#include "3D0214View.h"
class CDlgBaseHeight : public CDialog
{
// Construction
public:
	CDlgBaseHeight(CWnd* pParent = NULL);   // standard constructor
	void SetBaseHeight();
	IScenePtr m_ipScene;

// Dialog Data
	//{{AFX_DATA(CDlgBaseHeight)
	enum { IDD = IDD_DIG_BASEHEIGHT };
	CComboBox	m_combo_layers;
	CComboBox	m_combo_currentlayer;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBaseHeight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBaseHeight)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBASEHEIGHT_H__FB09CB35_A762_487A_AE53_D067996CE8D6__INCLUDED_)
