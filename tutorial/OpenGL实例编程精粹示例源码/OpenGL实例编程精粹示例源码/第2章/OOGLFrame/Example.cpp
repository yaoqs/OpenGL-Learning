//=========================================================================
/**
*  @file  Example.cpp
*
*  ��Ŀ������ ʹ��OO��OpenGL��������ʾ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-10-10
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
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
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

	return true;												/**< �ɹ����� */
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

	if (m_Keys.IsPressed(VK_F1) == true)						/**< ��F1�л�����/ȫ��ģʽ */
	{
		ToggleFullscreen();										
	}
/** �û��Զ���ĸ��¹��� */
	m_Angle += (float)(milliseconds) / 15.0f;					/**< ������ת�ĽǶ� */
     
}

/** ���ƺ��� */
void Example::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();											
	glTranslatef(0.0f, 0.0f, -6.0f);							
	glRotatef(m_Angle, 0.0f, 1.0f, 0.0f);						
	glRotatef(m_Angle * 0.7f, -1.0f, 0.0f, 0.0f);				

	for (int rot1 = 0; rot1 < 2; rot1++)						/**< �����ĸ�����������Σ���ĺ������*/
	{
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);						
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);					
		for (int rot2 = 0; rot2 < 2; rot2++)					
		{
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);				
			glBegin(GL_TRIANGLES);								
				glColor3f(1.f, 0.f, 0.f);	glVertex3f( 0.0f,  1.0f, 0.0f);
				glColor3f(0.f, 1.f, 0.f);	glVertex3f(-1.0f, -1.0f, 1.0f);
				glColor3f(0.f, 0.f, 1.f);	glVertex3f( 1.0f, -1.0f, 1.0f);
			glEnd();											
		}
	}
	glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
