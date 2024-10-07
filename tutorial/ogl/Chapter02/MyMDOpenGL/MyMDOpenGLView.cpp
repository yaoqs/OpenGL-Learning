// MyMDOpenGLView.cpp : implementation of the CMyMDOpenGLView class
//

#include "stdafx.h"
#include "MyMDOpenGL.h"

#include "MyMDOpenGLDoc.h"
#include "MyMDOpenGLView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLView

IMPLEMENT_DYNCREATE(CMyMDOpenGLView, CGLEnabledView)

BEGIN_MESSAGE_MAP(CMyMDOpenGLView, CGLEnabledView)
	//{{AFX_MSG_MAP(CMyMDOpenGLView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLView construction/destruction

CMyMDOpenGLView::CMyMDOpenGLView()
{
	// TODO: add construction code here
/////////////////////////////////////////////////////////////////////////////
//初始化成员变量
	X_Angle=0.0;
	Y_Angle=0.0;
//////////////////////////////////////////////////////////////////////////////
}

CMyMDOpenGLView::~CMyMDOpenGLView()
{
}


/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLView printing

BOOL CMyMDOpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyMDOpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyMDOpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLView diagnostics

#ifdef _DEBUG
void CMyMDOpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void CMyMDOpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMDOpenGLDoc* CMyMDOpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMDOpenGLDoc)));
	return (CMyMDOpenGLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLView message handlers
void CMyMDOpenGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 记录鼠标的位置
	MouseDownPoint=point;
	// 捕捉鼠标的运动
	SetCapture();
	
//	CGLEnabledView::OnLButtonDown(nFlags, point);
}

void CMyMDOpenGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 鼠标按下位置置于原点
	MouseDownPoint=CPoint(0,0);
	// 解除捕捉鼠标
	ReleaseCapture();	
//	CGLEnabledView::OnLButtonUp(nFlags, point);
}

void CMyMDOpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 检测是否捕捉鼠标
	if (GetCapture()==this)
	{
	// 旋转对象一个步长
		X_Angle+=double(point.y-MouseDownPoint.y)/3.6;
		Y_Angle+=double(point.x-MouseDownPoint.x)/3.6;
	// 更新场景
		Invalidate(TRUE);
	// 记下鼠标位置
		MouseDownPoint=point;
	};	
//	CGLEnabledView::OnMouseMove(nFlags, point);
}


void CMyMDOpenGLView::OnDrawGL()
{
	glPushMatrix();
	// 旋转对象一个给定的角度
	glRotated(X_Angle,1.0,0.0,0.0);
	glRotated(Y_Angle,0.0,1.0,0.0);
	
	glBegin(GL_LINES);
		// yellow x axis arrow
		glColor3f(1.f,1.f,0.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,0.1f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,-0.1f,0.0f);
		// cyan y axis arrow
		glColor3f(0.f,1.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.1f,0.9f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-0.1f,0.9f,0.0f);
		// magenta z axis arrow
		glColor3f(1.f,0.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.1f,0.9f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,-0.1f,0.9f);
	glEnd();

	glutSolidSphere(0.2, 100, 100);

	glPopMatrix();


}


