// MyPick2Doc.cpp : implementation of the CMyPick2Doc class
//

#include "stdafx.h"
#include "MyPick2.h"

#include "MyPick2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPick2Doc

IMPLEMENT_DYNCREATE(CMyPick2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyPick2Doc, CDocument)
	//{{AFX_MSG_MAP(CMyPick2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPick2Doc construction/destruction

CMyPick2Doc::CMyPick2Doc()
{
	// TODO: add one-time construction code here

}

CMyPick2Doc::~CMyPick2Doc()
{
}

BOOL CMyPick2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyPick2Doc serialization

void CMyPick2Doc::Serialize(CArchive& ar)
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
// CMyPick2Doc diagnostics

#ifdef _DEBUG
void CMyPick2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyPick2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPick2Doc commands
