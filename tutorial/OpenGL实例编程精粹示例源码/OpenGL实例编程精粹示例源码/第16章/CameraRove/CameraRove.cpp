//=========================================================================
/**
*  @file      CameraRove.cpp
*
*  ��Ŀ������ ���������
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-02
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
#include <stdio.h>                          /**< ����ͷ�ļ� */
#include "CameraRove.h"						    

#include <gl\gl.h>							/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>	

#pragma comment(lib, "opengl32.lib")		/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")	

/** �����Դ������ֵ */
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	/**< ��������� */
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };	/**< ��Դλ�� */

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	CameraRove * test = new CameraRove(class_name);
	return reinterpret_cast<GLApplication *>(test);
}


/** ���캯�� */
CameraRove::CameraRove(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Fps = 0;
   
}

bool CameraRove::LoadTexture()
{
	
	if(!m_Texture.LoadBitmap("image.bmp"))                   /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
		return false;
	}
	glGenTextures(1, &m_Texture.ID);                        /**< ����һ������������� */
		
	glBindTexture(GL_TEXTURE_2D, m_Texture.ID);             /**< ����������� */
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture.imageWidth,
					m_Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
					m_Texture.image);
  	return true;
}

/** ��ʼ��OpenGL */
bool CameraRove::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	                             /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	
	/** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	/**< ��������� */
	
	
	/** ���ù�Դ������ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1); 
	glEnable(GL_TEXTURE_2D);

	/** ��ʼ������ */
	if(!m_Font.InitFont())
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
	
	/** �������� */
	if(!LoadTexture())
		MessageBox(NULL,"��������ʧ��!","����",MB_OK);
	
	/** ��������� */
	m_Camera.setCamera(0.0f,1.5f, 6.0f, 0.0f, 1.5f, 0.0f,0.0f, 1.0f, 0.0f);
	return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void CameraRove::Uninit()									
{
/** �û��Զ����ж�ع��� */
	m_Texture.FreeImage();              /** �ͷ�����ͼ��ռ�õ��ڴ� */
	glDeleteTextures(1, &m_Texture.ID); /**< ɾ��������� */

 }
/** ��������� */
void CameraRove::UpdateCamera()
{
	m_Camera.setViewByMouse();
	
	/** ���̰�����Ӧ */
	if(m_Keys.IsPressed(VK_SHIFT))                      /**< ����SHIFT��ʱ���� */
	{
		m_Camera.setSpeed(0.6f);
	}
	if(!m_Keys.IsPressed(VK_SHIFT))
	{
		m_Camera.setSpeed(0.2f);
	}
	if(m_Keys.IsPressed(VK_UP) || m_Keys.IsPressed('W'))   /**< ���Ϸ������'W'������ */
		m_Camera.moveCamera(m_Camera.getSpeed());          /**< �ƶ������ */

	if(m_Keys.IsPressed(VK_DOWN) || m_Keys.IsPressed('S')) /**< ���·������'S'������ */
		m_Camera.moveCamera(-m_Camera.getSpeed());         /**< �ƶ������ */

	if(m_Keys.IsPressed(VK_LEFT) || m_Keys.IsPressed('A')) /**< ���������'A'������ */
		m_Camera.yawCamera(-m_Camera.getSpeed());          /**< �ƶ������ */

	if(m_Keys.IsPressed(VK_RIGHT) || m_Keys.IsPressed('D')) /**< ���ҷ������'D'������ */
		m_Camera.yawCamera(m_Camera.getSpeed());            /**< �ƶ������ */

}
/** ������º��� */
void CameraRove::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

/** �û��Զ���ĸ��¹��� */
	/** ��������� */
	UpdateCamera();
	
	    
}

/** ����֡�� */
void CameraRove::CaculateFrameRate()
{
	static float framesPerSecond    = 0.0f;	     /**< ������ʾ֡�� */	
    static float lastTime			= 0.0f;	     /**< ��¼�ϴ�ʱ�� */						
    float currentTime = GetTickCount() * 0.001f; /**< ��õ�ǰʱ�� */	 			

	++framesPerSecond;                           /**< ��ʾ֡������1 */
    /** ���ʱ������1.0�� */
	if( currentTime - lastTime > 1.0f )          
    {
		
	    lastTime = currentTime;                   /**< ���浱ǰʱ�� */
		m_Fps = framesPerSecond;                  /**< ��ǰ֡������m_Fps */
        framesPerSecond = 0;                      /**< ��֡������ */                    
    }
}

