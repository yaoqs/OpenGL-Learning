//========================================================
/**
*  @file      Font.h
*
*  ��Ŀ������ ��Ӱ��
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-02
*
*/     
//========================================================
#ifndef	__GLFONT_H__
#define	__GLFONT_H__

#include "stdafx.h"

/** ���������� */
class GLFont															
{
public:
    /** ���캯������������ */
	GLFont();
	~GLFont();
    ///��Ա����
	bool InitFont();  /**< ��ʼ������ */
	void PrintText(char *string, float x, float y); /**< ��(x,y)�����string���� */
	
protected:
	HFONT m_hFont;  /**< ������ */
		
};

#endif	// __GLFONT_H__