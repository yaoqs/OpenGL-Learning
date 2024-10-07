// MyCollision2Doc.cpp : implementation of the CMyCollision2Doc class
//

#include "stdafx.h"
#include "MyCollision2.h"

#include "MyCollision2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2Doc

IMPLEMENT_DYNCREATE(CMyCollision2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyCollision2Doc, CDocument)
	//{{AFX_MSG_MAP(CMyCollision2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2Doc construction/destruction

CMyCollision2Doc::CMyCollision2Doc()
{
	// TODO: add one-time construction code here

}

CMyCollision2Doc::~CMyCollision2Doc()
{
}

BOOL CMyCollision2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyCollision2Doc serialization

void CMyCollision2Doc::Serialize(CArchive& ar)
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
// CMyCollision2Doc diagnostics

#ifdef _DEBUG
void CMyCollision2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyCollision2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCollision2Doc commands
