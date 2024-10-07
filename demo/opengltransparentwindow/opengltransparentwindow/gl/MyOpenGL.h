#pragma  once

#pragma comment( user, "ComPIled on " __DATE__ " at " __TIME__ ) 



//===================INCLUDE File && LIB Path==================
#include <math.h>

// �����й�OpenGL������ͷ�ļ�
#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/glaux.h"
#include "gl/glut.h"

#pragma comment(lib,"gl/opengl")
#pragma comment(lib,"gl/opengl32")
#pragma comment(lib,"gl/glu")
#pragma comment(lib,"gl/glu32")
#pragma comment(lib,"gl/glut")
#pragma comment(lib,"gl/glut32")
#pragma comment(lib,"gl/glaux")
///opengl.lib opengl32.lib glu.lib  glu32.lib   glut.lib glut32.lib  glaux.lib

//======================MACRO && DEFINE==========================
#ifndef _PI_
const double PI=acos(-1.0); 
#endif

#define DEG2RAD(angle)			((angle) * (PI / 180))	// ���Ƕ�ת��Ϊ����

//===============struct================
struct GLCOLOR
{
	GLfloat R;
	GLfloat G;
	GLfloat B;
};

struct COORDINATE
{
	double X;
	double Y;
	double Z;
};

struct Point
{
	double x;
	double y;
};

//===================
static HGLRC	m_hRC;			//OpenGL����������
static HPALETTE	m_hPalette;		//OpenGL��ɫ��
static HDC		hDC;			//OpenGL�豸������
//==font==
static int fontHeight;  //��ʾ�����С 
static HFONT hFont;//������ 
static LOGFONT lf;//�߼����� 
static GLYPHMETRICSFLOAT gmf[128];//�������ε�λ�úͷ�����Ϣ�Ľṹ 

static GLuint	base;			// Base Display List For The Font Set



//=======================FUNCTION DECLARATION=================
//�����߼���ɫ��
static GLvoid	SetLogicalPalette();
//�������ظ�ʽ
static BOOL		SetupPixelFormat();
//��ʼ��openGL����
#ifdef __AFX_H__
static BOOL	InitializeOpenGL(CDC* pDC);
#else
static BOOL	InitializeOpenGL(HDC hdc);
#endif

//
static GLvoid DeleteOpenGL();
//RGBתGLCOLOR
static GLCOLOR	RGBToGLColor(COLORREF color);
//���ñ���ɫ
static GLvoid	SetBGColor(COLORREF color);
//Բ����
static GLvoid drawArc(double x,double y,double start_angle,double end_angle,double delta_angle,double radius);
//Բ��
static GLvoid drawCircle(double x, double y, double radius) ;
//pie��
static GLvoid drawPie(double x,double y,double start_angle,double end_angle,double delta_angle,double radius) ;
//Բ����
static GLvoid drawTorus(double x,double y,double radius,int numc, int numt);
//��������
static GLvoid BuildFont(int fontHeight);
//ɾ������
static GLvoid KillFont(GLvoid);
//����ı� 
static GLvoid glPrint(char Text[]);   


//=====================FUNCTION IMPLEMENTATION================
/////////////////////////////////////////////////////////////////////
//	                  �����߼���ɫ��
//////////////////////////////////////////////////////////////////////
GLvoid SetLogicalPalette(GLvoid)
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
//						�������ظ�ʽ
//////////////////////////////////////////////////////////
BOOL SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
		1,                                // �汾�� 
		/*PFD_DRAW_TO_WINDOW */
		PFD_DRAW_TO_BITMAP |              // ֧���ڴ����л�ͼ 
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
	pixelformat = ::ChoosePixelFormat(hDC, &pfd);//ѡ�����ظ�ʽ
	::SetPixelFormat(hDC, pixelformat, &pfd);	//�������ظ�ʽ
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//�����߼���ɫ��
	return TRUE;
}

