// MyFireworkView.cpp : implementation of the CMyFireworkView class
//

#include "stdafx.h"
#include "MyFirework.h"

#include "MyFireworkDoc.h"
#include "MyFireworkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFireworkView

IMPLEMENT_DYNCREATE(CMyFireworkView, CView)

BEGIN_MESSAGE_MAP(CMyFireworkView, CView)
	//{{AFX_MSG_MAP(CMyFireworkView)
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
// CMyFireworkView construction/destruction

CMyFireworkView::CMyFireworkView()
{
	// TODO: add construction code here

}

CMyFireworkView::~CMyFireworkView()
{
}

BOOL CMyFireworkView::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyFireworkView drawing

void CMyFireworkView::OnDraw(CDC* pDC)
{
	CMyFireworkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyFireworkView printing

BOOL CMyFireworkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFireworkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFireworkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFireworkView diagnostics

#ifdef _DEBUG
void CMyFireworkView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFireworkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFireworkDoc* CMyFireworkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFireworkDoc)));
	return (CMyFireworkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFireworkView message handlers

int CMyFireworkView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	InitializeTexture();	
	return 0;
}

void CMyFireworkView::OnDestroy() 
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

void CMyFireworkView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.33, 1.33, 0, 2);
	glMatrixMode(GL_MODELVIEW);
	WindW = cx;
	WindH = cy;	
}

