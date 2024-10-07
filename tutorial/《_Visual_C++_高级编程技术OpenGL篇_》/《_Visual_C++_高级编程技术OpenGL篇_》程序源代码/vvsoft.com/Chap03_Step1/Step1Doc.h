// Step1Doc.h : interface of the CStep1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEP1DOC_H__4D9DCF8D_170C_11D2_83B2_0080C832FCF3__INCLUDED_)
#define AFX_STEP1DOC_H__4D9DCF8D_170C_11D2_83B2_0080C832FCF3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CStep1Doc : public CDocument
{
protected: // create from serialization only
	CStep1Doc();
	DECLARE_DYNCREATE(CStep1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStep1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStep1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStep1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP1DOC_H__4D9DCF8D_170C_11D2_83B2_0080C832FCF3__INCLUDED_)
