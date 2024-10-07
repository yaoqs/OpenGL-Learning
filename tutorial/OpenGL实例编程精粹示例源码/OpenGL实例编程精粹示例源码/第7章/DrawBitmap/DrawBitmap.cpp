//=========================================================================
/**
*  @file  DrawBitmap.cpp
*
*  ��Ŀ������ OpenGL����λͼ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-20
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

#include "DrawBitmap.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							


/** �ֱ����ַ�O P E N G L��λͼ���� */ 
static GLubyte O_Rasters[13] = { 0x00,0x00, 0x7e,0xe7, 0xc3,0xc3, 0xc3,0xc3, 0xc3,0xc3, 0xc3,0xe7, 0x7e};
static GLubyte P_Rasters[13] = { 0x00,0x00, 0xc0,0xc0, 0xc0,0xc0, 0xc0,0xfe, 0xc7,0xc3, 0xc3,0xc7, 0xfe};
static GLubyte E_Rasters[13] = { 0x00,0x00, 0xff,0xc0, 0xc0,0xc0, 0xc0,0xfc, 0xc0,0xc0, 0xc0,0xc0, 0xff};
static GLubyte N_Rasters[13] = { 0x00,0x00, 0xc7,0xc7, 0xcf,0xcf, 0xdf,0xdb, 0xfb,0xf3, 0xf3,0xe3, 0xe3};
static GLubyte G_Rasters[13] = { 0x00,0x00, 0x7e,0xe7, 0xc3,0xc3, 0xcf,0xc0, 0xc0,0xc0, 0xc0,0xe7, 0x7e};
static GLubyte L_Rasters[13] = { 0x00,0x00, 0xff,0xc0, 0xc0,0xc0, 0xc0,0xc0, 0xc0,0xc0, 0xc0,0xc0, 0xc0};

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	DrawBitmap * example = new DrawBitmap(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** ���캯�� */
DrawBitmap::DrawBitmap(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	//m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
}

/** ��ʼ��OpenGL */
bool DrawBitmap::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
    
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);      /**<��ָ���������ݴ洢ģʽ */
	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void DrawBitmap::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

/** ������º��� */
void DrawBitmap::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

	///if (m_Keys.IsPressed(VK_F1) == true)						/**< ��F1�л�����/ȫ��ģʽ */
	///{
	///	ToggleFullscreen();										
	///}
/** �û��Զ���ĸ��¹��� */
     
}

/** ���ƺ��� */
void DrawBitmap::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();											
	glTranslatef(0.0f, 0.0f, -6.0f);
	/** �����ַ� OPENGL  */ 
	glColor3f (1.0, 0.0, 1.0); /**< ָ����ɫ */
	glRasterPos2i (0, 0);   /**<��ָ����դλ�� */
	///�����ַ�
	glBitmap (8, 13, 0.0, 0.0, 15.0, 0.0, O_Rasters); /**< �����ַ�O */
	glBitmap (8, 13, 0.0, 0.0, 15.0, 0.0, P_Rasters); /**< �����ַ�P */
	glBitmap (8, 13, 0.0, 0.0, 15.0, 0.0, E_Rasters); /**< �����ַ�E */
	glBitmap (8, 13, 0.0, 0.0, 15.0, 0.0, N_Rasters); /**< �����ַ�N */
	glBitmap (8, 13, 0.0, 0.0, 15.0, 0.0, G_Rasters); /**< �����ַ�G */
	glBitmap (8, 13, 0.0, 0.0, 15.0, 0.0, L_Rasters); /**< �����ַ�L */
	
   glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
