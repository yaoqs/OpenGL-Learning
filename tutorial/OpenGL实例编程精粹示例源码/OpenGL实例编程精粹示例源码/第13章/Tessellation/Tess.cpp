//=========================================================================
/**
*  @file      Tess.cpp
*
*  ��Ŀ������ OpenGL����
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

#include "Tess.h"						    /**< ����ͷ�ļ� */

#include <gl\gl.h>							/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>	
#include <stdio.h>

#pragma comment(lib, "opengl32.lib")		/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")	

#ifndef CALLBACK                            /**< �Է���CALLBACKʹ�ÿն��� */
#define CALLBACK
#endif

/** ����εĻ���ģʽ */
GLuint polygonMode[] = { GL_FILL, GL_LINE }; /**< ���ģʽ���߿�ģʽ */
GLuint polyMode = 0;                         /**< ����λ���ģʽ���� */

/** ���ƹ��� */
GLdouble TessProperty[5] = 
{
	GLU_TESS_WINDING_ODD,        /**< ������Ϊ���� */
	GLU_TESS_WINDING_NONZERO,    /**< ������Ϊ��0 */
	GLU_TESS_WINDING_POSITIVE,   /**< ������Ϊ���� */
	GLU_TESS_WINDING_NEGATIVE,   /**< ������Ϊ���� */
	GLU_TESS_WINDING_ABS_GEQ_TWO /**< ����������ֵ���ڵ���2 */
 };
GLuint nProperty=0;              /**< ���ƹ������� */

/** �����ַ���,���������Ϣ */
char * TessWinding[] = 
{
	"GLU_TESS_WINDING_ODD",        /**< ������Ϊ���� */
	"GLU_TESS_WINDING_NONZERO",    /**< ������Ϊ��0 */
	"GLU_TESS_WINDING_POSITIVE",   /**< ������Ϊ���� */
	"GLU_TESS_WINDING_NEGATIVE",   /**< ������Ϊ���� */
	"GLU_TESS_WINDING_ABS_GEQ_TWO" /**< ����������ֵ���ڵ���2 */
};
/** gluTessCallbackע��Ļص����� */
void CALLBACK beginCallback(GLenum which)
{
   glBegin(which);
}

void CALLBACK errorCallback(GLenum errorCode)
{
   const GLubyte *string;
   ///���������Ϣ
   string = gluErrorString(errorCode);
   fprintf(stderr, "Tessellation Error: %s\n", string);
   exit(0);
}

void CALLBACK endCallback(void)
{
   glEnd();
}

void CALLBACK vertexCallback(GLvoid *vertex)
{
   
 GLdouble* pt;
 GLubyte red, green, blue;
 pt = (GLdouble* )vertex;
 /** �漴������ɫֵ */
 red   = (GLubyte)rand() & 0xff;   
 green = (GLubyte)rand() & 0xff;  
 blue  = (GLubyte)rand() & 0xff; 
 glColor3ub(red, green, blue);
 glVertex3dv(pt);

}

/** ���ڴ����������߽��㣬�������Ƿ�ϲ����㣬
    �´����Ķ�����������4�����ж���������ϣ���Щ��������洢��data��
    ����weightΪȨ�أ�weight[i]���ܺ�Ϊ1.0
 */
void CALLBACK combineCallback(GLdouble coords[3], 
                              GLdouble *vertex_data[4],
                              GLfloat weight[4], 
							  GLdouble **dataOut )
{
   GLdouble *vertex;
   int i;
   /** ����洢�¶�����ڴ� */
   vertex = (GLdouble *) malloc(6 * sizeof(GLdouble));
   
   /** �洢����ֵ */
   vertex[0] = coords[0];
   vertex[1] = coords[1];
   vertex[2] = coords[2];
   
   /** ͨ����ֵ����RGB��ɫֵ */
   for (i = 3; i < 6; i++)
      vertex[i] = weight[0] * vertex_data[0][i] + 
                  weight[1] * vertex_data[1][i] + 
                  weight[2] * vertex_data[2][i] + 
                  weight[3] * vertex_data[3][i];
   *dataOut = vertex;
}

