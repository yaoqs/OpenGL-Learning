// Skeleten.cpp : implementation file
#include "stdafx.h"
#include "Triangle.h"
#include "Skeleten.h"
#include "MainFrm.h"
#include "body.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CSkeleten dialog
CSkeleten::CSkeleten()
{
	//{{AFX_DATA_INIT(CSkeleten)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CSkeleten, CDialogBar)
	//{{AFX_MSG_MAP(CSkeleten)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BODYTYPE, OnDeltaposSpinBodytype)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ORIENTATIONX, OnDeltaposSpinOrientationx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ORIENTATIONY, OnDeltaposSpinOrientationy)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_POSITIONY, OnDeltaposSpinPositiony)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSkeleten message handlers
BOOL CSkeleten::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	BOOL flag;

	flag = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);

	return flag;
}

void CSkeleten::OnDeltaposSpinBodytype(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    int Delta = pNMUpDown->iDelta;

	CMainFrame *pFrame;
	pFrame = (CMainFrame*)AfxGetMainWnd();

	if(Delta > 0)
	{
		pFrame->SpinScroll(IDC_SPIN_BODYTYPE, UP);
	}else
	{
		pFrame->SpinScroll(IDC_SPIN_BODYTYPE, DOWN);
	}
	*pResult = 0;
}

void CSkeleten::OnDeltaposSpinOrientationx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    int Delta = pNMUpDown->iDelta;

	CMainFrame *pFrame;
	pFrame = (CMainFrame*)AfxGetMainWnd();

	if(Delta > 0)
	{
		pFrame->SpinScroll(IDC_SPIN_ORIENTATIONX, UP);
	}else
	{
		pFrame->SpinScroll(IDC_SPIN_ORIENTATIONX, DOWN);
	}	
	*pResult = 0;
}

void CSkeleten::OnDeltaposSpinOrientationy(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    int Delta = pNMUpDown->iDelta;

	CMainFrame *pFrame;
	pFrame = (CMainFrame*)AfxGetMainWnd();

	if(Delta > 0)
	{
		pFrame->SpinScroll(IDC_SPIN_ORIENTATIONY, UP);
	}else
	{
		pFrame->SpinScroll(IDC_SPIN_ORIENTATIONY, DOWN);
	}		
	*pResult = 0;
}

void CSkeleten::OnDeltaposSpinPositiony(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    int Delta = pNMUpDown->iDelta;

	CMainFrame *pFrame;
	pFrame = (CMainFrame*)AfxGetMainWnd();

	if(Delta > 0)
	{
		pFrame->SpinScroll(IDC_SPIN_POSITIONY, UP);
	}else
	{
		pFrame->SpinScroll(IDC_SPIN_POSITIONY, DOWN);
	}			
	*pResult = 0;
}
