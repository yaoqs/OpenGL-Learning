//=========================================================================
/**
*  @file      Test.cpp
*
*  ��Ŀ������ MD2�ļ�����
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
#include "MD2File.h"						    


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Test * test = new Test(class_name);
	return reinterpret_cast<GLApplication *>(test);
}


/** ���캯�� */
Test::Test(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Fps = 0;
	m_RenderMode = true;
	sp = false;
	mp = false;
	
}

/** ��ʼ��OpenGL */
bool Test::Init()									
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

	m_MD2.Init("hobgoblin.md2","hobgoblin.bmp");

		
	/** ��������� */
	m_Camera.setCamera( 381, 35, 674,  374.5, 35, 669,  0, 1, 0);

	return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Test::Uninit()									
{
}
/** ��������� */
void Test::UpdateCamera()
{
	m_Camera.setViewByMouse();
	
	/** ���̰�����Ӧ */
	if(m_Keys.IsPressed(VK_SHIFT))                        /**< ����SHIFT��ʱ���� */
	{
		m_Camera.setSpeed(5.0f);
	}
	if(!m_Keys.IsPressed(VK_SHIFT))
	{
		m_Camera.setSpeed(2.0f);
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
void Test::Update(DWORD milliseconds)						
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
	
	/** 'M'��������һ������ */
	if(m_Keys.IsPressed('M') && !mp)
	{
		mp = true;
		
		/** ���õ�ǰ����Ϊ��һ������ */
		m_MD2.GetModel().currentAnim = (m_MD2.GetModel().currentAnim + 1) % (m_MD2.GetModel().numOfAnimations);
		
		/** ���õ�ǰ֡Ϊ��һ�������Ŀ�ʼ֡ */
		m_MD2.GetModel().currentFrame = (m_MD2.GetModel()).pAnimations[m_MD2.GetModel().currentAnim].startFrame;
	}
	if(!m_Keys.IsPressed('M'))
	{
		mp = false;
	}
	    
}

/** ����֡�� */
void Test::CaculateFrameRate()
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
void  Test::PrintText()
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
	

	/** ���֡���� */
	sprintf(string,"��ǰ����:%s(��'M'���л���һ������)",m_MD2.GetModel().pAnimations[m_MD2.GetModel().currentAnim].strName);
	m_Font.PrintText(string,-5.0f,2.5f);
	glPopAttrib();
}

/** ����MD2���� */
void Test::Animate(float x,float z,float h,float scale)
{
	glPushAttrib(GL_CURRENT_BIT); /**< ����������ɫ��ʵ�� */
	float y = m_Terrain.getAveHeight(x,z) + h;
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(scale,scale,scale);
	m_MD2.AnimateMD2Model();
	glPopMatrix();
    glPopAttrib();   /**< �ָ�ǰһ���� */	
}
/** ���ƺ��� */
void Test::Draw()											
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

	Animate(300,600,18,0.75);
	/** �����Ļ��Ϣ */ 
	PrintText();
		
	glFlush();	                 /**< ǿ��ִ�����е�OpenGL���� */
}
