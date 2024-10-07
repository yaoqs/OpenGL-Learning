// DlgInfoQuery.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgInfoQuery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoQuery dialog


CDlgInfoQuery::CDlgInfoQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoQuery)
	m_edit_X = 0.0;
	m_edit_Y = 0.0;
	m_edit_Z = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgInfoQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoQuery)
	DDX_Control(pDX, IDC_EDIT_Z, m_control_Z);
	DDX_Control(pDX, IDC_EDIT_Y, m_control_Y);
	DDX_Control(pDX, IDC_EDIT_X, m_control_X);
	DDX_Text(pDX, IDC_EDIT_X, m_edit_X);
	DDX_Text(pDX, IDC_EDIT_Y, m_edit_Y);
	DDX_Text(pDX, IDC_EDIT_Z, m_edit_Z);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoQuery, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoQuery message handlers

BOOL CDlgInfoQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
