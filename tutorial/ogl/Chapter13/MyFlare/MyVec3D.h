// MyVec3D.h: interface for the CMyVec3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYVEC3D_H__63CED481_227A_4C4A_A3EB_8ACFF46D7017__INCLUDED_)
#define AFX_MYVEC3D_H__63CED481_227A_4C4A_A3EB_8ACFF46D7017__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyVec3D  
{
public:
	CMyVec3D();
	virtual ~CMyVec3D();

	void vnorm(float vec[3]);
	float vdot(float a[3], float b[3]);
	void vdiff(float dst[3], float a[3], float b[3]);
	void vadd(float dst[3], float a[3], float b[3]);
	void vcopy(float dst[3], float src[3]);
	void vscale(float dst[3], float src[3], float scale);
	void vcross(float cross[3], const float v1[3], const float v2[3]);
};

#endif // !defined(AFX_MYVEC3D_H__63CED481_227A_4C4A_A3EB_8ACFF46D7017__INCLUDED_)
