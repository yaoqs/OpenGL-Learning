///////////////////////////////////////////////////////////////////////////////
// Written by Roman Grof, Solid Graphics, 1999
// http://www.solidgraphics.com

// CreateProjectFilesDlg.h : header file
//

#if !defined(AFX_CreateProjectFilesDLG_H__DF18DE86_B0C3_11D2_BE63_0008C7406223__INCLUDED_)
#define AFX_CreateProjectFilesDLG_H__DF18DE86_B0C3_11D2_BE63_0008C7406223__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCreateProjectFilesDlg dialog

class CCreateProjectFilesDlg : public CDialog
{
// Construction
public:
	CCreateProjectFilesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateProjectFilesDlg)
	enum { IDD = IDD_CREATEPROJECTFILES_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateProjectFilesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCreateProjectFilesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CreateProjectFilesDLG_H__DF18DE86_B0C3_11D2_BE63_0008C7406223__INCLUDED_)
