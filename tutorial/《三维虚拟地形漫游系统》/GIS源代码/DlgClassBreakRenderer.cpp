// DlgClassBreakRenderer.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "DlgClassBreakRenderer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgClassBreakRenderer dialog


CDlgClassBreakRenderer::CDlgClassBreakRenderer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClassBreakRenderer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgClassBreakRenderer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgClassBreakRenderer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgClassBreakRenderer)
	DDX_Control(pDX, IDC_COMBO_CLASSES_NUM, m_combo_classesNum);
	DDX_Control(pDX, IDC_BUTTON_END_COLOR, m_endcolor);
	DDX_Control(pDX, IDC_BUTTON_START_COLOR, m_startcolor);
	DDX_Control(pDX, IDC_LIST_COLOR_RANGE, m_list_colorrange);
	//DDX_Control(pDX, IDC_BUTTON1, m_b);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgClassBreakRenderer, CDialog)
	//{{AFX_MSG_MAP(CDlgClassBreakRenderer)
	ON_BN_CLICKED(IDC_BUTTON_COLOR_RAMP, OnButtonColorRamp)
	ON_CBN_SELCHANGE(IDC_COMBO_CLASSES_NUM, OnSelchangeComboClassesNum)
	ON_BN_CLICKED(IDC_BUTTON_START_COLOR, OnButtonStartColor)
	ON_BN_CLICKED(IDC_BUTTON_END_COLOR, OnButtonEndColor)
	ON_LBN_SELCHANGE(IDC_LIST_COLOR_RANGE, OnSelchangeListColorRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgClassBreakRenderer message handlers

void CDlgClassBreakRenderer::OnButtonColorRamp() 
{
	// TODO: Add your control notification handler code here
	m_list_colorrange.ResetContent();
	HRESULT hr;
 	
	CreateRampColor(m_ClassNum);
 
	m_EnumColors->Reset();

	OLE_COLOR rgb;

	for( long i=0;i<m_ClassNum;i++)

	{
    
		IColorPtr pColor; 
		IUnknownPtr pUnk;
		pUnk=pColor;
	    hr=m_ipArray->get_Element((long)i,&pUnk);
        pColor=pUnk;
        pColor->get_RGB(&rgb);
        m_list_colorrange.AddString(_T(""),rgb);

	}
 
	 m_list_colorrange.SetCurSel(0);
	 m_SelIndex=0;
}
BOOL CDlgClassBreakRenderer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_combo_classesNum.SetCurSel(4);
    m_ClassNum=5;
	OnButtonColorRamp() ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgClassBreakRenderer::OnSelchangeComboClassesNum() 
{
	// TODO: Add your control notification handler code here
	m_ClassNum=m_combo_classesNum.GetCurSel()+1;
    OnButtonColorRamp();
	Invalidate();

	
}
void CDlgClassBreakRenderer::CreateRampColor(double nSize)
{
	m_ipArray.CreateInstance(CLSID_Array);
	HRESULT hr;
    //建一个AlgorithmicColorRamp对象，
    //获得它的IAlgorithmicColorRamp接口
    IAlgorithmicColorRampPtr pAlgoRamp(CLSID_AlgorithmicColorRamp);
	hr=pAlgoRamp->put_Size((long)nSize);

	//设置属性

	IRgbColorPtr pColor(CLSID_RgbColor);

 	pColor->put_RGB(OLE_COLOR(m_startcolor.GetColor()));
	pAlgoRamp->put_FromColor(pColor);

	pColor->put_RGB(OLE_COLOR(m_endcolor.GetColor()));
    pAlgoRamp->put_ToColor( pColor);
    pAlgoRamp->put_Algorithm(esriHSVAlgorithm);
    VARIANT_BOOL vb=VARIANT_TRUE;
    pAlgoRamp->CreateRamp(&vb);
    if(vb) 
		pAlgoRamp->get_Colors(&m_EnumColors);
      m_EnumColors->Reset();
    for( long i=0;i<m_ClassNum;i++)

	{
    
		IColorPtr pColor;    
		m_EnumColors->Next(&pColor); //取出颜色  
		m_ipArray->Add(pColor);  //颜色添加到IArray    

	}

	
}
BOOL CDlgClassBreakRenderer::GetLayerFromCurrentScene(ILayer **ipLayer)
{
	HRESULT hr;
    CMainFrame *pFrame=(CMainFrame*)AfxGetMainWnd();
    CMy3D0214View  *pView=(CMy3D0214View*) pFrame->GetActiveView(); 
	if(!pView->GetSceneFromView(&m_ipScene))
	{
		AfxMessageBox("NO Scene");
		return FALSE;
	}
	hr=m_ipScene->get_Layer(2,ipLayer);
	if(FAILED(hr)) return FALSE;
	return TRUE ;

}
void CDlgClassBreakRenderer::RasterClassBreak()
{HRESULT hr;    
    if(m_ipLayer == NULL) return;
	IRasterLayerPtr ipRasLyr(m_ipLayer);
    IRasterClassifyColorRampRendererPtr pClassRen(CLSID_RasterClassifyColorRampRenderer);
	IRasterRendererPtr pRasRen(pClassRen);
	IRasterPtr pRaster;
	ipRasLyr->get_Raster(&pRaster);
	hr=pRasRen->putref_Raster(pRaster);
	hr=pClassRen->put_ClassCount(m_ClassNum);
	hr=pRasRen->Update();
	IFillSymbolPtr pFSymbol(CLSID_SimpleFillSymbol);
	//CreateRampColor(m_ClassNum);
	m_EnumColors->Reset();//Resets the enumerator to the beginning.
	for ( long i=0;i<m_ClassNum;i++)
	{
    
		IColorPtr pColor;
		
        IUnknownPtr pUnk;
	    m_ipArray->get_Element(i,&pUnk);
        pColor=pUnk;	


		pFSymbol->put_Color(pColor);    
		ISymbolPtr pSymbol(pFSymbol); 
		hr=pClassRen->put_Symbol(i,pSymbol);
		
	//	pClassRen->put_Label(i, CComBSTR("Class"+CString (i)));
	}

	IRgbColorPtr pColor( CLSID_RgbColor);
	//更新渲染效果，并应用到图层
	hr=pRasRen->Update();
	hr=ipRasLyr->putref_Renderer( pRasRen);
	ISceneGraphPtr ipSceneG;
	hr=m_ipScene->get_SceneGraph(&ipSceneG);
	ISceneViewerPtr ppViewer;
	hr=ipSceneG->get_ActiveViewer(&ppViewer);
    //为了刷新
	hr=m_ipScene->DeleteLayer(ipRasLyr);
	hr=m_ipScene->AddLayer(ipRasLyr,VARIANT_TRUE);	

}
void CDlgClassBreakRenderer::TinClassBreak()//Tin的分层设色过程函数
{
  
    HRESULT hr;
    if(m_ipLayer==NULL) return;
    ITinLayerPtr ipTLyr(m_ipLayer);
	ITinPtr ipT;
	hr=ipTLyr->get_Dataset(&ipT);
 	//获得Zmax , Zmin ;
	double Zmax,Zmin;
	IEnvelopePtr ipEnv;
	hr=ipT->get_Extent(&ipEnv);
	hr=ipEnv->get_ZMax(&Zmax);
	hr=ipEnv->get_ZMin(&Zmin);
	double d;
	double dint;
	//创建Tin渲染对象
	ITinColorRampRendererPtr pTinRender(CLSID_TinElevationRenderer);
	d=Zmax-Zmin;
	dint=d/m_ClassNum;
	hr=pTinRender->put_BreakCount(m_ClassNum);
	hr=pTinRender->put_MinimumBreak(Zmin);
	hr=pTinRender->put_Break(0,Zmin+dint);
	//hr=pTinRender->put_MinimumBreak(Zmin); 
 	for(int i=1;i<m_ClassNum;i++)
	{
		double pValue;    
		pTinRender->get_Break(i-1,&pValue);    
		pTinRender->put_Break(i,pValue+dint);
	}

	//为每个渲染赋颜色
	ISimpleFillSymbolPtr pSym(CLSID_SimpleFillSymbol);
	IColorPtr pColor;
	IClassBreaksUIPropertiesPtr pC(pTinRender);
	hr=m_EnumColors->Reset();
	double min,value;
	pTinRender->get_MinimumBreak(&min);
	hr=pC->put_LowBreak(0,min); 
	//为每段渲染添加相应的颜色
    IUnknownPtr pUnk;
	for(i=0;i<m_ClassNum;i++)
	{
    
			/////////////////////////////////////////////////////////////
	        m_ipArray->get_Element(i,&pUnk);
            pColor=pUnk;	
            /////////////////////////////////////////////////////////////
			pSym->put_Color(pColor);   
			pTinRender->put_Symbol(i,(ISymbolPtr)pSym);    
			pTinRender->get_Break(i-1,&value); 
			
			CString strs;
			strs.Format("%f",(double)(Zmax-dint*i));

	    	hr=pTinRender->put_Label(i, CComBSTR(strs));
			pC->put_LowBreak(i,value);
	}
   

	ITinRendererPtr pTRend(pTinRender);
	//删除以前的渲染效果
	ITinRendererPtr ipRender; 
	long count;
	ipTLyr->get_RendererCount(&count); 
	for(i=0;i<count;i++)
	{    
			hr=ipTLyr->GetRenderer(i,&ipRender);    
			CComBSTR name;    
			hr=ipRender->get_Name(&name);    
			if(name=="Elevation") hr=ipTLyr->DeleteRenderer(ipRender);
			if(name=="Faces") hr=ipTLyr->DeleteRenderer(ipRender);
	}

	//添加新的渲染，并设为可视
	hr=pTRend->putref_Tin(ipT);

	hr=ipTLyr->AddRenderer( pTRend);
	hr=ipTLyr->GetRenderer( count-1,&ipRender);	
	hr=ipRender->put_Visible(VARIANT_TRUE);
 
	//为了刷新
	m_ipScene->DeleteLayer(ipTLyr);
	m_ipScene->AddLayer((ILayerPtr)ipTLyr,VARIANT_TRUE); 
}


void CDlgClassBreakRenderer::OnButtonStartColor() 
{
	// TODO: Add your control notification handler code here
	 OnButtonColorRamp();
	 Invalidate();	
}

void CDlgClassBreakRenderer::OnButtonEndColor() 
{
	// TODO: Add your control notification handler code here
	 OnButtonColorRamp();
	 Invalidate();
}

void CDlgClassBreakRenderer::OnOK() 
{
	// TODO: Add extra validation here
	if (m_ipLayer==NULL)	
		GetLayerFromCurrentScene(&m_ipLayer);
	ITinLayerPtr pTLayer(m_ipLayer);
	if (pTLayer!=NULL) 
	{

		TinClassBreak()	;
	}
	else
	{
		RasterClassBreak();
        delete pTLayer;
		//删除对象，释放内存,没有成功实例化的对象，不能自动释放，会引起内存溢出
	}

	
	CDialog::OnOK();
}

void CDlgClassBreakRenderer::OnSelchangeListColorRange() 
{
	// TODO: Add your control notification handler code here
	m_SelIndex=m_list_colorrange.GetCaretIndex();
  	Invalidate();
}
