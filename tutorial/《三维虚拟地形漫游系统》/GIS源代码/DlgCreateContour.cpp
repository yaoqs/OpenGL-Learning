// DlgCreateContour.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgCreateContour.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateContour dialog


CDlgCreateContour::CDlgCreateContour(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateContour::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreateContour)
	m_edit_Contour_SurfaceInput = _T("");
	m_edit_ContourFeatureOutput = _T("");
	m_edit_Contour_MaxContour = 0.0;
	m_edit_Contour_MinContour = 0.0;
	m_edit_ContourZMax_in = 0.0;
	m_edit_ContourZMin_in = 0.0;
	m_edit_ContourTotalNumContour = 0;
	//}}AFX_DATA_INIT
}


void CDlgCreateContour::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateContour)
	DDX_Control(pDX, IDC_EDIT_CONTOUR_CONTOURINTERVAL, m_edit_Contour_ContourInterval);
	DDX_Control(pDX, IDC_EDIT_CONTOUR_BASECONTOUR, m_edit_ContourBaseContour);
	DDX_Text(pDX, IDC_EDIT_CONTOUR_SURFACE_INPUT, m_edit_Contour_SurfaceInput);
	DDX_Text(pDX, IDC_EDIT_CONTOUR_FEATURE_OUTPUT, m_edit_ContourFeatureOutput);
	DDX_Text(pDX, IDC_EDIT_CONTOUR_MAXCONTOUR, m_edit_Contour_MaxContour);
	DDX_Text(pDX, IDC_EDIT_CONTOUR_MINCONTOUR, m_edit_Contour_MinContour);
	DDX_Text(pDX, IDC_EDIT_CONTOUR_ZMAX, m_edit_ContourZMax_in);
	DDX_Text(pDX, IDC_EDIT_CONTOUR_ZMIN, m_edit_ContourZMin_in);
	DDX_Text(pDX, IDC_EDIT_CONTOUR_TOTALNUMCONTOUR, m_edit_ContourTotalNumContour);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateContour, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateContour)
	ON_BN_CLICKED(IDC_BUTTON_CONTOUR_FEATURE_OUTPUT, OnButtonContourFeatureOutput)
	ON_BN_CLICKED(IDC_BUTTON_CONTOUR_SURFACE_INPUT, OnButtonContourSurfaceInput)
	ON_EN_CHANGE(IDC_EDIT_CONTOUR_BASECONTOUR, OnChangeEditContourBasecontour)
	ON_EN_CHANGE(IDC_EDIT_CONTOUR_CONTOURINTERVAL, OnChangeEditContourContourinterval)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateContour message handlers

void CDlgCreateContour::OnButtonContourFeatureOutput() 
{
	// TODO: Add your control notification handler code here
IGxDialogPtr ipGxDialog( CLSID_GxDialog);
	//FeatureClasses
	IGxObjectFilterPtr ipGxObjectFilter(CLSID_GxFilterFeatureClasses);
	HRESULT hr=ipGxDialog->putref_ObjectFilter( ipGxObjectFilter);
	if(FAILED(hr)) return;
	hr = ipGxDialog->put_Title(CComBSTR("保存等高线"));
	if(FAILED(hr)) return;
	VARIANT_BOOL bResult;
    IEnumGxObjectPtr ipEnumGxObject;
	OLE_HANDLE hwnd=(OLE_HANDLE)this->GetSafeHwnd();
	hr=ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);
	if(FAILED(hr)) return;
	if(bResult==VARIANT_FALSE)return;
	IGxObjectPtr ipGxObject;
	ipGxDialog->get_FinalLocation(&ipGxObject); 
	CComBSTR path;
	ipGxObject->get_FullName(&path);
	m_OutputFeatureDir=CString(path);
	CComBSTR name;
	ipGxDialog->get_Name(&name);
	m_OutputFeatureName=CString(name);
//    m_edit_ContourFeatureOutput;
//	m_OutputFeatureDir+"\\"+m_OutputFeatureName;
	UpdateData(FALSE);
}

