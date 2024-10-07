// ASELoaderDoc.cpp : implementation of the CASELoaderDoc class
//

#include "stdafx.h"
#include "ASELoader.h"

#include "ASELoaderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CASELoaderDoc

IMPLEMENT_DYNCREATE(CASELoaderDoc, CDocument)

BEGIN_MESSAGE_MAP(CASELoaderDoc, CDocument)
	//{{AFX_MSG_MAP(CASELoaderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CASELoaderDoc construction/destruction

CASELoaderDoc::CASELoaderDoc()
{
	// TODO: add one-time construction code here

}

CASELoaderDoc::~CASELoaderDoc()
{
}

BOOL CASELoaderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CASELoaderDoc serialization

void CASELoaderDoc::Serialize(CArchive& ar)
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
// CASELoaderDoc diagnostics

#ifdef _DEBUG
void CASELoaderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CASELoaderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CASELoaderDoc commands
