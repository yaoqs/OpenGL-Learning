#if !defined(AFX_DLGCREATETINFROMFEATURE_H__F03A26A4_ED2D_46A5_AA52_075268AA2020__INCLUDED_)
#define AFX_DLGCREATETINFROMFEATURE_H__F03A26A4_ED2D_46A5_AA52_075268AA2020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCreateTINfromFeature.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateTINfromFeature dialog
#include "MainFrm.h"
#include "3D0214Doc.h"
#include "3D0214View.h"

class CDlgCreateTINfromFeature : public CDialog
{
// Construction
public:
	CDlgCreateTINfromFeature(CWnd* pParent = NULL);   // standard constructor
	void CreateTINfromFeature(IFeatureClass *ipfeat);
	IScenePtr m_ipScene;


// Dialog Data
	//{{AFX_DATA(CDlgCreateTINfromFeature)
	enum { IDD = IDD_DLG_CREATE_TIN };
	CEdit	m_Control_Output_Path;
	CComboBox	m_combo_TINHeightField;
	CComboBox	m_combo_TINTriangulateAs;
	CString	m_edit_TINInputs;
	CString	m_edit_TINOutput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateTINfromFeature)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCreateTINfromFeature)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboTinHeightField();
	afx_msg void OnSelchangeComboTinTriangu();
	afx_msg void OnButtonTinInputs();
	virtual void OnOK();
	afx_msg void OnButtonSavefilepath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	IFeatureClassPtr m_ipfeat;
	int m_selHIndex;
	int m_selTIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATETINFROMFEATURE_H__F03A26A4_ED2D_46A5_AA52_075268AA2020__INCLUDED_)