/** ��ʼ��������� */
bool Tess::InitTess()
{
	/** ��������������� */
	GLdouble rectOut[4][3] = { -5.0, -5.0, 0.0,
                                5.0, -5.0, 0.0,
                                5.0,  5.0, 0.0,
                               -5.0,  5.0, 0.0};
	/** �����ھ������� */
    GLdouble rectIn[4][3] = { -2.0, -2.0, 0.0,
		                       2.0, -2.0, 0.0, 
							   2.0,  2.0, 0.0,
		                      -2.0,  2.0, 0.0						   
                              };
   /** ������������������ */
   GLdouble star[6][3] = { -5.1, -3.0, 0.0, 5.1, -3.0, 0.0,  0.0, 6.0, 0.0, 
                            0.0, -6.0, 0.0, 5.1,  3.0, 0.0, -5.1, 3.0, 0.0};

   
   list = glGenLists(2);/**< ��ȡ������ʾ�б����� */
   
   tobj = gluNewTess(); /**< �������񻯶��� */
   /** ע��ص����� */
   gluTessCallback(tobj, GLU_TESS_VERTEX, 
                   (void(__stdcall*)())glVertex3dv);
   gluTessCallback(tobj, GLU_TESS_BEGIN, 
                   (void(__stdcall*)())beginCallback);
   gluTessCallback(tobj, GLU_TESS_END, 
                   (void(__stdcall*)())endCallback);
   gluTessCallback(tobj, GLU_TESS_ERROR, 
                   (void(__stdcall*)())errorCallback);
   /** ����һ����ʾ�б�*/
   glNewList(list, GL_COMPILE);
   /** ���û��ƹ��� */
   gluTessProperty(tobj, GLU_TESS_WINDING_RULE,
                   TessProperty[nProperty]);
   /** ��ʼ����һ������� */    
   gluTessBeginPolygon(tobj, NULL);
      gluTessBeginContour(tobj);
         gluTessVertex(tobj, rectOut[0], rectOut[0]);
         gluTessVertex(tobj, rectOut[1], rectOut[1]);
         gluTessVertex(tobj, rectOut[2], rectOut[2]);
         gluTessVertex(tobj, rectOut[3], rectOut[3]);
      gluTessEndContour(tobj);
      
	  gluTessBeginContour(tobj);
         gluTessVertex(tobj, rectIn[0], rectIn[0]);
         gluTessVertex(tobj, rectIn[1], rectIn[1]);
         gluTessVertex(tobj, rectIn[2], rectIn[2]);
		  gluTessVertex(tobj, rectIn[3], rectIn[3]);
      gluTessEndContour(tobj);
   gluTessEndPolygon(tobj);
   glEndList();           /**< ������ʾ�б� */

   /** ע��ص����� */
   gluTessCallback(tobj, GLU_TESS_VERTEX, 
                   (void(__stdcall*)())vertexCallback);
   gluTessCallback(tobj, GLU_TESS_BEGIN, 
                   (void(__stdcall*)())beginCallback);
   gluTessCallback(tobj, GLU_TESS_END, 
                   (void(__stdcall*)())endCallback);
   gluTessCallback(tobj, GLU_TESS_ERROR, 
                   (void(__stdcall*)())errorCallback);
   gluTessCallback(tobj, GLU_TESS_COMBINE, 
                   (void(__stdcall*)())combineCallback);
   
   /** �����ڶ�����ʾ�б� */
   glNewList(list + 1, GL_COMPILE);
   /** ���û��ƹ��� */
   gluTessProperty(tobj, GLU_TESS_WINDING_RULE,
                   TessProperty[nProperty]);
   /** ��ʼ����һ������� */
   gluTessBeginPolygon(tobj, NULL);
      gluTessBeginContour(tobj);     /**< ����������1 ��ʱ�������� */
		gluTessVertex(tobj, star[0], star[0]);
		gluTessVertex(tobj, star[1], star[1]);
		gluTessVertex(tobj, star[2], star[2]);
      gluTessEndContour(tobj);
	  
	  gluTessBeginContour(tobj);     /**< ����������1 ��ʱ�������� */
		gluTessVertex(tobj, star[3], star[3]);
		gluTessVertex(tobj, star[4], star[4]);
		gluTessVertex(tobj, star[5], star[5]);
      gluTessEndContour(tobj);
  gluTessEndPolygon(tobj);
  glEndList();                /**< ������ʾ�б� */

  return true;
}
/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Tess * tess = new Tess(class_name);
	return reinterpret_cast<GLApplication *>(tess);
}


