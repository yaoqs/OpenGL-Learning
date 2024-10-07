// MyTerrain2View.cpp : implementation of the CMyTerrain2View class
//

#include "stdafx.h"
#include "MyTerrain2.h"

#include "MyTerrain2Doc.h"
#include "MyTerrain2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
float land[]= {
0.0f,0.0f,0.0f,1.0f,	// 绿色
0.0f,0.0f,0.0f,1.0f,
0.0f,0.0f,0.015625f,1.0f,
0.0f,0.0f,0.046875f,1.0f,
0.0f,0.0f,0.0625f,1.0f,
0.0f,0.0f,0.09375f,1.0f,
0.0f,0.0f,0.125f,1.0f,
0.0f,0.0f,0.140625f,1.0f,
0.0f,0.0f,0.171875f,1.0f,
0.0f,0.0f,0.1875f,1.0f,
0.0f,0.0f,0.21875f,1.0f,
0.0f,0.0f,0.25f,1.0f,
0.0f,0.0f,0.265625f,1.0f,
0.0f,0.0f,0.296875f,1.0f,
0.0f,0.0f,0.3125f,1.0f,
0.0f,0.0f,0.34375f,1.0f,
0.0f,0.0f,0.375f,1.0f,
0.0f,0.0f,0.390625f,1.0f,
0.0f,0.0f,0.421875f,1.0f,
0.0f,0.0f,0.453125f,1.0f,
0.0f,0.0f,0.46875f,1.0f,
0.0f,0.0f,0.5f,1.0f,
0.0f,0.0f,0.515625f,1.0f,
0.0f,0.0f,0.546875f,1.0f,
0.0f,0.0f,0.578125f,1.0f,
0.0f,0.0f,0.59375f,1.0f,
0.0f,0.0f,0.625f,1.0f,
0.0f,0.0f,0.640625f,1.0f,
0.0f,0.0f,0.671875f,1.0f,
0.0f,0.0f,0.703125f,1.0f,
0.0f,0.0f,0.71875f,1.0f,
0.0f,0.0f,0.75f,1.0f,
0.0f,0.0f,0.78125f,1.0f,
0.0f,0.015625f,0.78125f,1.0f,
0.0f,0.046875f,0.78125f,1.0f,
0.0f,0.0625f,0.796875f,1.0f,
0.0f,0.09375f,0.796875f,1.0f,
0.0f,0.109375f,0.8125f,1.0f,
0.0f,0.140625f,0.8125f,1.0f,
0.0f,0.15625f,0.8125f,1.0f,
0.0f,0.1875f,0.828125f,1.0f,
0.0f,0.21875f,0.828125f,1.0f,
0.0f,0.234375f,0.84375f,1.0f,
0.0f,0.265625f,0.84375f,1.0f,
0.0f,0.28125f,0.84375f,1.0f,
0.0f,0.3125f,0.859375f,1.0f,
0.0f,0.328125f,0.859375f,1.0f,
0.0f,0.359375f,0.875f,1.0f,
0.0f,0.390625f,0.875f,1.0f,
0.0f,0.40625f,0.875f,1.0f,
0.0f,0.4375f,0.890625f,1.0f,
0.0f,0.453125f,0.890625f,1.0f,
0.0f,0.484375f,0.90625f,1.0f,
0.0f,0.5f,0.90625f,1.0f,
0.0f,0.53125f,0.90625f,1.0f,
0.0f,0.546875f,0.921875f,1.0f,
0.0f,0.578125f,0.921875f,1.0f,
0.0f,0.609375f,0.9375f,1.0f,
0.0f,0.625f,0.9375f,1.0f,
0.0f,0.65625f,0.9375f,1.0f,
0.0f,0.671875f,0.953125f,1.0f,
0.0f,0.703125f,0.953125f,1.0f,
0.0f,0.71875f,0.96875f,1.0f,
0.0f,0.75f,0.96875f,1.0f,
0.0f,0.78125f,0.984375f,1.0f,
0.015625f,0.78125f,0.984375f,1.0f,
0.046875f,0.78125f,0.984375f,1.0f,
0.078125f,0.796875f,0.984375f,1.0f,
0.109375f,0.796875f,0.984375f,1.0f,
0.140625f,0.8125f,0.984375f,1.0f,
0.171875f,0.8125f,0.984375f,1.0f,
0.203125f,0.8125f,0.984375f,1.0f,
0.234375f,0.828125f,0.984375f,1.0f,
0.265625f,0.828125f,0.984375f,1.0f,
0.296875f,0.84375f,0.984375f,1.0f,
0.328125f,0.84375f,0.984375f,1.0f,
0.359375f,0.84375f,0.984375f,1.0f,
0.390625f,0.859375f,0.984375f,1.0f,
0.421875f,0.859375f,0.984375f,1.0f,
0.453125f,0.875f,0.984375f,1.0f,
0.484375f,0.875f,0.984375f,1.0f,
0.515625f,0.875f,0.984375f,1.0f,
0.546875f,0.890625f,0.984375f,1.0f,
0.578125f,0.890625f,0.984375f,1.0f,
0.609375f,0.90625f,0.984375f,1.0f,
0.640625f,0.90625f,0.984375f,1.0f,
0.671875f,0.90625f,0.984375f,1.0f,
0.703125f,0.921875f,0.984375f,1.0f,
0.734375f,0.921875f,0.984375f,1.0f,
0.765625f,0.9375f,0.984375f,1.0f,
0.796875f,0.9375f,0.984375f,1.0f,
0.828125f,0.9375f,0.984375f,1.0f,
0.859375f,0.953125f,0.984375f,1.0f,
0.890625f,0.953125f,0.984375f,1.0f,
0.921875f,0.96875f,0.984375f,1.0f,
0.953125f,0.96875f,0.984375f,1.0f,
0.984375f,0.984375f,0.984375f,1.0f,
0.96875f,0.984375f,0.984375f,1.0f,
0.953125f,0.984375f,0.984375f,1.0f,
0.9375f,0.984375f,0.984375f,1.0f,
0.90625f,0.984375f,0.984375f,1.0f,
0.890625f,0.984375f,0.984375f,1.0f,
0.875f,0.984375f,0.984375f,1.0f,
0.84375f,0.984375f,0.984375f,1.0f,
0.828125f,0.984375f,0.984375f,1.0f,
0.8125f,0.984375f,0.984375f,1.0f,
0.78125f,0.984375f,0.984375f,1.0f,
0.765625f,0.984375f,0.984375f,1.0f,
0.75f,0.984375f,0.984375f,1.0f,
0.71875f,0.984375f,0.984375f,1.0f,
0.703125f,0.984375f,0.984375f,1.0f,
0.6875f,0.984375f,0.984375f,1.0f,
0.65625f,0.984375f,0.984375f,1.0f,
0.640625f,0.984375f,0.984375f,1.0f,
0.625f,0.984375f,0.984375f,1.0f,
0.609375f,0.984375f,0.984375f,1.0f,
0.578125f,0.984375f,0.984375f,1.0f,
0.5625f,0.984375f,0.984375f,1.0f,
0.546875f,0.984375f,0.984375f,1.0f,
0.515625f,0.984375f,0.984375f,1.0f,
0.5f,0.984375f,0.984375f,1.0f,
0.484375f,0.984375f,0.984375f,1.0f,
0.453125f,0.984375f,0.984375f,1.0f,
0.4375f,0.984375f,0.984375f,1.0f,
0.421875f,0.984375f,0.984375f,1.0f,
0.390625f,0.984375f,0.984375f,1.0f,
0.375f,0.984375f,0.984375f,1.0f,
0.359375f,0.984375f,0.984375f,1.0f,
0.328125f,0.984375f,0.984375f,1.0f,
0.3125f,0.984375f,0.984375f,1.0f,
0.296875f,0.984375f,0.984375f,1.0f,
0.28125f,0.984375f,0.984375f,1.0f,
0.25f,0.984375f,0.984375f,1.0f,
0.234375f,0.984375f,0.984375f,1.0f,
0.21875f,0.984375f,0.984375f,1.0f,
0.1875f,0.984375f,0.984375f,1.0f,
0.171875f,0.984375f,0.984375f,1.0f,
0.15625f,0.984375f,0.984375f,1.0f,
0.125f,0.984375f,0.984375f,1.0f,
0.109375f,0.984375f,0.984375f,1.0f,
0.09375f,0.984375f,0.984375f,1.0f,
0.0625f,0.984375f,0.984375f,1.0f,
0.046875f,0.984375f,0.984375f,1.0f,
0.03125f,0.984375f,0.984375f,1.0f,
0.0f,0.984375f,0.984375f,1.0f,
0.0f,0.96875f,0.984375f,1.0f,
0.0f,0.953125f,0.984375f,1.0f,
0.0f,0.9375f,0.984375f,1.0f,
0.0f,0.90625f,0.984375f,1.0f,
0.0f,0.890625f,0.984375f,1.0f,
0.0f,0.875f,0.984375f,1.0f,
0.0f,0.84375f,0.984375f,1.0f,
0.0f,0.828125f,0.984375f,1.0f,
0.0f,0.8125f,0.984375f,1.0f,
0.0f,0.78125f,0.984375f,1.0f,
0.0f,0.765625f,0.984375f,1.0f,
0.0f,0.75f,0.984375f,1.0f,
0.0f,0.71875f,0.984375f,1.0f,
0.0f,0.703125f,0.984375f,1.0f,
0.0f,0.6875f,0.984375f,1.0f,
0.0f,0.65625f,0.984375f,1.0f,
0.0f,0.640625f,0.984375f,1.0f,
0.0f,0.625f,0.984375f,1.0f,
0.0f,0.609375f,0.984375f,1.0f,
0.0f,0.578125f,0.984375f,1.0f,
0.0f,0.5625f,0.984375f,1.0f,
0.0f,0.546875f,0.984375f,1.0f,
0.0f,0.515625f,0.984375f,1.0f,
0.0f,0.5f,0.984375f,1.0f,
0.0f,0.484375f,0.984375f,1.0f,
0.0f,0.453125f,0.984375f,1.0f,
0.0f,0.4375f,0.984375f,1.0f,
0.0f,0.421875f,0.984375f,1.0f,
0.0f,0.390625f,0.984375f,1.0f,
0.0f,0.375f,0.984375f,1.0f,
0.0f,0.359375f,0.984375f,1.0f,
0.0f,0.328125f,0.984375f,1.0f,
0.0f,0.3125f,0.984375f,1.0f,
0.0f,0.296875f,0.984375f,1.0f,
0.0f,0.28125f,0.984375f,1.0f,
0.0f,0.25f,0.984375f,1.0f,
0.0f,0.234375f,0.984375f,1.0f,
0.0f,0.21875f,0.984375f,1.0f,
0.0f,0.1875f,0.984375f,1.0f,
0.0f,0.171875f,0.984375f,1.0f,
0.0f,0.15625f,0.984375f,1.0f,
0.0f,0.125f,0.984375f,1.0f,
0.0f,0.109375f,0.984375f,1.0f,
0.0f,0.09375f,0.984375f,1.0f,
0.0f,0.0625f,0.984375f,1.0f,
0.0f,0.046875f,0.984375f,1.0f,
0.0f,0.03125f,0.984375f,1.0f,
0.0f,0.0f,0.984375f,1.0f,
0.0f,0.0f,0.96875f,1.0f,
0.0f,0.0f,0.953125f,1.0f,
0.0f,0.0f,0.9375f,1.0f,
0.0f,0.0f,0.921875f,1.0f,
0.0f,0.0f,0.90625f,1.0f,
0.0f,0.0f,0.890625f,1.0f,
0.0f,0.0f,0.875f,1.0f,
0.0f,0.0f,0.859375f,1.0f,
0.0f,0.0f,0.84375f,1.0f,
0.0f,0.0f,0.828125f,1.0f,
0.0f,0.0f,0.8125f,1.0f,
0.0f,0.0f,0.796875f,1.0f,
0.0f,0.0f,0.78125f,1.0f,
0.0f,0.0f,0.765625f,1.0f,
0.0f,0.0f,0.75f,1.0f,
0.0f,0.0f,0.734375f,1.0f,
0.0f,0.0f,0.71875f,1.0f,
0.0f,0.0f,0.703125f,1.0f,
0.0f,0.0f,0.6875f,1.0f,
0.0f,0.0f,0.671875f,1.0f,
0.0f,0.0f,0.65625f,1.0f,
0.0f,0.0f,0.640625f,1.0f,
0.0f,0.0f,0.625f,1.0f,
0.0f,0.0f,0.609375f,1.0f,
0.0f,0.0f,0.59375f,1.0f,
0.0f,0.0f,0.578125f,1.0f,
0.0f,0.0f,0.5625f,1.0f,
0.0f,0.0f,0.546875f,1.0f,
0.0f,0.0f,0.53125f,1.0f,
0.0f,0.0f,0.515625f,1.0f,
0.0f,0.0f,0.5f,1.0f,
0.0f,0.0f,0.484375f,1.0f,
0.0f,0.0f,0.46875f,1.0f,
0.0f,0.0f,0.453125f,1.0f,
0.0f,0.0f,0.4375f,1.0f,
0.0f,0.0f,0.421875f,1.0f,
0.0f,0.0f,0.40625f,1.0f,
0.0f,0.0f,0.390625f,1.0f,
0.0f,0.0f,0.375f,1.0f,
0.0f,0.0f,0.359375f,1.0f,
0.0f,0.0f,0.34375f,1.0f,
0.0f,0.0f,0.328125f,1.0f,
0.0f,0.0f,0.3125f,1.0f,
0.0f,0.0f,0.296875f,1.0f,
0.0f,0.0f,0.28125f,1.0f,
0.0f,0.0f,0.265625f,1.0f,
0.0f,0.0f,0.25f,1.0f,
0.0f,0.0f,0.234375f,1.0f,
0.0f,0.0f,0.21875f,1.0f,
0.0f,0.0f,0.203125f,1.0f,
0.0f,0.0f,0.1875f,1.0f,
0.0f,0.0f,0.171875f,1.0f,
0.0f,0.0f,0.15625f,1.0f,
0.0f,0.0f,0.140625f,1.0f,
0.0f,0.0f,0.125f,1.0f,
0.0f,0.0f,0.109375f,1.0f,
0.0f,0.0f,0.09375f,1.0f,
0.0f,0.0f,0.078125f,1.0f,
0.0f,0.0f,0.0625f,1.0f,
0.0f,0.0f,0.046875f,1.0f,
0.0f,0.0f,0.03125f,1.0f,
0.0f,0.0f,0.0f,1.0f,
0.0f,0.0f,0.0f,1.0f
};
/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2View

