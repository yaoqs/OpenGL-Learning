// MyWaterDoc.cpp : implementation of the CMyWaterDoc class
//

#include "stdafx.h"
#include "MyWater.h"

#include "MyWaterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWaterDoc

IMPLEMENT_DYNCREATE(CMyWaterDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyWaterDoc, CDocument)
	//{{AFX_MSG_MAP(CMyWaterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyWaterDoc construction/destruction

CMyWaterDoc::CMyWaterDoc()
{
	// TODO: add one-time construction code here

}

CMyWaterDoc::~CMyWaterDoc()
{
}

BOOL CMyWaterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyWaterDoc serialization

void CMyWaterDoc::Serialize(CArchive& ar)
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
// CMyWaterDoc diagnostics

#ifdef _DEBUG
void CMyWaterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyWaterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyWaterDoc commands
