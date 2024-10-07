#if !defined(AFX_DLGCREATERASTERIDW_H__81371ECB_D037_4EB3_ABA3_9E70D4C141E5__INCLUDED_)
#define AFX_DLGCREATERASTERIDW_H__81371ECB_D037_4EB3_ABA3_9E70D4C141E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCreateRasterIDW.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateRasterIDW dialog

class CDlgCreateRasterIDW : public CDialog
{
// Construction
public:
	CDlgCreateRasterIDW(CWnd* pParent = NULL);   // standard constructor
	void IDWOp(IFeatureClass * ipfeatureclass);

// Dialog Data
	//{{AFX_DATA(CDlgCreateRasterIDW)
	enum { IDD = IDD_DLG_CREATE_RASTER_IDW };
	CEdit	m_Control_IDWOutputRaster;
	CStatic	m_static_settings2;
	CStatic	m_static_settings1;
	CEdit	m_edit_settings2;
	CEdit	m_edit_settings1;
	CComboBox	m_combo_IDWsearchRadiusType;
	CComboBox	m_combo_IDWZvalueField;
	double	m_edit_IDWInputCellsize;
	CString	m_edit_IDWOutputRaster;
	CString	m_edit_IDWPointInput;
	double	m_edit_IDWPower;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateRasterIDW)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCreateRasterIDW)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboIdwSearchRadiusType();
	afx_msg void OnButtonIdwAddpointlayer();
	virtual void OnOK();
	afx_msg void OnButtonSelsaverasterpath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	IFeatureClassPtr m_ipfeat;
	int m_selIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATERASTERIDW_H__81371ECB_D037_4EB3_ABA3_9E70D4C141E5__INCLUDED_)
