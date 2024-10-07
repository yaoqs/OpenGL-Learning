// MyCollision1Doc.cpp : implementation of the CMyCollision1Doc class
//

#include "stdafx.h"
#include "MyCollision1.h"

#include "MyCollision1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCollision1Doc

IMPLEMENT_DYNCREATE(CMyCollision1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyCollision1Doc, CDocument)
	//{{AFX_MSG_MAP(CMyCollision1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCollision1Doc construction/destruction

CMyCollision1Doc::CMyCollision1Doc()
{
	// TODO: add one-time construction code here

}

CMyCollision1Doc::~CMyCollision1Doc()
{
}

BOOL CMyCollision1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyCollision1Doc serialization

void CMyCollision1Doc::Serialize(CArchive& ar)
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
// CMyCollision1Doc diagnostics

#ifdef _DEBUG
void CMyCollision1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyCollision1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCollision1Doc commands
