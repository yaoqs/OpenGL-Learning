//=========================================================================
/**
*  @file  Fog.h
*
*  ��Ŀ������ OpenGL��Ч��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-01
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

#ifndef __FOG_H__
#define __FOG_H__


#include "GLFrame.h"            /**< ���������Ŀ���� */
  

/** ��GL_Application������һ������ */
class Fog : GLApplication								
{
public:
	bool	Init();										/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();									/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);					/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();										/**< ִ�����еĻ��Ʋ��� */

	void    DrawSphere(float x,float y,float z);        /**< ����һ������ */

private:
	friend class GLApplication;							/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Fog(const char * class_name);					/**< ���캯�� */

	/** �û��Զ���ĳ������ */
	float  z;                                           /**< ������Ļ�ľ��� */
	bool   fp;                                          /**< �ж�F���Ƿ��ͷ� */
	
};

#endif	// __FOG_H__