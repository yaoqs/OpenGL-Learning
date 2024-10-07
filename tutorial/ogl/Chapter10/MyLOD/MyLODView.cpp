// MyLODView.cpp : implementation of the CMyLODView class
//

#include "stdafx.h"
#include "MyLOD.h"

#include "MyLODDoc.h"
#include "MyLODView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLandTex lt;
int quadtree[QUAD_MAP * QUAD_MAP];
int location[3];
int lod_level=8;
int *y; // 保存地形的高程数组
COLOUR *colour_map; // 保存地形的颜色数值

/////////////////////////////////////////////////////////////////////////////
// CMyLODView

IMPLEMENT_DYNCREATE(CMyLODView, CView)

BEGIN_MESSAGE_MAP(CMyLODView, CView)
	//{{AFX_MSG_MAP(CMyLODView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyLODView construction/destruction

CMyLODView::CMyLODView()
{
	// TODO: add construction code here
	bilinear_filtering = 1;
	wireframe_mode = -1;
	flying_mode = 1;
	detail_texture_mode = -1;
	mapX = 128, mapZ = 128; 
	speed = 0.0; // 移动速度初始化
	timer = 0.0, wTimer = 0.0;
}

CMyLODView::~CMyLODView()
{
}

BOOL CMyLODView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyLODView drawing

void CMyLODView::OnDraw(CDC* pDC)
{
	CMyLODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyLODView printing

BOOL CMyLODView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyLODView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyLODView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyLODView diagnostics

#ifdef _DEBUG
void CMyLODView::AssertValid() const
{
	CView::AssertValid();
}

void CMyLODView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyLODDoc* CMyLODView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyLODDoc)));
	return (CMyLODDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyLODView message handlers

int CMyLODView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyLODView::OnDestroy() 
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
	delete[] y;
	delete[] colour_map;
	m_Bmpload.destroy_bmp(detail_texture);
}

void CMyLODView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	winWidth=cx;
	winHeight=cy;
	
}

