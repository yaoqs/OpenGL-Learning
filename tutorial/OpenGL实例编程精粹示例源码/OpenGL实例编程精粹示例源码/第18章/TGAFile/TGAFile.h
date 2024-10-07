//=========================================================================
/**
*  @file      TGAFile.h
*
*  ��Ŀ������ TGA�ļ���ȡ
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

#ifndef __TGAFILE_H__
#define __TGAFILE_H__

#include "stdafx.h"
#include "CBMPLoader.h"
#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "Font.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Terrain.h"
#include "TGALoader.h"


/** ��GL_Application������һ������ */
class TGAFile : GLApplication								
{
public:
	bool	Init();							   /**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						   /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		   /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							   /**< ִ�����еĻ��Ʋ��� */
	
	
	void    UpdateCamera();                    /**< ��������� */
	void    CaculateFrameRate();               /**< ����֡�� */
	void    PrintText();                       /**< ���������Ϣ */
	void    DrawSphere(float x,float z,        /**< �������� */
		               float radius); 
	void    DrawBox(float x,float z,           /**< ����ľ�� */
		               float length);
		
private:
	friend class GLApplication;				   /**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	TGAFile(const char * class_name);	   /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	CTGALoader m_TGATexture[2];               /**< TGA�ļ������� */
	CTerrain   m_Terrain;                     /**< ������ */
	CSkyBox    m_SkyBox;                      /**< ����� */
	GLFont     m_Font;                        /**< ������ */
	Camera     m_Camera;                      /**< ������� */     
  	float      m_Fps;                         /**< ֡�� */
	bool       m_RenderMode;		          /**< ����ģʽ */
	bool       sp;                            /**< �ո���Ƿ��ͷ� */
};


#endif	// __TGAFILE_H__