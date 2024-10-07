#include "stdafx.h"
#include "tool.h"

#include "mainfrm.h"
#include "tooldoc.h"
#include "renderview.h"
#include "dlgabout.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolApp
GLMmodel *  model;
BEGIN_MESSAGE_MAP(CToolApp, CWinApp)
	//{{AFX_MSG_MAP(CToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolApp construction

CToolApp::CToolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CToolApp object
CToolApp theApp;

// CToolApp initialization
BOOL CToolApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Enable3dControls();

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CToolDoc),
		RUNTIME_CLASS(CMainFrame),          // standard SDI frame
		RUNTIME_CLASS(CRenderView));
	AddDocTemplate(pDocTemplate);

	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.	
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// create a new (empty) document
//	OnFileNew();

	return TRUE;
}

// App command to run the dialog
void CToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CToolApp commands
CDocument* CToolApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	model = glmReadOBJ((char *)lpszFileName);
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 90);
	CMainFrame *pFrame = (CMainFrame *)m_pMainWnd;
	CView *pView = (CView *)pFrame->m_wndSplitter.GetPane(0,1);
	pView->Invalidate(FALSE);
	return NULL;
}
