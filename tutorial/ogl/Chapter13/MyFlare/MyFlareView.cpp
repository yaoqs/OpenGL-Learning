// MyFlareView.cpp : implementation of the CMyFlareView class
//

#include "stdafx.h"
#include "MyFlare.h"

#include "MyFlareDoc.h"
#include "MyFlareView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFlareView

IMPLEMENT_DYNCREATE(CMyFlareView, CView)

BEGIN_MESSAGE_MAP(CMyFlareView, CView)
	//{{AFX_MSG_MAP(CMyFlareView)
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
// CMyFlareView construction/destruction

CMyFlareView::CMyFlareView()
{
	// TODO: add construction code here
	num_flares = 0;
	tic = 0.0;
	shine_tic = 0;
	from[0] = 0.0;
	from[1]= 0.0;
	from[2]= 20.0;
	at[0] = 0.0;
	at[1]= 0.0;
	at[2]= 0.0;
	near_clip = 1.0;
	useMipmaps = 0, verbose = 0;
}

CMyFlareView::~CMyFlareView()
{
}

BOOL CMyFlareView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyFlareView drawing

void CMyFlareView::OnDraw(CDC* pDC)
{
	CMyFlareDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyFlareView printing

BOOL CMyFlareView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFlareView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFlareView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFlareView diagnostics

#ifdef _DEBUG
void CMyFlareView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFlareView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFlareDoc* CMyFlareView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFlareDoc)));
	return (CMyFlareDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFlareView message handlers

int CMyFlareView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyFlareView::OnDestroy() 
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

void CMyFlareView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	
}

void CMyFlareView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//添加定时器响应函数和场景更新函数
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	tic += 0.08f;	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  设置逻辑调色板
//////////////////////////////////////////////////////////////////////
void CMyFlareView::SetLogicalPalette(void)
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
BOOL CMyFlareView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyFlareView::SetupPixelFormat()
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
BOOL CMyFlareView::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	position[0] = sin(tic * 0.73) * 6;
	position[1] = 4.0 + 8.0 * sin(tic * 0.678);
    position[2] = sin(tic * 0.895) * 6;
    DoBackground();
    DoFlares(from, at, position, near_clip);

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyFlareView::Init(GLvoid) 
{
	  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
      init_flares();	// 初始化霓虹
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60.0, 1.0,  0.5, 30.0);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(from[0], from[1], from[2], at[0], at[1], at[2],
        0.0, 1.0, 0.);      
      load_textures();	// 转入纹理
      glEnable(GL_TEXTURE_2D);

}


void CMyFlareView::DoFlares(GLfloat from[3], GLfloat at[3], GLfloat light[3], GLfloat near_clip)
{
	GLfloat view_dir[3], tmp[3], light_dir[3], position[3], dx[3], dy[3],
		center[3], axis[3], sx[3], sy[3], dot, global_scale = 1.5;
	GLuint bound_to = 0;
	int i;

	m_MyVec.vdiff(view_dir, at, from);
	m_MyVec.vnorm(view_dir);

	m_MyVec.vscale(tmp, view_dir, near_clip);
	m_MyVec.vadd(center, from, tmp);

	m_MyVec.vdiff(light_dir, light, from);
	m_MyVec.vnorm(light_dir);

	dot = m_MyVec.vdot(light_dir, view_dir);
	m_MyVec.vscale(tmp, light_dir, near_clip / dot);
	m_MyVec.vadd(light, from, light_dir);

	m_MyVec.vdiff(axis, light, center);
	m_MyVec.vcopy(dx, axis);

	m_MyVec.vnorm(dx);
	m_MyVec.vcross(dy, dx, view_dir);
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DITHER);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	for (i = 0; i < num_flares; i++) 
	{
		m_MyVec.vscale(sx, dx, flare[i].scale * global_scale);
		m_MyVec.vscale(sy, dy, flare[i].scale * global_scale);
		glColor3fv(flare[i].color);

		if (flare[i].type < 0)
		{
			if (bound_to)
				glEnd();
			glBindTexture(GL_TEXTURE_2D, shineTex[shine_tic]);
			bound_to = shineTex[shine_tic];
			shine_tic = (shine_tic + 1) % 10;
			glBegin(GL_QUADS);
		} else 
		{
			if (bound_to != flareTex[flare[i].type]) 
			{
				glEnd();
				glBindTexture(GL_TEXTURE_2D, flareTex[flare[i].type]);
				bound_to = flareTex[flare[i].type];
				glBegin(GL_QUADS);
			}
		}
		m_MyVec.vscale(tmp, axis, flare[i].loc);
		m_MyVec.vadd(position, center, tmp);
		
		glTexCoord2f(0.0, 0.0);
		m_MyVec.vadd(tmp, position, sx);
		m_MyVec.vadd(tmp, tmp, sy);
		glVertex3fv(tmp);

		glTexCoord2f(1.0, 0.0);
		m_MyVec.vdiff(tmp, position, sx);
		m_MyVec.vadd(tmp, tmp, sy);
		glVertex3fv(tmp);

		glTexCoord2f(1.0, 1.0);
		m_MyVec.vdiff(tmp, position, sx);
		m_MyVec.vdiff(tmp, tmp, sy);
		glVertex3fv(tmp);

		glTexCoord2f(0.0, 1.0);
		m_MyVec.vadd(tmp, position, sx);
		m_MyVec.vdiff(tmp, tmp, sy);
		glVertex3fv(tmp);
	}
	glEnd();
}