void CMyLODView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//添加定时器响应函数和场景更新函数
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	update_world(); 	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  设置逻辑调色板
//////////////////////////////////////////////////////////////////////
void CMyLODView::SetLogicalPalette(void)
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
BOOL CMyLODView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyLODView::SetupPixelFormat()
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
BOOL CMyLODView::RenderScene() 
{
	int i;
	int x, z;
	int aX, aZ;
	int r;
	float v1[3];
	float location_f[3];
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport(0, 0, (GLsizei) winWidth, (GLsizei) winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(60.0, (GLfloat) winWidth/(GLfloat) winHeight, 1.0, ((M_SIZE + 4) * 2) << SHIFT);
	
	// 设置摄像机位置和观看的矢量
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (xpos, ypos, zpos, xpos+lookx, ypos+looky, zpos+lookz, 0.0, 1.0, 0.0);
	
	m_Lod.reset_quad_tree();
	m_Lod.setup_quadtree(128, 128, 128);
	
	if(wireframe_mode < 0) {
		glEnable(GL_TEXTURE_2D);
	}
	else {
		glColor3f(0.0, 0.0, 0.0);
	}
	
	m_Lod.draw(128, 128, 128, 0);  // 地形的绘制
	
	if((wireframe_mode < 0) && (flying_mode < 0) && (detail_texture_mode > 0)) 
	{
		glBindTexture(GL_TEXTURE_2D, texName[20]);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBegin(GL_QUADS);
		location_f[0] = xpos / COMP;
		location_f[2] = zpos / COMP;
		aX = mapX - mapX%2;
		aZ = mapZ - mapZ%2;
		for(x=aX-16; x<aX+16; x+=2) {
			for(z=aZ-16; z<aZ+16; z+=2) {
				v1[0] = x;
				v1[2] = z;
				
				glColor4f(1.0, 1.0, 1.0, 0.5 - DISTANCE(v1, location_f)/20.0f);
				glTexCoord2f(0.0, 0.0);
				m_Lod.setVertex(x, z); 
				
				v1[0] = x;
				v1[2] = z+2;
				
				glColor4f(1.0, 1.0, 1.0, 0.5 - DISTANCE(v1, location_f)/20.0f);
				glTexCoord2f(0.0, 1.0);
				m_Lod.setVertex(x, z+2); 
				
				v1[0] = x+2;
				v1[2] = z+2;
				
				glColor4f(1.0, 1.0, 1.0, 0.5 - DISTANCE(v1, location_f)/20.0f);
				glTexCoord2f(1.0, 1.0);
				m_Lod.setVertex(x+2, z+2); 
				
				v1[0] = x+2;
				v1[2] = z;
				
				glColor4f(1.0, 1.0, 1.0, 0.5 - DISTANCE(v1, location_f)/20.0f);
				glTexCoord2f(1.0, 0.0);
				m_Lod.setVertex(x+2, z); 
			}
		}
		
		glEnd();
		
		glEnable(GL_DEPTH_TEST);
		
		glDisable(GL_BLEND); 
	}

	r = M_SIZE << SHIFT;
	
	glDisable(GL_TEXTURE_2D);
	
	glBegin(GL_QUADS);
	for(i=0; i<256; i+=16) {
		glColor3f(0.12, 0.27, 0.7);
		glVertex3f(xpos + sin_t[(i + 16)&255] * r, (64 << SHIFT), zpos + cos_t[(i + 16)&255] * r);
		
		glColor3f(0.42, 0.57, 1.0);
		glVertex3f(xpos + sin_t[(i + 16)&255] * r, 0, zpos + cos_t[(i + 16)&255] * r);
		
		glColor3f(0.42, 0.57, 1.0);
		glVertex3f(xpos + sin_t[i] * r, 0, zpos + cos_t[i] * r);
		
		glColor3f(0.12, 0.27, 0.7);
		glVertex3f(xpos + sin_t[i] * r, (64 << SHIFT), zpos + cos_t[i] * r);
	}
	
	for(i=0; i<256; i+=16) {
		glColor3f(0.42, 0.57, 1.0);
		glVertex3f(xpos + sin_t[(i + 16)&255] * r, 0, zpos + cos_t[(i + 16)&255] * r);
		
		glColor3f(0.12, 0.27, 0.7);
		glVertex3f(xpos + sin_t[(i + 16)&255] * r, -(16 << SHIFT), zpos + cos_t[(i + 16)&255] * r);
		
		glColor3f(0.12, 0.27, 0.7);
		glVertex3f(xpos + sin_t[i] * r, -(16 << SHIFT), zpos + cos_t[i] * r);
		
		glColor3f(0.42, 0.57, 1.0);
		glVertex3f(xpos + sin_t[i] * r, 0, zpos + cos_t[i] * r);
	}
	
	glEnd();

	glFlush();

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyLODView::Init(void) 
{
	GLfloat fogColor[] = {0.12, 0.27, 0.7, 1.0};
	GLfloat lightDiffuse[] = {1.0, 0.75, 0.5, 1.0};
	
	glClearColor(0.12, 0.27, 0.7, 1.0);
	
	for(int i=0; i<256; i++) {
		sin_t[i] = sin((i/128.0) * PI);
		cos_t[i] = cos((i/128.0) * PI);
	}
	
	initTerrain();  // 初始化地形数据
	
	xpos = (118) * COMP;
	ypos = 10.0;
	zpos = (125) * COMP;
	
	lookx = (120.0) * COMP;
	looky = (0.0) * COMP;
	lookz = (120.0) * COMP;
	
	speed = 0;
	
	update_world();
	
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 1);
	glFogf(GL_FOG_START, (M_SIZE/2)*0.1*COMP);
	glFogf(GL_FOG_END, (M_SIZE/2)*0.5*COMP);
	
	glGenTextures(100, texName);
	
	srand(1111111);

	randomTerrain();
	
	srand((unsigned)time(NULL));

	detail_texture = m_Bmpload.load_bitmap("DETAIL.BMP");

	glBindTexture(GL_TEXTURE_2D, texName[20]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5, detail_texture->w, detail_texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, detail_texture->data);
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightDiffuse);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glShadeModel(GL_SMOOTH);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_DITHER);

	m_Lod.m_bFlag=true;

	move(ROTATE, 2.6, 0);
	move(LOOKUP, -0.2, 0);
	

}

