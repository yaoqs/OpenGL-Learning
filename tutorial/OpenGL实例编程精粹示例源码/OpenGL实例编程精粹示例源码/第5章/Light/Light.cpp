//=========================================================================
/**
*  @file  Light.cpp
*
*  ��Ŀ������ OPenGL����Ч����ʾ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-17
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

#include "Light.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

/** ����������Դ����ɫ ��ɫ����ɫ����λ�� */
static float lightPositionR[] = { 0.0f, 0.0f, 5.0f, 1.0f };
static float lightPositionG[] = { 0.0f, 0.0f, 5.0f, 1.0f };
static float lightPositionB[] = { 0.0f, 0.0f, 5.0f, 1.0f };

/** ����������Դ������� */
static float diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float diffuseLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

/** ����������Դ�ľ���� */
static float specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float specularLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };

/** �ٶ���һ��Ĭ�ϵĹ�Դ */
static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };	 
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };	 
static float lightPosition[] = { 0.0f, 0.0f, 10.0f, 1.0f };


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Light * light = new Light(class_name);
	return reinterpret_cast<GLApplication *>(light);
}


/** ���캯�� */
Light::Light(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
	m_bRedX = 0.0f;
	m_bGreenX = 0.0f;
	m_bBlueX = 0.0f;
	m_bRedY = 0.0f;
	m_bGreenY = 0.0f;
	m_bBlueY = 0.0f;
	
}

/** ��ʼ��OpenGL */
bool Light::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);	
	glDepthFunc(GL_LEQUAL);	
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_LIGHTING);
	
	/** ����0�Ź�Դ */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	
	/** ����1�ź�ɫ��Դ */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);
	
	/** ����2����ɫ��Դ */
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightG);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightG);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);
	
	/** ����3����ɫ��Դ */
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLightB);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLightB);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);

	glEnable(GL_LIGHT0);                                     /**< ����0�Ż�ɫ��Դ,������ɼ� */
	
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Light::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

/** ������º��� */
void Light::Update(DWORD milliseconds)						
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
   /**�����º�ɫ��Դ */
	if(m_Keys.IsPressed(0x31) == false)       /**< ������'1'��û�б�����ʱ */
	{
		glEnable(GL_LIGHT1);                  /**< ����1�ź�ɫ��Դ */
		m_bRedX += (float)milliseconds / 30;  /**< ������ת�Ƕ� */
		m_bRedY += (float)milliseconds / 20;
	}
	else
		glDisable(GL_LIGHT1);               /**< ��������ʱ�����øù�Դ */
  /**��������ɫ��Դ */
	if(m_Keys.IsPressed(0x32) == false)        /**< ������'2'��û�б�����ʱ */
	{
		glEnable(GL_LIGHT2);                   /**< ����2����ɫ��Դ */
		m_bGreenX += (float)milliseconds / 20; /**< ������ת�Ƕ� */
		m_bGreenY += (float)milliseconds / 30;
	}
	else
		glDisable(GL_LIGHT2);             /**< ��������ʱ�����øù�Դ */
 /**��������ɫ��Դ */
	if(m_Keys.IsPressed(0x33) == false)     /**< ������'3'��û�б�����ʱ */
	{
		glEnable(GL_LIGHT3);                /**< ����3����ɫ��Դ */
		m_bBlueX += (float)milliseconds / 30; /**< ������ת�Ƕ� */
		m_bBlueY += (float)milliseconds / 30;
	}
	else
		glDisable(GL_LIGHT3);              /**< ��������ʱ�����øù�Դ */

     m_Angle += (float)milliseconds / 30;  /**< ����������ת�Ƕ� */

}

/** ���ƺ��� */
void Light::Draw()											
{
     /** �û��Զ���Ļ��ƹ��� */
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	
	
	glTranslatef(0.0f, 0.0f, -10.0f); /**< ������Ļ */
	
	/** ��ɫ��Դ */
	glPushMatrix();
		/** ��ת��ɫ��Դ�� */
		glRotatef(m_bRedX, 1.0f, 0.0f, 0.0f);
		glRotatef(m_bRedY, 0.0f, 1.0f, 0.0f);
		
		/** ���ú�ɫ��Դλ�� */
		glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);

		/**< �ڹ�Դλ�ô�����һ��������Դ */
		glTranslatef(lightPositionR[0], lightPositionR[1], lightPositionR[2]);
		glColor3f(1.0f, 0.0f, 0.0f);	/**< ��ɫ */
		
		glPushAttrib(GL_LIGHTING_BIT);
			glDisable(GL_LIGHTING);	/**< �رչ��� */
			  auxSolidSphere(0.1);
			glEnable(GL_LIGHTING); /**< ���ù��� */
		glPopAttrib();	
	glPopMatrix();
	
	/** ��ɫ��Դ */
	glPushMatrix();
		/** ��ת��ɫ��Դ�� */
		glRotatef(m_bGreenX, 1.0f, 0.0f, 0.0f);
		glRotatef(m_bGreenY, 0.0f, 1.0f, 0.0f);
		
		/** ������ɫ��Դλ�� */
		glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);
	
		/**< �ڹ�Դλ�ô�����һ��������Դ */
		glTranslatef(lightPositionG[0], lightPositionG[1], lightPositionG[2]);
		glColor3f(0.0f, 1.0f, 0.0f);	/**< ��ɫ */
		
		glPushAttrib(GL_LIGHTING_BIT);
			glDisable(GL_LIGHTING);	/**< �رչ��� */
			  auxSolidSphere(0.1);
			glEnable(GL_LIGHTING);  /**< ���ù��� */
		glPopAttrib();	
	glPopMatrix();
	
	/** ��ɫ��Դ */
	glPushMatrix();
		
	    /** ��ת��ɫ��Դ�� */
		glRotatef(m_bBlueX, 1.0f, 0.0f, 0.0f);
		glRotatef(m_bBlueY, 0.0f, 1.0f, 0.0f);

		/** ������ɫ��Դλ�� */
		glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);
	
		/**< �ڹ�Դλ�ô�����һ��������Դ */
		glTranslatef(lightPositionB[0], lightPositionB[1], lightPositionB[2]);
		glColor3f(0.0f, 0.0f, 1.0f);	/**< ��ɫ */
		
		glPushAttrib(GL_LIGHTING_BIT);
			glDisable(GL_LIGHTING);	/**< �رչ��� */
			  auxSolidSphere(0.1);
			glEnable(GL_LIGHTING); /**< ���ù��� */
		glPopAttrib();	
	glPopMatrix();
	
	/** ����һ������ */
	glPushMatrix();
		/**< ������ת */
		glRotatef(m_Angle, 1.0f, 0.0f, 0.0f);
		glRotatef(m_Angle, 0.0f, 1.0f, 0.0f);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0, 1.0, 1.0);
		auxSolidSphere(2.5);
	glPopMatrix();

   glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
