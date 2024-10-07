// MyWaterView.cpp : implementation of the CMyWaterView class
//

#include "stdafx.h"
#include "MyWater.h"

#include "MyWaterDoc.h"
#include "MyWaterView.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MESH 32
/////////////////////////////////////////////////////////////////////////////
// CMyWaterView

IMPLEMENT_DYNCREATE(CMyWaterView, CView)

BEGIN_MESSAGE_MAP(CMyWaterView, CView)
	//{{AFX_MSG_MAP(CMyWaterView)
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
// CMyWaterView construction/destruction

CMyWaterView::CMyWaterView()
{
	// TODO: add construction code here
	mesh = 0;
	ttrans[0]=0.0f;
	ttrans[1]=0.0f;
	amplitude = 0.03;
	freq = 5.0f;
	phase = .003;
}

CMyWaterView::~CMyWaterView()
{
}

BOOL CMyWaterView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyWaterView drawing

void CMyWaterView::OnDraw(CDC* pDC)
{
	CMyWaterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyWaterView printing

BOOL CMyWaterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyWaterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyWaterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyWaterView diagnostics

#ifdef _DEBUG
void CMyWaterView::AssertValid() const
{
	CView::AssertValid();
}

void CMyWaterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyWaterDoc* CMyWaterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyWaterDoc)));
	return (CMyWaterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyWaterView message handlers

int CMyWaterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	InitializeTexture();	
	return 0;
}

void CMyWaterView::OnDestroy() 
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

void CMyWaterView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	
}

void CMyWaterView::OnTimer(UINT nIDEvent) 
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
void CMyWaterView::SetLogicalPalette(void)
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
BOOL CMyWaterView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyWaterView::SetupPixelFormat()
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
BOOL CMyWaterView::RenderScene() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glScalef(10,1,10);
    if (!rgb)
		glColor3f(.31, .41, .97);
	else
		glColor3f(1.f,1.f,1.f);
    glTranslatef(0.f,-1.f,0.f);
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glTranslatef(ttrans[0], ttrans[1], 0.);
    glScalef(10.f, 10.f,1.f);
    draw_mesh();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    ttrans[0] += .005f;
    if (ttrans[0] == 1.0f) ttrans[0] = 0.0f;
    ttrans[1] -= .0025f;
    if (ttrans[1] <= 0.0f) ttrans[1] = 1.0f;

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void CMyWaterView::InitializeTexture()
{
    GLfloat cloud_color[4] = { 1.0, 1.0, 1.0, 0.0, };
    GLfloat fog_color[4], fog_density = 0.05, density, far_cull;
    unsigned *image;
    int width, height, components;
	char* filename;
	filename="water1.bw";
    if (filename) 
	{
		image = m_Tex->read_texture(filename, &width, &height, &components);
		if (image == NULL) 
		{
			AfxMessageBox("����װ��ͼ���ļ���");
		}
		if (components < 3) rgb = 0;
    } else 
	{
		int i, j;
		unsigned char *img;
		components = 4; width = height = 512;
		image = (unsigned *) malloc(width*height*sizeof(unsigned));
		img = (unsigned char *)image;
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++) 
			{
				int w2 = width/2, h2 = height/2;
				if (i & 32)
					img[4*(i+j*width)+0] = 0xff;
				else
					img[4*(i+j*width)+1] = 0xff;
				if (j&32)
					img[4*(i+j*width)+2] = 0xff;
				if ((i-w2)*(i-w2) + (j-h2)*(j-h2) > 64*64 &&
		    (i-w2)*(i-w2) + (j-h2)*(j-h2) < 300*300) img[4*(i+j*width)+3] = 0xff;
			}
	}
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, cloud_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, components, width,
                 height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 image);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.,1.,.1,far_cull = 10.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.,0.,-5.5);

    density = 1.- expf(-5.5 * fog_density * fog_density *
			      far_cull * far_cull);

    density = MAX(MIN(density, 1.), 0.);

    fog_color[0] = .23 + density *.57;
    fog_color[1] = .35 + density *.45;
    fog_color[2] = .78 + density *.22;

    glClearColor(fog_color[0], fog_color[1], fog_color[2], 1.f);

    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, fog_density);
    glFogfv(GL_FOG_COLOR, fog_color);
    if (fog_density > 0)
	glEnable(GL_FOG);
    glLineWidth(2.0f);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void CMyWaterView::draw_mesh(void) 
{
    if (mesh) 
	{
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(-1.f, 0.f, -1.f);
			glTexCoord2f(0, 1); glVertex3f(-1.f, 0.f,  1.f);
			glTexCoord2f(1, 1); glVertex3f( 1.f, 0.f,  1.f);
			glTexCoord2f(1, 0); glVertex3f( 1.f, 0.f, -1.f);
		glEnd();
    } 
	else 
	{
		int i, j;
		static float off;
		float d = 1.f/MESH;
		for(i = 0; i < MESH; i++) 
		{
			glBegin(GL_TRIANGLE_STRIP);
			for(j = 0; j < MESH; j++) 
			{
				float s = (float)j*d;
				float t = (float)i*d;
				float x = -1.0 + 2.f*s;
				float z = -1.0 + 2.f*t;
				float y = amplitude*sinf(freq*2.f*M_PI*t+off);
				glTexCoord2f(s, t); glVertex3f(x, y, z);
				s += d; t += d;
				x = -1.0 + 2.f*s;
				z = -1.0 + 2.f*t;
				y = amplitude*sinf(freq*2.f*M_PI*t+off);
				glTexCoord2f(s, t); glVertex3f(x, y, z);
				off += phase;
			}
			glEnd();
		}
    }
}