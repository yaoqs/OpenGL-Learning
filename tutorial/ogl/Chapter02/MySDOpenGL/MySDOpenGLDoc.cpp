// MySDOpenGLDoc.cpp : implementation of the CMySDOpenGLDoc class
//

#include "stdafx.h"
#include "MySDOpenGL.h"

#include "MySDOpenGLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySDOpenGLDoc

IMPLEMENT_DYNCREATE(CMySDOpenGLDoc, CDocument)

BEGIN_MESSAGE_MAP(CMySDOpenGLDoc, CDocument)
	//{{AFX_MSG_MAP(CMySDOpenGLDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySDOpenGLDoc construction/destruction

CMySDOpenGLDoc::CMySDOpenGLDoc()
{
	// TODO: add one-time construction code here

}

CMySDOpenGLDoc::~CMySDOpenGLDoc()
{
}

BOOL CMySDOpenGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMySDOpenGLDoc serialization

void CMySDOpenGLDoc::Serialize(CArchive& ar)
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
// CMySDOpenGLDoc diagnostics

#ifdef _DEBUG
void CMySDOpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMySDOpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySDOpenGLDoc commands
