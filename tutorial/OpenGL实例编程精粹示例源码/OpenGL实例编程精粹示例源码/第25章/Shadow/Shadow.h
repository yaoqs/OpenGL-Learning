//=========================================================================
/**
*  @file      Shadow.h
*
*  ��Ŀ������ ƽ����Ӱ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-19
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

#ifndef __SHADOW_H__
#define __SHADOW_H__

#include "stdafx.h"

#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "Font.h"
#include "Vector.h"
#include <vector>
using namespace std;

/** ǽ�ṹ�� */
struct Wall
{
	vector<Vector3> vVerts;	/**< �������� */
	Vector3 vNormal;		/**< ������ */
	Vector3 vColor;			/**< ��ɫ */
};

/** ǽ���������Ϣ���� */
vector<Wall> walls;

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
    void    RenderWall(const Wall& wall);      /**< ����ǽ������ */
	void    RenderObjects();                   /**< �������� */
	void    RenderLight();                     /**< ���ƹ�Դ */
	
	/** ����ͶӰ���� */
	void    CreateShadowMatrix(float m[16], Vector3 point, 
		                       Vector3 normal, float lp[4]);
	/** �����������Ӱ */
	void    Render();                          
	
private:
	friend class GLApplication;				   /**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Test(const char * class_name);	           /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
 	GLFont     m_Font;                        /**< ������ */
  	float      m_Fps;                         /**< ֡�� */

};


#endif	// __SHADOW_H__