// MyFountainDoc.cpp : implementation of the CMyFountainDoc class
//

#include "stdafx.h"
#include "MyFountain.h"

#include "MyFountainDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFountainDoc

IMPLEMENT_DYNCREATE(CMyFountainDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyFountainDoc, CDocument)
	//{{AFX_MSG_MAP(CMyFountainDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFountainDoc construction/destruction

CMyFountainDoc::CMyFountainDoc()
{
	// TODO: add one-time construction code here

}

CMyFountainDoc::~CMyFountainDoc()
{
}

BOOL CMyFountainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyFountainDoc serialization

void CMyFountainDoc::Serialize(CArchive& ar)
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
// CMyFountainDoc diagnostics

#ifdef _DEBUG
void CMyFountainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyFountainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFountainDoc commands
