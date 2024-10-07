// MyLODDoc.cpp : implementation of the CMyLODDoc class
//

#include "stdafx.h"
#include "MyLOD.h"

#include "MyLODDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyLODDoc

IMPLEMENT_DYNCREATE(CMyLODDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyLODDoc, CDocument)
	//{{AFX_MSG_MAP(CMyLODDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyLODDoc construction/destruction

CMyLODDoc::CMyLODDoc()
{
	// TODO: add one-time construction code here

}

CMyLODDoc::~CMyLODDoc()
{
}

BOOL CMyLODDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyLODDoc serialization

void CMyLODDoc::Serialize(CArchive& ar)
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
// CMyLODDoc diagnostics

#ifdef _DEBUG
void CMyLODDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyLODDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyLODDoc commands
