// MyFireworkView.h : interface of the CMyFireworkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyTexture.h"
#define MAX_POINTS 400  //  爆炸粒子的最大数目
struct fire_point
{
  float dir;			//  粒子运动的方向
  float speed;			//  粒子的速度
  float r, g, b;		//  粒子的颜色
  float x;				//  粒子的坐标
};

struct firework
{
  int type;                         //  烟火的类型
  float x, y;                       //  主位置
  float t;                          //  生命时间
  float dir;                        //  方向
  int flag, counter;                //  标志，计数器
  struct fire_point fp[MAX_POINTS]; //  爆炸粒子
  struct firework *next;            // 下一个烟火
};

class CMyFireworkView : public CView
{
protected: // create from serialization only
	CMyFireworkView();
	DECLARE_DYNCREATE(CMyFireworkView)

// Attributes
public:
	CMyFireworkDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFireworkView)
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
	virtual ~CMyFireworkView();
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
	void InitializeTexture();
	void AddFirework();
	void Init();
	int WindW, WindH;	
	int i;
	unsigned *teximage;  //  粒子的纹理
	struct firework *fw;
	CMyTexture*  m_Tex;
	int rgb;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFireworkView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyFireworkView.cpp
inline CMyFireworkDoc* CMyFireworkView::GetDocument()
   { return (CMyFireworkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
