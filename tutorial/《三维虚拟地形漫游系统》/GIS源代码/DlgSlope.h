#if !defined(AFX_DLGSLOPE_H__2766A879_D92F_4E9A_BACD_195CF6A7DC77__INCLUDED_)
#define AFX_DLGSLOPE_H__2766A879_D92F_4E9A_BACD_195CF6A7DC77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSlope.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSlope dialog

class CDlgSlope : public CDialog
{
// Construction
public:
	CDlgSlope(CWnd* pParent = NULL);   // standard constructor
	ITinPtr           m_ipT;
	IRasterDatasetPtr m_ipR;
	CString           m_OutputPath;
	CString           m_OutputRasterName_Slop;
	void CreateSlope(ITin*ipT);
	void CreateSlope(IRasterDataset*ipR);

// Dialog Data
	//{{AFX_DATA(CDlgSlope)
	enum { IDD = IDD_DLG_SLOPE };
	CString	m_edit_inputSurf_slope;
	double	m_edit_OutputCellsizeSlope;
	CString	m_edit_outputRaster_slope;
	int m_degree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSlope)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSlope)
	afx_msg void OnButtonInputsurfSlope();
	afx_msg void OnButtonOutputrasterSlope();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSLOPE_H__2766A879_D92F_4E9A_BACD_195CF6A7DC77__INCLUDED_)
