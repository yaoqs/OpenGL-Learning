// MyTerrain1Doc.cpp : implementation of the CMyTerrain1Doc class
//

#include "stdafx.h"
#include "MyTerrain1.h"

#include "MyTerrain1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain1Doc

IMPLEMENT_DYNCREATE(CMyTerrain1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyTerrain1Doc, CDocument)
	//{{AFX_MSG_MAP(CMyTerrain1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain1Doc construction/destruction

CMyTerrain1Doc::CMyTerrain1Doc()
{
	// TODO: add one-time construction code here

}

CMyTerrain1Doc::~CMyTerrain1Doc()
{
}

BOOL CMyTerrain1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyTerrain1Doc serialization

void CMyTerrain1Doc::Serialize(CArchive& ar)
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
// CMyTerrain1Doc diagnostics

#ifdef _DEBUG
void CMyTerrain1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyTerrain1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTerrain1Doc commands
