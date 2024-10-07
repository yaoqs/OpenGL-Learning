//=========================================================================
/**
*  @file      Bezier.h
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

#ifndef __BEZIER_H__
#define __BEZIER_H__


#include "GLFrame.h"            /**< ���������Ŀ���� */

#include <gl\gl.h>	            /**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>	

/** ��GL_Application������һ������ */
class Bezier : GLApplication								
{
public:
	bool	Init();										/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();								    /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);				    /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();									    /**< ִ�����еĻ��Ʋ��� */
	
private:
	friend class GLApplication;							/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Bezier(const char * class_name);					/**< ���캯�� */

	/** �û��Զ���ĳ������ */
	
};

#endif	// __BEZIER_H__