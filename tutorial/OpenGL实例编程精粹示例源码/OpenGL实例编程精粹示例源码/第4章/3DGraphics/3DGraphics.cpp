
//=========================================================================
/**
*  @file  3DGraphics.cpp
*
*  ��Ŀ������ 3Dͼ�εĻ���
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-10-13	
*  �޸����ڣ� 2006-11-13
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
#include "3DGraphics.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

/** ���峣��GL_PI */
static const GLfloat GL_PI = 3.14f;

/** �������� */
static GLfloat vertices[] = { 1.0f,1.0f,-1.0f, -1.0f,1.0f,-1.0f,
                              -1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,
						      1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,
							  -1.0f,-1.0f,-1.0f,1.0f,-1.0f,-1.0f};
/** ������ɫ���� */
static GLfloat colors[] = {1.f,0.f,0.f,0.f,1.f,0.f,
                          0.f,0.f,1.f,1.f,1.f,0.f,
						  1.f,0.f,1.f,0.f,1.f,1.f,
                          0.4f,0.6f,0.3f,0.f,0.8f,0.4f};
/** ������������ */
static GLbyte indexs[] = {0,1,2,3,/**< �������� */
                          4,5,6,7,/**< �������� */
						  0,3,4,7,/**< �������� */
						  2,5,4,3,/**< ǰ������ */
						  2,1,6,5,/**< �������� */
						  0,1,6,7};/**< �������� */
	                      

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Graphics * graphics = new Graphics(class_name);
	return reinterpret_cast<GLApplication *>(graphics);
}


/** ���캯�� */
Graphics::Graphics(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
	m_Pivot = 1;                                                /**< ���ó�ʼֵΪ0 */
		
}

/** ��ʼ��OpenGL */
bool Graphics::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);
	
	/** ���ö����������ɫ���� */
	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_COLOR_ARRAY);
	/** ָ�������е����� */
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glColorPointer(3,GL_FLOAT,0,colors);
	
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Graphics::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

/** ������º��� */
void Graphics::Update(DWORD milliseconds)						
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
void Graphics::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/**< �����ɫ�������Ȼ��� */		
	glLoadIdentity();
    
	/** ����Բ׶�� */
	glPushMatrix();
	   glTranslatef(-1.5f,0.5f,-7.0f);	/**< �����Ͻ��ƣ���������Ļ */					
	   glRotatef(m_Angle,1.0f,1.0f,0.0f);  
	   glShadeModel(GL_FLAT); /**< ����Ϊ�㶨��ɫ */
	   /** ����Բ׶���� */
	   glBegin(GL_TRIANGLE_FAN);
	       glVertex3f(0.f,1.8f,0.f);/**< ָ��Բ׶���� */
		   for(float angle = 0.0f; angle < 2.0f *GL_PI ; angle += GL_PI/8.0f)
		   {
			  if(m_Pivot % 2 == 0)
				  glColor3f(0.f,1.f,0.f);
			  else
				  glColor3f(0.f,0.0f,1.0f);
			 
			  m_Pivot++;
			  glVertex3f(0.8*sin(angle),0.f,0.8*cos(angle));/**< ָ��Բ׶�����ϵ� */
		   }
		glEnd();
       
		/** �������Բ׶���� */
	   glBegin(GL_TRIANGLE_FAN);
	     glVertex2f(0.0f,0.f);                             /**< ָ��Բ������ */
		 for(float angle = 0.0f; angle < 2.0 * GL_PI; angle +=GL_PI/8.0f)
          {
			  if(m_Pivot % 2 == 0)
				  glColor3f(0.f,1.f,0.f);
			  else
				  glColor3f(0.f,0.0f,1.0f);
			  
			  m_Pivot++;
			  glVertex3f(0.8* sin(angle),0.f,0.8 * cos(angle));/**< ָ��Բ���ϵĵ� */
		   }
	 glEnd();                                                  /**< ���ƽ��� */
   glPopMatrix(); 
	  
   /** ���������� */
   glPushMatrix(); 
	glTranslatef(1.5f,1.0f,-7.0f);						/**< �����Ͻ��ƣ���������Ļ */
	glRotatef(m_Angle,1.0f,1.0f,1.0f);					/**< ��XYZ������ת������ */
	glScalef(0.75f,0.75f,0.75f);
	glShadeModel(GL_SMOOTH);                            /**< ʹ��ƽ����ɫ */
    ///��ʼ����	
	glBegin(GL_QUADS);
	  for(int i = 0; i < 6; i++)                         /**< ʹ�ö�������������������������� */
		{ 
		    glArrayElement(indexs[4 * i]);
			glArrayElement(indexs[4 * i + 1]);
			glArrayElement(indexs[4 * i + 2]);
			glArrayElement(indexs[4 * i + 3]);
		}
	glEnd();                                /**< ���ƽ��� */
   glPopMatrix();

  /**�������߿��� */
   glPushMatrix();
	 glTranslatef(-1.5f,-1.5f,-7.0f);
	 glRotatef(m_Angle,0.0f,1.0f,1.0f);
	 glColor3f(0.3f,0.7f,0.6f);
	 auxWireSphere(1.0);                          /**< ʹ��aux�����⺯������һ���߿��� */
   glPopMatrix();

  /** �����߿��� */
    glPushMatrix();
	  glTranslatef(1.5f,-1.5f,-7.0f);
	  glRotatef(m_Angle,0.0f,1.0f,0.0f);
	  glColor3f(0.3f,0.6f,0.2f);
	  auxWireTeapot(1.0);                        /**< ʹ��aux�����⺯������һ���߿��� */
    glPopMatrix();

	glFlush();									/**< ǿ��ִ�����е�OpenGL���� */
}
