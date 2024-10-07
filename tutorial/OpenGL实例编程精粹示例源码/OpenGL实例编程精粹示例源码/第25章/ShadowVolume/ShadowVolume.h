//=========================================================================
/**
*  @file      ShadowVolume.h
*
*  ��Ŀ������ ��Ӱ��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-20
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

#ifndef __SHADOW_VOLUME_H__
#define __SHADOW_VOLUME_H__

#include "stdafx.h"

#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "Font.h"
#include "Vector.h"
#include "TGALoader.h"

/** ��GL_Application������һ������ */
class Test : GLApplication								
{
public:
	bool	Init();							   /**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						   /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		   /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							   /**< ִ�����еĻ��Ʋ��� */
	
	void    CaculateFrameRate();               /**< ����֡�� */
	void    PrintText();                       /**< ���������Ϣ */
  
	/** ���Ƴ������������� */
	void    render();    

	/** ������Ӱ�� */
	void    DrawSilhouette(CVector4 lightPos, float Extend);
	
private:
	friend class GLApplication;				   /**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Test(const char * class_name);	           /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	CTGALoader  ground;                        /** �������� */
 	GLFont      m_Font;                        /**< ������ */
  	float       m_Fps;                         /**< ֡�� */
	bool        sp;                            /**< �жϿո���Ƿ��ͷ� */

};


#endif	// __SHADOW_VOLUME_H__