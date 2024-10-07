// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "Skeleten.h"
#include "frame.h"

class CTriangleView;

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	HTREEITEM body;
	HTREEITEM upper_body;
	HTREEITEM lower_body;
	HTREEITEM left_arm;
	HTREEITEM right_arm;
	HTREEITEM left_leg;
	HTREEITEM right_leg;
	HTREEITEM left_upper_arm;
	HTREEITEM right_upper_arm;
	HTREEITEM left_lower_arm;
	HTREEITEM right_lower_arm;
	HTREEITEM left_hand;
	HTREEITEM right_hand;
	HTREEITEM left_upper_leg;
	HTREEITEM right_upper_leg;
	HTREEITEM left_lower_leg;
	HTREEITEM right_lower_leg;
	HTREEITEM left_foot;
	HTREEITEM right_foot;
	HTREEITEM head;
	HTREEITEM shoulder;

	HICON m_hIcon;

	CTriangleView *m_pView;

	int body_id;

	void SetCurrentView(CTriangleView *pView) { m_pView = pView; };
	void SetRoot(void);
	void SpinScroll(int id, UINT updown);
	void SetCurrentBodyToTree(int body_id);
	void UpdateOrientation(int body_id, float x, float y);
	void UpdatePosition(float height);
	void UpdateFrame(int iCurrentFrame, int iMaxFrame);
	void AddGroupString(CString *str);
	void DelGroupString(CString *str);
	void SetCurrentAnim(CString *str);
	void GetCurrentAnim(CString *str);
	void ListBoxChange(int  i, CString &str);
	void ChangeGroupName(void);
	void PlaySpeed(int updown);
	void UpdatePlaySpeedInfo(int iplayspeed);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	CFrame m_wndFrameDialogBar;
	CSkeleten m_wndSkeletenDialogBar;
	CToolBar    m_wndManipulateBar;
	CToolBar	m_wndAttributeBar;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonAddGroup();
	afx_msg void OnButtonDelGroup();
	afx_msg void OnButtonAddFrame();
	afx_msg void OnButtonDelFrame();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonPrev();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonLast();
	afx_msg void OnToggleAttributebar();
	afx_msg void OnUpdateToggleAttributebar(CCmdUI* pCmdUI);
	afx_msg void OnToggleManipulatebar();
	afx_msg void OnUpdateToggleManipulatebar(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
/////////////////////////////////////////////////////////////////////////////
