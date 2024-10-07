
//========================================================
/**
*  @file      Matrix.h
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
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vector.h"

/** 4x4������ */
class  CMatrix4x4
{
	public:
	  ///���캯��
      CMatrix4x4();                               
      CMatrix4x4(const CMatrix4x4 &m);             
      CMatrix4x4(float r11, float r12, float r13, float r14,
                 float r21, float r22, float r23, float r24,
                 float r31, float r32, float r33, float r34,
                 float r41, float r42, float r43, float r44);
      ~CMatrix4x4();                               

      ///���þ���
	  void Clear();                                
      void Zero();                                 

	  ///���������
      void operator=(CMatrix4x4 m);                
      CMatrix4x4 operator-(CMatrix4x4 m);         
      CMatrix4x4 operator+(CMatrix4x4 m);          
      CMatrix4x4 operator*(CMatrix4x4 m);          
      CMatrix4x4 operator/(CMatrix4x4 m);          

      void operator +=(CMatrix4x4 m);             
      void operator -=(CMatrix4x4 m);              
      void operator *=(CMatrix4x4 m);              
      void operator /=(CMatrix4x4 m);             
      
      CMatrix4x4 operator-(float f);               
      CMatrix4x4 operator+(float f);               
      CMatrix4x4 operator*(float f);               
      CMatrix4x4 operator/(float f);               

      void operator -=(float f);                   
      void operator +=(float f);                   
      void operator *=(float f);                  
      void operator /=(float f);                   

      bool operator ==(CMatrix4x4 v);             
      bool operator !=(CMatrix4x4 v);              

	  ///ƽ��һ����
      void Translate(CVector4 Translate);          
      void Translate(float x, float y, float z);   
      void inverseTranslate();

	  ///��תһ����
	  void Rotate(double angle, float x, float y,
                  float z);    
	  
	  ///������������
	  CVector4 VectorMatrixMultiply(CVector4 v);  
      CVector4 VectorMatrixMultiply3x3(CVector4 v);


public:
	float matrix[16];
};

#endif