// MyFlareView.h : interface of the CMyFlareView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "loadlum.h"
#include "myvec3d.h"

typedef struct t_flare {
  int type;             // flare纹理
  float scale;
  float loc;            
  GLfloat color[3];
} Flare;

class CMyFlareView : public CView
{
protected: // create from serialization only
	CMyFlareView();
	DECLARE_DYNCREATE(CMyFlareView)

// Attributes
public:
	CMyFlareDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFlareView)
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
	virtual ~CMyFlareView();
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
	void Init(GLvoid);
	void DoBackground(void);
	void DoFlares(GLfloat from[3], GLfloat at[3], GLfloat light[3], GLfloat near_clip);
	void init_flares(void);
	void load_textures(void);
	Flare set_flare(int type, float location, float scale, GLfloat color[3], float colorScale);
	void setup_texture(char *filename, GLuint texobj,GLenum minFilter, GLenum maxFilter);

	Flare flare[20];
	int num_flares;
	float tic ;
	float position[3];
	int shine_tic ;
	GLfloat from[3] ;
	GLfloat at[3] ;
	GLfloat near_clip ;
	int useMipmaps, verbose;
	GLuint logoTex, flareTex[6], shineTex[10];
	CLoadLUM m_LoadLUM;
	CMyVec3D m_MyVec;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFlareView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyFlareView.cpp
inline CMyFlareDoc* CMyFlareView::GetDocument()
   { return (CMyFlareDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
