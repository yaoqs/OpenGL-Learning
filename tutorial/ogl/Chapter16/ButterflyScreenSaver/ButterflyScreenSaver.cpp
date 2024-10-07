
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

struct object						// ����һ������ṹ�壨������
{
	int   tex;						// ����ID
	float x;						// X ����
	float y;						// Y ����
	float z;						// Z ����
	float yi;						// Y �ٶ�
	float spinz;					// Z ����ת
	float spinzi;					// Z ����ת�ٶ�
	float flap;						// ���Ĵ����Ƭ�����ڻ���
	float fi;						// ���Ĵ�ķ���
};

object obj[50];						// ����50������

void SetObject(int loop)			// ���ö���ĳ�ʼ����(���)
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

void LoadGLTextures()				// ��������ID
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
			glBindTexture(GL_TEXTURE_2D, texture[loop]);					// ��������
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// ���Թ���
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
		}
	}
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// ����OpenGL����
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

int InitGL(GLvoid)											// ��ʼ��OpenGL
{
	LoadGLTextures();										// װ������
	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);					// ��ɫ����
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glDisable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glEnable(GL_TEXTURE_2D);								// 2D����ӳ��
	glBlendFunc(GL_ONE,GL_SRC_ALPHA);	
	glEnable(GL_BLEND);
	
	for (int loop=0; loop<50; loop++)	
	{
		SetObject(loop);									// ����50������
	}
	return TRUE;
}

int DrawGLScene(GLvoid)	            // ���Ƴ���
{								
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// �����Ļ����Ȼ���
	for (int loop=0; loop<50; loop++)							// ����50�����󣨺�����
	{
		glLoadIdentity ();	
		glBindTexture(GL_TEXTURE_2D, texture[obj[loop].tex]);	// ��������
		glTranslatef(obj[loop].x,obj[loop].y,obj[loop].z);		// ����λ��
		glRotatef(45.0f,1.0f,0.0f,0.0f);						// ��X-Axis��ת
		glRotatef((obj[loop].spinz),0.0f,0.0f,1.0f);			// ��Z-Axis��ת

		glBegin(GL_TRIANGLES);									// ����������
			// ��һ��������		
			glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);	
			glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, 1.0f, obj[loop].flap);
			glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);	

			// �ڶ���������
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
	if (hRC)											// �����Ⱦ�����Ĵ���
	{
		if (!wglMakeCurrent(NULL,NULL))					// ��Ⱦ����������Ϊ��
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// ɾ����Ⱦ������RC
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// �ͷ�DC
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

	hInstance			= GetModuleHandle(NULL);				// ��ô��ھ��

	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &DMsaved); // ���浱ǰ����ʾ״̬

	static	PIXELFORMATDESCRIPTOR pfd = { 
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
	
	if (!(hDC=GetDC(hWnd)))							// ����豸������
	{
		KillGLWindow();							
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ����FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// ѡ����ʵ����ظ�ʽ
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ����FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// �������ظ�ʽ
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ����FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// ��ȡ����������
	{
		KillGLWindow();	
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ����FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// �������������
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ����FALSE
	}

    GetClientRect (hWnd, &WindowRect); 
	
	width = WindowRect.right - WindowRect.left;
	height = WindowRect.bottom - WindowRect.top;
	ReSizeGLScene(width, height);


    if (!InitGL())									// ��ʼ��OpenGL����
	{
		KillGLWindow();	
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ��������FALSE
	}

	return TRUE;									// �ɹ�������Success
}

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, 
					 WPARAM wParam, LPARAM lParam) 
{

	switch (message)								// ���Windows��Ϣ
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

