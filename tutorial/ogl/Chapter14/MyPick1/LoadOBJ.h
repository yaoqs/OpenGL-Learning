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
	GLuint AddNewTexture(char *lpszName); // 装入新的纹理
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
	struct SMat *next;	// 列表中的下一个材质
};

// 三角形
struct STriangle
{
	int a, b, c;	// 三角形顶点坐标
	int ta, tb, tc; // 三角形纹理坐标
	int na, nb, nc; // 三角形方向量
	struct STriangle *next;
};

// 三角形块
struct STriangleBlock
{
	STriangle *tr;	// 三角形
	SMat *mat;		// 材质
	struct STriangleBlock *next;
};

class CLoadOBJ  
{
public:
	CLoadOBJ();
	virtual ~CLoadOBJ();
	int LoadFromFile(char *lpszName, CTexture *tex_obj); // 装入Obj文件和对应的纹理
	int GetMtlName(FILE *f); // 获得MTL文件
	int LoadObjFile(FILE *f); // 装入Obj文件
	int LoadMtlFile(FILE *f, CTexture *tex_obj); // 装入MTL文件
	SMat *GetMaterialByName(char *lpszName);
	void Draw();
protected:
	int m_vtotal;			// 总顶点数
	int m_vntotal;			// 总顶点方向量数
	int m_vttotal;			// 总纹理坐标数
	float *vx, *vy, *vz;	// 指向顶点坐标序列的指针
	float *vnx, *vny, *vnz;	// 指向顶点方向量序列的指针
	float *tx, *ty;			// 指向纹理坐标序列的指针
	char *m_lpMtlName;		// Mtl文件名称
	struct SMat *Materials;
	struct STriangleBlock *tb; // 所有的多边形

};

#endif // !defined(AFX_LOADOBJ_H__C86685F4_FFC5_11D5_AF74_879002C05864__INCLUDED_)
