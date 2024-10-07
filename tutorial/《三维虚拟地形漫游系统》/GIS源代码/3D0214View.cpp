// 3D0214View.cpp : implementation of the CMy3D0214View class
//

#include "stdafx.h"
#include "3D0214.h"

#include "3D0214Doc.h"
#include "3D0214View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3D0214View

IMPLEMENT_DYNCREATE(CMy3D0214View, CFormView)

BEGIN_MESSAGE_MAP(CMy3D0214View, CFormView)
	//{{AFX_MSG_MAP(CMy3D0214View)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_EXPORT_MAP, OnFileExportMap)
	ON_COMMAND(ID_ADD_DEM_TO_SCENE, OnAddDemToScene)
	ON_COMMAND(ID_CREATE_RASTER_IDW, OnCreateRasterIdw)
	ON_COMMAND(ID_CREATEDEM_TIN, OnCreatedemTin)
	ON_COMMAND(ID_SET_SCENE, OnSetScene)
	ON_COMMAND(ID_SET_BASEHEIGHT, OnSetBaseheight)
	ON_COMMAND(ID_ADDLAYER, OnAddlayer)
	ON_COMMAND(ID_CLASSBREAKRENDERER, OnClassbreakrenderer)
	ON_COMMAND(ID_INFORMATION_QUERY, OnInformationQuery)
	ON_UPDATE_COMMAND_UI(ID_INFORMATION_QUERY, OnUpdateInformationQuery)
	ON_COMMAND(ID_CREATE_SLOP, OnCreateSlop)
	ON_COMMAND(ID_VIEWSHED, OnViewshed)
	ON_COMMAND(ID_LINEOFSIGHTPROFILE, OnLineofsightprofile)
	ON_UPDATE_COMMAND_UI(ID_LINEOFSIGHTPROFILE, OnUpdateLineofsightprofile)
	ON_COMMAND(ID_CREATE_CONTOUR, OnCreateContour)
	ON_COMMAND(ID_SELECTFEATRUES, OnSelectfeatrues)
	ON_UPDATE_COMMAND_UI(ID_SELECTFEATRUES, OnUpdateSelectfeatrues)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DEMO,CMy3D0214View::OnUpdateIndicatorDEMO)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_AUTHOR,CMy3D0214View::OnUpdateIndicatorAUTHOR)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3D0214View construction/destruction

CMy3D0214View::CMy3D0214View()
	: CFormView(CMy3D0214View::IDD)
{
	//{{AFX_DATA_INIT(CMy3D0214View)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	tbrIsstarted=0;
	m_Qcheckstate=0;
	m_Pcheckstate=0;
	m_Scheckstate=0;
	m_pInfoQueryDlg=NULL;
}

CMy3D0214View::~CMy3D0214View()
{
}

void CMy3D0214View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy3D0214View)
	DDX_Control(pDX, IDC_SCENECONTROL1, m_Scontrol);
	//}}AFX_DATA_MAP
}

BOOL CMy3D0214View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMy3D0214View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	///�������뿪ʼ
	CWnd *pWndCal=GetDlgItem(IDC_SCENECONTROL1);
	LPUNKNOWN pUnk=pWndCal->GetControlUnknown();
	//��ȡIScenePtr�ؼ��ӿ�
	pUnk->QueryInterface(IID_ISceneControl,(LPVOID *)&m_ipSceneControl);
	m_ipSceneControl->get_Scene(&m_ipScene);    //��SceneCpntrol�õ�Scene
	m_ipScene->get_Layer (2,&m_ipLayer);
	
//	m_ipSceneGrap->get_Scene(&m_ipScene);//Scene�õ�SceneGrap
//	m_ipSceneGrap->SetBackgroundColor(1.0,0.0,1.0);
	//�����������
	LoadData();
}
/////////////////////////////////////////////////////////////////////////////
// CMy3D0214View printing

BOOL CMy3D0214View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy3D0214View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy3D0214View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMy3D0214View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CMy3D0214View diagnostics

#ifdef _DEBUG
void CMy3D0214View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy3D0214View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy3D0214Doc* CMy3D0214View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3D0214Doc)));
	return (CMy3D0214Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3D0214View message handlers

void CMy3D0214View::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
    CWnd *  Control=GetDlgItem(IDC_SCENECONTROL1);
    CRect  Controlrect;
	if(Control)
	{
		 Control->GetWindowRect(&Controlrect);
		 Control->MoveWindow(0,0,cx,cy);
	}
}

