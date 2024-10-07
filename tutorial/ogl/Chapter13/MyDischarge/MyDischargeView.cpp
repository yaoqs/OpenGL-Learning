// MyDischargeView.cpp : implementation of the CMyDischargeView class
//

#include "stdafx.h"
#include "MyDischarge.h"

#include "MyDischargeDoc.h"
#include "MyDischargeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDischargeView

IMPLEMENT_DYNCREATE(CMyDischargeView, CView)

BEGIN_MESSAGE_MAP(CMyDischargeView, CView)
	//{{AFX_MSG_MAP(CMyDischargeView)
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
// CMyDischargeView construction/destruction

CMyDischargeView::CMyDischargeView()
{
	// TODO: add construction code here

}

CMyDischargeView::~CMyDischargeView()
{
}

BOOL CMyDischargeView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyDischargeView drawing

void CMyDischargeView::OnDraw(CDC* pDC)
{
	CMyDischargeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyDischargeView printing

BOOL CMyDischargeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyDischargeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyDischargeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyDischargeView diagnostics

#ifdef _DEBUG
void CMyDischargeView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDischargeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDischargeDoc* CMyDischargeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDischargeDoc)));
	return (CMyDischargeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDischargeView message handlers

int CMyDischargeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	LoadTexture();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
	
	return 0;
}

void CMyDischargeView::OnDestroy() 
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

void CMyDischargeView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluOrtho2D(-13, 33, -20, 20);
	 glMatrixMode(GL_MODELVIEW);
}

void CMyDischargeView::OnTimer(UINT nIDEvent) 
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
void CMyDischargeView::SetLogicalPalette(void)
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
BOOL CMyDischargeView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyDischargeView::SetupPixelFormat()
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
BOOL CMyDischargeView::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	ModifyKnots();
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex2f(10.5, -40);
		glVertex2f(0.5, 0);
		glVertex2f(10.5, -40);
		glVertex2f(20.5, 0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		for (i=0; i<KNOTS-1; i++)
			Line((float)(i+1), ds[i]/2, (float)(i+2), ds[i+1]/2, 0.05);
	glEnd();
	glColor4f(0, 1, 1, 1);
	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(-2, -2);
		glTexCoord2f(1, 0); glVertex2f(2, -2);
		glTexCoord2f(1, 1); glVertex2f(2, 2);
		glTexCoord2f(0, 1); glVertex2f(-2, 2);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20.5, 0, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(-2, -2);
		glTexCoord2f(1, 0); glVertex2f(2, -2);
		glTexCoord2f(1, 1); glVertex2f(2, 2);
		glTexCoord2f(0, 1); glVertex2f(-2, 2);
	glEnd();
	glPopMatrix();
	glFlush();  

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyDischargeView::LoadTexture( )
{
  int texwid, texht;
  int texcomps;
  char fn[]="particle.rgb";
   teximage = m_Tex->read_texture(fn, &texwid, &texht, &texcomps);
  if (!teximage)
  {
    MessageBox("Sorry, can't read texture file...","Error",MB_OK);
    exit(0);
  }
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);  
} 


void CMyDischargeView::ModifyKnots()
{
  for (i=0; i<KNOTS; i++)
  {
    ds[i] = (float)(rand() % 100)/80;
  }
}

void CMyDischargeView::Line(float x1, float y1, float x2, float y2, float offset)
{
  float k;
  k = (y2-y1)/(x2-x1);
  while (1)  
  {
    glColor3f(0, 0, 0.3);
    glTexCoord2f(0, 0); glVertex2f(x1-0.4, y1-0.4);
    glTexCoord2f(1, 0); glVertex2f(x1+0.4, y1-0.4);
    glTexCoord2f(1, 1); glVertex2f(x1+0.4, y1+0.2);
    glTexCoord2f(0, 1); glVertex2f(x1-0.4, y1+0.2);

    glColor4f(0.5, 0.5, 0.9, 1);
    glTexCoord2f(0, 0); glVertex2f(x1-0.15, y1-0.15);
    glTexCoord2f(1, 0); glVertex2f(x1+0.15, y1-0.15);
    glTexCoord2f(1, 1); glVertex2f(x1+0.15, y1+0.15);
    glTexCoord2f(0, 1); glVertex2f(x1-0.15, y1+0.15);
    
    glColor4f(0, 0, 1, 0.3);
    glTexCoord2f(0, 0); glVertex2f(x1-0.4, y1-0.2);
    glTexCoord2f(1, 0); glVertex2f(x1+0.4, y1-0.2);
    glTexCoord2f(1, 1); glVertex2f(x1+0.4, y1+0.4);
    glTexCoord2f(0, 1); glVertex2f(x1-0.4, y1+0.4);

    x1 += offset;
    y1 += k*offset;
    if (x1 >= x2) return;
  }
}
