//=========================================================================
/**
*  @file      Bezier.cpp
*
*  ��Ŀ������ ��������
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-04
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

#include "Bezier.h"											    /**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>	 
                                      
#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

/** ���Ƶ����� */
GLfloat points[4][3] = {
	   { -4.0f,  -2.0f,  0.0f }, { -2.0f,  3.0f,  2.0f},
       {  2.0f,  -3.0f, -2.0f }, {  4.0f,  2.0f,  0.0f}};


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Bezier * bezier = new Bezier(class_name);
	return reinterpret_cast<GLApplication *>(bezier);
}


/** ���캯�� */
Bezier::Bezier(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	
}


/** ��ʼ��OpenGL */
bool Bezier::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
    
	/**���ò�����һά��ֵ����  */
	glEnable(GL_MAP1_VERTEX_3);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &points[0][0]);
 	
	ResizeDraw(true);									/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

  	return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Bezier::Uninit()									
{
	
}

/** ������º��� */
void Bezier::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)  /**< ��ESC�˳� */
	{
		TerminateApplication();									
	}
/** �û��Զ���ĸ��¹��� */
	    
}

/** ���ƺ��� */
void Bezier::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	  /**< ������� */		
	glLoadIdentity();	
    
	/** ���ƹ��� */
	glTranslatef(0.0f,0.0f,-13.0f);
	glBegin(GL_LINE_STRIP);
	for( int i = 0; i < 100; i++)
	{
		/** ִ����ֵ���� */
		glEvalCoord1f((float)i / 100.0f); 
	}
	glEnd();
    
	/** ���ƿ��Ƶ� */
	glPointSize(4.0);            /**< ���õ�Ĵ�С */
    
	glBegin(GL_POINTS);
	for(int j = 0; j < 4; j++)
		glVertex3fv(&points[j][0]);
    glEnd();

	glFlush();				      /**< ǿ��ִ�����е�OpenGL���� */
}
