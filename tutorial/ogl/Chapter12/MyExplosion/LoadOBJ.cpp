// LoadOBJ.cpp: implementation of the CLoadOBJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyExplosion.h"
#include "LoadOBJ.h"
#include <math.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const float pi = 3.1415926;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static char *NormalizeString(char *s)
{
	while (*s == ' ') s++;
	ULONG l = strlen(s);
	for (ULONG i=(l-1); i>0; i--)
		if (s[i] < 33) s[i] = 0;
		else break;
	return s;
}

static void ParseFloat(char *s, float *a, float *b, float *c)
{
	int i, j;
	int x, y, z;
	s = NormalizeString(s);
	x = 0; y = -1; z = -1;
	j = (int)strlen(s);
	for (i=0; i<j; i++)
	{
		if ((s[i] == ' ') || (s[i] == '\n'))
		{
			s[i] = 0;
			if (y == -1) y = i+1;
			else
			if (z == -1) z = i+1;
		}
	}
	*a = (float)atof(&s[x]);
	*b = (float)atof(&s[y]);
	*c = (float)atof(&s[z]);
}

static int Parse3(char *s, int *a, int *b, int *c)
{
	int i, j;
	char *sp;
	int stage=0;
	j = (int)strlen(s);
	sp = s;
	for (i=0; i<j; i++)
	{
		if ((s[i] == '/') || (i == j-1))
		{
			if (i != j-1) s[i] = 0;
			switch (stage)
			{
				case 0: *a = atoi(sp); break;
				case 1: *b = atoi(sp); break;
				case 2: *c = atoi(sp); break;
			}
			stage++;
			sp = &s[i+1];
		}
	}
	return stage;
}

static int ParseFace(char *s, int *a, int *ta, int *na, int *b, int *tb, int *nb, int *c, int *tc, int *nc)
{
	int i, j, stage=0, total;
	char *sp;
	s = NormalizeString(s);
	j = (int)strlen(s);
	sp = s;
	for (i=0; i<j; i++)
	{
		if ((s[i] == ' ') || (i == j-1))
		{
			if (i != j-1) s[i] = 0;
			 
			switch (stage)
			{
				case 0: total = Parse3(sp, a, ta, na); break;
				case 1: total = Parse3(sp, b, tb, nb); break;
				case 2: total = Parse3(sp, c, tc, nc); break;
			}
			stage++;
			sp = &s[i+1];
		}
	}
	return total;
}

CTexture::CTexture()
{
	cur_texture = 0;
}

CTexture::~CTexture()
{
	// 删除所有纹理
	if (cur_texture > 0) glDeleteTextures(cur_texture, &textures[0]);
}

void CTexture::Init()
{
	glGenTextures(MAX_TEXTURES, textures);
}


GLuint CTexture::AddNewTexture(char *lpszName)
{
	unsigned *teximage;
	int texwid, texht;
	int texcomps;
	teximage = m_Texture->read_texture(lpszName, &texwid, &texht, &texcomps);
	if (!teximage) return -1;
	
	glBindTexture(GL_TEXTURE_2D, textures[cur_texture]);
	cur_texture++;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texwid, texht, GL_RGBA, GL_UNSIGNED_BYTE, teximage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	
	free(teximage);

	return textures[cur_texture-1];
}


CLoadOBJ::CLoadOBJ()
{
	m_lpMtlName = NULL;
	Materials = NULL;
	tb = NULL;
	tx = NULL;
	ty = NULL;
	vx = NULL;
	vy = NULL;
	vz = NULL;
	vnx = NULL;
	vny = NULL;
	vnz = NULL;
	m_vtotal = 0;
	m_vttotal = 0;
	m_vntotal = 0;
	Explosion_Flag = 0;
	srand((unsigned int)time(NULL));
	e_tb = NULL;
}

