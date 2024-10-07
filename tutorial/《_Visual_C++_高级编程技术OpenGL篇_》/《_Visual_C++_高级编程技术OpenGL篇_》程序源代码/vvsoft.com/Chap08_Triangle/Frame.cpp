// Frame.cpp : implementation file
//

#include "stdafx.h"
#include "Triangle.h"
#include "Frame.h"
#include "MainFrm.h"
#include "body.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrame dialog


CFrame::CFrame()
{
	//{{AFX_DATA_INIT(CFrame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CFrame, CDialogBar)
	//{{AFX_MSG_MAP(CFrame)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SPEED, OnDeltaposSpinSpeed)
	ON_LBN_SELCHANGE(IDC_LIST_ANIMGROUP, OnSelchangeListAnimgroup)
	ON_LBN_DBLCLK(IDC_LIST_ANIMGROUP, OnDblclkListAnimgroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrame message handlers

BOOL CFrame::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	BOOL flag;

	flag = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);

	return flag;
}

void CFrame::OnDeltaposSpinSpeed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
    int Delta = pNMUpDown->iDelta;
	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if(Delta > 0)
	{
		//down
		pMainFrame->PlaySpeed(DOWN);
	}else
	{
		//up
		pMainFrame->PlaySpeed(UP);
	}
	*pResult = 0;
}

void CFrame::OnSelchangeListAnimgroup() 
{
	// TODO: Add your control notification handler code here
	CListBox *pBox = (CListBox*)this->GetDlgItem(IDC_LIST_ANIMGROUP);
	int i = pBox->GetCurSel();

	CString str;
	str.GetBuffer(20);
	
	pBox->GetText(i, str);

	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->ListBoxChange(i, str);
}

void CFrame::OnDblclkListAnimgroup() 
{
	// TODO: Add your control notification handler code here
//	AfxMessageBox("DB");	
	CMainFrame *pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->ChangeGroupName();
}
