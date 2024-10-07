#if !defined(AFX_DLGINFOQUERY_H__4397050D_36AC_44C9_A705_FEB5688F0F24__INCLUDED_)
#define AFX_DLGINFOQUERY_H__4397050D_36AC_44C9_A705_FEB5688F0F24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoQuery.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoQuery dialog

class CDlgInfoQuery : public CDialog
{
// Construction
public:
	CDlgInfoQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoQuery)
	enum { IDD = IDD_DLG_INFO_QUERY };
	CEdit	m_control_Z;
	CEdit	m_control_Y;
	CEdit	m_control_X;
	double	m_edit_X;
	double	m_edit_Y;
	double	m_edit_Z;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoQuery)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoQuery)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFOQUERY_H__4397050D_36AC_44C9_A705_FEB5688F0F24__INCLUDED_)
