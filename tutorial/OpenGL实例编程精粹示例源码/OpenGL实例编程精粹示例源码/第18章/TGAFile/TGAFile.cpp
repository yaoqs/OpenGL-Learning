//=========================================================================
/**
*  @file      SkyAndTerrain.cpp
*
*  ��Ŀ������ TGA�ļ�����
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
#include "stdafx.h"
#include "TGAFile.h"						    


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	TGAFile * test = new TGAFile(class_name);
	return reinterpret_cast<GLApplication *>(test);
}


/** ���캯�� */
TGAFile::TGAFile(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Fps = 0;
	m_RenderMode = true;
	sp = false;
}

/** ��ʼ��OpenGL */
bool TGAFile::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	                             /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	
	/** �������� */
	glEnable(GL_TEXTURE_2D);

	/** ��ʼ������ */
	if(!m_Font.InitFont())
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
	
	/** ��ʼ������ */	
	if(!m_Terrain.initTerrain())
	{
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
		exit(0);
	}

	/** ��ʼ����� */
	if(!m_SkyBox.Init())
	{
		MessageBox(NULL,"��ʼ�����ʧ��!","����",MB_OK);
		exit(0);
	}

	/** ����TGA���� */
	if(!m_TGATexture[0].Load("data/sphere.tga"))
	{
		MessageBox(NULL,"����TGA����ʧ��!","����",MB_OK);
		exit(0);
	}

	if(!m_TGATexture[1].Load("data/box.tga"))
	{
		MessageBox(NULL,"����TGA����ʧ��!","����",MB_OK);
		exit(0);
	}
	
	/** ��������� */
	m_Camera.setCamera( 270, 35, 656,  268, 35, 654,  0, 1, 0);

	return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void TGAFile::Uninit()									
{
}
/** ��������� */
void TGAFile::UpdateCamera()
{
	m_Camera.setViewByMouse();
	
	/** ���̰�����Ӧ */
	if(m_Keys.IsPressed(VK_SHIFT))                        /**< ����SHIFT��ʱ���� */
	{
		m_Camera.setSpeed(0.5f);
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

	/** ���ݵ��θ߶ȸ�������� */
	Vector3 vPos = m_Camera.getPosition();                  /**< �õ���ǰ�����λ�� */
    Vector3 vNewPos = vPos; 
	
	/** ����������߶�Ϊ ���θ߶� + 10 */
	vNewPos.y = (float)m_Terrain.getAveHeight(vPos.x,vPos.z ) + 10;

		/** �õ��߶Ȳ�ֵ */
		float temp = vNewPos.y - vPos.y;

		/** ������������� */
		Vector3 vView = m_Camera.getView();
		vView.y += temp;

		/** ��������� */
		m_Camera.setCamera(vNewPos.x,  vNewPos.y,  vNewPos.z,
						   vView.x,	   vView.y,	   vView.z,	 
						   0, 1, 0);								
	
}
/** ������º��� */
void TGAFile::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

/** �û��Զ���ĸ��¹��� */
	
	/** ��������� */
	UpdateCamera();

	/** �ո���л�����ģʽ */
	if(m_Keys.IsPressed(VK_SPACE) && !sp)
	{
		sp = true;
		m_RenderMode = !m_RenderMode;
		if(m_RenderMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if(!m_Keys.IsPressed(VK_SPACE))
		sp = false;
	
	    
}

/** ����֡�� */
void TGAFile::CaculateFrameRate()
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
void  TGAFile::PrintText()
{
	char string[128];                               /**< ���ڱ�������ַ��� */
	glPushAttrib(GL_CURRENT_BIT);                   /**< ����������ɫ������Ϣ */
	glColor3f(0.0f,1.0f,0.0f);                      /**< ����������ɫ */
	sprintf(string,"��ǰλ��:X=%3.1f  Y=%3.1f Speed =%3.1f ",   
		m_Camera.getPosition().x,m_Camera.getPosition().z ,m_Camera.getSpeed()); /**< �ַ�����ֵ */
	m_Font.PrintText(string,-5.0f,3.5f);

	/** ���֡�� */
	CaculateFrameRate();                               /**< ����֡�� */
    sprintf(string,"FPS:%3.0f",m_Fps);                 /**< �ַ�����ֵ */
	m_Font.PrintText(string, -5.0f,3.0f);              /**< ����ַ��� */
	glPopAttrib();
		
}

/** �������� */
void TGAFile::DrawSphere(float x,float z,float radius)
{
	/** ָ������ */
	glBindTexture(GL_TEXTURE_2D,m_TGATexture[0].ID);
	
	float y = m_Terrain.getAveHeight(x,z);
	
	/** ���ƹ��� */
	glPushMatrix();
	glTranslatef(x,y + radius,z);
	  GLUquadricObj * sphere = gluNewQuadric();
      gluQuadricOrientation(sphere, GLU_OUTSIDE);
	  gluQuadricNormals(sphere,GLU_SMOOTH);
	  gluQuadricTexture(sphere,GL_TRUE);
	  gluSphere(sphere,radius,50,50);
	  gluDeleteQuadric(sphere);
	glPopMatrix();

}

/** ����ľ�� */
void TGAFile::DrawBox(float x,float z,float length)
{
	/** ָ������ */
	glBindTexture(GL_TEXTURE_2D,m_TGATexture[1].ID);

	float y = m_Terrain.getAveHeight(x,z);

	glPushMatrix();
	glTranslatef(x,y + length ,z);
	glScalef(length,length,length);
	glPushMatrix();
	
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
void TGAFile::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
	
	/** ��������� */	
	m_Camera.setLook();
	
	/** ��Ⱦ���� */
	m_Terrain.render();
	
	/** ������� */
	m_SkyBox.CreateSkyBox(0, 0, 0, 1.0, 0.5,1.0);

	/** ����С�� */
	DrawSphere(230,515,10);

	/** ����ľ�� */
	DrawBox(135,555,10);
	/** �����Ļ��Ϣ */ 
	PrintText();
		
	glFlush();	                 /**< ǿ��ִ�����е�OpenGL���� */
}
