// Step1View.cpp : implementation of the CStep1View class
//

#include "stdafx.h"
#include "Step1.h"

#include "Step1Doc.h"
#include "Step1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep1View

IMPLEMENT_DYNCREATE(CStep1View, CView)

BEGIN_MESSAGE_MAP(CStep1View, CView)
	//{{AFX_MSG_MAP(CStep1View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep1View construction/destruction

CStep1View::CStep1View()
{
	// TODO: add construction code here
	m_pDC=NULL;

}

CStep1View::~CStep1View()
{
}

BOOL CStep1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStep1View drawing

void CStep1View::OnDraw(CDC* pDC)
{
	CStep1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	DrawScene();
}

/////////////////////////////////////////////////////////////////////////////
// CStep1View diagnostics

#ifdef _DEBUG
void CStep1View::AssertValid() const
{
	CView::AssertValid();
}

void CStep1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStep1Doc* CStep1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStep1Doc)));
	return (CStep1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStep1View message handlers

void CStep1View::Init()
{
   PIXELFORMATDESCRIPTOR pfd;
    int         n;
	HGLRC		hrc;

    m_pDC = new CClientDC(this);
    ASSERT(m_pDC != NULL);
    if (!bSetupPixelFormat())
        return;

    n =::GetPixelFormat(m_pDC->GetSafeHdc());
    ::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
    hrc = wglCreateContext(m_pDC->GetSafeHdc());
    wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

    GetClientRect(&m_oldRect);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

BOOL CStep1View::bSetupPixelFormat()
{
static PIXELFORMATDESCRIPTOR pfd = 
{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
          PFD_SUPPORT_OPENGL,			// support OpenGL
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    int pixelformat;
    if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )
    {
        MessageBox("ChoosePixelFormat failed");
        return FALSE;
    }
    if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
        MessageBox("SetPixelFormat failed");
        return FALSE;
    }
    return TRUE;
}

int CStep1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	Init();
	
	return 0;
}

void CStep1View::DrawScene()
{
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(1.0f,1.0f);
	glEnd();
    glFinish();
}

void CStep1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(cy > 0)
    { 
	   if((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
            RedrawWindow();
        m_oldRect.right = cx;
        m_oldRect.bottom = cy;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1.0,1.0,-1.0,1.0,0.0,7.0);
        glViewport(0, 0, cx, cy);
    }
}

void CStep1View::OnDestroy() 
{
	// TODO: Add your message handler code here
	HGLRC	hrc;

	hrc = ::wglGetCurrentContext();
    ::wglMakeCurrent(NULL,  NULL);
    if (hrc)
        ::wglDeleteContext(hrc);
    if (m_pDC)
        delete m_pDC;
	CView::OnDestroy();
}
