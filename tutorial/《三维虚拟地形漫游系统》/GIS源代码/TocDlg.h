//{{AFX_INCLUDES()
#include "toccontroldefault.h"
//}}AFX_INCLUDES
#if !defined(AFX_TOCDLG_H__9D922A8E_AB1D_45B1_8362_B25849F54D87__INCLUDED_)
#define AFX_TOCDLG_H__9D922A8E_AB1D_45B1_8362_B25849F54D87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TocDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTocDlg dialog

class CTocDlg : public CDialog
{
// Construction
public:
	CTocDlg(CWnd* pParent = NULL);   // standard constructor

//	IToolbarMenuPtr    m_ipToolbarMenu;
//	ICommandPtr        m_DelCmd;       // 命令
//    IPutLayerNamePtr   ipDl;           // 删除图层组件图层名传递接口
//    IPutLayerNamePtr   ipUl;           // 上移图层组件图层名传递接口
//    IPutLayerNamePtr   ipNl;           // 下移图层组件图层名传递接口 
//    ICommandPoolPtr    m_CmdPool;      // 命令池

// Dialog Data
	//{{AFX_DATA(CTocDlg)
	enum { IDD = IDD_TOCDLG };
	CTOCControlDefault	m_TocControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTocDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTocDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOnMouseDownToccontrol1(long button, long shift, long x, long y);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOCDLG_H__9D922A8E_AB1D_45B1_8362_B25849F54D87__INCLUDED_)
