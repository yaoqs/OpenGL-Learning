// Terrain3DTestView.cpp : implementation of the CTerrain3DTestView class
//

#include "stdafx.h"
#include "Terrain3DTest.h"
#include "MilkShapeModel.h"

#include "Terrain3DTestDoc.h"
#include "Terrain3DTestView.h"
#include "math.h"
#include <ppl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
GLuint texturem = 0;
GLfloat XPOS = -MAX/2;
GLfloat YPOS = 0;
GLfloat ZPOS = -MAX/2;
GLfloat XP=0;
GLfloat YP=0;
GLfloat ZP=0;

GLfloat xtrans = MAX/2;
GLfloat ytrans = 0;
GLfloat ztrans = MAX/2;

GLfloat visual_distance = 100;
GLfloat sun_height = 1000;
GLfloat sun_zdistance = -5000;

GLfloat xtexa; 
GLfloat ytexa; 
GLfloat xtexa2; 
GLfloat ytexa2; 
    
int xrange1 ; 
int xrange2 ;
int zrange1 ;
int zrange2 ;   

GLfloat	xrot=0;				// �� X ����ת
GLfloat	yrot=0;				// �� Y ����ת
GLfloat	zrot=0;				// �� Z ����ת
GLfloat Throttlei;
GLfloat Throttle = 5;
GLfloat _Throttle=Throttle;
GLfloat Speed = Throttle;
GLfloat Speedi;
GLfloat piover180 = 0.0174532925f;
GLfloat sceneroty;
GLfloat heading;
GLfloat pitch = 0;
GLfloat yaw = 0;

GLfloat zprot;

int quality = 3;

GLfloat H = 0;

GLfloat glow = .4;
GLfloat glowp = 0;

bool  wireframe = FALSE;	// �߿����ģʽON/OFF
bool  water = true;			// �Ƿ����ˮ ON/OFF
bool  Afterburner = false;

GLUquadricObj *quadratic;
GLuint	texture[8];

GLuint MODEL;

GLfloat V;
GLfloat Angle;
int loop;

/////////////////////////////////////////////////////////////////////////////
// CTerrain3DTestView

IMPLEMENT_DYNCREATE(CTerrain3DTestView, CView)

BEGIN_MESSAGE_MAP(CTerrain3DTestView, CView)
	//{{AFX_MSG_MAP(CTerrain3DTestView)
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
// CTerrain3DTestView construction/destruction

CTerrain3DTestView::CTerrain3DTestView()
{
	// TODO: add construction code here
	pModel = NULL;
}

CTerrain3DTestView::~CTerrain3DTestView()
{
}

BOOL CTerrain3DTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
////////////////////////////////////////////////////////////////
//���ô�������
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
////////////////////////////////////////////////////////////////
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTerrain3DTestView drawing

void CTerrain3DTestView::OnDraw(CDC* pDC)
{
	CTerrain3DTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	
	RenderScene();	//��Ⱦ����

//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CTerrain3DTestView printing

BOOL CTerrain3DTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTerrain3DTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTerrain3DTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTerrain3DTestView diagnostics

#ifdef _DEBUG
void CTerrain3DTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTerrain3DTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTerrain3DTestDoc* CTerrain3DTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTerrain3DTestDoc)));
	return (CTerrain3DTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTerrain3DTestView message handlers

int CTerrain3DTestView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//////////////////////////////////////////////////////////////////
//��ʼ��OpenGL�����ö�ʱ��
	m_pDC = new CClientDC(this);
	SetTimer(1, 20, NULL);
	InitializeOpenGL(m_pDC);
//////////////////////////////////////////////////////////////////
	pModel = new MilkShapeModel();									// Memory To Hold The Model
	if ( pModel->loadModelData( "model.ms3d" ) == false )		// Loads The Model And Checks For Errors
	{
		MessageBox( "Couldn't load the model data\\model.ms3d", "Error", MB_OK | MB_ICONERROR );
		return 0;													// If Model Didn't Load Quit
	}

	InitGL();
	return 0;
}

void CTerrain3DTestView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//ɾ����ɫ�����Ⱦ�����ġ���ʱ��
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

void CTerrain3DTestView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (cy==0)	
	{
		cy=1;	
	}
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	

	gluPerspective(90.0f,(GLfloat)cx/(GLfloat)cy,0.9f,50000.0f);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	
}

