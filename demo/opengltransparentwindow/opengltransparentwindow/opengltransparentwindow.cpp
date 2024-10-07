// opengltransparentwindow.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "opengltransparentwindow.h"


#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

////////////////////
#ifndef _WIN32_WINNT
#define  _WIN32_WINNT 0x0500
#endif // !_WIN32_WINNT

#include <Windows.h>
#include <WindowsX.h>
#include "gl/GL.h"
#include "gl/GLU.h"
#include <math.h>

#pragma comment (lib,"gl/opengl32.lib")
#pragma comment (lib,"gl/glu32.lib")

const double PI=3.1415926154;
#define  _PI_

#include "gl/MyOpenGL.h"

#include <assert.h>
#include <tchar.h>

#ifdef assert
#define verify(expr) if(!expr) assert(0)
#else verify(expr) expr
#endif

//HDC hDC;
HGLRC m_hrc;
int w(500);
int h(500);

HDC pdcDIB;
HBITMAP hbmpDIB;
void *bmp_cnt(NULL);
int cxDIB(0);
int cyDIB(0);

BITMAPINFOHEADER BIH;

int n(0);

void polarCoorCircle(float radius,float circlePointX,float circlrPointY)
{
	float i,n=360.0;
	float t=2*PI/n,x,y;
	glBegin(GL_LINE_LOOP);
	for (i=0.0;i<n;i+=0.2)
	{
		x=radius*sinf(t*i);
		y=radius*cosf(t*i);
		glVertex2f(circlePointX+x,circlrPointY+y);
	}
	glEnd();
}

BOOL initSC()
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0,0,0,1);

	BOOL ret=wglUseFontBitmaps(wglGetCurrentDC(),0,255,100);
	DWORD err=GetLastError();
	HDC hdc=wglGetCurrentDC();
	glListBase(100);
	
	KillFont();
	BuildFont(-14);
	return 0;
}

