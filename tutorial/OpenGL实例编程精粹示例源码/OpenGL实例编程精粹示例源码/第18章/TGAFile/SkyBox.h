//========================================================
/**
*  @file      SkyBox.h
*
*  ��Ŀ������ TGA�ļ�����
*  �ļ�����:  ��պ���  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-10
*
*/     
//========================================================
#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "stdafx.h"
#include "CBMPLoader.h"
#include "Vector.h"
#include "Camera.h"

#define GL_CLAMP_TO_EDGE	0x812F

/** ��պ��� */
class CSkyBox
{
public:
	/** ���캯�� */
	CSkyBox();
	~CSkyBox();

	/** ��ʼ�� */
	bool Init();
	
	/** ��Ⱦ��� */
	void  CreateSkyBox(float x, float y, float z, 
		               float width, float height, 
					   float length);

private:
	
	CBMPLoader  m_texture[6];   /**< ��պ����� */
		
};


#endif ///__SKYBOX_H__