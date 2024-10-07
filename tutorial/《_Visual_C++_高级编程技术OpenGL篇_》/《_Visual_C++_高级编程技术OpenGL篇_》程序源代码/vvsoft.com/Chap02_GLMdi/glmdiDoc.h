// glmdiDoc.h : interface of the CGlmdiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLMDIDOC_H__606EE8F9_E046_11D2_9DF8_0000214474ED__INCLUDED_)
#define AFX_GLMDIDOC_H__606EE8F9_E046_11D2_9DF8_0000214474ED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGlmdiDoc : public CDocument
{
protected: // create from serialization only
	CGlmdiDoc();
	DECLARE_DYNCREATE(CGlmdiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlmdiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGlmdiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGlmdiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLMDIDOC_H__606EE8F9_E046_11D2_9DF8_0000214474ED__INCLUDED_)
