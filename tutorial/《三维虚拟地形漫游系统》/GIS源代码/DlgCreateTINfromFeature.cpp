// DlgCreateTINfromFeature.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgCreateTINfromFeature.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateTINfromFeature dialog


CDlgCreateTINfromFeature::CDlgCreateTINfromFeature(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateTINfromFeature::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreateTINfromFeature)
	m_edit_TINInputs = _T("");
	m_edit_TINOutput = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCreateTINfromFeature::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateTINfromFeature)
	DDX_Control(pDX, IDC_EDIT_TIN_OUTPUT, m_Control_Output_Path);
	DDX_Control(pDX, IDC_COMBO_TIN_HEIGHT_FIELD, m_combo_TINHeightField);
	DDX_Control(pDX, IDC_COMBO_TIN_TRIANGU, m_combo_TINTriangulateAs);
	DDX_Text(pDX, IDC_EDIT_TIN_INPUTS, m_edit_TINInputs);
	DDX_Text(pDX, IDC_EDIT_TIN_OUTPUT, m_edit_TINOutput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateTINfromFeature, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateTINfromFeature)
	ON_CBN_SELCHANGE(IDC_COMBO_TIN_HEIGHT_FIELD, OnSelchangeComboTinHeightField)
	ON_CBN_SELCHANGE(IDC_COMBO_TIN_TRIANGU, OnSelchangeComboTinTriangu)
	ON_BN_CLICKED(IDC_BUTTON_TIN_INPUTS, OnButtonTinInputs)
	ON_BN_CLICKED(IDC_BUTTON_SAVEFILEPATH, OnButtonSavefilepath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateTINfromFeature message handlers

BOOL CDlgCreateTINfromFeature::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_combo_TINTriangulateAs.SetCurSel(0);
	m_selHIndex=0;
	m_selTIndex=0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateTINfromFeature::OnSelchangeComboTinHeightField() 
{
	// TODO: Add your control notification handler code here
	 if(m_combo_TINHeightField. GetCurSel()!=CB_ERR)
       m_selHIndex=m_combo_TINHeightField.GetCurSel();	
	
}

void CDlgCreateTINfromFeature::OnSelchangeComboTinTriangu() 
{
	// TODO: Add your control notification handler code here
	if(m_combo_TINTriangulateAs.GetCurSel()!=CB_ERR)
        m_selTIndex=m_combo_TINTriangulateAs.GetCurSel();

	
}

void CDlgCreateTINfromFeature::OnButtonTinInputs() 
{
	// TODO: Add your control notification handler code here
	//打开对话框
	::OleInitialize(NULL);//组件操作初始化
	IGxDialogPtr        ipGxDialog(CLSID_GxDialog);
	IGxObjectFilterPtr  ipGxObjectFilter( CLSID_GxFilterFeatureClasses);
	HRESULT             hr=ipGxDialog->putref_ObjectFilter( ipGxObjectFilter);
	if(FAILED(hr)) return;
	hr=ipGxDialog->put_Title(CComBSTR("选择特征类"));
	if(FAILED(hr)) return;
	IEnumGxObjectPtr ipEnumGxObject;
	VARIANT_BOOL bResult;
	hr = ipGxDialog->DoModalOpen(0,&ipEnumGxObject,&bResult);
	if(FAILED(hr)) return;
	if(bResult==VARIANT_FALSE)return;
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
			m_ipfeat=ipFeatureClass;
			CComBSTR bstrName;//获得输入点层的全名
			ipGxObject->get_FullName(&bstrName);
			CString str( bstrName);
			m_edit_TINInputs=str;
			UpdateData(FALSE);
			//将层ipFeaureClass的所有字段添加到combo box控件列表中
			m_combo_TINHeightField.ResetContent();	//先清空
			long lFieldCount;
			IFieldsPtr pFClassPointFields;
			ipFeatureClass->get_Fields(&pFClassPointFields);
			pFClassPointFields->get_FieldCount(&lFieldCount);
			for(int i=0;i<lFieldCount;i++)
			{
				CComBSTR pname;
				IFieldPtr pField;
				hr = pFClassPointFields->get_Field(i,&pField);
				if ( FAILED(hr)) return;
				hr=pField->get_Name(&pname);
				if( FAILED(hr)) return;
				CString ppname(pname);
				m_combo_TINHeightField.AddString(ppname);
			}
			m_combo_TINHeightField.SetCurSel(0);
			//初始化显示comboBox

		}		
	
	}

	
}

