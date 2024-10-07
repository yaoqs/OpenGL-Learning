// DlgViewshed.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgViewshed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgViewshed dialog


CDlgViewshed::CDlgViewshed(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewshed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgViewshed)
	m_edit_viewshedSurfaceinput = _T("");
	m_edit_viewshedRasteroutput = _T("");
	m_edit_viewshedCellsize = 0.0;
	m_edit_viewshedobserverpoints = _T("");
	//}}AFX_DATA_INIT
}


void CDlgViewshed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgViewshed)
	DDX_Text(pDX, IDC_EDIT_VIEWSHED_SURFACEINPUT, m_edit_viewshedSurfaceinput);
	DDX_Text(pDX, IDC_EDIT_VIEWSHED_RASTEROUTPUT, m_edit_viewshedRasteroutput);
	DDX_Text(pDX, IDC_EDIT_VIEWSHED_CELLSIZE, m_edit_viewshedCellsize);
	DDX_Text(pDX, IDC_EDIT_VIEWSHED_OBSERVERPOINTS, m_edit_viewshedobserverpoints);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgViewshed, CDialog)
	//{{AFX_MSG_MAP(CDlgViewshed)
	ON_BN_CLICKED(IDC_BUTTON_VIEWSHED_OBSERVERPOINTS, OnButtonViewshedObserverpoints)
	ON_BN_CLICKED(IDC_BUTTON_VIEWSHED_RASTEROUTPUT, OnButtonViewshedRasteroutput)
	ON_BN_CLICKED(IDC_BUTTON_VIEWSHED_SURFACEINPUT, OnButtonViewshedSurfaceinput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgViewshed message handlers

void CDlgViewshed::OnButtonViewshedObserverpoints() 
{
	// TODO: Add your control notification handler code here
	//�򿪶Ի���         
	IGxDialogPtr ipGxDialog(CLSID_GxDialog);         
	IGxObjectFilterPtr ipGxObjectFiiter( CLSID_GxFilterPointFeatureClasses);
    //ע��:����ʹ����GxFilterPointFeatureClasses ,
    //���Թ��˵������������㹦��ֻ�õ��ڲ����Ҫ          
	HRESULT hr=ipGxDialog->putref_ObjectFilter(ipGxObjectFiiter);            
	if(FAILED(hr)) return;
    hr=ipGxDialog->put_Title(CComBSTR("ѡ��һ�������ݼ�"));
    if(FAILED(hr))return;
	IEnumGxObjectPtr ipEnumGxObject;
	VARIANT_BOOL bResult;
	hr=ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);
	if(FAILED(hr)) return;
	if(bResult==VARIANT_FALSE)return;
	hr=ipEnumGxObject->Reset();
	if(FAILED(hr)) return;
	IGxObjectPtr ipGxObject;
	while(!ipEnumGxObject->Next(&ipGxObject))
		{		
			IGxDatasetPtr ipGxDataset(ipGxObject);		
			if(ipGxDataset!=0)		
			{   
			IDatasetPtr ipDataset;    
			hr=ipGxDataset->get_Dataset(&ipDataset);    
			if(FAILED(hr))return;    
			IFeatureClassPtr ipFeatureClass(ipDataset);    
			IFeatureLayerPtr ipFeatureLayer( CLSID_FeatureLayer);    
			hr=ipFeatureLayer->putref_FeatureClass(ipFeatureClass);    
			if(FAILED(hr)) return;
			m_ipfeat=ipFeatureClass;
			CComBSTR bstrName; //*} book����������ȫ��
			ipGxObject->get_FullName(&bstrName);
			CString str( bstrName);
			m_edit_viewshedobserverpoints=str;
			UpdateData(FALSE);
			}
		}

	
}

void CDlgViewshed::OnButtonViewshedRasteroutput() 
{
	// TODO: Add your control notification handler code here
	IGxDialogPtr ipGxDialog(CLSID_GxDialog);
    IGxObjectFilterPtr ipGxObjectFilter(CLSID_GxFilterRasterDatasets);
	HRESULT hr=ipGxDialog->putref_ObjectFilter(ipGxObjectFilter);
	if(FAILED(hr))return;
	hr=ipGxDialog->put_Title( CComBSTR("����"));
	if(FAILED(hr)) return;
     VARIANT_BOOL bResult;
	OLE_HANDLE hwnd=(OLE_HANDLE)this->GetSafeHwnd();
	hr=ipGxDialog->DoModalSave(hwnd,&bResult);
	if(FAILED(hr)) return;
	if(bResult==VARIANT_FALSE) return;
	IGxObjectPtr ipGxObject;
	ipGxDialog->get_FinalLocation(&ipGxObject);
	CComBSTR path;
	ipGxObject->get_FullName(&path);
	m_OutputPath=CString(path);
	CComBSTR name;
	ipGxDialog->get_Name(&name);
	m_OutputName=CString(name);
	UpdateData(TRUE);
	m_edit_viewshedRasteroutput=m_OutputPath+"\\"+m_OutputName;
	UpdateData(FALSE);
	
}

