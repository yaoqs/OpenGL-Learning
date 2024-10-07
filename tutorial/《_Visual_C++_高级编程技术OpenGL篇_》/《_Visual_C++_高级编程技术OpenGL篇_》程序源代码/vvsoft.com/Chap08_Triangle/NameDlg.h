#if !defined(AFX_NAMEDLG_H__107A67C0_CAAF_11D1_85FD_987208C10000__INCLUDED_)
#define AFX_NAMEDLG_H__107A67C0_CAAF_11D1_85FD_987208C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NameDlg dialog

class NameDlg : public CDialog
{
// Construction
public:
	NameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NameDlg)
	enum { IDD = IDD_DIALOG_NAME };
	CString	m_sName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NameDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMEDLG_H__107A67C0_CAAF_11D1_85FD_987208C10000__INCLUDED_)
