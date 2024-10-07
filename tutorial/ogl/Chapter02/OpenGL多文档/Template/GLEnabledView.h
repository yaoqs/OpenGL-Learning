#if !defined(AFX_GLENABLEDVIEW_H__26581ABB_E2E6_47D2_8A86_B45FFECA00C5__INCLUDED_)
#define AFX_GLENABLEDVIEW_H__26581ABB_E2E6_47D2_8A86_B45FFECA00C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GLEnabledView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView view

class CGLEnabledView : public CView
{
protected:
	CGLEnabledView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGLEnabledView)

// Attributes
public:

// Operations
public:
//////////////////////////////////////////////////////////////////
//��ӳ�Ա�������Ա����
	CDC* m_pDC;						// Windows�豸������
	HGLRC m_hRC;					// OpenGL��Ⱦ������
	CRect m_ClientRect;				// �ͻ����Ĵ�С
	double m_dAspectRatio;			// ���ڵı���

	HPALETTE	m_hPalette;			//��ɫ��
	BOOL SetupPixelFormat();		
	BOOL InitializeOpenGL(CDC* pDC);
	void SetLogicalPalette(void);
	virtual void OnDrawGL();		// ͼ�λ����麯�����ڼ̳����п��Ը�д
//////////////////////////////////////////////////////////////////

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLEnabledView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGLEnabledView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLEnabledView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLENABLEDVIEW_H__26581ABB_E2E6_47D2_8A86_B45FFECA00C5__INCLUDED_)
