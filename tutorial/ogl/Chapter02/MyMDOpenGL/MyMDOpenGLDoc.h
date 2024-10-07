// MyMDOpenGLDoc.h : interface of the CMyMDOpenGLDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMDOPENGLDOC_H__2EA2AE24_6BAC_4C34_A5BC_4DE449FE25AC__INCLUDED_)
#define AFX_MYMDOPENGLDOC_H__2EA2AE24_6BAC_4C34_A5BC_4DE449FE25AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyMDOpenGLDoc : public CDocument
{
protected: // create from serialization only
	CMyMDOpenGLDoc();
	DECLARE_DYNCREATE(CMyMDOpenGLDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMDOpenGLDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyMDOpenGLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyMDOpenGLDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMDOPENGLDOC_H__2EA2AE24_6BAC_4C34_A5BC_4DE449FE25AC__INCLUDED_)
