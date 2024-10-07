#if !defined(AFX_DLGCLASSBREAKRENDERER_H__8C1D1C8A_E303_47C6_BF8A_FF8BEC75EE42__INCLUDED_)
#define AFX_DLGCLASSBREAKRENDERER_H__8C1D1C8A_E303_47C6_BF8A_FF8BEC75EE42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgClassBreakRenderer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgClassBreakRenderer dialog
#include "src/ColorPicker.h"
#include "src/ColorListBox.h"
#include "MainFrm.h"
#include "3D0214Doc.h"
#include "3D0214View.h"

class CDlgClassBreakRenderer : public CDialog
{
// Construction
public:
	CDlgClassBreakRenderer(CWnd* pParent = NULL);   // standard constructor
	
	BOOL GetLayerFromCurrentScene(ILayer **ipLayer);//从当前三维场景中获得ILayer接口对象	
	void CreateRampColor(double nSize);//建立颜色集
	void TinClassBreak();//Tin的分层设色过程函数	
	void RasterClassBreak();//Raster的分层设色过程函数

// Dialog Data
	//{{AFX_DATA(CDlgClassBreakRenderer)
	enum { IDD = IDD_DLG_CLASSBREAKRENDERER };
	CComboBox	m_combo_classesNum;
	
	CColorPicker	m_endcolor;
	CColorPicker	m_startcolor;
	CColorListBox   m_list_colorrange;
	//CColorPicker	m_b;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgClassBreakRenderer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgClassBreakRenderer)
	afx_msg void OnButtonColorRamp();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboClassesNum();
	afx_msg void OnButtonStartColor();
	afx_msg void OnButtonEndColor();
	virtual void OnOK();
	afx_msg void OnSelchangeListColorRange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	ILayerPtr m_ipLayer;
	IScenePtr m_ipScene;
	IEnumColorsPtr m_EnumColors;
	long m_ClassNum;
	
	IArrayPtr m_ipArray;
	int m_SelIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLASSBREAKRENDERER_H__8C1D1C8A_E303_47C6_BF8A_FF8BEC75EE42__INCLUDED_)
