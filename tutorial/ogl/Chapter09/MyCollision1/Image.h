// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__A30C8294_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_)
#define AFX_IMAGE_H__A30C8294_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

class CImage  
{
public:
	CImage();
	virtual ~CImage();
	unsigned int getint(FILE *fp);
	unsigned int getshort(FILE *fp);
	int ImageLoad(char *filename, Image *image);
};

#endif // !defined(AFX_IMAGE_H__A30C8294_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_)
