// MyStarspaceView.h : interface of the CMyStarspaceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#undef PI               /* Some systems may have this defined. */
#define PI 3.141592657
#define MAXSTARS 400
#define MAXPOS 10000
#define MAXWARP 10
#define MAXANGLES 6000

enum {
  NORMAL = 0,
  WEIRD = 1
};

enum {
	STREAK = 0,
	CIRCLE = 1
};

typedef struct _starRec 
{
	GLint type;
    float x[2], y[2], z[2];
    float offsetX, offsetY, offsetR;
} starRec;

class CMyStarspaceView : public CView
{
protected: // create from serialization only
	CMyStarspaceView();
	DECLARE_DYNCREATE(CMyStarspaceView)

// Attributes
public:
	CMyStarspaceDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStarspaceView)
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
	virtual ~CMyStarspaceView();
/////////////////////////////////////////////////////////////////
//添加成员函数与成员变量
	BOOL RenderScene();
	BOOL SetupPixelFormat(void);
	void SetLogicalPalette(void);
	BOOL InitializeOpenGL(CDC* pDC);

	HGLRC		m_hRC;			//OpenGL绘制描述表
	HPALETTE	m_hPalette;		//OpenGL调色板
	CDC*	    m_pDC;			//OpenGL设备描述表
/////////////////////////////////////////////////////////////////
	void ShowStar(GLint n);
	void ShowStars(void);
	void Init(void);
	void RotatePoint(float *x, float *y, float rotation);
	float Sin(float angle);
	float Cos(float angle);
	void NewStar(GLint n, GLint d);
	void UpdateStars(void);
	void MoveStars(void);
	GLenum StarPoint(GLint n);

	GLint windW;
	GLint windH;
	GLenum flag ;
	GLint starCount ;
	float speed ;
	GLint nitro ;
	starRec stars[MAXSTARS];
	float sinTable[MAXANGLES];
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyStarspaceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyStarspaceView.cpp
inline CMyStarspaceDoc* CMyStarspaceView::GetDocument()
   { return (CMyStarspaceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
