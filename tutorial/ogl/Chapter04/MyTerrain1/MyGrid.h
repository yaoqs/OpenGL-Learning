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
	CMyGrid(int width, int height); // �������Ĺ��캯��

	virtual ~CMyGrid();

	void SetDimensions(int width, int height); // ���õ�������ߴ�
	void SetCellLength(float l);
	void SetHeight(float min, float max); // ���õ��ε���С�����߶�
	void SetInterpolationLevel(int level);
	void GenerateNewGrid(); // �����µĵ���
	void Draw();			// ���Ƶ���ͼ��
	void Compile();			// ���ɵ�����ʾ�б�

protected:

	float *grid;				// ����
	int m_width, m_height;		// ������ܳ����ܿ�
	float m_min, m_max;			// �������С�����ֵ
	float m_cell;				// ��Ԫ��ĳߴ�
	int m_interpol_level;		// ���ߵĲ�ֵ�����

};

#endif // !defined(AFX_MYGRID_H__B294C4F4_0031_11D6_AF74_F1529D857764__INCLUDED_)
