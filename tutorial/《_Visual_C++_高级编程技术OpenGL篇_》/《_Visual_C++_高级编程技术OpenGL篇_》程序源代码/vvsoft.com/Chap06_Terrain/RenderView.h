//********************************************
// RenderView.h : interface of the CRenderView class
//********************************************
// feigz@ox.ios.ac.cn
// Created :
// Modified
//********************************************

#if !defined(AFX_RENDERVIEW_H__06A35633_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
#define AFX_RENDERVIEW_H__06A35633_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "glm.h"

class CToolDoc;

class CRenderView : public CView
{
protected: // create from serialization only
	CRenderView();
	DECLARE_DYNCREATE(CRenderView)

// Attributes
public:
	CToolDoc* GetDocument();
// Operations
public:
	// OpenGL specific
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);

	void MoveEye(int type, GLfloat amount, int update);
	void GenScean(void);
	void CheckHeight(void);
	void DrawTree(int x, int z);
	void MakeTexture(void);
    void TrackObj(void);
    void RenderTerrain();
	void MakeFireList();
	void GenFire();
	void DrawPatriot(void);
	void DrawPlane(void);
	void InitGeometry(void);

	HGLRC m_hGLContext;
	int m_GLPixelIndex;
	GLMmodel* patriot;
	GLMmodel* plane;

    float loop;
	BOOL  Shoot;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenderView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRenderView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRenderView)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#ifndef _DEBUG  // debug version in RenderView.cpp
inline CToolDoc* CRenderView::GetDocument()
   { return (CToolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENDERVIEW_H__06A35633_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