void CMyFlareView::DoBackground(void)
{
  glEnable(GL_DITHER);
  glDisable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D, logoTex);

  glBegin(GL_QUADS);
  glColor3f(0.0, 0.0, 1.0);
  glTexCoord2f(0.075, 0.1);
  glVertex3f(-11.0, -7.0, 0.0);

  glColor3f(0.8, 0.8, 1.0);
  glTexCoord2f(1.0, 0.1);
  glVertex3f(11.0, -7.0, 0.0);

  glColor3f(0.0, 0.0, 1.0);
  glTexCoord2f(1.0, 0.9);
  glVertex3f(11.0, 7.0, 0.0);

  glColor3f(0.0, 0.5, 1.0);
  glTexCoord2f(0.075, 0.9);
  glVertex3f(-11.0, 7.0, 0.0);
  glEnd();
}

void CMyFlareView::init_flares(void)
{
	GLfloat red[3] = {1.0, 0.0, 0.0};
	GLfloat green[3] = {0.0, 1.0, 0.0};
	GLfloat blue[3] = {0.0, 0.0, 1.0};
  flare[0] = set_flare(-1, 1.0, 0.3, blue, 1.0);
  flare[1] = set_flare(-1, 1.0, 0.2, green, 1.0);
  flare[2] = set_flare(-1, 1.0, 0.25, red, 1.0);
  flare[3] = set_flare(1, 0.5, 0.2f, red, 0.3);
  flare[4] = set_flare(2, 1.3, 0.04f, red, 0.6);
  flare[5] = set_flare(3, 1.0, 0.1f, red, 0.4);
  flare[6] = set_flare(3, 0.2, 0.05f, red, 0.3);
  flare[7] = set_flare(0, 0.0, 0.04f, red, 0.3);
  flare[8] = set_flare(5, -0.25, 0.07f, red, 0.5);
  flare[9] = set_flare(5, -0.4, 0.02f, red, 0.6);
  flare[10] = set_flare(5, -0.6, 0.04f, red, 0.4);
  flare[11] = set_flare(5, -1.0, 0.03f, red, 0.2);
  num_flares = 12;
}

void CMyFlareView::load_textures(void)
{
  char filename[256];
  GLenum minFilter, maxFilter;
  int id = 1, i;

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  if (useMipmaps) {
    minFilter = GL_LINEAR_MIPMAP_LINEAR;
    maxFilter = GL_LINEAR;
  } else {
    minFilter = GL_LINEAR;
    maxFilter = GL_LINEAR;
  }
  logoTex = id;
  setup_texture("OpenGL.bw", logoTex, minFilter, maxFilter);
  id++;

  if (!useMipmaps) {
    minFilter = GL_NEAREST;
    maxFilter = GL_NEAREST;
  }
  for (i = 0; i < 10; i++) {
    shineTex[i] = id;
    sprintf(filename, "Shine%d.bw", i);
    setup_texture(filename, shineTex[i], minFilter, maxFilter);
    id++;
  }
  for (i = 0; i < 6; i++) {
    flareTex[i] = id;
    sprintf(filename, "Flare%d.bw", i + 1);
    setup_texture(filename, flareTex[i], minFilter, maxFilter);
    id++;
  }
}

Flare CMyFlareView::set_flare(int type, float location, float scale, GLfloat color[3], float colorScale)
{
  Flare ret;

  ret.type = type;
  ret.loc = location;
  ret.scale = scale;
  ret.color[0] = color[0] * colorScale;
  ret.color[1] = color[1] * colorScale;
  ret.color[2] = color[2] * colorScale;
  return ret;
}

void CMyFlareView::setup_texture(char *filename, GLuint texobj,
  GLenum minFilter, GLenum maxFilter)
{
  unsigned char *buf;
  int width, height, components;

  glBindTexture(GL_TEXTURE_2D, texobj);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
  buf = m_LoadLUM.load_luminance(filename, &width, &height, &components);
  if (useMipmaps)
    gluBuild2DMipmaps(GL_TEXTURE_2D, 1, width, height,
      GL_LUMINANCE, GL_UNSIGNED_BYTE, buf);
  else
    glTexImage2D(GL_TEXTURE_2D, 0, 1, width, height, 0,
      GL_LUMINANCE, GL_UNSIGNED_BYTE, buf);
  free(buf);
}
