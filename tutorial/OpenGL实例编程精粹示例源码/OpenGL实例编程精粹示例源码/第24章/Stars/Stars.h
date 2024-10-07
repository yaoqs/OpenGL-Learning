//=========================================================================
/**
*  @file      Protechny.h
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-18
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

#ifndef __TEST_H__
#define __TEST_H__

#include "stdafx.h"
#include "BMPLoader.h"
#include "Font.h" 
#include "GLFrame.h"	
#include "Particle.h"


/** ��GL_Application������һ������ */
class Test : GLApplication								
{
public:
	bool	Init();							   /**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						   /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		   /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							   /**< ִ�����еĻ��Ʋ��� */
	
	void    DrawParticle();                    /**< �������� */
		
	bool    InitStars();                   /**< ��ʼ����Ȫ */
	void    UpdateStars();                 /**< ������Ȫ */
	
	void    PrintText();                       /**< �����Ϣ */
	void    CaculateFrameRate();               /**< ����֡�� */

private:
	friend class GLApplication;				   
	Test(const char * class_name);	          /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	
	CParticle*       Stars;        /**< ����ϵͳ�Ķ��� */
   	GLFont           m_Font;          /**< ������ */
	float            m_Fps;           /**< ����֡�� */
	float            angle;           /**< �������ת�Ƕ� */
			
};

#endif	// __TEST_H__