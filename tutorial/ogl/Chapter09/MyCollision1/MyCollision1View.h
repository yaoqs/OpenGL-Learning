// MyCollision1View.h : interface of the CMyCollision1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector.h"
#include "matrix33.h"
#include "tray.h"
#include "image.h"
#include <mmsystem.h>
struct Plane
{
	        CVector _Position;
			CVector _Normal;
};
// Բ����ṹ
struct Cylinder
{                          
	   CVector _Position;
       CVector _Axis;
       double _Radius;
};
// ��ըЧ���ṹ
struct Explosion
{
	   CVector _Position;
	   float   _Alpha;
	   float   _Scale;
};

class CMyCollision1View : public CView
{
protected: // create from serialization only
	CMyCollision1View();
	DECLARE_DYNCREATE(CMyCollision1View)

// Attributes
public:
	CMyCollision1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCollision1View)
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
	virtual ~CMyCollision1View();
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
	int Init(GLvoid);
	int TestIntersionPlane(const Plane& plane,const CVector& position,const CVector& direction, double& lamda, CVector& pNormal);
	int TestIntersionCylinder(const Cylinder& cylinder,const CVector& position,const CVector& direction, double& lamda, CVector& pNormal,CVector& newposition);
	void LoadGLTextures();                    
	void InitVars();
	void idle();
	int FindBallCol(CVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2);

	CImage     m_MyImage;
	Plane pl1,pl2,pl3,pl4,pl5;        // �����е�5��ƽ��
	Cylinder cyl1,cyl2,cyl3;          // �����е�2��Բ����
	GLUquadricObj *cylinder_obj;
	GLuint texture[4], dlist;         // ��������������ʾ�б�
	Explosion ExplosionArray[20];     // ÿ�α������20����ը����

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCollision1View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyCollision1View.cpp
inline CMyCollision1Doc* CMyCollision1View::GetDocument()
   { return (CMyCollision1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
