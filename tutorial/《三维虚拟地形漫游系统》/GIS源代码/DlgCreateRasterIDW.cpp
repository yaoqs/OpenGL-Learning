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
	//��������ΧĬ��ѡ������Ϊ"�ɱ��
	m_combo_IDWsearchRadiusType.SetCurSel(0);
	m_edit_settings1.SetWindowText("12");
	m_selIndex=0;
//	m_combo_IDWZvalueField. AddString("�ɱ��");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateRasterIDW::OnSelchangeComboIdwSearchRadiusType() 
{
	// TODO: Add your control notification handler code here
	if(m_combo_IDWsearchRadiusType.GetCurSel()!=CB_ERR)
	{
		m_selIndex=m_combo_IDWsearchRadiusType.GetCurSel();
		if ( m_selIndex == 0 ) //**��ѡ��"�ɱ��"
		{
			m_static_settings1.SetWindowText("�����Ŀ:");
			m_static_settings2.SetWindowText("������:");
			m_edit_settings1.SetWindowText("12");
			m_edit_settings2.SetWindowText("");
		}
		if( m_selIndex ==1) //*��ѡ��"�̶���"
		{
			m_static_settings1.SetWindowText("����:");
			m_static_settings2.SetWindowText("���ٵ���:");
			m_edit_settings1.SetWindowText("");
			m_edit_settings2.SetWindowText("0");			
		}
	}
}

void CDlgCreateRasterIDW::OnButtonIdwAddpointlayer() 
{
	// TODO: Add your control notification handler code here
		::OleInitialize(NULL);//���������ʼ��
	//�򿪶Ի���
	IGxDialogPtr ipGxDialog(CLSID_GxDialog);

	 IGxObjectFilterPtr ipGxObjectFilter(CLSID_GxFilterPointFeatureClasses);	  
		//ע��ʹ����GxFilterPointFeatureClasses
		//���Թ��˵������������㹦��ֻ�õ��ڲ����Ҫ
    HRESULT hr=ipGxDialog->putref_ObjectFilter(ipGxObjectFilter);
			
	//HRESULT hr;

	if(FAILED(hr)) return;
	
	hr=ipGxDialog->put_Title(::SysAllocString(L"ѡ������"));
	
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
			CComBSTR bstrName ;//������˵���ȫ��
			ipGxObject->get_FullName(&bstrName);
			CString str(bstrName);
			m_edit_IDWPointInput=str;
			UpdateData(FALSE);
			//�����ipFeatureClass�������ֶ���ӵ���ombo box�ؼ��б���
			m_combo_IDWZvalueField.ResetContent();//�����
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
			//��ʼ����ʾ��omboBox(3)
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
		AfxMessageBox("û�����˵��!");	return;
	}
	CDialog::OnOK();
}
void CDlgCreateRasterIDW::IDWOp(IFeatureClass * ipfeatureclass) 
{
	IFeatureClassDescriptorPtr pFDescr(CLSID_FeatureClassDescriptor);
		//���ѡ���ֶε��ַ���
		int index=m_combo_IDWZvalueField.GetCurSel();
		CString sFieldName;
		m_combo_IDWZvalueField.GetLBText(index,sFieldName);
		CComBSTR s=(CComBSTR)sFieldName;
		HRESULT hr;
		hr=pFDescr->Create(ipfeatureclass,NULL,s);
		//����RasterlnterpolationOp����

		IInterpolationOpPtr pIntOp(CLSID_RasterInterpolationOp);
		//�������RASTER�����С��Ĭ�ϵ�RASTER����ռ䷶Χ������������ͬ
		
		IRasterAnalysisEnvironmentPtr pEnv(pIntOp);
		VARIANT cs;		
		cs.vt=VT_R8;
		cs .dblVal=m_edit_IDWInputCellsize;	//�Ի�������cell �ߴ�	
		hr = pEnv->SetCellSize(esriRasterEnvValue,&cs);

		//������Χ����
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


			//ʹ��FeatureClassDescriptor��ΪIInterpolationOp�����˶�������ڲ����

			IGeoDatasetPtr pFDescr2Geo(pFDescr);
			IGeoDatasetPtr pOutRaster2Geo;		
			hr=pIntOp->IDW(pFDescr2Geo,m_edit_IDWPower,pRadius,NULL,&pOutRaster2Geo);
			if(FAILED("hr"))
			{
				AfxMessageBox ("�ڲ����ʧ��!");
				return;
			}    
			IRasterPtr pOutRaster(pOutRaster2Geo);    
			IRasterBandCollectionPtr pRasBandC(pOutRaster);    
			//���RASTER·�������Ƽ����ʽ����    
			IWorkspaceFactoryPtr pWSF(CLSID_RasterWorkspaceFactory);    
			IWorkspacePtr pWS; 
			hr=	pWSF->OpenFromFile((CComBSTR)m_edit_IDWOutputRaster,NULL,&pWS); 
	    	if(FAILED(hr)) AfxMessageBox("failed");
			//RASTER��ʽ����Ϊ"GRID" , " TIFF"����"IMAGINE Image"    
			IDatasetPtr prasterdataset;    
			hr=pRasBandC->SaveAs(CComBSTR("Raster"),pWS,CComBSTR("GRID"),&prasterdataset);    
			if(FAILED( hr))
    		{        
				AfxMessageBox ( " DEM����ʧ��!");    
			}

}
void CDlgCreateRasterIDW::OnButtonSelsaverasterpath() 
{
	// TODO: Add your control notification handler code here
	    CString strFilter="File Folder(*.File Folder)|*.File Folder||";//���ô��ļ��Ĺ�������
		CString strTitle="ѡ�񱣴�·��";
        DWORD MAXFILE = 2412; // allocate enough memory space
    	CString strPath,strInit,strTemp;
        CFileDialog pDlg(FALSE,0,0,OFN_ALLOWMULTISELECT| OFN_EXPLORER | OFN_LONGNAMES|
                        OFN_FILEMUSTEXIST |OFN_HIDEREADONLY,strFilter, NULL);

        //���öԻ���               
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