void CMyFireworkView::OnTimer(UINT nIDEvent) 
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
void CMyFireworkView::SetLogicalPalette(void)
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
BOOL CMyFireworkView::InitializeOpenGL(CDC* pDC)
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
BOOL CMyFireworkView::SetupPixelFormat()
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
BOOL CMyFireworkView::RenderScene() 
{
	float s;
	int i, flag_temp;
	struct firework *fw_temp, *fw_temp2;
	AddFirework();		//  ����̻�
	glClear(GL_COLOR_BUFFER_BIT);
	//  �����̻�
	glColor3f(1, 1, 1);
	fw_temp = fw;
	glDisable(GL_TEXTURE_2D);
	while (fw_temp)
	{
		if (!fw_temp->flag)
		{
			glPushMatrix();
			s = (9.8*fw_temp->t*fw_temp->t)/1000;
			glRotatef(fw_temp->dir, 0, 0, 1);
			glTranslatef(0, 1.5-s, 0);
			glBegin(GL_POINTS);
			glVertex2f(0, 0);
			glEnd();
			glPopMatrix();
		}
		fw_temp = fw_temp->next;
	}
	glEnable(GL_TEXTURE_2D);
	// �������еı�ը����
	fw_temp = fw;
	fw_temp2 = NULL;
	while (fw_temp)
	{
		glPushMatrix();
		s = (9.8*fw_temp->t*fw_temp->t)/1000; // ���ӵ�λ�� s = gt^2/2 
		glRotatef(fw_temp->dir, 0, 0, 1);
		glTranslatef(0, 1.5-s, 0);
		fw_temp->t -= 0.08;
		if (fw_temp->t <= 2)
			if (!fw_temp->flag) fw_temp->flag = 1; // ��������ģʽ
			if (fw_temp->flag)
			{
				// ��������
				flag_temp = 0;
				for (i=0; i<MAX_POINTS; i++)
				{
					glPushMatrix();
					glTranslatef(fw_temp->x, fw_temp->y, 0);
					glRotatef(fw_temp->fp[i].dir, 0, 0, 1);
					glColor4f(fw_temp->fp[i].r, fw_temp->fp[i].g, fw_temp->fp[i].b, 1);
					glBegin(GL_QUADS);
					glTexCoord2f(0, 0); glVertex2f(fw_temp->fp[i].x-0.02, -0.02);
					glTexCoord2f(1, 0); glVertex2f(fw_temp->fp[i].x+0.02, -0.02);
					glTexCoord2f(1, 1); glVertex2f(fw_temp->fp[i].x+0.02, 0.02);
					glTexCoord2f(0, 1); glVertex2f(fw_temp->fp[i].x-0.02, 0.02);
					glEnd();
					glPopMatrix();
					fw_temp->fp[i].x += fw_temp->fp[i].speed;
					// ��ɫ�䵭
					if (fw_temp->fp[i].r > 0) fw_temp->fp[i].r -= 0.01;
					if (fw_temp->fp[i].r < 0) 
					{
						fw_temp->fp[i].r = 0;
						fw_temp->counter++;
					}
					if (fw_temp->fp[i].g > 0) fw_temp->fp[i].g -= 0.01;
					if (fw_temp->fp[i].g < 0)
					{
						fw_temp->fp[i].g = 0;
						fw_temp->counter++;
					}
					if (fw_temp->fp[i].b > 0) fw_temp->fp[i].b -= 0.01;
					if (fw_temp->fp[i].b < 0)
					{
						fw_temp->fp[i].b = 0;
						fw_temp->counter++;
					}
					// ����̻������Ƿ����
					if (fw_temp->counter >= MAX_POINTS*3) 
					{
						// ɾ�����̻�
						if (fw_temp2 != NULL)
						{
							fw_temp2->next = fw_temp->next;
							free(fw_temp);
							fw_temp = fw_temp2->next;
						}
						else
						{
							fw = fw_temp->next;
							free(fw_temp);
							fw_temp2 = NULL;
							fw_temp = fw;
						}
						flag_temp = 1;
						glPopMatrix();
						break;
					}
				}
				if (flag_temp) continue;
			}
			glPopMatrix();
			// ������һ���̻�
			fw_temp2 = fw_temp;
			fw_temp = fw_temp->next;
	}
	glFlush();  

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void CMyFireworkView::AddFirework()
{
  struct firework *fw_temp;

  if ((rand() % 50) == 0)
  {
    // ����µ��̻�
    if (fw == NULL)
    {
      fw = (struct firework *)malloc(sizeof(struct firework));
      fw->next = NULL;
    }
    else
    {
      fw_temp = (struct firework *)malloc(sizeof(struct firework));
      fw_temp->next = fw;
      fw = fw_temp;
    }
    fw->type = (rand() % 8);
    fw->x = 0;
    fw->y = 0;
    fw->flag = 0;
    fw->t = 20; 
    fw->counter = 0;
    fw->dir = (rand() % 70)-35;
    // ��ʼ���̻�����
    for (i=0; i<MAX_POINTS; i++)
    {
      fw->fp[i].dir = (rand() % 360);
      if (fw->type & 4) fw->fp[i].speed = (float)(rand() % 1000)/100000;
      else fw->fp[i].speed = 0.005+(float)(rand() % 1000)/1000000;;
          
      fw->fp[i].x = 0;
      
      if ((fw->type & 3) == 0)
      {
        // ��ɫ
        fw->fp[i].r = 1;
        fw->fp[i].g = 1;
        fw->fp[i].b = 1;
      }
      else
      if ((fw->type & 3) == 1)
      {
        // ��ɫ
        fw->fp[i].r = 1;
        fw->fp[i].g = 0;
        fw->fp[i].b = 0;
      }
      else
      if ((fw->type & 3) == 2)
      {
        // ��ɫ
        fw->fp[i].r = 1;
        fw->fp[i].g = 1;
        fw->fp[i].b = 0;
      }
      else
      {
        // �����ɫ
        fw->fp[i].r = (float)(rand() % 256)/255;
        fw->fp[i].g = (float)(rand() % 256)/255;
        fw->fp[i].b = (float)(rand() % 256)/255;
      }
      if (fw->fp[i].r == 0) fw->counter++;
      if (fw->fp[i].g == 0) fw->counter++;
      if (fw->fp[i].b == 0) fw->counter++;
    }
  }
}


void CMyFireworkView::InitializeTexture()
{
	int texwid, texht;
	int texcomps;
	char fn[]="particle.rgb";
 
	teximage = m_Tex->read_texture(fn, &texwid, &texht, &texcomps);
	if (!teximage)
	{
		printf("Sorry, can't read texture file...");
		exit(0);
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);  
} 


void CMyFireworkView::Init()
{
  srand((unsigned int)time(NULL));
  fw = NULL;
  glPointSize(2.0f);
  glClearColor(0, 0, 0, 1);
  glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
  glEnable(GL_BLEND);
}

