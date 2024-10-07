// MyRainDoc.cpp : implementation of the CMyRainDoc class
//

#include "stdafx.h"
#include "MyRain.h"

#include "MyRainDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRainDoc

IMPLEMENT_DYNCREATE(CMyRainDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyRainDoc, CDocument)
	//{{AFX_MSG_MAP(CMyRainDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRainDoc construction/destruction

CMyRainDoc::CMyRainDoc()
{
	// TODO: add one-time construction code here

}

CMyRainDoc::~CMyRainDoc()
{
}

BOOL CMyRainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyRainDoc serialization

void CMyRainDoc::Serialize(CArchive& ar)
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
// CMyRainDoc diagnostics

#ifdef _DEBUG
void CMyRainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyRainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyRainDoc commands