void CDlgCreateTINfromFeature::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_ipfeat!=NULL)
	{
       CreateTINfromFeature(m_ipfeat);
	}
	else
	{
		AfxMessageBox("没有输入层!");
		return;
	}

	
	CDialog::OnOK();
}
void CDlgCreateTINfromFeature::CreateTINfromFeature(IFeatureClass *ipfeat)
{
	//获得feature class的空间引用来构建TIN
		IGeoDatasetPtr pGeoDataset(ipfeat); 
		IEnvelopePtr pExtent;
		HRESULT hr=pGeoDataset->get_Extent(&pExtent);
		// TIN将使用通过pExten，设置的空间引用
		ISpatialReferencePtr ipSpatR;		 
		hr= pGeoDataset->get_SpatialReference(&ipSpatR);
		hr=pExtent->putref_SpatialReference(ipSpatR);//创建TIN对象并且得到ITinEdit接口
		ITinEditPtr pTinEdit(CLSID_Tin);
		//初始化TIN
		hr=pTinEdit->InitNew(pExtent);
		//注意:到此为止虽然已经实际生成了TIN，但是此时的TIN是一个没有高程。
		
		//这样它就不是真正的高程模型，因此，通过下面步骤将feature中的高程信
		//刚刚生成的TIN，并且保存至硬盘。*/
		//获得高程字段
		IFieldsPtr pfields;
		IFieldPtr pHeightField;
		hr=ipfeat->get_Fields(&pfields);
		hr=pfields->get_Field(m_selHIndex,&pHeightField);
		if (FAILED(hr)) return;
		//调用相应的函数将shape文件(含高程信息)增加到TIN中
		
		if(m_selTIndex==0)
		 hr= pTinEdit->AddFromFeatureClass(ipfeat,NULL,pHeightField,NULL,esriTinMassPoint);
		if(m_selTIndex==1)    
			hr=pTinEdit->AddFromFeatureClass(ipfeat,NULL, pHeightField,NULL,esriTinHardLine);
		if(m_selTIndex==2)    
			hr=pTinEdit->AddFromFeatureClass(ipfeat,NULL,pHeightField,NULL, esriTinSoftLine);
		if(FAILED(hr))
		{

			AfxMessageBox("创建TIN失败");
			return;
		}
		//保存TIN
		ITinPtr ipTin(pTinEdit);		
		if ( ipTin!=NULL)		
		{
				        
	            HRESULT hr;    
				CMainFrame *pFrame=(CMainFrame*)AfxGetMainWnd();  //huoqu  
				CMy3D0214View  *pView=(CMy3D0214View*) pFrame->GetActiveView(); 
				if(!pView->GetSceneFromView(&m_ipScene))	
				{	
					AfxMessageBox("NO Scene");		
					return  ;	
				}
	 
			 
				//构造TIN图层			
				ITinLayerPtr pTLayer( CLSID_TinLayer);			
				hr=pTLayer->putref_Dataset(ipTin);	
				BSTR fName;
                ipfeat->get_AliasName(&fName);//以输入点文件名为输出tin 的默认名
				hr=pTLayer->put_Name(CComBSTR(fName)); 	
				ILayerPtr	m_ipLayer=pTLayer;			
				//增加TIN图层
      			hr=m_ipScene->AddLayer(m_ipLayer,VARIANT_TRUE);		
				hr=pTinEdit->SaveAs(CComBSTR(m_edit_TINOutput));
				if(FAILED(hr))
				{	
					AfxMessageBox("保存TIN失败!");
					return;
				}
		
				AfxMessageBox("成功!");
		}

}

void CDlgCreateTINfromFeature::OnButtonSavefilepath() 
{
	// TODO: Add your control notification handler code here
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
			m_Control_Output_Path.SetWindowText(strPath);
			AfxMessageBox(strPath,MB_YESNO);
			//AfxMessageBox("Do you really want to exit?",MB_YESNO);
		}
	
}
