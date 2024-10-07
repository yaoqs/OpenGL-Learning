// LoadOBJ.h: interface for the CLoadOBJ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADOBJ_H__A7CAE694_FF95_11D5_AF74_9FF7D5375F64__INCLUDED_)
#define AFX_LOADOBJ_H__A7CAE694_FF95_11D5_AF74_9FF7D5375F64__INCLUDED_

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
	CMyTexture*  m_Texture;
	void Init();
	GLuint AddNewTexture(char *lpszName); 
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
	struct SMat *next;	// ���������е���һ������
};

// ������
struct STriangle
{
	int a, b, c;	// ��������a, b, c
	int ta, tb, tc; // ������������ta, tb, tc
	int na, nb, nc; // ������na, nb, nc
	struct STriangle *next;
};

struct STriangleFull
{
	float x1, y1, z1;	// ����a
	float x2, y2, z2;	// ����b
	float x3, y3, z3;	// ����c
	float ofs_x, ofs_y, ofs_z; // �����ƫ����(��ը����)
	int delete_coef;
	struct STriangleFull *next;
};

// �����ο�
struct STriangleBlock
{
	STriangle *tr; // ������
	SMat *mat;     // ����
	struct STriangleBlock *next;
};

struct STriangleBlockFull
{
	STriangleFull *tr;	// ������
	struct STriangleBlockFull *next;
};

class CLoadOBJ  
{
public:
	CLoadOBJ();
	virtual ~CLoadOBJ();

	int LoadFromFile(char *lpszName, CTexture *tex_obj); 
	int GetMtlName(FILE *f); 
	int LoadObjFile(FILE *f); 
	int LoadMtlFile(FILE *f, CTexture *tex_obj); 
	SMat *GetMaterialByName(char *lpszName);
	void Draw();
	void DrawExplode();
	void Explosion();
	void Explosion_Step(float coef);
	void Explosion_End();
protected:
	int m_vtotal;		// ��������
	int m_vntotal;		// ���㷨��������
	int m_vttotal;		// ������������
	float *vx, *vy, *vz;	
	float *vnx, *vny, *vnz;	
	float *tx, *ty;			
	char *m_lpMtlName; 
	struct SMat *Materials;
	struct STriangleBlock *tb; 
	// ���Ʊ�ը�ı���
	char Explosion_Flag;
	struct STriangleBlockFull *e_tb; // ���ж����
};

#endif // !defined(AFX_LOADOBJ_H__A7CAE694_FF95_11D5_AF74_9FF7D5375F64__INCLUDED_)
