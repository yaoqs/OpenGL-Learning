// LoadBMP.cpp: implementation of the CLoadBMP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyFire2.h"
#include "LoadBMP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoadBMP::CLoadBMP()
{

}

CLoadBMP::~CLoadBMP()
{

}

///////////////////////////////////////////////////////////////////////////////
// 该函数的功能是装入24位的BMP文件，大小必须是2的幂
BOOL CLoadBMP::LoadBMP(TCHAR* szFileName)
	{
	HANDLE hFileHandle;
	BITMAPINFO *pBitmapInfo = NULL;
	unsigned long lInfoSize = 0;
	unsigned long lBitSize = 0;
	int nTextureWidth;
	int nTextureHeight;
	BYTE *pBitmapData;
	// 打开位图文件
	hFileHandle = CreateFile(szFileName,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	if(hFileHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	// 读入位图文件头数据
	BITMAPFILEHEADER	bitmapHeader;
	DWORD dwBytes;
	ReadFile(hFileHandle,&bitmapHeader,sizeof(BITMAPFILEHEADER),
		&dwBytes,NULL);
		if(dwBytes != sizeof(BITMAPFILEHEADER))
			return FALSE;
		// 检查文件格式
		if(bitmapHeader.bfType != 'MB')
			return FALSE;
		// 读入位图结构信息
		lInfoSize = bitmapHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
		pBitmapInfo = (BITMAPINFO *) new BYTE[lInfoSize];
		ReadFile(hFileHandle,pBitmapInfo,lInfoSize,&dwBytes,NULL);
		if(dwBytes != lInfoSize)
			return FALSE;
		nTextureWidth = pBitmapInfo->bmiHeader.biWidth;
		nTextureHeight = pBitmapInfo->bmiHeader.biHeight;
		lBitSize = pBitmapInfo->bmiHeader.biSizeImage;

		if(lBitSize == 0)
			lBitSize = (nTextureWidth *
               pBitmapInfo->bmiHeader.biBitCount + 7) / 8 *
  			  abs(nTextureHeight);
		// 分配位图数据的存储空间
		pBitmapData = new BYTE[lBitSize];
		// 读入位图数据
		ReadFile(hFileHandle,pBitmapData,lBitSize,&dwBytes,NULL);
		if(lBitSize != dwBytes)
			{
			if(pBitmapData)
				delete [] (BYTE *) pBitmapData;
			pBitmapData = NULL;

			return FALSE;
			}

		CloseHandle(hFileHandle);

		if(pBitmapInfo != NULL)
			delete [] (BYTE *)pBitmapInfo;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, nTextureWidth, nTextureHeight, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pBitmapData);

	if(pBitmapData)
		delete [] (BYTE *) pBitmapData;

	return TRUE;
	}

CLoadBMP::GLLoadTextures(GLuint* ptList)
{
	// 生成7个纹理对象
	glGenTextures(8, ptList);

	glBindTexture(GL_TEXTURE_2D, ptList[KEY]);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		LoadBMP("key.bmp");

	glBindTexture(GL_TEXTURE_2D, ptList[STAR]);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		LoadBMP("star.bmp");

	glBindTexture(GL_TEXTURE_2D, ptList[BUBBLE]);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		LoadBMP("bubble.bmp");

	glBindTexture(GL_TEXTURE_2D, ptList[CLOUD]);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		LoadBMP("CLOUD.bmp");

	glBindTexture(GL_TEXTURE_2D, ptList[CIRCLE]);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		LoadBMP("circle.bmp");

	glBindTexture(GL_TEXTURE_2D, ptList[SPARK]);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		LoadBMP("spark.bmp");

	glBindTexture(GL_TEXTURE_2D, ptList[LOWKEY]);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		LoadBMP("LOWKEY.bmp");

}
