// ASELoaderView.h : interface of the CASELoaderView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPROJECTVIEW_H__6CC07ECC_CD06_4DF3_8FCA_227F6A29DA39__INCLUDED_)
#define AFX_MYPROJECTVIEW_H__6CC07ECC_CD06_4DF3_8FCA_227F6A29DA39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_TEXTURES 100								// The maximum amount of textures to load
#include "ASEReader.h"

class CASELoaderView : public CView
{
protected: // create from serialization only
	CASELoaderView();
	DECLARE_DYNCREATE(CASELoaderView)

// Attributes
public:
	CASELoaderDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CASELoaderView)
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
	virtual ~CASELoaderView();

	BOOL RenderScene();
	BOOL SetupPixelFormat(void);
	void SetLogicalPalette(void);
	BOOL InitializeOpenGL(CDC* pDC);

	HGLRC		m_hRC;			//OpenGL rendering context
	HPALETTE	m_hPalette;	
	CDC*	    m_pDC;

	void Init(GLvoid);
	void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID);

	CAseReader m_LoadASE;										// This is ASE class.  This should go in a good model class.
	t3DModel m_3DModel;										// This holds the 3D Model info that we load in
	int   m_ViewMode;					// We want the default drawing mode to be normal
	bool  m_bLighting;							// Turn lighting on initially
	float m_RotateX	;							// This is the current value at which the model is rotated
	float m_RotationSpeed ;							// This is the speed that our model rotates.  (-speed rotates left)


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CASELoaderView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ASELoaderView.cpp
inline CASELoaderDoc* CASELoaderView::GetDocument()
   { return (CASELoaderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROJECTVIEW_H__6CC07ECC_CD06_4DF3_8FCA_227F6A29DA39__INCLUDED_)