void CTerrain3DTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//��Ӷ�ʱ����Ӧ�����ͳ������º���
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  �����߼���ɫ��
//////////////////////////////////////////////////////////////////////
void CTerrain3DTestView::SetLogicalPalette(void)
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
//						��ʼ��openGL����
//////////////////////////////////////////////////////////
BOOL CTerrain3DTestView::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	//���ɻ���������
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//�õ�ǰ����������
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return TRUE;
}

//////////////////////////////////////////////////////////
//						�������ظ�ʽ
//////////////////////////////////////////////////////////
BOOL CTerrain3DTestView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
	    1,                                // �汾�� 
	    PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
	    PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
	    PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
	    PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
	    24,                               // 24 λ��ɫ��� 
	    0, 0, 0, 0, 0, 0,                 // ������ɫλ 
	    0,                                // û�з�͸���Ȼ��� 
	    0,                                // ������λλ 
	    0,                                // ���ۼӻ��� 
	    0, 0, 0, 0,                       // �����ۼ�λ 
	    32,                               // 32 λ��Ȼ���     
	    0,                                // ��ģ�建�� 
	    0,                                // �޸������� 
	    PFD_MAIN_PLANE,                   // ���� 
	    0,                                // ���� 
	    0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);//ѡ�����ظ�ʽ
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);	//�������ظ�ʽ
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//�����߼���ɫ��
	return TRUE;
}



//////////////////////////////////////////////////////////
//						������������Ⱦ
//////////////////////////////////////////////////////////
BOOL CTerrain3DTestView::RenderScene() 
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//////////////////////////////////////
	
