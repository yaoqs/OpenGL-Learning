// MyFire1Doc.cpp : implementation of the CMyFire1Doc class
//

#include "stdafx.h"
#include "MyFire1.h"

#include "MyFire1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFire1Doc

IMPLEMENT_DYNCREATE(CMyFire1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyFire1Doc, CDocument)
	//{{AFX_MSG_MAP(CMyFire1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFire1Doc construction/destruction

CMyFire1Doc::CMyFire1Doc()
{
	// TODO: add one-time construction code here

}

CMyFire1Doc::~CMyFire1Doc()
{
}

BOOL CMyFire1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyFire1Doc serialization

void CMyFire1Doc::Serialize(CArchive& ar)
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
// CMyFire1Doc diagnostics

#ifdef _DEBUG
void CMyFire1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyFire1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFire1Doc commands
