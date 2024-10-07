#if !defined(AFX_DLGCREATECONTOUR_H__DD2617E5_B9E0_4B2C_A5D2_45D2EAEA9A62__INCLUDED_)
#define AFX_DLGCREATECONTOUR_H__DD2617E5_B9E0_4B2C_A5D2_45D2EAEA9A62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCreateContour.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateContour dialog

class CDlgCreateContour : public CDialog
{
// Construction
private:
	IRasterDatasetPtr m_ipR;
	ITinPtr m_ipT;
    ITinSurfacePtr m_ipTS;
	CString m_inputSurfaceDir;
	CString M_inputSurfaceName;
	CString m_OutputFeatureDir;
	CString m_OutputFeatureName;

public:
    void ComputerHeightRange(ITin *ipT);
	void ComputerHeightRange(IRasterDataset * pRasterDataset);
	void CreateContour();
	void CreateContour(IRasterDataset * ipR);
	void ComputerOutputInfo(double Zmax,double Zmin,double interval,double base);

public:
	CDlgCreateContour(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CDlgCreateContour)
	enum { IDD = IDD_DLG_CREATE_CONTOUR };
	CEdit	m_edit_Contour_ContourInterval;
	CEdit	m_edit_ContourBaseContour;
	CString	m_edit_Contour_SurfaceInput;
	CString	m_edit_ContourFeatureOutput;
	double	m_edit_Contour_MaxContour;
	double	m_edit_Contour_MinContour;
	double	m_edit_ContourZMax_in;
	double	m_edit_ContourZMin_in;
	UINT	m_edit_ContourTotalNumContour;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateContour)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCreateContour)
	afx_msg void OnButtonContourFeatureOutput();
	afx_msg void OnButtonContourSurfaceInput();
	virtual void OnOK();
	afx_msg void OnChangeEditContourBasecontour();
	afx_msg void OnChangeEditContourContourinterval();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATECONTOUR_H__DD2617E5_B9E0_4B2C_A5D2_45D2EAEA9A62__INCLUDED_)