IMPLEMENT_DYNCREATE(CMyTerrain2View, CView)

BEGIN_MESSAGE_MAP(CMyTerrain2View, CView)
	//{{AFX_MSG_MAP(CMyTerrain2View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2View construction/destruction

CMyTerrain2View::CMyTerrain2View()
{
	// TODO: add construction code here

}

CMyTerrain2View::~CMyTerrain2View()
{
}

BOOL CMyTerrain2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
////////////////////////////////////////////////////////////////
//设置窗口类型
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
////////////////////////////////////////////////////////////////
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2View drawing

void CMyTerrain2View::OnDraw(CDC* pDC)
{
	CMyTerrain2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2View printing

BOOL CMyTerrain2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyTerrain2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyTerrain2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2View diagnostics

#ifdef _DEBUG
void CMyTerrain2View::AssertValid() const
{
	CView::AssertValid();
}

void CMyTerrain2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyTerrain2Doc* CMyTerrain2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyTerrain2Doc)));
	return (CMyTerrain2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2View message handlers

int CMyTerrain2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//////////////////////////////////////////////////////////////////
//初始化OpenGL和设置定时器
	m_pDC = new CClientDC(this);
	SetTimer(1, 20, NULL);
	InitializeOpenGL(m_pDC);
//////////////////////////////////////////////////////////////////
	InitGL();	
	return 0;
}

