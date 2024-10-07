//=========================================================================
/**
*  @file      Snow.cpp
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-18
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
#include "Snow.h"						    


/** �����������ӵ�����ֵ */
float x,y,z,vx,vy,vz,ax,ay,az,size,lifetime,dec;
int r,g,b;


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
	Snow = new CParticle();
	m_Fps = 0;
	angle =0;
	
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
	ResizeDraw(true);	                             
	 
	glEnable(GL_TEXTURE_2D);             /**< ��������ӳ�� */      
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);    /**< ���û�����ӻ�ð�͸��Ч�� */
	glEnable(GL_BLEND);				     /**< ���û�� */

	/** ��ʼ������ */
	if(!m_Font.InitFont())
	{
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
		exit(-1);
	}
 
	/**  �������� */
	if(!Snow->LoadTextures())
	{
		MessageBox(NULL,"��������ʧ��!","����",MB_OK);
		exit(-1);
	}
	
	/** ����500������ */
	Snow->Create(500);
	
	/** ��ʼ������ */
	InitSnow();
	
	return true;                                        /**< �ɹ����� */
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

/** ���Ƶ��� */
void Test::DrawGround()
{
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-6.0f);
	glRotatef(angle,0.0f,1.0f,0.0f);   

	/** ָ������ */
	glBindTexture(GL_TEXTURE_2D,Snow->GetTexture(0));
	glColor4ub(255,255,255,255);
	glNormal3f(0.0f,1.0f,0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);glVertex3f(-2.5f,-1.0f,2.5f);
		glTexCoord2f(1.0f,0.0f);glVertex3f(-2.5f,-1.0f,-2.5f);
		glTexCoord2f(1.0f,1.0f);glVertex3f(2.5f,-1.0f,-2.5f);
		glTexCoord2f(0.0f,1.0f);glVertex3f(2.5f,-1.0f,2.5f);
	glEnd();
	glPopMatrix();
	
	/** ����ת���ĽǶ� */
	angle += 0.02f;
}

/** ��ʼ��ѩ������ */
bool Test::InitSnow()
{
	for (int i=0; i < Snow->GetNumOfParticle(); ++i)
	{
		///��ʼ����ɫ
		r = 255;
		g = 255;
		b = 255;

		Snow->SetColor(i,r,g,b);

		///��ʼ������
		x = 0.1f * (rand() % 50) - 2.5f;
		y = 2 + 0.1f * (rand() % 2);
		if((int)x % 2 == 0)
			z = rand()%6;
		else 
			x = -rand()%3;

		Snow->SetPosition(i,x,y,z);

		///��ʼ���ٶ�
		vx = 0.00001 * (rand()%100);
		vy = 0.0000002 * (rand()%28000);
		vz = 0;

		Snow->SetVelocity(i,vx,vy,vz);

		///��ʼ�����ٶ�
		ax = 0;
		ay = 0.000005f;
		az = 0;
		
		Snow->SetAcceleration(i,ax,ay,az);

		///��ʼ����������
		lifetime = 100;
		Snow->SetLifeTime(i,lifetime);

		///��ʧ�ٶ�
		dec = 0.005 * (rand()%50);
		Snow->SetDec(i,dec);

		///��ʼ����С
		Snow->SetSize(i,0.03f);

	}
	return true;
}

/** �������� */
void Test::DrawParticle()
{
	/** ������ */
	glBindTexture(GL_TEXTURE_2D,Snow->GetTexture(1));
	
	for(int i = 0; i<Snow->GetNumOfParticle(); ++i)
	{
		/** ������ӵ��������� */
		Snow->GetAll(i,r,g,b,x,y,z,vx,vy,vz,ax,ay,az,size,lifetime,dec);
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,-6.0f);
		glColor4ub(r,g,b,255);
		glNormal3f(0.0f,0.0f,1.0f);   /**< ���巨�߷��� */
		/** �������� */
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);glVertex3f(x-size,y-size,z);
			glTexCoord2f(1.0f,0.0f);glVertex3f(x-size,y+size,z);
			glTexCoord2f(1.0f,1.0f);glVertex3f(x+size,y+size,z);
			glTexCoord2f(0.0f,1.0f);glVertex3f(x+size,y-size,z);
		glEnd();
		
		/** ������������ */
		UpdateSnow();
		Snow->SetAll(i,r,g,b,x,y,z,vx,vy,vz,ax,ay,az,size,lifetime,dec);
		
	}
}

/** �������� */
void Test::UpdateSnow()
{
	/** ����λ�� */
	x += (vx * 5);
	y -= vy;

	/** �����ٶ� */
	vy += ay;
	
	/** ��������ʱ�� */
	lifetime -= dec;
	
	if(x > 3)
		x = -2;

	/** ���������ʧ���������� */
	if (y <= -1 || lifetime <= 0)
	{
		/** ��ʼ��λ�� */
		x = 0.1f * (rand()%50) - 2.5f;
		y = 2 + 0.1f * (rand()%2);
		if((int)x%2 == 0)
			z = rand()%6;
		else 
			z = -rand()%3;
		
		/** ��ʼ���ٶ� */
		vx = (float)(0.00001 * (rand()%100));
		vy = (float)(0.0000002 * (rand()%28000));
		vz = 0;
		
		/** ��ʼ�����ٶ� */
		ax = 0;
		ay = 0.000005f;
		az = 0;
		lifetime = 100;
		dec = 0.005*(rand()%50);
	}
}

/** ���ƺ��� */
void Test::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
	
	/** ���Ƶ��� */
	DrawGround();

	/** �������� */
	DrawParticle();

	/** �����Ϣ */
	PrintText();
		
	glFlush();	                     /**< ǿ��ִ�����е�OpenGL���� */
}
