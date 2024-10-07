#if !defined(AFX_FRAME_H__B657C742_C98E_11D1_85FD_987208C10000__INCLUDED_)
#define AFX_FRAME_H__B657C742_C98E_11D1_85FD_987208C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Frame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrame dialog

class CFrame : public CDialogBar
{
// Construction
public:
	CFrame(); 

// Dialog Data
	//{{AFX_DATA(CFrame)
	enum { IDD = CG_IDD_FRAMEDIALOGBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrame)
	public:
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CFrame)
	afx_msg void OnDeltaposSpinSpeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeListAnimgroup();
	afx_msg void OnDblclkListAnimgroup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAME_H__B657C742_C98E_11D1_85FD_987208C10000__INCLUDED_)
