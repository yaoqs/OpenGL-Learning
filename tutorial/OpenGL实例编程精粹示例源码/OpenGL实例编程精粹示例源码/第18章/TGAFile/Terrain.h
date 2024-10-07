//========================================================
/**
*  @file      Terrain.h
*
*  ��Ŀ������ TGA�ļ�����
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-10
*
*/     
//========================================================

#ifndef _TERRAIN_H
#define _TERRAIN_H


#include "stdafx.h"
#include "CBMPLoader.h"

/** ������ */
class CTerrain
{
public:
	/** ���캯�� */
	CTerrain();
	~CTerrain();
    
	/** ���õ��εĴ�С */
	void setSize(unsigned  int width, unsigned  int cell); 
	
	/** ��ʼ������ */
	bool initTerrain();

	/** ����'.raw'�߶�ͼ */
	bool loadRawFile(const char* fileName);

	/** װ�ص������� */
	bool loadTexture(const char * fileName);

	/** ��õ�(x,y)�ĸ߶���Ϣ */
	int getHeight(int x, int y);

	/** ��õ���߶� */
	float getAveHeight(float x, float z);

	/** ������������ */
	void setTexCoord(float x, float z);

	/** ��Ⱦ���� */
	void render();
	
private:
	unsigned  int   m_nWidth;          /**< ���������� */
	unsigned  int   m_nCellWidth;      /**< ÿһ���� */
   	BYTE*           m_pHeightMap;      /**< ��Ÿ߶���Ϣ */
	CBMPLoader      m_texture;         /**< �������� */
	
};

#endif

