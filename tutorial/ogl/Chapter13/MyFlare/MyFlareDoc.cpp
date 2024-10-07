// MyFlareDoc.cpp : implementation of the CMyFlareDoc class
//

#include "stdafx.h"
#include "MyFlare.h"

#include "MyFlareDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFlareDoc

IMPLEMENT_DYNCREATE(CMyFlareDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyFlareDoc, CDocument)
	//{{AFX_MSG_MAP(CMyFlareDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFlareDoc construction/destruction

CMyFlareDoc::CMyFlareDoc()
{
	// TODO: add one-time construction code here

}

CMyFlareDoc::~CMyFlareDoc()
{
}

BOOL CMyFlareDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyFlareDoc serialization

void CMyFlareDoc::Serialize(CArchive& ar)
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
// CMyFlareDoc diagnostics

#ifdef _DEBUG
void CMyFlareDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyFlareDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFlareDoc commands
