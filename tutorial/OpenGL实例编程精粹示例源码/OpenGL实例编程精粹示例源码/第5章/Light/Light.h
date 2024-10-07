//=========================================================================
/**
*  @file  Light.h
*
*  ��Ŀ������ OPenGL����Ч����ʾ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-10-10
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

#ifndef __LIGHT_H__
#define __LIGHT_H__


#include "GLFrame.h"												/**< ���������Ŀ���� */

/** ��GL_Application������һ������ */
class Light : GLApplication								
{
public:
	bool	Init();										/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();										/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);							/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();												/**< ִ�����еĻ��Ʋ��� */

private:
	friend class GLApplication;								/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Light(const char * class_name);						/**< ���캯�� */
/** �û��Զ���ĳ������ */
	 
	float m_Angle;                                     /** ������ת���� */
    float m_bRedX;                                      /** ��ɫ�����ת�Ƕ� */
	float m_bRedY;
	float m_bGreenX;                                    /** ��ɫ�����ת�Ƕ� */
	float m_bGreenY;
	float m_bBlueX;                                     /** ��ɫ�����ת�Ƕ� */
	float m_bBlueY; 

};


#endif	// __LIGHT_H__