//======================================================================
/**
*  @file      BMPLoader.h
*
*  ��Ŀ������ ��ײ���
*  �ļ�����:  ����λͼ�� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-11-23	
*  �޸����ڣ� 2006-11-26
*	
*/																			
//======================================================================

#ifndef __BMPLOADER_H__
#define __BMPLOADER_H__

#include "stdafx.h"

#define BITMAP_ID 0x4D42	/**< λͼ�ļ��ı�־ */

/** λͼ������ */
class CBMPLoader
{
   public:
      CBMPLoader();
      ~CBMPLoader();

      bool LoadBitmap(const char *filename); /**< װ��һ��bmp�ļ� */
      void FreeImage();                /**< �ͷ�ͼ������ */

      unsigned int ID;                 /**< ���������ID�� */
      int imageWidth;                  /**< ͼ���� */
      int imageHeight;                 /**< ͼ��߶� */
      unsigned char *image;            /**< ָ��ͼ�����ݵ�ָ�� */
};

#endif //__BMPLOADER_H__

