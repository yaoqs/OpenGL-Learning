// DlgCreateRasterIDW.cpp : implementation file
//
#include "stdafx.h"
#include "3D0214.h"
#include "DlgCreateRasterIDW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateRasterIDW dialog


CDlgCreateRasterIDW::CDlgCreateRasterIDW(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateRasterIDW::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreateRasterIDW)
	m_edit_IDWInputCellsize = 0.0;
	m_edit_IDWOutputRaster = _T("");
	m_edit_IDWPointInput = _T("");
	m_edit_IDWPower = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgCreateRasterIDW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateRasterIDW)
	DDX_Control(pDX, IDC_EDIT_IDW_OUTPUT_RASTER, m_Control_IDWOutputRaster);
	DDX_Control(pDX, IDC_STATIC_Set2, m_static_settings2);
	DDX_Control(pDX, IDC_STATIC_Set1, m_static_settings1);
	DDX_Control(pDX, IDC_EDIT_IDW_RADIUSSETTINGS_2, m_edit_settings2);
	DDX_Control(pDX, IDC_EDIT_IDW_RADIUSSETTINGS_1, m_edit_settings1);
	DDX_Control(pDX, IDC_COMBO_IDW_SEARCH_RADIUS_TYPE, m_combo_IDWsearchRadiusType);
	DDX_Control(pDX, IDC_COMBO_IDW_ZVALUE_FIELD, m_combo_IDWZvalueField);
	DDX_Text(pDX, IDC_EDIT_IDW_INPUT_CELL_SIZE, m_edit_IDWInputCellsize);
	DDX_Text(pDX, IDC_EDIT_IDW_OUTPUT_RASTER, m_edit_IDWOutputRaster);
	DDX_Text(pDX, IDC_EDIT_IDW_POINT_INPUT, m_edit_IDWPointInput);
	DDX_Text(pDX, IDC_EDIT_IDW_WIGHT, m_edit_IDWPower);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateRasterIDW, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateRasterIDW)
	ON_CBN_SELCHANGE(IDC_COMBO_IDW_SEARCH_RADIUS_TYPE, OnSelchangeComboIdwSearchRadiusType)
	ON_BN_CLICKED(IDC_BUTTON_IDW_ADDPOINTLAYER, OnButtonIdwAddpointlayer)
	ON_BN_CLICKED(IDC_BUTTON_SELSAVERASTERPATH, OnButtonSelsaverasterpath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateRasterIDW message handlers

BOOL CDlgCreateRasterIDW::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//将搜索范围默认选项设置为"可变的
	m_combo_IDWsearchRadiusType.SetCurSel(0);
	m_edit_settings1.SetWindowText("12");
	m_selIndex=0;
//	m_combo_IDWZvalueField. AddString("可变的");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateRasterIDW::OnSelchangeComboIdwSearchRadiusType() 
{
	// TODO: Add your control notification handler code here
	if(m_combo_IDWsearchRadiusType.GetCurSel()!=CB_ERR)
	{
		m_selIndex=m_combo_IDWsearchRadiusType.GetCurSel();
		if ( m_selIndex == 0 ) //**当选中"可变的"
		{
			m_static_settings1.SetWindowText("点的数目:");
			m_static_settings2.SetWindowText("最大距离:");
			m_edit_settings1.SetWindowText("12");
			m_edit_settings2.SetWindowText("");
		}
		if( m_selIndex ==1) //*当选中"固定的"
		{
			m_static_settings1.SetWindowText("距离:");
			m_static_settings2.SetWindowText("最少点数:");
			m_edit_settings1.SetWindowText("");
			m_edit_settings2.SetWindowText("0");			
		}
	}
}

void CDlgCreateRasterIDW::OnButtonIdwAddpointlayer() 
{
	// TODO: Add your control notification handler code here
		::OleInitialize(NULL);//组件操作初始化
	//打开对话框
	IGxDialogPtr ipGxDialog(CLSID_GxDialog);

	 IGxObjectFilterPtr ipGxObjectFilter(CLSID_GxFilterPointFeatureClasses);	  
		//注意使用了GxFilterPointFeatureClasses
		//可以过滤点特征集，满足功能只用点内插的需要
    HRESULT hr=ipGxDialog->putref_ObjectFilter(ipGxObjectFilter);
			
	//HRESULT hr;

	if(FAILED(hr)) return;
	
	hr=ipGxDialog->put_Title(::SysAllocString(L"选择数据"));
	
	if(FAILED(hr)) return;
	IEnumGxObjectPtr ipEnumGxObject;
	VARIANT_BOOL bResult;
	hr=ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);
	if(FAILED(hr)) return;
	if(bResult==VARIANT_FALSE) return;
	hr=ipEnumGxObject->Reset();///
	if(FAILED(hr)) return;
	IGxObjectPtr ipGxObject;
		
	while(!ipEnumGxObject->Next( &ipGxObject))
	{
		IGxDatasetPtr ipGxDataset( ipGxObject);
		if(ipGxDataset!=0)
		{
			IDatasetPtr ipDataset;
			hr=ipGxDataset->get_Dataset( &ipDataset);
			if(FAILED(hr)) return;
			IFeatureClassPtr ipFeatureClass(ipDataset);
			m_ipfeat=ipFeatureClass;
			CComBSTR bstrName ;//获得输人点层的全名
			ipGxObject->get_FullName(&bstrName);
			CString str(bstrName);
			m_edit_IDWPointInput=str;
			UpdateData(FALSE);
			//将点层ipFeatureClass的所有字段添加到。ombo box控件列表中
			m_combo_IDWZvalueField.ResetContent();//先清空
			HRESULT hr;
			long lFieldCount;
			IFieldsPtr pFClassPointFields;
			m_ipfeat->get_Fields(&pFClassPointFields);
			pFClassPointFields->get_FieldCount(&lFieldCount);
			for(int i=0;i<lFieldCount;i++)
			{    
				CComBSTR pname;    
				IFieldPtr pField;   
				hr=pFClassPointFields->get_Field(i,&pField);    
				if(FAILED(hr )) return;   
				hr=pField->get_Name(&pname);    
				if( FAILED(hr)) return;   
				CString ppname(pname);    
				m_combo_IDWZvalueField. AddString(ppname);

			}

			m_combo_IDWZvalueField.SetCurSel(0);
			//初始化显示。omboBox(3)
		}
	}
}

