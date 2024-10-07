// MyCollision1View.cpp : implementation of the CMyCollision1View class
//

#include "stdafx.h"
#include "MyCollision1.h"

#include "MyCollision1Doc.h"
#include "MyCollision1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

GLfloat spec[]={1.0, 1.0 ,1.0 ,1.0};      // ������ľ���߹�
GLfloat posl[]={0,400,0,1};               // ��Դ��λ��
GLfloat amb[]={0.2f, 0.2f, 0.2f ,1.0f};   // ȫ�ֻ�����
GLfloat amb2[]={0.3f, 0.3f, 0.3f ,1.0f};  // ��Դ�Ļ�����

CVector dir(0,0,-10);                     // ��������������
CVector pos(0,-50,1000);                  // ����������λ��
float camera_rotation=0;                  // Χ�� Y ����ת

CVector veloc(0.5,-0.1,0.5);              // �������˶��ٶ�
CVector accel(0,-0.05,0);                 // ��ļ��ٶ�

CVector ArrayVel[10];                     // ��������ٶ�
CVector ArrayPos[10];                     // ���λ��
CVector OldPos[10];                       // �����λ��
int NrOfBalls;                            // �����������
double Time=0.6;                          // �����ʱ�䲽��
int hook_toball1=0, sounds=1;             


/////////////////////////////////////////////////////////////////////////////
// CMyCollision1View

IMPLEMENT_DYNCREATE(CMyCollision1View, CView)

BEGIN_MESSAGE_MAP(CMyCollision1View, CView)
	//{{AFX_MSG_MAP(CMyCollision1View)
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
// CMyCollision1View construction/destruction

CMyCollision1View::CMyCollision1View()
{
	// TODO: add construction code here

}

CMyCollision1View::~CMyCollision1View()
{
}

BOOL CMyCollision1View::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyCollision1View drawing

void CMyCollision1View::OnDraw(CDC* pDC)
{
	CMyCollision1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyCollision1View printing

BOOL CMyCollision1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyCollision1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyCollision1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyCollision1View diagnostics

#ifdef _DEBUG
void CMyCollision1View::AssertValid() const
{
	CView::AssertValid();
}

void CMyCollision1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCollision1Doc* CMyCollision1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCollision1Doc)));
	return (CMyCollision1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCollision1View message handlers

int CMyCollision1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	InitVars();
	Init();
	
	return 0;
}

void CMyCollision1View::OnDestroy() 
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

void CMyCollision1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();	
	gluPerspective(50.0f,(GLfloat)cx/(GLfloat)cy,10.f,1700.0f);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();		
	
}

