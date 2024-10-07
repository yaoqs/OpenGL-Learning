// MyTerrain2Doc.cpp : implementation of the CMyTerrain2Doc class
//

#include "stdafx.h"
#include "MyTerrain2.h"

#include "MyTerrain2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2Doc

IMPLEMENT_DYNCREATE(CMyTerrain2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyTerrain2Doc, CDocument)
	//{{AFX_MSG_MAP(CMyTerrain2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2Doc construction/destruction

CMyTerrain2Doc::CMyTerrain2Doc()
{
	// TODO: add one-time construction code here

}

CMyTerrain2Doc::~CMyTerrain2Doc()
{
}

BOOL CMyTerrain2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2Doc serialization

void CMyTerrain2Doc::Serialize(CArchive& ar)
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
// CMyTerrain2Doc diagnostics

#ifdef _DEBUG
void CMyTerrain2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyTerrain2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain2Doc commands
