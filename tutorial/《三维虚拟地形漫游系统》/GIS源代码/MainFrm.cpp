// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdAfx.h"
#include "3D0214.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_DEMO,CBRS_GRIPPER,230);
	m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_AUTHOR,CBRS_GRIPPER,80);
	m_wndStatusBar.UpdateWindow();


	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!m_wndMyToolBar1.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndMyToolBar1.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndMyToolBar1.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMyToolBar1);
	//设置窗口标题
	m_wndMyToolBar1.SetWindowText(_T("Tools"));

    //将ToolControl 加入ToolBar
    #define SNAP_WIDTH 1000 //the width   
    int index = 0;
	RECT rect;
    while (m_wndMyToolBar1.GetItemID(index) !=ID_PLACEHOLD) index++;
    m_wndMyToolBar1.SetButtonInfo(index, ID_PLACEHOLD, TBBS_SEPARATOR,SNAP_WIDTH);
    //找出放toolBarControl 的图标的位置

    m_wndMyToolBar1.GetItemRect(index, &rect);//获取RECT指针
    if (!m_tbr.Create("", WS_CHILD|WS_VISIBLE|CBS_AUTOHSCROLL| 
                                       CBS_DROPDOWNLIST|CBS_HASSTRINGS,
                                        rect, &m_wndMyToolBar1,NULL,FALSE,NULL))
	{
        AfxMessageBox("Failed to create ToolBarControl\n");
        return FALSE;
    }
    m_tbr.SetToolTips(true); 
    m_tbr.ShowWindow(SW_SHOW);

	//生成活动Bar1
    if (!m_wndMyBar1.Create(_T("Table of Contents"),this,CSize(200,400),TRUE,123)) 
	{ TRACE0("Failed to create mybar\n"); return -1; } 
    //设置样式
    m_wndMyBar1.SetBarStyle(m_wndMyBar1.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC); 
 	//设置停靠
    m_wndMyBar1.EnableDocking(CBRS_ALIGN_LEFT);
 	DockControlBar(&m_wndMyBar1, AFX_IDW_DOCKBAR_LEFT);///停靠在右边
	//生成TABCTRL
	m_TabCtrl.Create(TCS_DOWN|WS_CHILD|WS_VISIBLE,CRect(0,0,200,400),&m_wndMyBar1,125);
	if(	m_tocdlg.Create(IDD_TOCDLG,&m_TabCtrl))
		m_TabCtrl.AddPage(&m_tocdlg,"Display");
	m_tocdlg.ShowWindow(SW_SHOW);       //显示出来
	m_TabCtrl.UpdateWindow(); ///更新TabControl
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
    // center window at 90% of full screen
	int xSize = ::GetSystemMetrics (SM_CXSCREEN);
	int ySize = ::GetSystemMetrics (SM_CYSCREEN);
	cs.cx = xSize*8/10;
	cs.cy = ySize*8/10;
	cs.x = (xSize-cs.cx)/2;
	cs.y = (ySize-cs.cy)/2;
	return CFrameWnd::PreCreateWindow(cs);

//	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif; //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

