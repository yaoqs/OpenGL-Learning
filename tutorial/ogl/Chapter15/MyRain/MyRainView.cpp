// MyRainView.cpp : implementation of the CMyRainView class
//

#include "stdafx.h"
#include "MyRain.h"

#include "MyRainDoc.h"
#include "MyRainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRainView

IMPLEMENT_DYNCREATE(CMyRainView, CView)

BEGIN_MESSAGE_MAP(CMyRainView, CView)
	//{{AFX_MSG_MAP(CMyRainView)
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
// CMyRainView construction/destruction

CMyRainView::CMyRainView()
{
	// TODO: add construction code here
	damp = 500.0f;
	cmap=0;
	nmap=1;
}

CMyRainView::~CMyRainView()
{
}

BOOL CMyRainView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyRainView drawing

void CMyRainView::OnDraw(CDC* pDC)
{
	CMyRainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyRainView printing

BOOL CMyRainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyRainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyRainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyRainView diagnostics

#ifdef _DEBUG
void CMyRainView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyRainDoc* CMyRainView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyRainDoc)));
	return (CMyRainDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyRainView message handlers

int CMyRainView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyRainView::OnDestroy() 
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

void CMyRainView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-7, 7, -5, 5, 10, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void CMyRainView::OnTimer(UINT nIDEvent) 
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
void CMyRainView::SetLogicalPalette(void)
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
BOOL CMyRainView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyRainView::SetupPixelFormat()
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
BOOL CMyRainView::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(250, 250, 250, 0, 0, 0, 0, 1, 0);
	glColor3f(1, 1, 1);
	
	DrawModel();

	if ((rand() % 2) == 0) 
	{
		wavemap[nmap][(rand() % (MAPY-2))+1][(rand() % (MAPX-2))+1] = 50;
		wavemap[cmap][(rand() % (MAPY-2))+1][(rand() % (MAPX-2))+1] = 50;
	}

	ProcessWave();
	glTranslatef(-128, 0, -128);
	DrawWave();
	InvertWaveMap();
	glLoadIdentity();


	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyRainView::Init(GLvoid)
{
	srand((unsigned int)time(NULL));
	glClearColor(0, 0, 0, 1);
	glGenTextures(2, texture);
	LoadTexture("wall.rgb", 0);
	LoadTexture("wood.rgb", 1);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	for (int i=0; i<MAPY; i++)
		for (int j=0; j<MAPX; j++)
			for (int k=0; k<2; k++)
				wavemap[k][i][j] = 0;
}

void CMyRainView::DrawModel()
{
	glDisable(GL_BLEND);
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);	
		glTexCoord2f(0, 0); glVertex3f(128, 0, 256);
		glTexCoord2f(2, 0); glVertex3f(256, 0, 256);
		glTexCoord2f(2, 6); glVertex3f(256, 0, -256);
		glTexCoord2f(0, 6); glVertex3f(128, 0, -256);

		glTexCoord2f(0, 0); glVertex3f(-256, 0, 256);
		glTexCoord2f(2, 0); glVertex3f(-128, 0, 256);
		glTexCoord2f(2, 6); glVertex3f(-128, 0, -256);
		glTexCoord2f(0, 6); glVertex3f(-256, 0, -256);

		glTexCoord2f(0, 0); glVertex3f(-128, 0, 128);
		glTexCoord2f(0, 4); glVertex3f(-128, 0, 256);
		glTexCoord2f(4, 4); glVertex3f(128, 0, 256);
		glTexCoord2f(4, 0); glVertex3f(128, 0, 128);

		glTexCoord2f(0, 0); glVertex3f(-128, 0, -256);
		glTexCoord2f(0, 4); glVertex3f(-128, 0, -128);
		glTexCoord2f(4, 4); glVertex3f(128, 0, -128);
		glTexCoord2f(4, 0); glVertex3f(128, 0, -256);
	glEnd();	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);	
		glTexCoord2f(0, 0); glVertex3f(-128, -64, -128);
		glTexCoord2f(4, 0); glVertex3f(-128, -64, 128);
		glTexCoord2f(4, 4); glVertex3f(128, -64, 128);
		glTexCoord2f(0, 4); glVertex3f(128, -64, -128);

		glTexCoord2f(0, 0); glVertex3f(128, -64, -128);
		glTexCoord2f(3, 0); glVertex3f(128, -64, 128);
		glTexCoord2f(3, 2); glVertex3f(128, 0, 128);
		glTexCoord2f(0, 2); glVertex3f(128, 0, -128);

		glTexCoord2f(0, 0); glVertex3f(-128, -64, 128);
		glTexCoord2f(4, 0); glVertex3f(-128, -64, -128);
		glTexCoord2f(4, 2); glVertex3f(-128, 0, -128);
		glTexCoord2f(0, 2); glVertex3f(-128, 0, 128);

		glTexCoord2f(0, 0); glVertex3f(-128, -64, -128);
		glTexCoord2f(4, 0); glVertex3f(128, -64, -128);
		glTexCoord2f(4, 2); glVertex3f(128, 0, -128);
		glTexCoord2f(0, 2); glVertex3f(-128, 0, -128);

		glTexCoord2f(0, 0); glVertex3f(128, -64, 128);
		glTexCoord2f(4, 0); glVertex3f(-128, -64, 128);
		glTexCoord2f(4, 2); glVertex3f(-128, 0, 128);
		glTexCoord2f(0, 2); glVertex3f(128, 0, 128);
	glEnd();
	glEnable(GL_BLEND);
}


void CMyRainView::LoadTexture(char *fn, int t_num)
{
	int texwid, texht;
	int texcomps;
 	teximage = m_Texture.read_texture(fn, &texwid, &texht, &texcomps);
	if (!teximage)
	{
		MessageBox("Sorry, can't read texture file...","ERROR",MB_OK);
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, texture[t_num]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	free(teximage);
} 

void CMyRainView::ProcessWave()
{
	float temp;
	for (int i=1; i<MAPY-1; i++)
		for (int j=1; j<MAPX-1; j++)
		{
			temp = ((wavemap[cmap][i-1][j] + 
					wavemap[cmap][i+1][j] + 
				    wavemap[cmap][i][j-1] + 
				    wavemap[cmap][i][j+1] +
					wavemap[cmap][i-1][j+1] + 
					wavemap[cmap][i+1][j+1] + 
					wavemap[cmap][i-1][j-1] + 
					wavemap[cmap][i+1][j-1]) / 4) -
				    wavemap[nmap][i][j];			
			temp = temp - (temp / damp);
			if (temp < 0.01) temp = 0;
			wavemap[nmap][i][j] = temp;
		}
}

void CMyRainView::InvertWaveMap()
{
	int temp = cmap;
	cmap = nmap;
	nmap = temp;
}

void CMyRainView::DrawWave()
{
	int i, j;
	glDisable(GL_TEXTURE_2D);	
	glColor4f(1, 1, 1, 0.1);
	glBegin(GL_TRIANGLES);
	for (i=0; i<MAPY-1; i++)
	{
		for (j=0; j<MAPX-1; j++)
		{
			glVertex3f(j*2, wavemap[cmap][i][j], i*2);
			glVertex3f((j+1)*2, wavemap[cmap][i+1][j+1], (i+1)*2);
			glVertex3f(j*2, wavemap[cmap][i+1][j], (i+1)*2);

			glVertex3f(j*2, wavemap[cmap][i][j], i*2);
			glVertex3f((j+1)*2, wavemap[cmap][i][j+1], i*2);
			glVertex3f((j+1)*2, wavemap[cmap][i+1][j+1], (i+1)*2);
		}
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);	
}