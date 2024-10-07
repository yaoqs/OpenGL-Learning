// MyGrid.cpp: implementation of the CMyGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyTerrain1.h"
#include "MyGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
struct cvPoint
{
	float x, y, z; //点的坐标
};

//矢量相乘 C = A x B 
void vect_mult(struct cvPoint *A, struct cvPoint *B, struct cvPoint *C)
{
	C->x = A->y*B->z - A->z*B->y;
	C->y = A->z*B->x - A->x*B->z;
	C->z = A->x*B->y - A->y*B->x;
}

// Catmull-Rom Curve calculations
void cvCatmullRom(struct cvPoint *p, float t, struct cvPoint *outp)
{
	float t2, t3, t1;

	t2 = t*t;
	t3 = t*t*t;
	t1 = (1-t)*(1-t);

	outp->x = (-t*t1*p[0].x + (2-5*t2+3*t3)*p[1].x + t*(1+4*t-3*t2)*p[2].x - t2*(1-t)*p[3].x)/2;
	outp->y = (-t*t1*p[0].y + (2-5*t2+3*t3)*p[1].y + t*(1+4*t-3*t2)*p[2].y - t2*(1-t)*p[3].y)/2;
	outp->z = (-t*t1*p[0].z + (2-5*t2+3*t3)*p[1].z + t*(1+4*t-3*t2)*p[2].z - t2*(1-t)*p[3].z)/2;
}



CMyGrid::CMyGrid()
{
	grid = NULL;
	m_width = 0;
	m_height = 0;
	SetCellLength(1.0);
	SetHeight(0, 2);
	SetInterpolationLevel(20);
	SetDimensions(10, 10);

}

//带参数的构造函数
CMyGrid::CMyGrid(int width, int height)
{
	grid = NULL;
	m_width = 0;
	m_height = 0;
	SetCellLength(1.0);
	SetDimensions(width, height);
	SetHeight(0, 2);
	SetInterpolationLevel(20);
}

CMyGrid::~CMyGrid()
{
	if (grid) delete [] grid;

}

// 设置地形的大小
void CMyGrid::SetDimensions(int width, int height)
{
	if (grid) delete [] grid;
	grid = new float [height*width];

	for (int i=0; i<(height*width); i++) grid[i] = 0;
	m_width = width;
	m_height = height;
}

// 网格的边长
void CMyGrid::SetCellLength(float l)
{
	m_cell = l;
}

// 设置地形最小和最大高度
void CMyGrid::SetHeight(float min, float max)
{
	m_min = min;
	m_max = max;
}

// 曲线内的插值阶数(曲线内点的个数)
void CMyGrid::SetInterpolationLevel(int level)
{
	m_interpol_level = level;
}

// 网格的生成
void CMyGrid::GenerateNewGrid()
{
	srand((unsigned int)time(NULL));

	for (int i=0; i<m_height; i++)
		for (int j=0; j<m_width; j++)
		{
			float a = m_min+(m_max-m_min)*(float)(rand() % 10000)/10000;
			grid[i*m_width+j] = a;
		}
}

// 绘制网格地形
void CMyGrid::Draw()
{
	glCallList(1);	
}

// 生成网格列表
void CMyGrid::Compile()
{
	cvPoint pa[4];
	cvPoint op[4];
	cvPoint outp, a, b, c;
	float t_int_x=0, t_int_y=0, int_const;
	int flag;
	cvPoint *temp;

	int_const = 1.0f/m_interpol_level;
	temp = new cvPoint [m_interpol_level+1];
	glNewList(1, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int i=0; i<m_height-3; i++)
	{
		flag = 0;
		for (int j=0; j<m_width-3; j++)
		{
			t_int_x = 0;
			for (int m=0; m<m_interpol_level; m++)
			{
				
				for (int l=0; l<4; l++)
				{
					for (int k=0; k<4; k++)
					{
						pa[k].x = m_cell*(j+k);
						pa[k].y = m_cell*(i+l);
						pa[k].z = grid[(i+l)*m_width+(j+k)];
					}
					cvCatmullRom(pa, t_int_x, &op[l]);
				}
			
				t_int_y = 0;
				for (l=0; l<(m_interpol_level+1); l++)
				{
					cvCatmullRom(op, t_int_y, &outp);
					if (!flag) temp[l] = outp;
					else
					{
						if (l < (m_interpol_level))
						{
							// 计算矢量A
							a.x = temp[l+1].x - outp.x;
							a.y = temp[l+1].y - outp.y;
							a.z = temp[l+1].z - outp.z;

							// 计算矢量B
							b.x = temp[l].x - outp.x;
							b.y = temp[l].y - outp.y;
							b.z = temp[l].z - outp.z;
							
							// 计算矢量C = AxB
							vect_mult(&a, &b, &c);

							glNormal3f(c.x, c.y, c.z);
							glTexCoord2f(t_int_x, t_int_y);
							glVertex3f(outp.x, outp.y, outp.z);
							
							glTexCoord2f(t_int_x-int_const, t_int_y+int_const);
							glVertex3f(temp[l+1].x, temp[l+1].y, temp[l+1].z);
							
							glTexCoord2f(t_int_x-int_const, t_int_y);
							glVertex3f(temp[l].x, temp[l].y, temp[l].z);

						}
						if (l > 0)
						{
							// 计算矢量A
							a.x = temp[l].x - outp.x;
							a.y = temp[l].y - outp.y;
							a.z = temp[l].z - outp.z;

							// 计算矢量B
							b.x = temp[l-1].x - outp.x;
							b.y = temp[l-1].y - outp.y;
							b.z = temp[l-1].z - outp.z;
							
							// 计算矢量C = AxB
							vect_mult(&a, &b, &c);

							glNormal3f(c.x, c.y, c.z);

							glTexCoord2f(t_int_x, t_int_y);
							glVertex3f(outp.x, outp.y, outp.z);
					
							glTexCoord2f(t_int_x-int_const, t_int_y);
							glVertex3f(temp[l].x, temp[l].y, temp[l].z);
							
							glTexCoord2f(t_int_x-int_const, t_int_y-int_const);
							glVertex3f(temp[l-1].x, temp[l-1].y, temp[l-1].z);
						}
						temp[l] = outp;
					}
					t_int_y += int_const;
				}
				flag = 1;
				t_int_x += int_const;
			}
			
		}
	}
	glEnd();

	delete [] temp;
	glEndList();
}

