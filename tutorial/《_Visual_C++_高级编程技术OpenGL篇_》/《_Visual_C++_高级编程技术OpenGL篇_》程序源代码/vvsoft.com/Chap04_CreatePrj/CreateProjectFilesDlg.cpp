// CreateProjectFilesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CreateProjectFiles.h"
#include "CreateProjectFilesDlg.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool CopyFiles( CString & ProjectName, CString & SourceDirectory, CString & DestinationDirectory );
bool CopyFiles( const char* ProjectName, const char* TemplateName, const char* SourceDirectory, const char* DestinationDirectory );
bool CopyFile( const char* ProjectName, const char* TemplateName, char* SourceFile, char* DestinationFile );
void ReplaceText( char* String, const char* SrcText, const char* DstText );

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateProjectFilesDlg dialog

CCreateProjectFilesDlg::CCreateProjectFilesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateProjectFilesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateProjectFilesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateProjectFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateProjectFilesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateProjectFilesDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateProjectFilesDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateProjectFilesDlg message handlers

BOOL CCreateProjectFilesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetDlgItemText( IDC_EDIT1, "NewProject" );
	SetDlgItemText( IDC_EDIT2, "..\\NewProject" );
	SetDlgItemText( IDC_EDIT3, "..\\Chap04_MyTemplate" );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCreateProjectFilesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCreateProjectFilesDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCreateProjectFilesDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCreateProjectFilesDlg::OnOK() 
{
	CString	ProjectName;
	CString	ProjectDirectory;
	CString	SampleDirectory;

	// get dialog data
	GetDlgItemText( IDC_EDIT1, ProjectName );
	GetDlgItemText( IDC_EDIT2, ProjectDirectory );
	GetDlgItemText( IDC_EDIT3, SampleDirectory );


	// verify Sample (source) directory
	if ( -1 == _access( ( const char* ) SampleDirectory, 0 ) )
	{
		AfxMessageBox( "Template Project's directory does not exist" );
		return;
	}

	if ( -1 == _access( ( const char* ) ProjectDirectory, 0 ) )
	{
		if ( -1 == _mkdir( ProjectDirectory ) )
		{
			AfxMessageBox( "New Project Directory does not exist. You must create it manually" );
			return;
		}
	}

	if ( true == CopyFiles( ProjectName, SampleDirectory, ProjectDirectory ) )
		AfxMessageBox( "New Project created successfully" );
	else
		AfxMessageBox( "Creating new project failed!!!" );
}

bool CopyFiles( CString & ProjectName, CString & SourceDirectory, CString & DestinationDirectory )
{
	// get out spaces from project name
	ProjectName.SpanIncluding( " \t\n\\\"" );
	// get template project name
	char	TemplateName[ _MAX_FNAME ];
	_splitpath( ( const char* ) SourceDirectory, NULL, NULL, TemplateName, NULL );

	return CopyFiles( ( const char* ) ProjectName, TemplateName, ( const char* )SourceDirectory, ( const char* )DestinationDirectory );
}

