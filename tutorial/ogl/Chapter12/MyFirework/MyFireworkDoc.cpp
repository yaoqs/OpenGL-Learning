// MyFireworkDoc.cpp : implementation of the CMyFireworkDoc class
//

#include "stdafx.h"
#include "MyFirework.h"

#include "MyFireworkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFireworkDoc

IMPLEMENT_DYNCREATE(CMyFireworkDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyFireworkDoc, CDocument)
	//{{AFX_MSG_MAP(CMyFireworkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFireworkDoc construction/destruction

CMyFireworkDoc::CMyFireworkDoc()
{
	// TODO: add one-time construction code here

}

CMyFireworkDoc::~CMyFireworkDoc()
{
}

BOOL CMyFireworkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyFireworkDoc serialization

void CMyFireworkDoc::Serialize(CArchive& ar)
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
// CMyFireworkDoc diagnostics

#ifdef _DEBUG
void CMyFireworkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyFireworkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFireworkDoc commands
