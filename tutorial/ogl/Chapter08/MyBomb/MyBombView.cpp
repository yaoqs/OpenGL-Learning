// MyBombView.cpp : implementation of the CMyBombView class
//

#include "stdafx.h"
#include "MyBomb.h"

#include "MyBombDoc.h"
#include "MyBombView.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBombView

IMPLEMENT_DYNCREATE(CMyBombView, CView)

BEGIN_MESSAGE_MAP(CMyBombView, CView)
	//{{AFX_MSG_MAP(CMyBombView)
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
// CMyBombView construction/destruction

CMyBombView::CMyBombView()
{
	// TODO: add construction code here
	active=TRUE;		
	fcol=false;
	dcol=0,rcol=0;
	fcamera=false;
	ancamera=0;
	xcam=0,ycam=5,zcam=20;
}

CMyBombView::~CMyBombView()
{
}

BOOL CMyBombView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyBombView drawing

void CMyBombView::OnDraw(CDC* pDC)
{
	CMyBombDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//渲染场景
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyBombView printing

BOOL CMyBombView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyBombView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyBombView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyBombView diagnostics

#ifdef _DEBUG
void CMyBombView::AssertValid() const
{
	CView::AssertValid();
}

void CMyBombView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyBombDoc* CMyBombView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyBombDoc)));
	return (CMyBombDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyBombView message handlers

int CMyBombView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyBombView::OnDestroy() 
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

void CMyBombView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(45.0f,(GLfloat)cx/(GLfloat)cy,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	
}

void CMyBombView::OnTimer(UINT nIDEvent) 
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
void CMyBombView::SetLogicalPalette(void)
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
BOOL CMyBombView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyBombView::SetupPixelFormat()
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
BOOL CMyBombView::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();									

	if(fcamera==false)
		gluLookAt(0,5,20,0,0,0,0.0f,1.0f,0.0f);
	else
	{
		xcam=20*sin(ancamera*3.141/180);
		ycam=5+ancamera/100;
		zcam=20*cos(ancamera*3.141/180);
		ancamera+=0.1;
		gluLookAt(xcam,ycam,zcam,0,0,0,0.0f,1.0f,0.0f);
	}

	Movepp();
	Drawbk();
	Drawpp();

	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	return TRUE;
}

void CMyBombView::Drawbk(void)
{
	float t;
	float col=0;

	if(fcol==true)
	{
		dcol-=4;
		col=rcol*sin(dcol*3.141/180);
		rcol-=0.001;
		if(rcol<=0)
			fcol=false;
	}
	
	glColor3f(1,1,1);
	for(t=-20;t<20;t+=3)
	{
		glBegin(GL_LINES);
		glVertex3f(-20,col,t);
		glVertex3f(20,col,t);
		glVertex3f(t,col,-20);
		glVertex3f(t,col,20);
		glEnd();
	}
}

