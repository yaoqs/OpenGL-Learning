// 3D0214Doc.cpp : implementation of the CMy3D0214Doc class
//

#include "stdafx.h"
#include "3D0214.h"

#include "3D0214Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3D0214Doc

IMPLEMENT_DYNCREATE(CMy3D0214Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy3D0214Doc, CDocument)
	//{{AFX_MSG_MAP(CMy3D0214Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3D0214Doc construction/destruction

CMy3D0214Doc::CMy3D0214Doc()
{
	// TODO: add one-time construction code here

}

CMy3D0214Doc::~CMy3D0214Doc()
{
}

BOOL CMy3D0214Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy3D0214Doc serialization

void CMy3D0214Doc::Serialize(CArchive& ar)
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
// CMy3D0214Doc diagnostics

#ifdef _DEBUG
void CMy3D0214Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3D0214Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3D0214Doc commands
