// CreateProjectFiles.cpp : ����Ӧ�ó����������Ϊ
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

// CCreateProjectFilesApp��Ĺ��캯��
CCreateProjectFilesApp::CCreateProjectFilesApp()
{
	// �˴��ɼ��빹�캯����������
	// �����ĳ�ʼ����������InitInstance�����б�д
}

// �������õ���Ψһ��CCreateProjectFilesApp����
CCreateProjectFilesApp theApp;

// ������һ�α�׼��ʼ������
BOOL CCreateProjectFilesApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();	      // ��MFC���ӷ�ʽѡ����Ƕ�̬���ӷ�ʽʱ����
#else
	Enable3dControlsStatic(); // ��MFC���ӷ�ʽѡ����Ǿ�̬���ӷ�ʽʱ����
#endif

	CCreateProjectFilesDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// �˴�������Ӵ����Ok��ť����ʱ���д���
	}
	else if (nResponse == IDCANCEL)
	{
       // �˴�������Ӵ����Cancel��ť����ʱ���д���
	}

	//  ��Ϊ�Ի����Ѿ��رգ�����Ӧ�÷���FALSE�Ӷ��˳�
	//  Ӧ�ó����������½���������Ϣѭ��
	return FALSE;
}
