// MyCloudView.cpp : implementation of the CMyCloudView class
//

#include "stdafx.h"
#include "MyCloud.h"

#include "MyCloudDoc.h"
#include "MyCloudView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
/////////////////////////////////////////////////////////////////////////////
// CMyCloudView

IMPLEMENT_DYNCREATE(CMyCloudView, CView)

BEGIN_MESSAGE_MAP(CMyCloudView, CView)
	//{{AFX_MSG_MAP(CMyCloudView)
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
// CMyCloudView construction/destruction

CMyCloudView::CMyCloudView()
{
	// TODO: add construction code here
	ttrans[0]=0.01f;
	ttrans[1]=0.01f;
	Cloudcolor_R=1.0f;
	Cloudcolor_G=1.0f; 
	Cloudcolor_B=1.0f;
	Backcolor_R=0.19f;
	Backcolor_G=0.25f; 
	Backcolor_B=0.70f;
	m_Speed=50;
	m_Fogdensity=50;
}

CMyCloudView::~CMyCloudView()
{
}

BOOL CMyCloudView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyCloudView drawing

void CMyCloudView::OnDraw(CDC* pDC)
{
	CMyCloudDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyCloudView printing

BOOL CMyCloudView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyCloudView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyCloudView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyCloudView diagnostics

#ifdef _DEBUG
void CMyCloudView::AssertValid() const
{
	CView::AssertValid();
}

void CMyCloudView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCloudDoc* CMyCloudView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCloudDoc)));
	return (CMyCloudDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCloudView message handlers

int CMyCloudView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	InitializeTexture();	
	return 0;
}

void CMyCloudView::OnDestroy() 
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

void CMyCloudView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	
}

void CMyCloudView::OnTimer(UINT nIDEvent) 
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
void CMyCloudView::SetLogicalPalette(void)
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
BOOL CMyCloudView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyCloudView::SetupPixelFormat()
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
BOOL CMyCloudView::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glScalef(10,1,10);
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glTranslatef(ttrans[0], ttrans[1], 0.);
	// 绘制云彩
    glBegin(GL_QUADS);
	glColor3f(Backcolor_R,Backcolor_G,Backcolor_B);
    glTexCoord2f(0.f, 0.f); glVertex3f(-1.f, 1.f, -1.f);
    glTexCoord2f(0.f, 5.f); glVertex3f(-1.f, 1.f,  1.f);
    glTexCoord2f(5.f, 5.f); glVertex3f( 1.f, 1.f,  1.f);
    glTexCoord2f(5.f, 0.f); glVertex3f( 1.f, 1.f, -1.f);
    glEnd();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
	// 云彩的流动效果
	ttrans[0] =ttrans[0]+0.01f*m_Speed/50.0f;
    if (ttrans[0] == 1.0f) ttrans[0] = 0.f;
    ttrans[1] =ttrans[1]+0.005f*m_Speed/50.0f;;
    if (ttrans[1] == 1.0f) ttrans[1] = 0.f;	

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyCloudView::InitializeTexture()
{
	//设置云彩的颜色
    GLfloat cloud_color[4] = { Cloudcolor_R, Cloudcolor_G, Cloudcolor_B, 0.f, };
    GLfloat fog_density , density, far_cull;
	//设置雾化效果
	fog_density=m_Fogdensity/1000.0f;
    unsigned *image;
    int width, height, components;
	char* filename;
	filename="clouds.bw";
    if (filename) 
	{
		image = m_Tex->read_texture(filename, &width, &height, &components);
		if (image == NULL) 
		{
			AfxMessageBox("不能装入图形文件！");
			exit(EXIT_FAILURE);
		}
		if (components != 1) 
			{
			AfxMessageBox("图形文件必须是bw文件！");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int i, j;
		unsigned char *img;
		components = 4; width = height = 512;
		image = (unsigned *) malloc(width*height*sizeof(unsigned));
		img = (unsigned char *)image;
		for (j = 0; j < height; j++)
	    for (i = 0; i < width; i++) 
		{
			int w2 = width/2, h2 = height/2;
			if (i & 32)
				img[4*(i+j*width)+0] = 0xff;
			else
				img[4*(i+j*width)+1] = 0xff;
			if (j&32)
				img[4*(i+j*width)+2] = 0xff;
			if ((i-w2)*(i-w2) + (j-h2)*(j-h2) > 64*64 &&
				(i-w2)*(i-w2) + (j-h2)*(j-h2) < 300*300) img[4*(i+j*width)+3] = 0xff;
	    }
	}
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, cloud_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, components, width,
                 height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 image);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.,1.,.1,far_cull = 10.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.,0.,-5.5);
	//设置雾化方程
    density = 1.- expf(-5.5 * fog_density * fog_density *
			      far_cull * far_cull);

    density = MAX(MIN(density, 1.), 0.);
	//计算雾的颜色
    fog_color[0] = .23 + density *.57;
    fog_color[1] = .35 + density *.45;
    fog_color[2] = .78 + density *.22;

    glClearColor(fog_color[0], fog_color[1], fog_color[2], 1.f);

    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, fog_density);
    glFogfv(GL_FOG_COLOR, fog_color);
    if (fog_density > 0)
	glEnable(GL_FOG);

}
