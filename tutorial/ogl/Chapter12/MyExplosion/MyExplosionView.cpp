// MyExplosionView.cpp : implementation of the CMyExplosionView class
//

#include "stdafx.h"
#include "MyExplosion.h"

#include "MyExplosionDoc.h"
#include "MyExplosionView.h"

#include <math.h>
const float pi = 3.1415926;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionView

IMPLEMENT_DYNCREATE(CMyExplosionView, CView)

BEGIN_MESSAGE_MAP(CMyExplosionView, CView)
	//{{AFX_MSG_MAP(CMyExplosionView)
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
// CMyExplosionView construction/destruction

CMyExplosionView::CMyExplosionView()
{
	// TODO: add construction code here
	sc=0;
	stop=0;
	alpha=0;
	coef=30;
	counter=100;
	flag_exp=0;
	flag_exp1=0;
	exp_coef=0;
	exp_color = 1;
}

CMyExplosionView::~CMyExplosionView()
{
}

BOOL CMyExplosionView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyExplosionView drawing

void CMyExplosionView::OnDraw(CDC* pDC)
{
	CMyExplosionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionView printing

BOOL CMyExplosionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyExplosionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyExplosionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionView diagnostics

#ifdef _DEBUG
void CMyExplosionView::AssertValid() const
{
	CView::AssertValid();
}

void CMyExplosionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyExplosionDoc* CMyExplosionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyExplosionDoc)));
	return (CMyExplosionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionView message handlers

int CMyExplosionView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	LoadTexture(0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	textures.Init();
	ship.LoadFromFile("data/ship.obj", &textures);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);	

	return 0;
}

void CMyExplosionView::OnDestroy() 
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

void CMyExplosionView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 3, 250);
	glMatrixMode(GL_MODELVIEW);	
}

void CMyExplosionView::OnTimer(UINT nIDEvent) 
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
void CMyExplosionView::SetLogicalPalette(void)
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
BOOL CMyExplosionView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyExplosionView::SetupPixelFormat()
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
BOOL CMyExplosionView::RenderScene() 
{
	float cx, cy, cz;
	float px, py, pz;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLoadIdentity();
	glTranslatef(0, 0, -100);
	glColor3f(1, 1, 1);
	glRotatef(alpha, 0, 1, 0);
	glRotatef(-120, 1, 0, 0);
	alpha += 2;
	glDisable(GL_BLEND);
	counter--;
	if (counter < 0) counter = 0;
	if ((counter == 0) && (!flag_exp))
	{
		ship.Explosion();
		flag_exp = 1;
	}
	if (flag_exp1)
	{	
		ship.Explosion_Step(coef);
		coef -= coef/30;
	}
	if (coef < 0) coef = 0;
	ship.Draw();
	glEnable(GL_BLEND);
	// ���Ʊ�ը��Ķ����
	// cx, cy, cz - ���������ʸ��
	// px, py, pz - ����η���ʸ��
	if (flag_exp)
	{
		cx = 0;
		cy = 0;
		cz = 1;
		px = cx;
		py = cy;
		pz = -cz;
		float d = sqrt(px*px + py*py + pz*pz);
		px /= d;
		py /= d;
		pz /= d;
		float phi, theta;
		theta = asin(pz);
		phi = asin(py/cos(theta));
		theta = (theta*180)/pi;
		phi = (phi*180)/pi;
		glLoadIdentity();
		glTranslatef(0, 0, -180);
		glRotatef(phi, 1, 0, 0);
		glRotatef(theta, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glScalef(exp_coef, exp_coef, exp_coef);
		exp_coef += exp_coef/20 + 0.1;
		if (exp_coef > 0.5) flag_exp1 = 1;
		glColor4f(1, 1, 1, exp_color);
		if (flag_exp1) exp_color -= 0.05;
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex3f(0, -100, -100);
			glTexCoord2f(0, 0); glVertex3f(0, 100, -100);
			glTexCoord2f(1, 0); glVertex3f(0, 100, 100);
			glTexCoord2f(1, 1); glVertex3f(0, -100, 100);
		glEnd();
	}
	glFlush();  

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void CMyExplosionView::LoadTexture(int t_num)
{
	int texwid, texht;
	int texcomps;
    char fn[]="data/vzr.rgb";
	teximage = m_Tex->read_texture(fn, &texwid, &texht, &texcomps);
	if (!teximage)
	{
		MessageBox("Sorry, can't read texture file...","Error",MB_OK);
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, texture[t_num]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texwid, texht, GL_RGBA, GL_UNSIGNED_BYTE, teximage);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	free(teximage);
} 