void CMyCollision1View::OnTimer(UINT nIDEvent) 
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
void CMyCollision1View::SetLogicalPalette(void)
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
BOOL CMyCollision1View::InitializeOpenGL(CDC* pDC)
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
BOOL CMyCollision1View::SetupPixelFormat()
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
BOOL CMyCollision1View::RenderScene() 
{
	idle();
	int i;
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	if (hook_toball1)
	{
		CVector unit_followvector=ArrayVel[0];
		unit_followvector.unit();
 		gluLookAt(ArrayPos[0].X()+250,ArrayPos[0].Y()+250 ,ArrayPos[0].Z(), ArrayPos[0].X()+ArrayVel[0].X() ,ArrayPos[0].Y()+ArrayVel[0].Y() ,ArrayPos[0].Z()+ArrayVel[0].Z() ,0,1,0);  
    
    }
	else
	    gluLookAt(pos.X(),pos.Y(),pos.Z(), pos.X()+dir.X(),pos.Y()+dir.Y(),pos.Z()+dir.Z(), 0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glRotatef(camera_rotation,0,1,0);
	// ������
	for (i=0;i<NrOfBalls;i++)
	{
		switch(i){
        case 1: glColor3f(1.0f,1.0f,1.0f);
			       break;
		case 2: glColor3f(1.0f,1.0f,0.0f);
			       break;
		case 3: glColor3f(0.0f,1.0f,1.0f);
			       break;
		case 4: glColor3f(0.0f,1.0f,0.0f);
			       break;
		case 5: glColor3f(0.0f,0.0f,1.0f);
			       break;
		case 6: glColor3f(0.65f,0.2f,0.3f);
			       break;
		case 7: glColor3f(1.0f,0.0f,1.0f);
			       break;
		case 8: glColor3f(0.0f,0.7f,0.4f);
			       break;
		default: glColor3f(1.0f,0,0);
		}
		glPushMatrix();
		glTranslated(ArrayPos[i].X(),ArrayPos[i].Y(),ArrayPos[i].Z());
		gluSphere(cylinder_obj,20,20,20);
		glPopMatrix();
	}
	glEnable(GL_TEXTURE_2D);
	// ���ƴ������ǽ��
	glBindTexture(GL_TEXTURE_2D, texture[3]); 
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(320,320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,320,320);
        
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,320,-320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-320,-320,-320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(320,320,-320);
    
	glTexCoord2f(1.0f, 0.0f); glVertex3f(320,320,-320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,-320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(320,320,320);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,320,-320);
	glEnd();
	// ��������ɫ�ĵ���
	glBindTexture(GL_TEXTURE_2D, texture[2]); 
    glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,-320,-320);
	glEnd();
    // ����Բ����
	glBindTexture(GL_TEXTURE_2D, texture[0]);   
	glColor3f(0.5,0.5,0.5);
    glPushMatrix();
	glRotatef(90, 1,0,0);
	glTranslatef(0,0,-500);
	gluCylinder(cylinder_obj, 60, 60, 1000, 20, 2);
	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(200,-300,-500);
	gluCylinder(cylinder_obj, 60, 60, 1000, 20, 2);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(-200,0,0);
	glRotatef(135, 1,0,0);
	glTranslatef(0,0,-500);
	gluCylinder(cylinder_obj, 30, 30, 1000, 20, 2);
	glPopMatrix();
	
	// ���Ʊ�ըЧ��
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
    glBindTexture(GL_TEXTURE_2D, texture[1]);   
	for(i=0; i<20; i++)
	{
		if(ExplosionArray[i]._Alpha>=0)
		{
		   glPushMatrix();
           ExplosionArray[i]._Alpha-=0.01f;
		   ExplosionArray[i]._Scale+=0.03f;
		   glColor4f(1,1,0,ExplosionArray[i]._Alpha);	 
		   glScalef(ExplosionArray[i]._Scale,ExplosionArray[i]._Scale,ExplosionArray[i]._Scale);
           glTranslatef((float)ExplosionArray[i]._Position.X()/ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Y()/ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Z()/ExplosionArray[i]._Scale);
           glCallList(dlist);
	       glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

int CMyCollision1View::Init(GLvoid)										
{
   	float df=100.0;

	glClearDepth(1.0f);								
	glEnable(GL_DEPTH_TEST);						
	glDepthFunc(GL_LEQUAL);							
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	glClearColor(0,0,0,0);
  	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT,GL_SHININESS,&df);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_POSITION,posl);
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb2);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
   
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   	
	glEnable(GL_TEXTURE_2D);
    LoadGLTextures();

    glNewList(dlist=glGenLists(1), GL_COMPILE);
    glBegin(GL_QUADS);
	glRotatef(-45,0,1,0);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50,-40,0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50,-40,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50,40,0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50,40,0);
    glNormal3f(0,0,-1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50,40,0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50,40,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50,-40,0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50,-40,0);

	glNormal3f(1,0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,-40,50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,-40,-50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,40,-50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,40,50);
    glNormal3f(-1,0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,40,50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,40,-50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,-40,-50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,-40,50);
	glEnd();
    glEndList();

	return TRUE;	
}