void CDlgCreateRasterIDW::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_ipfeat!=NULL)	
	{
			IDWOp(m_ipfeat);
	}
	else
	{
		AfxMessageBox("没有输人点层!");	return;
	}
	CDialog::OnOK();
}
void CDlgCreateRasterIDW::IDWOp(IFeatureClass * ipfeatureclass) 
{
	IFeatureClassDescriptorPtr pFDescr(CLSID_FeatureClassDescriptor);
		//获得选中字段的字符串
		int index=m_combo_IDWZvalueField.GetCurSel();
		CString sFieldName;
		m_combo_IDWZvalueField.GetLBText(index,sFieldName);
		CComBSTR s=(CComBSTR)sFieldName;
		HRESULT hr;
		hr=pFDescr->Create(ipfeatureclass,NULL,s);
		//创建RasterlnterpolationOp对象

		IInterpolationOpPtr pIntOp(CLSID_RasterInterpolationOp);
		//设置输出RASTER网格大小，默认的RASTER输出空间范围和输人数据相同
		
		IRasterAnalysisEnvironmentPtr pEnv(pIntOp);
		VARIANT cs;		
		cs.vt=VT_R8;
		cs .dblVal=m_edit_IDWInputCellsize;	//对话框输入cell 尺寸	
		hr = pEnv->SetCellSize(esriRasterEnvValue,&cs);

		//搜索范围设置
		IRasterRadiusPtr pRadius(CLSID_RasterRadius);
 		if(m_selIndex==0)
		{
			CString strl;
			m_edit_settings1.GetWindowText(strl);
			long count=atoi(strl); CString str2;
			m_edit_settings2.GetWindowText(str2);
			double distance=atof ( str2);

			VARIANT dis;
			dis.vt=VT_R8;
			dis. dblVal=distance;    
			hr=pRadius->SetVariable(count,&dis);
		}
 		if(m_selIndex==1)
		{     
			CString str1,str2;    
			m_edit_settings1.GetWindowText(str1);    
			double distance=atof( str1);    
			m_edit_settings2.GetWindowText(str2);
    		long count=atoi(str2);    
			VARIANT cou;
			cou. vt=VT_I4;
			cou.lVal=count;
			hr=pRadius->SetFixed(distance,&cou); 
		}


			//使用FeatureClassDescriptor作为IInterpolationOp的输人对象进行内插操作

			IGeoDatasetPtr pFDescr2Geo(pFDescr);
			IGeoDatasetPtr pOutRaster2Geo;		
			hr=pIntOp->IDW(pFDescr2Geo,m_edit_IDWPower,pRadius,NULL,&pOutRaster2Geo);
			if(FAILED("hr"))
			{
				AfxMessageBox ("内插操作失败!");
				return;
			}    
			IRasterPtr pOutRaster(pOutRaster2Geo);    
			IRasterBandCollectionPtr pRasBandC(pOutRaster);    
			//输出RASTER路径、名称及其格式设置    
			IWorkspaceFactoryPtr pWSF(CLSID_RasterWorkspaceFactory);    
			IWorkspacePtr pWS; 
			hr=	pWSF->OpenFromFile((CComBSTR)m_edit_IDWOutputRaster,NULL,&pWS); 
	    	if(FAILED(hr)) AfxMessageBox("failed");
			//RASTER格式可以为"GRID" , " TIFF"或者"IMAGINE Image"    
			IDatasetPtr prasterdataset;    
			hr=pRasBandC->SaveAs(CComBSTR("Raster"),pWS,CComBSTR("GRID"),&prasterdataset);    
			if(FAILED( hr))
    		{        
				AfxMessageBox ( " DEM保存失败!");    
			}

}
void CDlgCreateRasterIDW::OnButtonSelsaverasterpath() 
{
	// TODO: Add your control notification handler code here
	    CString strFilter="File Folder(*.File Folder)|*.File Folder||";//设置打开文件的过滤条件
		CString strTitle="选择保存路径";
        DWORD MAXFILE = 2412; // allocate enough memory space
    	CString strPath,strInit,strTemp;
        CFileDialog pDlg(FALSE,0,0,OFN_ALLOWMULTISELECT| OFN_EXPLORER | OFN_LONGNAMES|
                        OFN_FILEMUSTEXIST |OFN_HIDEREADONLY,strFilter, NULL);

        //设置对话框               
        pDlg.m_ofn.nMaxFile = MAXFILE; // set the buffer size        
        pDlg.m_ofn.lpstrTitle=strTitle;
        pDlg.m_ofn.lpstrInitialDir=strInit;
		char* buf = new char[MAXFILE];
		pDlg.m_ofn.lpstrFile = buf;
		pDlg.m_ofn.lpstrFile[0] = NULL;
		if(pDlg.DoModal()== IDOK)
		{
			//POSITION pos = pDlg.GetStartPosition();	
			strPath=pDlg.GetPathName();
			//strPath=pDlg.GetFolderPath();
			m_Control_IDWOutputRaster.SetWindowText(strPath);
			AfxMessageBox(strPath,MB_YESNO);
			//AfxMessageBox("Do you really want to exit?",MB_YESNO);
		}
}
