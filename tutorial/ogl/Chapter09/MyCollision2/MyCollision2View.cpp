// MyCollision2View.cpp : implementation of the CMyCollision2View class
//

#include "stdafx.h"
#include "MyCollision2.h"

#include "MyCollision2Doc.h"
#include "MyCollision2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2View

IMPLEMENT_DYNCREATE(CMyCollision2View, CView)

BEGIN_MESSAGE_MAP(CMyCollision2View, CView)
	//{{AFX_MSG_MAP(CMyCollision2View)
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
// CMyCollision2View construction/destruction

CMyCollision2View::CMyCollision2View()
{
	// TODO: add construction code here
	g_fSphere_radius = 0.5f;
	bDistanceCheck = false;
	q=NULL;
	g_vSpherePos = vec3(0,0,0);
	g_vVelocity = vec3(0,0,0.1f);
}

CMyCollision2View::~CMyCollision2View()
{
}

BOOL CMyCollision2View::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyCollision2View drawing

void CMyCollision2View::OnDraw(CDC* pDC)
{
	CMyCollision2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2View printing

BOOL CMyCollision2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyCollision2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyCollision2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2View diagnostics

#ifdef _DEBUG
void CMyCollision2View::AssertValid() const
{
	CView::AssertValid();
}

void CMyCollision2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCollision2Doc* CMyCollision2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCollision2Doc)));
	return (CMyCollision2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2View message handlers

int CMyCollision2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyCollision2View::OnDestroy() 
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

void CMyCollision2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)cx / cy,1,999);		
}

void CMyCollision2View::OnTimer(UINT nIDEvent) 
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
void CMyCollision2View::SetLogicalPalette(void)
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
BOOL CMyCollision2View::InitializeOpenGL(CDC* pDC)
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
BOOL CMyCollision2View::SetupPixelFormat()
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
BOOL CMyCollision2View::RenderScene() 
{
	int i=0;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	// �ƶ������
	glTranslatef(-5.0f,0.0f,-25.0f);
	glRotatef(-45,0.0f,1.0f,0.0f);
	// ���������ı��δ�������ƽ��
	glBegin(GL_QUADS);
	for (;i<2;i++)
	{
		int v=0;	
		glColor3fv((const float*)&g_sQuads[i].sColor);
		for (v=0;v<4;v++)
			glVertex3f(
				g_sQuads[i].vVertices[v].x,
				g_sQuads[i].vVertices[v].y,
				g_sQuads[i].vVertices[v].z
			);
	}
	glEnd();
	// ����4����	
	glBegin(GL_LINES);
	for (i=0;i<4;i++)
	{
		glColor3f(1,1,1);
		glVertex3f(
			g_sQuads[0].vVertices[i].x,
			g_sQuads[0].vVertices[i].y,
			g_sQuads[0].vVertices[i].z);

		glVertex3f(
			g_sQuads[1].vVertices[i].x,
			g_sQuads[1].vVertices[i].y,
			g_sQuads[1].vVertices[i].z);
	}
	// ����z����
	glVertex3f(0.0f,0.0f,-5.0f); glVertex3f(0.0f,0.0f,5.0f);
	glEnd();
	// ��������
	glTranslatef(g_vSpherePos.x,g_vSpherePos.y,g_vSpherePos.z);
	gluSphere(q,g_fSphere_radius,32,32);
	//  ������ײ���
	CollisionCheck();
	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void CMyCollision2View::Init(GLvoid)
{
	g_sQuads[0].vVertices[0] = vec3( -2.0 ,  2.0 , -5.0f);
	g_sQuads[0].vVertices[1] = vec3(  2.0 ,  2.0 , -5.0f);
	g_sQuads[0].vVertices[2] = vec3(  2.0 , -2.0 , -5.0f);
	g_sQuads[0].vVertices[3] = vec3( -2.0 , -2.0 , -5.0f);
	g_sQuads[0].vNormal = vec3(0,0,1);
	g_sQuads[0].D = g_sQuads[0].vVertices[0].DotProduct(g_sQuads[0].vNormal); // (*)
	g_sQuads[0].sColor.r = 1.0f;
	g_sQuads[0].sColor.g = 0.0f;
	g_sQuads[0].sColor.b = 0.0f;
	g_sQuads[1].vVertices[0] = vec3( -2.0 ,  2.0 ,  5.0f);
	g_sQuads[1].vVertices[1] = vec3(  2.0 ,  2.0 ,  5.0f);
	g_sQuads[1].vVertices[2] = vec3(  2.0 , -2.0 ,  5.0f);
	g_sQuads[1].vVertices[3] = vec3( -2.0 , -2.0 ,  5.0f);
	g_sQuads[1].vNormal = vec3(0,0,1);
	g_sQuads[1].D = g_sQuads[1].vVertices[1].DotProduct(g_sQuads[1].vNormal); // (*)
	g_sQuads[1].sColor.r = 0.0f;
	g_sQuads[1].sColor.g = 1.0f;
	g_sQuads[1].sColor.b = 0.0f;
		// ��ʼ��opengl
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	q = gluNewQuadric();
	gluQuadricNormals(q, GLU_SMOOTH);

}

void CMyCollision2View::CollisionCheck(GLvoid)
{
	int i=0;
	bool collision=false;
	vec3 g_vSphereAfter = g_vSpherePos + g_vVelocity;
	// ������ƽ���ڽ�����ײ���
	for (;i<2;i++)
	{
		float D0;
		float D1;
		D0 = g_vSpherePos.DotProduct(g_sQuads[i].vNormal) - g_sQuads[i].D;   // before movement
		D1 = g_vSphereAfter.DotProduct(g_sQuads[i].vNormal) - g_sQuads[i].D; // after movement
		// ������
		if (bDistanceCheck)
		{
			if (abs(D1) < g_fSphere_radius)
			{
				// ��ײ����
				collision=true;
			}
		}		
		if ( (D0 > 0 && D1 < 0) || (D0 < 0 && D1 > 0) )
		{
			collision=true;			
		}
	}

	if (!collision)
	{
		// �ƶ�����
		g_vSpherePos = g_vSphereAfter;
	}
	else
	{
		// �ٶȷ���
		g_vVelocity=-g_vVelocity;
	}	
}