CLoadOBJ::~CLoadOBJ()
{
	STriangle *cur_s, *temp_s;
	STriangleFull *cur_f, *temp_f;
	STriangleBlock *temp;
	STriangleBlockFull *temp1;

	delete [] m_lpMtlName;
	if (vx) delete [] vx;
	if (vy) delete [] vy;
	if (vz) delete [] vz;

	if (vnx) delete [] vnx;
	if (vny) delete [] vny;
	if (vnz) delete [] vnz;

	if (tx) delete [] tx;
	if (ty) delete [] ty;

	while (tb)
	{
		temp = tb->next;
		cur_s = tb->tr;
		while (cur_s)
		{
			temp_s = cur_s->next;
			delete cur_s;
			cur_s = temp_s;
		}
		delete tb;
		tb = temp;
	}
	while (e_tb)
	{
		temp1 = e_tb->next;
		cur_f = e_tb->tr;
		while (cur_f)
		{
			temp_f = cur_f->next;
			delete cur_f;
			cur_f = temp_f;
		}
		delete e_tb;
		e_tb = temp1;
	}
}

// 获得Mtl文件
int CLoadOBJ::GetMtlName(FILE *f)
{
	char buffer[512];
	char *str;
	while (!feof(f))
	{
		fgets(buffer, 512, f);
		str = NormalizeString(buffer);
		// 分析字符串
		if (str[0] == '#') continue;
		for (ULONG i=0; i<strlen(str); i++)
		{
			if (str[i] == ' ')
			{
				str[i] = 0;
				if (!strcmp(str, "mtllib")) 
				{
					// 删除老的Mtl名称
					if (m_lpMtlName) delete [] m_lpMtlName;
	
					m_lpMtlName = new char [MAX_FILE_NAME];

					strcpy(m_lpMtlName, &str[i+1]);
					return 0;

				} else break;
			}
			else continue;
		}
	}
	
	return -1; // 没有找到Mtl文件
}

