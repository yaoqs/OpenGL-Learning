//=========================================================================
/**
*  @file  BasciGraphics.cpp
*
*  ��Ŀ������ OpenGL����ͼ�εĻ���
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-10-13	
*  �޸����ڣ� 2006-11-10
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

#include <cmath>                                                /**< ����mathͷ�ļ� */
#include "BasicGraphics.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	BasicGraphics * basic = new BasicGraphics(class_name);
	return reinterpret_cast<GLApplication *>(basic);
}


/** ���캯�� */
BasicGraphics::BasicGraphics(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
	
}

/** ��ʼ��OpenGL */
bool BasicGraphics::Init()									
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
void BasicGraphics::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

/** ������º��� */
void BasicGraphics::Update(DWORD milliseconds)						
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
	m_Angle += (float)(milliseconds) /15.0f;					/**< ������ת�ĽǶ� */

	if(m_Angle > 360.0f)
		m_Angle = 0.0f;
	

     
}

/** ���ƺ��� */
void BasicGraphics::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/**< �����ɫ�������Ȼ��� */		
	glLoadIdentity();
	/** ���� */
	glPushMatrix();
		glTranslatef(-1.5f, 1.0f, -6.0f);
		glScalef(0.75f, 0.75f, 0.75f);
		glRotatef(m_Angle, 1.0f, 1.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 0.0f);							
		glBegin(GL_LINE_LOOP); /**< ���Ʊպ��߶� */
			glVertex3f( 0.0f, 1.0f,-0.0f); /**< ��һ����a */ 
			glVertex3f(-1.0f,-1.0f, 0.0f); /**< �ڶ�����b */ 
			glVertex3f( 1.0f,-1.0f, 0.0f); /**< ��������c */ 
		glEnd();
	glPopMatrix();

	/** ��Բ */
	glPushMatrix();	
		glTranslatef(1.5f, 1.0f, -6.0f);
		glScalef(0.75f,0.75f,0.75f);
		glRotatef(m_Angle,1.0f,1.0f,1.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLE_FAN); /**< ������������ */
			glVertex3f(0,0,0.0f );   
			for ( int i = 0; i <= 370; i += 10)
			{
				float p = (float)(i * 3.14 / 180);
				glVertex3f((float)sin(p), (float)cos(p), 0.0f );
			}
		glEnd();
	glPopMatrix();
	/** �������� */
	glPushMatrix();	
		glTranslatef(-1.5f, -1.0f, -6.0f);
		glScalef(0.75f,0.75f,0.75f);
		glRotatef(m_Angle,1.0f,1.0f,1.0f);
		glColor3f(0.0f, 1.0f, 1.0f);							
		glBegin(GL_TRIANGLES);	/**< ���������� */							
			glVertex3f( 0.0f,  1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f( 1.0f, -1.0f, 0.0f);
		glEnd();
    glPopMatrix();
	/** �������� */
	glPushMatrix();
		glTranslatef(1.5f,-1.0f,-6.0f);
		glScalef(0.75f,0.75f,0.75f);
		glRotatef(m_Angle,1.0f,1.0f,1.0f);
		glColor3f(1.f, 1.f, 0.f);
		glBegin(GL_QUADS);	/**< �����ı��� */
			glVertex3f(-1.0f, 1.0f, 0.0f);	/**< ���� */
			glVertex3f( 1.0f, 1.0f, 0.0f);	/**< ���� */				
			glVertex3f( 1.0f,-1.0f, 0.0f);	/**< ���� */				
			glVertex3f(-1.0f,-1.0f, 0.0f);	/**< ���� */				
		glEnd();					
	 glPopMatrix(); 

    glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
