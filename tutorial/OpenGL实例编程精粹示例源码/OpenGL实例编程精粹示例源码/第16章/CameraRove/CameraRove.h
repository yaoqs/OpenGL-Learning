//=========================================================================
/**
*  @file      CameraRove.h
*
*  ��Ŀ������ ���������
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-02
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

#ifndef __CAMERA_ROVE_H__
#define __CAMERA_ROVE_H__

#include <windows.h>
#include <gl\gl.h>												    /**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>

#include "CBMPLoader.h"
#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "Font.h"
#include "Camera.h"


/** ��GL_Application������һ������ */
class CameraRove : GLApplication								
{
public:
	bool	Init();							/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							/**< ִ�����еĻ��Ʋ��� */
	
	bool    LoadTexture();                  /**< �������� */
    void    UpdateCamera();                 /**< ��������� */
	void    CaculateFrameRate();            /**< ����֡�� */
	void    PrintText();                    /**< ���������Ϣ */
	void    DrawGrid();                     /**< ����������� */
	void    DrawSphere();                   /**< �������� */
	void    DrawBox();                      /**< ����ľ�� */
private:
	friend class GLApplication;				/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	CameraRove(const char * class_name);	/**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	CBMPLoader m_Texture;                     /**< λͼ������ */
	GLFont     m_Font;                        /**< ������ */
	Camera     m_Camera;                      /**< ������� */     
  	float      m_Fps;                         /**< ֡�� */
				
};


#endif	// __CAMERA_ROVE_H__