int CLoadOBJ::LoadObjFile(FILE *f)
{
	struct vertx
	{
		float x, y, z;
		struct vertx *next;
	};
	struct tcoord
	{
		float x, y;
		struct tcoord *next;
	};
	struct vertx *vrt=NULL, *vrt_cur, *vrt_temp;
	struct vertx *nrm=NULL, *nrm_cur, *nrm_temp;
	struct tcoord *tc=NULL, *tc_cur, *tc_temp;
	char buffer[512];
	char *str;
	float zzz;
	ULONG i;
	struct STriangleBlock *tb_cur, *tb_temp;
	struct STriangle *tr_cur, *tr_temp;
	int pa, pb, pc, pat, pbt, pct, pan, pbn, pcn, total; 
	m_vtotal = 0;
	m_vttotal = 0;
	while (!feof(f))
	{
		fgets(buffer, 512, f);
		str = NormalizeString(buffer);
		if (str[0] == '#' || str[0] == 'g' || str[0] == 0) continue;
		for (i=0; i<strlen(str); i++)
		{
			if (str[i] == ' ')
			{
				str[i] = 0;
				if (!strcmp(str, "v")) // 顶点坐标
				{
					if (!vrt)
					{
						vrt = new vertx;
						vrt_cur = vrt;
					}
					else
					{
						vrt_temp = new vertx;
						vrt_cur->next = vrt_temp;
						vrt_cur = vrt_temp;
					}
					vrt_cur->next = NULL;
					ParseFloat(&str[i+1], &vrt_cur->x, &vrt_cur->y, &vrt_cur->z);
					m_vtotal++;
					break;
				}
				else
				if (!strcmp(str, "vt")) // 纹理坐标
				{
					if (!tc)
					{
						tc = new tcoord;
						tc_cur = tc;
					}
					else
					{
						tc_temp = new tcoord;
						tc_cur->next = tc_temp;
						tc_cur = tc_temp;
					}
					tc_cur->next = NULL;
					ParseFloat(&str[i+1], &tc_cur->x, &tc_cur->y, &zzz);
					m_vttotal++;
					break;
				} 
				else
				if (!strcmp(str, "vn")) // 法向坐标
				{
					if (!nrm)
					{
						nrm = new vertx;
						nrm_cur = nrm;
					}
					else
					{
						nrm_temp = new vertx;
						nrm_cur->next = nrm_temp;
						nrm_cur = nrm_temp;
					}
					nrm_cur->next = NULL;
					ParseFloat(&str[i+1], &nrm_cur->x, &nrm_cur->y, &nrm_cur->z);
					m_vntotal++;
					break;
				}
				else
				if (!strcmp(str, "usemtl")) 
				{
					if (!tb)
					{
						tb = new STriangleBlock;
						tb_cur = tb;

					} else
					{
						tb_temp = new STriangleBlock;
						tb_cur->next = tb_temp;
						tb_cur = tb_temp;
					}
					tb_cur->next = NULL;
					tb_cur->mat = GetMaterialByName(&str[i+1]);
					tb_cur->tr = NULL;
					break;
				}
				else
				if (!strcmp(str, "f"))
				{
					total = ParseFace(&str[i+1], &pa, &pat, &pan, &pb, &pbt, &pbn, &pc, &pct, &pcn);
					if (!tb_cur->tr)
					{
						tb_cur->tr = new STriangle;
						tr_cur = tb_cur->tr;
					}
					else
					{
						tr_temp = new STriangle;
						tr_cur->next = tr_temp;
						tr_cur = tr_temp;
					}
					tr_cur->next = NULL;
					
					if (total > 0)
					{
						tr_cur->a = pa;
						tr_cur->b = pb;
						tr_cur->c = pc;
					}
					if (total > 1)
					{
						tr_cur->ta = pat;
						tr_cur->tb = pbt;
						tr_cur->tc = pct;
					}
					if (total > 2)
					{
						tr_cur->na = pan;
						tr_cur->nb = pbn;
						tr_cur->nc = pcn;
					}
					break;
				}
			}
			else continue;
		}
	}
	// 为顶点序列分配存储空间
	vx = new float [m_vtotal];
	vy = new float [m_vtotal];
	vz = new float [m_vtotal];
	// 为法向量分配存储空间
	vnx = new float [m_vntotal];
	vny = new float [m_vntotal];
	vnz = new float [m_vntotal];
	// 为纹理坐标序列分配存储空间
	tx = new float [m_vttotal];
	ty = new float [m_vttotal];
	i = 0;
	// 保存并删除顶点序列
	vrt_cur = vrt;
	while (vrt_cur)
	{
		vx[i] = vrt_cur->x;
		vy[i] = vrt_cur->y;
		vz[i] = vrt_cur->z;
		i++;

		vrt_temp = vrt_cur->next;
		delete vrt_cur;
		vrt_cur = vrt_temp;
	}

	i = 0;
	// 保存和删除方向量序列
	nrm_cur = nrm;
	while (nrm_cur)
	{
		vnx[i] = nrm_cur->x;
		vny[i] = nrm_cur->y;
		vnz[i] = nrm_cur->z;
		i++;

		nrm_temp = nrm_cur->next;
		delete nrm_cur;
		nrm_cur = nrm_temp;
	}
	// 保存和删除纹理坐标序列
	i = 0;
	tc_cur = tc;
	while (tc_cur)
	{
		tx[i] = tc_cur->x;
		ty[i] = tc_cur->y;
		i++;

		tc_temp = tc_cur->next;
		delete tc_cur;
		tc_cur = tc_temp;
	}
	return -1;
}

int CLoadOBJ::LoadMtlFile(FILE *f, CTexture *tex_obj)
{
	char buffer[512];
	char *str;
	char *name;
	struct SMat *cur_mat = NULL;
	struct SMat *temp_mat = NULL;

	while (!feof(f))
	{
		fgets(buffer, 512, f);
		str = NormalizeString(buffer);

		for (ULONG i=0; i<strlen(str); i++)
		{
			if (str[i] == ' ')
			{
				str[i] = 0;
				if (!strcmp(str, "newmtl"))
				{
					name = &str[i+1];
					// 添加新的材质
					if (!Materials)
					{
						Materials = new SMat;
						cur_mat = Materials;
					}
					else
					{
						temp_mat = new SMat;
						cur_mat->next = temp_mat;
						cur_mat = temp_mat;
					}
					cur_mat->next = NULL;

					cur_mat->MatName = new char [strlen(name)+1];
					strcpy(cur_mat->MatName, name);
					cur_mat->texture = -1;
				} else
				if (!strcmp(str, "map_Kd")) 
				{
					cur_mat->texture = tex_obj->AddNewTexture(&str[i+1]); // Load this texture from file
					if (cur_mat->texture == -1) return -1;
				}
				else 
				if (!strcmp(str, "Ka"))
				{
					ParseFloat(&str[i+1], &cur_mat->ar, &cur_mat->ag, &cur_mat->ab);
				}
				else 
				if (!strcmp(str, "Kd"))
				{
					ParseFloat(&str[i+1], &cur_mat->dr, &cur_mat->dg, &cur_mat->db);
				}
				else 
				if (!strcmp(str, "Ks"))
				{
					ParseFloat(&str[i+1], &cur_mat->sr, &cur_mat->sg, &cur_mat->sb);
				}
				else break;
			}
			else continue;
		}
	}
	return -1;
}


