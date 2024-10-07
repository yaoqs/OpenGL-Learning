// MySmokeView.cpp : implementation of the CMySmokeView class
//

#include "stdafx.h"
#include "MySmoke.h"

#include "MySmokeDoc.h"
#include "MySmokeView.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define sinf(x) ((float)sin((x)))
#define cosf(x) ((float)cos((x)))
#define atan2f(x, y) ((float)atan2((x), (y)))
#define M_PI 3.14159265

#define MAX_TIME	(2*196.0)
#define MAX_SMOKE	320
#define RAD(x) (((x)*M_PI)/180.)
#define sgn(a) ((a) >= 0 ? 1.0 : -1.0)


static float rot = 0.f;
static float opacity = 1.0f;
static float intensity = 1.0f;
static float size = .2f, delta = 0.f;
static float scale = 1.;

/////////////////////////////////////////////////////////////////////////////
// CMySmokeView

IMPLEMENT_DYNCREATE(CMySmokeView, CView)

BEGIN_MESSAGE_MAP(CMySmokeView, CView)
	//{{AFX_MSG_MAP(CMySmokeView)
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
// CMySmokeView construction/destruction

CMySmokeView::CMySmokeView()
{
	// TODO: add construction code here

}

CMySmokeView::~CMySmokeView()
{
}

BOOL CMySmokeView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMySmokeView drawing

void CMySmokeView::OnDraw(CDC* pDC)
{
	CMySmokeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMySmokeView printing

BOOL CMySmokeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMySmokeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMySmokeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMySmokeView diagnostics

#ifdef _DEBUG
void CMySmokeView::AssertValid() const
{
	CView::AssertValid();
}

void CMySmokeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMySmokeDoc* CMySmokeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySmokeDoc)));
	return (CMySmokeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySmokeView message handlers

int CMySmokeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMySmokeView::OnDestroy() 
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

void CMySmokeView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	
}

void CMySmokeView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//添加定时器响应函数和场景更新函数
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	static int time = 0;
    int i;
     //更新爆炸纹理
    size += .07f;
    delta += .04f;
    rot += .4f;
    opacity -= .003f;

    for (i = 0; i < 30; i++) 
	{
	corners[i][0] += 0.7 * traj[i / 3][0];
	corners[i][1] += 0.7 * traj[i / 3][1];
	corners[i][2] += 0.7 * traj[i / 3][2];
    }

    for (i = 0; i < 10; i++)
	traj[i][1] -= 0.025f;
	time++;	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  设置逻辑调色板
