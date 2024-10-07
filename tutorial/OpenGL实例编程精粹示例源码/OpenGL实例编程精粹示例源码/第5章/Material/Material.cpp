//=========================================================================
/**
*  @file  Material.cpp
*
*  ��Ŀ������ OPenGL����
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-17
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

#include "Material.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							




/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Material * material = new Material(class_name);
	return reinterpret_cast<GLApplication *>(material);
}


/** ���캯�� */
Material::Material(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
	
}

/** ��ʼ��OpenGL */
bool Material::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	///�����ԴGL_LIGHT0
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 }; /**< ������ */
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; /**< ����� */
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };/**< ����� */
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };/**< ��Դλ�� */
	
	///���ù�Դ����
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	///��ʼ��
	glClearColor(0.0f, 0.2f, 0.2f, 0.0f);						
	glClearDepth(1.0f);	
	glDepthFunc(GL_LEQUAL);	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_LIGHTING); /**< ���ù�Դ */
	glEnable(GL_LIGHT0);  /**< ����0�Ź�Դ */                                  
	
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Material::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

/** ������º��� */
void Material::Update(DWORD milliseconds)						
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
  
    m_Angle += (float)milliseconds / 30;  /**< ����������ת�Ƕ� */

}

/** ���ƺ��� */
void Material::Draw()											
{
     /** �û��Զ���Ļ��ƹ��� */
	///�����������ֵ
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 }; /** < �޲�����ɫ */
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; /** < ������ɫ */
	GLfloat mat_ambient_color[] = { 0.8, 0.6, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.2, 0.5, 0.8, 1.0 };/** < ɢ����ɫ */
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };/** < ���淴����ɫ */
	GLfloat no_shininess[] = { 0.0 };              /** < ���淴��ָ��Ϊ0 */
	GLfloat low_shininess[] = { 5.0 };             /** < ���淴��ָ��Ϊ5.0 */
	GLfloat high_shininess[] = { 100.0 };          /** < ���淴��ָ��Ϊ100.0 */
	GLfloat mat_emission[] = {0.3, 0.2, 0.3, 0.0}; /** < �������ɫ */

	//������沢���õ�λ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	
	
	/** ��һ�е�һ�л��Ƶ���������������޻�����;���⡣*/
	glPushMatrix();
		glTranslatef (-2.0, 1.75, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** ��һ�еڶ��л��Ƶ������������;���⣬���е͸߹⣬���޻����� ��*/
	glPushMatrix();
		glTranslatef (-0.75, 1.75, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();

	/** ��һ�е����л��Ƶ������������;���⣬���к����ĸ߹⣬���޻����� ��*/
	glPushMatrix();
		glTranslatef (0.75, 1.75, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** ��һ�е����л��Ƶ������������ͷ���⣬���޻����;��淴��⡣*/
	glPushMatrix();
		glTranslatef (2.0, 1.75, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** �ڶ��е�һ�л��Ƶ������������ͻ����⣬�����淴��⡣*/
	glPushMatrix();
		glTranslatef (-2.0, 0.0, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** �ڶ��еڶ��л��Ƶ�����������⡢������;���⣬���е͸߹⡣*/
	glPushMatrix();
		glTranslatef (-0.75, 0.0, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** �ڶ��е����л��Ƶ�����������⡢������;���⣬���к����ĸ߹⡣*/
	glPushMatrix();
		glTranslatef (0.75, 0.0, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** �ڶ��е����л��Ƶ�����������⡢������ͷ���⣬���޾���⡣*/
	glPushMatrix();
		glTranslatef (2, 0.0, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		auxSolidSphere(0.5); 
	glPopMatrix();

	/** �����е�һ�л��Ƶ�����������������ɫ�Ļ����⣬���޾���⡣*/
	glPushMatrix();
		glTranslatef (-2.0, -1.75, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** �����еڶ��л��Ƶ�����������������ɫ�Ļ������Լ�����⣬���е͸߹⡣*/
	glPushMatrix();
		glTranslatef (-0.75, -1.75, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** �����е����л��Ƶ�����������������ɫ�Ļ������Լ�����⣬���к����ĸ߹⡣*/
	glPushMatrix();
		glTranslatef (0.75, -1.75, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		auxSolidSphere(0.5);
	glPopMatrix();

	/** �����е����л��Ƶ�����������������ɫ�Ļ������Լ�����⣬���޾���⡣*/
	glPushMatrix();
		glTranslatef (2, -1.75, -6.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		auxSolidSphere(0.5);
	glPopMatrix();

   glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