/** ���캯�� */
Tess::Tess(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;				/**< ���ó�ʼ�Ƕ�Ϊ0 */
	wp = false;
	sp = false;
	
}

/** ��ʼ��OpenGL */
bool Tess::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	     /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
    /** ��ʼ��������� */
	if(!InitTess())
	{
		MessageBox(NULL,"��ʼ�����񻯶���ʧ��!","����",MB_OK);
		return false;
	}
	if(!font.InitFont())
	{
		MessageBox(NULL,"��ʼ������ʧ�ܣ�","����",MB_OK);
	}

	return true;             /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Tess::Uninit()									
{
/** �û��Զ����ж�ع��� */
   if(list != 0)             /**< ɾ����ʾ�б����� */
	   glDeleteLists(list,2);  
   gluDeleteTess(tobj);      /**< ɾ�����񻯶��� */

 }

/** ������º��� */
void Tess::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

/** �û��Զ���ĸ��¹��� */
	if(m_Keys.IsPressed('W') && !wp )          /**< W���Ƿ񱻰��£�*/
	{
		wp = true;                             /**< �� */
        
		polyMode += 1;
		if(polyMode > 1)                       
			polyMode = 0;                      /**< ���� */
		/** ���ö���λ���ģʽ */
		glPolygonMode(GL_FRONT_AND_BACK,polygonMode[polyMode]);

	}
	if(!m_Keys.IsPressed('W'))                /**< W���Ƿ��ͷţ�*/
	{
		wp = false;                           /**< �ǣ�������Ϊ�ͷ� */
	}

	if(m_Keys.IsPressed(VK_SPACE) && !sp )     /**< �ո���Ƿ񱻰��£�*/
	{
		sp = true;                             /**< �� */
        
		nProperty += 1;
		if(nProperty > 4)
			nProperty = 0;                     /**< ���� */
		InitTess();                            /**< ��ʼ��������� */

	}
	if(!m_Keys.IsPressed(VK_SPACE))            /**< �ո���Ƿ��ͷţ�*/
	{
		sp = false;                            /**< �ǣ�������Ϊ�ͷ� */
		
	}
    
	/** ������ת�ĽǶ� */
	m_Angle += (float)(milliseconds) / 15.0f;
     
}

/** ���ƺ��� */
void Tess::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	
	//glTranslatef(0.0f, 0.0f, -30.0f);
	/** ���ƴ��յ������� */	
	glPushMatrix();
	  glTranslatef(-6.0f, 0.0f, -30.0f);
	  glRotatef(m_Angle,1.0f,1.0f,1.0f);
	  glColor3f(1.0f,1.0f,0.0f);
	  glCallList(list);
	glPopMatrix();
    
	/** ���ƻ��������������һ�������� */
	glPushMatrix();
	  glTranslatef(6.0f, 0.0f, -30.0f);
	  glRotatef(m_Angle,1.0f,1.0f,1.0f);
	  glCallList(list + 1);
	glPopMatrix();
    /** ���һЩ��Ϣ */
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-1.0f);
	glColor3f(0.0f,1.0f,1.0f);              /**< ָ����ɫ */
	char string[128];                       /**< �����ǰ����ģʽ */
	sprintf(string, "��ǰ����ģʽ��%s",TessWinding[nProperty]);
	font.PrintText(string,-5.0f,3.0f);
	sprintf(string,"�ո��---�л�����ģʽ");
	font.PrintText(string,-5.0f,2.0f);
    glPopMatrix();

	glFlush();							    /**< ǿ��ִ�����е�OpenGL���� */
}
