#if !defined(AFX_SKELETEN_H__97F4D45B_C926_11D1_85FD_987208C10000__INCLUDED_)
#define AFX_SKELETEN_H__97F4D45B_C926_11D1_85FD_987208C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Skeleten.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkeleten dialog

class CSkeleten : public CDialogBar
{
// Construction
public:
	CSkeleten();

// Dialog Data
	//{{AFX_DATA(CSkeleten)
	enum { IDD = CG_IDD_SKELETENDIALOGBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkeleten)
	public:
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CSkeleten)
	afx_msg void OnDeltaposSpinBodytype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinOrientationx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinOrientationy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinPositiony(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKELETEN_H__97F4D45B_C926_11D1_85FD_987208C10000__INCLUDED_)