/** ���������Ϣ */
void  CameraRove::PrintText()
{
	char string[128];                               /**< ���ڱ�������ַ��� */
	glPushAttrib(GL_CURRENT_BIT);                   /**< ����������ɫ������Ϣ */
	glColor3f(0.0f,1.0f,0.0f);                      /**< ����������ɫ */
	sprintf(string,"��ǰλ��:X=%3.1f  Y=%3.1f Speed =%3.1f ",   
		     m_Camera.getView().x,-m_Camera.getView().z ,m_Camera.getSpeed()); /**< �ַ�����ֵ */
	m_Font.PrintText(string,-5.0f,3.5f);

	/** ���֡�� */
	CaculateFrameRate();                               /**< ����֡�� */
    sprintf(string,"FPS:%3.0f",m_Fps);                 /**< �ַ�����ֵ */
	m_Font.PrintText(string, -5.0f,3.0f);              /**< ����ַ��� */
	glPopAttrib();
		
}

/** ����������� */
void CameraRove::DrawGrid()
{
    /** ��ó�����һЩ״̬  */
	GLboolean  lp,tp;
	glGetBooleanv(GL_LIGHTING,&lp);  
	glGetBooleanv(GL_TEXTURE_2D,&tp);
	
	/** �ر�����͹��� */
	glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
	
	/** ���ƹ��� */
	glPushAttrib(GL_CURRENT_BIT);   /**< ���浱ǰ���� */
    glPushMatrix();                 /**< ѹ���ջ */
	glTranslatef(0.0f,0.0f,0.0f);  
	glColor3f(0.0f, 0.0f, 1.0f);    /**< ������ɫ */

	/** ��X,Zƽ���ϻ������� */
	for(float i = -50; i <= 50; i += 1)
	{
		/** ������ */
		glBegin(GL_LINES);

		    /** X�᷽�� */
			glVertex3f(-50, 0, i);
			glVertex3f(50, 0, i);

			/** Z�᷽�� */
			glVertex3f(i, 0, -50);
			glVertex3f(i, 0, 50);

		glEnd();
	}
	glPopMatrix();
	glPopAttrib();
	/** �ָ�����״̬ */
	if(tp)
	  glEnable(GL_TEXTURE_2D);
	if(lp)
      glEnable(GL_LIGHTING);
}

/** �������� */
void CameraRove::DrawSphere()
{
	/** ���ò������� */
	GLfloat mat_ambient[] = { 0.9f, 0.5f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.9f, 0.5f, 0.8f, 1.0f };
	GLfloat mat_shininess[] = { 100.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
	/** �����������״̬ */
	GLboolean tp;
	glGetBooleanv(GL_TEXTURE_2D,&tp);
    glDisable(GL_TEXTURE_2D);                   /**< �ر����� */
    /** ���ƹ��� */
	glPushMatrix();
    glTranslatef(-5.0f,2.0f,-10.0f);
    GLUquadricObj * sphere = gluNewQuadric();
    gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricNormals(sphere,GLU_SMOOTH);
	gluSphere(sphere,2.0,50,50);
	gluDeleteQuadric(sphere);
    glPopMatrix();
    
	/** �ָ�״̬ */
	if(tp)
	   glEnable(GL_TEXTURE_2D);
	
}

/** ����ľ�� */
void CameraRove::DrawBox()
{
	/** ���ò������� */
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glPushMatrix();
	glTranslatef(5.0f,2.0f,-10.0f);
	glScalef(2.0f,2.0f,2.0f);
	/** ѡ������ */
	glBindTexture(GL_TEXTURE_2D, m_Texture.ID);
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
	glEnd();
	glPopMatrix();
}
/** ���ƺ��� */
void CameraRove::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	
	
	/** ��������� */	
	m_Camera.setLook();
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	/**< ���ù�Դλ�� */

	/**< ���ƹ��� */
	DrawGrid();
    DrawSphere();
	DrawBox();
	
	/** ���������Ϣ */
	PrintText();
		
	glFlush();							    /**< ǿ��ִ�����е�OpenGL���� */
}
