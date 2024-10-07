// LoadOBJ.h: interface for the CLoadOBJ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADOBJ_H__C86685F4_FFC5_11D5_AF74_879002C05864__INCLUDED_)
#define AFX_LOADOBJ_H__C86685F4_FFC5_11D5_AF74_879002C05864__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyTexture.h"

typedef unsigned long ULONG;
typedef unsigned char UCHAR;
typedef unsigned char BYTE;

#define MAX_FILE_NAME 256
#define MAX_TEXTURES 128

class CTexture
{
public:
	CTexture();
	virtual ~CTexture();
	CMyTexture* myTex;
	void Init();
	GLuint AddNewTexture(char *lpszName); // װ���µ�����
protected:
	int cur_texture;
	GLuint textures[MAX_TEXTURES];

};

// ����
struct SMat
{
	char *MatName;		// ��������
	
	float ar, ag, ab;   // Ambient r, g, b
	float dr, dg, db;   // Diffuse r, g, b
	float sr, sg, sb;   // Specular r, g, b

	GLuint texture;		// ��������
	struct SMat *next;	// �б��е���һ������
};

// ������
struct STriangle
{
	int a, b, c;	// �����ζ�������
	int ta, tb, tc; // ��������������
	int na, nb, nc; // �����η�����
	struct STriangle *next;
};

// �����ο�
struct STriangleBlock
{
	STriangle *tr;	// ������
	SMat *mat;		// ����
	struct STriangleBlock *next;
};

class CLoadOBJ  
{
public:
	CLoadOBJ();
	virtual ~CLoadOBJ();
	int LoadFromFile(char *lpszName, CTexture *tex_obj); // װ��Obj�ļ��Ͷ�Ӧ������
	int GetMtlName(FILE *f); // ���MTL�ļ�
	int LoadObjFile(FILE *f); // װ��Obj�ļ�
	int LoadMtlFile(FILE *f, CTexture *tex_obj); // װ��MTL�ļ�
	SMat *GetMaterialByName(char *lpszName);
	void Draw();
protected:
	int m_vtotal;			// �ܶ�����
	int m_vntotal;			// �ܶ��㷽������
	int m_vttotal;			// ������������
	float *vx, *vy, *vz;	// ָ�򶥵��������е�ָ��
	float *vnx, *vny, *vnz;	// ָ�򶥵㷽�������е�ָ��
	float *tx, *ty;			// ָ�������������е�ָ��
	char *m_lpMtlName;		// Mtl�ļ�����
	struct SMat *Materials;
	struct STriangleBlock *tb; // ���еĶ����

};

#endif // !defined(AFX_LOADOBJ_H__C86685F4_FFC5_11D5_AF74_879002C05864__INCLUDED_)
