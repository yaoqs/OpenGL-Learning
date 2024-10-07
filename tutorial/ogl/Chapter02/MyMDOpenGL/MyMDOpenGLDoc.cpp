// MyMDOpenGLDoc.cpp : implementation of the CMyMDOpenGLDoc class
//

#include "stdafx.h"
#include "MyMDOpenGL.h"

#include "MyMDOpenGLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLDoc

IMPLEMENT_DYNCREATE(CMyMDOpenGLDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyMDOpenGLDoc, CDocument)
	//{{AFX_MSG_MAP(CMyMDOpenGLDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLDoc construction/destruction

CMyMDOpenGLDoc::CMyMDOpenGLDoc()
{
	// TODO: add one-time construction code here

}

CMyMDOpenGLDoc::~CMyMDOpenGLDoc()
{
}

BOOL CMyMDOpenGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLDoc serialization

void CMyMDOpenGLDoc::Serialize(CArchive& ar)
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
// CMyMDOpenGLDoc diagnostics

#ifdef _DEBUG
void CMyMDOpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyMDOpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyMDOpenGLDoc commands
