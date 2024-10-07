// FormCommandView.cpp : implementation file
#include "stdafx.h"
#include "Tool.h"
#include "MainFrm.h"
#include "FormCommandView.h"
#include "ToolDoc.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CFormCommandView
IMPLEMENT_DYNCREATE(CFormCommandView, CFormView)

CFormCommandView::CFormCommandView()
: CFormView(CFormCommandView::IDD)
{
	//{{AFX_DATA_INIT(CFormCommandView)
	//}}AFX_DATA_INIT
}

CFormCommandView::~CFormCommandView()
{
}

void CFormCommandView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormCommandView)
	DDX_Control(pDX, IDC_RADIO_WIREFRAME, m_wireframe);
	DDX_Control(pDX, IDC_RADIO_FILLED, m_filled);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormCommandView, CFormView)
	//{{AFX_MSG_MAP(CFormCommandView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_MODEL_1, OnRadioWireFrame)
	ON_BN_CLICKED(IDC_RADIO_MODEL_2, OnRadioFilled)
	ON_BN_CLICKED(IDC_SHOOT, OnShoot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView diagnostics

#ifdef _DEBUG
void CFormCommandView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormCommandView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CToolDoc* CFormCommandView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}

#endif //_DEBUG

void CFormCommandView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_filled.SetCheck(1);	
}

// OnPaint
void CFormCommandView::OnPaint() 
{
	// Device context for painting
	CPaintDC dc(this); 
	// Options are stored in Application
	CToolApp *pApp = (CToolApp *)AfxGetApp();
}

// GetRenderView
CView *CFormCommandView::GetRenderView() 
{
	CToolApp *pApp = (CToolApp *)AfxGetApp();
	CMainFrame *pFrame = (CMainFrame *)pApp->m_pMainWnd;
	CView *pView = (CView *)pFrame->m_wndSplitter.GetPane(0,1);
	return pView;
}

// Model
void CFormCommandView::OnRadioWireFrame() 
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	this->GetRenderView()->InvalidateRect(NULL,FALSE); 
}

void CFormCommandView::OnRadioFilled() 
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	this->GetRenderView()->InvalidateRect(NULL,FALSE); 
}

void CFormCommandView::OnShoot() 
{
    CRenderView *pView = (CRenderView *)GetRenderView();
	pView->Shoot = !(pView->Shoot);
}
