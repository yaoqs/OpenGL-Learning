#if !defined(AFX_DLGPROFILEGRAPH_H__B8C04E72_488A_430F_AD05_07827E42A053__INCLUDED_)
#define AFX_DLGPROFILEGRAPH_H__B8C04E72_488A_430F_AD05_07827E42A053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProfileGraph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProfileGraph dialog

class CDlgProfileGraph : public CDialog
{
// Construction
public:
	CDlgProfileGraph(CWnd* pParent = NULL);   // standard constructor
public:
// Dialog Data
	//{{AFX_DATA(CDlgProfileGraph)
	enum { IDD = IDD_DLG_PROFILE_GRAPH };
	CStatic	m_static_ProfileGraph;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProfileGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProfileGraph)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROFILEGRAPH_H__B8C04E72_488A_430F_AD05_07827E42A053__INCLUDED_)
