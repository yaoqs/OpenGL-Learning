// RenderView.cpp
// Created : 05/17/1999
// Modified: 10/26/1999
#include "stdafx.h"
#include "MyTemplate.h"
#include <GL/glaux.h>
#include <math.h>
#include "MyTemplateDoc.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CRenderView
IMPLEMENT_DYNCREATE(CRenderView, CView)

BEGIN_MESSAGE_MAP(CRenderView, CView)
//{{AFX_MSG_MAP(CRenderView)
ON_WM_DESTROY()
ON_WM_SIZE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_CREATE()
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CRenderView���캯��/destruction
CRenderView::CRenderView()
{
	// OpenGL
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;
	
	// Mouse
	m_LeftButtonDown = FALSE;
	m_RightButtonDown = FALSE;
	m_CursorRotation = AfxGetApp()->LoadCursor(IDC_CURSOR_ROTATION);

	// Colors
	CMyTemplateApp *pApp = (CMyTemplateApp *)AfxGetApp();
	InitGeometry();
}

// CRenderView��������
CRenderView::~CRenderView()
{
}

// ��ʼ��һЩȫ�ֱ���
void CRenderView::InitGeometry(void)
{
	m_xRotation = 0.0f;
	m_yRotation = 0.0f;
	m_xTranslation = 0.0f;
	m_yTranslation = 0.0f;
	m_zTranslation = -3.0f;
	m_xScaling = 0.5f;
	m_yScaling = 0.5f;
	m_zScaling = 0.5f;
}

BOOL CRenderView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CRenderView::OnDraw(CDC* pDC)
{
	CMyTemplateDoc *pDoc = GetDocument();
	ASSERT(pDoc);
}

// CRenderView��ӡ
BOOL CRenderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

// ��ʼ��ӡ
void CRenderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

// ������ӡ
void CRenderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

// CRenderView���
#ifdef _DEBUG
void CRenderView::AssertValid() const
{
	CView::AssertValid();
}

void CRenderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyTemplateDoc* CRenderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyTemplateDoc)));
	return (CMyTemplateDoc*)m_pDocument;
}
#endif //_DEBUG

// ��Ĵ�������
// ���������д���OpenGL�Ļ���������
int CRenderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if(SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	
	if(CreateViewGLContext(hDC)==FALSE)
		return 0;
	
	// ���ö���λ��Ƶ�ȱʡģʽ
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);
	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);

	// ���ù��ռ����ʵ�����
	GLfloat	ambientProperties[]  = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat	specularProperties[] = {0.0f, 0.8f, 0.2f, 1.0f};
	
	glClearDepth( 1.0f );

	m_ClearColorRed=1.0f;
	m_ClearColorGreen=1.0f;
	m_ClearColorBlue=1.0f;
	
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0f);

	// ȱʡ����¼ӹ���
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_ClearColorRed,m_ClearColorGreen,m_ClearColorBlue,1.0f);
	// ���ö�ʱ��Ϊ0.1��
	SetTimer( 0, 100, NULL);
	return 0;
}

// ���ô��ڵ����ظ�ʽ
BOOL CRenderView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;
	
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;
	
	m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
	if(m_GLPixelIndex == 0) // Choose default
	{
		m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
			return FALSE;
	}
	
	if(!SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc))
		return FALSE;
	
	return TRUE;
}

// ����һ��OpenGL����������
BOOL CRenderView::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	
	if(m_hGLContext==NULL)
		return FALSE;
	
	if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)
		return FALSE;
	
	return TRUE;
}

// �������OpenGL����������
// ���ٺ���
void CRenderView::OnDestroy() 
{
	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);
	
	if(m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
	
	CView::OnDestroy();
}

//  ���ڴ�С�仯��Ӧ����
void CRenderView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// ����OpenGLͶӰ���ӿں;���ģʽ
	CSize size(cx,cy);

	glViewport(0,0,size.cx,size.cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0f, 1.0f, 128.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);	
}

void CRenderView::OnLButtonDown(UINT nFlags, 
								CPoint point) 
{
	m_LeftButtonDown = TRUE;
	m_LeftDownPos = point;
	CView::OnLButtonDown(nFlags, point);
}

void CRenderView::OnLButtonUp(UINT nFlags, 
								CPoint point) 
{
	m_LeftButtonDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}

void CRenderView::OnMouseMove(UINT nFlags, 
							CPoint point) 
{
	if(m_LeftButtonDown)
	{
		m_xRotation += (float)(point.y - m_LeftDownPos.y) / 3.0f;
		m_yRotation += (float)(point.x - m_LeftDownPos.x) / 3.0f;
		m_LeftDownPos = point;
		InvalidateRect(NULL,FALSE);
	}
	CView::OnMouseMove(nFlags, point);
}

// ���ƺ���
void CRenderView::OnPaint() 
{
	// ���ڻ��Ƶ��豸������
	CPaintDC dc(this); 
	
	// Useful in singledoc templates
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	wglMakeCurrent(hDC,m_hGLContext);
	DrawWithOpenGL();
	// ʹ��˫����
	SwapBuffers(hDC); //dc.m_ps.hdc
}

// �ö�ʱ��ʵ��һ�μ򵥵Ķ�����ÿ֡��X�ᡢY��ֱ���ת1.0��
void CRenderView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
		{
		case 0:
			break;
		case 1:
			m_xRotation+=1.0f;
			m_yRotation+=1.0f;
			InvalidateRect(NULL,FALSE);
			break;
		default:
			{}
		}
}

void CRenderView::DrawWithOpenGL()
{
	// �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_ClearColorRed,m_ClearColorGreen,m_ClearColorBlue,1.0f);

	glPushMatrix();
	
	// ���š�ƽ�ơ���ת�任
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(m_xScaling,m_yScaling,m_zScaling);
	glTranslatef(m_xTranslation,m_yTranslation,m_zTranslation);
 	glRotatef(m_xRotation,1.0f,0.0f,0.0f);
	glRotatef(m_yRotation,0.0f,1.0f,0.0f);
    auxSolidSphere(1.0);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0f, 1.0f, 128.0);
	
	glPopMatrix();	
}
