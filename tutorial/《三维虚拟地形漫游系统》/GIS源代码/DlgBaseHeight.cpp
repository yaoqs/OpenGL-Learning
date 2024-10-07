// DlgBaseHeight.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgBaseHeight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBaseHeight dialog


CDlgBaseHeight::CDlgBaseHeight(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBaseHeight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBaseHeight)
	//}}AFX_DATA_INIT
}


void CDlgBaseHeight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBaseHeight)
	DDX_Control(pDX, IDC_COMBO_LAYERS, m_combo_layers);
	DDX_Control(pDX, IDC_COMBO_CURRENT_LAYER, m_combo_currentlayer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBaseHeight, CDialog)
	//{{AFX_MSG_MAP(CDlgBaseHeight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBaseHeight message handlers

BOOL CDlgBaseHeight::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��������Ҫע�⣺����Conbo box �ؼ������Ե� Sort ������ѡ
	//������ѡ��Ķ�Ҫ��
	m_combo_layers.ResetContent();
	//���Scene
	HRESULT hr;
	CMainFrame *pFrame=(CMainFrame*)AfxGetMainWnd();//��������ָ��
	CMy3D0214View *pView=(CMy3D0214View*)pFrame->GetActiveView();//����ͼָ��
	
	
	if(!pView->GetSceneFromView(&m_ipScene))
	{
		AfxMessageBox("���ܵõ�Scene");
		return false;
	}	
 

	//Ϊcombo box�����

	long layercount;

	m_ipScene->get_LayerCount(&layercount);

	ILayerPtr ipLayer;

	CComBSTR layername;

	for(int i=0;i<layercount;i++)
	{
	    

		m_ipScene->get_Layer(i,&ipLayer);
	
		hr=ipLayer->get_Name(&layername);
		 

 		m_combo_layers.AddString((CString)layername);
		m_combo_layers.SetItemDataPtr(i,ipLayer);

		m_combo_currentlayer.AddString((CString)layername);
		m_combo_currentlayer.SetItemDataPtr(i,ipLayer);
	}
	//����como boxĬ��ѡ����
	//	m_combo_currentlayer.SetCurSel(0);
	//	m_combo_layers.SetCurSel(0);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBaseHeight::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_ipScene) SetBaseHeight();
	CDialog::OnOK();
}
void CDlgBaseHeight::SetBaseHeight()
{
	::OleInitialize(FALSE);//���������ʼ��
	 HRESULT hr;
	 int index=m_combo_currentlayer.GetCurSel();
	 
	 ILayerPtr pCurrentLyer=(ILayer*)m_combo_currentlayer.GetItemDataPtr(index);
	 
	 index=m_combo_layers.GetCurSel();
     ILayerPtr ppbasehLyer=(ILayer*) m_combo_layers.GetItemDataPtr(index);	 
	 
	 //Raster���� 
	 IRasterSurfacePtr pRSurface(CLSID_RasterSurface);
	 IRasterLayerPtr prbasehLyer( ppbasehLyer);
	 ISurfacePtr pSurface;     
	 if(prbasehLyer!=NULL)
	 {
       
		 IRasterPtr ipR;    
		 prbasehLyer->get_Raster(&ipR);    
		 IRasterBandCollectionPtr pRasterBands(ipR);    
		 IRasterBandPtr pRasterBand;   
		 pRasterBands->Item(0,&pRasterBand);   
		 pRSurface->put_RasterBand(pRasterBand);    
		 pSurface=pRSurface;
	 }
	 //Tin����
	 ITinLayerPtr pTbasehLyer(ppbasehLyer);
	 ITinPtr ipT;
	 if(pTbasehLyer!=NULL)
	 {            
		 pTbasehLyer->get_Dataset(&ipT);    
		 pSurface=ipT;
	 }
	 I3DPropertiesPtr pDDD;
	 //�õ�pDDD
//	AfxMessageBox("���ܵõ�1");
	 ILayerExtensionsPtr pLayerExts( pCurrentLyer) ;
 	
	 //(pCurrentLyer);
	 //��Extension�����ά����;
	 //������ά��ʾ�Ĺؼ�
	 long count=1;
 	  hr=pLayerExts->get_ExtensionCount(&count);
	 if(FAILED(hr))  AfxMessageBox("���ܵõ�2");;
  	 //AfxMessageBox("���ܵõ�2");;
	 IUnknownPtr p3DProps;

	 for(long i=0;i<count;i++)
	 {
		 pLayerExts->get_Extension(i,&p3DProps);
		 if(p3DProps!= NULL)
		 {
			 pDDD=p3DProps;
			 break;
		 }
	 }
		 pDDD->put_BaseOption(esriBaseSurface);
		 hr=pDDD->putref_BaseSurface(pSurface);
		 if(FAILED(hr)) return;
		 hr=pDDD->Apply3DProperties(pCurrentLyer);
		 ISceneGraphPtr ipSceneGrap;
		 m_ipScene->get_SceneGraph(&ipSceneGrap);
		 ipSceneGrap->RefreshViewers();
}
 
