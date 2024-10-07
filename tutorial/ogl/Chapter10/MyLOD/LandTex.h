// LandTex.h: interface for the CLandTex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANDTEX_H__391B9854_1AD2_4D13_89C6_683378F7F4F8__INCLUDED_)
#define AFX_LANDTEX_H__391B9854_1AD2_4D13_89C6_683378F7F4F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "BMPLoad.h"

class CLandTex  
{
public:
	CLandTex();
	virtual ~CLandTex();

	void NEW_BITMAP(unsigned int *, int *);
	TEXTURE *tex[4][4];
	unsigned int texture_name[4][4];

	CBMPLoad m_Bmpload;
};

#endif // !defined(AFX_LANDTEX_H__391B9854_1AD2_4D13_89C6_683378F7F4F8__INCLUDED_)