///////////////////////////////////////
  	RestoreMyDefaultSettings(); 

	if (-XPOS < 0) XPOS -= MAX; 
	if (-XPOS > MAX) XPOS += MAX;
	if (-ZPOS < 0) ZPOS -= MAX; 
	if (-ZPOS > MAX) ZPOS += MAX;

	xtrans = -XPOS;
	ytrans = YPOS;   
	ztrans = -ZPOS;
	
	yrot = heading;
    
	sceneroty = 360.0f - yrot;
	H = sceneroty;
	if (H > 360) H = 0;
	else if (H < 0) H = 360;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0,0,-10);
	glRotatef(sceneroty,0,1,0);
	glTranslatef(xtrans,ytrans-3.5-ABS(Speed)/5,ztrans);    
   
	xrange1 = int(MAX-xtrans - visual_distance); 
	xrange2 = int(MAX-xtrans + visual_distance);
	zrange1 = int(MAX-ztrans - visual_distance);
	zrange2 = int(MAX-ztrans + visual_distance);   
  
	if (quality != 1)
	{
		xrange1 /= quality;
		xrange1 *= quality;
		xrange2 /= quality;
		xrange2 *= quality;

		zrange1 /= quality;
		zrange1 *= quality;
		zrange2 /= quality;
		zrange2 *= quality;
	}    

	if (wireframe)
	{  
		DrawWireframe();
	}
	else
	{ 
		DrawTexture();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	Caculate();

	/////////////////////////////
	/*glRasterPos3d(10,2,0);
	glEnable(GL_SCISSOR_TEST);
	//	glScissor(0,0,::GetSystemMetrics(SM_CXMAXIMIZED),::GetSystemMetrics(SM_CYMAXIMIZED));
	glScissor(::GetSystemMetrics(SM_CXMAXIMIZED)/2,::GetSystemMetrics(SM_CYMAXIMIZED)/2,100,100);*/
	
	GLuint base=100;
	wglUseFontBitmaps(wglGetCurrentDC(),0,255,base);
	glListBase(base);
	static CString str(_T("Love"));
	str+="A";
	glCallLists(str.GetLength(),GL_UNSIGNED_BYTE ,str);
	if (GLEE_ARB_window_pos)
	{
		
		glWindowPos2iARB(0,0);
	}
	else
	{
		GLint viewport[4];
		GLdouble modelview[16],projection[16];
		GLdouble x,y,z;

		glGetIntegerv(GL_VIEWPORT,viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
		glGetDoublev(GL_PROJECTION_MATRIX,projection);
		gluUnProject(0,0,0.5,modelview,projection,viewport,&x,&y,&z);
		glRasterPos3d(x,y,z);
	}
	
	

//	glScissor(0,0,::GetSystemMetrics(SM_CXMAXIMIZED),::GetSystemMetrics(SM_CYMAXIMIZED));
	/////////////////////////////

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

bool CTerrain3DTestView::InitGL(GLvoid)
{

	if (!m_texture.LoadGLTextures())				// װ������
	{
		return FALSE;								// �����������,�򷵻�FALSE
	}
	float fog_r = 211.f/255.f;
	float fog_g = 237.f/255.f;
	float fog_b = 254.f/255.f;
	glClearColor(fog_r, fog_g, fog_b, 1);			// �ڱ�����ɫ
	glClearDepth(1.0f);		   							// ��Ȼ�������
  
	RestoreMyDefaultSettings();
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    // ���ù���Ч��
	GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightSpecular[]=	{ 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightPosition[]=	{ 0.0f, 0.0f, 0.0f, 1.0f };
	
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	
	glLightfv(GL_LIGHT1, GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);							
	// ������Ч��
	GLuint	fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };	// �����������ģʽ
	GLuint	fogfilter = 0;								// ��ǰʹ�õ����ģʽ 
	GLfloat	fogColor[4] = {fog_r, fog_g, fog_b, 1};		// �����ɫ

	glFogi(GL_FOG_MODE, fogMode[2]);			        // �������ģʽ
	glFogfv(GL_FOG_COLOR, fogColor);					// ���������ɫ
	glFogf(GL_FOG_DENSITY, 0.294f);						// �������Ũ��
	glHint(GL_FOG_HINT, GL_NICEST);					    // Fog Hint Value
	glFogf(GL_FOG_START, 10.0f);						// ������Ŀ�ʼ���
	glFogf(GL_FOG_END, visual_distance);				// ������Ľ������
	glEnable(GL_FOG);									// ʹ����

	quadratic=gluNewQuadric();						
	gluQuadricNormals(quadratic, GLU_SMOOTH);			// ���ɹ⻬����
	gluQuadricTexture(quadratic, GL_TRUE);				// ������������

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	InitTerrain();
	InitSmoke();
	MODEL = pModel->makeDisplayList();			// ����ģ�͵���ʾ�б�

	return TRUE;

}

GLfloat CTerrain3DTestView::Hypot(GLfloat A, GLfloat B)
{
	return sqrt(A*A+B*B);
}

GLfloat CTerrain3DTestView::ABS(GLfloat A)
{
	if (A < 0)
		A = -A; 
	return A;
}
void CTerrain3DTestView::RestoreMyDefaultSettings()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_FOG);
}

void CTerrain3DTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==49)	// ����'1'��
	{
		_Throttle = 1;
	}
	if(nChar==50)	// ����'2'��
	{
		_Throttle = 2;
	}
	if(nChar==51)	// ����'3'��
	{
		_Throttle = 3;
	}
	if(nChar==52)	// ����'4'��
	{
		_Throttle = 4;
	}	
	if(nChar==53)	// ����'5'��
	{
		_Throttle = 5;
	}
	if(nChar==54)	// ����'6'��
	{
		_Throttle = 6;
	}	
	if(nChar==55)	// ����'7'��
	{
		_Throttle = 7;
	}
	if(nChar==56)	// ����'8'��
	{
		_Throttle = 8;
	}
	if(nChar==57)	// ����'9'��
	{
		_Throttle = 9;
	}
	if(nChar==48)	// ����'0'��
	{
		_Throttle = 15;
	}

	if(nChar==VK_UP)
	{
		pitch -= 15 / (ABS(Speed)+1);
	}
	if(nChar==VK_DOWN)
	{
		pitch += 15 / (ABS(Speed)+1);
	}
	if(nChar==VK_LEFT)
	{
		zprot += 5/(ABS(Speed)+1);
		Throttle*=.99;               

	}
	if(nChar==VK_RIGHT)
	{
		zprot -= 5/(ABS(Speed)+1);
		Throttle*=.99;
	}

	if (Throttle == 15)
	{
		Afterburner = true;
	}
	else 
	{
		Afterburner = false;
	}

	if(nChar==76||nChar==108)		// ����'L'��	
	{
		water=!water;
	}
	if(nChar==87||nChar==119)		// ����'W'��
	{
		wireframe=!wireframe;  
	}	

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

