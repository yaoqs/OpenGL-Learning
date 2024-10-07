// MyFountainView.cpp : implementation of the CMyFountainView class
//

#include "stdafx.h"
#include "MyFountain.h"

#include "MyFountainDoc.h"
#include "MyFountainView.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFountainView

IMPLEMENT_DYNCREATE(CMyFountainView, CView)

BEGIN_MESSAGE_MAP(CMyFountainView, CView)
	//{{AFX_MSG_MAP(CMyFountainView)
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
// CMyFountainView construction/destruction

CMyFountainView::CMyFountainView()
{
	// TODO: add construction code here

}

CMyFountainView::~CMyFountainView()
{
}

BOOL CMyFountainView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyFountainView drawing

void CMyFountainView::OnDraw(CDC* pDC)
{
	CMyFountainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyFountainView printing

BOOL CMyFountainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFountainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFountainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFountainView diagnostics

#ifdef _DEBUG
void CMyFountainView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFountainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFountainDoc* CMyFountainView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFountainDoc)));
	return (CMyFountainDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFountainView message handlers

int CMyFountainView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyFountainView::OnDestroy() 
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

void CMyFountainView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 1000);
  glMatrixMode(GL_MODELVIEW);

}

void CMyFountainView::OnTimer(UINT nIDEvent) 
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
void CMyFountainView::SetLogicalPalette(void)
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
BOOL CMyFountainView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyFountainView::SetupPixelFormat()
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
BOOL CMyFountainView::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	a += 0.2;
	gluLookAt(cam.x, cam.y, cam.z, 0, 0, 0, upv.x, upv.y, upv.z); 
	// 绘制地面
	glPushMatrix();
	glRotatef(a, 0, -1, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-100, 0, -100);
		glTexCoord2f(2, 0); glVertex3f(-100, 0, 100);
		glTexCoord2f(2, 2); glVertex3f(100, 0, 100);
		glTexCoord2f(0, 2); glVertex3f(100, 0, -100);
	glEnd();
	glPopMatrix();

	// 绘制喷泉
	DrawFountain();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	glRotatef(a, 0, -1, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-100, 0, -100);
		glTexCoord2f(1, 0); glVertex3f(-100, 0, 100);
		glTexCoord2f(1, 1); glVertex3f(100, 0, 100);
		glTexCoord2f(0, 1); glVertex3f(100, 0, -100);
	glEnd();
	glPopMatrix();
 
	glFlush();  

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}


