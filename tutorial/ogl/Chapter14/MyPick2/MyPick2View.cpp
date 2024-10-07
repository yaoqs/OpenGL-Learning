// MyPick2View.cpp : implementation of the CMyPick2View class
//

#include "stdafx.h"
#include "MyPick2.h"

#include "MyPick2Doc.h"
#include "MyPick2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BUFFER_LENGTH 64
#define EARTH	1
#define MARS	2
#define MOON1	3
#define MOON2	4

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View

IMPLEMENT_DYNCREATE(CMyPick2View, CView)

BEGIN_MESSAGE_MAP(CMyPick2View, CView)
	//{{AFX_MSG_MAP(CMyPick2View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View construction/destruction

CMyPick2View::CMyPick2View()
{
	// TODO: add construction code here

}

CMyPick2View::~CMyPick2View()
{
}

BOOL CMyPick2View::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyPick2View drawing

void CMyPick2View::OnDraw(CDC* pDC)
{
	CMyPick2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View printing

BOOL CMyPick2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyPick2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyPick2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View diagnostics

#ifdef _DEBUG
void CMyPick2View::AssertValid() const
{
	CView::AssertValid();
}

void CMyPick2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPick2Doc* CMyPick2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPick2Doc)));
	return (CMyPick2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View message handlers

int CMyPick2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyPick2View::OnDestroy() 
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

void CMyPick2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	fAspect = (GLfloat)cx/(GLfloat)cy;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, 1.0, 425.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void CMyPick2View::OnTimer(UINT nIDEvent) 
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
void CMyPick2View::SetLogicalPalette(void)
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
BOOL CMyPick2View::InitializeOpenGL(CDC* pDC)
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
BOOL CMyPick2View::SetupPixelFormat()
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
BOOL CMyPick2View::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -300.0f);	
	// 初始化名称堆栈
	glInitNames();
	glPushName(0);
	// 绘制Earth
	glPushMatrix();
	glRGB(0,0,255);
	glTranslatef(-100.0f,0.0f,0.0f);
	glLoadName(EARTH);
	auxSolidSphere(30.0f);
	// 绘制Moon
	glTranslatef(45.0f, 0.0f, 0.0f);
	glRGB(220,220,220);
	glPushName(MOON1);
	auxSolidSphere(5.0f);
	glPopName();
	glPopMatrix();

	// 绘制Mars

	glRGB(255,0,0);
	glPushMatrix();
	glTranslatef(100.0f, 0.0f, 0.0f);
	glLoadName(MARS);
	auxSolidSphere(20.0f);
	// 绘制Moon1
	glTranslatef(-40.0f, 40.0f, 0.0f);
	glRGB(220,220,220);
	glPushName(MOON1);
	auxSolidSphere(5.0f);
	glPopName();
	// 绘制Moon2
	glTranslatef(0.0f, -80.0f, 0.0f);
	glPushName(MOON2);
	auxSolidSphere(5.0f);
	glPopName();
	glPopMatrix();

	// 恢复矩阵状态
	glPopMatrix();	
	glFlush();


	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyPick2View::Init(GLvoid)
{
	// 光源值
	GLfloat  whiteLight[] = { 0.35f, 0.35f, 0.35f, 1.0f };
	GLfloat  sourceLight[] = { 0.65f, 0.65f, 0.65f, 1.0f };
	GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);		
	glEnable(GL_CULL_FACE);	
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.60f, 0.60f, 0.60f, 1.0f );

}

void CMyPick2View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int xPos = point.x;  // horizontal position of cursor 
	int yPos = point.y;  // vertical position of cursor 
	ProcessSelection(xPos, yPos);	
	CView::OnLButtonDown(nFlags, point);
}

void CMyPick2View::ProcessSelection(int xPos, int yPos)
{
	// 选择缓冲区
	GLuint selectBuff[BUFFER_LENGTH];
	// 单击与视口保存
	GLint hits, viewport[4];
	// 设置选择缓冲区
	glSelectBuffer(BUFFER_LENGTH, selectBuff);
	// 获得视口
	glGetIntegerv(GL_VIEWPORT, viewport);
	// 切换到投影，并保存矩阵
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	// 改变渲染模式
	glRenderMode(GL_SELECT);
	glLoadIdentity();
	gluPickMatrix(xPos, yPos, 2,2, viewport);
	gluPerspective(45.0f, fAspect, 1.0, 425.0);
	RenderScene();
	// 收集鼠标单击
	hits = glRenderMode(GL_RENDER);
	// 如果选择发生
	if(hits == 1)
		ProcessPlanet(selectBuff);
	// 保存投影矩阵
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void CMyPick2View::ProcessPlanet(GLuint *pSelectBuff)
{
	int id,count;
	char cMessage[64];
	// 名称堆栈中名称的数目
	count = pSelectBuff[0];
	// 名称堆栈的栈底
	id = pSelectBuff[3];
	// 选择发生
	switch(id)
		{
		case EARTH:
			strcpy(cMessage,"You clicked Earth.");
			if(count == 2)
				strcat(cMessage,"\nSpecifically the moon.");
			break;
		case MARS:
			strcpy(cMessage,"You clicked Mars.");
			if(count == 2)
				{
				if(pSelectBuff[4] == MOON1)
					strcat(cMessage,"\nSpecifically Moon #1.");
				else
					strcat(cMessage,"\nSpecifically Moon #2.");
				}
			break;
		default:
			strcpy(cMessage,"Error - Nothing was clicked on!");
			break;
		}
	MessageBox(cMessage,"Selection Message",MB_OK);
}