void CMyLODView::initTerrain(void) 
{
	y = new int[M_SIZE*M_SIZE];
	if(!y) 
	{
		MessageBox("Unable to allocate memory for height map.","Error",MB_OK);
	}

	colour_map = new COLOUR[M_SIZE*M_SIZE];
	if(!colour_map) 
	{
		MessageBox("Unable to allocate memory for shadow map.","Error",MB_OK);
	}

}


void CMyLODView::randomTerrain(void) 
{
	int x, z;
	int i, j;
	int bsize, csize;
	int rnd;
	
	for(i=0; i<(M_SIZE*M_SIZE); i++) {
		y[i] = 0;
	}
	
	bsize = M_SIZE;
	csize = M_SIZE/2;
	
	rnd = 256;
	
	while(csize > 0) {
		for(x=0; x<M_SIZE; x+=bsize) {
			for(z=0; z<M_SIZE; z+=bsize) {
				y[IX(x+csize, z+csize)] =   f4(y[IX(x, z)], y[IX(x+bsize, z)], y[IX(x+bsize, z+bsize)], y[IX(x, z+bsize)]) + rand()%(rnd+1) - (rnd/2);
			}
		}
		
		for(x=0; x<M_SIZE; x+=bsize) {
			for(z=0; z<M_SIZE; z+=bsize) {
				y[IX(x+csize, z)] = f4(y[IX(x, z)],
					y[IX(x+bsize, z)],
					y[IX(x+csize, z+csize)],
					y[IX(x+csize, z-csize)]) + (rand()%(rnd+1) - (rnd/2));
			}
		}
		
		for(x=0; x<M_SIZE; x+=bsize) {
			for(z=0; z<M_SIZE; z+=bsize) {
				y[IX(x, z+csize)] = f4(y[IX(x, z)],
					y[IX(x, z+bsize)],
					y[IX(x-csize, z+csize)],
					y[IX(x+csize, z+csize)]) + (rand()%(rnd+1) - (rnd/2));
			}
		} 
		
		bsize /= 2;
		csize /= 2;
		if(csize < 16)
			rnd /= 2;
	}
	
	
	for(i=0; i<M_SIZE*M_SIZE; i++) {
		if(y[i] < 0) {
			y[i] = 0;
		}
	} 
	
	for(j=0; j<4; j++) {
		x = rand()%M_SIZE;
		z = rand()%M_SIZE;
		
		for(i=0; i<100; i++) {
			x += rand()%17 - 8;
			z += rand()%17 - 8;
			
			y[IX(x, z)] = 1000; 
		}
		
	}
	
	// 高程数据的平滑处理
	
	for(j=0; j<8; j++) {
		for(x=0; x<M_SIZE; x++) {
			for(z=0; z<M_SIZE; z++) {
				i =	y[IX(x-1, z-1)] +
					y[IX(x,   z-1)] +
					y[IX(x+1, z-1)] +
					y[IX(x-1, z)] + 
					y[IX(x,   z)] +
					y[IX(x+1, z)] +
					y[IX(x-1, z+1)] +
					y[IX(x,   z+1)] + 
					y[IX(x+1, z+1)];
				
				y[IX(x, z)] = i / 9;
			}
		}
	} 
	
	colorTerrain();
}

void CMyLODView::update_world(void)
{
	timer += 0.05;
	wTimer += 0.0005;
	
	if(wTimer>1.0) {
		wTimer = 0.0;
	}
	
	move(FORWARD, speed, 1);
}

void CMyLODView::move(int type, GLfloat amount, int update)
{
	GLfloat lightPosition[] = {-1.0, 0.0, 0.2, 0.0};
	GLfloat a;
	switch(type)
	{
	case FORWARD:
		xpos += lookx * amount;
		zpos += lookz * amount;
		break;
	case ROTATE:
		lookx = lookx*cos(amount) + lookz*sin(amount);
		lookz = lookz*cos(amount) - lookx*sin(amount);
		a = 1/sqrt(lookx*lookx + lookz*lookz);
		lookx *= a;
		lookz *= a;
		break;
	case LOOKUP:
		looky += amount;
		break;
	}
	
	if (update)
	{
		check_height();
		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
		
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	}
}

