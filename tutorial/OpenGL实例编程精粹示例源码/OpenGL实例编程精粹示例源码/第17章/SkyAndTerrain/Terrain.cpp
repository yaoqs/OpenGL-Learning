//========================================================
/**
*  @file      Terrain.cpp
*
*  ��Ŀ������ ������պ͵���
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

#include "Terrain.h"
#include "CBMPLoader.h"

/** ���캯�� */
CTerrain::CTerrain()//:m_vertex(0),m_index(0),m_texCoord(0)
{
	/** ���õ��δ�С */
	setSize(MAP_WIDTH,CELL_WIDTH);
	
	/** Ϊ���θ̷߳����ڴ�,����ʼ�� */
	m_pHeightMap = new BYTE[m_nWidth * m_nWidth];
	for(int i=0; i<m_nWidth * m_nWidth; i++)
		m_pHeightMap[i] = 0;
}

/** �������� */
CTerrain::~CTerrain()
{
	/** ɾ���ڴ��ָ�� */
	if(m_pHeightMap)
	{
		delete[] m_pHeightMap;
	    m_pHeightMap = 0;
	}
	/** ɾ�����������ռ���ڴ� */	
	m_texture.FreeImage();
	glDeleteTextures(1,&m_texture.ID);
		
}

/** ��ʼ������ */
bool CTerrain::initTerrain()
{
	/** ����߶��ļ� */
	loadRawFile("data/terrain.raw");

	/** �������� */
	loadTexture("data/terrain.bmp");

	return true;
}

/** ���õ��δ�С */
void CTerrain::setSize(unsigned  int width, unsigned  int cell)
{
	m_nWidth = width;
	m_nCellWidth = cell; 
}

/** ��ø߶�ͼ�и߶�ֵ */
int CTerrain::getHeight(int x,int y)
{
	if(!m_pHeightMap)
		return 0;
	int xx = x % m_nWidth;
	int yy = y % m_nWidth;
    /** ���ص�ǰ�߶� */
	return m_pHeightMap[(xx + yy * m_nWidth)];
}
/** ��õ���߶� */
float CTerrain::getAveHeight(float x,float z)
{
	float CameraX, CameraZ;

	CameraX = x / m_nCellWidth;
	CameraZ = z / m_nCellWidth;
	/** ����߳�����(Col0, Row0)��(Col1, Row1) */
	int col0 = int(CameraX);
	int row0 = int(CameraZ);
	unsigned int col1 = col0 + 1;
	unsigned int row1 = row0 + 1;
	/** ȷ����Ԫ���겻�����߳����� */
	if (col1 > m_nWidth) col1 = 0;
	if (row1 > m_nWidth) row1 = 0;

	/** ��ȡ��Ԫ���ĸ��ǵĸ߶� */
	float h00 = (float)(m_pHeightMap[col0*m_nCellWidth + row0*m_nCellWidth*m_nWidth]);
	float h01 = (float)(m_pHeightMap[col1*m_nCellWidth + row0*m_nCellWidth*m_nWidth]);
	float h11 = (float)(m_pHeightMap[col1*m_nCellWidth + row1*m_nCellWidth*m_nWidth]);
	float h10 = (float)(m_pHeightMap[col0*m_nCellWidth + row1*m_nCellWidth*m_nWidth]);

	/** ��������������ڵ�Ԫ���λ�� */
	float tx = CameraX - int(CameraX);
	float ty = CameraZ - int(CameraZ);

	/** ����˫���Բ�ֵ�õ�����߶� */
	float txty = tx * ty;

	float final_height	= h00 * (1.0f - ty - tx + txty)
						+ h01 * (tx - txty)
						+ h11 * txty
						+ h10 * (ty - txty);
	return final_height;
}

/** ����߶�ͼ */
bool CTerrain::loadRawFile(const char* fileName)
{
	FILE *pFile = NULL;

	/** ���ļ� */
	pFile = fopen( fileName, "rb" );

	/** ������ */
	if ( pFile == NULL )	
	{
		/** ���������Ϣ��������false */
		MessageBox(NULL, "�򿪸߶�ͼ�ļ�ʧ�ܣ�", "����", MB_OK);
		exit(0);
	}

	/** ��ȡ�߶�ͼ�ļ� */
	fread( m_pHeightMap, 1, m_nWidth*m_nWidth, pFile );

	/** ��ȡ������� */
	int result = ferror( pFile );

	/** ��������� */
	if (result)
	{
		MessageBox(NULL, "�޷���ȡ�߶����ݣ�", "����", MB_OK);
		exit(0);
	}
    /** �ر��ļ����ɹ����� */
	fclose(pFile);
	return true;
}

/** ������������ */
void CTerrain::setTexCoord(float x,float z)
{
	glTexCoord2f(   (float)x / (float)m_nWidth,	
				  - (float)z / (float)m_nWidth	);
}

/** ����������� */
bool CTerrain::loadTexture(const char* fileName)
{
	if(!m_texture.LoadBitmap(fileName))                   /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);    /**< �������ʧ���򵯳��Ի��� */
		exit(0);
	}
	glGenTextures(1, &m_texture.ID);                            /**< ����һ������������� */
		
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);                 /**< ����������� */
	/** �����˲� */
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture.imageWidth,
					m_texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
					m_texture.image);
  	return true;
}

/** ��Ⱦ���� */
void CTerrain::render()
{
		
	
	int X = 0, Y = 0;						
	float x, y, z;							
	bool bSwitchSides = false;

	/** ���߶�ͼ�Ƿ���Ч */
	if(!m_pHeightMap) 
		return;					

	/** ������ */
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);
	glDisable(GL_LIGHTING);                          /** �رչ��� */

	/** ���������δ� */
	glBegin( GL_TRIANGLE_STRIP );			

	/** ����(X)��ʼѭ�� */
	for ( X = 0; X <= m_nWidth; X += m_nCellWidth )
	{
		/** �������Ƿ���Ҫ���෴˳����� */
		if(bSwitchSides)
		{	
			/** ���Ƶ��ε�һ�� */
			for ( Y = m_nWidth; Y >= 0; Y -= m_nCellWidth )
			{
				/** ����(X, Y, Z) */		
				x = X;							
				y = getHeight( X, Y );	
				z = Y;							

				/** ָ����������,�����Ͷ��� */
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);		

				/** ����(X + m_nCellWidth, Y, Z) */		
				x = X + m_nCellWidth; 
				y = getHeight( X + m_nCellWidth, Y ); 
				z = Y;

				/** ָ����������,�����Ͷ��� */
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);			
			}
		}
		else
		{	
			/** ���Ƶ��ε�һ�� */
			for ( Y = 0; Y <= m_nWidth; Y += m_nCellWidth )
			{
				/** ����(X + m_nCellWidth, Y, Z) */	
				x = X + m_nCellWidth; 
				y = getHeight( X + m_nCellWidth, Y ); 
				z = Y;

				/** ָ����������,�����Ͷ��� */
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);

				/** ���� (X, Y, Z) */		
				x = X;							
				y = getHeight( X, Y );	
				z = Y;							

				/** ָ����������,�����Ͷ��� */
				setTexCoord( (float)x, (float)z );
				glVertex3f(x, y, z);		
			}
		}
			
		/** �任���� */
		bSwitchSides = !bSwitchSides;
	}

	/** ���ƽ��� */
	glEnd();

}

