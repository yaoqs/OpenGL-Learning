// MyFire2View.cpp : implementation of the CMyFire2View class
//

#include "stdafx.h"
#include "MyFire2.h"

#include "MyFire2Doc.h"
#include "MyFire2View.h"

#include <math.h>			
#include <time.h>		
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFire2View

IMPLEMENT_DYNCREATE(CMyFire2View, CView)

BEGIN_MESSAGE_MAP(CMyFire2View, CView)
	//{{AFX_MSG_MAP(CMyFire2View)
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
// CMyFire2View construction/destruction

CMyFire2View::CMyFire2View()
{
	// TODO: add construction code here
	iFrames = 0;
	iParticleTexture = 1;
	bIsBurstEnable = 0;
	bIsCamFollowing = FALSE;

	pPS = new CParticleSystem();
}

CMyFire2View::~CMyFire2View()
{
}

BOOL CMyFire2View::PreCreateWindow(CREATESTRUCT& cs)
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
// CMyFire2View drawing

void CMyFire2View::OnDraw(CDC* pDC)
{
	CMyFire2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// CMyFire2View printing

BOOL CMyFire2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFire2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFire2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFire2View diagnostics

#ifdef _DEBUG
void CMyFire2View::AssertValid() const
{
	CView::AssertValid();
}

void CMyFire2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFire2Doc* CMyFire2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFire2Doc)));
	return (CMyFire2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFire2View message handlers

int CMyFire2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	InitParticleSystem();	
	return 0;
}

void CMyFire2View::OnDestroy() 
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
	delete pPS;	
}

void CMyFire2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	glViewport(0, 0, cx, cy);			
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,1.3333f,0.1f,1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}

void CMyFire2View::OnTimer(UINT nIDEvent) 
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
void CMyFire2View::SetLogicalPalette(void)
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
BOOL CMyFire2View::InitializeOpenGL(CDC* pDC)
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
BOOL CMyFire2View::SetupPixelFormat()
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
BOOL CMyFire2View::RenderScene() 
{
	// �����ɫ�������Ȼ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	glLoadIdentity();
	glPushMatrix();
	// ��ֹ�����
	gluLookAt(vCamPos.x, vCamPos.y, vCamPos.z, 
						0.0f,0.0f,0.0f,
						0.0f,1.0f,0.0f);	

	// ��õ�ǰϵͳʱ��
	fTime = static_cast<float>(timeGetTime())*0.001f;
	fEndFrameTime = fTime;
	// ����֡��	
	if ((fEndFrameTime - fStartFrameTime) >= 1.0f) 
	{
		iFramesPerSec  = iFrames;
		iFrames = 0;
		fStartFrameTime = fTime;
	}
	else 	iFrames++;
	// ����ϵͳ����
	pPS->Update(fTime);
	// �������ӵ�����
	glBindTexture(GL_TEXTURE_2D, tList[iParticleTexture]);
	// ��������ϵͳλͼ
	pPS->Draw(fCamRotX,fCamRotY);
	glPopMatrix();

	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

//��ʼ������ϵͳ
bool CMyFire2View::InitParticleSystem(void)
{
	// ȱʡ�������ֵ
	fCameraRadius = 25.0f;
	fCameraYaw = 0.0f;
	fCameraPitch = 0.0f;
	// ��ʼ�������λ��
	vCamPos.x = (float)(cos(fCameraYaw) * cos(fCameraPitch) * fCameraRadius);
	vCamPos.z = (float)(sin(fCameraYaw) * cos(fCameraPitch) * fCameraRadius);
	vCamPos.y = (float)(sin(fCameraPitch) * fCameraRadius);
	fCamRotY = fCameraYaw*360.0f/-6.28f+90.0f;
	fCamRotX = fCameraPitch*360.0f/-6.28f;
	pPS->m_fTimeLastUpdate = static_cast<float>(timeGetTime())*0.001f;
	fStartFrameTime = static_cast<float>(timeGetTime())*0.001f;
	fEndFrameTime   = static_cast<float>(timeGetTime())*0.001f;
	if ( !pPS )
	{
		MessageBox("Couldn't create Particle System!", "Fatal Error", MB_OK );
		return (FALSE);
	}
			// ��������� 
			fCameraPitch  =  0.15f; 
			fCameraYaw	  =  1.56f; 
			fCameraRadius =  37.00f; 
			// ����ϵͳ���� 
			pPS->m_vColorStart.r = 0.48f; 
			pPS->m_vColorStart.g = 0.42f; 
			pPS->m_vColorStart.b = 0.10f; 
			pPS->m_vColorVar.r = 0.15f; 
			pPS->m_vColorVar.g = 0.15f; 
			pPS->m_vColorVar.b = 0.15f; 
			pPS->m_vColorEnd.r = 0.04f; 
			pPS->m_vColorEnd.g = 0.22f; 
			pPS->m_vColorEnd.b = 0.81f; 
			pPS->m_fAlphaStart = 0.92f; 
			pPS->m_fAlphaVar   = 0.14f; 
			pPS->m_fAlphaEnd   = 0.14f; 
			pPS->m_fSizeStart  = 1.04f; 
			pPS->m_fSizeVar    = 0.04f; 
			pPS->m_fSizeEnd    = 1.08f; 
			pPS->m_fSpeed      = 3.00f; 
			pPS->m_fSpeedVar   = 12.00f; 
			pPS->m_fTheta      = 0.20f; 
			pPS->m_fLifeTime   = 0.60f; 
			pPS->m_fLifeVar    = 0.10f; 
			pPS->m_vGravityStart.x		= 0.00f; 
			pPS->m_vGravityEnd.x			= 0.00f; 
			pPS->m_vGravityStart.y		= 0.00f; 
			pPS->m_vGravityEnd.y			= 0.00f; 
			pPS->m_vGravityStart.z		= 0.00f; 
			pPS->m_vGravityEnd.z			= 0.00f; 
			pPS->m_fGravityVar			= 0.00f; 
			pPS->m_uParticlesPerSec = 20; 
			pPS->m_bIsMoving     = 0; 
			pPS->m_bIsColliding		= 1; 
			bIsCamFollowing		= 0; 
			bIsBurstEnable		= 0; 
			pPS->m_fBoing					= 0.30f; 
			iParticleTexture = 1; 
	
	return (TRUE);
}


void CMyFire2View::InitGL(GLvoid)
{
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		
	glClearDepth(1.0);							
	glShadeModel(GL_SMOOTH);					
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();							
	gluPerspective(45.0f,1.3333f,0.1f,1000.0f);	
	glMatrixMode(GL_MODELVIEW);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);			
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	// ���������
	srand( (unsigned)time( NULL ) );
	// װ������
	m_Loadbmp.GLLoadTextures(&tList[0]);
}
