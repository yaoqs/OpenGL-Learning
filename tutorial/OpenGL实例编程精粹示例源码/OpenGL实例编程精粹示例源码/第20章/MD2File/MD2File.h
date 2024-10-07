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
#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "Font.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Terrain.h"
#include "MD2Loader.h"



/** ��GL_Application������һ������ */
class Test : GLApplication								
{
public:
	bool	Init();							   /**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						   /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		   /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							   /**< ִ�����еĻ��Ʋ��� */
	
	
	void    UpdateCamera();                    /**< ��������� */
	void    CaculateFrameRate();               /**< ����֡�� */
	void    PrintText();                       /**< ���������Ϣ */
		
	void    Animate(float x,float z,
		            float h,float scale);      /**< ����MD2���� */
private:
	friend class GLApplication;				   
	Test(const char * class_name);	      /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	CMD2Loader m_MD2;                         /**< MD2������ */
	CTerrain   m_Terrain;                     /**< ������ */
	CSkyBox    m_SkyBox;                      /**< ����� */
	GLFont     m_Font;                        /**< ������ */
	Camera     m_Camera;                      /**< ������� */     
  	float      m_Fps;                         /**< ֡�� */
	bool       m_RenderMode;		          /**< ����ģʽ */
	bool       sp;                            /**< �ո���Ƿ��ͷ� */
	bool       mp;                            /**< 'M'���Ƿ��ͷ� */
};

#endif	// __TEST_H__