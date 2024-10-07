// Texture Object C++ Class
// ooglTexture.cpp

#include "stdafx.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "ooglTexture.h"


// Implementation

/////////////////////////////////////////////////////////////////////
// Object constructor. Primary task is to get a texture name, and 
// setup any internal variables and states needed.
/////////////////////////////////////////////////////////////////////
ooglTexture2D::ooglTexture2D()
	{
	// Initialize state variable
	_bValid = FALSE;		// Initially, no valid texutre loaded
	_pBitmapData = NULL;	// Initially, no pixmap data
	_nTextureWidth = 0;		// Initially no width
	_nTextureHeight = 0;	// Initially no height

	_nTextureID = 0;		// Initially no name allocated
	}

/////////////////////////////////////////////////////////////////////
// Object destructor. Primary task is to free the texture name and 
// deallocate any memory allocated previously.
/////////////////////////////////////////////////////////////////////
ooglTexture2D::~ooglTexture2D()
	{
	// Deallocate texture name
	if(_nTextureID != 0)
		glDeleteTextures(1,&_nTextureID);
	}


/////////////////////////////////////////////////////////////////////
// Loads a BMP file for use as a texture. The file must be in 24-bit
// format for this version of the texture object. Also the bitmap
// must have dimensions that are a power of two (2 X 2, 4X4, 8X8, 16X16
// 32X32, 64X64, etc.
/////////////////////////////////////////////////////////////////////
BOOL ooglTexture2D::LoadBMP(TCHAR* szFileName)
	{
	HANDLE hFileHandle;
	BITMAPINFO *pBitmapInfo = NULL;
	unsigned long lInfoSize = 0;
	unsigned long lBitSize = 0;

	char *swap;
	char temp;
	int i;
	// If this load fails, any previously loaded texture
	// is no longer valid.
	_bValid = FALSE;

	// Free pixmap data
	if(_pBitmapData)
		delete [] _pBitmapData;

	// Lose texture ID
	if(_nTextureID != 0)
		{
		glDeleteTextures(1,&_nTextureID);
		_nTextureID = 0;
		}

	// Open the Bitmap file
	hFileHandle = CreateFile(szFileName,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);

	// Check for open failure (most likely file does not exist).
	if(hFileHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	// File is Open. Read in bitmap header information
	BITMAPFILEHEADER	bitmapHeader;
	DWORD dwBytes;
	ReadFile(hFileHandle,&bitmapHeader,sizeof(BITMAPFILEHEADER),	
		&dwBytes,NULL);

	__try {
		if(dwBytes != sizeof(BITMAPFILEHEADER))
			return FALSE;

		// Check format of bitmap file
		if(bitmapHeader.bfType != 'MB')
			return FALSE;

		// Read in bitmap information structure
		lInfoSize = bitmapHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
		pBitmapInfo = (BITMAPINFO *) new BYTE[lInfoSize];

		ReadFile(hFileHandle,pBitmapInfo,lInfoSize,&dwBytes,NULL);

		if(dwBytes != lInfoSize)
			return FALSE;


		_nTextureWidth = pBitmapInfo->bmiHeader.biWidth;
		_nTextureHeight = pBitmapInfo->bmiHeader.biHeight;
		lBitSize = pBitmapInfo->bmiHeader.biSizeImage;

		if(lBitSize == 0)
			lBitSize = (_nTextureWidth *
               pBitmapInfo->bmiHeader.biBitCount + 7) / 8 *
  			  abs(_nTextureHeight);
	
		// Allocate space for the actual bitmap
		_pBitmapData = (void *)new BYTE[lBitSize];

		// Read in the bitmap bits
		ReadFile(hFileHandle,_pBitmapData,lBitSize,&dwBytes,NULL);

		if(lBitSize != dwBytes)
			{
			if(_pBitmapData)
				delete [] (BYTE *) _pBitmapData;
			_pBitmapData = NULL;
			
			return FALSE;
			}
		}
	__finally // Fail or success, close file and free working memory
		{
		CloseHandle(hFileHandle);

		if(pBitmapInfo != NULL)
			delete [] (BYTE *)pBitmapInfo;
		}

	// Once we get this far, we are home free	
	_bValid = TRUE;

	swap = (char*)_pBitmapData;
	for(i=0; i<(int)lBitSize; i+=3)
	{
		temp = *(swap);
		*(swap) = *(swap+2);
		*(swap+2) = temp;

		swap += 3;
	}
	// Get a new texture name for this texture,
	// bind this texture and make it current
	glGenTextures(1,&_nTextureID);
	glBindTexture(GL_TEXTURE_2D, _nTextureID);

	// Define the 2D texture image.
   
	// This is specific to the binary format of the data read in.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);	
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

//    glTexImage2D(GL_TEXTURE_2D, 0, 3, _nTextureWidth, _nTextureHeight, 0,
//						   GL_RGB, GL_UNSIGNED_BYTE, _pBitmapData);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _nTextureWidth, _nTextureHeight,
				GL_RGB, GL_UNSIGNED_BYTE, _pBitmapData);

//     glTexImage2D(GL_TEXTURE_2D, 0, 3, _nTextureWidth, _nTextureHeight, 0,
//						   GL_BGR_EXT, GL_UNSIGNED_BYTE, _pBitmapData);

	// Uncomment or add a member function to do this if you want mip mapping
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _nTextureWidth, _nTextureHeight,
	//			GL_BGR_EXT, GL_UNSIGNED_BYTE, _pBitmapData);

	// We don't need this loaded any more once it has been passed on to OpenGL,
	// UNLESS you are going to do the above (build mip maps) latter
	if(_pBitmapData)
		delete [] (BYTE *) _pBitmapData;

	return _bValid;
	}


