//********************************************
// ToolDoc.cpp
//********************************************
// The active document, contain a SceneGraph
//********************************************
// feigz@ox.ios.ac.cn
// Created : 4/12/98
// Modified
//********************************************


#include "stdafx.h"
#include "math.h"
#include "Tool.h"
#include "MainFrm.h"

#include "ToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolDoc
extern GLMmodel *  model;
IMPLEMENT_DYNCREATE(CToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolDoc, CDocument)
	//{{AFX_MSG_MAP(CToolDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolDoc construction/destruction

//********************************************
// Constructor
//********************************************
CToolDoc::CToolDoc()
{
}

//********************************************
// Destructor
//********************************************
CToolDoc::~CToolDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
// CToolDoc serialization

void CToolDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CToolDoc commands
void CToolDoc::OnCloseDocument() 
{
	CDocument::OnCloseDocument();
}


BOOL CToolDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	return TRUE;
}