bool CopyFiles( const char* ProjectName, const char* TemplateName, const char* SourceDirectory, const char* DestinationDirectory )
{
	bool			hResult = false;
	char			SrcDir[ FILENAME_MAX ];
	char			DstDir[ FILENAME_MAX ];

	WIN32_FIND_DATA	ScanInfo;
	HANDLE			hScan = INVALID_HANDLE_VALUE;
	char			FilePattern[ FILENAME_MAX ];
	
	// copy parameters
	strcpy( SrcDir, SourceDirectory );
	strcpy( DstDir, DestinationDirectory );
	if ( SrcDir[ strlen( SrcDir ) - 1 ] == '\\' )
		SrcDir[ strlen( SrcDir ) - 1 ] = 0;
	if ( DstDir[ strlen( DstDir ) - 1 ] == '\\' )
		DstDir[ strlen( DstDir ) - 1 ] = 0;

	sprintf( FilePattern, "%s\\*.*", SrcDir );
	if ( ( hScan = FindFirstFile( FilePattern, & ScanInfo ) ) != INVALID_HANDLE_VALUE )
	{
		do
		{

			// check if it is a directory
			if ( ( ScanInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
			{
				char			SrcDir2[ FILENAME_MAX ];
				char			DstDir2[ FILENAME_MAX ];

				if	(
					0 == strcmp( ".", ( char* )ScanInfo.cFileName ) ||
					0 == strcmp( "..", ( char* )ScanInfo.cFileName ) 
					)
					continue;

				sprintf( SrcDir2, "%s\\%s", SrcDir, ( char* )ScanInfo.cFileName );
				sprintf( DstDir2, "%s\\%s", DstDir, ( char* )ScanInfo.cFileName );
				mkdir( DstDir2 );
				if ( ! CopyFiles( ProjectName, TemplateName, SrcDir2, DstDir2 ) )
					goto cleanup;
			}
			else
			{
				char			SrcFile[ FILENAME_MAX ];
				char			DstFile[ FILENAME_MAX ];

				sprintf( SrcFile, "%s\\%s", SrcDir, ( char* )ScanInfo.cFileName );

				// create dest file name
				char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
				_splitpath( SrcFile, drive, dir, fname, ext );
				ReplaceText( fname, TemplateName, ProjectName );
				
				sprintf( DstFile, "%s\\%s%s", DstDir, fname, ext );

				if ( ! CopyFile( ProjectName, TemplateName, SrcFile, DstFile ) )
					goto cleanup;
			}
		} while ( FindNextFile( hScan, & ScanInfo ) != 0 );
	}
	hResult = true;

cleanup:
	if ( INVALID_HANDLE_VALUE != hScan )
		FindClose( hScan );
	return true;
}

bool CopyFile( const char* ProjectName, const char* TemplateName, char* SourceFile, char* DestinationFile )
{
	bool	RetStatus = false;
	FILE*	hSrcFile = NULL;
	FILE*	hDstFile = NULL;
	char	InputLine[ 4096 ];

	char	FileExtension[ _MAX_EXT ];
	char	FileName[ _MAX_FNAME ];

	_splitpath( SourceFile, NULL, NULL, FileName, FileExtension );

	if	(
		0 == stricmp( ".reg", FileExtension ) ||
		0 == stricmp( ".txt", FileExtension ) ||
		0 == stricmp( ".clw", FileExtension ) ||
		0 == stricmp( ".dsw", FileExtension ) ||
		0 == stricmp( ".dsp", FileExtension ) ||
		0 == stricmp( ".cpp", FileExtension ) ||
		0 == stricmp( ".rc", FileExtension ) ||
		0 == stricmp( ".rc2", FileExtension ) ||
		0 == stricmp( ".c", FileExtension ) ||
		0 == stricmp( ".h", FileExtension )
		)
	{

		if ( NULL == ( hSrcFile = fopen( SourceFile, "rt" ) ) )
			goto cleanup;
		if ( NULL == ( hDstFile = fopen( DestinationFile, "wt" ) ) )
			goto cleanup;

		int		IfDefLevel;
		int		LineNumber;

		IfDefLevel = 0;
		LineNumber = 0;

		while ( NULL != fgets( InputLine, sizeof( InputLine ) / 2, hSrcFile ) )
		{
			ReplaceText( InputLine, TemplateName, ProjectName );
			fputs( InputLine, hDstFile );
		}
	}
	else
		CopyFile( SourceFile, DestinationFile, TRUE );

	RetStatus = true;

cleanup:
	if ( hSrcFile )
		fclose( hSrcFile );
	if ( hDstFile )
		fclose( hDstFile );
	return RetStatus;
}

void ReplaceText( char* String, const char* SrcText, const char* DstText )
{
	char	UpperSrcText[ 1024 ];
	char	UpperString[ 4096 ];
	char*	Pos2;

	strcpy( UpperString, String );
	strcpy( UpperSrcText, SrcText );

	strupr( UpperString );
	strupr( UpperSrcText );

	while ( NULL != ( Pos2 = strstr( UpperString, UpperSrcText ) ) )
	{
		char*		Pos	= String + ( Pos2 - UpperString );
		const char*	Dst;
		char		UpperDstText[ 1024 ];
		// determine whether all characters in src string
		// are originally uppercased
		int tt;
		for ( unsigned int i = 0; i < strlen( SrcText ); i++ )
			{
			tt = i;
	if ( islower( Pos[ i ] ) )
					break;

}
		if ( tt == strlen( SrcText ) )
		{
			strcpy( UpperDstText, DstText );
			strupr( UpperDstText );
			Dst = UpperDstText;
		}
		else
			Dst = DstText;

		// delete the old substring
		memmove
			(
			Pos,
			Pos + strlen( UpperSrcText ),
			strlen( Pos ) - strlen( UpperSrcText ) + 1
			);
		// insert new string
		memmove
			(
			Pos + strlen( DstText ),
			Pos,
			strlen( Pos ) + 1
			);
		for (int i = 0; i < strlen( DstText ); i++ )
			Pos[ i ] = Dst[ i ];

		// prepare variables for next loop for the case
		// when the template string is in String multiple times
		strcpy( UpperString, String );
		strcpy( UpperSrcText, SrcText );

		strupr( UpperString );
		strupr( UpperSrcText );
	}
}

void CCreateProjectFilesDlg::OnAbout() 
{
	// display the about dialog
	CAboutDlg	Dlg;
	Dlg.DoModal();
}
