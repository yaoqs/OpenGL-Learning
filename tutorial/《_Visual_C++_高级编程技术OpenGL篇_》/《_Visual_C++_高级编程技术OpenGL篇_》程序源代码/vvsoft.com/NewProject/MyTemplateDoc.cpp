//********************************************
// MyTemplateDoc.cpp
//********************************************
// The active document, contain a SceneGraph
//********************************************
// Created : 05/17/1999
// Modified: 10/26/1999
//********************************************


#include "stdafx.h"
#include "math.h"
#include "MyTemplate.h"
#include "MainFrm.h"

#include "MyTemplateDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTemplateDoc
IMPLEMENT_DYNCREATE(CMyTemplateDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyTemplateDoc, CDocument)
	//{{AFX_MSG_MAP(CMyTemplateDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTemplateDoc construction/destruction

//********************************************
// Constructor
//********************************************
CMyTemplateDoc::CMyTemplateDoc()
{
}

//********************************************
// Destructor
//********************************************
CMyTemplateDoc::~CMyTemplateDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMyTemplateDoc serialization

void CMyTemplateDoc::Serialize(CArchive& ar)
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
// CMyTemplateDoc diagnostics

#ifdef _DEBUG
void CMyTemplateDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyTemplateDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTemplateDoc commands
void CMyTemplateDoc::OnCloseDocument() 
{
	CDocument::OnCloseDocument();
}


BOOL CMyTemplateDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	return TRUE;
}
