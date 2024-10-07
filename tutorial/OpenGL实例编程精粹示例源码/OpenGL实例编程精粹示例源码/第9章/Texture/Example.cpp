//=========================================================================
/**
*  @file  Example.cpp
*
*  ��Ŀ������ ����ӳ��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-26
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
//#include <math.h>                                              /**< ����math.hͷ�ļ� */                                             


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

/** �����Դ������ֵ */
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	/**< ��������� */
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };	/**< ��Դλ�� */

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
	
	glEnable(GL_TEXTURE_2D);                          /**< ��������ӳ�� */
	if(!Texture.LoadBitmap("image.bmp"))              /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
		return false;
	}
	glGenTextures(1, &Texture.ID);        /**< ����һ������������� */
	 
	glBindTexture(GL_TEXTURE_2D, Texture.ID); /**< ����������� */
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    /** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture.imageWidth,
	                  Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
	                  Texture.image);
    /** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);			/**< ��������� */
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);			/**< ���ù�Դλ�� */
	/** ���ù��պ͹�Դ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);     

  	return true;           /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Example::Uninit()									
{
    Texture.FreeImage();              /** �ͷ�����ͼ��ռ�õ��ڴ� */
	glDeleteTextures(1, &Texture.ID); /**< ɾ��������� */
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
	rot += milliseconds/20.0;
	    
}

/** ���ƺ���// */
void Example::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< ������� */		
	glLoadIdentity();	
    /** ���ƹ��� */	
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(rot,1.0f,1.0f,0.0f);
	/** ѡ������ */
	glBindTexture(GL_TEXTURE_2D, Texture.ID);
	/** ��ʼ�����ı��� */
	glBegin(GL_QUADS);												
		/// ǰ����
		glNormal3f( 0.0f, 0.0f, 1.0f);								/**< ָ������ָ��۲��� */
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
		/// �����
		glNormal3f( 0.0f, 0.0f,-1.0f);								/**< ָ�����߱���۲��� */
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
		/// ����
		glNormal3f( 0.0f, 1.0f, 0.0f);								/**< ָ���������� */
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
		/// ����
		glNormal3f( 0.0f,-1.0f, 0.0f);								/**< ָ�����߳��� */
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
		/// �Ҳ���
		glNormal3f( 1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
		/// �����
		glNormal3f(-1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
	glEnd();														/**< �ı��λ��ƽ��� */
	
    glFlush();				           /**< ǿ��ִ�����е�OpenGL���� */
}
