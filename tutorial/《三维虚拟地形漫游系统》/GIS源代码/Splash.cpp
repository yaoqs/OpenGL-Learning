// Splash.cpp : implementation file
//

#include "stdafx.h"
#include "3D0214.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplash

CSplash::CSplash()
{
}

CSplash::~CSplash()
{
}


BEGIN_MESSAGE_MAP(CSplash, CWnd)
	//{{AFX_MSG_MAP(CSplash)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplash message handlers
void CSplash::Create( UINT nID )
{
	m_bitmap.LoadBitmapEx(nID,FALSE);
	int x = (::GetSystemMetrics (SM_CXSCREEN)-m_bitmap.m_Width)/2;
	int y = (::GetSystemMetrics (SM_CYSCREEN)-m_bitmap.m_Height)/2;
	CRect rect(x,y,x+m_bitmap.m_Width,y+m_bitmap.m_Height);
	CreateEx(0,AfxRegisterWndClass(0),"",WS_POPUP|WS_VISIBLE|WS_BORDER,rect,NULL,0);
}

void CSplash::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CPalette *pOldPal = dc.SelectPalette(m_bitmap.GetPalette(),FALSE);
	dc.RealizePalette();

	// get device context to select bitmap into
	CDC dcComp;
	dcComp.CreateCompatibleDC(&dc);
	dcComp.SelectObject(&m_bitmap);

	// draw bitmap
	dc.BitBlt(0,0,m_bitmap.m_Width,m_bitmap.m_Height, &dcComp, 0,0,SRCCOPY);

	// reselect old palette
	dc.SelectPalette(pOldPal,FALSE);
	// Do not call CWnd::OnPaint() for painting messages
}
