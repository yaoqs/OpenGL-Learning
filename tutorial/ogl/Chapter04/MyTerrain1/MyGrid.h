// MyGrid.h: interface for the CMyGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYGRID_H__B294C4F4_0031_11D6_AF74_F1529D857764__INCLUDED_)
#define AFX_MYGRID_H__B294C4F4_0031_11D6_AF74_F1529D857764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyGrid  
{
public:
	CMyGrid();
	CMyGrid(int width, int height); // 带参数的构造函数

	virtual ~CMyGrid();

	void SetDimensions(int width, int height); // 设置地形网格尺寸
	void SetCellLength(float l);
	void SetHeight(float min, float max); // 设置地形的最小和最大高度
	void SetInterpolationLevel(int level);
	void GenerateNewGrid(); // 生成新的地形
	void Draw();			// 绘制地形图形
	void Compile();			// 生成地形显示列表

protected:

	float *grid;				// 网格
	int m_width, m_height;		// 网格的总长和总宽
	float m_min, m_max;			// 网格的最小和最大值
	float m_cell;				// 单元格的尺寸
	int m_interpol_level;		// 曲线的插值界阶数

};

#endif // !defined(AFX_MYGRID_H__B294C4F4_0031_11D6_AF74_F1529D857764__INCLUDED_)
