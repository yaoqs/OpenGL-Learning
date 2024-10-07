// MyCloudDoc.cpp : implementation of the CMyCloudDoc class
//

#include "stdafx.h"
#include "MyCloud.h"

#include "MyCloudDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCloudDoc

IMPLEMENT_DYNCREATE(CMyCloudDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyCloudDoc, CDocument)
	//{{AFX_MSG_MAP(CMyCloudDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCloudDoc construction/destruction

CMyCloudDoc::CMyCloudDoc()
{
	// TODO: add one-time construction code here

}

CMyCloudDoc::~CMyCloudDoc()
{
}

BOOL CMyCloudDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyCloudDoc serialization

void CMyCloudDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyCloudDoc diagnostics

#ifdef _DEBUG
void CMyCloudDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyCloudDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCloudDoc commands