void CMy3D0214View::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	::OleInitialize(NULL);//���������ʼ��  
 
	if(!tbrIsstarted)
	{
	tbrIsstarted=1;
    UpdateData(TRUE);
	CMainFrame *pFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;//��ȡ�����ָ��
	LPUNKNOWN pUnk = m_Scontrol.GetControlUnknown();
    LPDISPATCH pDisp = 0;
    pUnk->QueryInterface(IID_IDispatch, (void **) &pDisp);	
    
	pFrm->m_tocdlg.m_TocControl.SetBuddyControl(pDisp);
	pFrm->m_tbr.SetBuddyControl(pDisp);
    
	//pFrm->m_tocdlg.m_ipToolbarMenu->SetHook(pDisp);

    pDisp->Release();
	CComBSTR bstrProgID;  
	CComVariant varProgID;  
	varProgID.vt = VT_BSTR;  
	// Add generic commands
	bstrProgID = _T("esri3DAnalyst.ControlsSceneOpenDocCommand");  
	varProgID.bstrVal = bstrProgID;
    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 

	bstrProgID = _T("esri3DAnalyst.ControlsSceneSceneToolbar");  
	varProgID.bstrVal = bstrProgID;
    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 

	
//	bstrProgID = _T("esriControlCommands.ControlsSelectTool");  
//	varProgID.bstrVal = bstrProgID;
 //   pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 

//	bstrProgID = _T("ESRI_Scene.Fly");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//	bstrProgID = _T("ESRI_Scene.ExpandFOV");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//    	bstrProgID = _T("ESRI_Scene.FullExtent");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//		bstrProgID = _T("ESRI_Scene.NarrowFOV");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//		bstrProgID = _T("ESRI_Scene.Navigate");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//		bstrProgID = _T("ESRI_Scene.Pan");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//		bstrProgID = _T("ESRI_Scene.ZoomInOut");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//		bstrProgID = _T("ESRI_Scene.ZoomOut");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//    bstrProgID = _T("ESRI_Scene.ZoomIn");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//	bstrProgID = _T("ESRI_Scene.SelectFeatures");  
//	varProgID.bstrVal = bstrProgID;
 //   pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//	bstrProgID = _T("ESRI_Scene.SetObserver");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//	bstrProgID = _T("ESRI_Scene.TargetCenter");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
//	bstrProgID = _T("ESRI_Scene.TargetZoom");  
//	varProgID.bstrVal = bstrProgID;
//    pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconOnly); 
   
//	bstrProgID = _T("TinBldgBurner.TinBuildingBurner");  
//	varProgID.bstrVal = bstrProgID;
//   pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconAndText); 

	//bstrProgID = _T("prjSceneBackdrop.SceneBackdrop");  
//	varProgID.bstrVal = bstrProgID;
 //   pFrm->m_tbr.AddItem(varProgID, -1, -1, VARIANT_FALSE, 0, esriCommandStyleIconAndText); 

	}
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
void CMy3D0214View::LoadData()
{
	CComBSTR SX_DATAFILE("DATE/Tin.sxd");
	//SX_DATAFILE ="DATE/Tin.sxd";
	VARIANT_BOOL bIsSceneDoc;
	m_ipSceneControl->CheckSxFile(SX_DATAFILE, &bIsSceneDoc);
	if (bIsSceneDoc)
	{
		m_ipSceneControl->LoadSxFile(SX_DATAFILE);
		m_ipSceneControl->get_Scene(&m_ipScene);
		m_ipScene->get_Layer(0,&m_ipLayer);
	}
}

void CMy3D0214View::OnFileExportMap() 
{
	// TODO: Add your command handler code here
	CString strFilter="JPEG File(*.jpg)|*.jpg||";//���ô��ļ��Ĺ�������
		CString strTitle="Export Map";
        DWORD MAXFILE = 2412; // allocate enough memory space
    	CString strPath,strInit,strTemp;
        CFileDialog pDlg(FALSE,".jpg",0,OFN_ALLOWMULTISELECT| OFN_EXPLORER | OFN_LONGNAMES|
                        OFN_FILEMUSTEXIST |OFN_HIDEREADONLY,(LPCTSTR)strFilter, NULL);

        //���öԻ���               
        pDlg.m_ofn.nMaxFile = MAXFILE; // set the buffer size        
        pDlg.m_ofn.lpstrTitle=strTitle;
        pDlg.m_ofn.lpstrInitialDir=strInit;
		char* buf = new char[MAXFILE];
		pDlg.m_ofn.lpstrFile = buf;
		pDlg.m_ofn.lpstrFile[0] = NULL;
		if(pDlg.DoModal()== IDOK)
		{
			POSITION pos = pDlg.GetStartPosition();	
			strPath=pDlg.GetNextPathName(pos);
			AfxMessageBox(strPath);
		}

	ISceneGraphPtr ipSceneGrap(m_Scontrol.GetSceneGraph());
	ISceneViewerPtr  ipViewer;
	ipSceneGrap->get_ActiveViewer(&ipViewer);
	ipViewer->GetScreenShot(JPEG,(CComBSTR)strPath);
}
void CMy3D0214View::OnAddDemToScene() 
{
	// TODO: Add your command handler code here
	::OleInitialize(NULL);//���������ʼ��      
	 IGxDialogPtr ipGxDialog(CLSID_GxDialog);
    //���ù�����ΪSurfaceDatasets
    IGxObjectFilterPtr ipGxObjectFilter(CLSID_GxFilterSurfaceDatasets);
    HRESULT hr = ipGxDialog->putref_ObjectFilter(ipGxObjectFilter);
    if(FAILED(hr)) return;
    hr=ipGxDialog->put_Title( CComBSTR("ѡ��һ��DEM��������"));
    if(FAILED(hr)) return;
	IEnumGxObjectPtr  ipEnumGxObject;
	VARIANT_BOOL bResult;
	hr=ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);
	if(FAILED(hr)) return;
	if(bResult== VARIANT_FALSE) return;
	hr=ipEnumGxObject->Reset();
	if(FAILED(hr)) return;
	IGxObjectPtr ipGxObject;
	ipGxDialog->get_FinalLocation(&ipGxObject);
	while(!ipEnumGxObject->Next(&ipGxObject))
	{   

		IGxDatasetPtr ipGxDataset(ipGxObject);
		if(ipGxDataset!=0) 

		{
			IDatasetPtr ipDataset;
		    hr=ipGxDataset->get_Dataset(&ipDataset);
		    if(FAILED(hr))return;
		    IRasterDatasetPtr ipRasterDataset(ipDataset);
		    if(ipRasterDataset!=NULL)
			{
			CComBSTR bstrName;
			hr=ipRasterDataset->get_CompleteName(&bstrName);
			if(FAILED(hr)) return;
			//����RASTERͼ��
			IRasterLayerPtr pRLayer(CLSID_RasterLayer);
			hr=pRLayer->CreateFromDataset(ipRasterDataset);
			hr=pRLayer->put_Name(CComBSTR("myRaster"));
			m_ipLayer=pRLayer;
			//����RASTERͼ��
			//��ȡISceneGrap�ӿ�ָ��
	        //m_ipSceneGrap=m_Scontrol.GetSceneGraph(); 
			//��ȡIScene�ӿ�ָ��   
			m_ipScene=m_Scontrol.GetScene();  
			hr=m_ipScene->AddLayer(m_ipLayer,VARIANT_TRUE);
			}
			ITinPtr ipTin(ipDataset);		
			if ( ipTin!=NULL)		
			{
				CComBSTR bstrName;			
				hr=ipDataset->get_Name(&bstrName);			
				if(FAILED(hr)) return;			
				//����TINͼ��			
				ITinLayerPtr pTLayer( CLSID_TinLayer);			
				hr=pTLayer->putref_Dataset(ipTin);	
				hr=pTLayer->put_Name(CComBSTR("myTin"));
				m_ipLayer=pTLayer;			
				//����TINͼ��
      		
				m_ipScene=m_Scontrol.GetScene(); 
			//	hr=m_ipSceneGrap->get_Scene(&m_ipScene);			
				hr=m_ipScene->AddLayer(m_ipLayer,VARIANT_TRUE);		
			}	
		}
	}
}

