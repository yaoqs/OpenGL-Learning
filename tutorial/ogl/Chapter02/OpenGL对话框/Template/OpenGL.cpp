// OpenGL.cpp : implementation file
//

#include "stdafx.h"
#include "$$root$$.h"
#include "OpenGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGL

COpenGL::COpenGL()
{
	//����Ա��������ֵ
	step=0.0;
	s=0.1;
}

COpenGL::~COpenGL()
{
	wglMakeCurrent(NULL, NULL) ; 
	wglDeleteContext(hglrc);	//ɾ����Ⱦ������
	::ReleaseDC (m_hWnd, hdc) ; //�ͷ��豸������

}


BEGIN_MESSAGE_MAP(COpenGL, CWnd)
	//{{AFX_MSG_MAP(COpenGL)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////
// �������ظ�ʽ����
int COpenGL::MySetPixelFormat(HDC hdc)
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
	
	int  iPixelFormat; 
 
	// Ϊ�豸������õ���ƥ������ظ�ʽ 
	if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat Failed", NULL, MB_OK);
		return 0;
	}
	 
	// ������ƥ������ظ�ʽΪ��ǰ�����ظ�ʽ 
	if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat Failed", NULL, MB_OK);
		return 0;
	}

	return 1;
}


/////////////////////////////////////////////////////////////////////////////
// COpenGL message handlers

int COpenGL::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	// ���õ�ǰ�Ļ�ͼ���ظ�ʽ
	MySetPixelFormat(::GetDC(m_hWnd));

	// ������ͼ������
	hdc = ::GetDC(m_hWnd);
	// ������Ⱦ������
	hglrc = wglCreateContext(hdc);
	// ʹ��ͼ������Ϊ��ǰ�����̵ֳĵ�ǰ��ͼ������ 
	wglMakeCurrent(hdc, hglrc);	
	return 0;
}

void COpenGL::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//����OpenGL��ͼ��������ͼ�λ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//�����ɫ�������Ȼ���

    s+=0.005;
    if(s>1.0)
		s=0.1;
	step = step + 1.0;
    if (step > 360.0)
		step = step - 360.0;
    glPushMatrix();
	glScalef(s,s,s);
    glRotatef(step,0.0,1.0,0.0);
    glRotatef(step,0.0,0.0,1.0);
  	glRotatef(step,1.0,0.0,0.0);
    DrawColorBox();
    glPopMatrix();
    glFlush();

	SwapBuffers(hdc);
	
	// Do not call CWnd::OnPaint() for painting messages
}

void COpenGL::DrawColorBox(void)
{
	GLfloat  p1[]={0.5,-0.5,-0.5}, p2[]={0.5,0.5,-0.5},
                p3[]={0.5,0.5,0.5},   p4[]={0.5,-0.5,0.5},
                p5[]={-0.5,-0.5,0.5}, p6[]={-0.5,0.5,0.5},
                p7[]={-0.5,0.5,-0.5}, p8[]={-0.5,-0.5,-0.5};

	GLfloat  m1[]={1.0,0.0,0.0},	m2[]={-1.0,0.0,0.0},
				m3[]={0.0,1.0,0.0},	m4[]={0.0,-1.0,0.0},
				m5[]={0.0,0.0,1.0},	m6[]={0.0,0.0,-1.0};

   	
	GLfloat  c1[]={0.0,0.0,1.0},  c2[]={0.0,1.0,1.0},
                c3[]={1.0,1.0,1.0},  c4[]={1.0,0.0,1.0},
                c5[]={1.0,0.0,0.0},  c6[]={1.0,1.0,0.0},
                c7[]={0.0,1.0,0.0},  c8[]={1.0,1.0,1.0};
              
 	
 	  glBegin (GL_QUADS);	//���ƶ���ı���
        
		  glColor3fv(c1);
         glNormal3fv(m1);
        glVertex3fv(p1);
		  glColor3fv(c2);
        glVertex3fv(p2);
		  glColor3fv(c3);
        glVertex3fv(p3);
		  glColor3fv(c4);
        glVertex3fv(p4);

		  glColor3fv(c5);
         glNormal3fv(m5);
        glVertex3fv(p5);
		  glColor3fv(c6);
        glVertex3fv(p6);
		  glColor3fv(c7);
        glVertex3fv(p7);
		  glColor3fv(c8);
        glVertex3fv(p8);

		  glColor3fv(c5);
         glNormal3fv(m3);
        glVertex3fv(p5);
		  glColor3fv(c6);
        glVertex3fv(p6);
		  glColor3fv(c3);
        glVertex3fv(p3);
		  glColor3fv(c4);
        glVertex3fv(p4);

		  glColor3fv(c1);
         glNormal3fv(m4);
        glVertex3fv(p1);
		  glColor3fv(c2);
        glVertex3fv(p2);
		  glColor3fv(c7);
        glVertex3fv(p7);
		  glColor3fv(c8);
        glVertex3fv(p8);

		  glColor3fv(c2);
         glNormal3fv(m5);
        glVertex3fv(p2);
		  glColor3fv(c3);
        glVertex3fv(p3);
		  glColor3fv(c6);
        glVertex3fv(p6);
		  glColor3fv(c7);
        glVertex3fv(p7);

		  glColor3fv(c1);
         glNormal3fv(m6);
        glVertex3fv(p1);
		  glColor3fv(c4);
        glVertex3fv(p4);
		  glColor3fv(c5);
        glVertex3fv(p5);
		  glColor3fv(c8);
        glVertex3fv(p8);

	  glEnd();


}
