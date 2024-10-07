//********************************************
// ToolDoc.h
// The document, contain a SceneGraph
//********************************************
// feigz@ox.ios.ac.cn
// Created : 12/12/97
// Modified
//********************************************
#include "glm.h"

#if !defined(AFX_TOOLDOC_H__06A35631_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
#define AFX_TOOLDOC_H__06A35631_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define MAX_VERTICE 40000  //define max vertice number of the mesh
#define MAX_VERTICE_PER_POLYGON 6
#define Object 1

class CSeneGraph3d; 

class CToolDoc : public CDocument
{
protected: // create from serialization only

// Attributes
private:
	//CSeneGraph3d m_SceneGraph;

// Functions
public:	
	// OpenGL
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CToolDoc();
	virtual ~CToolDoc();
	DECLARE_DYNCREATE(CToolDoc)
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLDOC_H__06A35631_72E5_11D1_A6C2_00A0242C0A32__INCLUDED_)
