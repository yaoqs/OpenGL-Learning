//=========================================================================
/**
*  @file  Material.h
*
*  ��Ŀ������ OPenGL����
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

#ifndef __MATERIAL_H__
#define __MATERIAL_H__


#include "GLFrame.h"												/**< ���������Ŀ���� */

/** ��GL_Application������һ������ */
class Material : GLApplication								
{
public:
	bool	Init();										/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();										/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);							/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();												/**< ִ�����еĻ��Ʋ��� */

private:
	friend class GLApplication;								/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Material(const char * class_name);						/**< ���캯�� */
/** �û��Զ���ĳ������ */
	 
	float m_Angle;                                     /** ������ת���� */
   

};


#endif	// __MATERIAL_H__