void CDlgCreateContour::OnButtonContourSurfaceInput() 
{
	// TODO: Add your control notification handler code here

	IGxDialogPtr ipGxDialog( CLSID_GxDialog);
	IGxObjectFilterPtr ipGxObjectFilter( CLSID_GxFilterSurfaceDatasets);
	HRESULT hr=ipGxDialog->putref_ObjectFilter(ipGxObjectFilter);
	if(FAILED(hr)) return;
	hr=ipGxDialog->put_Title(CComBSTR ("选择一个DEM表面数据"));
	if(FAILED( hr)) return;
	IEnumGxObjectPtr ipEnumGxObject;
	VARIANT_BOOL bResult;
	hr=ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);
	if(FAILED(hr)) return;
	if(bResult==VARIANT_FALSE)return;
	hr=ipEnumGxObject->Reset();
	if(FAILED(hr)) return;
	IGxObjectPtr ipGxObject;
	ipGxDialog->get_FinalLocation(&ipGxObject);
	CComBSTR path;
	ipGxObject->get_FullName(&path);
	m_edit_Contour_SurfaceInput=CString(path);
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
				m_edit_Contour_SurfaceInput= bstrName;
			}
    	ITinPtr ipTin(ipDataset);
	    ITinSurfacePtr ipTS(ipDataset);

	    if ( ipTin!=NULL)
		{
    
		m_ipT=ipTin;    
		m_ipTS=ipTS;      
		CComBSTR bstrName;    
		hr=ipDataset->get_Name(&bstrName);    
		if(FAILED(hr )) return;    
		m_edit_Contour_SurfaceInput=CString(bstrName);
		}
	   UpdateData(FALSE);
	   if(ipRasterDataset!=NULL)  
	   {
         ComputerHeightRange(ipRasterDataset);  
	   }
  
	   if(ipTin!=NULL)  
	   {
       ComputerHeightRange(ipTin);
	   }
		}
	}
}
void CDlgCreateContour::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	if(m_ipR!=NULL)
	{
		CreateContour(m_ipR);

	}
	if(m_ipT!=NULL)
	{
		CreateContour();
	}	
	CDialog::OnOK();
}

void CDlgCreateContour::OnChangeEditContourBasecontour() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_ipT!=NULL || m_ipR!=NULL)
 
	{    
		CString str;    
		m_edit_Contour_ContourInterval.GetWindowText(str);    
		double interval=atof(str);
		m_edit_ContourBaseContour.GetWindowText(str);
		double base=atof ( str );
		ComputerOutputInfo(m_edit_ContourZMax_in,
                          m_edit_ContourZMin_in,
                          interval,
                           base);
	}
}

