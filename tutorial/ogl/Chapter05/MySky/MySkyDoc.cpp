// MySkyDoc.cpp : implementation of the CMySkyDoc class
//

#include "stdafx.h"
#include "MySky.h"

#include "MySkyDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySkyDoc

IMPLEMENT_DYNCREATE(CMySkyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMySkyDoc, CDocument)
	//{{AFX_MSG_MAP(CMySkyDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySkyDoc construction/destruction

CMySkyDoc::CMySkyDoc()
{
	// TODO: add one-time construction code here

}

CMySkyDoc::~CMySkyDoc()
{
}

BOOL CMySkyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMySkyDoc serialization

void CMySkyDoc::Serialize(CArchive& ar)
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
// CMySkyDoc diagnostics

#ifdef _DEBUG
void CMySkyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMySkyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySkyDoc commands
