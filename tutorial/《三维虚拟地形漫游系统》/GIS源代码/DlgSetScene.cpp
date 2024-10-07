// DlgSetScene.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgSetScene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetScene dialog


CDlgSetScene::CDlgSetScene(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetScene::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetScene)
	m_edit_exaggerationFactor = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgSetScene::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetScene)
	DDX_Text(pDX, IDC_EDIT_EXAGGERATIONFACTOR, m_edit_exaggerationFactor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetScene, CDialog)
	//{{AFX_MSG_MAP(CDlgSetScene)
	ON_BN_CLICKED(IDC_BUTTON_EXAGGERATIONFACTOR, OnButtonExaggerationfactor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetScene message handlers

void CDlgSetScene::OnButtonExaggerationfactor() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SetExaggerationFactor(m_edit_exaggerationFactor);
	
}

void CDlgSetScene::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	SetExaggerationFactor(m_edit_exaggerationFactor);
	
	CDialog::OnOK();
}
void CDlgSetScene::SetExaggerationFactor( double factor) 
{
	//先得到Scene 
	HRESULT hr;
	CMainFrame *pFrame=(CMainFrame*)AfxGetMainWnd();//获得主框架指针
	CMy3D0214View *pView=(CMy3D0214View*)pFrame->GetActiveView();//获视图指针
	IScenePtr  ipScene; 
	if(!pView->GetSceneFromView(&ipScene))
	{
		AfxMessageBox("不能得到Scene");
		return;
	}	
	hr=ipScene->put_ExaggerationFactor(factor);
	ISceneGraphPtr ipSceneGrp;
	hr=ipScene->get_SceneGraph(&ipSceneGrp);
	hr=ipSceneGrp->RefreshViewers();
}