// OBJLoaderDoc.cpp : implementation of the COBJLoaderDoc class
//

#include "stdafx.h"
#include "OBJLoader.h"

#include "OBJLoaderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COBJLoaderDoc

IMPLEMENT_DYNCREATE(COBJLoaderDoc, CDocument)

BEGIN_MESSAGE_MAP(COBJLoaderDoc, CDocument)
	//{{AFX_MSG_MAP(COBJLoaderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBJLoaderDoc construction/destruction

COBJLoaderDoc::COBJLoaderDoc()
{
	// TODO: add one-time construction code here

}

COBJLoaderDoc::~COBJLoaderDoc()
{
}

BOOL COBJLoaderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COBJLoaderDoc serialization

void COBJLoaderDoc::Serialize(CArchive& ar)
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
// COBJLoaderDoc diagnostics

#ifdef _DEBUG
void COBJLoaderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COBJLoaderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COBJLoaderDoc commands

BOOL COBJLoaderDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	if( ((COBJLoaderApp*)AfxGetApp())->OpenFile(lpszPathName) ) return TRUE;
	
	return TRUE;
}