void resizeSC(int width,int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,width,0,height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

BOOL renderSC()
{
	glDrawBuffer(GL_BACK);
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(0.0,0.0,0.0,1.0);
	double tranx=0.0,trany=0.0,tranz=0.0;
	static double rotx=0.0,roty=0.0,rotz=0.0;

	//==========================4显示文本=========================
	int width4=cxDIB,height4=cyDIB;
	glViewport(0,90,width4,height4);
	glMatrixMode(GL_PROJECTION);// 选择投影矩阵   
	glLoadIdentity();// 重置投影矩阵   

	// 计算窗口的外观比例   
	//	gluPerspective(50.0,(GLfloat)width4/(GLfloat)height4,1.0f,100.0f);   

	//	glOrtho(0, 15,0, 15,1.0,1.0);
	if(cxDIB<=cyDIB)
		glOrtho(-200, 200,-200*(GLfloat)height4/(GLfloat)width4, 200,1.0,1.0);
	else
		glOrtho(-200, 200*(GLfloat)width4/(GLfloat)height4,-200, 200,1.0,1.0);

	glMatrixMode(GL_MODELVIEW);// 选择模型观察矩阵   
	glLoadIdentity();// 重置模型观察矩阵 
	/////////////////////////////////////////
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glFrontFace( GL_CCW );

	glLoadIdentity();
	glColor3ub(0,255,0);
	glTranslatef(0.1,0.0,0.0);
	glScalef(0.2f, 0.2f, 0.0f); 
	glPrint("你好");

	glLoadIdentity();
	glColor3f(0,1,1);
	glLineWidth(2);
	SYSTEMTIME ptime;
	GetLocalTime(&ptime);
	char buf[256]={0};
	wsprintf(buf,"%d-%d-%d %02d:%02d:%02d",ptime.wYear,ptime.wMonth,ptime.wDay,ptime.wHour,ptime.wMinute,ptime.wSecond);
	glTranslatef(-1,0.2,0.0);
	glScalef(0.2f, 0.2f, 0.2f); 
	glPrint(buf);

	rotz = -ptime.wSecond / 60.0 * 360 + 90;
	glLoadIdentity(); 
	glTranslatef(tranx,trany,tranz);   
	glRotatef(rotx,1.0f,0.0f,0.0f); // 在X轴上旋转立方体   
	glRotatef(roty,0.0f,1.0f,0.0f);   
	glRotatef(rotz,0.0f,0.0f,1.0f);
	

	glColor3ub(255,0,0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(0,0);
	glVertex2d(0.5,0);
	glEnd();

	rotz = -ptime.wMinute / 60.0 * 360 + 90;
	glLoadIdentity();// 重置投影矩阵 
	glTranslatef(tranx, trany, tranz);
	glRotatef(rotx, 1.0f, 0.0f, 0.0f); // 在X轴上旋转立方体   
	glRotatef(roty, 0.0f, 1.0f, 0.0f);
	glRotatef(rotz, 0.0f, 0.0f, 1.0f);
	
	glColor3ub(0, 255, 0);
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(0, 0);
	glVertex2d(0.3, 0);
	glEnd();
	
	rotz = -ptime.wHour / 24.0 * 360 + 90;
	glLoadIdentity();// 重置投影矩阵 
	glTranslatef(tranx, trany, tranz);
	glRotatef(rotx, 1.0f, 0.0f, 0.0f); // 在X轴上旋转立方体   
	glRotatef(roty, 0.0f, 1.0f, 0.0f);
	glRotatef(rotz, 0.0f, 0.0f, 1.0f);

	glColor3ub(0, 0, 255);
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(0, 0);
	glVertex2d(0.2, 0);
	glEnd();
	

	//////////////////////////////////
	glFlush(); 

	::SwapBuffers(hDC);		//交互缓冲区

	glDrawBuffer(GL_FRONT);

	return 0;
}

void draw(HDC pdcDest)
{
	assert(pdcDIB);
	verify(BitBlt(pdcDest,0,0,w,h,pdcDIB,0,0,SRCCOPY));
}

void CreateDIB(int cx,int cy)
{
	assert(cx>0);
	assert(cy>0);

	cxDIB=cx;
	cyDIB=cy;

	int iSize=sizeof(BITMAPINFOHEADER);
	memset(&BIH,0,iSize);

	BIH.biSize=iSize;
	BIH.biWidth=cx;
	BIH.biHeight=cy;
	BIH.biPlanes=1;
	BIH.biBitCount=24;
	BIH.biCompression=BI_RGB;

	if (pdcDIB)
	{
		verify(DeleteDC(pdcDIB));
	}

	pdcDIB=CreateCompatibleDC(NULL);
	assert(pdcDIB);

	if (hbmpDIB)
	{
		verify(DeleteObject(hbmpDIB));
	}

	hbmpDIB=CreateDIBSection(pdcDIB,(BITMAPINFO*)&BIH,DIB_RGB_COLORS,&bmp_cnt,NULL,0);
	assert(hbmpDIB);
	assert(bmp_cnt);

	if (hbmpDIB)
	{
		SelectObject(pdcDIB,hbmpDIB);
	}
}

BOOL CreateHGLRC()
{
	DWORD dwFlags=PFD_SUPPORT_OPENGL|PFD_DRAW_TO_BITMAP;

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion=1;
	pfd.dwFlags=dwFlags;
	pfd.iPixelType=PFD_TYPE_RGBA;
	pfd.cColorBits=24;
	pfd.cDepthBits=32;
	pfd.iLayerType=PFD_MAIN_PLANE;

	int PixelFormat=ChoosePixelFormat(pdcDIB,&pfd);
	if (PixelFormat==0)
	{
		assert(0);
		return FALSE;
	}

	BOOL bResult=SetPixelFormat(pdcDIB,PixelFormat,&pfd);
	if (bResult==FALSE)
	{
		assert(0);
		return FALSE;
	}

	m_hrc=wglCreateContext(pdcDIB);
	if (!m_hrc)
	{
		assert(0);
		return FALSE;
	}

	return TRUE;
}

BOOL CALLBACK enumUserWindowsCB(HWND hWnd, LPARAM lParam)
{
	long wflags = GetWindowLong(hWnd, GWL_STYLE);
	if(!(wflags & WS_VISIBLE)) return TRUE;

	HWND sndWnd;
	if( !(sndWnd=FindWindowEx(NULL, NULL,("Progman") , "Program Manager")) )
		return TRUE;
	HWND targetWnd;
	/*	if( !(targetWnd=FindWindowEx(sndWnd->GetSafeHwnd(), NULL, _T("WorkerW"),"")) )
		return TRUE;*/
	if( !(targetWnd=FindWindowEx(sndWnd, NULL, _T("SHELLDLL_DefView"),"")) )
		return TRUE;
	if( !(targetWnd=FindWindowEx(targetWnd, NULL, _T("SysListView32"), _T("FolderView"))) )
		return TRUE;
	/*if( !(targetWnd=FindWindowEx(targetWnd->GetSafeHwnd(), NULL, _T("SysHeader32"), "")) )
		return TRUE;*/

	HWND resultHwnd /*= (CWnd*)lParam*/;
	resultHwnd= targetWnd;
	HWND org((HWND)lParam);
	SetParent(org,targetWnd);
//	lParam=(LPARAM)targetWnd;	
	return FALSE;
}


HWND findDesktopIconWnd(HWND resultHwnd)
{
//	HWND resultHwnd=nullptr;
	BOOL ret=EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)resultHwnd);
	DWORD err=GetLastError();
	return resultHwnd;
}

////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OPENGLTRANSPARENTWINDOW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OPENGLTRANSPARENTWINDOW));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName	= 0;MAKEINTRESOURCE(IDC_OPENGLTRANSPARENTWINDOW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(NULL,IDI_APPLICATION);
	wcex.cbClsExtra=0;
	wcex.cbWndExtra=0;
	

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindowEx(WS_EX_LAYERED, szTitle, szWindowClass,
      WS_VISIBLE|WS_POPUP,200,200,w,h,
	  NULL,NULL,hInstance,NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   verify(SetLayeredWindowAttributes(hWnd,0x0,0,LWA_COLORKEY));

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
//	HDC hdc;

	switch (message)
	{
	/*case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;*/
	case WM_ERASEBKGND:
		return 0;
		break;
	case WM_CREATE:
		SetTimer(hWnd,1,500,NULL);
	//	findDesktopIconWnd(hWnd);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		
		renderSC();
		draw(hDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		if (m_hrc)
		{
			wglMakeCurrent(NULL,NULL);
			wglDeleteContext(m_hrc);
		}
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		w=LOWORD(lParam);
		h=HIWORD(lParam);
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(m_hrc);

		CreateDIB(w,h);
		CreateHGLRC();
		verify(wglMakeCurrent(pdcDIB,m_hrc));

		initSC();
		
	//	resizeSC(w,h);
		renderSC();

		break;
	case WM_TIMER:
		n++;
		RECT r;
		r.left=0;r.right=cxDIB;
		r.bottom=cyDIB;r.top=0;
		;InvalidateRect(hWnd,&r,FALSE);
		break;
	case WM_TIMECHANGE:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