void CMyTerrain2View::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//删除调色板和渲染上下文、定时器
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
	    DeleteObject(m_hPalette);
	if ( m_pDC )
	{
		delete m_pDC;
	}
	KillTimer(1);		
/////////////////////////////////////////////////////////////////
	
}

void CMyTerrain2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();									
	gluPerspective(45.0f,(GLfloat)cx/(GLfloat)cy,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();									
	
}

void CMyTerrain2View::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//添加定时器响应函数和场景更新函数
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  设置逻辑调色板
//////////////////////////////////////////////////////////////////////
void CMyTerrain2View::SetLogicalPalette(void)
{
    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

	BYTE reds[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE greens[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE blues[] = {0, 85, 170, 255};

    for (int colorNum=0; colorNum<256; ++colorNum)
    {
        logicalPalette.aEntries[colorNum].peRed =
            reds[colorNum & 0x07];
        logicalPalette.aEntries[colorNum].peGreen =
            greens[(colorNum >> 0x03) & 0x07];
        logicalPalette.aEntries[colorNum].peBlue =
            blues[(colorNum >> 0x06) & 0x03];
        logicalPalette.aEntries[colorNum].peFlags = 0;
    }

    m_hPalette = CreatePalette ((LOGPALETTE*)&logicalPalette);
}


//////////////////////////////////////////////////////////
//						初始化openGL场景
//////////////////////////////////////////////////////////
BOOL CMyTerrain2View::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	//生成绘制描述表
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//置当前绘制描述表
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return TRUE;
}

//////////////////////////////////////////////////////////
//						设置像素格式
//////////////////////////////////////////////////////////
BOOL CMyTerrain2View::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	    1,                                // 版本号 
	    PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
	    PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
	    PFD_DOUBLEBUFFER,                 // 双缓存模式 
	    PFD_TYPE_RGBA,                    // RGBA 颜色模式 
	    24,                               // 24 位颜色深度 
	    0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
	    0,                                // 没有非透明度缓存 
	    0,                                // 忽略移位位 
	    0,                                // 无累加缓存 
	    0, 0, 0, 0,                       // 忽略累加位 
	    32,                               // 32 位深度缓存     
	    0,                                // 无模板缓存 
	    0,                                // 无辅助缓存 
	    PFD_MAIN_PLANE,                   // 主层 
	    0,                                // 保留 
	    0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);//选择像素格式
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);	//设置像素格式
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//设置逻辑调色板
	return TRUE;
}



