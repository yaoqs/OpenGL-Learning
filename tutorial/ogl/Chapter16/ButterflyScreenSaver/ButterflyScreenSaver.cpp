
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>	
#include <gl\gl.h>
#include <gl\glu.h>	
#include <scrnsave.h>
#include "resource.h"

GLuint texture[3];

HDC				hDC=NULL;
HGLRC			hRC=NULL;
HWND			hWnd=NULL;	
HINSTANCE		hInstance;

DEVMODE			DMsaved;
UINT			uTimer;	

struct object						// 定义一个对象结构体（蝴蝶）
{
	int   tex;						// 纹理ID
	float x;						// X 坐标
	float y;						// Y 坐标
	float z;						// Z 坐标
	float yi;						// Y 速度
	float spinz;					// Z 轴旋转
	float spinzi;					// Z 轴旋转速度
	float flap;						// 翼拍打的面片，用于绘制
	float fi;						// 翼拍打的方向
};

object obj[50];						// 创建50个对象

void SetObject(int loop)			// 设置对象的初始属性(随机)
{
	obj[loop].tex=rand()%3;	
	obj[loop].x=rand()%34-17.0f;
	obj[loop].y=18.0f;	
	obj[loop].z=-((rand()%30000/1000.0f)+10.0f);
	obj[loop].spinzi=(rand()%10000)/5000.0f-1.0f;
	obj[loop].flap=0.0f;	
	obj[loop].fi=0.05f+(rand()%100)/1000.0f;
	obj[loop].yi=0.001f+(rand()%1000)/10000.0f;	
}

void LoadGLTextures()				// 生成纹理ID
{
	HBITMAP hBMP;	
	BITMAP	BMP;

	byte	Texture[]={	IDB_BUTTERFLY1,	IDB_BUTTERFLY2,	IDB_BUTTERFLY3 };

	glGenTextures(sizeof(Texture), &texture[0]);
	for (int loop=0; loop<sizeof(Texture); loop++)	
	{
		hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(Texture[loop]), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
		if (hBMP)		
		{										
			GetObject(hBMP,sizeof(BMP), &BMP);
			glPixelStorei(GL_UNPACK_ALIGNMENT,4);
			glBindTexture(GL_TEXTURE_2D, texture[loop]);					// 捆绑纹理
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// 线性过滤
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
		}
	}
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// 缩放OpenGL窗口
{
	if (height==0)		
	{
		height=1;	
	}

	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective (45.0f, (GLfloat)(width)/(GLfloat)(height),1.0f, 1000.0f);		
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
}

int InitGL(GLvoid)											// 初始化OpenGL
{
	LoadGLTextures();										// 装入纹理
	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);					// 黑色背景
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glDisable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glEnable(GL_TEXTURE_2D);								// 2D纹理映射
	glBlendFunc(GL_ONE,GL_SRC_ALPHA);	
	glEnable(GL_BLEND);
	
	for (int loop=0; loop<50; loop++)	
	{
		SetObject(loop);									// 生成50个对象
	}
	return TRUE;
}

int DrawGLScene(GLvoid)	            // 绘制场景
{								
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// 清除屏幕和深度缓存
	for (int loop=0; loop<50; loop++)							// 绘制50个对象（蝴蝶）
	{
		glLoadIdentity ();	
		glBindTexture(GL_TEXTURE_2D, texture[obj[loop].tex]);	// 捆绑纹理
		glTranslatef(obj[loop].x,obj[loop].y,obj[loop].z);		// 对象位置
		glRotatef(45.0f,1.0f,0.0f,0.0f);						// 绕X-Axis旋转
		glRotatef((obj[loop].spinz),0.0f,0.0f,1.0f);			// 绕Z-Axis旋转

		glBegin(GL_TRIANGLES);									// 绘制三角形
			// 第一个三角形		
			glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);	
			glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, 1.0f, obj[loop].flap);
			glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);	

			// 第二个三角形
			glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);	
			glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);	
			glTexCoord2f(1.0f,0.0f); glVertex3f( 1.0f,-1.0f, obj[loop].flap);

		glEnd();	

		obj[loop].y-=obj[loop].yi;		
		obj[loop].spinz+=obj[loop].spinzi;	
		obj[loop].flap+=obj[loop].fi;	

		if (obj[loop].y<-18.0f)	
		{
			SetObject(loop);	
		}

		if ((obj[loop].flap>1.0f) || (obj[loop].flap<-1.0f))
		{
			obj[loop].fi=-obj[loop].fi;			
		}
	}
	Sleep(15);			
	glFlush ();	
	return TRUE;
}

GLvoid KillGLWindow(GLvoid)	
{
	if (hRC)											// 如果渲染上下文存在
	{
		if (!wglMakeCurrent(NULL,NULL))					// 渲染上下文设置为空
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// 删除渲染上下文RC
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// 释放DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;
	}
}

BOOL CreateGLWindow(HWND hWnd, int bits)
{
	GLuint		PixelFormat;
	RECT		WindowRect;	
	int width;
	int height;

	hInstance			= GetModuleHandle(NULL);				// 获得窗口句柄

	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &DMsaved); // 保存当前的显示状态

	static	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	    1,                                // 版本号 
	    PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
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
	
	if (!(hDC=GetDC(hWnd)))							// 获得设备上下文
	{
		KillGLWindow();							
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// 返回FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// 选择合适的像素格式
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// 返回FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// 设置像素格式
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// 返回FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// 获取绘制上下文
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// 返回FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// 激活绘制上下文
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// 返回FALSE
	}

    GetClientRect (hWnd, &WindowRect); 
	
	width = WindowRect.right - WindowRect.left;
	height = WindowRect.bottom - WindowRect.top;
	ReSizeGLScene(width, height);


    if (!InitGL())									// 初始化OpenGL窗口
	{
		KillGLWindow();	
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// 出错，返回FALSE
	}

	return TRUE;									// 成功，返回Success
}

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, 
					 WPARAM wParam, LPARAM lParam) 
{

	switch (message)								// 检查Windows消息
	{
        case WM_CREATE:
		{
			if (!CreateGLWindow(hWnd,16))
			{
				return -1;									
			}
            uTimer = SetTimer(hWnd, 1, 10, NULL); 
			return 0;
		}

        case WM_TIMER: 
			DrawGLScene();                      
			SwapBuffers(hDC);					
			break;

        case WM_DESTROY: 
            if (uTimer) 
                KillTimer(hWnd, uTimer); 
			KillGLWindow();									
			glDeleteTextures(3,texture);
            break; 
	}

    return DefScreenSaverProc(hWnd, message, wParam, lParam); 
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, 
								WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, TRUE);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
	return TRUE;
}

