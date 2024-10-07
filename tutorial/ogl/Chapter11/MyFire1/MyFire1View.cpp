// MyFire1View.cpp : implementation of the CMyFire1View class
//

#include "stdafx.h"
#include "MyFire1.h"

#include "MyFire1Doc.h"
#include "MyFire1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFire1View

IMPLEMENT_DYNCREATE(CMyFire1View, CView)

BEGIN_MESSAGE_MAP(CMyFire1View, CView)
	//{{AFX_MSG_MAP(CMyFire1View)
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
// CMyFire1View construction/destruction

CMyFire1View::CMyFire1View()
{
	// TODO: add construction code here

}

CMyFire1View::~CMyFire1View()
{
}

BOOL CMyFire1View::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyFire1View drawing

void CMyFire1View::OnDraw(CDC* pDC)
{
	CMyFire1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyFire1View printing

BOOL CMyFire1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFire1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFire1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFire1View diagnostics

#ifdef _DEBUG
void CMyFire1View::AssertValid() const
{
	CView::AssertValid();
}

void CMyFire1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFire1Doc* CMyFire1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFire1Doc)));
	return (CMyFire1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFire1View message handlers

int CMyFire1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	InitGL();	
	return 0;
}

void CMyFire1View::OnDestroy() 
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

void CMyFire1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);	// ѡ��ͶӰ����
	glLoadIdentity();				// ����ͶӰ����
	// ���ݴ��ڵı������ñ任
	gluPerspective(45.0f,(GLfloat)cx/(GLfloat)cy,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);		// ѡ��ģ�;���
	glLoadIdentity();				// ����ģ�;���
	
}

void CMyFire1View::OnTimer(UINT nIDEvent) 
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
void CMyFire1View::SetLogicalPalette(void)
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
BOOL CMyFire1View::InitializeOpenGL(CDC* pDC)
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
BOOL CMyFire1View::SetupPixelFormat()
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
BOOL CMyFire1View::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();									
	frame++;
	frame=frame%2;
	if(frame==0)
	{
		if(freeze==false)
		Fuoco();	// ���ɻ���
	}
	glTranslatef(0.1f,0.0f,-2.7f);
	ShowFire(0,0,0,(float)0.1);		// ��ʾ����

	::SwapBuffers(m_pDC->GetSafeHdc());		// ����������
	return TRUE;
}

COL CMyFire1View::Colore(float k)
{
	COL c;
	if( k<64 )
	{
		c.r=k/64;
		c.g=0;
		c.b=0;
	}
	else
	{
		if(k<128)
		{
			c.r=1;
			c.g=k/128;
			c.b=0;
		}
		else
		{
			if(k<192)
			{
				c.r=1;
				c.g=1;
				c.b=k/192;
			}
			else
			{
				c.r=1;
				c.g=1;
				c.b=1;
			}
		}
	}
	return(c);
}

void CMyFire1View::ShowFire(float x,float y,float z,float dim)
{
	float xi,yi;
	float ka,kb,kc,kd;
	COL col;
	int xd,yd;

	yi=y+dim*FIREY/2;

	for(yd=0;yd<FIREY-1;yd++)
	{
		xi=x-dim*FIREX/2;
		for(xd=1;xd<FIREX-1;xd++)
		{
			ka=(float)Bfire[xd][yd];
			kb=(float)Bfire[xd+1][yd];
			kc=(float)Bfire[xd+1][yd+1];
			kd=(float)Bfire[xd][yd+1];

			glBegin(GL_QUADS);		// �����ı���
				col=Colore(kd);
				glColor3f(col.r,col.g,col.b);
				glVertex3f(xi,yi,z);
				col=Colore(kc);
				glColor3f(col.r,col.g,col.b);
				glVertex3f(xi+dim,yi,z);
				col=Colore(kb);
				glColor3f(col.r,col.g,col.b);
				glVertex3f(xi+dim,yi+dim,z);
				col=Colore(ka);
				glColor3f(col.r,col.g,col.b);
				glVertex3f(xi,yi+dim,z);
			glEnd();			
			xi+=dim;
		}
		yi-=dim;
	}
}

void CMyFire1View::Fuoco(void)
{
	int x,y;
	int k;

	for(x=8;x<FIREX-8;x++)
		Bfire[x][FIREY-1]=rand()%192;

	for(x=0;x<5;x++)
		Bfire[rand()%FIREX][FIREY-1]=0;

	for(y=0;y<FIREY-1;y++)
	{
		for(x=1;x<FIREX-1;x++)
		{
			k=Bfire[x][y]+Bfire[x-1][y+1]+Bfire[x+1][y+1]+Bfire[x][y+1];
			k=k/4-2;
			if(k<0)
				k=0;
			Bfire[x][y]=(unsigned char)k;
		}
	}
}

int CMyFire1View::InitGL(GLvoid)										
{
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	for(int y=0;y<FIREY;y++)
	{
		for(int x=0;x<FIREX;x++)
			Bfire[x][y]=0;
	}

	freeze=false;
	frame=0;
	return TRUE;										
}