void CDlgCreateContour::OnChangeEditContourContourinterval() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_ipT!=NULL || m_ipR!=NULL)
	{
        CString str;
        m_edit_Contour_ContourInterval.GetWindowText(str);
        double interval=atof (str);
        m_edit_ContourBaseContour.GetWindowText(str);
        double base=atof ( str);
        ComputerOutputInfo(m_edit_ContourZMax_in,
                            m_edit_ContourZMin_in,
                           interval,
                           base);
	}
}
void CDlgCreateContour::ComputerHeightRange(IRasterDataset * pRasterDataset)
{   //如何计算RasterDataset 的统计信息
	HRESULT hr;
	IRasterBandCollectionPtr pRasterBC(pRasterDataset);
	IRasterBandPtr pRasterB;
	hr=pRasterBC->Item(0,&pRasterB);
	IRasterStatisticsPtr pRasterS;
	hr=pRasterB->get_Statistics(&pRasterS);
	hr=pRasterS->get_Maximum(&m_edit_ContourZMax_in);
	if(FAILED(hr ))	return;
	hr=pRasterS->get_Minimum(&m_edit_ContourZMin_in);
    UpdateData(FALSE);
}
void CDlgCreateContour::ComputerHeightRange(ITin *ipT)
{   //如何计算Tin的空间范围统计信息
   HRESULT hr;
    IEnvelopePtr ipEnv;
    m_ipT->get_Extent(&ipEnv); 
	hr= ipEnv->get_ZMin(&m_edit_ContourZMax_in);
	if(FAILED(hr ))return; 
	hr=ipEnv->get_ZMax(&m_edit_ContourZMax_in); 
	UpdateData(FALSE);	
}
void CDlgCreateContour::ComputerOutputInfo(double Zmax,double Zmin,double interval,double base)
{
   if(interval==0)
    {
        AfxMessageBox("请不要把间隔设置为0");
        return;
    }
    if(base>Zmin)
    {
          int  N=1;
        for( int i=0;i<N;i++)
        {
            double temp= base-i *interval-Zmin;
            if(temp<=interval&&temp>=0)
              {
                  N=1;
                  m_edit_Contour_MinContour=base-i*interval;
              }
			else{
				N=i+2;}
		}
	}
    else
	{
		int N = 1;

		for( int i=0;i<N;i++)
		{

			double temp =base+i*interval-Zmin;
			if(temp<=interval&&temp>=0)
			{
				N=i;
				m_edit_Contour_MinContour=base+i*interval;
			}
		    else
			{

				N=i+2;
			}
		}
	}
	

	if(base>Zmax)
	{
		int N=1;
		for( int i=0;i<N;i++)
		{		
			double temp=Zmax-(base-i*interval);		
			if(temp<=interval&&temp>=0)		
			{					
				N=i;			
				m_edit_Contour_MaxContour=base-i*interval;		
			}        
			else		
			{              
				N=i+2;		
			}
		}		
	}
	else
	{
		int N=1;
		for( int i=0;i<N;i++)
		{
    
			double temp= Zmax-(base+i*interval);
    
				if(temp<= interval&&temp>=0)
    
				{
          
					N=3;
          
					m_edit_Contour_MaxContour = base+i*interval;
      
				}
      
				else
				{

					N=i+2; 
				}
          
				m_edit_ContourTotalNumContour=
					(m_edit_Contour_MaxContour-m_edit_Contour_MinContour)/interval+1;
				UpdateData(FALSE);
		}
	}
}
void CDlgCreateContour::CreateContour()
{
//先创建featureclass对象，用于等高线的输出
	HRESULT hr;
	CString strShapeFieldName="Shape";
	//打开一个存在的文件夹作为工作区Workspace
	IWorkspaceFactoryPtr ipWorkspaceFactory(CLSID_ShapefileWorkspaceFactory);
	IWorkspacePtr ipWorkspace;
	hr=ipWorkspaceFactory->OpenFromFile((CComBSTR)m_OutputFeatureDir,0,&ipWorkspace);
	if( FAILED(hr)) return;
	IFeatureWorkspacePtr ipFeatWorkspace(ipWorkspace);
	//创建Fields对象集
	IFieldsPtr ipFields(CLSID_Fields);
	IFieldsEditPtr ipFieldsEdit(ipFields);
	//创建Shape字段
	//it will need a geometry definition，with a spatial reference
	IFieldPtr ipField(CLSID_Field);
	IFieldEditPtr ipFieldEdit( ipField);
	hr=ipFieldEdit->put_Name((CComBSTR)strShapeFieldName);
	if ( FAILED(hr)) return;
	hr=ipFieldEdit->put_Type(esriFieldTypeGeometry);
	if( FAILED(hr)) return;
	IGeometryDefPtr ipGeomDef ( CLSID_GeometryDef );
	IGeometryDefEditPtr ipGeomDefEdit(ipGeomDef );
	ISpatialReferencePtr ipSpatialRef( CLSID_UnknownCoordinateSystem);
	hr=ipGeomDefEdit->put_GeometryType(esriGeometryPolyline);
	if ( FAILED(hr)) return;
	hr=ipGeomDefEdit->putref_SpatialReference( ipSpatialRef );
	if ( FAILED(hr)) return;
	hr=ipFieldEdit->putref_GeometryDef( ipGeomDef );
	if ( FAILED(hr )) return;
	hr=ipFieldsEdit->AddField(ipField);
	if ( FAILED(hr)) return;
	//创建Shapefile(一些参数默认为NULL)
	IFeatureClassPtr   ipFeatureClass;
	hr=ipFeatWorkspace->CreateFeatureClass((CComBSTR)m_OutputFeatureName,
				                                    ipFields,
                                                    NULL,
                                                    NULL,
                                                    esriFTSimple,
                                                    (CComBSTR)strShapeFieldName,
                                                    (CComBSTR)"",
                                                    &ipFeatureClass);

	if ( FAILED(hr )) return;
	if ( ipFeatureClass==NULL)return;
	CString str;
	m_edit_Contour_ContourInterval.GetWindowText(str);
	double interval=atof ( str );
	m_edit_ContourBaseContour. GetWindowText(str);
	double base=atof(str);
	hr=m_ipTS->Contour(base,interval,ipFeatureClass,CComBSTR("Contour"),0);
	if(FAILED(hr))
	{
		if(hr==-2147467259)
		{
				AfxMessageBox("等高线恢复无法进行，请更换表面数据!");
		}
		return;
		}
	AfxMessageBox ("成功!");
}
void CDlgCreateContour::CreateContour( IRasterDataset*ipR)
{
HRESULT hr;
	ISurfaceOpPtr pSurfaceOp(CLSID_RasterSurface);
	IGeoDatasetPtr plnputDataset(ipR);
	//声明输出对象
	IGeoDatasetPtr pOutput;
	//设置输出工作区
	IWorkspacePtr pWo;
	IWorkspaceFactoryPtr pWSF(CLSID_ShapefileWorkspaceFactory);
	hr=pWSF->OpenFromFile((CComBSTR)m_OutputFeatureDir,NULL,&pWo);
	if(FAILED(hr))
	{
			AfxMessageBox( "输出路径不存在!");
				return;
	}
	IRasterAnalysisEnvironmentPtr pEnv(pSurfaceOp);
	hr = pEnv->putref_OutWorkspace(pWo);
	if(FAILED(hr))

	{
		AfxMessageBox("输出路径设置失败!");

		return;

	}
	//Contour
	CString str;
	m_edit_Contour_ContourInterval.GetWindowText(str);
	double interval=atof ( str );
	m_edit_ContourBaseContour. GetWindowText(str );
	double base= atof(str);
	VARIANT BASE;
	BASE.vt =VT_R8;
	BASE.dblVal=base;
	hr=pSurfaceOp->Contour(plnputDataset,interval,&BASE,&pOutput);
	if(FAILED(hr ))
	if(hr==-2147467259)
	{

		AfxMessageBox("等高线恢复无法进行，请更换表面数据!");
		return;
	}
	//重命名:因为Contour后的文件名为默认的，不符合要求
	IDatasetPtr pda(pOutput);
	VARIANT_BOOL CanRename;
	hr = pda->CanRename(&CanRename);
	if(FAILED(hr ))
	{
        return;
	}
	if( CanRename == VARIANT_TRUE)
	{
		hr=pda->Rename((CComBSTR)m_OutputFeatureName);
	
		return;
	
		AfxMessageBox("成功!");
	}
}