bool CTerrain3DTestView::InitTerrain(GLvoid)
{
	int i,i2;     
    
	field[0][0].y=(GLfloat(rand()%100)-50)/3;

	// ���ɵ�������
	for (i = 0; i < MAX; i++)
	{  
		for (i2 = 0; i2 < MAX; i2++)
		{

			if (i<10 || i2<10 || i>MAX-10 || i2>MAX-10)
				field[i][i2].y=0;   
			else
				field[i][i2].y=(GLfloat(rand()%151)-75)/50+(field[i-1][i2-1].y+field[i-1][i2].y+field[i-1][i2+1].y+field[i-1][i2-2].y+field[i-1][i2+2].y)/5.05; //Calculate the y coordinate on the same principle. 				
		}
	}
	// ���ι⻬����
   for (int cnt = 0; cnt < 3; cnt++)
   {
	   for (int t = 1; t < MAX-1; t++)
	   {
		   for (int t2 = 1; t2 < MAX-1; t2++)
		   {
			   field[t][t2].y = (field[t+1][t2].y+field[t][t2-1].y+field[t-1][t2].y+field[t][t2+1].y)/4;           
			   if (cnt == 0)
			   {
				   if (field[t][t2].y < -1 && field[t][t2].y > -1-.5) 
					   field[t][t2].y -= .45, field[t][t2].y *= 2;
				   else if (field[t][t2].y > -1 && field[t][t2].y < -1+.5) 
					   field[t][t2].y += .5, field[t][t2].y /= 5;
			   }
		   }
	   }
   }
   return true;
}

bool CTerrain3DTestView::InitSmoke(GLvoid)
{
	// ����ϵͳ�ĳ�ʼ��
	for (loop=0;loop<MAX_PARTICLES;loop++)				
	{
		particle[loop].active=true;					// ʹ���е����Ӽ���
		particle[loop].life=1.0f;					// �����µ�����
		particle[loop].fade=GLfloat(rand()%100)/7500 + 0.0075f;	// ���������ֵ
		if (loop < MAX_PARTICLES/2) 
			particle[loop].x= .75f;
		else
			particle[loop].x= -.75f;
		particle[loop].y= -.15;						// Center On Y Axis
		particle[loop].z= 3;						// Center On Z Axis
		V = (GLfloat((rand()%5))+2)/5;
		Angle = GLfloat(rand()%360);
		particle[loop].zg = .15;
		particle[loop].xi = sin(Angle) * V;
		particle[loop].yi = cos(Angle) * V;
		particle[loop].zi = ((rand()%10)-5)/5;
	}
	return true;
}

bool CTerrain3DTestView::DrawWireframe(GLvoid)
{
	int i;    
	int i2;    
	int t, t2;
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	for (t = xrange1; t < xrange2; t+=quality)
	{
		for (t2 = zrange1; t2 < zrange2; t2+=quality)
  		{
			i = t;
			i2 = t2;
            
			while (i < 0) i += MAX;             
			while (i > MAX) i -= MAX;            
			while (i2 < 0) i2 += MAX;             
			while (i2 > MAX) i2 -= MAX;
			int coord=t-MAX;
			int coord2=t2-MAX;

			glBegin(GL_LINE_LOOP);
			glVertex3f(coord,field[i][i2].y,coord2);        
			glVertex3f(coord+quality,field[i+quality][i2].y,coord2);
			glVertex3f(coord+quality,field[i+quality][i2+quality].y,coord2+quality);
			glVertex3f(coord,field[i][i2+quality].y,coord2+quality);
			glVertex3f(coord+quality,field[i+quality][i2].y,coord2);
			glEnd();
		}
	}
	glEnable(GL_TEXTURE_2D);
	  
	glLoadIdentity();
	glTranslatef(0,-.5f,-10);    
	glRotatef(yaw,0,1,0);
	glRotatef(zprot*15,0,0,1);
	glRotatef(pitch,1,0,0);

	glEnable(GL_LIGHTING);
	glCallList(MODEL);		// ���Ʒɻ�ģ��
	glDisable(GL_LIGHTING);

	return true;
}

