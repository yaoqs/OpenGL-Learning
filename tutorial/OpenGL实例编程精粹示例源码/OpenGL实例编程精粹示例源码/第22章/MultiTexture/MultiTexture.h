//=========================================================================
/**
*  @file      Test.h
*
*  ��Ŀ������ MD2�ļ���ȡ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-11
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



/** ��GL_Application������һ������ */
class Test : GLApplication								
{
public:
	bool	Init();							   /**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						   /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		   /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							   /**< ִ�����еĻ��Ʋ��� */
	void    PrintText();                       

	bool    isExtensionSupported(const char *string);  /**< ����Ƿ�֧����չ */
	bool    initMultiTexture();     /**< ��ʼ�� */
	bool    loadTexture();          /**< װ������ */

private:
	friend class GLApplication;				   
	Test(const char * class_name);	      /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	GLFont       m_Font;                  /**< ������ */
	CBMPLoader   m_texture[4];            /**< ����4������ */
	bool         multitexturing;          /**< ��־�Ƿ�ʹ�ö������� */
	bool         sp;                      /**< �жϿո���Ƿ��ͷ� */
			
};

#endif	// __TEST_H__