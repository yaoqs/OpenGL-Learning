// MyDlgOpenGLDlg.h : header file
//

#if !defined(AFX_MYDLGOPENGLDLG_H__C88233C1_49C0_40BC_82C3_CA672C7FD64D__INCLUDED_)
#define AFX_MYDLGOPENGLDLG_H__C88233C1_49C0_40BC_82C3_CA672C7FD64D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// 添加COpenGL类的说明文件
#include "opengl.h"
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMyDlgOpenGLDlg dialog

class CMyDlgOpenGLDlg : public CDialog
{
// Construction
public:
	CMyDlgOpenGLDlg(CWnd* pParent = NULL);	// standard constructor
/////////////////////////////////////////////////////////////////////////////
// 添加类的虚构函数和成员变量
	~CMyDlgOpenGLDlg(void);
	COpenGL *m_pDisplay;

	COpenGL *m_pDisplay1;
/////////////////////////////////////////////////////////////////////////////


// Dialog Data
	//{{AFX_DATA(CMyDlgOpenGLDlg)
	enum { IDD = IDD_MYDLGOPENGL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgOpenGLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlgOpenGLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLGOPENGLDLG_H__C88233C1_49C0_40BC_82C3_CA672C7FD64D__INCLUDED_)