/////////////////////////////////////////////////////////////////////
// Loads a BMP file for use as a texture. The file must be in 24-bit
// format for this version of the texture object. Also the bitmap
// must have dimensions that are a power of two (2 X 2, 4X4, 8X8, 16X16
// 32X32, 64X64, etc.
/////////////////////////////////////////////////////////////////////
BOOL ooglTexture2D::LoadBMPA(TCHAR* szFileName, int iblend)
	{
	HANDLE hFileHandle;
	BITMAPINFO *pBitmapInfo = NULL;
	unsigned long lInfoSize = 0;
	unsigned long lBitSize = 0;

	GLubyte tex[256][256][4];

	char *swap;
	char temp;
	int i;
	// If this load fails, any previously loaded texture
	// is no longer valid.
	_bValid = FALSE;

	// Free pixmap data
	if(_pBitmapData)
		delete [] _pBitmapData;

	// Lose texture ID
	if(_nTextureID != 0)
		{
		glDeleteTextures(1,&_nTextureID);
		_nTextureID = 0;
		}

	// Open the Bitmap file
	hFileHandle = CreateFile(szFileName,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);

	// Check for open failure (most likely file does not exist).
	if(hFileHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	// File is Open. Read in bitmap header information
	BITMAPFILEHEADER	bitmapHeader;
	DWORD dwBytes;
	ReadFile(hFileHandle,&bitmapHeader,sizeof(BITMAPFILEHEADER),	
		&dwBytes,NULL);

	__try {
		if(dwBytes != sizeof(BITMAPFILEHEADER))
			return FALSE;

		// Check format of bitmap file
		if(bitmapHeader.bfType != 'MB')
			return FALSE;

		// Read in bitmap information structure
		lInfoSize = bitmapHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
		pBitmapInfo = (BITMAPINFO *) new BYTE[lInfoSize];

		ReadFile(hFileHandle,pBitmapInfo,lInfoSize,&dwBytes,NULL);

		if(dwBytes != lInfoSize)
			return FALSE;


		_nTextureWidth = pBitmapInfo->bmiHeader.biWidth;
		_nTextureHeight = pBitmapInfo->bmiHeader.biHeight;
		lBitSize = pBitmapInfo->bmiHeader.biSizeImage;

		if(lBitSize == 0)
			lBitSize = (_nTextureWidth *
               pBitmapInfo->bmiHeader.biBitCount + 7) / 8 *
  			  abs(_nTextureHeight);
	
		// Allocate space for the actual bitmap
		_pBitmapData = (void *)new BYTE[lBitSize];

		// Read in the bitmap bits
		ReadFile(hFileHandle,_pBitmapData,lBitSize,&dwBytes,NULL);

		if(lBitSize != dwBytes)
			{
			if(_pBitmapData)
				delete [] (BYTE *) _pBitmapData;
			_pBitmapData = NULL;
			
			return FALSE;
			}
		}
	__finally // Fail or success, close file and free working memory
		{
		CloseHandle(hFileHandle);

		if(pBitmapInfo != NULL)
			delete [] (BYTE *)pBitmapInfo;
		}

	// Once we get this far, we are home free	
	_bValid = TRUE;

	int count = 0;
	int x = 0, y = 0;

	swap = (char*)_pBitmapData;
	for(i=0; i<(int)lBitSize; i+=3)
	{
		temp = *(swap);
		*(swap) = *(swap+2);
		*(swap+2) = temp;

		tex[count][y][0] = *(swap);
		tex[count][y][1] = *(swap+1);
		tex[count][y][2] = *(swap+2);

		count++;
		if(count == 256)
		{
			count = 0;
			y+=1;
		}

		swap += 3;
	}

	for(y=0; y<256; y++)
	{
		for(x=0; x<256; x++)
		{
//			tex[x][y][0] = _pBitmapData[(y+x*128)*3];
//			tex[x][y][1] = _pBitmapData[(y+x*128)*3+1];
//			tex[x][y][2] = _pBitmapData[(y+x*128)*3+2];

			if((tex[x][y][0]==tex[x][y][1]) && (tex[x][y][1]==tex[x][y][2])&&(tex[x][y][2]==0))
			{
				tex[x][y][3] = 0;
			}else
			{
				tex[x][y][3] = iblend;
			}
		}
	}
	// Get a new texture name for this texture,
	// bind this texture and make it current
	glGenTextures(1,&_nTextureID);
	glBindTexture(GL_TEXTURE_2D, _nTextureID);

	// Define the 2D texture image.
   
	// This is specific to the binary format of the data read in.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);	
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

//    glTexImage2D(GL_TEXTURE_2D, 0, 3, _nTextureWidth, _nTextureHeight, 0,
//						   GL_RGB, GL_UNSIGNED_BYTE, _pBitmapData);

//     glTexImage2D(GL_TEXTURE_2D, 0, 3, _nTextureWidth, _nTextureHeight, 0,
//						   GL_BGR_EXT, GL_UNSIGNED_BYTE, _pBitmapData);

	// Uncomment or add a member function to do this if you want mip mapping
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, _nTextureWidth, _nTextureHeight,
				GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)(tex));

	// We don't need this loaded any more once it has been passed on to OpenGL,
	// UNLESS you are going to do the above (build mip maps) latter
	if(_pBitmapData)
		delete [] (BYTE *) _pBitmapData;

	return _bValid;
	}

