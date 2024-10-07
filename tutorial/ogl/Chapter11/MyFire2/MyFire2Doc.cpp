// MyFire2Doc.cpp : implementation of the CMyFire2Doc class
//

#include "stdafx.h"
#include "MyFire2.h"

#include "MyFire2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFire2Doc

IMPLEMENT_DYNCREATE(CMyFire2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMyFire2Doc, CDocument)
	//{{AFX_MSG_MAP(CMyFire2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFire2Doc construction/destruction

CMyFire2Doc::CMyFire2Doc()
{
	// TODO: add one-time construction code here

}

CMyFire2Doc::~CMyFire2Doc()
{
}

BOOL CMyFire2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyFire2Doc serialization

void CMyFire2Doc::Serialize(CArchive& ar)
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
// CMyFire2Doc diagnostics

#ifdef _DEBUG
void CMyFire2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyFire2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFire2Doc commands