//////////////////////////////////////////////////////////////////////
void CMySmokeView::SetLogicalPalette(void)
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
BOOL CMySmokeView::InitializeOpenGL(CDC* pDC)
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
BOOL CMySmokeView::SetupPixelFormat()
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
BOOL CMySmokeView::RenderScene() 
{
	float normals[10][3] = {
    {0.0, 0.0, -1.0},
    {0.0, 0.0, -1.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {-1.0, 0.0, 0.0},
    {-1.0, 0.0, 0.0}};
	float axes[10][3] = {
    {-1.0, 1.0, 0.0},
    {1.0, -1.0, 0.0},
    {-1.0, 1.0, 0.0},
    {1.0, -1.0, 0.0},
    {1.0, 0.0, -1.0},
    {-1.0, 0.0, 1.0},
    {0.0, 1.0, -1.0},
    {0.0, -1.0, 1.0},
    {0.0, 1.0, -1.0},
    {0.0, -1.0, 1.0}};
	float omega[10] = {20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0};
	static int time = 0;
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(-sinf(RAD(0)) * 5.5, 0, cosf(RAD(0)) * 5.5, 0., 0., 0., 0., 1., 0.);
    glColor4f(0.f, .2f, 0.f, 1.f);
    glBegin(GL_POLYGON);
		glVertex3f(-4.0, -1.0, -4.0);
        glVertex3f(4.0, -1.0, -4.0);
	    glVertex3f(4.0, -1.0, 4.0);
	    glVertex3f(-4.0, -1.0, 4.0);
    glEnd();

    glEnable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(.3f, .3f, .3f);
    glPushMatrix();
    glTranslatef(-1.f, -1.f + .2f, -1.5f);
    glScalef(.2f, .2f, .2f);

    for (i = 0; i < 10; i++) {
	float ax = (corners[3 * i][0] + corners[3 * i + 1][0] + corners[3 * i + 2][0]) / 3,
	      ay = (corners[3 * i][1] + corners[3 * i + 1][1] + corners[3 * i + 2][1]) / 3,
	      az = (corners[3 * i][2] + corners[3 * i + 1][2] + corners[3 * i + 2][2]) / 3;

	glPushMatrix();
	glTranslatef(ax, ay, az);
	glRotatef(omega[i] * delta, axes[i][0], axes[i][1], axes[i][2]);
	glTranslatef(-ax, -ay, -az);

	glBegin(GL_TRIANGLES);
	glNormal3fv(normals[i]);
	glVertex3fv(corners[3 * i]);
	glVertex3fv(corners[3 * i + 1]);
	glVertex3fv(corners[3 * i + 2]);
	glEnd();

	glPopMatrix();
    }

    glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(1.0, -1.0, -1.0);
    glEnd();
    glPopMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(-1.f, -1.f, -1.5f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texnames[1]);
    glDepthMask(0);
    time++;
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    exploder(0.f, 0.f, 0.f, size, intensity, opacity, 0.f, 3.f);
    exploder(0.f, 0.f, 1.f, size, intensity, opacity, .2f, 1.4f);
    exploder(0.f, .8f, 1.4f, size, intensity, opacity, .4f, 1.6f);
    exploder(0.f, 1.2f, 0.f, size - .4f, intensity, opacity, .4f, 2.f);
    exploder(1.6f, .3f, 0.f, size - 1.f, intensity, opacity, .5f, 3.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}


void CMySmokeView::Init(GLvoid)
{
    static unsigned *explosionimage,*smokeimage;
    static int width,height,components;
    explode();
    glGenTextures(2, texnames);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    explosionimage = m_Texture.read_texture("explosion0.rgba", &width, &height, &components);
    if (explosionimage == NULL) 
	{
		MessageBox("Can't load image file ","Error",MB_OK);
		exit(EXIT_FAILURE);
    } 
	if (components != 2 && components != 4)
		MessageBox("texture should be an RGBA or LA image","Warning",MB_OK);
    glBindTexture(GL_TEXTURE_2D, texnames[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0,
		 GL_RGBA, GL_UNSIGNED_BYTE, explosionimage);

    smokeimage = m_Texture.read_texture("smoke.la", &width, &height, &components);
    if (explosionimage == NULL) 
	{
	MessageBox("Can't load image file ","Error",MB_OK);
	exit(EXIT_FAILURE);
    } 
	
    if (components != 2 && components != 4)
	MessageBox("texture should be an RGBA or LA image","Warning",MB_OK);

    glBindTexture(GL_TEXTURE_2D, texnames[1]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0,
		 GL_RGBA, GL_UNSIGNED_BYTE, smokeimage);

    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50., 1., .1, 20.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0., 0., -5.5);
    glClearColor(.25f, .25f, .75f, .25f);

    glAlphaFunc(GL_GREATER, 0.016f);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

}

void CMySmokeView::explode(void)
{

	float startcorners[30][3] = {
    {-1.0, -1.0, -1.0},
    {-1.0, 1.0, -1.0},
    {1.0, 1.0, -1.0},
    {1.0, 1.0, -1.0},
    {1.0, -1.0, -1.0},
    {-1.0, -1.0, -1.0},

    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0},

    {-1.0, 1.0, -1.0},
    {1.0, 1.0, -1.0},
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},
    {-1.0, 1.0, -1.0},

    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0},

    {-1.0, -1.0, -1.0},
    {-1.0, 1.0, -1.0},
    {-1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0},
    {-1.0, -1.0, -1.0}
};

	float starttraj[10][3] = {
    {0.25, -0.25, -1.0},
    {-0.25, 0.25, -1.0},
    {0.25, -0.25, 1.0},
    {-0.25, 0.25, 1.0},
    {0.25, 1.0, -0.25},
    {-0.25, 1.0, 0.25},
    {0.25, -1.0, -0.25},
    {-0.25, -1.0, 0.25},
    {-1.0, 0.25, -0.25},
    {-1.0, -0.25, 0.25}};
    static int freeze = 0;
    int i,
        j;
    for (i = 0; i < 30; i++)
	for (j = 0; j < 3; j++)
	    corners[i][j] = startcorners[i][j];

    for (i = 0; i < 10; i++)
	for (j = 0; j < 3; j++)
	    traj[i][j] = starttraj[i][j];

    size = 0.f;
    rot = 0.f;
    opacity = 1.f;
    intensity = 1.f;
    delta = 0.f;
    scale = 1.f;
}


void CMySmokeView::exploder(float x, float y, float z, float size, float intensity, float opacity, float delay, float scale)
{
    if (size - delay <= 0.f)
	return;

    glPushMatrix();
    calcMatrix();
    glTranslatef(x, y, z);
    glScalef((size - delay) * scale, (size - delay) * scale, 1.);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texnames[0]);
    glColor4f(intensity, intensity, intensity, opacity);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(-1.0, -1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(1.0, -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(-1.0, 1.0);
    glEnd();
    glPopMatrix();
}

void CMySmokeView::buildRot(float theta, float x, float y, float z, float m[16])
{
    float d = x * x + y * y + z * z;
    float ct = cosf(RAD(theta)),
          st = sinf(RAD(theta));

    if (d > 0) 
	{
	d = 1 / d;
	x *= d;
	y *= d;
	z *= d;
    }
    m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
    m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

    m[0] = x * x + ct * (1 - x * x) + st * 0;
    m[4] = x * y + ct * (0 - x * y) + st * -z;
    m[8] = x * z + ct * (0 - x * z) + st * y;

    m[1] = y * x + ct * (0 - y * x) + st * z;
    m[5] = y * y + ct * (1 - y * y) + st * 0;
    m[9] = y * z + ct * (0 - y * z) + st * -x;

    m[2] = z * x + ct * (0 - z * x) + st * -y;
    m[6] = z * y + ct * (0 - z * y) + st * x;
    m[10] = z * z + ct * (1 - z * z) + st * 0;
}

void CMySmokeView::calcMatrix(void)
{
    float mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    buildRot(-180 * atan2f(mat[8], mat[10]) / M_PI, 0, 1, 0, mat);
    glMultMatrixf(mat);
}

