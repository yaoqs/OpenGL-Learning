// LoadLUM.h: interface for the CLoadLUM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADLUM_H__CA9584DA_22C4_4573_BB9D_8E20DF439DB2__INCLUDED_)
#define AFX_LOADLUM_H__CA9584DA_22C4_4573_BB9D_8E20DF439DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _ImageRec 
{
  unsigned short imagic;
  unsigned short type;
  unsigned short dim;
  unsigned short xsize, ysize, zsize;
  unsigned int min, max;
  unsigned int wasteBytes;
  char name[80];
  unsigned long colorMap;
  FILE *file;
  unsigned char *tmp;
  unsigned long rleEnd;
  unsigned int *rowStart;
  int *rowSize;
} ImageRec;


class CLoadLUM  
{
public:
	CLoadLUM();
	virtual ~CLoadLUM();

	void ConvertShort(unsigned short *array, unsigned int length);
	void ConvertUint(unsigned *array, unsigned int length);
	ImageRec *ImageOpen(char *fileName);
	void ImageClose(ImageRec * image);
	void ImageGetRow(ImageRec * image, unsigned char *buf, int y, int z);
	unsigned char *load_luminance(char *name, int *width, int *height, int *components);

};

#endif // !defined(AFX_LOADLUM_H__CA9584DA_22C4_4573_BB9D_8E20DF439DB2__INCLUDED_)
