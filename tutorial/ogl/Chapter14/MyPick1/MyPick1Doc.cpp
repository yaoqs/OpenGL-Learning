// MyPick1Doc.cpp : implementation of the CMyPick1Doc class
//

#include "stdafx.h"
#include "MyPick1.h"

#include "MyPick1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPick1Doc

IMPLEMENT_DYNCREATE(CMyPick1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyPick1Doc, CDocument)
	//{{AFX_MSG_MAP(CMyPick1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPick1Doc construction/destruction

CMyPick1Doc::CMyPick1Doc()
{
	// TODO: add one-time construction code here

}

CMyPick1Doc::~CMyPick1Doc()
{
}

BOOL CMyPick1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyPick1Doc serialization

void CMyPick1Doc::Serialize(CArchive& ar)
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
// CMyPick1Doc diagnostics

#ifdef _DEBUG
void CMyPick1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyPick1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPick1Doc commands
