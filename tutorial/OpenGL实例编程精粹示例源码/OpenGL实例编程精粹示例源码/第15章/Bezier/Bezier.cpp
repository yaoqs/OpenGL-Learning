//=========================================================================
/**
*  @file      Bezier.cpp
*
*  ��Ŀ������ Bezier����
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

#include "Bezier.h"											   /**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>	 
                                      

#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							


/** ����ģʽ */
GLint renderMode[] = { GL_FILL,GL_LINE };
GLuint mode = 0;  /**< ����ģʽ���� */

/** ���������Ϣ */
char *RenderMode[] = 
{
	"GL_FILL",
	"GL_LINE",
};

/** �����Դ������ֵ */
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	/**< ��������� */
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };	/**< ��Դλ�� */

/** �����������ֵ */
GLfloat mat_diffuse[] = { 0.4, 0.5, 0.6, 1.0 };         /**< �������� */ 
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };        /**< �������� */
GLfloat mat_shinness[] = { 50.0 };                      /**< ���淴��ָ�� */

/** ��������Ŀ��Ƶ� */
GLfloat ctrlpoints[4][4][3] = { 
	{{ -0.8f, -0.6f, 0.8f },{ -0.2f, -0.6f, 1.6f },{  0.2f, -0.6f, -0.4f },{ 0.6f, -0.6f,  0.8f }},
	{{ -0.6f, -0.2f, 0.8f },{ -0.2f, -0.2f, 1.6f },{  0.2f, -0.2f, -0.4f },{ 0.6f, -0.2f,  0.8f }},
	{{ -0.6f,  0.2f, 0.8f },{ -0.2f, -0.2f, 0.4f },{  0.2f,  0.2f,  0.0f },{ 0.3f,  0.2f, -0.4f }},
	{{ -0.6f,  0.6f, 0.8f },{ -0.2f,  0.6f, 0.4f },{ -0.8f,  0.6f,  0.0f },{ 0.8f,  0.6f, -0.4f }}
};

GLfloat texpts[2][2][2] = {{{0.0, 0.0}, {0.0, 1.0}}, {{1.0, 0.0}, {1.0, 1.0}}};

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Bezier * bezier = new Bezier(class_name);
	return reinterpret_cast<GLApplication *>(bezier);
}


/** ���캯�� */
Bezier::Bezier(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	rot = 0.0;
	light = FALSE;
	lp = FALSE;
	sp = FALSE;
	
}

/** װ������ */
bool Bezier::LoadTexture()
{
	/** ����λͼ�ļ� */
	if(!Texture.LoadBitmap("image.bmp"))                     /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
		return false;
	}
	glGenTextures(1, &Texture.ID);                           /**< ����һ������������� */
		
	glBindTexture(GL_TEXTURE_2D, Texture.ID);                /**< ����������� */
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture.imageWidth,
					Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
					Texture.image);
    
	return true;
}
/** ��ʼ��OpenGL */
bool Bezier::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);	       
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			

	/** �������� */
	if( !LoadTexture() )
		MessageBox(NULL,"�����������!","����",MB_OK);
	
	/** ��ʼ������ */
	if(!font.InitFont())
	{
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
	}
	/** ��������ӳ�� */
	glEnable(GL_TEXTURE_2D);            
	
    /** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT,  LightAmbient);		/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  LightDiffuse);		/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	    /**< ��������� */
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	    /**< ���ù�Դλ�� */
	
    /** ���ò�������ֵ */
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shinness);
    
	/** ���ù�Դ */
	glEnable(GL_LIGHT1);

	/**   */
	glEnable(GL_MAP2_VERTEX_3); 
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_AUTO_NORMAL);
	
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,&ctrlpoints[0][0][0]); 
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0][0][0]);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0); 
  
	ResizeDraw(true);									/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

  	return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Bezier::Uninit()									
{
	Texture.FreeImage();               /** �ͷ�����ͼ��ռ�õ��ڴ� */
	glDeleteTextures(1, &Texture.ID);  /**< ɾ��������� */
}

/** ������º��� */
void Bezier::Update(DWORD milliseconds)						
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

	/**   */
	if(m_Keys.IsPressed(VK_SPACE) && !sp)
	{
		sp = TRUE;
		mode += 1;
		if(mode > 1)
			mode = 0;
		glEvalMesh2(renderMode[mode],0,20,0,20);

	}
	if(!m_Keys.IsPressed(VK_SPACE))
	{
		sp = FALSE;
	}

	
	/** ������ת�Ƕ� */
 	rot += milliseconds/20.0;
	    
}

/** ���ƺ��� */
void Bezier::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	  /**< ������� */		
	glLoadIdentity();	
    
	/** ���ƹ��� */
	glTranslatef(0.0f,0.0f,-13.0f);
	glRotatef(rot,1.0,1.0,1.0);
	glScalef(3.0f,3.0f,3.0f);
	glEvalMesh2(renderMode[mode],0,20,0,20);

	char string[128];
	sprintf(string,"��ǰģʽ:%s",RenderMode[mode]);
    font.PrintText(string,-5.0f,3.0f);
    
	glFlush();				                                           /**< ǿ��ִ�����е�OpenGL���� */
}
