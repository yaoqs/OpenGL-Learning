//========================================================
/**
*  @file      Vector.h
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

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#define M_PI 3.141592654

/** ��ά������ */
class CVector4
{
	public:
	  ///���캯��
      CVector4();                                        
      CVector4(float X, float Y, float Z);              
      CVector4(float X, float Y, float Z, float W);      
      CVector4(const CVector4 &v);                       

      ///��������� 
	  void operator=(CVector4 v);                        
      CVector4 operator-(CVector4 v);                   
      CVector4 operator+(CVector4 v);                    
      CVector4 operator*(CVector4 v);                   
      CVector4 operator/(CVector4 v);                   
      CVector4 operator+(float f);                       
      CVector4 operator-(float f);                       
      CVector4 operator*(float f);                       
      CVector4 operator/(float f);                      

      void operator +=(CVector4 v);                      
      void operator -=(CVector4 v);                      
      void operator *=(CVector4 v);                     
      void operator /=(CVector4 v);                      
      void operator +=(float f);                         
      void operator -=(float f);                        
      void operator *=(float f);                         
      void operator /=(float f);                        

      bool operator ==(CVector4 v);                    
      bool operator !=(CVector4 v); 

	  ///���
	  void CrossProduct(CVector4 v1, CVector4 v2);       
      void CrossProduct3(CVector4 v1, CVector4 v2,
                         CVector4 v3);  

	  ///���
      float DotProduct3(CVector4 v1);                   
      float DotProduct4(CVector4 v1);  

	  ///������������
      float GetLength();   

	  ///��һ������
      void Normal();                                     

public:
	   float x, y, z, w; 
};


#endif