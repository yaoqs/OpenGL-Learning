//========================================================
/**
*  @file      TGALoader.h
*
*  ��Ŀ������ TGA�ļ�����
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-11
*
*/     
//========================================================


#ifndef __TGALOADER_H__
#define __TGALOADER_H__

#include "stdafx.h"

/** TGA�ļ������� */
class CTGALoader
{
   public:
	  
      CTGALoader();                             /**< ���캯�� */
      ~CTGALoader();

      bool LoadTGA(const char *file);          /**< ����TGA�ļ� */
      void FreeImage();                        /**< �ͷ��ڴ� */ 
	  bool Load(const char* fileName); /**< ����TGA�ļ�Ϊ���� */

      unsigned int ID;                        /**< ���������ID�� */
      int imageWidth;                         /**< ͼ���� */
      int imageHeight;                        /**< ͼ��߶� */
      unsigned char *image;                   /**< ָ��ͼ�����ݵ�ָ�� */
      unsigned int type;                      /**< ͼ������GL_RGB ��GL_RGBA */
};


#endif