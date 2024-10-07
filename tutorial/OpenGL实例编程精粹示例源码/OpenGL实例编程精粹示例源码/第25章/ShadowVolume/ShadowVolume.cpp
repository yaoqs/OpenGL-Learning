//=========================================================================
/**
*  @file      ShadowVolume.cpp
*
*  ��Ŀ������ ��Ӱ��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-20
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
#include "ShadowVolume.h"						    

/** ��Դλ�� */
CVector4 lightPos(2.0f, 5.0f, 0.0f, 1.0f);

#define MAX_SHADOW_CASTER_POINTS 4  /**< �����ڵ��嶥����� */
bool displayVolume = false;         /**< ������Ӱ���־ */  
float ExtendAmount = 5.0f;          /**< �������� */

/** �ڵ��嶥������ */
CVector4 ShadowObject[MAX_SHADOW_CASTER_POINTS];


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
	sp = false;
	
}


/** ��ʼ��OpenGL */
bool Test::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.2f, 0.2f, 0.2f, 0.5f);						
	glClearDepth(1.0f);											
	glEnable(GL_DEPTH_TEST);
	ResizeDraw(true);	                             /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

   /** ���ù�Դ���� */
   float ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
   float diffuseLight[] = {1.0, 1.0, 1.0, 1.0}; 
   float specularLight[] = {1.0, 1.0, 1.0, 1.0};

   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
   
   /** ���ù��պ͹�Դ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	
	/** �������� */
	glEnable(GL_TEXTURE_2D);
	
	if(!ground.Load("ground.tga"))
	{
		MessageBox(NULL,"��������ʧ��!","����",MB_OK);
		exit(-1);
	}

	/** ��ʼ������ */
	if(!m_Font.InitFont())
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);

   /** ��ʼ���ڵ���λ�� */
   ShadowObject[0] = CVector4(-1.0f, 2.5f, -1.0f);
   ShadowObject[1] = CVector4(-1.0f, 2.5f,  1.0f);
   ShadowObject[2] = CVector4(1.0f, 2.5f,  1.0f);
   ShadowObject[3] = CVector4(1.0f, 2.5f, -1.0f);

	return true;                                            /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Test::Uninit()									
{
}

/** ������º��� */
void Test::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

	/** ���ƹ�Դλ���ƶ� */
	if(m_Keys.IsPressed(VK_UP))
		lightPos.z -= 0.01f;
	if(m_Keys.IsPressed(VK_DOWN))
		lightPos.z += 0.01f;

	if(m_Keys.IsPressed(VK_LEFT))
		lightPos.x -= 0.01f;
    if(m_Keys.IsPressed(VK_RIGHT))
		lightPos.x += 0.01f;
   
	/** �ո���л��Ƿ������Ӱ�� */
	if(m_Keys.IsPressed(VK_SPACE) && !sp)
     {  
	   sp =true;
	   displayVolume = !displayVolume;
     }
     if(!m_Keys.IsPressed(VK_SPACE))
	   sp =false;
	    
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
	
	/** ���֡�� */
	CaculateFrameRate();                               /**< ����֡�� */
    sprintf(string,"FPS:%3.0f",m_Fps);                 /**< �ַ�����ֵ */
	m_Font.PrintText(string, -5.0f,3.0f);              /**< ����ַ��� */
	glPopAttrib();
		
}

