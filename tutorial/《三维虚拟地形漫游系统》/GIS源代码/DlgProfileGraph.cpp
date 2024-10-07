// DlgProfileGraph.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgProfileGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProfileGraph dialog


CDlgProfileGraph::CDlgProfileGraph(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProfileGraph::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProfileGraph)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgProfileGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProfileGraph)
	DDX_Control(pDX, IDC_STATIC_PROFILE_GRAPH, m_static_ProfileGraph);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProfileGraph, CDialog)
	//{{AFX_MSG_MAP(CDlgProfileGraph)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProfileGraph message handlers

BOOL CDlgProfileGraph::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProfileGraph::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}