/////////////////////////////////////////////////////////////////////
// Loads a BMP file for use as a texture. The file must be in 24-bit
// format for this version of the texture object. Also the bitmap
// must have dimensions that are a power of two (2 X 2, 4X4, 8X8, 16X16
// 32X32, 64X64, etc.
/////////////////////////////////////////////////////////////////////
BOOL ooglTexture2D::LoadBMPA64(TCHAR* szFileName, int iblend)
	{
	HANDLE hFileHandle;
	BITMAPINFO *pBitmapInfo = NULL;
	unsigned long lInfoSize = 0;
	unsigned long lBitSize = 0;

	GLubyte tex[64][64][4];

	char *swap;
	char temp;
	int i;
	// If this load fails, any previously loaded texture
	// is no longer valid.
	_bValid = FALSE;

	// Free pixmap data
	if(_pBitmapData)
		delete [] _pBitmapData;

	// Lose texture ID
	if(_nTextureID != 0)
		{
		glDeleteTextures(1,&_nTextureID);
		_nTextureID = 0;
		}

	// Open the Bitmap file
	hFileHandle = CreateFile(szFileName,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);

	// Check for open failure (most likely file does not exist).
	if(hFileHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	// File is Open. Read in bitmap header information
	BITMAPFILEHEADER	bitmapHeader;
	DWORD dwBytes;
	ReadFile(hFileHandle,&bitmapHeader,sizeof(BITMAPFILEHEADER),	
		&dwBytes,NULL);

	__try {
		if(dwBytes != sizeof(BITMAPFILEHEADER))
			return FALSE;

		// Check format of bitmap file
		if(bitmapHeader.bfType != 'MB')
			return FALSE;

		// Read in bitmap information structure
		lInfoSize = bitmapHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
		pBitmapInfo = (BITMAPINFO *) new BYTE[lInfoSize];

		ReadFile(hFileHandle,pBitmapInfo,lInfoSize,&dwBytes,NULL);

		if(dwBytes != lInfoSize)
			return FALSE;


		_nTextureWidth = pBitmapInfo->bmiHeader.biWidth;
		_nTextureHeight = pBitmapInfo->bmiHeader.biHeight;
		lBitSize = pBitmapInfo->bmiHeader.biSizeImage;

		if(lBitSize == 0)
			lBitSize = (_nTextureWidth *
               pBitmapInfo->bmiHeader.biBitCount + 7) / 8 *
  			  abs(_nTextureHeight);
	
		// Allocate space for the actual bitmap
		_pBitmapData = (void *)new BYTE[lBitSize];

		// Read in the bitmap bits
		ReadFile(hFileHandle,_pBitmapData,lBitSize,&dwBytes,NULL);

		if(lBitSize != dwBytes)
			{
			if(_pBitmapData)
				delete [] (BYTE *) _pBitmapData;
			_pBitmapData = NULL;
			
			return FALSE;
			}
		}
	__finally // Fail or success, close file and free working memory
		{
		CloseHandle(hFileHandle);

		if(pBitmapInfo != NULL)
			delete [] (BYTE *)pBitmapInfo;
		}

	// Once we get this far, we are home free	
	_bValid = TRUE;

	int count = 0;
	int x = 0, y = 0;

	swap = (char*)_pBitmapData;
	for(i=0; i<(int)lBitSize; i+=3)
	{
		temp = *(swap);
		*(swap) = *(swap+2);
		*(swap+2) = temp;

		tex[count][y][0] = *(swap);
		tex[count][y][1] = *(swap+1);
		tex[count][y][2] = *(swap+2);

		count++;
		if(count == 64)
		{
			count = 0;
			y+=1;
		}

		swap += 3;
	}

	for(y=0; y<64; y++)
	{
		for(x=0; x<64; x++)
		{
//			tex[x][y][0] = _pBitmapData[(y+x*128)*3];
//			tex[x][y][1] = _pBitmapData[(y+x*128)*3+1];
//			tex[x][y][2] = _pBitmapData[(y+x*128)*3+2];

			if((tex[x][y][0]==tex[x][y][1]) && (tex[x][y][1]==tex[x][y][2])&&(tex[x][y][2]==0))
			{
				tex[x][y][3] = 0;
			}else
			{
				tex[x][y][3] = iblend;
			}
		}
	}
	// Get a new texture name for this texture,
	// bind this texture and make it current
	glGenTextures(1,&_nTextureID);
	glBindTexture(GL_TEXTURE_2D, _nTextureID);

	// Define the 2D texture image.
   
	// This is specific to the binary format of the data read in.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);	
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

//    glTexImage2D(GL_TEXTURE_2D, 0, 3, _nTextureWidth, _nTextureHeight, 0,
//						   GL_RGB, GL_UNSIGNED_BYTE, _pBitmapData);

//     glTexImage2D(GL_TEXTURE_2D, 0, 3, _nTextureWidth, _nTextureHeight, 0,
//						   GL_BGR_EXT, GL_UNSIGNED_BYTE, _pBitmapData);

	// Uncomment or add a member function to do this if you want mip mapping
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, _nTextureWidth, _nTextureHeight,
				GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)(tex));

	// We don't need this loaded any more once it has been passed on to OpenGL,
	// UNLESS you are going to do the above (build mip maps) latter
	if(_pBitmapData)
		delete [] (BYTE *) _pBitmapData;

	return _bValid;
	}

