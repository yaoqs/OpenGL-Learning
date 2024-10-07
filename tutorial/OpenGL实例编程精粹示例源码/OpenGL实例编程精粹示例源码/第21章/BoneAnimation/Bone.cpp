//========================================================
/**
*  @file      Bone.pp
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
#include "Bone.h"

CBone::CBone() : parent(0), length(0)
{

}

/** ���ù������� */
void CBone::SetBone(unsigned int P, float L)
{
     parent = P; length = L;
}


void CBone::SetBone(unsigned int P, float L, CMatrix4x4 R, CMatrix4x4 A)
{
    parent = P; length = L; relative = R; absolute = A;
}


CBoneVertex::CBoneVertex() : r(0), g(0), b(0), a(0), numBones(0)
{
   ///��ʼ������Ա
   boneIndex[0] = 0; boneIndex[1] = 0; boneIndex[2] = 0; boneIndex[3] = 0;
   weights[0] = 0; weights[1] = 0; weights[2] = 0; weights[3] = 0;
}

/** ���ö�����Ϣ */
void CBoneVertex::SetVertex(CVector4 p, CVector4 n, int b1, int b2, int b3, int b4,
                            float w1, float w2, float w3, float w4,
                            float R, float G, float B, float A, int numB)
{
   
   pos = p;
   normal = n;
   boneIndex[0] = b1; boneIndex[1] = b2; boneIndex[2] = b3; boneIndex[3] = b4;
   weights[0] = w1; weights[1] = w2; weights[2] = w3; weights[3] = w4;
   r = R; g = G; b = B; a = A;
   numBones = numB;
}
