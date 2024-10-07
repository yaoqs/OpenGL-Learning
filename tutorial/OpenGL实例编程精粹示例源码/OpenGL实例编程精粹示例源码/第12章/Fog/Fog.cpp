//=========================================================================
/**
*  @file  Fog.cpp
*
*  ��Ŀ������ OpenGL��Ч��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-01
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

#include "Fog.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>	 
                         
#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

/** �����Դ������ֵ */
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	/**< ��������� */
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };	/**< ��Դλ�� */

/** ����������� */
GLfloat mat_ambient[]={0.0,0.1,0.8,1.0};  /**< ������ɫ */
GLfloat mat_diffuse[]={0.0,0.3,0.6,1.0};  /**< ɢ����ɫ */
GLfloat mat_specular[]={1.0,0.0,1.0,1.0}; /**< ���淴����ɫ */
GLfloat mat_shininess[]={10.0};           /**< ���淴��ָ�� */

GLuint fogMode[]= { GL_LINEAR, GL_EXP, GL_EXP2 };		/**< ��Ч��ģʽ */
GLuint fogFilter= 0;									/**< ʹ����һ����Чģʽ */
GLfloat fogColor[4]={0.5,0.5,0.5,1.0};                  /**< �����ɫ */ 

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Fog * fog = new Fog(class_name);
	return reinterpret_cast<GLApplication *>(fog);
}


/** ���캯�� */
Fog::Fog(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	z = -5.0f;             /**< ��ʼ��Ϊ-5.0f */
	fp = false;            /**< ��ʼ��Ϊflase */
}



/** ��ʼ��OpenGL */
bool Fog::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.5f,0.5f,0.5f,1.0f);
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	
    /** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);			/**< ��������� */
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);			/**< ���ù�Դλ�� */
    /** ���ò��ʵ�����ֵ */
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);              /**< ���û�����ɫ */
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);              /**< ����ɢ����ɫ */
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);            /**< ���þ��淴����ɫ */
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);          /**< ���þ��淴��ָ�� */

	/** ���ù��պ͹�Դ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);     
    /** ������Ч */
	glEnable(GL_FOG); 
    { 
		glFogi(GL_FOG_MODE,fogMode[fogFilter]); /** ������Ч��ģʽ */
		glFogfv(GL_FOG_COLOR,fogColor);         /** ָ�������ɫ */ 
       	glFogf(GL_FOG_DENSITY,0.2f);            /** �������Ũ�� */
		glFogf(GL_FOG_START,1.0);               /** ����������Ŀ�ʼλ�� */
		glFogf(GL_FOG_END,10.0);                /** ����������Ľ���λ�� */
		glHint(GL_FOG_HINT,GL_DONT_CARE);       /** �涨��Ч�������� */  
    } 
	ResizeDraw(true);						   /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	
  	return true;                               /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Fog::Uninit()									
{
}

/** ������º��� */
void Fog::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}
  
 /** �û��Զ���ĸ��¹��� */

	if(m_Keys.IsPressed(VK_DOWN))             /**< ���·������������ô��*/
		z -= 0.02f;                           /**< ��ģ��������Ļ�ڲ� */

	if(m_Keys.IsPressed(VK_UP))               /**< ���Ϸ������������ô��*/
		z += 0.02f;                           /**< �����е�������۲��� */

	if(m_Keys.IsPressed('F') && !fp )         /**< F���Ƿ񱻰��£�*/
	{
		fp = true;                            /**< �� */
		fogFilter += 1;                       /**< �任��Чģʽ */
		if(fogFilter > 2)                     /**< fogFilter�Ƿ����2 */
		{
			fogFilter = 0;                    /**< ���� */
    	}
		glFogi (GL_FOG_MODE, fogMode[fogFilter]); /**< ������Чģʽ */
	}
	if(!m_Keys.IsPressed('F'))                /**< F���Ƿ��ͷţ�*/
		fp = false;                           /**< �ǣ�������Ϊ�ͷ� */

	    
}
/** �������� */
void Fog::DrawSphere(float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);     /**< �Ƶ�ָ��λ�� */
	auxSolidSphere(0.5);     /**< ����һ������ */
	glPopMatrix();
}

/** ���ƺ���// */
void Fog::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< ������� */		
	glLoadIdentity();
	/** ���ƹ��� */	
	for(int i=1; i < 10; i++)         /**< ѭ��10�λ���10������ */
	    DrawSphere(-3 + i * 0.8, 0.0, z - i + 1);	
   
    glFlush();				           /**< ǿ��ִ�����е�OpenGL���� */
}