//////////////////////////////////////////////////////////
//						��ʼ��openGL����
//////////////////////////////////////////////////////////
#ifdef __AFX_H__
BOOL InitializeOpenGL(CDC* pDC)
{
	hDC=pDC->GetSafeHdc();
	SetupPixelFormat();
	//���ɻ���������
	m_hRC = ::wglCreateContext(hDC);
	//�õ�ǰ����������
	::wglMakeCurrent(hDC, m_hRC);	  

	return TRUE;
}
#else
BOOL InitializeOpenGL(HDC hdc)
{
	hDC=hdc;
	SetupPixelFormat();
	//���ɻ���������
	m_hRC = ::wglCreateContext(hDC);
	//�õ�ǰ����������
	::wglMakeCurrent(hDC, m_hRC);	  

	return TRUE;
}
#endif // _DEBUG

GLvoid DeleteOpenGL()
{
	//ɾ����ɫ�����Ⱦ������
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
		DeleteObject(m_hPalette);
}

GLvoid SetBGColor(COLORREF color)
{
	GLCOLOR gc=RGBToGLColor(color);

	::glClearColor(gc.R , gc.G, gc.B, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
}

GLCOLOR RGBToGLColor(COLORREF color)
{
	GLCOLOR gc;
	gc.R=(color&0x000000FF)/255.0f;
	gc.G=((color&0x0000FF00)>>8)/255.0f;
	gc.B=((color&0x00FF0000)>>16)/255.0f;

	return gc;
}

GLvoid drawArc(double x,double y,double start_angle,double end_angle,double delta_angle,double radius) 
{  
	glBegin(GL_TRIANGLE_FAN);  
	for (double i=start_angle;i<=end_angle;i+=delta_angle)  
	{  
		double vx=x+radius * cos(i);  
		double vy=y+radius*sin(i);  
		glVertex2d(vx,vy);  
	}  
	glEnd();  
}  

GLvoid drawCircle(double x, double y, double radius)  
{	 
	drawArc(x,y,0,2*PI,PI/180,radius);  
}  

GLvoid drawPie(double x,double y,double start_angle,double end_angle,double delta_angle,double radius)  
{  
	drawArc(x,y,start_angle,end_angle,delta_angle,radius);  
	glBegin(GL_TRIANGLE_STRIP);  
	glVertex2d(x,y);  
	glVertex2d(x+radius*cos(start_angle),y+radius*sin(start_angle));  
	glVertex2d(x+radius*cos(end_angle),y+radius*sin(end_angle));  
	glEnd();  
}

GLvoid drawTorus(double x,double y,double radius,int numc, int numt)  
{  
	double s, t, vx, vy, vz, twoPI;  
	twoPI = 2 * PI;  
	for (int i = 0; i < numc; i++) {  
		glBegin(GL_QUAD_STRIP);  
		for (int j = 0; j <= numt; j++) {  
			for (int k = 1; k >= 0; k--) {  
				s = (i + k) % numc + 0.5;  
				t = j % numt;  

				vx = (1+.1*cos(s*twoPI/numc))*cos(t*twoPI/numt)*radius+x;  
				vy = (1+.1*cos(s*twoPI/numc))*sin(t*twoPI/numt)*radius+y;  
				vz =0;// .1 * sin(s * twoPI / numc);  
				glVertex3f(vx, vy, vz);  
			}  
		}  
		glEnd();  
	}  
}

GLvoid BuildFont(int fontHeight)   
{   
  /*  HFONT font;                       // Windows Font ID  
  //  HFONT oldfont;                    // Used For Good House Keeping  
  
    base = glGenLists(96);                  // Storage For 96 Characters ( NEW )  
    font = CreateFont(  fontHeight,             // Height Of Font ( NEW )�����С  
                        0,              // Width Of Font  
                        0,              // Angle Of Escapement  
                        0,              // Orientation Angle  
                        FW_BOLD,            // Font Weight  
                        FALSE,              // Italic  
                        FALSE,              // Underline  
                        FALSE,              // Strikeout  
                        ANSI_CHARSET,           // Character Set Identifier  
                        OUT_TT_PRECIS,          // Output Precision  
                        CLIP_DEFAULT_PRECIS,        // Clipping Precision  
                        ANTIALIASED_QUALITY,        // Output Quality  
                        FF_DONTCARE|DEFAULT_PITCH,  // Family And Pitch  
                        "Times New Roman");         // Font Name  
  
/*  oldfont = (HFONT)SelectObject(m_pDC->GetSafeHdc(), font);        // Selects The Font We Want  
    wglUseFontBitmaps(m_pDC->GetSafeHdc(), 32, 96, base);            // Builds 96 Characters Starting At Character 32  
    SelectObject(m_pDC->GetSafeHdc(), oldfont);              // Selects The Font We Want  
    DeleteObject(font);                 // Delete The Font*/   
/*  SelectObject(m_pDC->GetSafeHdc(), font);             // Selects The Font We Created  
    wglUseFontOutlines( m_pDC->GetSafeHdc(),             // Select The Current DC  
                32,             // Starting Character  
                96,             // Number Of Display Lists To Build  
                base,               // Starting Display Lists  
                0.0f,               // Deviation From The True Outlines  
                0.0f,               // Font Thickness In The Z Direction  
                WGL_FONT_POLYGONS,      // Use Polygons, Not Lines  
                gmf);               // Address Of Buffer To Recieve Data*/   
    memset(&lf,0,sizeof(LOGFONT));//����ڴ�   
   
    //�趨�߼�����lf������   
   
    lf.lfHeight=-1;//ָ���ָ�   
   
    lf.lfWidth = -1 ;//ָ���ֿ�    
   
    lf.lfEscapement = 0 ; //ָ���Ƕ�(1/10��)   
   
    lf.lfOrientation = 0 ; //ָ���ַ��Ļ�����x��ĽǶ�(1/10��)   
   
    lf.lfWeight = FW_BOLD ; //ָ�����������(FW_BOLD=700)   
   
    lf.lfItalic = FALSE ;//ָ���Ƿ�б��    
   
    lf.lfUnderline = FALSE ; //ָ���Ƿ����»���   
   
    lf.lfStrikeOut = FALSE ; //ָ���Ƿ���StrikeOut����   
   
    lf.lfCharSet = ANSI_CHARSET ; //ָ���ַ���   
   
    lf.lfOutPrecision = OUT_TT_PRECIS ; //ָ���������   
   
    lf.lfClipPrecision= CLIP_DEFAULT_PRECIS ; //ָ���ü�����   
   
    lf.lfQuality = PROOF_QUALITY ;//ָ���������    
   
    lf.lfPitchAndFamily = VARIABLE_PITCH | TMPF_TRUETYPE | FF_MODERN ; //ָ������Ķ�λ�����   
   
    lstrcpy (lf.lfFaceName, "����") ; //ָ����������   
   
    hFont=CreateFontIndirect(&lf);//�����߼�����

    SelectObject(wglGetCurrentDC(), hFont);//���߼�����ѡ���豸����    
}   
   
GLvoid KillFont(GLvoid)   
{   
    glDeleteLists(base, 96);                // Delete All 96 Characters ( NEW )     
}   
   
GLvoid glPrint(char Text[])   //����ı�   
{
	DWORD dwChar;
	int ListNum;
	for(size_t i=0;i<strlen((char *)Text);i++)
	{
		if(IsDBCSLeadByte(Text[i]))
		{
			dwChar=(DWORD)((Text[i]<<8)+256+Text[i+1]);
			i++;
		}
		else
		{
			dwChar=Text[i];
		}
		ListNum=glGenLists(1);
		BOOL ret=wglUseFontOutlines(/*hDC*/wglGetCurrentDC(),dwChar,1,ListNum,0.0,0.0f,WGL_FONT_POLYGONS,gmf);
		DWORD err=GetLastError();
		glCallList(ListNum);
		glDeleteLists(ListNum,1);
	}
} 