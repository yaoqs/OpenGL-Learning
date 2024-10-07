//========================================================
/**
*  @file      Vector.h
*
*  ��Ŀ������ ��Ӱ��
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-19
*
*/     
//========================================================

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "stdafx.h"

/** ������ */
class Vector3
{
public:
	/** ���캯�� */
	Vector3()  { x = 0.0; y = 0.0; z = 0.0; }
	Vector3( float xx, float yy, float zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}
	Vector3(const Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}
    
	/** ��Ա���� */
	inline float length();                       /**< ������������ */
	Vector3 normalize();                         /**< ��λ������ */
	float dotProduct(const Vector3 &v );          /**< ������ */
	Vector3 crossProduct(const Vector3 &v);     /**< ������ */

	/** ���ز����� */
	Vector3 operator + (const Vector3& v);
	Vector3 operator += (const Vector3& v);
	Vector3 operator - (const Vector3& v);
	Vector3 operator -= (const Vector3& v);
	Vector3 operator * (const Vector3& v);
	Vector3 operator / (const Vector3& v);
	Vector3 operator * (float scale);
	Vector3 operator / (float scale);
	Vector3 operator - ();
	
public:
	  float x,y,z;

};

/** ��ά������ */
class CVector4
{
   public:
	  ///���캯��
      CVector4();                                        
      CVector4(float X, float Y, float Z);               
      CVector4(float X, float Y, float Z, float W);      
      CVector4(const CVector4 &v);   
	   
	  /** ���������� */
	  void operator=(CVector4 v);
	  CVector4 operator-(CVector4 v);                   
      CVector4 operator+(CVector4 v);                    
      CVector4 operator*(CVector4 v);                   
      CVector4 operator/(CVector4 v);                  
      CVector4 operator+(float f);                     
      CVector4 operator-(float f);                     
      CVector4 operator*(float f);                      
      CVector4 operator/(float f);                      

	  /** ����ǰ����ĳ���������� */
	  void ExtendVertexPos(CVector4 currentVertex,       
                           CVector4 lightPos,            
                           float Extend);

public:
	float x,y,z,w;
};

#endif //__VECTOR_H__