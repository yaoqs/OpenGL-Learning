// OBJFileRead.h: interface for the COBJFileRead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJFILEREAD_H__8BFF131F_D05E_4137_B48A_47FEA8EC20D4__INCLUDED_)
#define AFX_OBJFILEREAD_H__8BFF131F_D05E_4137_B48A_47FEA8EC20D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "modelcontext.h"

extern   ModelContext *model;

class COBJFileRead  
{
public:
	COBJFileRead();
	virtual ~COBJFileRead();
	
	void readLineData(char *FileName);
	void readObjData(char *FileName);
	FILE *fileOpen(const char *filename, const char *mode);
	MaterialColor *readMaterials(char *FileName);


};

#endif // !defined(AFX_OBJFILEREAD_H__8BFF131F_D05E_4137_B48A_47FEA8EC20D4__INCLUDED_)
