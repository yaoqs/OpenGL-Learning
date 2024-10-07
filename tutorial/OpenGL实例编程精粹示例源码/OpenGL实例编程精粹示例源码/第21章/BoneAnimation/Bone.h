//========================================================
/**
*  @file      Bone.h
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
#ifndef __BONE_H__
#define __BONE_H__

#include "Matrix.h"

/** ������ */
class CBone
{
public:
      CBone();
      
	  /** ���ù��� */
      void SetBone(unsigned int P, float L);
      void SetBone(unsigned int P, float L, CMatrix4x4 R, CMatrix4x4 A);

      unsigned int parent;  /**< ����� */
      float length;         /**< ���� */

	  /** �任���� */
      CMatrix4x4 relative; 
      CMatrix4x4 absolute;
};

/** ���������� */
class CBoneVertex
{
   public:
      CBoneVertex();

	  /** ���ö������� */
      void SetVertex(CVector4 p, CVector4 n, int b1, int b2, int b3, int b4,
                     float w1, float w2, float w3, float w4, float R, float G,
                     float B, float A, int numB);
      
      
      CVector4 pos;         /**< λ�� */
      CVector4 normal;      /**< ���� */
      
      int boneIndex[4];     /**< �������� */
      float weights[4];     /**< Ȩֵ */
      int numBones;         /**< Ӱ��Ĺ�����Ŀ */

      float r, g, b, a;     /**< ��ɫ */
};

#endif