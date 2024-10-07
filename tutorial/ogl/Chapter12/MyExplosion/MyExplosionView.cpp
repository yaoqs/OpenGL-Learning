// MyExplosionView.cpp : implementation of the CMyExplosionView class
//

#include "stdafx.h"
#include "MyExplosion.h"

#include "MyExplosionDoc.h"
#include "MyExplosionView.h"

#include <math.h>
const float pi = 3.1415926;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionView

IMPLEMENT_DYNCREATE(CMyExplosionView, CView)

BEGIN_MESSAGE_MAP(CMyExplosionView, CView)
	//{{AFX_MSG_MAP(CMyExplosionView)
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
// CMyExplosionView construction/destruction

CMyExplosionView::CMyExplosionView()
{
	// TODO: add construction code here
	sc=0;
	stop=0;
	alpha=0;
	coef=30;
	counter=100;
	flag_exp=0;
	flag_exp1=0;
	exp_coef=0;
	exp_color = 1;
}

CMyExplosionView::~CMyExplosionView()
{
}

BOOL CMyExplosionView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyExplosionView drawing

void CMyExplosionView::OnDraw(CDC* pDC)
{
	CMyExplosionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionView printing

BOOL CMyExplosionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyExplosionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyExplosionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionView diagnostics

#ifdef _DEBUG
void CMyExplosionView::AssertValid() const
{
	CView::AssertValid();
}

void CMyExplosionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyExplosionDoc* CMyExplosionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyExplosionDoc)));
	return (CMyExplosionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionView message handlers

int CMyExplosionView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	LoadTexture(0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	textures.Init();
	ship.LoadFromFile("data/ship.obj", &textures);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);	

	return 0;
}

void CMyExplosionView::OnDestroy() 
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

void CMyExplosionView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 3, 250);
	glMatrixMode(GL_MODELVIEW);	
}

void CMyExplosionView::OnTimer(UINT nIDEvent) 
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
void CMyExplosionView::SetLogicalPalette(void)
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
BOOL CMyExplosionView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyExplosionView::SetupPixelFormat()
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
BOOL CMyExplosionView::RenderScene() 
{
	float cx, cy, cz;
	float px, py, pz;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLoadIdentity();
	glTranslatef(0, 0, -100);
	glColor3f(1, 1, 1);
	glRotatef(alpha, 0, 1, 0);
	glRotatef(-120, 1, 0, 0);
	alpha += 2;
	glDisable(GL_BLEND);
	counter--;
	if (counter < 0) counter = 0;
	if ((counter == 0) && (!flag_exp))
	{
		ship.Explosion();
		flag_exp = 1;
	}
	if (flag_exp1)
	{	
		ship.Explosion_Step(coef);
		coef -= coef/30;
	}
	if (coef < 0) coef = 0;
	ship.Draw();
	glEnable(GL_BLEND);
	// 绘制爆炸后的多边形
	// cx, cy, cz - 摄像机方向矢量
	// px, py, pz - 多边形方向矢量
	if (flag_exp)
	{
		cx = 0;
		cy = 0;
		cz = 1;
		px = cx;
		py = cy;
		pz = -cz;
		float d = sqrt(px*px + py*py + pz*pz);
		px /= d;
		py /= d;
		pz /= d;
		float phi, theta;
		theta = asin(pz);
		phi = asin(py/cos(theta));
		theta = (theta*180)/pi;
		phi = (phi*180)/pi;
		glLoadIdentity();
		glTranslatef(0, 0, -180);
		glRotatef(phi, 1, 0, 0);
		glRotatef(theta, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glScalef(exp_coef, exp_coef, exp_coef);
		exp_coef += exp_coef/20 + 0.1;
		if (exp_coef > 0.5) flag_exp1 = 1;
		glColor4f(1, 1, 1, exp_color);
		if (flag_exp1) exp_color -= 0.05;
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex3f(0, -100, -100);
			glTexCoord2f(0, 0); glVertex3f(0, 100, -100);
			glTexCoord2f(1, 0); glVertex3f(0, 100, 100);
			glTexCoord2f(1, 1); glVertex3f(0, -100, 100);
		glEnd();
	}
	glFlush();  

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyExplosionView::LoadTexture(int t_num)
{
	int texwid, texht;
	int texcomps;
    char fn[]="data/vzr.rgb";
	teximage = m_Tex->read_texture(fn, &texwid, &texht, &texcomps);
	if (!teximage)
	{
		MessageBox("Sorry, can't read texture file...","Error",MB_OK);
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, texture[t_num]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texwid, texht, GL_RGBA, GL_UNSIGNED_BYTE, teximage);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	free(teximage);
} 

