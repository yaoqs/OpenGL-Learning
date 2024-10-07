//=========================================================================
/**
*  @file      Quadrics.cpp
*
*  ��Ŀ������ ��������
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-04
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

#include "Quadrics.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>	 
                                      


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

/** ����ģʽ */
GLint renderMode[] = { GLU_FILL,GLU_LINE,GLU_SILHOUETTE };
GLuint mode = 0;  /**< ����ģʽ���� */

/** ���������Ϣ */
char *RenderMode[] = 
{
	"GLU_FILL",
	"GLU_LINE",
	"GLU_SILHOUETTE"
};

/** �����Դ������ֵ */
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	/**< ��������� */
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
GLfloat LightPosition[]= { 0.0f, 0.0f, 5.0f, 1.0f };	/**< ��Դλ�� */

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Quadrics * quad = new Quadrics(class_name);
	return reinterpret_cast<GLApplication *>(quad);
}


/** ���캯�� */
Quadrics::Quadrics(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	rot = 0.0;
	lp = FALSE;
	light = FALSE;
	
}

/** װ������ */
bool Quadrics::LoadTexture()
{
	char filename[128] ;                                         /**< ���������ļ��� */
	for(int i=0; i< 4; i++)
	{
		sprintf(filename,"data/image%d",i);
		strcat(filename,".bmp");
		if(!Texture[i].LoadBitmap(filename))                     /**< ����λͼ�ļ� */
		{
			MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
			return false;
		}
		glGenTextures(1, &Texture[i].ID);                        /**< ����һ������������� */
		 
		glBindTexture(GL_TEXTURE_2D, Texture[i].ID);             /**< ����������� */
		/** �����˲� */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		/** �������� */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture[i].imageWidth,
						Texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
					    Texture[i].image);
	}
    
	return true;
}

/** ��ʼ��OpenGL */
bool Quadrics::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);                       /**< ��������ӳ�� */
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	
	/** �������� */
	if( !LoadTexture() )
		MessageBox(NULL,"�����������!","����",MB_OK);

    /** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	/**< ��������� */
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	/**< ���ù�Դλ�� */
	/** ���ù�Դ */
	glEnable(GL_LIGHT1); 
	/** ��ʼ������ */
	if(!font.InitFont())
		MessageBox(NULL,"��ʼ������ʧ�ܣ�","����",MB_OK);

	/**< �������μ����� */
	quadratic = gluNewQuadric();							
	gluQuadricNormals(quadratic, GLU_SMOOTH);			/**< ʹ��ƽ������ */
	gluQuadricTexture(quadratic, GL_TRUE);				/**< ʹ������ */
	
	ResizeDraw(true);									/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

  	return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Quadrics::Uninit()									
{
	for(int i=0; i < 4; i++) 
	{
		Texture[i].FreeImage();               /** �ͷ�����ͼ��ռ�õ��ڴ� */
	    glDeleteTextures(1, &Texture[i].ID);  /**< ɾ��������� */
	}
	/** ɾ�����ζ��� */
	if(quadratic != NULL)
		gluDeleteQuadric(quadratic);
}

/** ������º��� */
void Quadrics::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)  /**< ��ESC�˳� */
	{
		TerminateApplication();									
	}
/** �û��Զ���ĸ��¹��� */
	if (m_Keys.IsPressed('L') && !lp)		  /**< L ���Ѱ��²����ɿ���? */
	{
		lp = TRUE;						      /**< lp ��Ϊ TRUE */
		light = !light;					      /**< �л���Դ�� TRUE/FALSE */
		if (!light)						      /**< ���û�й�Դ */
		{
			glDisable(GL_LIGHTING);		      /**< ���ù�Դ */
		}
		else							
		{
			glEnable(GL_LIGHTING);		      /**< ���ù�Դ */
		}
	}

	if (!m_Keys.IsPressed('L'))				  /**< L���ɿ���ô? */
	{
		lp = FALSE;						      /**< ���ǣ���lp��ΪFALSE */
	}

	if (m_Keys.IsPressed(VK_SPACE) && !sp)		  /**< L ���Ѱ��²����ɿ���? */
	{
		sp = TRUE;						      /**< lp ��Ϊ TRUE */
		mode += 1;
		if(mode > 2)
			mode = 0;
		
		gluQuadricDrawStyle(quadratic,renderMode[mode]);
		
	}

	if (!m_Keys.IsPressed(VK_SPACE))				  /**< L���ɿ���ô? */
	{
		sp = FALSE;						      /**< ���ǣ���lp��ΪFALSE */
	}
	
	/** ������ת�Ƕ� */
 	rot += milliseconds/20.0;
	    
}

/** ���ƺ��� */
void Quadrics::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	  /**< ������� */		
	glLoadIdentity();	
    
	/** ���ƹ��� */
	glTranslatef(0.0f,0.0f,-8.0f);
	///����Բ����
	glBindTexture(GL_TEXTURE_2D, Texture[0].ID);                      /**< ������ */
	glPushMatrix();
	  glTranslatef(-2.0f,1.1f,0.0f);
	  glRotatef(-90,1.0f,0.0f,0.0f);
      glRotatef(rot,1.0f,0.0f,1.0f);
      gluCylinder(quadratic,0.8f,0.8f,1.8f,32,32);
	glPopMatrix();
	///����Բ׶��
	glBindTexture(GL_TEXTURE_2D, Texture[1].ID);                      /**< ������ */
	glPushMatrix();
	  glTranslatef(2.0f,1.1f,0.0f);
	  glRotatef(-90,1.0f,0.0f,0.0f);
      glRotatef(rot,1.0f,0.0f,1.0f);
      gluCylinder(quadratic,1.0f,0.0f,1.8f,32,32);
    glPopMatrix();
    ///����Բ��	   
    glBindTexture(GL_TEXTURE_2D, Texture[2].ID);                      /**< ������ */
	glPushMatrix();
	  glTranslatef(-2.0f,-1.1f,0.0f);
      glRotatef(rot,0.0f,1.0f,0.0f);
	  gluDisk(quadratic,0.4f,1.2f,32,32);
	glPopMatrix();
	///��������  
	glBindTexture(GL_TEXTURE_2D, Texture[3].ID);                      /**< ������ */
	glPushMatrix();
	  glTranslatef(2.0f,-1.1f,0.0f);
      glRotatef(rot,0.0f,1.0f,0.0f);
	  gluSphere(quadratic,1.1f,32,32);
	glPopMatrix();
	/** ���һЩ��Ϣ */
	char string[256];                                                /**< ���������Ϣ */
	sprintf(string,"��ǰģʽ��%s",RenderMode[mode]);
	font.PrintText(string,-5.0f,-4.0f);
	
	glFlush();				                                           /**< ǿ��ִ�����е�OpenGL���� */
}
