// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCollision1.h"
#include "Image.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage::CImage()
{

}

CImage::~CImage()
{

}

unsigned int CImage::getint(FILE *fp)
{
  int c, c1, c2, c3;
  // ���4���ֽ�
  c = getc(fp);  
  c1 = getc(fp);  
  c2 = getc(fp);  
  c3 = getc(fp);
  return ((unsigned int) c) +   
    (((unsigned int) c1) << 8) + 
    (((unsigned int) c2) << 16) +
    (((unsigned int) c3) << 24);
}

unsigned int CImage::getshort(FILE *fp)
{
  int c, c1;
  // ���2���ֽ�
  c = getc(fp);  
  c1 = getc(fp);
  return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

int CImage::ImageLoad(char *filename, Image *image) 
{
    FILE *file;
    unsigned long size;                 // ͼ�εĴ�С(�ֽ���)
    unsigned long i;                    // ��׼������
    unsigned short int planes;          // ͼ�ε�ƽ����(����Ϊ1)
    unsigned short int bpp;             // ÿ�����ص�λ��(����Ϊ24)
    char temp;                          // ��ʱ����ɫ����
    // ȷ���ļ�����
    if ((file = fopen(filename, "rb"))==NULL) {
      printf("File Not Found : %s\n",filename);
      return 0;
    }
    fseek(file, 18, SEEK_CUR);
    // �����
    image->sizeX = getint (file);
    printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // ���߶�
    image->sizeY = getint (file);
    printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // ����ͼ�εĴ�С(�ٶ�ÿ������Ϊ24λ��3���ֽ�)
    size = image->sizeX * image->sizeY * 3;
    planes = getshort(file);
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }
    bpp = getshort(file);
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
    fseek(file, 24, SEEK_CUR);
    // ��������
    image->data = (char *) malloc(size);
    if (image->data == NULL) 
	{
		MessageBox(NULL,"Error allocating memory for color-corrected image data", "ERROR",MB_OK);
		return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) 
	{
		MessageBox(NULL,"Error reading image data", "ERROR",MB_OK);
		return 0;
    }

    for (i=0;i<size;i+=3) 
	{ 
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
    }

    return 1;
}