/** ��Ⱦ�����е����� */
void Test::render()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  	glTranslatef(0.0f, -2.0f, -10.0f);
	
	/** ���Ƶ��� */
	glDisable(GL_LIGHTING);
	glPushMatrix();

	   /** ָ������ */
	   glBindTexture(GL_TEXTURE_2D, ground.ID);

       ///�����ı���
      glBegin(GL_QUADS);
		 glNormal3f(0.0f, 1.0f, 0.0f); /**< ָ������ */
         glTexCoord2f(0.0, 0.0); glVertex3f(15.0f, -0.01f, 15.0f);
         glTexCoord2f(1.0, 0.0); glVertex3f(-15.0f, -0.01f, 15.0f);
         glTexCoord2f(1.0, 1.0); glVertex3f(-15.0f, -0.01f, -15.0f);
         glTexCoord2f(0.0, 1.0); glVertex3f(15.0f, -0.01f, -15.0f);
      glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	
	/** ����Բ�� */
	glPushMatrix();
        glDisable(GL_TEXTURE_2D);
		glTranslatef(-2.0f, 0.8f, -0.2f);
		auxSolidTorus(0.2f, 0.4f);
	glPopMatrix();

   /** ���������� */
	glPushMatrix();
		glTranslatef(0.0f, 0.8f, -0.2f );
		auxSolidCube(1.0f);
	glPopMatrix();

   /** �������� */
	glPushMatrix();
		glTranslatef(2.0f, 0.8f, -0.2f);
		auxSolidSphere(0.7f);
    glPopMatrix();

   /** �����ڵ��� */
   glPushMatrix();
     glBegin(GL_QUADS);
  			glNormal3f(0, 1, 0);
        	glVertex3f(ShadowObject[0].x, ShadowObject[0].y, ShadowObject[0].z);
        	glVertex3f(ShadowObject[1].x, ShadowObject[1].y, ShadowObject[1].z);
			glVertex3f(ShadowObject[2].x, ShadowObject[2].y, ShadowObject[2].z);
			glVertex3f(ShadowObject[3].x, ShadowObject[3].y, ShadowObject[3].z);
	glEnd();
  glPopMatrix();


   /** ���ƹ�Դ */
	glDisable(GL_LIGHTING);
	glPushMatrix();

	    /** ���ù�Դλ�� */
		float lp[4];		
		
		lp[0] = lightPos.x; 
		lp[1] = lightPos.y;
		lp[2] = lightPos.z; 
		lp[3] = lightPos.w;
		glLightfv(GL_LIGHT0, GL_POSITION, lp);
	
		/** ��ʼ���� */
		glTranslatef(lightPos.x,lightPos.y, lightPos.z);
		glColor3f(1.0f, 1.0f, 0.5f);
		auxSolidSphere(0.1);
		glColor3f(1.0f,1.0f,1.0f);  
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	
}

/** ������Ӱ�� */
void Test::DrawSilhouette(CVector4 lightPos, float Extend)
{
   CVector4 Extended;     
   int A, B;

   /** �رչ��� */
   glDisable(GL_LIGHTING);

   /** ������ɫ */
   glColor3f(0.5f, 0.7f, 0.5f);

   /** ��ÿ�����㶼���� */
   for(int i = 0; i < MAX_SHADOW_CASTER_POINTS; i++)
      {
          
          A = i; B = i + 1;

          /** �߽��� */
          if(B >= MAX_SHADOW_CASTER_POINTS) B = 0;

         /** �����ı��� */
         glBegin(GL_QUADS);

            /** ԭʼ����A */
            glVertex3f(ShadowObject[A].x, ShadowObject[A].y, ShadowObject[A].z);

            /** ����A�����ĵ� */
            Extended.ExtendVertexPos(ShadowObject[A], lightPos, Extend);
            glVertex3f(Extended.x, Extended.y, Extended.z);

            /** ����B�����ĵ� */
            Extended.ExtendVertexPos(ShadowObject[B], lightPos, Extend);
            glVertex3f(Extended.x, Extended.y, Extended.z);

            /** ԭʼ����B */
            glVertex3f(ShadowObject[B].x, ShadowObject[B].y, ShadowObject[B].z);

         glEnd();
      }

   glEnable(GL_LIGHTING);
}

/** ���ƺ��� */
void Test::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);			
	glLoadIdentity();
    
	/** �ر���ɫ����д�� */
	 glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	 
	 /** ��Ⱦ���� */
	 render();
	

	/** ָ��ģ�滺����� */
    glEnable(GL_CULL_FACE);
    glEnable(GL_STENCIL_TEST);   
    glDepthMask(GL_FALSE);
    glStencilFunc(GL_ALWAYS, 0, 0);

	/** ������Ӱ��,ģ��ֵ��1 */   
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glCullFace(GL_BACK);
	DrawSilhouette(lightPos, ExtendAmount);

	/** �ٴλ�����Ӱ��,ģ��ֵ��1 */
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	glCullFace(GL_FRONT);
	DrawSilhouette(lightPos, ExtendAmount);

	///�ָ���ǰ������
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);

	/** ������Ӱ���� */
    glDisable(GL_LIGHT0);
	glStencilFunc(GL_EQUAL, 1, 1);
	render();

	/** ������Ӱ����Ĳ��� */
    glEnable(GL_LIGHT0);
	glStencilFunc(GL_EQUAL, 0, 1);
	render();

	/** �ر�ģ����� */
	glDepthFunc(GL_LESS);
	glDisable(GL_STENCIL_TEST);

    /** ������Ӱ�� */
	if(displayVolume == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   /**< ָ���߿�ģʽ */
		DrawSilhouette(lightPos, ExtendAmount);      /**< ������Ӱ�� */
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);   /**< �ָ����ģʽ */
	}

	/** �����Ļ��Ϣ */ 
	PrintText();
		
	glFlush();	                 /**< ǿ��ִ�����е�OpenGL���� */
}