void CMy3D0214View::OnCreateRasterIdw() 
{
	// TODO: Add your command handler code here
	CDlgCreateRasterIDW theDlg;
	if(theDlg.DoModal()==IDOK) 
	{
		return;
	}
}

void CMy3D0214View::OnCreatedemTin() 
{
	// TODO: Add your command handler code here
	CDlgCreateTINfromFeature theDLG;
	if(theDLG.DoModal()==IDOK)
	{

	}
}
bool CMy3D0214View::GetSceneFromView(IScene **ipScene)
{
	 m_ipScene=m_Scontrol.GetScene(); 
      *ipScene = m_ipScene;
      if ( m_ipScene==NULL) return FALSE;
     // (*ipScene)->AddRef();
      return TRUE;
}
void CMy3D0214View::OnSetScene() 
{
	// TODO: Add your command handler code here
	CDlgSetScene theDLG;
	if(theDLG.DoModal()==IDOK)
	{
	}
}

void CMy3D0214View::OnSetBaseheight() 
{
	// TODO: Add your command handler code here
	CDlgBaseHeight theDlg;
	if(theDlg.DoModal()==IDOK) 
	{
	}
}
void CMy3D0214View::OnAddlayer() 
{
	// TODO: Add your command handler code here
	   //�򿪶Ի���
    ::OleInitialize(NULL);//���������ʼ�� 
   	IGxDialogPtr ipGxDialog(CLSID_GxDialog);
	//Set the Filter to FeatureDatasets and FeatureClasses
	IGxObjectFilterPtr ipGxObjectFilter(CLSID_GxFilterFeatureClasses);
	HRESULT hr=ipGxDialog->putref_ObjectFilter(ipGxObjectFilter);
	if(FAILED(hr ))return;

	    hr=ipGxDialog->put_AllowMultiSelect(VARIANT_TRUE);
		if(FAILED(hr))return;
		hr = ipGxDialog->put_Title(CComBSTR("ѡ������"));
		if(FAILED(hr)) return;
		IEnumGxObjectPtr ipEnumGxObject;
		VARIANT_BOOL bResult;

		hr=ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);

		if(FAILED(hr)) return;

		if(bResult== VARIANT_FALSE)return;

		hr= ipEnumGxObject->Reset();

		if(FAILED(hr)) return;

		IGxObjectPtr ipGxObject;

			while(!ipEnumGxObject->Next(&ipGxObject))
			{
				IGxDatasetPtr ipGxDataset(ipGxObject);

				if(ipGxDataset!=0)
				{

					IDatasetPtr ipDataset;				
					hr=ipGxDataset->get_Dataset(&ipDataset);				
					if(FAILED(hr)) return;				
					IFeatureClassPtr ipFeatureClass(ipDataset);				
					IFeatureLayerPtr ipFeatureLayer(CLSID_FeatureLayer);				
					hr=ipFeatureLayer->putref_FeatureClass(ipFeatureClass);
					if(FAILED(hr)) return;
					hr=ipFeatureLayer->put_Visible(VARIANT_FALSE);
					if(FAILED(hr)) return;
					CComBSTR bstrName;
					hr=ipFeatureClass->get_AliasName(&bstrName);
					if(FAILED(hr)) return;
					hr = ipFeatureLayer->put_Name(bstrName);
					if(FAILED(hr )) return;
					hr=ipFeatureLayer->put_Visible(VARIANT_TRUE);
					if(FAILED(hr)) return;
					ILayerPtr m_ipLayer=ipFeatureLayer;
					//hr=m_ipMap->AddLayer( m_ipLayer);

                    m_ipScene=m_Scontrol.GetScene(); 
					//�ӵ���ά����
                     hr=m_ipScene->get_SceneGraph(&m_ipSceneGrap);
					if( FAILED(hr ))return;
					hr=m_ipScene->AddLayer(m_ipLayer,VARIANT_TRUE);
    				if( FAILED(hr ))return;
    				m_ipSceneGrap->RefreshViewers();
				}
			}
}

