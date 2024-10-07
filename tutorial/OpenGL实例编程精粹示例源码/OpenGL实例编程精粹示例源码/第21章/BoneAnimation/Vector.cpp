//========================================================
/**
*  @file      Vector.cpp
*
*  ��Ŀ������ ������
*  �ļ�����:  ��������    
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-10-13	
*  �޸����ڣ� 2006-12-29
*
*/     
//========================================================

#include "Vector.h"

CVector4::CVector4()
{
   ///��ʼ��
   x = y = z = 0.0; w = 1;
}


CVector4::CVector4(float X, float Y, float Z)
{
   ///��ʼ��
   x = X;
   y = Y;
   z = Z;
}


CVector4::CVector4(float X, float Y, float Z, float W)
{
   ///��ʼ��.
   x = X;
   y = Y;
   z = Z;
   w = W;
}


CVector4::CVector4(const CVector4 &v)
{
  
   x = v.x;
   y = v.y;
   z = v.z;
   w = v.w;
}


void CVector4::operator =(CVector4 v)
{
   
   x = v.x;
   y = v.y;
   z = v.z;
   w = v.w;
}

/// -
CVector4 CVector4::operator -(CVector4 v)
{
      return CVector4(x - v.x, y - v.y, z - v.z);
}

/// +
CVector4 CVector4::operator +(CVector4 v)
{
     return CVector4(x + v.x, y + v.y, z + v.z);
}

/// *
CVector4 CVector4::operator *(CVector4 v)
{
      return CVector4(x * v.x, y * v.y, z * v.z);
}

/// /
CVector4 CVector4::operator /(CVector4 v)
{
      return CVector4(x / v.x, y / v.y, z / v.z);
}

/// +
CVector4 CVector4::operator +(float f)
{
     return CVector4(x + f, y + f, z + f);
}

/// -
CVector4 CVector4::operator -(float f)
{
     return CVector4(x - f, y - f, z - f);
}

/// *
CVector4 CVector4::operator *(float f)
{
      return CVector4(x * f, y * f, z * f);
}

/// /
CVector4 CVector4::operator /(float f)
{
    f = 1/f;

   return CVector4(x * f, y * f, z * f);
}

/// +=
void CVector4::operator +=(CVector4 v)
{
   x += v.x;
   y += v.y;
   z += v.z;
}

/// -=
void CVector4::operator -=(CVector4 v)
{
 
   x -= v.x;
   y -= v.y;
   z -= v.z;
}

/// *=
void CVector4::operator *=(CVector4 v)
{
   x *= v.x;
   y *= v.y;
   z *= v.z;
}

/// /=
void CVector4::operator /=(CVector4 v)
{
   x /= v.x;
   y /= v.y;
   z /= v.z;
}

/// +=
void CVector4::operator +=(float f)
{
   x += f;
   y += f;
   z += f;
}

/// -=
void CVector4::operator -=(float f)
{
   
   x -= f;
   y -= f;
   z -= f;
}

/// *=
void CVector4::operator *=(float f)
{
   
   x *= f;
   y *= f;
   z *= f;
}

/// /=
void CVector4::operator /=(float f)
{
   
   f = 1/f;

   x *= f;
   y *= f;
   z *= f;
}

/// ==
bool CVector4::operator ==(CVector4 v)
{
    return ((x == v.x) && (y== v.y) && (z == v.z));
}

/// ��=
bool CVector4::operator !=(CVector4 v)
{
     return !((x == v.x) && (y== v.y) && (z == v.z));
}

/// ���
void CVector4::CrossProduct(CVector4 v1, CVector4 v2)
{
   
   x = ((v1.y * v2.z) - (v1.z * v2.y));
   y = ((v1.z * v2.x) - (v1.x * v2.z));
   z = ((v1.x * v2.y) - (v1.y * v2.x));
}


void CVector4::CrossProduct3(CVector4 v1, CVector4 v2, CVector4 v3)
{
   ///���v1,v2,v3�Ĳ��
   x = v1.y * v2.z * v3.w +
       v1.z * v2.w * v3.y +
       v1.w * v2.y * v3.z - 
       v1.y * v2.w * v3.z -
       v1.z * v2.y * v3.w -
       v1.w * v2.z * v3.y;

   y = v1.x * v2.w * v3.z +
       v1.z * v2.x * v3.w +
       v1.w * v2.z * v3.x -
       v1.x * v2.z * v3.w -
       v1.z * v2.w * v3.x -
       v1.w * v2.x * v3.z;

   z = v1.x * v2.y * v3.w +
       v1.y * v2.w * v3.x +
       v1.w * v2.x * v3.y -
       v1.x * v2.w * v3.y -
       v1.y * v2.x * v3.w -
       v1.w * v2.y * v3.x;

   w = v1.x * v2.z * v3.y +
       v1.y * v2.x * v3.z +
       v1.z * v2.y * v3.x -
       v1.x * v2.y * v3.z -
       v1.y * v2.z * v3.x -
       v1.z * v2.x * v3.y;
}

/// ���
float CVector4::DotProduct3(CVector4 v1)
{
    return x * v1.x + y * v1.y + z * v1.z;
}


float CVector4::DotProduct4(CVector4 v1)
{
   return x * v1.x + y * v1.y + z * v1.z + w * v1.w;
}

/// ���س���
float CVector4::GetLength()
{
   return (float)sqrt((x * x + y * y + z * z));
}

/// ��һ��
void CVector4::Normal()
{
  
   float lenght = GetLength();

   if(lenght == 0.0f)
      lenght = 1.0f;

   x = x/lenght;
   y = y/lenght;
   z = z/lenght;
   w = w/lenght;
}

