// NameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Triangle.h"
#include "NameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NameDlg dialog


NameDlg::NameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(NameDlg)
	m_sName = _T("");
	//}}AFX_DATA_INIT
}


void NameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NameDlg)
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDV_MaxChars(pDX, m_sName, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NameDlg, CDialog)
	//{{AFX_MSG_MAP(NameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NameDlg message handlers
