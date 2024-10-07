// MyNeonView.cpp : implementation of the CMyNeonView class
//

#include "stdafx.h"
#include "MyNeon.h"

#include "MyNeonDoc.h"
#include "MyNeonView.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyNeonView

IMPLEMENT_DYNCREATE(CMyNeonView, CView)

BEGIN_MESSAGE_MAP(CMyNeonView, CView)
	//{{AFX_MSG_MAP(CMyNeonView)
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
// CMyNeonView construction/destruction

CMyNeonView::CMyNeonView()
{
	// TODO: add construction code here

}

CMyNeonView::~CMyNeonView()
{
}

BOOL CMyNeonView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyNeonView drawing

void CMyNeonView::OnDraw(CDC* pDC)
{
	CMyNeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyNeonView printing

BOOL CMyNeonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyNeonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyNeonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyNeonView diagnostics

#ifdef _DEBUG
void CMyNeonView::AssertValid() const
{
	CView::AssertValid();
}

void CMyNeonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyNeonDoc* CMyNeonView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyNeonDoc)));
	return (CMyNeonDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyNeonView message handlers

int CMyNeonView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	Init();	
	return 0;
}

void CMyNeonView::OnDestroy() 
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
	glDeleteTextures(1,&BlurTexture);	
}

void CMyNeonView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode (GL_PROJECTION);										
	glLoadIdentity ();												
	gluPerspective(50, (float)cx/(float)cy, 5,  2000);
	glMatrixMode (GL_MODELVIEW);								
	glLoadIdentity ();											
	
}

void CMyNeonView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//��Ӷ�ʱ����Ӧ�����ͳ������º���
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	angle += 4.0;	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  �����߼���ɫ��
//////////////////////////////////////////////////////////////////////
void CMyNeonView::SetLogicalPalette(void)
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
BOOL CMyNeonView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyNeonView::SetupPixelFormat()
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
BOOL CMyNeonView::RenderScene() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();												
	RenderToTexture();			// ��Ⱦ������
	ProcessHelix();				// ������������
	DrawBlur(25,0.02f);			// ����ģ��Ч��
	glFlush ();				

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void CMyNeonView::RenderToTexture()	
{
	glViewport(0,0,128,128);		// �����ӿڱ任(������ߴ��Ӧ)
	ProcessHelix();					// ��Ⱦ��������
	glBindTexture(GL_TEXTURE_2D,BlurTexture);	
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);
	glClearColor(0.0f, 0.0f, 0.5f, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, 640, 480);		// �����ӿڱ任
}

void CMyNeonView::ProcessHelix()	// ������������
{
	GLfloat x;						// ������X����
	GLfloat y;						// ������Y����
	GLfloat z;						// ������Z����
	GLfloat phi;					// �Ƕ�
	GLfloat theta;					// �Ƕ�
	GLfloat v,u;					// �Ƕ�
	GLfloat r;						// �����İ뾶
	int twists = 5;					// 5������

	GLfloat glfMaterialColor[]={0.4f,0.2f,0.8f,1.0f};   // ���ò�����ɫ
	GLfloat specular[]={1.0f,1.0f,1.0f,1.0f};   		// ���ø߹�
	glLoadIdentity();									
	gluLookAt(0, 5, 50, 0, 0, 0, 0, 1, 0);				
	glPushMatrix();										
	glTranslatef(0,0,-50);								
	glRotatef(angle/2.0f,1,0,0);						
	glRotatef(angle/3.0f,0,1,0);						
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,glfMaterialColor);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);

	r=1.5f;												// �뾶

	glBegin(GL_QUADS);									// �����ı���
	for(phi=0; phi <= 360; phi+=20.0)					// ����Ϊ20,�ܳ�360
	{
		for(theta=0; theta<=360*twists; theta+=20.0)	
		{
			v=(phi/180.0f*3.142f);						
			u=(theta/180.0f*3.142f);					

			x=float(cos(u)*(2.0f+cos(v) ))*r;			
			y=float(sin(u)*(2.0f+cos(v) ))*r;			
			z=float((( u-(2.0f*3.142f)) + sin(v) ) * r);

			vertexes[0][0]=x;							
			vertexes[0][1]=y;							
			vertexes[0][2]=z;							

			v=(phi/180.0f*3.142f);		
			u=((theta+20)/180.0f*3.142f);		

			x=float(cos(u)*(2.0f+cos(v) ))*r;
			y=float(sin(u)*(2.0f+cos(v) ))*r;	
			z=float((( u-(2.0f*3.142f)) + sin(v) ) * r);

			vertexes[1][0]=x;									
			vertexes[1][1]=y;									
			vertexes[1][2]=z;									

			v=((phi+20)/180.0f*3.142f);						
			u=((theta+20)/180.0f*3.142f);					

			x=float(cos(u)*(2.0f+cos(v) ))*r;			
			y=float(sin(u)*(2.0f+cos(v) ))*r;			
			z=float((( u-(2.0f*3.142f)) + sin(v) ) * r);

			vertexes[2][0]=x;						
			vertexes[2][1]=y;						
			vertexes[2][2]=z;						

			v=((phi+20)/180.0f*3.142f);				
			u=((theta)/180.0f*3.142f);				

			x=float(cos(u)*(2.0f+cos(v) ))*r;			
			y=float(sin(u)*(2.0f+cos(v) ))*r;			
			z=float((( u-(2.0f*3.142f)) + sin(v) ) * r);

			vertexes[3][0]=x;							
			vertexes[3][1]=y;						
			vertexes[3][2]=z;						

			calcNormal(vertexes,normal);						// �����ı��η���

			glNormal3f(normal[0],normal[1],normal[2]);			// ���÷���

			// ��Ⱦ�ı���
			glVertex3f(vertexes[0][0],vertexes[0][1],vertexes[0][2]);
			glVertex3f(vertexes[1][0],vertexes[1][1],vertexes[1][2]);
			glVertex3f(vertexes[2][0],vertexes[2][1],vertexes[2][2]);
			glVertex3f(vertexes[3][0],vertexes[3][1],vertexes[3][2]);
		}
	}
	glEnd();											
	
	glPopMatrix();									
}