void CMy3D0214View::OnClassbreakrenderer() 
{
	// TODO: Add your command handler code here
	CDlgClassBreakRenderer theDlg;
     if(theDlg.DoModal()==IDOK)
	{
	}
	
}

BEGIN_EVENTSINK_MAP(CMy3D0214View, CFormView)
    //{{AFX_EVENTSINK_MAP(CMy3D0214View)
	ON_EVENT(CMy3D0214View, IDC_SCENECONTROL1, 1 /* OnMouseDown */, OnOnMouseDownScenecontrol1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CMy3D0214View, IDC_SCENECONTROL1, 3 /* OnMouseMove */, OnOnMouseMoveScenecontrol1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CMy3D0214View, IDC_SCENECONTROL1, 2 /* OnMouseUp */, OnOnMouseUpScenecontrol1, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMy3D0214View::OnInformationQuery() 
{
	// TODO: Add your command handler code here

	 if(!m_Qcheckstate)
    {
		m_Qcheckstate=1;
		m_pInfoQueryDlg=new CDlgInfoQuery(this);
		m_pInfoQueryDlg->Create(IDD_DLG_INFO_QUERY);
		m_pInfoQueryDlg->ShowWindow(SW_SHOW);
 	}
	 else
	{	
		m_Qcheckstate=0;	
		if(m_pInfoQueryDlg!=NULL)	
		{		
			delete m_pInfoQueryDlg;    
		}
	}
}
void CMy3D0214View::OnUpdateInformationQuery(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Qcheckstate);
}

void CMy3D0214View::OnOnMouseDownScenecontrol1(long button, long shift, long x, long y) 
{
	// TODO: Add your control notification handler code here
	HRESULT hr=m_ipScene->get_SceneGraph(&m_ipSceneGrap);//��ȡSceneGraph
    if(m_ipSceneGrap==NULL)
    {
        AfxMessageBox("no scene!");
            return;
    }
    if(m_Qcheckstate==1)
    {
	    m_Scontrol.SetMousePointer(esriPointerCrosshair);	
		//ISceneGraphPtr pSG(m_ipSceneGrap);
		ISceneViewerPtr pViewer;
		m_ipSceneGrap->get_ActiveViewer(&pViewer);
		//�����������
		IPointPtr pPoint;
		IUnknownPtr pOwner;
		IUnknownPtr pObject;
		//��������ʱִ��Locate�������ú�������һ���������3D�㡢
		//��������Ͱ����ö����ͼ��
		m_ipSceneGrap->Locate(pViewer,
			                  x,
							  y,
							  esriScenePickGeography,
							  VARIANT_TRUE,
							  &pPoint,
							  &pOwner,
							  &pObject);

		//������
		if(pPoint==NULL) return;
		//���õ��Ч��
	    m_ipScene=m_Scontrol.GetScene(); //��SceneCpntrol�õ�Scene
		m_ipSceneGrap->get_Scene(&m_ipScene);//Scene�õ�SceneGrap

		IClonePtr ppFlashPoint;
		IClonePtr pClone(pPoint);
		pClone->Clone(&ppFlashPoint);
		IPointPtr pFlashPoint(ppFlashPoint);
		IDisplay3DPtr pDisplay(m_ipSceneGrap);
		pDisplay->FlashLocation(pFlashPoint);
//		double x1,y1,z1;
//		pPoint->get_X(&x1);
//		pPoint->get_Y(&y1);
// 		pPoint->get_Z(&z1);
	//	CString str;
	//	str.Format("(%f,%f)\n Height=%f",x1,y1,z1);
	//	AfxMessageBox(str); 

		pPoint->get_X(&(m_pInfoQueryDlg->m_edit_X));
		pPoint->get_Y(&(m_pInfoQueryDlg->m_edit_Y));
 		pPoint->get_Z(&(m_pInfoQueryDlg->m_edit_Z));
		CString strX,strY,strZ;
		strX.Format("%f",m_pInfoQueryDlg->m_edit_X);
		strY.Format("%f",m_pInfoQueryDlg->m_edit_Y);
		strZ.Format("%f",m_pInfoQueryDlg->m_edit_Z);
		

		m_pInfoQueryDlg->m_control_X.SetWindowText(strX);
		m_pInfoQueryDlg->m_control_Y.SetWindowText(strY);
		m_pInfoQueryDlg->m_control_Z.SetWindowText(strZ);
	}
	else
	{
		m_Scontrol.SetMousePointer(0);
	}
	if(m_Pcheckstate==1)
	{ 
		DoRealGraphWork(x, y);
	}
}
void CMy3D0214View::OnOnMouseMoveScenecontrol1(long button, long shift, long x, long y) 
{
	// TODO: Add your control notification handler code here
	if(m_Qcheckstate==1)
	{
		//�ı������ʽ
		m_Scontrol.SetMousePointer(esriPointerCrosshair);
	}
	else
	{
		m_Scontrol.SetMousePointer(0); 
	}
}

