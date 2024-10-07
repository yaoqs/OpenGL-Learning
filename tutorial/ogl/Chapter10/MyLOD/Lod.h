// Lod.h: interface for the CLod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOD_H__8C91EFFD_346E_4F84_A1E4_F20F3431FFF0__INCLUDED_)
#define AFX_LOD_H__8C91EFFD_346E_4F84_A1E4_F20F3431FFF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define DISTANCE(v1, v2) sqrt((v1[0] - v2[0]) * (v1[0] - v2[0]) + \
                              (v1[2] - v2[2]) * (v1[2] - v2[2]))

#define MAP 256
#define QUAD_MAP (MAP + 1)
#define IX_QT(x, z) (((x)%QUAD_MAP) + (((z)%QUAD_MAP) * QUAD_MAP))
#define EDGE_POINT 0
#define NODE_POINT 1
#define UNKNOWN    2
//方向的宏定义
#define NORTH   0
#define WEST    1
#define SOUTH   2
#define EAST    3
#define NW      4
#define NE      5
#define SW      6
#define SE      7
#define NORTH_L 8
#define NORTH_R 9
#define WEST_T  10
#define WEST_B  11
#define SOUTH_L 12
#define SOUTH_R 13
#define EAST_T  14
#define EAST_B  15
#define texScale 64.0 

#define TRUE 1
#define FALSE 0
#define WIDTH 4.0

#define ZOOMSIZE 4

#define COMP 128 
#define SHIFT 7 

#define FORWARD 1
#define ROTATE 2
#define LOOKUP 3

typedef struct COLOUR 
{
	int r,g,b;
} COLOUR;

class CLod  
{
public:
	CLod();
	virtual ~CLod();

	BOOL m_bFlag;

	void reset_quad_tree(void);
	void draw(int x, int z, int width, int direction);
	void setup_quadtree(int x, int y, int width);
	void draw_point(int x, int z, int width, int direction);
	void triangle1(int x1, int z1, int x2, int z2, int x3, int z3) ;
	void triangle2(int x1, int z1, int x2, int z2, int x3, int z3) ;
	void setColor(int x, int z); 
	void setVertex(int x, int z); 

};

#endif // !defined(AFX_LOD_H__8C91EFFD_346E_4F84_A1E4_F20F3431FFF0__INCLUDED_)
