// MyFire2View.h : interface of the CMyFire2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Particle.h"
#include "ParticleSystem.h"
#include "loadbmp.h"

class CMyFire2View : public CView
{
protected: // create from serialization only
	CMyFire2View();
	DECLARE_DYNCREATE(CMyFire2View)

// Attributes
public:
	CMyFire2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFire2View)
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
	virtual ~CMyFire2View();
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
	bool InitParticleSystem(void);
	void InitGL(GLvoid);
	POINTVECTOR vCamPos;// 摄像机位置坐标
	// 帧的长度计算
	float fStartFrameTime;
	float fEndFrameTime;
	float fTime;
	// 当前激活的预设
	int iFrames ;
	int iFramesPerSec;
	int iParticleTexture ;// 粒子当前使用的纹理
	bool bIsBurstEnable ;// 爆炸效果是否激活
	bool bIsCamFollowing ;// 是否采用摄像机跟踪
	CParticleSystem* pPS ;
	// 摄像机变量
	float fCameraRadius ;
	float fCameraYaw ;
	float fCameraPitch ;
	float fCamRotX,fCamRotY;
	GLuint tList[7];// 纹理对象序列
	CLoadBMP m_Loadbmp;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFire2View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyFire2View.cpp
inline CMyFire2Doc* CMyFire2View::GetDocument()
   { return (CMyFire2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
