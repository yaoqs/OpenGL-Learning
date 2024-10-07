// MyFountainView.cpp : implementation of the CMyFountainView class
//

#include "stdafx.h"
#include "MyFountain.h"

#include "MyFountainDoc.h"
#include "MyFountainView.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFountainView

IMPLEMENT_DYNCREATE(CMyFountainView, CView)

BEGIN_MESSAGE_MAP(CMyFountainView, CView)
	//{{AFX_MSG_MAP(CMyFountainView)
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
// CMyFountainView construction/destruction

CMyFountainView::CMyFountainView()
{
	// TODO: add construction code here

}

CMyFountainView::~CMyFountainView()
{
}

BOOL CMyFountainView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyFountainView drawing

void CMyFountainView::OnDraw(CDC* pDC)
{
	CMyFountainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyFountainView printing

BOOL CMyFountainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFountainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFountainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFountainView diagnostics

#ifdef _DEBUG
void CMyFountainView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFountainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFountainDoc* CMyFountainView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFountainDoc)));
	return (CMyFountainDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFountainView message handlers

int CMyFountainView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyFountainView::OnDestroy() 
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

void CMyFountainView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 1000);
  glMatrixMode(GL_MODELVIEW);

}

void CMyFountainView::OnTimer(UINT nIDEvent) 
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
void CMyFountainView::SetLogicalPalette(void)
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
BOOL CMyFountainView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyFountainView::SetupPixelFormat()
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
BOOL CMyFountainView::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	a += 0.2;
	gluLookAt(cam.x, cam.y, cam.z, 0, 0, 0, upv.x, upv.y, upv.z); 
	// ���Ƶ���
	glPushMatrix();
	glRotatef(a, 0, -1, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-100, 0, -100);
		glTexCoord2f(2, 0); glVertex3f(-100, 0, 100);
		glTexCoord2f(2, 2); glVertex3f(100, 0, 100);
		glTexCoord2f(0, 2); glVertex3f(100, 0, -100);
	glEnd();
	glPopMatrix();

	// ������Ȫ
	DrawFountain();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	glRotatef(a, 0, -1, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-100, 0, -100);
		glTexCoord2f(1, 0); glVertex3f(-100, 0, 100);
		glTexCoord2f(1, 1); glVertex3f(100, 0, 100);
		glTexCoord2f(0, 1); glVertex3f(100, 0, -100);
	glEnd();
	glPopMatrix();
 
	glFlush();  

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}


