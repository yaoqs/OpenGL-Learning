// Terrain3DTestView.h : interface of the CTerrain3DTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
#define AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Texture.h"
#define	MAX_PARTICLES	250		// ��Ҫ������������Ŀ
#define MAX  500
struct vertex
{
	GLfloat x, y, z, light;
};

typedef struct						// ����һ�����ӵĽṹ
{
	bool	active;					// �����Ƿ��ڼ���״̬
	GLfloat	life;					// ���ӵ�����
	GLfloat	fade;					// ���ӵĵ����ٶ�
	GLfloat	r;						// ���ӵ���ɫ
	GLfloat	g;
	GLfloat	b;
	GLfloat	x;						// ���ӵ�λ������
	GLfloat	y;
	GLfloat	z;
	GLfloat	xi;						// ���ӵķ���ʸ��
	GLfloat	yi;	
	GLfloat	zi;
	GLfloat	xg;						// ���Ӽ��ٶ�ֵ
	GLfloat	yg;	
	GLfloat	zg;	
}
particles;

class Model;
class CTerrain3DTestView : public CView
{
protected: // create from serialization only
	CTerrain3DTestView();
	DECLARE_DYNCREATE(CTerrain3DTestView)

// Attributes
public:
	CTerrain3DTestDoc* GetDocument();

	Model *pModel;
	vertex field[MAX+9][MAX+9];
	particles particle[MAX_PARTICLES];
	Texture m_texture;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTerrain3DTestView)
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
	virtual ~CTerrain3DTestView();
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
	bool InitGL(GLvoid);
	bool InitTerrain(GLvoid);
	bool InitSmoke(GLvoid);
	bool DrawWireframe(GLvoid);
	bool DrawTexture(GLvoid);
	bool DrawWater(GLvoid);
	bool DrawSun(GLvoid);
	bool DrawPlane(GLvoid);
	bool DrawTerrain(GLvoid);
	bool DrawSky(GLvoid);
	void Caculate(GLvoid);
	GLfloat Hypot(GLfloat A, GLfloat B);
	GLfloat ABS(GLfloat A);
	void RestoreMyDefaultSettings();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTerrain3DTestView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Terrain3DTestView.cpp
inline CTerrain3DTestDoc* CTerrain3DTestView::GetDocument()
   { return (CTerrain3DTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGLVIEW_H__75C5AAEC_37B0_4A8B_9132_9A0C663F6DDC__INCLUDED_)