//////////////////////////////////////////////////////////
//						场景绘制与渲染
//////////////////////////////////////////////////////////
BOOL CMyTerrain2View::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();									

	Io.x+=0.1;
	Io.z+=0.1;
	if(Io.x>MAXX)
	{
		Io.x=0;
		Io.z=0;
		InitTerreno();  //地形的动态生成
	}
	gluLookAt(Io.x,Io.y,Io.z,Io.x+4,3,Io.z+4,0.0f,1.0f,0.0f);

	Superficie(); //地形绘制

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyTerrain2View::Superficie(void)
{
	int x,z,xi,xf,zi,zf;
	float c1,c2,c3,c4;
	float xd,zd;
	float media;
	float tt;
	int ka,kb,kc,kd;

	xi=(int)Io.x-0;
	xf=(int)Io.x+30;
	zi=(int)Io.z-0;
	zf=(int)Io.z+30;
	
	for(x=xi;x<xf;x++)
	{
		for(z=zi;z<zf;z++)
		{
			if( (x > MAXX-1 || z > MAXZ-1) ||
			    (x < 0 || z < 0) )
				continue;
				
				xd=(float)x*SIZE;
				zd=(float)z*SIZE;

				c1=Buffer[x][z];
				c2=Buffer[x+1][z];
				c3=Buffer[x+1][z+1];
				c4=Buffer[x][z+1];

				tt=256/(max-min);
				// 根据高程求出颜色
				media=c1-min;
				media=media*tt;
				ka=255-(int)media;
				ka=ka*4;
				if(ka<0 || ka>256*4)
					ka=0;
				// 根据高程求出颜色
				media=c2-min;
				media=media*tt;
				kb=255-(int)media;
				kb=kb*4;
				if(kb<0 || kb>256*4)
					kb=0;
				// 根据高程求出颜色
				media=c3-min;
				media=media*tt;
				kc=255-(int)media;
				kc=kc*4;
				if(kc<0 || kc>256*4)
					kc=0;
				// 根据高程求出颜色
				media=c4-min;
				media=media*tt;
				kd=255-(int)media;
				kd=kd*4;
				if(kd<0 || kd>256*4)
					kd=0;
				//  地形由四边形构成
				glBegin(GL_QUADS);
					glColor3f(land[ka],land[ka+1],land[ka+2]);
					glVertex3d( xd, c1*FY, zd );
					glColor3f(land[kb],land[kb+1],land[kb+2]);
					glVertex3d( xd+SIZE, c2*FY, zd );
					glColor3f(land[kc],land[kc+1],land[kc+2]);
					glVertex3d( xd+SIZE, c3*FY, zd+SIZE );
					glColor3f(land[kd],land[kd+1],land[kd+2]);
					glVertex3d( xd, c4*FY, zd+SIZE );
				glEnd();
		}
	}
}

