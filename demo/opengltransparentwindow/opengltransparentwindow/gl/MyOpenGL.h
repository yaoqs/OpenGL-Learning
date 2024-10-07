#pragma  once

#pragma comment( user, "ComPIled on " __DATE__ " at " __TIME__ ) 



//===================INCLUDE File && LIB Path==================
#include <math.h>

// 包含有关OpenGL函数的头文件
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

#define DEG2RAD(angle)			((angle) * (PI / 180))	// 将角度转换为弧度

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
static HGLRC	m_hRC;			//OpenGL绘制描述表
static HPALETTE	m_hPalette;		//OpenGL调色板
static HDC		hDC;			//OpenGL设备描述表
//==font==
static int fontHeight;  //显示字体大小 
static HFONT hFont;//字体句柄 
static LOGFONT lf;//逻辑字体 
static GLYPHMETRICSFLOAT gmf[128];//包括字形的位置和方向信息的结构 

static GLuint	base;			// Base Display List For The Font Set



//=======================FUNCTION DECLARATION=================
//设置逻辑调色板
static GLvoid	SetLogicalPalette();
//设置像素格式
static BOOL		SetupPixelFormat();
//初始化openGL场景
#ifdef __AFX_H__
static BOOL	InitializeOpenGL(CDC* pDC);
#else
static BOOL	InitializeOpenGL(HDC hdc);
#endif

//
static GLvoid DeleteOpenGL();
//RGB转GLCOLOR
static GLCOLOR	RGBToGLColor(COLORREF color);
//设置背景色
static GLvoid	SetBGColor(COLORREF color);
//圆弧面
static GLvoid drawArc(double x,double y,double start_angle,double end_angle,double delta_angle,double radius);
//圆面
static GLvoid drawCircle(double x, double y, double radius) ;
//pie面
static GLvoid drawPie(double x,double y,double start_angle,double end_angle,double delta_angle,double radius) ;
//圆环面
static GLvoid drawTorus(double x,double y,double radius,int numc, int numt);
//创建字体
static GLvoid BuildFont(int fontHeight);
//删除字体
static GLvoid KillFont(GLvoid);
//输出文本 
static GLvoid glPrint(char Text[]);   


//=====================FUNCTION IMPLEMENTATION================
/////////////////////////////////////////////////////////////////////
//	                  设置逻辑调色板
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
//						设置像素格式
//////////////////////////////////////////////////////////
BOOL SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
		1,                                // 版本号 
		/*PFD_DRAW_TO_WINDOW */
		PFD_DRAW_TO_BITMAP |              // 支持在窗口中绘图 
		PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
		PFD_DOUBLEBUFFER,                 // 双缓存模式 
		PFD_TYPE_RGBA,                    // RGBA 颜色模式 
		24,                               // 24 位颜色深度 
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
		0,                                // 没有非透明度缓存 
		0,                                // 忽略移位位 
		0,                                // 无累加缓存 
		0, 0, 0, 0,                       // 忽略累加位 
		32,                               // 32 位深度缓存     
		0,                                // 无模板缓存 
		0,                                // 无辅助缓存 
		PFD_MAIN_PLANE,                   // 主层 
		0,                                // 保留 
		0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(hDC, &pfd);//选择像素格式
	::SetPixelFormat(hDC, pixelformat, &pfd);	//设置像素格式
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//设置逻辑调色板
	return TRUE;
}

//////////////////////////////////////////////////////////
//						初始化openGL场景
//////////////////////////////////////////////////////////
#ifdef __AFX_H__
BOOL InitializeOpenGL(CDC* pDC)
{
	hDC=pDC->GetSafeHdc();
	SetupPixelFormat();
	//生成绘制描述表
	m_hRC = ::wglCreateContext(hDC);
	//置当前绘制描述表
	::wglMakeCurrent(hDC, m_hRC);	  

	return TRUE;
}
#else
BOOL InitializeOpenGL(HDC hdc)
{
	hDC=hdc;
	SetupPixelFormat();
	//生成绘制描述表
	m_hRC = ::wglCreateContext(hDC);
	//置当前绘制描述表
	::wglMakeCurrent(hDC, m_hRC);	  

	return TRUE;
}
#endif // _DEBUG

GLvoid DeleteOpenGL()
{
	//删除调色板和渲染上下文
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
    font = CreateFont(  fontHeight,             // Height Of Font ( NEW )字体大小  
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
    memset(&lf,0,sizeof(LOGFONT));//清空内存   
   
    //设定逻辑字体lf的属性   
   
    lf.lfHeight=-1;//指定字高   
   
    lf.lfWidth = -1 ;//指定字宽    
   
    lf.lfEscapement = 0 ; //指定角度(1/10度)   
   
    lf.lfOrientation = 0 ; //指定字符的基线与x轴的角度(1/10度)   
   
    lf.lfWeight = FW_BOLD ; //指定字体的重量(FW_BOLD=700)   
   
    lf.lfItalic = FALSE ;//指定是否斜体    
   
    lf.lfUnderline = FALSE ; //指定是否有下划线   
   
    lf.lfStrikeOut = FALSE ; //指定是否是StrikeOut字体   
   
    lf.lfCharSet = ANSI_CHARSET ; //指定字符集   
   
    lf.lfOutPrecision = OUT_TT_PRECIS ; //指定输出精度   
   
    lf.lfClipPrecision= CLIP_DEFAULT_PRECIS ; //指定裁剪精度   
   
    lf.lfQuality = PROOF_QUALITY ;//指定输出质量    
   
    lf.lfPitchAndFamily = VARIABLE_PITCH | TMPF_TRUETYPE | FF_MODERN ; //指定字体的定位和外观   
   
    lstrcpy (lf.lfFaceName, "宋体") ; //指定字体名称   
   
    hFont=CreateFontIndirect(&lf);//创建逻辑字体

    SelectObject(wglGetCurrentDC(), hFont);//将逻辑字体选入设备环境    
}   
   
GLvoid KillFont(GLvoid)   
{   
    glDeleteLists(base, 96);                // Delete All 96 Characters ( NEW )     
}   
   
GLvoid glPrint(char Text[])   //输出文本   
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