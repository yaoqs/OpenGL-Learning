// MyExplosionDoc.cpp : implementation of the CMyExplosionDoc class
//

#include "stdafx.h"
#include "MyExplosion.h"

#include "MyExplosionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionDoc

IMPLEMENT_DYNCREATE(CMyExplosionDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyExplosionDoc, CDocument)
	//{{AFX_MSG_MAP(CMyExplosionDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionDoc construction/destruction

CMyExplosionDoc::CMyExplosionDoc()
{
	// TODO: add one-time construction code here

}

CMyExplosionDoc::~CMyExplosionDoc()
{
}

BOOL CMyExplosionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyExplosionDoc serialization

void CMyExplosionDoc::Serialize(CArchive& ar)
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
// CMyExplosionDoc diagnostics

#ifdef _DEBUG
void CMyExplosionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyExplosionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyExplosionDoc commands