// ��Ȫ�ĳ�ʼ��
void CMyFountainView::Init()
{
	a=0;
    fn[0] = NULL;
	fn[1] = NULL;
	fn[2] = NULL;
	upv.x = -5;
	upv.y = 5;
	upv.z = -5;
	cam.x = 200;
	cam.y = 200;
	cam.z = 200;
	glGenTextures(3, texture); 
	glClearColor(0, 0, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	LoadTexture("particle.rgb", 0);
	LoadTexture("ground1.rgb", 1);
	LoadTexture("ground2.rgb", 2);
}

// ����װ�뺯��
void CMyFountainView::LoadTexture(char *fn, int t_num)
{
	int texwid, texht;
	int texcomps;
	
	teximage = m_Tex->read_texture(fn, &texwid, &texht, &texcomps);
	if (!teximage)
	{
		MessageBox("Sorry, can't read texture file...","ERROR",MB_OK);
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, texture[t_num]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

	if ((t_num == 0) || (t_num == 2)) glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	if (t_num == 1)
	{
		// ���ڵ�������,�ظ��������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	}
	free(teximage);
} 


// ����µ�����
void CMyFountainView::AddParticles()
{
	struct particle *tempp;
	int i, j;

	for (j=0; j<3; j++)
		for (i=0; i<2; i++)
		{
			tempp = (struct particle *)malloc(sizeof(struct particle));
			if (fn[j]) fn[j]->prev = tempp;
			tempp->next = fn[j];
			fn[j] = tempp;
			
			tempp->t = -9.9;
			tempp->v = (float)(rand() % 200000)/100000+1; // �����ٶ�
			tempp->d = (float)(rand() % 400)/100-2;       // ���ӷ���
			// ��ʼλ�õ�����
			tempp->x = 0;
			tempp->y = 0;
			tempp->z = 0;
			tempp->xd = cos((tempp->d*3.14159)/180)*tempp->v/4;
			tempp->zd = sin((tempp->d*3.14159)/180)*tempp->v;
			tempp->type = 0; // ����״̬Ϊ�˶�
			tempp->a = 1;    // ���ӵ���
		}
}

// �����˶�����
void CMyFountainView::MoveParticles()
{
	struct particle *tempp;
	int j;
	for (j=0; j<3; j++)
	{
		tempp = fn[j]; 
		while (tempp)
		{
			if (tempp->type == 0) // ������Ӵ����˶�״̬
			{
				tempp->x += tempp->xd;
				tempp->z += tempp->zd;
				tempp->y = -(9.8*(tempp->t*tempp->t/4))/2+122.5; // �������ӵĸ߶� H = gt^2/2 
				tempp->t += 0.1; // ������������
				if (tempp->y < 0) tempp->type = 1; // �������λ�ڵ���
			}else // ����λ�ڵ���
			{
				tempp->y = -(9.8*(tempp->t*tempp->t/4))/2+122.5; 
				tempp->a -= 0.1; // ���ӵ���
			}
			tempp = tempp->next; // ��һ������
		}
	}
}

//ɾ������
void CMyFountainView::DeleteParticles()
{
	struct particle *tempp, *temp1;
	int j;

	for (j=0; j<3; j++)
	{
		tempp = fn[j];
		while (tempp)
		{
			if ((tempp->type == 1) && (tempp->a <= 0)) // ��������
			{
				// ɾ������
				temp1 = tempp->prev;
				tempp->prev->next = tempp->next;
				if (tempp->next) tempp->next->prev = temp1;
				free(tempp);
				tempp = temp1;
			}
			tempp = tempp->next;
		}
	}
}

void CMyFountainView::vect_mult(struct point *A, struct point *B, struct point *C)
{
	// ʸ�����
	C->x = A->y*B->z - A->z*B->y;
	C->y = A->z*B->x - A->x*B->z;
	C->z = A->x*B->y - A->y*B->x;
}

// ʸ����λ��
void CMyFountainView::normalize(struct point *V)
{
	float d;
	// ʸ������
	d = sqrt(V->x*V->x + V->y*V->y + V->z*V->z);
	// ��λ��
	V->x /= d; 
	V->y /= d; 
	V->z /= d; 
}

void CMyFountainView::DrawFountain()
{
	int j;
	struct particle *tempp;
	struct point vectd, vectl; 
	float alpha, ttx, ttz;

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	
	AddParticles();
	MoveParticles();
	DeleteParticles();
	glPushMatrix();
	for (j=0; j<3; j++)
	{
		glBegin(GL_QUADS);
		tempp = fn[j];
		while (tempp)
		{
			// ��ת��Ȫ
			alpha = ((j*120+a)*PI)/180;
			ttx = tempp->x*cos(alpha)-tempp->z*sin(alpha);
			ttz = tempp->x*sin(alpha)+tempp->z*cos(alpha);
			// ���㷽��ʸ��
			vectd.x = ttx - cam.x;
			vectd.y = tempp->y - cam.y;
			vectd.z = ttz - cam.z;
			vect_mult(&vectd, &upv, &vectl);
			normalize(&vectl);
			vectl.x *= 5;
			vectl.y *= 5;
			vectl.z *= 5;
			glColor4f(0.5, 0.5, 1, tempp->a);
			// ���ƶ���κ���������ӳ��
			glTexCoord2f(0, 0); glVertex3f((ttx-vectl.x), (tempp->y-upv.y), (ttz-vectl.z));
			glTexCoord2f(1, 0); glVertex3f((ttx+vectl.x), (tempp->y-upv.y), (ttz+vectl.z));
			glTexCoord2f(1, 1); glVertex3f((ttx+vectl.x), (tempp->y+upv.y), (ttz+vectl.z));
			glTexCoord2f(0, 1); glVertex3f((ttx-vectl.x), (tempp->y+upv.y), (ttz-vectl.z));
			tempp = tempp->next; // ������һ�������б�
		}
		glEnd();
	}
	glPopMatrix();
}