// Tool.cpp 
// Created :
// Modified
#include "stdafx.h"
#include "Tool.h"
#include "DlgAbout.h"
#include "MainFrm.h"
#include "ToolDoc.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CToolApp
CToolDoc  *MyDocument;

BEGIN_MESSAGE_MAP(CToolApp, CWinApp)
	//{{AFX_MSG_MAP(CToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

// CToolApp construction
CToolApp::CToolApp()
{
	// Options
	m_OptionColorGlBack = RGB(0,0,255);
}

// The one and only CToolApp object
CToolApp theApp;

// CToolApp initialization
BOOL CToolApp::InitInstance()
{
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("3D Toolbox"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;

	// create main SDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	
	pDocTemplate = new CSingleDocTemplate(
		IDR_MODELTYPE,
		RUNTIME_CLASS(CToolDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CRenderView));
	AddDocTemplate(pDocTemplate);

	// The main window has been initialized, so show and update it.	
	pMainFrame->ShowWindow(SW_SHOW);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// App command to run the dialog
void CToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
