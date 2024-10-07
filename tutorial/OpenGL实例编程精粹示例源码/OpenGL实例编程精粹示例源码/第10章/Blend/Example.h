//=========================================================================
/**
*  @file  Example.h
*
*  ��Ŀ������ OpenGL���
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-28
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

#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__


#include "GLFrame.h"            /**< ���������Ŀ���� */
#include "CBMPLoader.h"         /**< ����λͼ������ */    

/** ��GL_Application������һ������ */
class Example : GLApplication								
{
public:
	bool	Init();										/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();										/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);							/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();												/**< ִ�����еĻ��Ʋ��� */

	bool    LoadTexture();                                        /**< װ������ */
	void    DrawBox(float r);                                     /**< ����һ������ */

private:
	friend class GLApplication;								/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Example(const char * class_name);						/**< ���캯�� */

	/** �û��Զ���ĳ������ */
	CBMPLoader  Texture;          /**< λͼ������Ķ��� */
	float  rot;					  /**< ������ת���� */

	
};

#endif	// __EXAMPLE_H__