// ������֮���Ƿ��໥��ײ
int CMyCollision1View::FindBallCol(CVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2)
{
	CVector RelativeV;
	CTray rays;
	double MyTime=0.0, Add=Time2/150.0, Timedummy=10000, Timedummy2=-1;
	CVector posi;
	// �������е����Ƿ��໥��ײ
	for (int i=0;i<NrOfBalls-1;i++)
	{
		for (int j=i+1;j<NrOfBalls;j++)
		{	
		    RelativeV=ArrayVel[i]-ArrayVel[j];
			rays=CTray(OldPos[i],CVector::unit(RelativeV));
			MyTime=0.0;
			if ( (rays.dist(OldPos[j])) > 40) continue; 
			while (MyTime<Time2)
			{
				MyTime+=Add;
				posi=OldPos[i]+RelativeV*MyTime;
				if (posi.dist(OldPos[j])<=40) 
				{
					point=posi;
					if (Timedummy>(MyTime-Add)) Timedummy=MyTime-Add;
					BallNr1=i;
					BallNr2=j;
					break;
				}
			}
		}
	}
	if (Timedummy!=10000) 
	{ 
		TimePoint=Timedummy;
		return 1;
	}
	return 0;
}

// ������,��ǰ�������˶����е���,�����ײ����
void CMyCollision1View::idle()
{
	double rt,rt2,rt4,lamda=10000;
	CVector norm,uveloc;
	CVector normal,point,time;
	double RestTime,BallTime;
	CVector Pos2;
	int BallNr=0,dummy=0,BallColNr1,BallColNr2;
	CVector Nc;
	if (!hook_toball1)
	{
		camera_rotation+=0.1f;
		if (camera_rotation>360)
			camera_rotation=0;
	}
	RestTime=Time;
	lamda=1000;
	// ʹ��Euler���̼�����һ�����ٶ�
	for (int j=0;j<NrOfBalls;j++)
		ArrayVel[j]+=accel*RestTime;
	// ��ʱ��û�н���
	while (RestTime>ZERO)
	{
		lamda=10000;
		// �����е���������ƽ��/Բ����֮���ҵ�������ཻ��
		for (int i=0;i<NrOfBalls;i++)
		{
			// �����µ�λ�ú;���
			OldPos[i]=ArrayPos[i];
			CVector::unit(ArrayVel[i],uveloc);
			ArrayPos[i]=ArrayPos[i]+ArrayVel[i]*RestTime;
			rt2=OldPos[i].dist(ArrayPos[i]);
			// ����������5��ƽ��֮���Ƿ�����ײ
			if (TestIntersionPlane(pl1,OldPos[i],uveloc,rt,norm))
			{
				// �����ཻʱ��
				rt4=rt*RestTime/rt2;
				if (rt4<=lamda)
				{
					if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						{
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						}
				}
			}
			if (TestIntersionPlane(pl2,OldPos[i],uveloc,rt,norm))
			{
				rt4=rt*RestTime/rt2;
				if (rt4<=lamda)
				{
					if (rt4<=RestTime+ZERO)
						if(! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						{
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
							dummy=1;
						 }
				  }
				 
			  }

			  if (TestIntersionPlane(pl3,OldPos[i],uveloc,rt,norm))
			  {
			      rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

			  if (TestIntersionPlane(pl4,OldPos[i],uveloc,rt,norm))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

			  if (TestIntersionPlane(pl5,OldPos[i],uveloc,rt,norm))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
						 }
				  }
			  }

              // ��������3��Բ�����Ƿ�����ײ
			  if (TestIntersionCylinder(cyl1,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
			  if (TestIntersionCylinder(cyl2,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
			  if (TestIntersionCylinder(cyl3,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=Nc;
							lamda=rt4;
							BallNr=i;
						 }
				  }
				 
			  }
	   }

	   // �����֮���Ƿ�����ײ
	   if (FindBallCol(Pos2,BallTime,RestTime,BallColNr1,BallColNr2))
			  {
				  if (sounds)
					  PlaySound("Data/Explode.wav",NULL,SND_FILENAME|SND_ASYNC);
			      
				  if ( (lamda==10000) || (lamda>BallTime) )
				  {
					  RestTime=RestTime-BallTime;

					  CVector pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
					  double a,b;

					  pb1=OldPos[BallColNr1]+ArrayVel[BallColNr1]*BallTime;
					  pb2=OldPos[BallColNr2]+ArrayVel[BallColNr2]*BallTime;
					  xaxis=(pb2-pb1).unit();

					  a=xaxis.dot(ArrayVel[BallColNr1]);
					  U1x=xaxis*a;
					  U1y=ArrayVel[BallColNr1]-U1x;

					  xaxis=(pb1-pb2).unit();
					  b=xaxis.dot(ArrayVel[BallColNr2]);
      				  U2x=xaxis*b;
					  U2y=ArrayVel[BallColNr2]-U2x;

					  V1x=(U1x+U2x-(U1x-U2x))*0.5;
					  V2x=(U1x+U2x-(U2x-U1x))*0.5;
					  V1y=U1y;
					  V2y=U2y;

					  for (j=0;j<NrOfBalls;j++)
					  ArrayPos[j]=OldPos[j]+ArrayVel[j]*BallTime;

					  ArrayVel[BallColNr1]=V1x+V1y;
					  ArrayVel[BallColNr2]=V2x+V2y;

					  // ���±�ը����
                      for(j=0;j<20;j++)
					  {
						  if (ExplosionArray[j]._Alpha<=0)
						  {
							  ExplosionArray[j]._Alpha=1;
                              ExplosionArray[j]._Position=ArrayPos[BallColNr1];
							  ExplosionArray[j]._Scale=1;
							  break;
						  }
					  }

					  continue;
				  }
			  }
 
			if (lamda!=10000)
			{		 
				      RestTime-=lamda;

					  for (j=0;j<NrOfBalls;j++)
					  ArrayPos[j]=OldPos[j]+ArrayVel[j]*lamda;

					  rt2=ArrayVel[BallNr].mag();
					  ArrayVel[BallNr].unit();
					  ArrayVel[BallNr]=CVector::unit( (normal*(2*normal.dot(-ArrayVel[BallNr]))) + ArrayVel[BallNr] );
					  ArrayVel[BallNr]=ArrayVel[BallNr]*rt2;
							
					  for(j=0;j<20;j++)
					  {
						  if (ExplosionArray[j]._Alpha<=0)
						  {
							  ExplosionArray[j]._Alpha=1;
                              ExplosionArray[j]._Position=point;
							  ExplosionArray[j]._Scale=1;
							  break;
						  }
					  }
			}
			else RestTime=0;

	}

}

// ��ʼ�����ֱ���
void CMyCollision1View::InitVars()
{
	 //create palnes
	pl1._Position=CVector(0,-300,0);
	pl1._Normal=CVector(0,1,0);
	pl2._Position=CVector(300,0,0);
	pl2._Normal=CVector(-1,0,0);
	pl3._Position=CVector(-300,0,0);
	pl3._Normal=CVector(1,0,0);
	pl4._Position=CVector(0,0,300);
	pl4._Normal=CVector(0,0,-1);
	pl5._Position=CVector(0,0,-300);
	pl5._Normal=CVector(0,0,1);
	// ����Բ����
	cyl1._Position=CVector(0,0,0);
	cyl1._Axis=CVector(0,1,0);
	cyl1._Radius=60+20;
	cyl2._Position=CVector(200,-300,0);
	cyl2._Axis=CVector(0,0,1);
	cyl2._Radius=60+20;
	cyl3._Position=CVector(-200,0,0);
	cyl3._Axis=CVector(0,1,1);
    cyl3._Axis.unit();
	cyl3._Radius=30+20;
	cylinder_obj= gluNewQuadric();
	gluQuadricTexture(cylinder_obj, GL_TRUE);
    // ����������λ�ú��˶��ٶ�
	NrOfBalls=10;
	ArrayVel[0]=veloc;
	ArrayPos[0]=CVector(199,180,10);
	ExplosionArray[0]._Alpha=0;
	ExplosionArray[0]._Scale=1;
	ArrayVel[1]=veloc;
	ArrayPos[1]=CVector(0,150,100);
	ExplosionArray[1]._Alpha=0;
	ExplosionArray[1]._Scale=1;
	ArrayVel[2]=veloc;
	ArrayPos[2]=CVector(-100,180,-100);
	ExplosionArray[2]._Alpha=0;
	ExplosionArray[2]._Scale=1;
	for (int i=3; i<10; i++)
	{
         ArrayVel[i]=veloc;
	     ArrayPos[i]=CVector(-500+i*75, 300, -500+i*50);
		 ExplosionArray[i]._Alpha=0;
	     ExplosionArray[i]._Scale=1;
	}
	for (i=10; i<20; i++)
	{
         ExplosionArray[i]._Alpha=0;
	     ExplosionArray[i]._Scale=1;
	}
}

// ����ֱ���Ƿ���ƽ���ཻ���� 
int CMyCollision1View::TestIntersionPlane(const Plane& plane,const CVector& position,const CVector& direction, double& lamda, CVector& pNormal)
{
    double DotProduct=direction.dot(plane._Normal);
	double l2;
    // ���ֱ���Ƿ���ƽ��ƽ��
    if ((DotProduct<ZERO)&&(DotProduct>-ZERO)) 
		return 0;

    l2=(plane._Normal.dot(plane._Position-position))/DotProduct;

    if (l2<-ZERO) 
		return 0;

    pNormal=plane._Normal;
	lamda=l2;
    return 1;

}

// ����ֱ���Ƿ���Բ�����ཻ
int CMyCollision1View::TestIntersionCylinder(const Cylinder& cylinder,const CVector& position,const CVector& direction, double& lamda, CVector& pNormal,CVector& newposition)
{
	CVector RC;
	double d;
	double t,s;
	CVector n,D,O;
	double ln;
	double in,out;

	CVector::subtract(position,cylinder._Position,RC);
	CVector::cross(direction,cylinder._Axis,n);

    ln=n.mag();

	if ( (ln<ZERO)&&(ln>-ZERO) ) return 0;

	n.unit();

	d= fabs( RC.dot(n) );

    if (d<=cylinder._Radius)
	{
		CVector::cross(RC,cylinder._Axis,O);
		t= - O.dot(n)/ln;
		CVector::cross(n,cylinder._Axis,O);
		O.unit();
		s= fabs( sqrt(cylinder._Radius*cylinder._Radius - d*d) / direction.dot(O) );

		in=t-s;
		out=t+s;

		if (in<-ZERO){
			if (out<-ZERO) return 0;
			else lamda=out;
		}
		else
        if (out<-ZERO) {
			      lamda=in;
		}
		else
		if (in<out) lamda=in;
		else lamda=out;

    	newposition=position+direction*lamda;
		CVector HB=newposition-cylinder._Position;
		pNormal=HB - cylinder._Axis*(HB.dot(cylinder._Axis));
		pNormal.unit();

		return 1;
	}
    
	return 0;
}

void CMyCollision1View::LoadGLTextures() 
{	
    // װ������
    Image *image1, *image2, *image3, *image4;
    // Ϊ�������洢�ռ�
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }
	image2 = (Image *) malloc(sizeof(Image));
    if (image2 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }
	image3 = (Image *) malloc(sizeof(Image));
    if (image3 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }
	image4 = (Image *) malloc(sizeof(Image));
    if (image4 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    if (!m_MyImage.ImageLoad("data/marble.bmp", image1)) {
	exit(1);
    } 
	if (!m_MyImage.ImageLoad("data/spark.bmp", image2)) {
	exit(1);
    }
	if (!m_MyImage.ImageLoad("data/boden.bmp", image3)) {
	exit(1);
    } 
	if (!m_MyImage.ImageLoad("data/wand.bmp", image4)) {
	exit(1);
    }
    // ��������
    glGenTextures(2, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

    glBindTexture(GL_TEXTURE_2D, texture[1]);   

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);

    glGenTextures(2, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);   

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->data);

    glBindTexture(GL_TEXTURE_2D, texture[3]);   

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->data);

	free(image1->data);
	free(image1);
	free(image2->data);
	free(image2);
	free(image3->data);
	free(image3);
	free(image4->data);
	free(image4);

};

