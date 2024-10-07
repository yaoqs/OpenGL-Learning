//=========================================================================
/**
*  @file      Quadrics.h
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

#ifndef __QUADRICS_H__
#define __QUADRICS_H__


#include "GLFrame.h"            /**< ���������Ŀ���� */
#include "CBMPLoader.h"         /**< ����λͼ������ */ 
#include "Font.h"               /**< ���������� */   
#include <gl\gl.h>	            /**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												

/** ��GL_Application������һ������ */
class Quadrics : GLApplication								
{
public:
	bool	Init();										/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();								    /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);				    /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();									    /**< ִ�����еĻ��Ʋ��� */

	bool    LoadTexture();                              /**< װ������ */
	
private:
	friend class GLApplication;							/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Quadrics(const char * class_name);					/**< ���캯�� */

	/** �û��Զ���ĳ������ */
	GLFont         font;                               /**< ������ */
	CBMPLoader     Texture[4];                         /**< λͼ������Ķ��� */
	GLUquadricObj  *quadratic;			               /**< ���μ����� */
	GLfloat        rot;					               /**< ������ת���� */
	GLboolean      light;                              /**< ���ڿ���/�رչ�Դ */
	GLboolean      lp;                                 /**< �ж�L���Ƿ��ͷ� */
	GLboolean      sp;                                 /**< �жϿո���Ƿ��ͷ� */
	                              
		
};

#endif	// __QUADRICS_H__