void CMyNeonView::DrawBlur(int times, float inc)	// ����ģ��Ӱ��
{
	float spost = 0.0f;								// ��������ƫ��
	float alphainc = 0.9f / times;					// Alpha��ϵĵ����ٶ�
	float alpha = 0.2f;								// ��ʼAlphaֵ

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glEnable(GL_TEXTURE_2D);				
	glDisable(GL_DEPTH_TEST);			
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);					
	glBindTexture(GL_TEXTURE_2D,BlurTexture);
	ViewOrtho();							

	alphainc = alpha / times;								

	glBegin(GL_QUADS);									
		for (int num = 0;num < times;num++)				
		{
			glColor4f(1.0f, 1.0f, 1.0f, alpha);		
			glTexCoord2f(0+spost,1-spost);			
			glVertex2f(0,0);					

			glTexCoord2f(0+spost,0+spost);		
			glVertex2f(0,480);					

			glTexCoord2f(1-spost,0+spost);		
			glVertex2f(640,480);				

			glTexCoord2f(1-spost,1-spost);	
			glVertex2f(640,0);					

			spost += inc;						
			alpha = alpha - alphainc;			
		}
	glEnd();									

	ViewPerspective();							

	glEnable(GL_DEPTH_TEST);				
	glDisable(GL_TEXTURE_2D);					
	glDisable(GL_BLEND);					
	glBindTexture(GL_TEXTURE_2D,0);				
}

void CMyNeonView::ViewOrtho()						
{
	glMatrixMode(GL_PROJECTION);				
	glPushMatrix();								
	glLoadIdentity();							
	glOrtho( 0, 640 , 480 , 0, -1, 1 );		
	glMatrixMode(GL_MODELVIEW);					
	glPushMatrix();								
	glLoadIdentity();								
}

void CMyNeonView::ViewPerspective()						
{
	glMatrixMode( GL_PROJECTION );					
	glPopMatrix();									
	glMatrixMode( GL_MODELVIEW );				
	glPopMatrix();							
}

GLuint CMyNeonView::EmptyTexture()	// ���ɿ�����
{
	GLuint txtnumber;		
	unsigned int* data;		

	data = (unsigned int*)new GLuint[((128 * 128)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((128 * 128)* 4 * sizeof(unsigned int)));	// ����ڴ�

	glGenTextures(1, &txtnumber);								// ��������
	glBindTexture(GL_TEXTURE_2D, txtnumber);				
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);			
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// �ͷ��ڴ�

	return txtnumber;										
}

void CMyNeonView::ReduceToUnit(float vector[3])		// ʸ����λ��
{													
	float length;								
	// ����ʸ���ĳ���
	length = (float)sqrt((vector[0]*vector[0]) + (vector[1]*vector[1]) + (vector[2]*vector[2]));

	if(length == 0.0f)								
		length = 1.0f;								

	vector[0] /= length;									
	vector[1] /= length;									
	vector[2] /= length;							
}

void CMyNeonView::calcNormal(float v[3][3], float out[3])	
{
	float v1[3],v2[3];									
	static const int x = 0;						
	static const int y = 1;							
	static const int z = 2;						

	v1[x] = v[0][x] - v[1][x];						
	v1[y] = v[0][y] - v[1][y];							
	v1[z] = v[0][z] - v[1][z];							
	v2[x] = v[1][x] - v[2][x];							
	v2[y] = v[1][y] - v[2][y];							
	v2[z] = v[1][z] - v[2][z];							
	out[x] = v1[y]*v2[z] - v1[z]*v2[y];				
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];					
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];				

	ReduceToUnit(out);										
}

BOOL CMyNeonView::Init(void)
{
	angle		= 0.0f;											// ��ʼ�Ƕ�
	BlurTexture = EmptyTexture();								// ���ɿ�����
	glEnable(GL_DEPTH_TEST);									
	GLfloat global_ambient[4]={0.2f, 0.2f,  0.2f, 1.0f};		
	GLfloat light0pos[4]=     {0.0f, 5.0f, 10.0f, 1.0f};		
	GLfloat light0ambient[4]= {0.2f, 0.2f,  0.2f, 1.0f};		
	GLfloat light0diffuse[4]= {0.3f, 0.3f,  0.3f, 1.0f};		
	GLfloat light0specular[4]={0.8f, 0.8f,  0.8f, 1.0f};		
	GLfloat lmodel_ambient[]= {0.2f,0.2f,0.2f,1.0f};			
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);		
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);	
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);			
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0ambient);		
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0diffuse);		
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0specular);		
	glEnable(GL_LIGHTING);								
	glEnable(GL_LIGHT0);								
	glShadeModel(GL_SMOOTH);							
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5);			

	return TRUE;										

}