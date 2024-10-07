// MyPick2View.cpp : implementation of the CMyPick2View class
//

#include "stdafx.h"
#include "MyPick2.h"

#include "MyPick2Doc.h"
#include "MyPick2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)
#define BUFFER_LENGTH 64
#define EARTH	1
#define MARS	2
#define MOON1	3
#define MOON2	4

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View

IMPLEMENT_DYNCREATE(CMyPick2View, CView)

BEGIN_MESSAGE_MAP(CMyPick2View, CView)
	//{{AFX_MSG_MAP(CMyPick2View)
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
// CMyPick2View construction/destruction

CMyPick2View::CMyPick2View()
{
	// TODO: add construction code here

}

CMyPick2View::~CMyPick2View()
{
}

BOOL CMyPick2View::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyPick2View drawing

void CMyPick2View::OnDraw(CDC* pDC)
{
	CMyPick2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View printing

BOOL CMyPick2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyPick2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyPick2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View diagnostics

#ifdef _DEBUG
void CMyPick2View::AssertValid() const
{
	CView::AssertValid();
}

void CMyPick2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPick2Doc* CMyPick2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPick2Doc)));
	return (CMyPick2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPick2View message handlers

int CMyPick2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyPick2View::OnDestroy() 
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

void CMyPick2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	fAspect = (GLfloat)cx/(GLfloat)cy;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, 1.0, 425.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void CMyPick2View::OnTimer(UINT nIDEvent) 
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
void CMyPick2View::SetLogicalPalette(void)
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
BOOL CMyPick2View::InitializeOpenGL(CDC* pDC)
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
BOOL CMyPick2View::SetupPixelFormat()
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
BOOL CMyPick2View::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -300.0f);	
	// ��ʼ�����ƶ�ջ
	glInitNames();
	glPushName(0);
	// ����Earth
	glPushMatrix();
	glRGB(0,0,255);
	glTranslatef(-100.0f,0.0f,0.0f);
	glLoadName(EARTH);
	auxSolidSphere(30.0f);
	// ����Moon
	glTranslatef(45.0f, 0.0f, 0.0f);
	glRGB(220,220,220);
	glPushName(MOON1);
	auxSolidSphere(5.0f);
	glPopName();
	glPopMatrix();

	// ����Mars

	glRGB(255,0,0);
	glPushMatrix();
	glTranslatef(100.0f, 0.0f, 0.0f);
	glLoadName(MARS);
	auxSolidSphere(20.0f);
	// ����Moon1
	glTranslatef(-40.0f, 40.0f, 0.0f);
	glRGB(220,220,220);
	glPushName(MOON1);
	auxSolidSphere(5.0f);
	glPopName();
	// ����Moon2
	glTranslatef(0.0f, -80.0f, 0.0f);
	glPushName(MOON2);
	auxSolidSphere(5.0f);
	glPopName();
	glPopMatrix();

	// �ָ�����״̬
	glPopMatrix();	
	glFlush();


	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void CMyPick2View::Init(GLvoid)
{
	// ��Դֵ
	GLfloat  whiteLight[] = { 0.35f, 0.35f, 0.35f, 1.0f };
	GLfloat  sourceLight[] = { 0.65f, 0.65f, 0.65f, 1.0f };
	GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);		
	glEnable(GL_CULL_FACE);	
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.60f, 0.60f, 0.60f, 1.0f );

}

void CMyPick2View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int xPos = point.x;  // horizontal position of cursor 
	int yPos = point.y;  // vertical position of cursor 
	ProcessSelection(xPos, yPos);	
	CView::OnLButtonDown(nFlags, point);
}

void CMyPick2View::ProcessSelection(int xPos, int yPos)
{
	// ѡ�񻺳���
	GLuint selectBuff[BUFFER_LENGTH];
	// �������ӿڱ���
	GLint hits, viewport[4];
	// ����ѡ�񻺳���
	glSelectBuffer(BUFFER_LENGTH, selectBuff);
	// ����ӿ�
	glGetIntegerv(GL_VIEWPORT, viewport);
	// �л���ͶӰ�����������
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	// �ı���Ⱦģʽ
	glRenderMode(GL_SELECT);
	glLoadIdentity();
	gluPickMatrix(xPos, yPos, 2,2, viewport);
	gluPerspective(45.0f, fAspect, 1.0, 425.0);
	RenderScene();
	// �ռ���굥��
	hits = glRenderMode(GL_RENDER);
	// ���ѡ����
	if(hits == 1)
		ProcessPlanet(selectBuff);
	// ����ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void CMyPick2View::ProcessPlanet(GLuint *pSelectBuff)
{
	int id,count;
	char cMessage[64];
	// ���ƶ�ջ�����Ƶ���Ŀ
	count = pSelectBuff[0];
	// ���ƶ�ջ��ջ��
	id = pSelectBuff[3];
	// ѡ����
	switch(id)
		{
		case EARTH:
			strcpy(cMessage,"You clicked Earth.");
			if(count == 2)
				strcat(cMessage,"\nSpecifically the moon.");
			break;
		case MARS:
			strcpy(cMessage,"You clicked Mars.");
			if(count == 2)
				{
				if(pSelectBuff[4] == MOON1)
					strcat(cMessage,"\nSpecifically Moon #1.");
				else
					strcat(cMessage,"\nSpecifically Moon #2.");
				}
			break;
		default:
			strcpy(cMessage,"Error - Nothing was clicked on!");
			break;
		}
	MessageBox(cMessage,"Selection Message",MB_OK);
}


