//=========================================================================
/**
*  @file      Tess.h
*
*  ��Ŀ������ OpenGL����
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

#ifndef __TESS_H__
#define __TESS_H__


#include "GLFrame.h"												/**< ���������Ŀ���� */
#include <gl\gl.h>												    /**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>
#include "Font.h"

/** ��GL_Application������һ������ */
class Tess : GLApplication								
{
public:
	bool	Init();							/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							/**< ִ�����еĻ��Ʋ��� */

	bool    InitTess();                     /**< ��ʼ�����񻯶��� */

private:
	friend class GLApplication;				/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Tess(const char * class_name);		    /**< ���캯�� */
/** �û��Զ���ĳ������ */ 
	GLFont font;                            /**< ���� */                  
	GLUtesselator *tobj;                    /**< ���񻯶���ָ�� */                
  	GLfloat m_Angle;                        /**< ��ת�Ƕ� */
	GLuint list;                            /**< ��ʾ�б����� */
	bool   wp;                              /**< �ж�W���Ƿ��ͷ� */
	bool   sp;								/**< �жϿո���Ƿ��ͷ� */
	
};


#endif	// __TESS_H__