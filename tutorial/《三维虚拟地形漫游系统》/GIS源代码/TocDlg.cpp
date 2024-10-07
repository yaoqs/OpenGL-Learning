// TocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "TocDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTocDlg dialog


CTocDlg::CTocDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTocDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTocDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTocDlg)
	DDX_Control(pDX, IDC_TOCCONTROL1, m_TocControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTocDlg, CDialog)
	//{{AFX_MSG_MAP(CTocDlg)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTocDlg message handlers

void CTocDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	CWnd * tocControl=GetDlgItem(IDC_TOCCONTROL1);
	CRect tocControlrect;
	if(tocControl)
	{	
		tocControl->GetWindowRect(&tocControlrect);
		tocControl->MoveWindow(0,0,cx,cy);
	}
}

BOOL CTocDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	CComBSTR bstrProgID;
//    CComVariant varProgID;  
//	varProgID.vt = VT_BSTR;
//	//����ָ��ʵ����
//	m_ipToolbarMenu.CreateInstance(CLSID_ToolbarMenu);
//	//��Ӳ˵���Ŀ
//	bstrProgID = _T("C0214.DelLayer.1");//���ɾ����ť
//	varProgID.bstrVal = bstrProgID;
//	m_ipToolbarMenu->AddItem(varProgID, -1, -1, VARIANT_FALSE, esriCommandStyleIconAndText, 0);
//	bstrProgID = _T("C0214.UpLayer.1"); //������ư�ť
//	varProgID.bstrVal = bstrProgID;
//	m_ipToolbarMenu->AddItem(varProgID, -1, -1, VARIANT_FALSE, esriCommandStyleIconAndText, 0);
//	bstrProgID = _T("C0214.DownLayer.1");//������ư�ť
//	varProgID.bstrVal = bstrProgID;
//	m_ipToolbarMenu->AddItem(varProgID, -1, -1, VARIANT_FALSE, esriCommandStyleIconAndText, 0); 
//  
//	m_ipToolbarMenu->get_CommandPool(&m_CmdPool);
//
//    m_CmdPool->get_Command(0,&m_DelCmd);//��ȡɾ��ICommandʵ��
//    ipDl=m_DelCmd;//��ѯɾ�� IPutLayerName �ӿ�
//    m_CmdPool->get_Command(1,&m_DelCmd);//��ȡ����ICommandʵ��
//    ipUl=m_DelCmd;//��ѯ���� IPutLayerName �ӿ�
//    m_CmdPool->get_Command(2,&m_DelCmd);//��ȡ����ICommandʵ��
//    ipNl=m_DelCmd;//��ѯ���� IPutLayerName �ӿ�

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CTocDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	
	
	return 0;
}

BEGIN_EVENTSINK_MAP(CTocDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTocDlg)
	ON_EVENT(CTocDlg, IDC_TOCCONTROL1, 1 /* OnMouseDown */, OnOnMouseDownToccontrol1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTocDlg::OnOnMouseDownToccontrol1(long button, long shift, long x, long y) 
{
	// TODO: Add your control notification handler code here
//	ILayerPtr ipLayer; 
//    IUnknownPtr ipUn1;
//    IUnknownPtr ipUn2;
//    IUnknownPtr ipUn3;
// 	VARIANT vd;
//    long lt;BSTR bName;
//	m_TocControl.HitTest(x,y,&lt,&ipUn1,&ipUn2,&ipUn3,&vd);//��ȡ�����TOCControl �ϵ������Ŀ��Ϣ
//	if(lt==2)// ��ĿΪ2ʱ�ǵ����ͼ��
//	{
//	
//		ipLayer=ipUn2;//ipUn1�Ƿ��ص����ͼ��� IUnknown �ӿ�ʵ����ͨ����ѯ�õ�ͼ��ӿ�ʵ��      
//		ipLayer->get_Name(&bName);//��ȡͼ����      
//    	ipDl->PutName(bName);//��ͼ�������ݸ�����ť���󣬵��û����Ҽ���ѡ����Ӧ����ʱ��ϵͳ��
//        ipUl->PutName(bName);//���������Ӧͼ����в�����
//        ipNl->PutName(bName);
//		if (button ==2 ) 
//			m_ipToolbarMenu->PopupMenu(x, y,(long)this->GetSafeHwnd());
//		
//	}
//	else
//	{
//		bName=::SysAllocString(L"");
//        ipDl->PutName(bName);
//	} 
	
}