// 喷泉的初始化
void CMyFountainView::Init()
{
	a=0;
    fn[0] = NULL;
	fn[1] = NULL;
	fn[2] = NULL;
	upv.x = -5;
	upv.y = 5;
	upv.z = -5;
	cam.x = 200;
	cam.y = 200;
	cam.z = 200;
	glGenTextures(3, texture); 
	glClearColor(0, 0, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	LoadTexture("particle.rgb", 0);
	LoadTexture("ground1.rgb", 1);
	LoadTexture("ground2.rgb", 2);
}

// 纹理装入函数
void CMyFountainView::LoadTexture(char *fn, int t_num)
{
	int texwid, texht;
	int texcomps;
	
	teximage = m_Tex->read_texture(fn, &texwid, &texht, &texcomps);
	if (!teximage)
	{
		MessageBox("Sorry, can't read texture file...","ERROR",MB_OK);
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, texture[t_num]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

	if ((t_num == 0) || (t_num == 2)) glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	if (t_num == 1)
	{
		// 对于地面纹理,重复纹理参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	}
	free(teximage);
} 


// 添加新的粒子
void CMyFountainView::AddParticles()
{
	struct particle *tempp;
	int i, j;

	for (j=0; j<3; j++)
		for (i=0; i<2; i++)
		{
			tempp = (struct particle *)malloc(sizeof(struct particle));
			if (fn[j]) fn[j]->prev = tempp;
			tempp->next = fn[j];
			fn[j] = tempp;
			
			tempp->t = -9.9;
			tempp->v = (float)(rand() % 200000)/100000+1; // 粒子速度
			tempp->d = (float)(rand() % 400)/100-2;       // 粒子方向
			// 开始位置的坐标
			tempp->x = 0;
			tempp->y = 0;
			tempp->z = 0;
			tempp->xd = cos((tempp->d*3.14159)/180)*tempp->v/4;
			tempp->zd = sin((tempp->d*3.14159)/180)*tempp->v;
			tempp->type = 0; // 粒子状态为运动
			tempp->a = 1;    // 粒子淡化
		}
}

// 粒子运动函数
void CMyFountainView::MoveParticles()
{
	struct particle *tempp;
	int j;
	for (j=0; j<3; j++)
	{
		tempp = fn[j]; 
		while (tempp)
		{
			if (tempp->type == 0) // 如果粒子处于运动状态
			{
				tempp->x += tempp->xd;
				tempp->z += tempp->zd;
				tempp->y = -(9.8*(tempp->t*tempp->t/4))/2+122.5; // 计算粒子的高度 H = gt^2/2 
				tempp->t += 0.1; // 增加粒子寿命
				if (tempp->y < 0) tempp->type = 1; // 如果粒子位于地面
			}else // 粒子位于地面
			{
				tempp->y = -(9.8*(tempp->t*tempp->t/4))/2+122.5; 
				tempp->a -= 0.1; // 粒子淡化
			}
			tempp = tempp->next; // 下一个粒子
		}
	}
}

//删除粒子
void CMyFountainView::DeleteParticles()
{
	struct particle *tempp, *temp1;
	int j;

	for (j=0; j<3; j++)
	{
		tempp = fn[j];
		while (tempp)
		{
			if ((tempp->type == 1) && (tempp->a <= 0)) // 粒子死亡
			{
				// 删除粒子
				temp1 = tempp->prev;
				tempp->prev->next = tempp->next;
				if (tempp->next) tempp->next->prev = temp1;
				free(tempp);
				tempp = temp1;
			}
			tempp = tempp->next;
		}
	}
}

void CMyFountainView::vect_mult(struct point *A, struct point *B, struct point *C)
{
	// 矢量相乘
	C->x = A->y*B->z - A->z*B->y;
	C->y = A->z*B->x - A->x*B->z;
	C->z = A->x*B->y - A->y*B->x;
}

// 矢量单位化
void CMyFountainView::normalize(struct point *V)
{
	float d;
	// 矢量长度
	d = sqrt(V->x*V->x + V->y*V->y + V->z*V->z);
	// 单位化
	V->x /= d; 
	V->y /= d; 
	V->z /= d; 
}

void CMyFountainView::DrawFountain()
{
	int j;
	struct particle *tempp;
	struct point vectd, vectl; 
	float alpha, ttx, ttz;

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	AddParticles();
	MoveParticles();
	DeleteParticles();
	glPushMatrix();
	for (j=0; j<3; j++)
	{
		glBegin(GL_QUADS);
		tempp = fn[j];
		while (tempp)
		{
			// 旋转喷泉
			alpha = ((j*120+a)*PI)/180;
			ttx = tempp->x*cos(alpha)-tempp->z*sin(alpha);
			ttz = tempp->x*sin(alpha)+tempp->z*cos(alpha);
			// 计算方向矢量
			vectd.x = ttx - cam.x;
			vectd.y = tempp->y - cam.y;
			vectd.z = ttz - cam.z;
			vect_mult(&vectd, &upv, &vectl);
			normalize(&vectl);
			vectl.x *= 5;
			vectl.y *= 5;
			vectl.z *= 5;
			glColor4f(0.5, 0.5, 1, tempp->a);
			// 绘制多边形和粒子纹理映射
			glTexCoord2f(0, 0); glVertex3f((ttx-vectl.x), (tempp->y-upv.y), (ttz-vectl.z));
			glTexCoord2f(1, 0); glVertex3f((ttx+vectl.x), (tempp->y-upv.y), (ttz+vectl.z));
			glTexCoord2f(1, 1); glVertex3f((ttx+vectl.x), (tempp->y+upv.y), (ttz+vectl.z));
			glTexCoord2f(0, 1); glVertex3f((ttx-vectl.x), (tempp->y+upv.y), (ttz-vectl.z));
			tempp = tempp->next; // 绘制下一个粒子列表
		}
		glEnd();
	}
	glPopMatrix();
}