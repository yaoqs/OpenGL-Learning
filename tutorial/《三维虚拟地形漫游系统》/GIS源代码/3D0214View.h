// 3D0214View.h : interface of the CMy3D0214View class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "scenecontroldefault.h"
//}}AFX_INCLUDES

#if !defined(AFX_3D0214VIEW_H__77197693_96BF_4D35_96B3_BA163F1702A8__INCLUDED_)
#define AFX_3D0214VIEW_H__77197693_96BF_4D35_96B3_BA163F1702A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DlgProfileGraph.h"
#include "MainFrm.h"
#include "DlgCreateRasterIDW.h"
#include "DlgCreateTINfromFeature.h"
#include "DlgSetScene.h"
#include "DlgBaseHeight.h"
#include "DlgClassBreakRenderer.h"
#include "DlgSlope.h"
#include "DlgViewshed.h"
#include "DlgCreateContour.h"
#include "DlgInfoQuery.h"


class CMy3D0214View : public CFormView
{
protected: // create from serialization only
	CMy3D0214View();
	DECLARE_DYNCREATE(CMy3D0214View)

public:
	//{{AFX_DATA(CMy3D0214View)
	enum { IDD = IDD_MY3D0214_FORM };
	CSceneControlDefault	m_Scontrol;
	//}}AFX_DATA

// Attributes
public:
	CMy3D0214Doc* GetDocument();
	ISceneControlPtr m_ipSceneControl;
	IScenePtr m_ipScene;
    ISceneGraphPtr m_ipSceneGrap;
	ISceneViewerPtr  m_ipViewer;



	CString   FindBasename(CString filename);
	BOOL      DeleteSHP(CString pathname,CString filename);
	int       IsDirectory(CString pathname);
	CString   GetCurrentDir();
	BOOL      MakeProfileChart(CString sDir,CString sFileName,CString sGraphTitle,CString sGraphSubTitle);
    void      DoRealGraphWork(long xPos,long yPos);
private:
	int tbrIsstarted;
	ILayerPtr m_ipLayer;

	int              m_Scheckstate;//

	int              m_Qcheckstate;//空间查询按钮状态
		
	int              m_Pcheckstate;  //剖面图绘制按钮状态
	IPointCollectionPtr m_pScenePoints;//收集线段端点;
	CDlgProfileGraph *m_pDlg;  //模态对话框
	CDlgInfoQuery *m_pInfoQueryDlg;


	// Operations
public:
	bool GetSceneFromView(IScene ** ipScene);
	void LoadData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3D0214View)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMy3D0214View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy3D0214View)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileExportMap();
	afx_msg void OnAddDemToScene();
	afx_msg void OnCreateRasterIdw();
	afx_msg void OnCreatedemTin();
	afx_msg void OnSetScene();
	afx_msg void OnSetBaseheight();
	afx_msg void OnAddlayer();
	afx_msg void OnClassbreakrenderer();
	afx_msg void OnInformationQuery();
	afx_msg void OnUpdateInformationQuery(CCmdUI* pCmdUI);
	afx_msg void OnOnMouseDownScenecontrol1(long button, long shift, long x, long y);
	afx_msg void OnOnMouseMoveScenecontrol1(long button, long shift, long x, long y);
	afx_msg void OnCreateSlop();
	afx_msg void OnViewshed();
	afx_msg void OnLineofsightprofile();
	afx_msg void OnUpdateLineofsightprofile(CCmdUI* pCmdUI);
	afx_msg void OnCreateContour();
	afx_msg void OnSelectfeatrues();
	afx_msg void OnUpdateSelectfeatrues(CCmdUI* pCmdUI);
	afx_msg void OnOnMouseUpScenecontrol1(long button, long shift, long x, long y);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnUpdateIndicatorDEMO(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorAUTHOR(CCmdUI *pCmdUI);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 3D0214View.cpp
inline CMy3D0214Doc* CMy3D0214View::GetDocument()
   { return (CMy3D0214Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3D0214VIEW_H__77197693_96BF_4D35_96B3_BA163F1702A8__INCLUDED_)