bool CTerrain3DTestView::DrawTexture(GLvoid)
{
	DrawTerrain();		// ���Ƶ���
	DrawSky();			// �������
	if(water)
	{ 
		DrawWater();	// ����ˮ
	}         
   
	DrawPlane();		// ���Ʒɻ�����β��
	DrawSun();			// ����̫��


// 	using namespace Concurrency;
// 	using namespace std;
// 	parallel_invoke([&]{DrawTerrain();},
// 		[&]{DrawSky();},
// 		[&]{DrawPlane();},
// 		[&]{DrawSun();},
// 		[&]{if(water)
// 			{ 
// 		 		DrawWater();	// ����ˮ
// 			}}
// 		);
	return true;
}

bool CTerrain3DTestView::DrawWater(GLvoid)
{
	glEnable(GL_BLEND);
  	glLoadIdentity();
	glTranslatef(0,0,-10);
	glRotatef(sceneroty,0,1,0);
	glTranslatef(xtrans,ytrans-3.5-ABS(Speed)/5,ztrans);

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glColor4f(1,1,1,.35f);
	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(xtexa2,ytexa2); glVertex3f(xrange2-MAX,-1,zrange2-MAX);
		glTexCoord2f(xtexa2,ytexa);  glVertex3f(xrange2-MAX,-1,zrange1-MAX); 
		glTexCoord2f(xtexa,ytexa2);  glVertex3f(xrange1-MAX,-1,zrange2-MAX); 
		glTexCoord2f(xtexa,ytexa);   glVertex3f(xrange1-MAX,-1,zrange1-MAX); 
	glEnd();

	glDisable(GL_BLEND);
	return true;
}

bool CTerrain3DTestView::DrawSun(GLvoid)
{
	float sun_flare_size;
	sun_flare_size = 5000;
	glColor4f(1,.5f,0,.5f);
	glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
		glTexCoord2f(1,1); glVertex3f(MAX/2+sun_flare_size,sun_height+sun_flare_size,sun_zdistance); // Top Right
		glTexCoord2f(0,1); glVertex3f(MAX/2-sun_flare_size,sun_height+sun_flare_size,sun_zdistance); // Top Left
		glTexCoord2f(1,0); glVertex3f(MAX/2+sun_flare_size,sun_height-sun_flare_size,sun_zdistance); // Bottom Right
		glTexCoord2f(0,0); glVertex3f(MAX/2-sun_flare_size,sun_height-sun_flare_size,sun_zdistance); // Bottom Left
	glEnd();										// Done Building Triangle Strip
	
	sun_flare_size = 500;
	glColor4f(1,.5f,0,1);
	glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
		glTexCoord2f(1,1); glVertex3f(MAX/2+sun_flare_size,sun_height+sun_flare_size,sun_zdistance); // Top Right
		glTexCoord2f(0,1); glVertex3f(MAX/2-sun_flare_size,sun_height+sun_flare_size,sun_zdistance); // Top Left
		glTexCoord2f(1,0); glVertex3f(MAX/2+sun_flare_size,sun_height-sun_flare_size,sun_zdistance); // Bottom Right
		glTexCoord2f(0,0); glVertex3f(MAX/2-sun_flare_size,sun_height-sun_flare_size,sun_zdistance); // Bottom Left
	glEnd();										// Done Building Triangle Strip
	return true;

}