void CDlgViewshed::OnButtonViewshedSurfaceinput() 
{
	// TODO: Add your control notification handler code here
	IGxDialogPtr ipGxDialog(CLSID_GxDialog);
	IGxObjectFilterPtr ipGxObjectFilter( CLSID_GxFilterSurfaceDatasets);
	HRESULT hr=ipGxDialog->putref_ObjectFilter( ipGxObjectFilter);
	if(FAILED(hr)) return;
	hr = ipGxDialog->put_Title(CComBSTR("ѡ��һ��DEM��������"));
	if(FAILED(hr)) return;
	IEnumGxObjectPtr ipEnumGxObject;
	VARIANT_BOOL bResult;
	hr=ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);
	if(FAILED(hr)) return;
	if(bResult==VARIANT_FALSE)return;
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
			if(FAILED(hr )) return;
			IRasterDatasetPtr ipRasterDataset(ipDataset);
			if(ipRasterDataset!=NULL)
			{			 
				m_ipR=ipRasterDataset;			  
				CComBSTR bstrName;			  
				hr=ipRasterDataset->get_CompleteName(&bstrName);
				if(FAILED(hr)) return;
				m_edit_viewshedSurfaceinput=bstrName;
				IRasterPtr ipRas;
				//�������Raster����������С,��Ϊviewshed��Ĭ��ֵ
				hr=ipRasterDataset->CreateDefaultRaster(&ipRas);
				IRasterAnalysisPropsPtr ipRA(ipRas);
				double defaultcellsize;
				hr=ipRA->get_PixelHeight(&defaultcellsize);
				m_edit_viewshedCellsize=defaultcellsize;
				UpdateData(FALSE);		
			}	     
			ITinPtr ipTin(ipDataset);	     
			ITinSurfacePtr ipTS(ipDataset);	     
			if( ipTin!=NULL)		 
			{		  
				m_ipT=ipTin;		  
				CComBSTR bstrName;		  
				hr=ipDataset->get_Name(&bstrName);		  
				if(FAILED(hr)) return;
				m_edit_viewshedSurfaceinput=bstrName;		 
				IGeoDatasetPtr plnTin(m_ipT);		 
				//ͨ�����Tin�ķ�Χ����Ĭ�ϡ�ellsize��С		 
				IEnvelopePtr pExtent;		 
				hr=plnTin->get_Extent(&pExtent);		 
				double width,height;
				hr=pExtent->get_Width(&width);
				hr= pExtent->get_Height(&height);
				double defaultcellsize;
				if ( width>height)
					defaultcellsize=height/250;
				else			
					defaultcellsize=width/250;		
				m_edit_viewshedCellsize=defaultcellsize;	
				UpdateData( FALSE);
			}
		}
	}

	
}

void CDlgViewshed::OnOK() 
{
	// TODO: Add extra validation here
		if(m_ipT!=NULL)
	{
		TintoRaster( m_ipT);//��TinתΪRaster}
	}
	Viewshed();
	CDialog::OnOK();

}
 void CDlgViewshed::TintoRaster(ITin*ipT)
{
	HRESULT hr;
    IGeoDatasetPtr pInTin(ipT);
    IEnvelopePtr pExtent;
    hr=pInTin->get_Extent(&pExtent);
	IPointPtr pOrigin;
	hr=pExtent->get_LowerLeft(&pOrigin);
	double x,y;
	hr=pOrigin->get_X(&x);
	hr=pOrigin->get_Y(&y);
	hr = pOrigin->put_X(x-m_edit_viewshedCellsize*0.5);
	hr = pOrigin->put_Y(y-m_edit_viewshedCellsize*0.5);
	long nCol,nRow;
	double width,height;
	hr=pExtent->get_Width(&width);
	hr=pExtent->get_Height(&height);
	nCol=int(width/m_edit_viewshedCellsize)+1;
	nRow=int(height/m_edit_viewshedCellsize)+1;
	ISpatialReferencePtr pSR;
	hr=pInTin->get_SpatialReference(&pSR);
	IRasterDatasetPtr pRDS;
	IWorkspaceFactoryPtr rWksFac(CLSID_RasterWorkspaceFactory);
	IWorkspacePtr wks;
	hr=rWksFac->OpenFromFile(CComBSTR(m_OutputPath),0,&wks);
	IRasterWorkspace2Ptr rWks(wks);
	long numbands=1;
	hr=rWks->CreateRasterDataset(CComBSTR("tempToR"),
                                 CComBSTR("GRID"),
                                 pOrigin,
                                 nCol,
                                 nRow,
								 m_edit_viewshedCellsize,
								 m_edit_viewshedCellsize,
								 numbands,
								 PT_FLOAT,
								 pSR,
								 VARIANT_TRUE,
								 &pRDS);

	if(FAILED(hr))
	{
		if(hr=-2147467259)
		{
			AfxMessageBox( " ��ʱ�ļ�tempTtoR�Ѿ�����,����ɾ��");
		}
		AfxMessageBox ( " ��ʱ�ļ�Raster�ļ�tempTtoR����ʧ��!");
		return;
	}
	//�����ǵ���GetRawPixel������ 
	IRasterBandCollectionPtr pBandCollection(pRDS);
	IRasterBandPtr pRasterBand;
	hr=pBandCollection->Item(0,&pRasterBand);
	IRawPixelsPtr pRawPixels(pRasterBand);
	IPntPtr pBlockSize(CLSID_DblPnt);
	hr=pBlockSize->put_X(nCol);
	hr=pBlockSize->put_Y(nRow);
	IPixelBlockPtr pPixelBlock;
	hr=pRawPixels->CreatePixelBlock(pBlockSize,&pPixelBlock);
	VARIANT val;
	val.vt=VT_SAFEARRAY ;//Ҫָ������
	hr=pPixelBlock->get_SafeArray(0,&val);
	ITinSurfacePtr pTinSurf( ipT);
	IRasterPropsPtr pRasterProps(pRawPixels);
	VARIANT nodataFloat;
	nodataFloat.vt=VT_R4 ;//Ҫָ������
    hr=pOrigin->get_X(&x);
    hr=pOrigin->get_Y(&y);
    hr=pOrigin->put_X(x+m_edit_viewshedCellsize*0.5);
    hr=pOrigin->put_Y(y+m_edit_viewshedCellsize*nRow-m_edit_viewshedCellsize*0.5);
	hr=pRasterProps->get_NoDataValue(&nodataFloat);
	hr=pOrigin->get_X(&x);
	hr=pOrigin->get_Y(&y);
	hr= pTinSurf->QueryPixelBlock(x,y,		
		m_edit_viewshedCellsize,
		m_edit_viewshedCellsize,
		esriElevationAsRaster,
		nodataFloat,
		val);
	IPntPtr pOffset(CLSID_DblPnt);
	hr=pOffset->put_X(0);
	hr=pOffset->put_Y(0);
	hr=pRawPixels->Write(pOffset,pPixelBlock);
    //ע��:ֻ��ָ��pRDS���ͷ�,Raster�Ż���ڴ�д��Ӳ�̡�
}
void CDlgViewshed::Viewshed()
{
	HRESULT hr;
	if( m_ipT!=NULL)
	{
		IWorkspacePtr ppRW ;//�����ɵ�Raster����ipR   
		IWorkspaceFactoryPtr pWF(CLSID_RasterWorkspaceFactory);    
		hr=pWF->OpenFromFile(CComBSTR(m_OutputPath),0,&ppRW);    
		IRasterWorkspacePtr pRW(ppRW);   
		hr=pRW->OpenRasterDataset(CComBSTR("tempTtoR"),&m_ipR);
	}
	//����RasterSurface0p����
	ISurfaceOpPtr pSurfaceOp(CLSID_RasterSurfaceOp);
	//�������˱������
	IGeoDatasetPtr pElevation(m_ipR);
	//�����۲�����
	IGeoDatasetPtr pObservers(m_ipfeat);
	//�����������
	IGeoDatasetPtr pOutputRaster;
	//ͨ�����û����ӿ�IRasterAnalysisEnvironment��
	//����OutV}Torkspace�ı�·��
	IRasterAnalysisEnvironmentPtr pEnv(pSurfaceOp);
	hr=pEnv->Reset();
	VARIANT cellsize;//���á�iewshed������cellsize�Ĵ�С
	cellsize.vt=VT_R8;
	cellsize.dblVal=m_edit_viewshedCellsize;
	hr=pEnv->SetCellSize(esriRasterEnvValue,&cellsize);
	IWorkspacePtr pWo;
	IWorkspaceFactoryPtr pWSF(CLSID_RasterWorkspaceFactory);
	hr=pWSF->OpenFromFile(CComBSTR(m_OutputPath),NULL,&pWo);
	if(FAILED(hr))
	{
       AfxMessageBox ("�򿪱�������ʧ��!");
       return; 
	}

	hr=pEnv->putref_OutWorkspace(pWo);

	if(FAILED(hr ))
	{
		AfxMessageBox("���·������ʧ��!");
		return;
	}

	hr=pSurfaceOp->Visibility(pElevation,
                              pObservers,
                              esriGeoAnalysisVisibilityFrequency,
                              &pOutputRaster);

	if(FAILED(hr))
	{    
		AfxMessageBox("viewshed failed!");     
		return;
	}
	//���ñ������ɵ�Raster
	IRasterPtr pOutRaster(pOutputRaster);
	IRasterBandCollectionPtr pRasBandC(pOutRaster);
	IDatasetPtr pOut;
	hr=pRasBandC->SaveAs(CComBSTR(m_OutputName),pWo,CComBSTR("GRID"),&pOut);

	if(FAILED(hr))
	{
    
		AfxMessageBox("����ʧ��!");
        return;
	}
} 

