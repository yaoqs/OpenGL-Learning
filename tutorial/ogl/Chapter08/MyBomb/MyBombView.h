// MyBombView.h : interface of the CMyBombView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PMAX 32
#define FV 100
#define GRAVITY 0.001
#define FTIME 0.004

typedef struct
{
	double x;
	double y;
	double z;
} Vector;

typedef struct {
	bool active;
	float x;
	float y;
	float z;
	float dx;
	float dy;
	float dz;
	float time;
} PP;

class CMyBombView : public CView
{
protected: // create from serialization only
	CMyBombView();
	DECLARE_DYNCREATE(CMyBombView)

// Attributes
public:
	CMyBombDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBombView)
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
	virtual ~CMyBombView();
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
	int Init(GLvoid);
	void Drawbk(void);
	void Drawpp(void);
	void Makepp(void);
	void Makesp(void);
	void Movepp(void);
	double VectorLength( Vector v );
	Vector VectorNormalize( Vector v );
	Vector VectorMultiply( Vector v1, Vector v2 );
	Vector VectorScalarMultiply( Vector v, double s );
	Vector VectorDiff( Vector v1, Vector v2 );
	void Luce(double x, double y, double z,double dimensione,float r,float g,float b,float iox,float ioy,float ioz,int Tex);
	AUX_RGBImageRec *LoadBMP(char *Filename);
	int LoadGLTextures();
	
	PP pp[PMAX+1];
	GLuint	texture[3];			// 保存三个纹理
	GLUquadricObj *quadratic;	
	bool	active;		
	bool fcol;
	float dcol,rcol;
	int fcamera;
	float ancamera;
	float xcam,ycam,zcam;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyBombView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyBombView.cpp
inline CMyBombDoc* CMyBombView::GetDocument()
   { return (CMyBombDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