bool CTerrain3DTestView::DrawPlane(GLvoid)
{
	glColor4f(1,1,1,1);
	glLoadIdentity();
	glTranslatef(0,-.5f,-10);
     
	glRotatef(yaw,0,1,0);
	glRotatef(zprot*15,0,0,1);
	glRotatef(pitch,1,0,0);

	glEnable(GL_LIGHTING);
	glCallList(MODEL);		// ���Ʒɻ�ģ��
	glDisable(GL_LIGHTING);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindTexture(GL_TEXTURE_2D,texture[5]);

	GLfloat exhaust_r, exhaust_g, exhaust_b;
	if (Afterburner)
	{
		exhaust_r = 1;
		exhaust_g = .5f;
		exhaust_b = 0;
	}
	else
	{
		exhaust_r = .5f;
		exhaust_g = .5f;
		exhaust_b = 1;
	}
	
	glowp += .5f-glow;    
	glow += glowp*(ABS(Throttle)/500);
	if (glow > 1) glow = 1;
	else if (glow < .25f) glow = .25f;
	glColor4f(exhaust_r,exhaust_g,exhaust_b,glow);
	float glowsize = 1;
	for (float glowpos = 3; glowpos <= 3.25f; glowpos+=.25f)
	{
		glowsize -= .175f;
		glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			glTexCoord2f(1,1); glVertex3f(.52+glowsize,-.8f+glowsize,glowpos); // Top Right
			glTexCoord2f(0,1); glVertex3f(.52-glowsize,-.8f+glowsize,glowpos); // Top Left
			glTexCoord2f(1,0); glVertex3f(.52+glowsize,-.8f-glowsize,glowpos); // Bottom Right
			glTexCoord2f(0,0); glVertex3f(.52-glowsize,-.8f-glowsize,glowpos); // Bottom Left
		glEnd();										// Done Building Triangle Strip
		glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			glTexCoord2f(1,1); glVertex3f(-.52+glowsize,-.8f+glowsize,glowpos); // Top Right
			glTexCoord2f(0,1); glVertex3f(-.52-glowsize,-.8f+glowsize,glowpos); // Top Left
			glTexCoord2f(1,0); glVertex3f(-.52+glowsize,-.8f-glowsize,glowpos); // Bottom Right
			glTexCoord2f(0,0); glVertex3f(-.52-glowsize,-.8f-glowsize,glowpos); // Bottom Left
		glEnd();										// Done Building Triangle Strip
	} 
	
	for (loop=0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
	{       	
		GLfloat x=particle[loop].x;						// Grab Our Particle X Position
		GLfloat y=particle[loop].y;						// Grab Our Particle Y Position
		GLfloat z=particle[loop].z;					// Particle Z Pos + Zoom           
		glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life/2);		  	                  
    
		glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			glTexCoord2f(1,1); glVertex3f(x+0.1f,y+0.1f,z); // Top Right
			glTexCoord2f(0,1); glVertex3f(x-0.1f,y+0.1f,z); // Top Left
			glTexCoord2f(1,0); glVertex3f(x+0.1f,y-0.1f,z); // Bottom Right
			glTexCoord2f(0,0); glVertex3f(x-0.1f,y-0.1f,z); // Bottom Left
		glEnd();										// Done Building Triangle Strip
            
		particle[loop].x+=particle[loop].xi/250;// Move On The X Axis By X Speed
		particle[loop].y+=particle[loop].yi/250;// Move On The Y Axis By Y Speed
		particle[loop].z+=particle[loop].zi/250;// Move On The Z Axis By Z Speed
		particle[loop].xi*=.975f;
		particle[loop].yi*=.975f;
		particle[loop].zi*=.975f;
		particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
		particle[loop].life-=particle[loop].fade*3;		// Reduce Particles Life By 'Fade'
		if (particle[loop].life < .5f) 
			particle[loop].life*=.975;

		if (particle[loop].life<0.05f)					// If Particle Is Burned Out
		{ 			    
			particle[loop].r=exhaust_r;
			particle[loop].g=exhaust_g;
			particle[loop].b=exhaust_b;
			
			particle[loop].life=1.0f;					// Give It New Life
			particle[loop].fade=GLfloat(rand()%100)/2500 + 0.02f;	// Random Fade Value
			if (loop < MAX_PARTICLES/2) 
				particle[loop].x= .52f;						
			else  
				particle[loop].x= -.52f;						
			particle[loop].y= -.8f;						
			particle[loop].z= 3.f;						
			V = (GLfloat((rand()%5))+2)/5;
			Angle = GLfloat(rand()%360);
              
			particle[loop].xi = sin(Angle) * V;
			particle[loop].yi = cos(Angle) * V;
			particle[loop].zi = ((rand()%10)-5)/5 + Throttle*4;
		}
	} 
	glDisable(GL_FOG);
	glLoadIdentity();
	glRotatef(sceneroty,0,1,0);

	return true;
}

