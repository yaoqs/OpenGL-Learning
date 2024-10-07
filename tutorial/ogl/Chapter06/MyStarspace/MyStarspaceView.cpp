// MyStarspaceView.cpp : implementation of the CMyStarspaceView class
//

#include "stdafx.h"
#include "MyStarspace.h"

#include "MyStarspaceDoc.h"
#include "MyStarspaceView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStarspaceView

IMPLEMENT_DYNCREATE(CMyStarspaceView, CView)

BEGIN_MESSAGE_MAP(CMyStarspaceView, CView)
	//{{AFX_MSG_MAP(CMyStarspaceView)
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
// CMyStarspaceView construction/destruction

CMyStarspaceView::CMyStarspaceView()
{
	// TODO: add construction code here
	flag = NORMAL;
	starCount = MAXSTARS / 2;
	speed = 1.0;
	nitro = 0;
	windW = 300;
	windH = 300;
}

CMyStarspaceView::~CMyStarspaceView()
{
}

BOOL CMyStarspaceView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyStarspaceView drawing

void CMyStarspaceView::OnDraw(CDC* pDC)
{
	CMyStarspaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyStarspaceView printing

BOOL CMyStarspaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyStarspaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyStarspaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyStarspaceView diagnostics

#ifdef _DEBUG
void CMyStarspaceView::AssertValid() const
{
	CView::AssertValid();
}

void CMyStarspaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyStarspaceDoc* CMyStarspaceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyStarspaceDoc)));
	return (CMyStarspaceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyStarspaceView message handlers

int CMyStarspaceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyStarspaceView::OnDestroy() 
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

void CMyStarspaceView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	windW = cx;
	windH = cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-0.5, windW + 0.5, -0.5, windH + 0.5);
	glMatrixMode(GL_MODELVIEW);	
}

void CMyStarspaceView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//��Ӷ�ʱ����Ӧ�����ͳ������º���
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	MoveStars();
	UpdateStars();
	if (nitro > 0) 
	{
		speed = (float) (nitro / 10) + 1.0;
		if (speed > MAXWARP) 
		{
			speed = MAXWARP;
		}
		if (++nitro > MAXWARP * 10) 
		{
			nitro = -nitro;
		}
	} else if (nitro < 0)
	{
		nitro++;
		speed = (float) (-nitro / 10) + 1.0;
		if (speed > MAXWARP) 
		{
			speed = MAXWARP;
		}
	}	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  �����߼���ɫ��
//////////////////////////////////////////////////////////////////////
void CMyStarspaceView::SetLogicalPalette(void)
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
BOOL CMyStarspaceView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyStarspaceView::SetupPixelFormat()
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
BOOL CMyStarspaceView::RenderScene() 
{
	ShowStars();

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void CMyStarspaceView::ShowStars(void)
{
	GLint n;

	glClear(GL_COLOR_BUFFER_BIT);

	for (n = 0; n < starCount; n++) 
	{
		if (stars[n].z[0] > speed || (stars[n].z[0] > 0.0 && speed < MAXWARP)) 
		{
			ShowStar(n);
		}
	}
}

void CMyStarspaceView::ShowStar(GLint n)
{
	float x0, y0, x1, y1, width;
	GLint i;

	x0 = stars[n].x[0] * windW / stars[n].z[0];
	y0 = stars[n].y[0] * windH / stars[n].z[0];
	x0 += windW / 2.0;
	y0 += windH / 2.0;

	if (x0 >= 0.0 && x0 < windW && y0 >= 0.0 && y0 < windH) 
	{
		if (stars[n].type == STREAK) 
		{
			x1 = stars[n].x[1] * windW / stars[n].z[1];
			y1 = stars[n].y[1] * windH / stars[n].z[1];
			x1 += windW / 2.0;
			y1 += windH / 2.0;

			glLineWidth(MAXPOS / 100.0 / stars[n].z[0] + 1.0);
			glColor3f(1.0, (MAXWARP - speed) / MAXWARP, (MAXWARP - speed) / MAXWARP);
			if (fabs(x0 - x1) < 1.0 && fabs(y0 - y1) < 1.0) 
			{
				glBegin(GL_POINTS);
				glVertex2f(x0, y0);
				glEnd();
			} else
			{
				glBegin(GL_LINES);
				glVertex2f(x0, y0);
				glVertex2f(x1, y1);
				glEnd();
			}
		}else
		{
			width = MAXPOS / 10.0 / stars[n].z[0] + 1.0;
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			for (i = 0; i < 8; i++) 
			{
				float x = x0 + width * Cos((float) i * MAXANGLES / 8.0);
				float y = y0 + width * Sin((float) i * MAXANGLES / 8.0);
				glVertex2f(x, y);
			};
			glEnd();
		}
	}
}



void CMyStarspaceView::Init(void)
{
	float angle;
	GLint n;

	srand((unsigned int) time(NULL));
	for (n = 0; n < MAXSTARS; n++) 
	{
		NewStar(n, 100);
	}

	angle = 0.0;
	for (n = 0; n <= MAXANGLES; n++) 
	{
		sinTable[n] = sin(angle);
		angle += PI / (MAXANGLES / 2.0);
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glDisable(GL_DITHER);
}

void CMyStarspaceView::RotatePoint(float *x, float *y, float rotation)
{
	float tmpX, tmpY;
	
	tmpX = *x * Cos(rotation) - *y * Sin(rotation);
	tmpY = *y * Cos(rotation) + *x * Sin(rotation);
	*x = tmpX;
	*y = tmpY;
}

float CMyStarspaceView::Sin(float angle)
{
	return (sinTable[(GLint) angle]);
}

float CMyStarspaceView::Cos(float angle)
{
	return (sinTable[((GLint) angle + (MAXANGLES / 4)) % MAXANGLES]);
}

void CMyStarspaceView::NewStar(GLint n, GLint d)
{
	if (rand() % 4 == 0) 
	{
		stars[n].type = CIRCLE;
	}else
	{
		stars[n].type = STREAK;
	}
	stars[n].x[0] = (float) (rand() % MAXPOS - MAXPOS / 2);
	stars[n].y[0] = (float) (rand() % MAXPOS - MAXPOS / 2);
	stars[n].z[0] = (float) (rand() % MAXPOS + d);
	stars[n].x[1] = stars[n].x[0];
	stars[n].y[1] = stars[n].y[0];
	stars[n].z[1] = stars[n].z[0];
	if (rand() % 4 == 0 && flag == WEIRD) 
	{
		stars[n].offsetX = (float) (rand() % 100 - 100 / 2);
		stars[n].offsetY = (float) (rand() % 100 - 100 / 2);
		stars[n].offsetR = (float) (rand() % 25 - 25 / 2);
	}else 
	{
		stars[n].offsetX = 0.0;
		stars[n].offsetY = 0.0;
		stars[n].offsetR = 0.0;
	}
}

void CMyStarspaceView::MoveStars(void)
{
	float offset;
	GLint n;

	offset = speed * 60.0;

	for (n = 0; n < starCount; n++) 
	{
		stars[n].x[1] = stars[n].x[0];
		stars[n].y[1] = stars[n].y[0];
		stars[n].z[1] = stars[n].z[0];
		stars[n].x[0] += stars[n].offsetX;
		stars[n].y[0] += stars[n].offsetY;
		stars[n].z[0] -= offset;
	}
}

void CMyStarspaceView::UpdateStars(void)
{
	GLint n;
	glClear(GL_COLOR_BUFFER_BIT);

	for (n = 0; n < starCount; n++) 
	{
		if (stars[n].z[0] > speed || (stars[n].z[0] > 0.0 && speed < MAXWARP)) 
		{
			if (StarPoint(n) == GL_FALSE) 
			{
				NewStar(n, MAXPOS);
			}
		}
		else
		{
			NewStar(n, MAXPOS);
		}
	}
}

GLenum CMyStarspaceView::StarPoint(GLint n)
{
	float x0, y0;
	x0 = stars[n].x[0] * windW / stars[n].z[0];
	y0 = stars[n].y[0] * windH / stars[n].z[0];
	x0 += windW / 2.0;
	y0 += windH / 2.0;

	if (x0 >= 0.0 && x0 < windW && y0 >= 0.0 && y0 < windH) 
	{
		return GL_TRUE;
	}
	else 
	{
		return GL_FALSE;
	}
}