void CMyBombView::Drawpp(void)
{
	int t;

	if(pp[0].active==true)
	{
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();

		glColor3f(1,1,1);
		glTranslatef(pp[0].x,pp[0].y,pp[0].z);
		glRotatef(90,1,1,0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		gluSphere(quadratic,0.5,8,8);

		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		for(t=1;t<PMAX;t++)
			Luce(pp[t].x,pp[t].y,pp[t].z,1,pp[t].time,pp[t].time,pp[t].time,xcam,ycam,zcam,1);
	}
}

void CMyBombView::Makepp(void)
{
	int t;
	float dx,dy,dz;

	for(t=1;t<PMAX;t++)
		pp[t].active=false;

	pp[0].x=(float)(rand()%10-rand()%10);
	pp[0].y=5+(float)(rand()%5);
	pp[0].z=(float)(rand()%10-rand()%10);

	dx=(0-pp[0].x)/100;
	dy=(0-pp[0].y)/100;
	dz=(0-pp[0].z)/100;

	pp[0].dx=dx;
	pp[0].dy=dy;
	pp[0].dz=dz;

	pp[0].active=true;
}

void CMyBombView::Makesp(void)
{
	int t;
	float fan,an=0;
	float dx,dy,dz;

	fan=(float)360/PMAX;

	for(t=1;t<PMAX;t++)
	{
		pp[t].active=true;
		pp[t].time=(float)(rand()%100)/1000+0.5;
		
		pp[t].x=pp[0].x;
		pp[t].y=-pp[0].y;
		pp[t].z=pp[0].z;
		
		dx=cos(an*3.141/180)/((float)FV/(rand()%3));
		dy=(float)(rand()%100)/1000;
		dz=sin(an*3.141/180)/((float)FV/(rand()%3));
		pp[t].dx=dx;
		pp[t].dy=dy;
		pp[t].dz=dz;
		an=an+fan+(float)(rand()%10)/2;
	}
}

void CMyBombView::Movepp(void)
{
	int t,k=PMAX-1;

	if(pp[0].active==false)
	{
		for(t=1;t<PMAX;t++)
		{
			if(pp[t].active==true)
			{
				pp[t].time-=FTIME;
				if(pp[t].time<=0)
					pp[t].active=false;
				
				pp[t].x+=(pp[t].dx);
				pp[t].y+=pp[t].dy;
				pp[t].z+=(pp[t].dz);
				pp[t].dy-=(float)GRAVITY;

				if(pp[t].y<0)
				{
					pp[t].dy=-pp[t].dy/2;
					pp[t].y+=pp[t].dy;
					pp[t].dx=pp[t].dx/2;
					pp[t].dz=pp[t].dz/2;
				}
			}
			else
				k--;
		}
	}
	else
	{
		pp[0].dy-=(float)GRAVITY;
		pp[0].x+=pp[0].dx;
		pp[0].y+=pp[0].dy;
		pp[0].z+=pp[0].dz;

		if(pp[0].y<0)
		{
			pp[0].active=false;
			dcol=0;
			rcol=0.2;
			fcol=true;
			Makesp();
		}
	}

	if(k<=1)
		Makepp();
}

double CMyBombView::VectorLength( Vector v )
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector CMyBombView::VectorNormalize( Vector v )
{
	Vector vresult;
	double l = VectorLength( v );

	vresult.x = v.x/l;
	vresult.y = v.y/l;
	vresult.z = v.z/l;

	return vresult;
}

Vector CMyBombView::VectorMultiply( Vector v1, Vector v2 )
{
	Vector vresult;

	vresult.x = v1.y * v2.z - v1.z * v2.y;
	vresult.y = v1.z * v2.x - v1.x * v2.z;
	vresult.z = v1.x * v2.y - v1.y * v2.x;

	return vresult;
}

Vector CMyBombView::VectorScalarMultiply( Vector v, double s )
{
	Vector vresult;

	vresult.x = v.x * s;
	vresult.y = v.y * s;
	vresult.z = v.z * s;

	return vresult;
}

Vector CMyBombView::VectorDiff( Vector v1, Vector v2 )
{
	Vector vresult;

	vresult.x = v1.x - v2.x;
	vresult.y = v1.y - v2.y;
	vresult.z = v1.z - v2.z;

	return vresult;
}

void CMyBombView::Luce(double x, double y, double z,double dimensione,float r,float g,float b,float iox,float ioy,float ioz,int Tex)
{
	Vector Position;
	Vector MyPosition;
	Position.x = x;
	Position.y = y;
	Position.z = z;

	MyPosition.x=iox;
	MyPosition.y=ioy;
	MyPosition.z=ioz;
	Vector sight = VectorDiff(MyPosition, Position);

	Vector cz;
	cz.x = 0;
	cz.y = 0;
	cz.z = 1;

	Vector cross1 = VectorMultiply( sight, cz );
	Vector cross2 = VectorMultiply( sight, cross1 );

	cross1 = VectorNormalize(cross1);
	cross2 = VectorNormalize(cross2);

	cross1 = VectorScalarMultiply(cross1, dimensione);
	cross2 = VectorScalarMultiply(cross2, dimensione);

	glColor3f(r,g,b);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc( (1,1,1,1), (1,1,1,1));
	glDepthMask (GL_FALSE);

	glBindTexture( GL_TEXTURE_2D, texture[Tex] );
	glBegin(GL_QUADS);
		glTexCoord2d( 0.0, 0.0 );
		glVertex3d( Position.x + cross1.x, Position.y + cross1.y, Position.z + cross1.z);
		glTexCoord2d( 1.0, 0.0 );
		glVertex3d( Position.x - cross2.x, Position.y - cross2.y, Position.z - cross2.z);
		glTexCoord2d( 1.0, 1.0 );
		glVertex3d( Position.x - cross1.x, Position.y - cross1.y, Position.z - cross1.z);
		glTexCoord2d( 0.0, 1.0 );
		glVertex3d( Position.x + cross2.x, Position.y + cross2.y, Position.z + cross2.z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable (GL_BLEND);
	glDepthMask (GL_TRUE);
}

AUX_RGBImageRec * CMyBombView::LoadBMP(char *Filename)				
{
	FILE *File=NULL;									

	if (!Filename)										
	{
		return NULL;									
	}

	File=fopen(Filename,"r");							

	if (File)											
	{
		fclose(File);									
		return auxDIBImageLoad(Filename);				
	}

	return NULL;									
}

int CMyBombView::LoadGLTextures()				
{
	int Status=FALSE;							

	AUX_RGBImageRec *TextureImage[1];					

	memset(TextureImage,0,sizeof(void *)*1);           

	if (TextureImage[0]=LoadBMP("PP0.bmp"))
	{
		Status=TRUE;								

		glGenTextures(1, &texture[0]);	

		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

	if (TextureImage[0]=LoadBMP("PP.bmp"))
	{
		Status=TRUE;								

		glGenTextures(1, &texture[1]);		

		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

	if (TextureImage[0])							
	{
		if (TextureImage[0]->data)				
		{
			free(TextureImage[0]->data);	
		}

		free(TextureImage[0]);		
	}

	return Status;				
}


int CMyBombView::Init(GLvoid)	
{
	if (!LoadGLTextures())		// 装入纹理
	{
		return FALSE;									
	}

	Makepp();
	
	glEnable(GL_TEXTURE_2D);						
	glShadeModel(GL_SMOOTH);				
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);					
	glEnable(GL_DEPTH_TEST);		
	glDepthFunc(GL_LEQUAL);							
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	quadratic=gluNewQuadric();					
	gluQuadricNormals(quadratic, GLU_SMOOTH);	
	gluQuadricTexture(quadratic, GL_TRUE);		

	return TRUE;								
}

