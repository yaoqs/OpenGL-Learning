// MyBombDoc.cpp : implementation of the CMyBombDoc class
//

#include "stdafx.h"
#include "MyBomb.h"

#include "MyBombDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBombDoc

IMPLEMENT_DYNCREATE(CMyBombDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyBombDoc, CDocument)
	//{{AFX_MSG_MAP(CMyBombDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyBombDoc construction/destruction

CMyBombDoc::CMyBombDoc()
{
	// TODO: add one-time construction code here

}

CMyBombDoc::~CMyBombDoc()
{
}

BOOL CMyBombDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyBombDoc serialization

void CMyBombDoc::Serialize(CArchive& ar)
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
// CMyBombDoc diagnostics

#ifdef _DEBUG
void CMyBombDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyBombDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyBombDoc commands