/*	
BOOL ooglTexture2D::GetBMP(TCHAR* szFileName, GLubyte* uData, int *w, int *h)
{
	HANDLE hFileHandle;
	BITMAPINFO *pBitmapInfo = NULL;
	unsigned long lInfoSize = 0;
	unsigned long lBitSize = 0;

	char *swap;
	char temp;
	int i;
	// If this load fails, any previously loaded texture
	// is no longer valid.
	_bValid = FALSE;

	// Free pixmap data
	if(_pBitmapData)
		delete [] _pBitmapData;

	// Open the Bitmap file
	hFileHandle = CreateFile(szFileName,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);

	// Check for open failure (most likely file does not exist).
	if(hFileHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	// File is Open. Read in bitmap header information
	BITMAPFILEHEADER	bitmapHeader;
	DWORD dwBytes;
	ReadFile(hFileHandle,&bitmapHeader,sizeof(BITMAPFILEHEADER),	
		&dwBytes,NULL);

	__try {
		if(dwBytes != sizeof(BITMAPFILEHEADER))
			return FALSE;

		// Check format of bitmap file
		if(bitmapHeader.bfType != 'MB')
			return FALSE;

		// Read in bitmap information structure
		lInfoSize = bitmapHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
		pBitmapInfo = (BITMAPINFO *) new BYTE[lInfoSize];

		ReadFile(hFileHandle,pBitmapInfo,lInfoSize,&dwBytes,NULL);

		if(dwBytes != lInfoSize)
			return FALSE;


		*w = pBitmapInfo->bmiHeader.biWidth;
		*h = pBitmapInfo->bmiHeader.biHeight;
		lBitSize = pBitmapInfo->bmiHeader.biSizeImage;

		if(lBitSize == 0)
			lBitSize = (_nTextureWidth *
               pBitmapInfo->bmiHeader.biBitCount + 7) / 8 *
  			  abs(_nTextureHeight);
	
		// Allocate space for the actual bitmap
		_pBitmapData = (void *)new BYTE[lBitSize];

		// Read in the bitmap bits
		ReadFile(hFileHandle,_pBitmapData,lBitSize,&dwBytes,NULL);

		if(lBitSize != dwBytes)
			{
			if(_pBitmapData)
				delete [] (BYTE *) _pBitmapData;
			_pBitmapData = NULL;
			
			return FALSE;
			}
		}
	__finally // Fail or success, close file and free working memory
		{
		CloseHandle(hFileHandle);

		if(pBitmapInfo != NULL)
			delete [] (BYTE *)pBitmapInfo;
		}

	// Once we get this far, we are home free	
	_bValid = TRUE;

	swap = (char*)_pBitmapData;
	GLubyte *ptr = uData;
	for(i=0; i<(int)lBitSize; i+=3)
	{
		temp = *(swap);
		*(swap) = *(swap+2);
		*(swap+2) = temp;

		*ptr = *(swap);
		*(ptr+1) = *(swap+1);
		*(ptr+2)= *(swap+2);
	
		if((*(ptr) == *(ptr+1)) && (*(ptr+1) == *(ptr+2)) && (*(ptr+2) == 0))
		{
			*(ptr+3) = 0;
		}else
		{
			*(ptr+3) = 255;
		}

		swap += 3;
		ptr +=4;
	}

	if(_pBitmapData)
		delete [] (BYTE *) _pBitmapData;

	return _bValid;
}
*/