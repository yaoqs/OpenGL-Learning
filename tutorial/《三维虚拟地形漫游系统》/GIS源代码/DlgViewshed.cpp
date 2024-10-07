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
	//打开对话框         
	IGxDialogPtr ipGxDialog(CLSID_GxDialog);         
	IGxObjectFilterPtr ipGxObjectFiiter( CLSID_GxFilterPointFeatureClasses);
    //注意:这里使用了GxFilterPointFeatureClasses ,
    //可以过滤点特征集，满足功能只用点内插的需要          
	HRESULT hr=ipGxDialog->putref_ObjectFilter(ipGxObjectFiiter);            
	if(FAILED(hr)) return;
    hr=ipGxDialog->put_Title(CComBSTR("选择一个点数据集"));
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
			CComBSTR bstrName; //*} book获得输入点层的全名
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
	hr=ipGxDialog->put_Title( CComBSTR("保存"));
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
	hr = ipGxDialog->put_Title(CComBSTR("选择一个DEM表面数据"));
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
				//获得输人Raster表面的网格大小,作为viewshed的默认值
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
				//通过获得Tin的范围设置默认。ellsize大小		 
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
		TintoRaster( m_ipT);//将Tin转为Raster}
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
			AfxMessageBox( " 临时文件tempTtoR已经存在,请先删除");
		}
		AfxMessageBox ( " 临时文件Raster文件tempTtoR生成失败!");
		return;
	}
	//下面是调用GetRawPixel。函数 
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
	val.vt=VT_SAFEARRAY ;//要指定类型
	hr=pPixelBlock->get_SafeArray(0,&val);
	ITinSurfacePtr pTinSurf( ipT);
	IRasterPropsPtr pRasterProps(pRawPixels);
	VARIANT nodataFloat;
	nodataFloat.vt=VT_R4 ;//要指定类型
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
    //注意:只有指针pRDS被释放,Raster才会从内存写人硬盘。
}
void CDlgViewshed::Viewshed()
{
	HRESULT hr;
	if( m_ipT!=NULL)
	{
		IWorkspacePtr ppRW ;//将生成的Raster赋给ipR   
		IWorkspaceFactoryPtr pWF(CLSID_RasterWorkspaceFactory);    
		hr=pWF->OpenFromFile(CComBSTR(m_OutputPath),0,&ppRW);    
		IRasterWorkspacePtr pRW(ppRW);   
		hr=pRW->OpenRasterDataset(CComBSTR("tempTtoR"),&m_ipR);
	}
	//创建RasterSurface0p对象
	ISurfaceOpPtr pSurfaceOp(CLSID_RasterSurfaceOp);
	//声明输人表面对象
	IGeoDatasetPtr pElevation(m_ipR);
	//声明观察点对象
	IGeoDatasetPtr pObservers(m_ipfeat);
	//声明输出对象
	IGeoDatasetPtr pOutputRaster;
	//通过设置环境接口IRasterAnalysisEnvironment的
	//函数OutV}Torkspace改变路径
	IRasterAnalysisEnvironmentPtr pEnv(pSurfaceOp);
	hr=pEnv->Reset();
	VARIANT cellsize;//设置、iewshed输出结果cellsize的大小
	cellsize.vt=VT_R8;
	cellsize.dblVal=m_edit_viewshedCellsize;
	hr=pEnv->SetCellSize(esriRasterEnvValue,&cellsize);
	IWorkspacePtr pWo;
	IWorkspaceFactoryPtr pWSF(CLSID_RasterWorkspaceFactory);
	hr=pWSF->OpenFromFile(CComBSTR(m_OutputPath),NULL,&pWo);
	if(FAILED(hr))
	{
       AfxMessageBox ("打开表面数据失败!");
       return; 
	}

	hr=pEnv->putref_OutWorkspace(pWo);

	if(FAILED(hr ))
	{
		AfxMessageBox("输出路径设置失败!");
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
	//永久保存生成的Raster
	IRasterPtr pOutRaster(pOutputRaster);
	IRasterBandCollectionPtr pRasBandC(pOutRaster);
	IDatasetPtr pOut;
	hr=pRasBandC->SaveAs(CComBSTR(m_OutputName),pWo,CComBSTR("GRID"),&pOut);

	if(FAILED(hr))
	{
    
		AfxMessageBox("分析失败!");
        return;
	}
} 

