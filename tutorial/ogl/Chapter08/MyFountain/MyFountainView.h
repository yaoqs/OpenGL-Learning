// MyFountainView.h : interface of the CMyFountainView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyTexture.h"
#define PI 3.14159
struct particle
{
  float t;       // ���ӵ�������
  float v;       // �����˶����ٶ�
  float d;       // �����˶��ķ���
  float x, y, z; // ���ӵ�λ������
  float xd, zd;  // ���ӵ� X �� Z ��������ֵ
  char type;     // ��������(�˶��򵭻�)
  float a;       // ���� alpha ֵ
  struct particle *next, *prev;
};
struct point
{
  float x, y, z;
};

class CMyFountainView : public CView
{
protected: // create from serialization only
	CMyFountainView();
	DECLARE_DYNCREATE(CMyFountainView)

// Attributes
public:
	CMyFountainDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFountainView)
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
	virtual ~CMyFountainView();
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
	void Init();
	void DrawFountain();
	void normalize(struct point *V);
	void vect_mult(struct point *A, struct point *B, struct point *C);
	void DeleteParticles();
	void MoveParticles();
	void AddParticles();
	void LoadTexture(char *fn, int t_num);

	CMyTexture*  m_Tex;
	unsigned *teximage;     // ���ӵ�����
	GLuint texture[2];      // ��������
	float a;
	struct particle *fn[3]; // ��Ȫ
	struct point upv, cam;   

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFountainView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyFountainView.cpp
inline CMyFountainDoc* CMyFountainView::GetDocument()
   { return (CMyFountainDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
