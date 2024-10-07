// MyDischargeDoc.cpp : implementation of the CMyDischargeDoc class
//

#include "stdafx.h"
#include "MyDischarge.h"

#include "MyDischargeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDischargeDoc

IMPLEMENT_DYNCREATE(CMyDischargeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDischargeDoc, CDocument)
	//{{AFX_MSG_MAP(CMyDischargeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDischargeDoc construction/destruction

CMyDischargeDoc::CMyDischargeDoc()
{
	// TODO: add one-time construction code here

}

CMyDischargeDoc::~CMyDischargeDoc()
{
}

BOOL CMyDischargeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyDischargeDoc serialization

void CMyDischargeDoc::Serialize(CArchive& ar)
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
// CMyDischargeDoc diagnostics

#ifdef _DEBUG
void CMyDischargeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDischargeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDischargeDoc commands