bool CTerrain3DTestView::DrawTerrain(GLvoid)
{
	int i;    
	int i2;  
	int t, t2;	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glColor4f(1,1,1,1);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	for (t = xrange1; t < xrange2; t+=quality)
	{        
		for (t2 = zrange1; t2 < zrange2; t2+=quality)
		{                                     
			i = t;
			i2 = t2;
            
			while (i < 0) i += MAX;             
			while (i > MAX) i -= MAX;            
			while (i2 < 0) i2 += MAX;             
			while (i2 > MAX) i2 -= MAX;

   			xtexa = (GLfloat(i)/MAX)*57;
			xtexa2 = (GLfloat(i+quality)/MAX)*57;    
			ytexa = (GLfloat(i2)/MAX)*57;
			ytexa2 = (GLfloat(i2+quality)/MAX)*57;       
			int coord=t-MAX;
			int coord2=t2-MAX;
      
			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(xtexa2,ytexa2);  glVertex3f(coord+quality,field[i+quality][i2+quality].y,  coord2+quality);
			glTexCoord2f(xtexa2,ytexa);   glVertex3f(coord+quality,field[i+quality][i2].y,coord2); 
			glTexCoord2f(xtexa,ytexa2);   glVertex3f(coord,field[i][i2+quality].y,coord2+quality); 
			glTexCoord2f(xtexa,ytexa);   glVertex3f(coord,field[i][i2].y,coord2); 
			glEnd();       
		}   
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	// �ڶ��λ��Ƶ���(��������)
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glColor4f(1,1,1,.5f);
	for (t = xrange1; t < xrange2; t+=quality)
	{   
		for (t2 = zrange1; t2 < zrange2; t2+=quality)
		{               
			i = t;
			i2 = t2;
            
			while (i < 0) i += MAX;             
			while (i > MAX) i -= MAX;            
			while (i2 < 0) i2 += MAX;             
			while (i2 > MAX) i2 -= MAX;

			xtexa = (GLfloat(i)/MAX)*1;
			xtexa2 = (GLfloat(i+quality)/MAX)*1;
			ytexa = (GLfloat(i2)/MAX)*1;
			ytexa2 = (GLfloat(i2+quality)/MAX)*1;       
			int coord=t-MAX;
			int coord2=t2-MAX;
            
			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(xtexa2,ytexa2);  glVertex3f(coord+quality,field[i+quality][i2+quality].y,  coord2+quality);
			glTexCoord2f(xtexa2,ytexa);   glVertex3f(coord+quality,field[i+quality][i2].y,coord2); 
			glTexCoord2f(xtexa,ytexa2);   glVertex3f(coord,field[i][i2+quality].y,coord2+quality); 
			glTexCoord2f(xtexa,ytexa);   glVertex3f(coord,field[i][i2].y,coord2); 
			glEnd();            
		}
	}   
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
       
	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);
	return true;
}

bool CTerrain3DTestView::DrawSky(GLvoid)
{
	glFogf(GL_FOG_START, MAX*2);					// ��Ŀ�ʼ���
	glFogf(GL_FOG_END, MAX*15);						// ��Ľ������
	glColor4f(1,1,1,1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslatef(-xtrans,-ytrans-MAX*48,-ztrans);
	glRotatef(90,1,0,1);
	gluSphere(quadratic,MAX*50,20,20);
	glFogf(GL_FOG_START, 10.0f);					// ��Ŀ�ʼ���
	glFogf(GL_FOG_END, visual_distance);			// ��Ľ������
	return true;
}

void CTerrain3DTestView::Caculate(GLvoid)
{
	zprot*=0.935f;
	heading += zprot/3;
	yaw += zprot/5;
	yaw*=.95f; 

	Throttlei += (_Throttle-Throttle)/10;
	Throttlei *= .9f;
	Throttle += Throttlei/10;
				
	GLfloat MAX_Speed = (sqrt(Throttle+1)) * 10; 
	Speedi += MAX_Speed-Speed;
	Speedi *= .9f;
	Speed += Speedi/1000;
	XP = -(GLfloat)sin(heading*piover180) * Speed;	
	YP = -(GLfloat)sin(pitch*piover180) * Speed;
	ZP = -(GLfloat)cos(heading*piover180) * Speed;
    GLfloat overallspeed = Hypot(Hypot(XP,YP),ZP) / (ABS(Speed)+1);  				
				
	YP *= overallspeed;
	XP *= overallspeed;
	ZP *= overallspeed;

	XPOS += XP/30;
	YPOS += YP/30;
	ZPOS += ZP/30;
}