#if !defined(AFX_DLGVIEWSHED_H__8CC3FDB9_8A82_46F4_A1FA_55BE55E8F05A__INCLUDED_)
#define AFX_DLGVIEWSHED_H__8CC3FDB9_8A82_46F4_A1FA_55BE55E8F05A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgViewshed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgViewshed dialog

class CDlgViewshed : public CDialog
{
// Construction
public:
	CDlgViewshed(CWnd* pParent = NULL);   // standard constructor
private:
	IRasterDatasetPtr m_ipR;
	ITinPtr           m_ipT;
	IFeatureClassPtr  m_ipfeat;
	CString           m_OutputPath;
	CString           m_OutputName;

public:
	void TintoRaster(ITin * ipT);
	void Viewshed();

// Dialog Data
	//{{AFX_DATA(CDlgViewshed)
	enum { IDD = IDD_DLG_VIEWSHED };
	CString	m_edit_viewshedSurfaceinput;
	CString	m_edit_viewshedRasteroutput;
	double	m_edit_viewshedCellsize;
	CString	m_edit_viewshedobserverpoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgViewshed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgViewshed)
	afx_msg void OnButtonViewshedObserverpoints();
	afx_msg void OnButtonViewshedRasteroutput();
	afx_msg void OnButtonViewshedSurfaceinput();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIEWSHED_H__8CC3FDB9_8A82_46F4_A1FA_55BE55E8F05A__INCLUDED_)
