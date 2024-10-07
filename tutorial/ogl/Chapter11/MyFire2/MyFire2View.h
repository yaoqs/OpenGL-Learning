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
//��ӳ�Ա�������Ա����
	BOOL RenderScene();
	BOOL SetupPixelFormat(void);
	void SetLogicalPalette(void);
	BOOL InitializeOpenGL(CDC* pDC);

	HGLRC		m_hRC;			//OpenGL����������
	HPALETTE	m_hPalette;		//OpenGL��ɫ��
	CDC*	    m_pDC;			//OpenGL�豸������
/////////////////////////////////////////////////////////////////
	bool InitParticleSystem(void);
	void InitGL(GLvoid);
	POINTVECTOR vCamPos;// �����λ������
	// ֡�ĳ��ȼ���
	float fStartFrameTime;
	float fEndFrameTime;
	float fTime;
	// ��ǰ�����Ԥ��
	int iFrames ;
	int iFramesPerSec;
	int iParticleTexture ;// ���ӵ�ǰʹ�õ�����
	bool bIsBurstEnable ;// ��ըЧ���Ƿ񼤻�
	bool bIsCamFollowing ;// �Ƿ�������������
	CParticleSystem* pPS ;
	// ���������
	float fCameraRadius ;
	float fCameraYaw ;
	float fCameraPitch ;
	float fCamRotX,fCamRotY;
	GLuint tList[7];// �����������
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
