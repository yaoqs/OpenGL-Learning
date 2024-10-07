#include "stdafx.h"
#include "math.h"
#include "Tool.h"

#include "ToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolDoc, CDocument)
	//{{AFX_MSG_MAP(CToolDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern CToolApp theApp;

// CToolDoc construction/destruction

// Constructor
CToolDoc::CToolDoc()
{
}

// Destructor
CToolDoc::~CToolDoc()
{
}

BOOL CToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

// CToolDoc serialization
void CToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()){}
	else{}
}

/////////////////////////////////////////////////////////////////////////////
// CToolDoc diagnostics

#ifdef _DEBUG
void CToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG