// DlgSlope.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgSlope.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSlope dialog


CDlgSlope::CDlgSlope(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSlope::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSlope)
	m_edit_inputSurf_slope = _T("");
	m_edit_OutputCellsizeSlope = 0.0;
	m_edit_outputRaster_slope = _T("");
	m_degree=-1;
	//}}AFX_DATA_INIT
}


void CDlgSlope::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSlope)
	DDX_Text(pDX, IDC_EDIT_INPUT_SURF_SLOPE, m_edit_inputSurf_slope);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_CELLSIZE_SLOPE, m_edit_OutputCellsizeSlope);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_RASTER_SLOPE, m_edit_outputRaster_slope);
	DDX_Text(pDX, IDC_RADIO_DEGREE_SLOPE, m_degree);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSlope, CDialog)
	//{{AFX_MSG_MAP(CDlgSlope)
	ON_BN_CLICKED(IDC_BUTTON_INPUTSURF_SLOPE, OnButtonInputsurfSlope)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUTRASTER_SLOPE, OnButtonOutputrasterSlope)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSlope message handlers

void CDlgSlope::OnButtonInputsurfSlope() 
{
	// TODO: Add your control notification handler code here
IGxDialogPtr ipGxDialog(CLSID_GxDialog);
    IGxObjectFilterPtr ipGxObjectFilter( CLSID_GxFilterSurfaceDatasets);
    HRESULT hr=ipGxDialog->putref_ObjectFilter(ipGxObjectFilter);
    if(FAILED(hr)) return;
    hr = ipGxDialog->put_Title(CComBSTR("ѡ��һ��DEM��������"));
    if(FAILED(hr)) return;

	IEnumGxObjectPtr ipEnumGxObject;

	VARIANT_BOOL bResult;

	hr=ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);

	if(FAILED(hr)) return;
 	if(bResult==VARIANT_FALSE) return;
	hr=ipEnumGxObject->Reset();
	if(FAILED(hr)) return;
	IGxObjectPtr ipGxObject;
	ipGxDialog->get_FinalLocation( &ipGxObject);
 
	while(!ipEnumGxObject->Next(&ipGxObject))
	{
		 
		IGxDatasetPtr ipGxDataset(ipGxObject);
		if(ipGxDataset!=0)
		{
			IDatasetPtr ipDataset;
			hr=ipGxDataset->get_Dataset(&ipDataset);
			if(FAILED(hr)) return;
			IRasterDatasetPtr ipRasterDataset(ipDataset);
			if(ipRasterDataset!=NULL)
			{
				m_ipR=ipRasterDataset;
				CComBSTR bstrName;
				hr=ipRasterDataset->get_CompleteName(&bstrName);
				if(FAILED(hr)) return;
				m_edit_inputSurf_slope=bstrName;
				IRasterPtr ipRas;
				//�������Raster����������С,
				//��Ϊ���Raster�����С��Ĭ��ֵ
				hr=ipRasterDataset->CreateDefaultRaster(&ipRas);
				IRasterAnalysisPropsPtr ipRA(ipRas);
				double defaultcellsize;
				hr=ipRA->get_PixelHeight( &defaultcellsize);
				m_edit_OutputCellsizeSlope=defaultcellsize;
				UpdateData(FALSE);
			}
			
			ITinPtr ipTin(ipDataset);

			if(ipTin!=NULL)
			{
					  
					m_ipT=ipTin ;
					CComBSTR bstrName;  
					hr= ipDataset->get_Name(&bstrName);  
					if(FAILED(hr)) return;  
					m_edit_inputSurf_slope=CString(bstrName);    
					IGeoDatasetPtr plnTin(m_ipT);    
					//ͨ�����Tin�ķ�Χ����Ĭ�ϡ�ellsize��С    
					IEnvelopePtr pExtent;    
					hr=plnTin->get_Extent(&pExtent);    
					double width,height;  
					hr=pExtent->get_Width(&width);    
					hr=pExtent->get_Height(&height);    
					double defaultcellsize;    
					if ( width>height)        
						defaultcellsize=height/250;      
					else        
						defaultcellsize=width/250;    
					m_edit_OutputCellsizeSlope=defaultcellsize;    
					UpdateData(FALSE);
			}
			UpdateData(FALSE);
			
		}
	}
}

void CDlgSlope::OnButtonOutputrasterSlope() //���դ������·����ť������Ϣ��Ӧ����
{
	// TODO: Add your control notification handler code here
 IGxDialogPtr ipGxDialog(CLSID_GxDialog);
    //Set the Filter to FeatureDatasets and FeatureClasses
    IGxObjectFilterPtr ipGxObjectFilter(CLSID_GxFilterRasterDatasets);
    HRESULT hr = ipGxDialog->putref_ObjectFilter(ipGxObjectFilter);
    if(FAILED(hr))return;
    hr = ipGxDialog->put_Title(CComBSTR("�����¶�ͼ"));
    if(FAILED(hr)) return;
	VARIANT_BOOL bResult;
	OLE_HANDLE hwnd=(OLE_HANDLE)this->GetSafeHwnd();
	hr=ipGxDialog->DoModalSave(hwnd,&bResult);
	if(FAILED(hr))return;
	IGxObjectPtr ipGxObject;
	ipGxDialog->get_FinalLocation(&ipGxObject);
	CComBSTR path;
	ipGxObject->get_FullName(&path);
	m_OutputPath=CString(path);
	CComBSTR name;
	ipGxDialog->get_Name(&name);
	m_OutputRasterName_Slop=CString(name);
	UpdateData(TRUE);
	m_edit_outputRaster_slope=m_OutputPath+"\\"+m_OutputRasterName_Slop;
	UpdateData(FALSE);
}

void CDlgSlope::OnOK() 
{
	// TODO: Add extra validation here
::OleInitialize(NULL);//���������ʼ�� 
	if(m_ipR!=NULL)
	{
		UpdateData(TRUE);
		CreateSlope(m_ipR);
	}
	if(m_ipT!=NULL)
	{
		UpdateData(TRUE);
		CreateSlope(m_ipT);
	}
	CDialog::OnOK();
}

void CDlgSlope::CreateSlope(ITin* ipT) //ΪTIN�����¶ȹ��̺�����
{ 
 ::OleInitialize(NULL);//���������ʼ�� 

 	HRESULT hr;
    IGeoDatasetPtr pInTin(ipT);
	IEnvelopePtr pExtent;
	hr=pInTin->get_Extent(&pExtent);
    IPointPtr pOrigin;
	hr=pExtent->get_LowerLeft(&pOrigin);
	double x,y;
	hr=pOrigin->get_X(&x);
	hr=pOrigin->get_Y(&y); 
	hr=pOrigin->put_X(x-m_edit_OutputCellsizeSlope*0.5);
	hr=pOrigin->put_Y(y-m_edit_OutputCellsizeSlope*0.5);
	long nCol,nRow;
	double width,height;
	hr=pExtent->get_Width(&width);
	hr=pExtent->get_Height(&height);
	nCol=int(width/m_edit_OutputCellsizeSlope)+1;
	nRow=int(height/m_edit_OutputCellsizeSlope)+1;
	ISpatialReferencePtr pSR;
	hr=pInTin->get_SpatialReference(&pSR);
	IRasterDatasetPtr pRDS;
	IWorkspaceFactoryPtr rWksFac(CLSID_RasterWorkspaceFactory);
	IWorkspacePtr wks;
	hr = rWksFac->OpenFromFile(CComBSTR(m_OutputPath),0,&wks);
	IRasterWorkspace2Ptr rWks(wks);
	long numbands=1;
 	rWks->CreateRasterDataset((CComBSTR)m_OutputRasterName_Slop,
                               CComBSTR("GRID"),
                               pOrigin,
                               nCol,
                               nRow,
                               m_edit_OutputCellsizeSlope,
                               m_edit_OutputCellsizeSlope,
                               numbands,
                               PT_FLOAT,
                               pSR,
                               VARIANT_TRUE,     
                               &pRDS);

	if(FAILED(hr))
	{
      AfxMessageBox ( " Raster�ļ�����ʧ��!");
      return;
	}
 AfxMessageBox ( " 1�ļ�����ʧ��!");
	//�õ�RawPixels
	IRasterBandCollectionPtr pBandCollection(pRDS);
	long cont;
    CString str;

 hr=pBandCollection->get_Count(&cont);
        str.Format("(%f\n",(double) cont);
		AfxMessageBox(str); 

	IRasterBandPtr pRasterBand;
  AfxMessageBox ( " 2r�ļ�����ʧ��!");
	hr=pBandCollection->Item(0,&pRasterBand);
	 AfxMessageBox ( " 3�ļ�����ʧ��!");
 
	IRawPixelsPtr pRawPixels(pRasterBand);
 
	IPntPtr pBlockSize(CLSID_DblPnt);
	hr=pBlockSize->put_X(nCol);
	hr=pBlockSize->put_Y(nRow);
	IPixelBlockPtr pPixelBlock;
	hr=pRawPixels->CreatePixelBlock(pBlockSize,&pPixelBlock);
	VARIANT val;
	val.vt = VT_SAFEARRAY ;//Ҫָ������
	hr=pPixelBlock->get_SafeArray(0,&val);
	ITinSurfacePtr pTinSurf(ipT); 
	IRasterPropsPtr pRasterProps(pRawPixels);
	VARIANT nodatafloat;
	nodatafloat.vt = VT_R4 ;//Ҫָ������
	// QueryPixelBlockʹ�����Ͻǵ������Ϊԭ��
	//����Ϊ������������
 
	hr=pOrigin->get_X(&x);
	hr=pOrigin->get_Y(&y);
	hr=pOrigin->put_X(x+m_edit_OutputCellsizeSlope*0.5);
	hr = pOrigin->put_Y(y+m_edit_OutputCellsizeSlope*nRow-m_edit_OutputCellsizeSlope*0.5);
	hr=pRasterProps->get_NoDataValue(&nodatafloat);
	hr = pOrigin->get_X(&x);
	hr=pOrigin->get_Y(&y);
	esriRasterizationType Type;
	UpdateData(TRUE);
	
m_degree=0;
	if ( m_degree==0)
		Type=esriDegreeSlopeAsRaster;
	if(m_degree==1)
		Type=esriPercentageSlopeAsRaster;
	if(m_degree ==-1)
	{
		AfxMessageBox("��ѡ�������λ!");
		return;
	}
//	AfxMessageBox ( " 2....!");

	hr=pTinSurf->QueryPixelBlock(x,y,
                                  m_edit_OutputCellsizeSlope,
                                  m_edit_OutputCellsizeSlope,
                                  Type,
                                  nodatafloat,
                                  val);

	IPntPtr pOffset(CLSID_DblPnt);
	hr=pOffset->put_X(0);
	hr = pOffset->put_Y(0);
	hr=pRawPixels->Write(pOffset,pPixelBlock);
    //ע��:ֻ��ָ��pRDS���ͷ�,Raster�Ż���ڴ�д��Ӳ�̡�
}

void CDlgSlope::CreateSlope(IRasterDataset* ipR)  //ΪRaster�����¶�ͼ���̺�����
{
    HRESULT hr;
   ISurfaceOpPtr pSurfaceOp(CLSID_RasterSurfaceOp);
   IGeoDatasetPtr pInputDataset(ipR);
   //�����������
   IGeoDatasetPtr pOutputRaster;
   //�������������
   IRasterAnalysisEnvironmentPtr pEnv(pSurfaceOp);
   hr=pEnv->put_VerifyType(esriRasterVerifyOn);
   VARIANT vCellsize;
   vCellsize.vt=VT_R8;
   vCellsize.dblVal=m_edit_OutputCellsizeSlope;
   hr=pEnv->SetCellSize(esriRasterEnvValue,&vCellsize);
   if(FAILED(hr)) return;
   IWorkspacePtr pWo;
   IWorkspaceFactoryPtr pWSF(CLSID_RasterWorkspaceFactory);
   hr=pWSF->OpenFromFile((CComBSTR)m_OutputPath,NULL,&pWo);
   if(FAILED(hr))
   {
	   AfxMessageBox("ʧ��!");      
	   return;
   }
   //Slope��ʼ
   VARIANT vZfactor;
   vZfactor.vt= VT_R8;
   vZfactor.dblVal=1;
   enum esriGeoAnalysisSlopeEnum slopeType;
	UpdateData(TRUE);
   if(m_degree==0) slopeType=esriGeoAnalysisSlopeDegrees;
   if(m_degree==1) slopeType=esriGeoAnalysisSlopePercentrise;
   if(m_degree==-1)
   {
    AfxMessageBox("��ѡ�������λ!");
        return;
   }
   hr=pSurfaceOp->Slope(pInputDataset,slopeType,&vZfactor,&pOutputRaster);
	   if(FAILED(hr))
	   {
		   AfxMessageBox ("�¶�ͼ����ʧ��!");
			   return;
	   }
	   IRasterBandCollectionPtr pBands(pOutputRaster);
	   IDatasetPtr pRD;
	   hr= pBands->SaveAs(CComBSTR(m_OutputRasterName_Slop),
                                   pWo,
								   CComBSTR("GRID"),
                                   &pRD);
}

