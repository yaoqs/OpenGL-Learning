//=========================================================================
/**
*  @file  List.cpp
*
*  ��Ŀ������ OPenGL��ʾ�б�
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-19
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

#include "List.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	DisplayList * list = new DisplayList(class_name);
	return reinterpret_cast<GLApplication *>(list);
}


/** ���캯�� */
DisplayList::DisplayList(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
	m_Pyramid = 0;
	
}

/** ��ʼ��OpenGL */
bool DisplayList::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	
	m_Pyramid = glGenLists(1); /**< ����1��δ��ʹ�õ������� */
	if(m_Pyramid != 0)
	{
		///����һ����ʾ�б�
		glNewList(m_Pyramid,GL_COMPILE); 
		 ///����һ����������
		  glBegin(GL_TRIANGLES);
			///ǰ����
			glColor3f(1.0f,0.0f,0.0f);			/**< ��ɫ */
			glVertex3f( 0.0f, 1.0f, 0.0f);		/**< �����ε��϶��� (ǰ����) */
			glColor3f(0.0f,1.0f,0.0f);			/**< ��ɫ */
			glVertex3f(-1.0f,-1.0f, 1.0f);		/**< �����ε����¶��� (ǰ����) */
			glColor3f(0.0f,0.0f,1.0f);			/**< ��ɫ */
			glVertex3f( 1.0f,-1.0f, 1.0f);		/**< �����ε����¶��� (ǰ����) */
            //�Ҳ���
			glColor3f(1.0f,0.0f,0.0f);			/**< ��ɫ */
			glVertex3f( 0.0f, 1.0f, 0.0f);		/**< �����ε��϶��� (�Ҳ���) */
			glColor3f(0.0f,0.0f,1.0f);			/**< ��ɫ */
			glVertex3f( 1.0f,-1.0f, 1.0f);		/**< �����ε����¶��� (�Ҳ���) */
			glColor3f(0.0f,1.0f,0.0f);			/**< ��ɫ */
			glVertex3f( 1.0f,-1.0f, -1.0f);		/**< �����ε����¶��� (�Ҳ���) */
			///�����
			glColor3f(1.0f,0.0f,0.0f);			/**< ��ɫ */
			glVertex3f( 0.0f, 1.0f, 0.0f);		/**< �����ε��϶��� (�����) */
			glColor3f(0.0f,1.0f,0.0f);			/**< ��ɫ */
			glVertex3f( 1.0f,-1.0f, -1.0f);		/**< �����ε����¶��� (�����) */
			glColor3f(0.0f,0.0f,1.0f);			/**< ��ɫ */
			glVertex3f(-1.0f,-1.0f, -1.0f);		/**< �����ε����¶��� (�����) */
            ///������
			glColor3f(1.0f,0.0f,0.0f);			/**< ��ɫ */
			glVertex3f( 0.0f, 1.0f, 0.0f);		/**< �����ε��϶��� (�����) */
			glColor3f(0.0f,0.0f,1.0f);			/**< ��ɫ */
			glVertex3f(-1.0f,-1.0f,-1.0f);		/**< �����ε����¶��� (�����) */
			glColor3f(0.0f,1.0f,0.0f);			/**< ��ɫ */
			glVertex3f(-1.0f,-1.0f, 1.0f);		/**< �����ε����¶��� (�����) */
		  glEnd();
		   
		  ///���Ƶ����ı���	
		  glBegin(GL_QUADS);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(-1.0f,-1.0f, 1.0f);
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f( 1.0f,-1.0f, 1.0f);
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f( 1.0f,-1.0f, -1.0f);
			glColor3f(1.0f,0.0f,1.0f);
			glVertex3f(-1.0f,-1.0f, -1.0f);
		  glEnd();
         //glTranslatef(3.0f,0.0f,0.0f); /**< ����ƫ��,Ϊ��һ�λ�����׼�� */
	   glEndList();/**< ������ʾ�б� */
	}
	///��ʼ��ʼ��	
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);	
	glDepthFunc(GL_LEQUAL);	
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);     /**< ����ƽ����ɫ */
		
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void DisplayList::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

/** ������º��� */
void DisplayList::Update(DWORD milliseconds)						
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

	m_Angle += (float)milliseconds / 30;  /**< ����������ת�Ƕ� */

}

/** ���ƺ��� */
void DisplayList::Draw()											
{
     /** �û��Զ���Ļ��ƹ��� */
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		/**< �����ɫ����Ȼ��� */	
	glLoadIdentity();	
	
	///ѭ������12����������
	for(int y =0; y < 3; y++)  /**< ��Y��ѭ�� */
	{
		for(int x=0; x < 4; x++)  /**< ��X��ѭ�� */
		{
			glLoadIdentity();  /**< ����ģ�ͱ仯���� */
			glTranslatef(-3.0 + 2.0 * x , -2.0 + 2.0 * y, -10.0f);
			glScalef(0.8f,0.8f,0.8f);
			glRotatef(m_Angle,1.0f,1.0f,0.0f);
			glCallList(m_Pyramid); /**< ���ƽ������� */
			
		}
	}

   glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
