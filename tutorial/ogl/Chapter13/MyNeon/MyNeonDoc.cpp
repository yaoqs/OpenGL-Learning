// MyNeonDoc.cpp : implementation of the CMyNeonDoc class
//

#include "stdafx.h"
#include "MyNeon.h"

#include "MyNeonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyNeonDoc

IMPLEMENT_DYNCREATE(CMyNeonDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyNeonDoc, CDocument)
	//{{AFX_MSG_MAP(CMyNeonDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyNeonDoc construction/destruction

CMyNeonDoc::CMyNeonDoc()
{
	// TODO: add one-time construction code here

}

CMyNeonDoc::~CMyNeonDoc()
{
}

BOOL CMyNeonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyNeonDoc serialization

void CMyNeonDoc::Serialize(CArchive& ar)
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
// CMyNeonDoc diagnostics

#ifdef _DEBUG
void CMyNeonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyNeonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyNeonDoc commands