void CMy3D0214View::OnCreateSlop() 
{
	// TODO: Add your command handler code here
	CDlgSlope theDlg;
    if(theDlg.DoModal()==IDOK)
	{
	}
}

void CMy3D0214View::OnViewshed() 
{
	// TODO: Add your command handler code here
	CDlgViewshed theDlg;
	if(theDlg.DoModal()==IDOK)
	{
	}
}

void CMy3D0214View::OnLineofsightprofile() 
{
	// TODO: Add your command handler code here
	 if(!m_Pcheckstate)
    {
		m_Pcheckstate=1;
		m_pDlg=new CDlgProfileGraph(this);
		m_pDlg->Create(IDD_DLG_PROFILE_GRAPH);
		m_pDlg->ShowWindow(SW_SHOW);
 	}
	
	else
	{	
		m_Pcheckstate=0;	
		if(m_pDlg!=NULL)	
		{		
			delete m_pDlg;    
		}
	}
}
void CMy3D0214View::OnUpdateLineofsightprofile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Pcheckstate);
}
CString CMy3D0214View::FindBasename(CString filename)
{
    CString basename;
   int pos=filename.ReverseFind('.');
   if ( pos==-1)return filename; //û��'.' 
   basename=filename.Left(pos);		
   return basename;
}
BOOL CMy3D0214View::DeleteSHP(CString pathname,CString filename)
{	CFileFind finder;
	CString strWildcard(pathname);
    CString basename= FindBasename(filename);
    strWildcard +=_T("\\"+basename+".*");

	BOOL bWorking=finder.FindFile(strWildcard);
	while(bWorking)
	{      
		bWorking=finder.FindNextFile(); 
		
		if(!finder.IsDots())
			if(!finder.IsDirectory())		
			{		
				CString str=finder.GetFilePath();	
				

				CString fileExtension;			
				fileExtension= str.Right(3);			
				if(fileExtension=="shp"||             
					fileExtension=="shx"||			 
					fileExtension=="dbf"||			  
					fileExtension=="sbx"||			   
					fileExtension=="sbn") 
				{
					DeleteFile(str);
				
				}
			 
					
			} 
		
	}
	finder.Close();
	return TRUE;
}
int CMy3D0214View::IsDirectory (CString pathname )//**�ж��ļ����ļ����Ƿ����
{
	DWORD  dwFlag=GetFileAttributes(pathname);
	if( 0xFFFFFFFF==dwFlag)
		return 0 ;//������

	else
	{
		if(FILE_ATTRIBUTE_DIRECTORY&dwFlag)
			return 1;//���ļ���
        else
            return -1; //���ļ�
	}
     
} 
CString CMy3D0214View::GetCurrentDir()
{
    TCHAR cCurDir[100];
    CString strCurDir;
	::GetCurrentDirectory(256,cCurDir);
	strCurDir=cCurDir;
    return strCurDir;
} 
BOOL CMy3D0214View::MakeProfileChart(CString sDir,CString sFileName,CString sGraphTitle,CString sGraphSubTitle)
{
    HRESULT hr;
    //��ָ����featurec}}ss
    IWorkspaceFactoryPtr pFact(CLSID_ShapefileWorkspaceFactory);
    IWorkspacePtr pWorkspace;
    hr=pFact->OpenFromFile((CComBSTR)sDir,NULL,&pWorkspace);
    if(FAILED(hr ))return FALSE; 
	IFeatureWorkspacePtr pFeatws(pWorkspace);
	IFeatureClassPtr pFClass;
	hr= pFeatws->OpenFeatureClass((CComBSTR)sFileName,&pFClass);
	if(FAILED(hr ))return FALSE;
	IFeatureLayerPtr pFLayer(CLSID_FeatureLayer );
	hr= pFLayer->putref_FeatureClass(pFClass);
	//QI table
	ITablePtr pTable(pFLayer);
	if(pTable==NULL){AfxMessageBox("Table QI failed!");return FALSE;}
	//����һ���µ�ͼ�����
	IDataGraphPtr pDataGraph(CLSID_DataGraph);
	if(m_pDlg==NULL)return FALSE;
	if(FAILED(hr=pDataGraph->Attach((OLE_HANDLE)m_pDlg->m_static_ProfileGraph.m_hWnd))) return FALSE;
	//����Ĭ�ϵı��
	hr=pDataGraph->putref_Table(pTable);
	//Ϊdatagraph�����ֶ�
	hr=pDataGraph->put_FieldSet1(CComBSTR("Z"));
	hr=pDataGraph->put_FieldSet2(CComBSTR("M"));
	hr=pDataGraph->put_Name((CComBSTR)sGraphTitle);
	//����datagraph����
	IDataGraphPropertiesPtr pDataGraphProp(pDataGraph);
	//��ͼ����������Ϊ��ά����
	hr=pDataGraphProp->put_GraphType(esriDataGraphTypeLine);
	hr=pDataGraphProp->put_GraphSubtype(esriDataGraphSubtypeLine2DSimple);
	hr=pDataGraphProp->put_ShowXAxisLabels(VARIANT_TRUE);
	hr=pDataGraphProp->put_ShowLegend(VARIANT_FALSE);
	hr=pDataGraphProp->put_Title(CComBSTR(sGraphTitle));
	hr=pDataGraphProp->put_SubTitle((CComBSTR)sGraphSubTitle);
    hr=pDataGraph->Reload();
    hr=pDataGraph->Draw();
    hr=pDataGraph->Detach();//�ͷ�
    return TRUE;
} 
void CMy3D0214View::DoRealGraphWork(long xPos,long yPos)
{
	HRESULT hr;
	m_ipScene=m_Scontrol.GetScene(); //��SceneCpntrol�õ�Scene
	hr=m_ipSceneGrap->get_Scene(&m_ipScene);//Scene�õ�SceneGrap
	
    ISceneGraphPtr pSG(m_ipSceneGrap);
	ISceneViewerPtr pViewer;
	m_ipSceneGrap->get_ActiveViewer(&pViewer);//SceneGrape�õ�SceneViewer

	IPointPtr pPnt;
	IUnknownPtr pOwner;
	IUnknownPtr pObject;
	hr=pSG->Locate(pViewer,xPos,yPos,
                    esriScenePickAll,
                    VARIANT_TRUE,
                    &pPnt,
                    &pOwner,
                    &pObject);
	if(FAILED(hr )){AfxMessageBox("Famed");return;}
	if(pPnt==NULL){return;}
    if(pOwner!= m_ipLayer){AfxMessageBox("WRONG LAYER!");return;}
	IClonePtr ppFlashPoint;
	IClonePtr pClone(pPnt);
	pClone->Clone(&ppFlashPoint);

	IPointPtr pFlashPoint( ppFlashPoint);

	//��������ϵ��Ӱ��
	//pFlashPoint. Z=pFlashPoint. Z/pSG. VerticalExaggetion

	ISpatialReferencePtr ipSR;
	m_ipScene->get_SpatialReference(&ipSR);
	pFlashPoint->putref_SpatialReference(ipSR);
	//���õ��Ч��
	IDisplay3DPtr pDisplay(pSG);
	pDisplay->FlashLocation(pFlashPoint);
	if(m_pScenePoints==NULL)
	{
		 m_pScenePoints. CreateInstance(CLSID_Polyline);
		 IGeometryPtr pGeom(m_pScenePoints);    
		 pGeom->putref_SpatialReference(ipSR);
	}

	 m_pScenePoints->AddPoint(pPnt);
	 long pcount;
	 m_pScenePoints->get_PointCount(&pcount);

	 IPolylinePtr pPolyline;
	 IClonePtr pCPolyline;
	 if(pcount==2)
	 {    
		pClone=m_pScenePoints;    
		pClone->Clone(&pCPolyline);    
		pPolyline=pCPolyline;
	 }
	 if(pPolyline!=NULL)
	 {		
			//׼������ͼ				 
			ISurfacePtr m_ipSurface;				 
			IRasterLayerPtr ipRLayer(m_ipLayer);				 
			ITinLayerPtr ipTLayer( m_ipLayer);
			if(ipRLayer==NULL&&ipTLayer==NULL){AfxMessageBox( "Ͷ�б�������!");return;}
			if(ipRLayer!=NULL)
			{
		
				IRasterPtr ipRaster;    
				IRasterBandPtr pRasterBand;
				hr=ipRLayer->get_Raster( &ipRaster);   
				if(FAILED(hr))   return;
				IRasterBandCollectionPtr pRasterBands(ipRaster);
				hr = pRasterBands->Item(0,&pRasterBand);    
				if(FAILED(hr ))return;    
				IRasterSurfacePtr pRasterSurface(CLSID_RasterSurface);    
				hr=pRasterSurface->put_RasterBand(pRasterBand);
				if(FAILED(hr )) return;    
				m_ipSurface=pRasterSurface;
			}

			if(ipTLayer!=NULL)
			{   
					ITinPtr ipT;   
					hr=ipTLayer->get_Dataset(&ipT);    
					m_ipSurface = ipT;
			}
				 

			IGeometryPtr pInshape(pPolyline);
			IGeometryPtr pOutshape;
			hr=m_ipSurface->InterpolateShape(pInshape,&pOutshape);
			//��2άͼ�β��뵽3ά����
			if(FAILED(hr)) return;   

			//��ʾ
			IElementPtr pElem(CLSID_LineElement);
			//ʹ��IElement�ӿ�����LineElement�ļ���ͼ�Ρ�
			hr=pElem->put_Geometry(pOutshape);
			//ʹ��ILineElement�ӿ�����Symbol����
			ILineElementPtr pElemLine(pElem);
			//����һ��RGB��ɫ
			IRgbColorPtr pRGB(CLSID_RgbColor);
			pRGB->put_Red(100);pRGB->put_Green(0);pRGB->put_Blue(100);
			//����һ��SimpleLineSymbol,����������ɫ����ʽ
			ISimpleLineSymbolPtr pSLnSym(CLSID_SimpleLineSymbol);
			pSLnSym->put_Color(pRGB);
			pSLnSym->put_Style(esriSLSSolid);
			pElemLine->put_Symbol(pSLnSym);

			IGraphicsLayerPtr pGLayer;
			hr=m_ipScene->get_BasicGraphicsLayer( &pGLayer);
			IGraphicsContainer3DPtr pGCon3D(pGLayer);
			hr=pGCon3D->AddElement((IElementPtr) pElemLine);
			IGraphicsSelectionPtr pGS(pGCon3D);
		
			hr=pGS->UnselectAllElements();
		 	hr=pGS->SelectElement((IElementPtr) pElemLine);
			m_ipSceneGrap->RefreshViewers();

			//��������ͼ

			IPointCollectionPtr pPointZGeom(pOutshape);
			if(pPointZGeom==NULL ){AfxMessageBox("No geometry found.");return;}
			IMAwarePtr pMA(pPointZGeom);//M ���Բ����ӿ�
			hr=pMA->put_MAware(VARIANT_TRUE);
			if(FAILED(hr))return;
			IZAwarePtr pZA(pPointZGeom);//Z ���Բ����ӿ�
			hr=pZA->put_ZAware(VARIANT_TRUE);
			if(FAILED(hr ))return;
			IMSegmentationPtr pMSeg(pPointZGeom);
			//IMSegmentation: access to members for defining an M-based linear
			//coordinate system on a polyline or polygon

			//���봢����M������
		    if(FAILED(pMSeg->SetMsAsDistance(VARIANT_FALSE)))return;
			//Sets the M values to the cumulative length from the origin of the geometry
			IEnvelopePtr pEnv;
			if(FAILED(pOutshape->get_Envelope(&pEnv)))return;
			double xmin;
			hr=pEnv->get_XMin(&xmin);
			ISpatialReferencePtr pSR(CLSID_UnknownCoordinateSystem);
			
			//׼������shapefile
			CString sDir=GetCurrentDir();
			IWorkspaceFactoryPtr shapeWorkspaceFactory(CLSID_ShapefileWorkspaceFactory);
         	IPropertySetPtr connectionProperties(CLSID_PropertySet);
			CString Name="DATABASE";
			CComBSTR bstr( sDir);
			CComVariant pValue(bstr);
			if(FAILED(connectionProperties->SetProperty(( CComBSTR)Name,pValue)))return;
			CString sFileName="Profile";
			IWorkspacePtr pshapeWorkspace;
			hr=shapeWorkspaceFactory->Open(connectionProperties,
                                                        NULL,
                                                        &pshapeWorkspace);

			IFeatureWorkspacePtr shapeWorkspace(pshapeWorkspace);
			if(shapeWorkspace!=NULL)
			{
					IFeatureClassPtr pFeatCls;
					IFeatureBufferPtr pBuffer;
					IFeatureCursorPtr pCursor;
					//���������ֶ�
					IFieldsPtr pFlds(CLSID_Fields);
					IFieldsEditPtr pFldsEdt(pFlds);
					IFieldPtr pFld(CLSID_Field);
					IFieldEditPtr pFldEdt(pFld);
					IGeometryDefEditPtr pGeoDef(CLSID_GeometryDef);
					hr=pGeoDef->put_GeometryType(esriGeometryPoint);
					hr=pGeoDef->put_HasM(VARIANT_TRUE);
					hr=pGeoDef->put_HasZ(VARIANT_TRUE);
					hr=pGeoDef->putref_SpatialReference(pSR);
					//���oid�ֶ�
					hr=pFldEdt.CreateInstance(CLSID_Field);
					hr=pFldEdt->put_Name(( CComBSTR)("OID"));
					hr=pFldEdt->put_Type(esriFieldTypeOID);
					hr=pFldsEdt->AddField(pFldEdt);
					//���Geometry�ֶ�
					hr=pFldEdt.CreateInstance(CLSID_Field);
					hr=pFldEdt->put_Name(CComBSTR("Shape"));
					hr=pFldEdt->put_IsNullable(VARIANT_TRUE);
					hr=pFldEdt->put_Type(esriFieldTypeGeometry);
					hr=pFldEdt->putref_GeometryDef(pGeoDef);
					hr=pFldsEdt->AddField(pFldEdt);
 					//��ʼ����shapefile
				
                	if(IsDirectory(sDir+"\\"+sFileName+".shp")==-1)
					{
						if(!DeleteSHP(sDir,sFileName))	return;
					}
					hr=shapeWorkspace->CreateFeatureClass(
                                        (CComBSTR)(sFileName),
                                         pFldsEdt,
                                         NULL,
                                         NULL,
                                         esriFTSimple,
                                         CComBSTR("Shape"),
                                         CComBSTR(""),
                                          &pFeatCls);

					if(FAILED(hr)){AfxMessageBox("������ʱshpʧ��!");   return;}
 
					//��������ֶ�:M��Z		

					IFieldEditPtr pFieldEdit(CLSID_Field);
					hr=pFieldEdit->put_Name((CComBSTR)("M"));
					hr=pFieldEdit->put_IsNullable(VARIANT_TRUE);
					hr=pFieldEdit->put_Type(esriFieldTypeDouble);
					hr=pFieldEdit->put_Length(8);
					IFieldPtr pField(pFieldEdit);
					hr=pFeatCls->AddField(pField);
					hr=pFieldEdit.CreateInstance(CLSID_Field);
					hr=pFieldEdit->put_Name((CComBSTR)("Z"));
					hr=pFieldEdit->put_IsNullable(VARIANT_TRUE);
					hr=pFieldEdit->put_Type(esriFieldTypeDouble);
					hr=pFieldEdit->put_Length(8);
					pField=pFieldEdit;
					hr=pFeatCls->AddField(pField);					
 					//��ӵ�Ҫ��
					hr=pFeatCls->Insert(VARIANT_TRUE,&pCursor);				 
					hr=pFeatCls->CreateFeatureBuffer(&pBuffer); 				 
					long j;long count;
					pPointZGeom->get_PointCount(&count);
					for(j=0;j<count;j++)
					{   
						IPointPtr pPoint;    
						hr =pPointZGeom->get_Point(j,&pPoint);    
						IGeometryPtr pGeo(pPoint);    
						hr=pBuffer->putref_Shape(pGeo);    
						double pM,pZ;    
						hr=pPoint->get_M(&pM);    
						hr=pPoint->get_Z(&pZ);     	                  
						VARIANT tempM;    
						tempM.vt=VT_R8;    
						tempM.dblVal=pM;    
						VARIANT tempZ;    
						tempZ.vt=VT_R8;    
						tempZ.dblVal=pZ;    
						hr=pBuffer->put_Value(3,tempM);    
						hr=pBuffer->put_Value(4,tempZ); 
						CComVariant ret ;

						hr=pCursor->InsertFeature(pBuffer,&ret);//���в���ΪNULL,���ܱ���
						//��Ҫ�ؼ��뵽Ҫ�ؼ��Ļ����У������е�Ҫ�ض���ɻ���д�룬
						//����� FLUSHһ��д�����ݿ���ļ�,�������д���ٶ�
						if (FAILED(hr))     
						{  AfxMessageBox("Couldn't insert feature\n");  return ; }						
					}
                 	 hr= pCursor->Flush();//�������е�����д��
					 pFeatCls=NULL;

				}
					shapeWorkspaceFactory=NULL;

					pshapeWorkspace=NULL;

					shapeWorkspace=NULL;

					CString graphTitle="Elevation-Profile";

					CString graphSubTitle="ZvsM";

					//**��������ͼ
					MakeProfileChart(sDir,sFileName,graphTitle,graphSubTitle);
					if(IsDirectory(sDir+CString("\\")+sFileName+CString(".shp"))==-1) 
					{
    
						if(!DeleteSHP(sDir,sFileName)) return;
                         
						m_pScenePoints=NULL;
            
					}
			}
					
		

				
}
void CMy3D0214View::OnCreateContour() 
{
	// TODO: Add your command handler code here
	CDlgCreateContour theDlg;
	if(theDlg.DoModal()== IDOK)
	{
	}
	
}
void CMy3D0214View::OnUpdateIndicatorDEMO(CCmdUI *pCCmdUI)
{
	//pCCmdUI->Enable(TRUE);
	pCCmdUI->SetRadio(TRUE);
	pCCmdUI->SetText("   Hunan University Of Science and Technology   ");

}
void CMy3D0214View::OnUpdateIndicatorAUTHOR(CCmdUI *pCCmdUI)
{
	//pCCmdUI->Enable(TRUE);
	pCCmdUI->SetRadio(TRUE);
	pCCmdUI->SetText(" Author:���ǻ�");

}

