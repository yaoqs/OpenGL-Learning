//=========================================================================
/**
*  @file      Protechny.cpp
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
#include "Protechny.h"						    


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
	Protechny = new CParticle();
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
	if(!Protechny->LoadTextures())
	{
		MessageBox(NULL,"��������ʧ��!","����",MB_OK);
		exit(-1);
	}
	
	/** ����10000������ */
	Protechny->Create(10000);
	
	/** ��ʼ������ */
	InitProtechny();
	
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
	glBindTexture(GL_TEXTURE_2D,Protechny->GetTexture(0));
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

/** ��ʼ������ */
bool Test::InitProtechny()
{
	for (int i=0; i < Protechny->GetNumOfParticle(); ++i)
	{
		///��ʼ����ɫ
		//r = rand()%255;
		//g = rand()%255;
		//b = rand()%255;
		r = 50;
		g = 50;
		b = 100;

		Protechny->SetColor(i,r,g,b);

		///��ʼ������
		x = 0.005f * (rand()%9);
		y = 0.005f * (rand()%9)-1;
		z = 0.005f * (rand()%6);
		Protechny->SetPosition(i,x,y,z);

		///��ʼ���ٶ�
		vx = 0.0000007f * (rand()%9000-rand()%9000);
		vy = 0.0000042f * (rand()%9000);
		vz = 0.0000001f * (rand()%9000);

		Protechny->SetVelocity(i,vx,vy,vz);


		///��ʼ�����ٶ�
		ax = 0;
		ay = -0.0002;
		az = 0;
		
		Protechny->SetAcceleration(i,ax,ay,az);
		///��ʼ����������
		lifetime = 100;
		Protechny->SetLifeTime(i,lifetime);

		///��ʧ�ٶ�
			dec=0.05*(rand()%50);
		Protechny->SetDec(i,dec);

		///��ʼ����С
			Protechny->SetSize(i,0.02f);


	}
	return true;
}

/** �������� */
void Test::DrawParticle()
{
	/** ������ */
	glBindTexture(GL_TEXTURE_2D,Protechny->GetTexture(1));
	
	for(int i = 0; i<Protechny->GetNumOfParticle(); ++i)
	{
		/** ������ӵ��������� */
		Protechny->GetAll(i,r,g,b,x,y,z,vx,vy,vz,ax,ay,az,size,lifetime,dec);
		
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
		UpdateProtechny();
		Protechny->SetAll(i,r,g,b,x,y,z,vx,vy,vz,ax,ay,az,size,lifetime,dec);
		
	}
}

/** �������� */
void Test::UpdateProtechny()
{
	/** ����λ�� */
	x += vx;
	y += vy;
	z += vz;

	/** �����ٶ� */
	vy += ay;
	
	/** ��������ʱ�� */
	lifetime -= dec;
	
	/** ���������ʧ���������� */
	if (y <= -1 || lifetime <= 0)
	{
		/** ��ʼ��λ�� */
		x = 0.005f * (rand()%9);
		y = 0.005f * (rand()%9)-1;
		z = 0.000001f * (rand()%9000);
		
		/** ��ʼ���ٶ� */
		vx = 0.0000007f * (rand()%9000-rand()%9000);
		vy = 0.0000042f * (rand()%9000);
		vz = 0.0000001f * (rand()%90000);

			
		lifetime = 100;
		dec = 0.1 * (rand()%50);
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
