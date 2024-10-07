// MyVec3D.cpp: implementation of the CMyVec3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyFlare.h"
#include "MyVec3D.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyVec3D::CMyVec3D()
{

}

CMyVec3D::~CMyVec3D()
{

}

void CMyVec3D::vnorm(float vec[3])
{
  float len;

  len = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
  vec[0] = vec[0] / len;
  vec[1] = vec[1] / len;
  vec[2] = vec[2] / len;
}

float CMyVec3D::vdot(float a[3], float b[3])
{
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void CMyVec3D::vdiff(float dst[3], float a[3], float b[3])
{
  dst[0] = a[0] - b[0];
  dst[1] = a[1] - b[1];
  dst[2] = a[2] - b[2];
}

void CMyVec3D::vadd(float dst[3], float a[3], float b[3])
{
  dst[0] = a[0] + b[0];
  dst[1] = a[1] + b[1];
  dst[2] = a[2] + b[2];
}

void CMyVec3D::vcopy(float dst[3], float src[3])
{
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
}

void CMyVec3D::vscale(float dst[3], float src[3], float scale)
{
  dst[0] = src[0] * scale;
  dst[1] = src[1] * scale;
  dst[2] = src[2] * scale;
}

void CMyVec3D::vcross(float cross[3], const float v1[3], const float v2[3])
{
  float tmp[3];

  tmp[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
  tmp[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
  tmp[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
  vcopy(cross, tmp);
}

