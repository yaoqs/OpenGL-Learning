//=========================================================================
/**
*  @file      Test.h
*
*  ��Ŀ������ emboss��͹ӳ��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-16
*
*  ����������������������¼����麯��
*																								
*	virtual bool Init();														
*		ִ�����еĳ�ʼ������������ɹ���������true							
*																			
*	virtual void Uninit();													
*		ִ�����е�ж�ع���										
*																			
*	virtual void Update(DWORD milliseconds);										
*		ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ
*																			
*	virtual void Draw();															
*		ִ�����еĻ��Ʋ���
*/
//=========================================================================

#ifndef __TEST_H__
#define __TEST_H__

#include "stdafx.h"
#include "GLFrame.h"	     /**< ���������Ŀ���� */
#include "TGALoader.h"
#include "Vector.h"
#include "Matrix.h"
#include "glext.h"           /**< ����glext.hͷ�ļ� */

/** ���嶥��ṹ�� */
struct Vertex
{
    float tu, tv;     /**< �������� */
    float nx, ny, nz; /**< ���� */
    float x, y, z;    /**< �������� */
};

/** ������� */
const int NUM_VERTICES = 4;

/** ��������ṹ */
struct TexCoords
{
    float tu2, tv2;
};

/** ��GL_Application������һ������ */
class Test : GLApplication								
{
public:
	bool	Init();							   /**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						   /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		   /**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							   /**< ִ�����еĻ��Ʋ��� */
	
	bool    isExtensionSupported(const char *string);  /**< ����Ƿ�֧����չ */
	bool    initMultiTexture();                        /**< ��ʼ�� */
	
    Vector3 computeTangentVector(Vertex pVtxA,Vertex pVtxB,Vertex pVtxC); /**< ���������� */
    void computeTangentsAndBinormals(void);     /**< �������ж��������T������B���� */
    void shiftTextureCoordinates(void);         /**< ƫ���������� */
    void renderQuadWithEmbossBumpMapping(void); /**< ��Ⱦ����͹���� */

			
private:
	friend class GLApplication;				  
	Test(const char * class_name);	       /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	CTGALoader  m_texture;                   /**< TGA�ļ������� */
	bool        sp;                          /**< �ո���Ƿ��ͷ� */

};


#endif	// __TEST_H__