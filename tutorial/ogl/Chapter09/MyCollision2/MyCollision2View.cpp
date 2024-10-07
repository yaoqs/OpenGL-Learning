// MyCollision2View.cpp : implementation of the CMyCollision2View class
//

#include "stdafx.h"
#include "MyCollision2.h"

#include "MyCollision2Doc.h"
#include "MyCollision2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2View

IMPLEMENT_DYNCREATE(CMyCollision2View, CView)

BEGIN_MESSAGE_MAP(CMyCollision2View, CView)
	//{{AFX_MSG_MAP(CMyCollision2View)
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
// CMyCollision2View construction/destruction

CMyCollision2View::CMyCollision2View()
{
	// TODO: add construction code here
	g_fSphere_radius = 0.5f;
	bDistanceCheck = false;
	q=NULL;
	g_vSpherePos = vec3(0,0,0);
	g_vVelocity = vec3(0,0,0.1f);
}

CMyCollision2View::~CMyCollision2View()
{
}

BOOL CMyCollision2View::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyCollision2View drawing

void CMyCollision2View::OnDraw(CDC* pDC)
{
	CMyCollision2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2View printing

BOOL CMyCollision2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyCollision2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyCollision2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2View diagnostics

#ifdef _DEBUG
void CMyCollision2View::AssertValid() const
{
	CView::AssertValid();
}

void CMyCollision2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCollision2Doc* CMyCollision2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCollision2Doc)));
	return (CMyCollision2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2View message handlers

int CMyCollision2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	Init();
	
	return 0;
}

void CMyCollision2View::OnDestroy() 
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

void CMyCollision2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)cx / cy,1,999);		
}

void CMyCollision2View::OnTimer(UINT nIDEvent) 
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
void CMyCollision2View::SetLogicalPalette(void)
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
BOOL CMyCollision2View::InitializeOpenGL(CDC* pDC)
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
BOOL CMyCollision2View::SetupPixelFormat()
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
BOOL CMyCollision2View::RenderScene() 
{
	int i=0;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	// 移动摄像机
	glTranslatef(-5.0f,0.0f,-25.0f);
	glRotatef(-45,0.0f,1.0f,0.0f);
	// 绘制两个四边形代表两个平面
	glBegin(GL_QUADS);
	for (;i<2;i++)
	{
		int v=0;	
		glColor3fv((const float*)&g_sQuads[i].sColor);
		for (v=0;v<4;v++)
			glVertex3f(
				g_sQuads[i].vVertices[v].x,
				g_sQuads[i].vVertices[v].y,
				g_sQuads[i].vVertices[v].z
			);
	}
	glEnd();
	// 绘制4条线	
	glBegin(GL_LINES);
	for (i=0;i<4;i++)
	{
		glColor3f(1,1,1);
		glVertex3f(
			g_sQuads[0].vVertices[i].x,
			g_sQuads[0].vVertices[i].y,
			g_sQuads[0].vVertices[i].z);

		glVertex3f(
			g_sQuads[1].vVertices[i].x,
			g_sQuads[1].vVertices[i].y,
			g_sQuads[1].vVertices[i].z);
	}
	// 绘制z轴线
	glVertex3f(0.0f,0.0f,-5.0f); glVertex3f(0.0f,0.0f,5.0f);
	glEnd();
	// 绘制球体
	glTranslatef(g_vSpherePos.x,g_vSpherePos.y,g_vSpherePos.z);
	gluSphere(q,g_fSphere_radius,32,32);
	//  进行碰撞检测
	CollisionCheck();
	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyCollision2View::Init(GLvoid)
{
	g_sQuads[0].vVertices[0] = vec3( -2.0 ,  2.0 , -5.0f);
	g_sQuads[0].vVertices[1] = vec3(  2.0 ,  2.0 , -5.0f);
	g_sQuads[0].vVertices[2] = vec3(  2.0 , -2.0 , -5.0f);
	g_sQuads[0].vVertices[3] = vec3( -2.0 , -2.0 , -5.0f);
	g_sQuads[0].vNormal = vec3(0,0,1);
	g_sQuads[0].D = g_sQuads[0].vVertices[0].DotProduct(g_sQuads[0].vNormal); // (*)
	g_sQuads[0].sColor.r = 1.0f;
	g_sQuads[0].sColor.g = 0.0f;
	g_sQuads[0].sColor.b = 0.0f;
	g_sQuads[1].vVertices[0] = vec3( -2.0 ,  2.0 ,  5.0f);
	g_sQuads[1].vVertices[1] = vec3(  2.0 ,  2.0 ,  5.0f);
	g_sQuads[1].vVertices[2] = vec3(  2.0 , -2.0 ,  5.0f);
	g_sQuads[1].vVertices[3] = vec3( -2.0 , -2.0 ,  5.0f);
	g_sQuads[1].vNormal = vec3(0,0,1);
	g_sQuads[1].D = g_sQuads[1].vVertices[1].DotProduct(g_sQuads[1].vNormal); // (*)
	g_sQuads[1].sColor.r = 0.0f;
	g_sQuads[1].sColor.g = 1.0f;
	g_sQuads[1].sColor.b = 0.0f;
		// 初始化opengl
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	q = gluNewQuadric();
	gluQuadricNormals(q, GLU_SMOOTH);

}

void CMyCollision2View::CollisionCheck(GLvoid)
{
	int i=0;
	bool collision=false;
	vec3 g_vSphereAfter = g_vSpherePos + g_vVelocity;
	// 在两个平面内进行碰撞检测
	for (;i<2;i++)
	{
		float D0;
		float D1;
		D0 = g_vSpherePos.DotProduct(g_sQuads[i].vNormal) - g_sQuads[i].D;   // before movement
		D1 = g_vSphereAfter.DotProduct(g_sQuads[i].vNormal) - g_sQuads[i].D; // after movement
		// 距离检测
		if (bDistanceCheck)
		{
			if (abs(D1) < g_fSphere_radius)
			{
				// 碰撞发生
				collision=true;
			}
		}		
		if ( (D0 > 0 && D1 < 0) || (D0 < 0 && D1 > 0) )
		{
			collision=true;			
		}
	}

	if (!collision)
	{
		// 移动球体
		g_vSpherePos = g_vSphereAfter;
	}
	else
	{
		// 速度反向
		g_vVelocity=-g_vVelocity;
	}	
}