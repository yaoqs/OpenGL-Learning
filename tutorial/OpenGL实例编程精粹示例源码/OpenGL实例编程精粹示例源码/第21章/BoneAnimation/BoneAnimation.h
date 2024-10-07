//=========================================================================
/**
*  @file      BoneAnimation.h
*
*  ��Ŀ������ ��������
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-29
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

#ifndef __BoneAnimation_H__
#define __BoneAnimation_H__

#include "stdafx.h"

#include "GLFrame.h"            /**< ���������Ŀ���� */
#include "Vector.h"
#include "Bone.h"	

/** ����һЩ���� */
#define MAX_BONES                2
#define MAX_MESHES               3
#define MAX_MESH_POINTS          4

/** ��GL_Application������һ������ */
class Test : GLApplication								
{
public:
	bool	Init();							   /**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						   /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		   /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							   /**< ִ�����еĻ��Ʋ��� */

	/** ���¹��� */
	void    UpdateBones();
	
		
private:
	friend class GLApplication;				   /**< ����Ϊ����һ����Ԫ�� */
	Test(const char * class_name);	           /**< ���캯�� */

	/** �û��Զ���ĳ������ */
	CVector4      trans;                       /**< ����ƽ�ƹ���ģ�� */   
	CBone         bones[MAX_BONES];            /**< ��������ṹ */
	CMatrix4x4    displayBones[MAX_BONES];     /**< ���ڻ��ƹ��� */
	CBoneVertex   modelPoints[MAX_MESHES * MAX_MESH_POINTS]; /**< ģ�Ͷ������� */
		
};


#endif	// __BoneAnimation_H__