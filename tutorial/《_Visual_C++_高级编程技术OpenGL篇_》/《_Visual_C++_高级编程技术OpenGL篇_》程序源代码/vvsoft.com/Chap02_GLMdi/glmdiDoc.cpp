// glmdiDoc.cpp : implementation of the CGlmdiDoc class
//

#include "stdafx.h"
#include "glmdi.h"

#include "glmdiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlmdiDoc

IMPLEMENT_DYNCREATE(CGlmdiDoc, CDocument)

BEGIN_MESSAGE_MAP(CGlmdiDoc, CDocument)
	//{{AFX_MSG_MAP(CGlmdiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlmdiDoc construction/destruction

CGlmdiDoc::CGlmdiDoc()
{
	// TODO: add one-time construction code here

}

CGlmdiDoc::~CGlmdiDoc()
{
}

BOOL CGlmdiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGlmdiDoc serialization

void CGlmdiDoc::Serialize(CArchive& ar)
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
// CGlmdiDoc diagnostics

#ifdef _DEBUG
void CGlmdiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGlmdiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGlmdiDoc commands
