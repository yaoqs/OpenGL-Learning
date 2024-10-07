//=========================================================================
/**
*  @file      Stars.cpp
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
#include "stars.h"						    


/** �����������ӵ�����ֵ */
float x,y,z,vx,vy,vz,ax,ay,az,size,lifetime,dec;
int r,g,b;
float rr,al;       /**< ������ת���� */

const float PI=3.1415926535;

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
	Stars = new CParticle();
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
	if(!Stars->LoadTextures())
	{
		MessageBox(NULL,"��������ʧ��!","����",MB_OK);
		exit(-1);
	}
	
	/** ����10000������ */
	Stars->Create(10000);
	
	/** ��ʼ������ */
	InitStars();
	
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


/** ��ʼ������ */
bool Test::InitStars()
{
	for (int i=0; i < Stars->GetNumOfParticle(); ++i)
	{
		///��ʼ����ɫ
		r = 55;
		g = 55;
		b = 100;

		Stars->SetColor(i,r,g,b);

		///��ʼ������
		al = float(rand()%360)/180*PI;
		rr = (float)(rand()%4000)*0.001f;
		if (rr < 0.4) 
			rr += (rand()%10000)*0.0005;
		x = rr*cos(al);
		y = rr*sin(al);
		z = 0;
		Stars->SetPosition(i,x,y,z);
		
		///��ʼ���ٶ�
		vx = 0;
		vy = 0;
		vz = 0;	
		Stars->SetVelocity(i,vx,vy,vz);


		///��ʼ�����ٶ�
		ax = 0;
		ay = 0;
		az = 0;
		
		Stars->SetAcceleration(i,ax,ay,az);
		
		///��ʼ����С
		Stars->SetSize(i,0.015f);


	}
	return true;
}

/** �������� */
void Test::DrawParticle()
{
	/** ������ */
	glBindTexture(GL_TEXTURE_2D,Stars->GetTexture(1));
	
	for(int i = 0; i<Stars->GetNumOfParticle()/2; ++i)
	{
		/** ������ӵ��������� */
		Stars->GetAll(i,r,g,b,x,y,z,vx,vy,vz,ax,ay,az,size,lifetime,dec);
		
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
		UpdateStars();
		Stars->SetAll(i,r,g,b,x,y,z,vx,vy,vz,ax,ay,az,size,lifetime,dec);
		
	}
}

/** �������� */
void Test::UpdateStars()
{
	/** ������ת�� */
	rr = sqrt(x*x+y*y);
	al = acos(x/rr);
	if(y < 0) 
		al = -al;
	if (rr < 0.4) 
		rr += (rand()%10000)*0.0005;
	
	al += 0.005f/rr*5;
   
	/** ����λ�� */
	x = rr*cos(al);
	y = rr*sin(al);
	

}

/** ���ƺ��� */
void Test::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();

	//DrawGround();

	/** �������� */
	DrawParticle();

	/** �����Ϣ */
	PrintText();
		
	glFlush();	                     /**< ǿ��ִ�����е�OpenGL���� */
}
