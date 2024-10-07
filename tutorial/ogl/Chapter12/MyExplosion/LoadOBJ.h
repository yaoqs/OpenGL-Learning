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

// 材质
struct SMat
{
	char *MatName;		// 材质名称
	float ar, ag, ab;   // Ambient r, g, b
	float dr, dg, db;   // Diffuse r, g, b
	float sr, sg, sb;   // Specular r, g, b
	GLuint texture;		// 材质纹理
	struct SMat *next;	// 纹理序列中的下一个材质
};

// 三角形
struct STriangle
{
	int a, b, c;	// 顶点索引a, b, c
	int ta, tb, tc; // 顶点纹理坐标ta, tb, tc
	int na, nb, nc; // 法向量na, nb, nc
	struct STriangle *next;
};

struct STriangleFull
{
	float x1, y1, z1;	// 顶点a
	float x2, y2, z2;	// 顶点b
	float x3, y3, z3;	// 顶点c
	float ofs_x, ofs_y, ofs_z; // 顶点的偏移量(爆炸方向)
	int delete_coef;
	struct STriangleFull *next;
};

// 三角形块
struct STriangleBlock
{
	STriangle *tr; // 三角形
	SMat *mat;     // 材质
	struct STriangleBlock *next;
};

struct STriangleBlockFull
{
	STriangleFull *tr;	// 三角形
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
	int m_vtotal;		// 顶点总数
	int m_vntotal;		// 顶点法向量总数
	int m_vttotal;		// 纹理坐标总数
	float *vx, *vy, *vz;	
	float *vnx, *vny, *vnz;	
	float *tx, *ty;			
	char *m_lpMtlName; 
	struct SMat *Materials;
	struct STriangleBlock *tb; 
	// 控制爆炸的变量
	char Explosion_Flag;
	struct STriangleBlockFull *e_tb; // 所有多边形
};

#endif // !defined(AFX_LOADOBJ_H__A7CAE694_FF95_11D5_AF74_9FF7D5375F64__INCLUDED_)
