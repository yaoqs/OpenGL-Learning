// MyPick1View.cpp : implementation of the CMyPick1View class
//

#include "stdafx.h"
#include "MyPick1.h"

#include "MyPick1Doc.h"
#include "MyPick1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPick1View

IMPLEMENT_DYNCREATE(CMyPick1View, CView)

BEGIN_MESSAGE_MAP(CMyPick1View, CView)
	//{{AFX_MSG_MAP(CMyPick1View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPick1View construction/destruction

CMyPick1View::CMyPick1View()
{
	// TODO: add construction code here
	model_pick = 0;
	bug1_scaling=1, bug2_scaling=1, bug3_scaling=1;

}

CMyPick1View::~CMyPick1View()
{
}

BOOL CMyPick1View::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyPick1View drawing

void CMyPick1View::OnDraw(CDC* pDC)
{
	CMyPick1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyPick1View printing

BOOL CMyPick1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyPick1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyPick1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyPick1View diagnostics

#ifdef _DEBUG
void CMyPick1View::AssertValid() const
{
	CView::AssertValid();
}

void CMyPick1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPick1Doc* CMyPick1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPick1Doc)));
	return (CMyPick1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPick1View message handlers

int CMyPick1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyPick1View::OnDestroy() 
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

void CMyPick1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-7, 7, -5, 5, 10, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	winWidth=cx;
	winHeight=cy;	
}

void CMyPick1View::OnTimer(UINT nIDEvent) 
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
void CMyPick1View::SetLogicalPalette(void)
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
BOOL CMyPick1View::InitializeOpenGL(CDC* pDC)
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
BOOL CMyPick1View::SetupPixelFormat()
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
BOOL CMyPick1View::RenderScene() 
{
	alpha += 1;
	DrawBugs();

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void CMyPick1View::DrawBugs()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// ��ʼ����������
	glInitNames();
	glPushName(0);
	// �����ӵ�
	gluLookAt(0, 30, 200, 0, 20, 0, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	// ����BUG 1
	glPushMatrix();
	glTranslatef(80, 0, 0);
	// ��ת����
	glRotatef(alpha, 0, 0, 1);
	glLoadName(BUG_1);
	if (model_pick == BUG_1)
	{
		// �������ѡ��
		bug1_scaling += 0.1f;
		if (bug1_scaling > 2.0f) bug1_scaling = 2.0f;
	}
	else
	{
		// �������û��ѡ��
		bug1_scaling -= 0.1f;
		if (bug1_scaling < 1.0f) bug1_scaling = 1.0f;
	}
	glScalef(bug1_scaling, bug1_scaling, bug1_scaling);
	bug1.Draw();
	glPopMatrix();
	
	// ���ƶ���BUG 2
	glPushMatrix();
	glRotatef(alpha, 0, 0, 1);
	glLoadName(BUG_2);
	if (model_pick == BUG_2)
	{
		bug2_scaling += 0.1f;
		if (bug2_scaling > 2.0f) bug2_scaling = 2.0f;
	}
	else
	{
		bug2_scaling -= 0.1f;
		if (bug2_scaling < 1.0f) bug2_scaling = 1.0f;
	}
	glScalef(bug2_scaling, bug2_scaling, bug2_scaling);
	bug2.Draw();
	glPopMatrix();
	
	// ���ƶ���BUG 3
	glPushMatrix();
	glTranslatef(-80, 0, 0);
	glRotatef(alpha, 0, 0, 1);
	glLoadName(BUG_3);
	if (model_pick == BUG_3)
	{
		bug3_scaling += 0.1f;
		if (bug3_scaling > 2.0f) bug3_scaling = 2.0f;
	}
	else
	{
		bug3_scaling -= 0.1f;
		if (bug3_scaling < 1.0f) bug3_scaling = 1.0f;
	}
	glScalef(bug3_scaling, bug3_scaling, bug3_scaling);
	bug3.Draw();
	glPopMatrix();

	glFlush();
}

void CMyPick1View::Init()
{
	// ��Դ����
	GLfloat light_ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat light_specular[] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat light_position[] = {0.0f, 100.0f, 0.0f, 1.0f};
	// ��ʼ���������
	textr.Init();
	// װ�����е�ģ��
	bug1.LoadFromFile("models/bug1.obj", &textr);
	bug2.LoadFromFile("models/bug2.obj", &textr);
	bug3.LoadFromFile("models/bug3.obj", &textr);
	
	glClearColor(0, 0, 0, 1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

void CMyPick1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int mx,my;
	mx = point.x;
    my = point.y;
	if  (mx & 1 << 15) mx -= (1 << 16);
	if  (my & 1 << 15) my -= (1 << 16);
	mouse_proc(mx, my);	
	CView::OnLButtonDown(nFlags, point);
}

void CMyPick1View::mouse_proc(int x, int y)
{
	GLuint selectBuff[64];
	GLint hits, viewport[4];
	// ѡ�񻺳�������
	glSelectBuffer(64, selectBuff);
	glGetIntegerv(GL_VIEWPORT, viewport);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glRenderMode(GL_SELECT);
	glLoadIdentity();
	// ����ʰȡ����
	gluPickMatrix(x, winHeight-y, 2, 2, viewport);
	glFrustum(-7, 7, -5, 5, 10, 300);
	glMatrixMode(GL_MODELVIEW);
	// ���Ƴ���
	DrawBugs();
	hits = glRenderMode(GL_RENDER);
	if(hits > 0) model_pick = selectBuff[3];
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	
}