int CLoadOBJ::LoadFromFile(char *lpszName, CTexture *tex_obj)
{
	FILE *f, *fmtl;
	f = fopen(lpszName, "rb");

	m_lpMtlName = new char[strlen(lpszName)+1];
	strcpy(m_lpMtlName, lpszName);
	m_lpMtlName[strlen(m_lpMtlName)-1] = 'l';
	m_lpMtlName[strlen(m_lpMtlName)-2] = 't';
	m_lpMtlName[strlen(m_lpMtlName)-3] = 'm';
	fmtl = fopen(m_lpMtlName, "rb");
	LoadMtlFile(fmtl, tex_obj);
	LoadObjFile(f);
	fclose(fmtl);
	fclose(f);

	return 0;
}

SMat *CLoadOBJ::GetMaterialByName(char *lpszName)
{
	SMat *temp;

	temp = Materials;
	while (temp)
	{
		if (!strcmp(temp->MatName, lpszName)) return temp;
		temp = temp->next;
	}
	return NULL;
}


static void setMaterial(float ambr, float ambg, float ambb,
                 float difr, float difg, float difb,
                 float specr, float specg, float specb,
                 float shine)
{
	float mat[4];

	mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
	mat[0] = difr; mat[1] = difg; mat[2] = difb; mat[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
	mat[0] = specr; mat[1] = specg; mat[2] = specb; mat[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine*128.0f);
}

void CLoadOBJ::Explosion()
{
	STriangleBlockFull *temp_e, *e_tb_cur;
	STriangleFull *temp_f, *cur_f;
	// 删除老的爆炸信息
	while (e_tb)
	{
		temp_e = e_tb->next;
		
		cur_f = e_tb->tr;
		while (cur_f)
		{
			temp_f = cur_f->next;
			delete cur_f;
			cur_f = temp_f;
		}
		delete e_tb;
		e_tb = temp_e;
	}

	e_tb = NULL;
	Explosion_Flag = 1;
	STriangleBlock *temp;
	STriangle *temp1;
	// 生成新的爆炸信息
	temp = tb;
	while (temp)
	{
		if (e_tb == NULL)
		{
			e_tb = new STriangleBlockFull;
			e_tb_cur = e_tb;
		}
		else
		{
			temp_e = new STriangleBlockFull;
			e_tb_cur->next = temp_e;
			e_tb_cur = temp_e;
		}
		e_tb_cur->next = NULL;
		e_tb_cur->tr = NULL;

		temp1 = temp->tr;
		while (temp1)
		{
			if (e_tb_cur->tr == NULL)
			{
				e_tb_cur->tr = new STriangleFull;
				cur_f = e_tb_cur->tr;
			}
			else
			{
				temp_f = new STriangleFull;
				cur_f->next = temp_f;
				cur_f = temp_f;
			}

			cur_f->next = NULL;
			
			cur_f->x1 = vx[temp1->a-1];
			cur_f->y1 = vy[temp1->a-1];
			cur_f->z1 = vz[temp1->a-1];
			
			cur_f->x2 = vx[temp1->b-1];
			cur_f->y2 = vy[temp1->b-1];
			cur_f->z2 = vz[temp1->b-1];

			cur_f->x3 = vx[temp1->c-1];
			cur_f->y3 = vy[temp1->c-1];
			cur_f->z3 = vz[temp1->c-1];
			float alpha, theta;
			float coef;
			alpha = ((float)(rand() % 360)*pi)/180;
			theta = ((float)(rand() % 360)*pi)/180;
			coef = (float)(rand() % 100)/100;
			cur_f->ofs_x = coef*cos(alpha)*cos(theta);
			cur_f->ofs_y = coef*sin(alpha)*cos(theta);
			cur_f->ofs_z = coef*sin(theta);
			cur_f->delete_coef = (rand() % 40);
			temp1 = temp1->next;
		}
		temp = temp->next;		
	}
}

void CLoadOBJ::Explosion_Step(float coef)
{
	STriangleBlock *temp;
	STriangle *temp1;
	STriangleBlockFull *temp_e;
	STriangleFull *temp1_e;
	temp = tb;
	temp_e = e_tb;
	while (temp)
	{
		temp1 = temp->tr;
		temp1_e = temp_e->tr;
		while (temp1)
		{
			temp1_e->x1 += temp1_e->ofs_x*coef;
			temp1_e->x2 += temp1_e->ofs_x*coef;
			temp1_e->x3 += temp1_e->ofs_x*coef;

			temp1_e->y1 += temp1_e->ofs_y*coef;
			temp1_e->y2 += temp1_e->ofs_y*coef;
			temp1_e->y3 += temp1_e->ofs_y*coef;

			temp1_e->z1 += temp1_e->ofs_z*coef;
			temp1_e->z2 += temp1_e->ofs_z*coef;
			temp1_e->z3 += temp1_e->ofs_z*coef;
			
			temp1_e->delete_coef--;

			temp1 = temp1->next;
			temp1_e = temp1_e->next;
		}
		temp = temp->next;
		temp_e = temp_e->next;
	}
}

void CLoadOBJ::Explosion_End()
{
	Explosion_Flag = 0;
}

void CLoadOBJ::Draw()
{
	STriangleBlock *temp;
	STriangle *temp1;
	if (Explosion_Flag)
	{
		DrawExplode();
		return;
	}
	temp = tb;
	while (temp)
	{
		if (temp->mat->texture != -1) glBindTexture(GL_TEXTURE_2D, temp->mat->texture);
		glColor3f(temp->mat->ar, temp->mat->ag, temp->mat->ab);
		glBegin(GL_TRIANGLES);
		temp1 = temp->tr;
		while (temp1)
		{
			glTexCoord2f(tx[temp1->ta-1], ty[temp1->ta-1]);
			glVertex3f(vx[temp1->a-1], vy[temp1->a-1], vz[temp1->a-1]);
			
			glTexCoord2f(tx[temp1->tb-1], ty[temp1->tb-1]);
			glVertex3f(vx[temp1->b-1], vy[temp1->b-1], vz[temp1->b-1]);

			glTexCoord2f(tx[temp1->tc-1], ty[temp1->tc-1]);
			glVertex3f(vx[temp1->c-1], vy[temp1->c-1], vz[temp1->c-1]);
			
			temp1 = temp1->next;
		}
		glEnd();
		temp = temp->next;		
	}
	glEnd();
}

void CLoadOBJ::DrawExplode()
{
	STriangleBlock *temp;
	STriangle *temp1;
	STriangleBlockFull *temp_e;
	STriangleFull *temp1_e;

	temp = tb;
	temp_e = e_tb;
	while (temp)
	{
		if (temp->mat->texture != -1) glBindTexture(GL_TEXTURE_2D, temp->mat->texture);
		glColor3f(temp->mat->ar, temp->mat->ag, temp->mat->ab);
		glBegin(GL_TRIANGLES);
		temp1 = temp->tr;
		temp1_e = temp_e->tr;
		while (temp1)
		{
			if (temp1_e->delete_coef > 0)
			{
				glTexCoord2f(tx[temp1->ta-1], ty[temp1->ta-1]);
				glVertex3f(temp1_e->x1, temp1_e->y1, temp1_e->z1);
			
				glTexCoord2f(tx[temp1->tb-1], ty[temp1->tb-1]);
				glVertex3f(temp1_e->x2, temp1_e->y2, temp1_e->z2);

				glTexCoord2f(tx[temp1->tc-1], ty[temp1->tc-1]);
				glVertex3f(temp1_e->x3, temp1_e->y3, temp1_e->z3);
			}
			
			temp1 = temp1->next;
			temp1_e = temp1_e->next;
		}
		glEnd();
		temp = temp->next;
		temp_e = temp_e->next;
	}
	glEnd();
}

