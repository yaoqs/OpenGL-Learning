// BMPLoad.h: interface for the CBMPLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPLOAD_H__A7A2B09D_8283_4DA1_8A5C_C023D4DDB6D0__INCLUDED_)
#define AFX_BMPLOAD_H__A7A2B09D_8283_4DA1_8A5C_C023D4DDB6D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define INDEX_TEXTURE_NAME(x, z) ((x) + ((z)*8))
#ifndef PI
#define PI 3.1415926535
#endif PI

#ifndef f4 
#define f4(a, b, c, d) ((a) + (b) + (c) + (d)) / 4
#endif
#define IX(x, z) (((x)&255) + (((z)&255) << 8)) // 将2D坐标转换为1D坐标
#define M_SIZE 256 

typedef unsigned char BYTE;
typedef short int SHORT;
typedef long int LONG;
typedef unsigned short int WORD;
typedef unsigned long int DWORD;

typedef struct TEXTURE{
	int w, h;
	unsigned char *data;
} TEXTURE;

typedef struct _Win3xBitmapHeader
{
	WORD	ImageFileType;
	DWORD FileSize;
	WORD	Reserved1;
	WORD	Reserved2;
	DWORD	ImageDataOffset;

} WIN3XHEAD;

typedef struct _Win3xBitmapInfoHeader
{
	DWORD	HeaderSize;
	LONG ImageWidth;
	LONG ImageHeight;
	WORD	NumberOfImagePlanes;
	WORD	BitsPerPixel;
	DWORD	CompressionMethod;
	DWORD SizeOfBitmap;
	LONG HorzResolution;
	LONG VertResolution;
	DWORD NumColorsUsed;
	DWORD NumSignificantColors;

} WIN3XINFOHEAD;

typedef struct _Win3xPixelData
{
	BYTE r;
	BYTE g;
	BYTE b;
} PAL;

class CBMPLoad  
{
public:
	CBMPLoad();
	virtual ~CBMPLoad();

	TEXTURE *load_bitmap(char *); 
	void destroy_bmp(TEXTURE *);
	void texture_terrain(TEXTURE *t, int *hf);
	
	int IX_MAP(int x, int z);
	float texture_factor(int h1, int h2);
	int limit255(int a);
	TEXTURE *new_bitmap(int x, int y);
	void SET_COLOR(TEXTURE *tex, int x, int y, BYTE r, BYTE g, BYTE b);
	void GET_COLOR(TEXTURE *tex, int x, int y, BYTE *r, BYTE *g, BYTE *b);


};


#endif // !defined(AFX_BMPLOAD_H__A7A2B09D_8283_4DA1_8A5C_C023D4DDB6D0__INCLUDED_)
