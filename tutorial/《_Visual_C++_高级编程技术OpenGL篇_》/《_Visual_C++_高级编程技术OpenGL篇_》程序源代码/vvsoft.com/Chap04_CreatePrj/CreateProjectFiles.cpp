// CreateProjectFiles.cpp : 定义应用程序中类的行为
#include "stdafx.h"
#include "CreateProjectFiles.h"
#include "CreateProjectFilesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CCreateProjectFilesApp, CWinApp)
	//{{AFX_MSG_MAP(CCreateProjectFilesApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		// DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

// CCreateProjectFilesApp类的构造函数
CCreateProjectFilesApp::CCreateProjectFilesApp()
{
	// 此处可加入构造函数程序内容
	// 大量的初始化程序请在InitInstance函数中编写
}

// 程序中用到的唯一的CCreateProjectFilesApp对象
CCreateProjectFilesApp theApp;

// 以下是一段标准初始化程序
BOOL CCreateProjectFilesApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();	      // 当MFC链接方式选择的是动态链接方式时调用
#else
	Enable3dControlsStatic(); // 当MFC链接方式选择的是静态链接方式时调用
#endif

	CCreateProjectFilesDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// 此处可以添加代码对Ok按钮按下时进行处理
	}
	else if (nResponse == IDCANCEL)
	{
       // 此处可以添加代码对Cancel按钮按下时进行处理
	}

	//  因为对话框已经关闭，我们应该返回FALSE从而退出
	//  应用程序，以免重新进入程序的消息循环
	return FALSE;
}
