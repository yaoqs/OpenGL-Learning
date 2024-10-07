// Step1View.h : interface of the CStep1View class
//
/////////////////////////////////////////////////////////////////////////////

#include "gl\gl.h"
#include "gl\glu.h"

#if !defined(AFX_STEP1VIEW_H__4D9DCF8F_170C_11D2_83B2_0080C832FCF3__INCLUDED_)
#define AFX_STEP1VIEW_H__4D9DCF8F_170C_11D2_83B2_0080C832FCF3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CStep1View : public CView
{
protected: // create from serialization only
	CStep1View();
	DECLARE_DYNCREATE(CStep1View)

// Attributes
public:
	CStep1Doc* GetDocument();

	CClientDC	*m_pDC;
	CRect  m_oldRect;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawScene();
	BOOL bSetupPixelFormat();
	void Init();
	virtual ~CStep1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStep1View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Step1View.cpp
inline CStep1Doc* CStep1View::GetDocument()
   { return (CStep1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP1VIEW_H__4D9DCF8F_170C_11D2_83B2_0080C832FCF3__INCLUDED_)
