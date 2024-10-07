// MyStarspaceDoc.cpp : implementation of the CMyStarspaceDoc class
//

#include "stdafx.h"
#include "MyStarspace.h"

#include "MyStarspaceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStarspaceDoc

IMPLEMENT_DYNCREATE(CMyStarspaceDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyStarspaceDoc, CDocument)
	//{{AFX_MSG_MAP(CMyStarspaceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStarspaceDoc construction/destruction

CMyStarspaceDoc::CMyStarspaceDoc()
{
	// TODO: add one-time construction code here

}

CMyStarspaceDoc::~CMyStarspaceDoc()
{
}

BOOL CMyStarspaceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyStarspaceDoc serialization

void CMyStarspaceDoc::Serialize(CArchive& ar)
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
// CMyStarspaceDoc diagnostics

#ifdef _DEBUG
void CMyStarspaceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyStarspaceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyStarspaceDoc commands
