// LoadBMP.h: interface for the CLoadBMP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADBMP_H__6CAAF6DA_E1D7_4760_8E5B_B649455D2F1D__INCLUDED_)
#define AFX_LOADBMP_H__6CAAF6DA_E1D7_4760_8E5B_B649455D2F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum Texture_Objects { KEY = 0, STAR, BUBBLE, SPARK, CIRCLE, CLOUD, LOWKEY };

class CLoadBMP  
{
public:
	CLoadBMP();
	virtual ~CLoadBMP();

	BOOL LoadBMP(TCHAR* szFileName);
	GLLoadTextures(GLuint* ptList);
};

#endif // !defined(AFX_LOADBMP_H__6CAAF6DA_E1D7_4760_8E5B_B649455D2F1D__INCLUDED_)
