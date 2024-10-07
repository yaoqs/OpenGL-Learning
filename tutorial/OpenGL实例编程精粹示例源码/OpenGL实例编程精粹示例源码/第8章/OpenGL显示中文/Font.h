//========================================================
/**
*  @file  Font.h
*
*  ��Ŀ������ OpenGL��ʾ����
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-24
*
*/     
//========================================================
#ifndef	__GLFONT_H__
#define	__GLFONT_H__

#pragma warning(disable: 4267)  /**< ��ֹ��������������ת���ľ��� */
#pragma warning(disable: 4244)

/** ���������� */
class GLFont															
{
public:
    /** ���캯������������ */
	GLFont();
	~GLFont();
    ///��Ա����
	bool InitFont();  /**< ��ʼ������ */
	void Print3DText(char *string, float z = 0.05f);/**< ��3D��ʽ���string���� */
	void PrintText(char *string, float x, float y); /**< ��(x,y)�����string���� */
	
protected:
	HFONT m_hFont;  /**< ������ */
		
};

#endif	// __GLFONT_H__