void CMyLODView::check_height(void) 
{
	
	float x0, x1, lx, lz, x, z, midpoint;
	int fx, fz;
	
	x = xpos/(COMP*1.0);
	z = zpos/(COMP*1.0);
	fx = (int)(x);
	fz = (int)(z);
	lx = x - fx;
	lz = z - fz;
	
	x0 = y[IX(fx,fz)] + (y[IX(fx,fz+1)] - y[IX(fx,fz)])*lz;
	x1 = y[IX(fx+1,fz)] + (y[IX(fx+1,fz+1)] - y[IX(fx+1,fz)])*lz;
	midpoint = x0 + (x1 - x0)*lx;

	if(flying_mode	> 0) {
		ypos = (midpoint * 8) + 1024.0f;
	}
	else {
		ypos = (midpoint * 8) + 16.0f;
	}

	if(x<0)
		xpos = 0;
	else if(x>(M_SIZE))
		xpos = ((M_SIZE) << SHIFT);
	if(z<0)
		zpos = 0;
	else if(z>(M_SIZE))
		zpos = ((M_SIZE) << SHIFT);
	
}


void CMyLODView::colorTerrain(void) 
{
	int x, z;
	int h;
	
	for(x=0; x<M_SIZE; x++) {
		for(z=0; z<M_SIZE; z++) {
			h = 200 + (y[IX(x, z)] - y[IX(x+1, z)]) * 8;
			
			if(h>255) 		
				h = 255;			
			else if(h<0)			
				h = 0; 
									
			colour_map[IX(x, z)].r = h;
			colour_map[IX(x, z)].g = h;
			colour_map[IX(x, z)].b = h;
		}
	}
	
	lt.NEW_BITMAP(texName, y);
}

void CMyLODView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==0x57) //VK_W
	{
		if(flying_mode > 0) 
		{
			if(speed < 128) 
			{
				speed += 8;
			}
		}
		else 
		{
			if(speed < 8) 
			{
				speed += 2;
			}
		}
	}
	else 
	{
		if(flying_mode > 0) 
		{
			if(speed > 0) 
			{
				speed -= 4;
			}
		}
		else 
		{
			if(speed > 0) 
			{
				speed -= 1;
			}
		}
	}

	if(nChar==0x53) //VK_S
	{
		speed = 0;
	}
	
	if(nChar==0x31) //VK_1
	{
		lod_level = 8;
	}
	if(nChar==0x32) //VK_2
	{
		lod_level = 16;
	}
	if(nChar==0x33) //VK_3
	{
		lod_level = 32;
	}
	if(nChar==0x34) //VK_4
	{
		lod_level = 64;
	}
			
	if(nChar==0x54) //VK_T
	{
		detail_texture_mode = -detail_texture_mode;
		Sleep(100);
	}

	if(nChar==0x46) //VK_F
	{
		flying_mode = -flying_mode;  //视点运动模式开关
		speed = 0;
		Sleep(100);
	}
		
	if(nChar==0x42) //VK_B
	{
		for(int i=0; i<100; i++) 
		{
			glBindTexture(GL_TEXTURE_2D, texName[i]);
			if(bilinear_filtering > 0) 
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}
			else 
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
		}
				
		bilinear_filtering = -bilinear_filtering;
				
		Sleep(100);
	}
	if(nChar==0x4D) //VK_M
	{
		if(wireframe_mode > 0) 
		{
			m_Lod.m_bFlag = true;  //线框模式
		}
		else 
		{
			m_Lod.m_bFlag = false;   //纹理模式
		}
				
		wireframe_mode = -wireframe_mode;
				
		Sleep(100);
	}
			
	if(nChar==VK_SPACE) 
	{
		randomTerrain();  // 生成随机地形
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