void CMy3D0214View::OnSelectfeatrues() 
{
	// TODO: Add your command handler code here
	if(!m_Scheckstate)
		m_Scheckstate=1;
	else
		m_Scheckstate=0;
}

void CMy3D0214View::OnUpdateSelectfeatrues(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_Scheckstate);
}

void CMy3D0214View::OnOnMouseUpScenecontrol1(long button, long shift, long x, long y) 
{
	// TODO: Add your control notification handler code here
	if(m_Scheckstate)
	{
		//��ȡIScene�ӿ�ָ��   
		m_ipScene=m_Scontrol.GetScene();
		
		IElementPtr ipElement;
		IElementPtr selElmt;
		
		IPointPtr ipPoint;
		IUnknownPtr ipOwner;
		IUnknownPtr ipObject;
		
//		selElmt = SelectElement(m_ipScene, x, y);
//		selElmt->get_Geometry()
//
//		IMarker3DSymbol m_ipMS;
//		
//		IMarkerElementPtr pME;
//    Set Posation = selElmt.Geometry  '  pMks.Shape
//    Set pME = selElmt
//    Set pMS = pME.Symbol
//    Dim pMP As IMarker3DPlacement
//    Set pMP = pMS
//    Dim outGem As IGeometry
//    pMP.ApplyToPoint Posation, outGem
//    Set selMP = outGem
//    
//     Dim pElemProps As IElementProperties: Set pElemProps = selElmt
//     
//    MsgBox pElemProps.Name
//    Debug.Print outGem.Envelope.zmax - outGem.Envelope.zmin
	}
}
