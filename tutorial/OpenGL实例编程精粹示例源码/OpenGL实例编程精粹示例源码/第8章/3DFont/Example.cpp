//=========================================================================
/**
*  @file  Example.cpp
*
*  ��Ŀ������ OpenGL3D������ʾ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-23
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

/** �����Դ������ */
///��Դ1
GLfloat ambient[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat diffuse[] = {0.0f,1.0f,1.0f,1.0f};
GLfloat specular[] = {0.0f,1.0f,1.0f,1.0f};
GLfloat position[] = {-1.0f,2.0f,-6.0f,1.0f};
/** ��Դ2 */
GLfloat ambient1[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat diffuse1[] = {0.5f,0.0f,0.5f,1.0f};
GLfloat specular1[] = {0.5f,0.0f,0.5f,1.0f};
GLfloat position1[] = {3.0f,0.0f,-1.0f,1.0f};

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
	cnt1 = 0.0;
	cnt2 = 0.0;
	rot = 0.0;
}

/** ��ʼ��OpenGL */
bool Example::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
    /** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,specular);
	//glLightfv(GL_LIGHT1,GL_POSITION,position);

	glLightfv(GL_LIGHT2,GL_AMBIENT,ambient1);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,diffuse1);
	glLightfv(GL_LIGHT2,GL_SPECULAR,specular1);
	glLightfv(GL_LIGHT2,GL_POSITION,position1);
	/** ������Դ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	///��ʼ������
	if(!font.InitFont(wglGetCurrentDC(),"Arial",60)) 
	   return false;
    
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

	cnt1 += milliseconds/1500.0;  /**< ���¼�����ֵ */
	cnt2 += milliseconds/1000.0;  /**< ���¼�����ֵ */
	rot += milliseconds/50.0;
	    
}

/** ���ƺ��� */
void Example::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< ������� */		
	glLoadIdentity();	
    ///�����ַ�����
	glTranslatef(0.0f, 0.0f, -10.0f); /**< ������Ļ */
	glRotatef(rot,1.0f,0.0f,0.0f);						/**< ��X����ת */
	glRotatef(rot*1.5f,0.0f,1.0f,0.0f);					/**< ��Y����ת */
    glLightfv(GL_LIGHT1,GL_POSITION,position);          /**< ָ����Դλ�ã����ӵ��ƶ� */
	glRotatef(rot*1.4f,0.0f,0.0f,1.0f);					/**< ��Z����ת */
	glScalef(1.0f,2.0f,1.0f);
	glColor3f(cos(cnt1),sin(cnt2),1.0f - 0.5f * cos(cnt1 + cnt2)); /**< ָ����ɫ */
    font.PrintText("Hello,OpenGL!",-3.5f + 2.0 * cos(cnt1), 3.5f * sin(cnt2)); /**< ���÷�������ַ��� */
	
    glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
