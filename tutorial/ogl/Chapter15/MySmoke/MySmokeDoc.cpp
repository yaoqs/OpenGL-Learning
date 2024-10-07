// MySmokeDoc.cpp : implementation of the CMySmokeDoc class
//

#include "stdafx.h"
#include "MySmoke.h"

#include "MySmokeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySmokeDoc

IMPLEMENT_DYNCREATE(CMySmokeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMySmokeDoc, CDocument)
	//{{AFX_MSG_MAP(CMySmokeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySmokeDoc construction/destruction

CMySmokeDoc::CMySmokeDoc()
{
	// TODO: add one-time construction code here

}

CMySmokeDoc::~CMySmokeDoc()
{
}

BOOL CMySmokeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMySmokeDoc serialization

void CMySmokeDoc::Serialize(CArchive& ar)
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
// CMySmokeDoc diagnostics

#ifdef _DEBUG
void CMySmokeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMySmokeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySmokeDoc commands
