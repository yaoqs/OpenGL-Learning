//=========================================================================
/**
*  @file  Example.cpp
*
*  ��Ŀ������ OpenGL��ʾ����
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-24
*
*  ����������������������¼����麯��
*																								
*	virtual bool Init();														
*		ִ�����еĳ�ʼ������������ɹ���������true							
*																			
*	virtual void Uninit();													
*		ִ�����е�ж�ع���										
*																			
*	virtual void Update(DWORD milliseconds);										
*		ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ
*																			
*	virtual void Draw();															
*		ִ�����еĻ��Ʋ���
*/
//=========================================================================

#include "Example.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>	 
#include <math.h>                                              /**< ����math.hͷ�ļ� */                                             


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Example * example = new Example(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** ���캯�� */
Example::Example(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	rot = 0.0;
}

/** ��ʼ��OpenGL */
bool Example::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	///��ʼ������
	if(!font.InitFont())
	   return false;
  	return true;										/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Example::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

/** ������º��� */
void Example::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

	///if (m_Keys.IsPressed(VK_F1) == true)						/**< ��F1�л�����/ȫ��ģʽ */
	///{
	///	ToggleFullscreen();										
	///}
 /** �û��Զ���ĸ��¹��� */
	rot += milliseconds/5.0;
	    
}

/** ���ƺ���// */
void Example::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< ������� */		
	glLoadIdentity();	
    /** ���ƹ��� */	
	glColor3f(1.0f,0.0f,1.0f);                 /**< ָ����ɫ */
	font.PrintText("OpenGL��ʾ����",-3.0f,2.0f); /**<����ָ��λ������ַ��� */
	/** ������庺�� */
	glColor3f(0.5f,1.0f,0.5f);       /**< ָ����ɫ */
	glTranslatef(-3.0f,0.0f,-10.0f); /**< ָ��λ�� */
	glRotatef(rot,1.0,0.0,0.0);      /**< ��ת */
	font.Print3DText("��������",0.2f); /**< ���,���Ϊ0.2 */
		
    glFlush();				           /**< ǿ��ִ�����е�OpenGL���� */
}
