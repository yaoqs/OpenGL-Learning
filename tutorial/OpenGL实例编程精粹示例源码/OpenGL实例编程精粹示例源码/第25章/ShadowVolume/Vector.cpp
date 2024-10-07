//========================================================
/**
*  @file      Vector.cpp
*
*  ��Ŀ������ ��Ӱ��
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-20
*
*/     
//========================================================

#include "Vector.h"                       /**< ����ͷ�ļ� */

/** ���������ĳ��� */
inline float Vector3::length()
{
	return (float)( x * x + y * y + z * z );
}

/** ��λ��һ���� */
Vector3 Vector3::normalize()
{
	float len = length();                  /**< ������������ */
	if( len == 0 )
		len = 1;
	x = x / len;
	y = y / len;
	z = z / len;

	return *this;
}

/** ��� */
float Vector3::dotProduct(const Vector3& v)
{
	return ( x * v.x + y * v.y + z * v.z );
}

/** ��� */
 Vector3 Vector3::crossProduct(const Vector3& v)
{
	Vector3 vec;

	vec.x = y * v.z - z * v.y;
	vec.y = z * v.x - x * v.z;
	vec.z = x * v.y - y * v.x;
	
	return vec;
}

/** ������ + */
 Vector3 Vector3::operator +(const Vector3& v)
{
	Vector3 vec;
	
	vec.x = x + v.x;
	vec.y = y + v.y;
	vec.z = z + v.z;

	return vec;
}

Vector3 Vector3::operator +=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	
	return *this;
}

Vector3 Vector3::operator -=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	
	return *this;
}

/** ������ - */
 Vector3 Vector3::operator -(const Vector3& v)
{
	Vector3 vec;
	
	vec.x = x - v.x;
	vec.y = y - v.y;
	vec.z = z - v.z;

	return vec;
}

/** ������ * */
 Vector3 Vector3::operator *(const Vector3& v)
{
	Vector3 vec(0.0f, 0.0f, 0.0f);
	
	vec.x = x * v.x;
	vec.y = y * v.y;
	vec.z = z * v.z;

	return vec;
}

/** ������ / */
 Vector3 Vector3::operator /(const Vector3& v)
{
	Vector3 vec(0.0f, 0.0f, 0.0f);
	
	vec.x = x / v.x;
	vec.y = y / v.y;
	vec.z = z / v.z;

	return vec;
}

/** ������ * */
 Vector3 Vector3::operator *(float scale)
{
	x = x * scale;
	y = y * scale;
	z = z * scale;
	
	return *this;
}

/** ������ / */
 Vector3 Vector3::operator /(float scale)
{
	if(scale != 0.0)
	{	
	   x = x / scale;
	   y = y / scale;
	   z = z / scale;
	}
	return *this;
}

/** ���� */
 Vector3 Vector3::operator -()
{
	Vector3 vec( - x,- y, - z);
	return vec;
}


/************ ��ά������ʵ�� *****/

CVector4::CVector4()
{
  
   x = y = z = 0.0;
}


CVector4::CVector4(float X, float Y, float Z)
{
   
   x = X;
   y = Y;
   z = Z;
}


CVector4::CVector4(float X, float Y, float Z, float W)
{
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


CVector4 CVector4::operator -(CVector4 v)
{

   return CVector4(x - v.x, y - v.y, z - v.z);
}


CVector4 CVector4::operator +(CVector4 v)
{

   return CVector4(x + v.x, y + v.y, z + v.z);
}


CVector4 CVector4::operator *(CVector4 v)
{

   return CVector4(x * v.x, y * v.y, z * v.z);
}


CVector4 CVector4::operator /(CVector4 v)
{
 
   return CVector4(x / v.x, y / v.y, z / v.z);
}


CVector4 CVector4::operator +(float f)
{
 
   return CVector4(x + f, y + f, z + f);
}


CVector4 CVector4::operator -(float f)
{
  
   return CVector4(x - f, y - f, z - f);
}


CVector4 CVector4::operator *(float f)
{
 
   return CVector4(x * f, y * f, z * f);
}


CVector4 CVector4::operator /(float f)
{
   
   f = 1/f;

   return CVector4(x * f, y * f, z * f);
}
/** ��������ĳ��Դ�������� */
void CVector4::ExtendVertexPos(CVector4 currentVertex, CVector4 lightPos, float Extend)
{
    CVector4 lightDir;  /**< ��Դλ�õ���������� */
    CVector4 newPos;    /**< �������¶��� */

   
	lightDir = currentVertex - lightPos;

    /** ���������Ķ��� */
    newPos = lightPos + lightDir * Extend;

	/** ����ö��� */
    x = newPos.x;
    y = newPos.y;
    z = newPos.z;
    w = newPos.w;
}











