// MyTerrain2View.h : interface of the CMyTerrain2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXX 128	//���ε�������
#define MAXZ 128
#define SIZE 1		//����Ĵ�С
#define FY 2

typedef struct nodo {
	float x;		// �ӵ��x����
	float y;		// �ӵ��y����
	float z;		// �ӵ��z����
	float vx;		// �ӵ���x������ƶ��ٶ�
	float vy;		// �ӵ���y������ƶ��ٶ�
	float vz;		// �ӵ���z������ƶ��ٶ�
	double angolo;	
} PERSONA;

class CMyTerrain2View : public CView
{
protected: // create from serialization only
	CMyTerrain2View();
	DECLARE_DYNCREATE(CMyTerrain2View)

// Attributes
public:
	CMyTerrain2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTerrain2View)
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
	virtual ~CMyTerrain2View();
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
	void InitTerreno(void);
	int InitGL(GLvoid);
	void Superficie(void);		//���λ��ƺ���

	PERSONA Io;
	float Buffer[MAXX][MAXZ];
	float min,max;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyTerrain2View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyTerrain2View.cpp
inline CMyTerrain2Doc* CMyTerrain2View::GetDocument()
   { return (CMyTerrain2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