int CMyTerrain2View::InitGL(GLvoid)										
{
	GLfloat fgcolor[]={ 0.0f, 0.0f, 0.0f,1.0f };

	InitTerreno();		// 地形初始化
	// 视点与运动速度初始化
	Io.x=0;
	Io.y=5;
	Io.z=0;
	Io.angolo=0;
	Io.vx=0;
	Io.vy=0;
	Io.vz=0;
	//  OpenGL场景初始化（光照、雾化等〕
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glFogfv(GL_FOG_COLOR,fgcolor);
	glFogf(GL_FOG_START,25.0f);
	glFogf(GL_FOG_END,33.0f);
	glFogf(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_DENSITY, 0.5f);						// How Dense Will The Fog Be
	glEnable(GL_FOG);

	return TRUE;										// Initialization Went OK
}

void CMyTerrain2View::InitTerreno(void)
{
	int i,i2;
	int t,t2;

	max=0;
	min=1000;

	//  随机生成地形    
	for(i=0;i<MAXZ;i++)
	{
		for(i2=0;i2<MAXX;i2++)
			Buffer[i2][i]=0;
	}
    for (i = 1; i < MAXZ-1; i++)
    {     
      for (i2 = 1; i2 < MAXX-1; i2++)
      {
		  if(rand()%2==1)
			  //计算地形高程
			Buffer[i2][i]=(float)(rand()%1000-rand()%1000)/150;  				
      }
    }        
	//  地形平滑
    for (int cnt = 0; cnt < 4; cnt++)
    {  

      for (int t = 1; t < MAXZ-1; t++)
      {
        for (int t2 = 1; t2 < MAXX-1; t2++)
        {
			  Buffer[t][t2] = (Buffer[t+1][t2]+Buffer[t][t2-1]+Buffer[t-1][t2]+Buffer[t][t2+1])/4;

              if (rand()%20==1 && Buffer[t][t2] > 0 && cnt == 0) 
              {
                Buffer[t][t2]*=2;
                 
                Buffer[t-1][t2]=Buffer[t][t2]/2;
                Buffer[t+1][t2]=Buffer[t][t2]/2;
                Buffer[t][t2-1]=Buffer[t][t2]/2;
                Buffer[t][t2+1]=Buffer[t][t2]/2;
              } 

        }
      }

    }

	for(t=0;t<MAXZ;t++)
	{
		for(t2=0;t2<MAXX;t2++)
		{
			if(Buffer[t][t2]>max)
				max=(float)Buffer[t][t2];

			if(Buffer[t][t2]<min)
				min=(float)Buffer[t][t2];
		}
	}
}