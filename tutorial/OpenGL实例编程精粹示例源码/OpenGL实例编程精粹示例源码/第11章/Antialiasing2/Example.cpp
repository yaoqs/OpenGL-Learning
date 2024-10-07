//=========================================================================
/**
*  @file  Example.cpp
*
*  ��Ŀ������ ����η�����
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-30
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
	rot = 0.0f;
}

/** ��ʼ��OpenGL */
bool Example::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
		
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_FLAT);

	glEnable(GL_POLYGON_SMOOTH);              /**< ��������η����� */
	glEnable(GL_BLEND);                       /**< ���û�� */
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);         /**< ָ��������� */
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);/**< ��Ϊ���� */
	
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

	///if (m_Keys.IsPressed(VK_F1) == true)						/**< ��F1�л�����/ȫ��ģʽ */
	///{
	///	ToggleFullscreen();										
	///}
/** �û��Զ���ĸ��¹��� */
     rot += milliseconds/50.0;
}

/** ���ƺ��� */
void Example::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
 	glDisable(GL_DEPTH_TEST);               /**< �ر���Ȳ��� */
	/** ���Ƶ�һ�������� */
	glPushMatrix();
	  glTranslatef(0.0f, 0.0f, -5.0f);      /**< ������Ļ 5����λ */
	  glRotatef(rot,1.0f,0.0f,1.0f);        /**< ��ת */
	  glColor4f(1.0f,0.0f,0.0f,0.5f);       /**< ָ����ɫ */
	  glBegin(GL_TRIANGLES);	            /**< ���������� */
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);	
	  glEnd();
	glPopMatrix();
	/** ���Ƶڶ��������� */
	glPushMatrix();
	  glTranslatef(0.0f, 0.0f, -5.0f);      /**< ������Ļ 5����λ */
      glRotatef(-rot,1.0f,0.0f,1.0f);       /**< ��ת */
	  glColor4f(0.0f,1.0f,0.0f,0.5f);       /**< ָ����ɫ */
	  glBegin(GL_TRIANGLES);	            /**< ���������� */							
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);	
		glVertex3f( 1.0f,-1.0f, -1.0f);
	glEnd();
    glPopMatrix();
   	glEnable(GL_DEPTH_TEST);              /** ������Ȳ��� */
	
   	glFlush();							  /**< ǿ��ִ�����е�OpenGL���� */
}
