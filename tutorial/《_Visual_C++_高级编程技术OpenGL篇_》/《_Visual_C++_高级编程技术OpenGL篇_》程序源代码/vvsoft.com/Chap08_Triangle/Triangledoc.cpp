// TriangleDoc.cpp : implementation of the CTriangleDoc class
//

#include "stdafx.h"
#include "Triangle.h"

#include "TriangleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTriangleDoc

IMPLEMENT_DYNCREATE(CTriangleDoc, CDocument)

BEGIN_MESSAGE_MAP(CTriangleDoc, CDocument)
	//{{AFX_MSG_MAP(CTriangleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTriangleDoc construction/destruction

CTriangleDoc::CTriangleDoc()
{
	// TODO: add one-time construction code here

}

CTriangleDoc::~CTriangleDoc()
{
}

BOOL CTriangleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

//	SetTitle("Motion Edit");
	SetTitle("");
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTriangleDoc serialization

void CTriangleDoc::Serialize(CArchive& ar)
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
// CTriangleDoc diagnostics

#ifdef _DEBUG
void CTriangleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTriangleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTriangleDoc commands
