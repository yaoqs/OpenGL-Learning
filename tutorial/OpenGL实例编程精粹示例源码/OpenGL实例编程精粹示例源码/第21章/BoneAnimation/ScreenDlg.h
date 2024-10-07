//========================================================
/**
*  @file      ScreenDlg.h
*
*  ��Ŀ������ ��������
*  �ļ�����:  ģʽѡ��Ի�����    
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-10-13	
*  �޸����ڣ� 2006-12-02
*
*/     
//========================================================
#ifndef	__SCREENDLG_H__
#define	__SCREENDLG_H__

#include "GLWindow.h"											/**< ����GLWindow.hͷ�ļ� */

/** ����ģʽѡ��Ի����� */
class ScreenDlg
{
public:
	ScreenDlg(void);   /**< ���캯�� */
	~ScreenDlg(void);  /**< �������� */

	void SetupWindow(GLWindow *pWindow); /**< ���ô��ڣ��������Ի��� */
    
	///�Ի�����Ϣ����ص�����
	static LRESULT CALLBACK ScreenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static GLWindow *m_pWindow; /**< ȫ�ִ����� */
};
#endif //__SCREENDLG_H__