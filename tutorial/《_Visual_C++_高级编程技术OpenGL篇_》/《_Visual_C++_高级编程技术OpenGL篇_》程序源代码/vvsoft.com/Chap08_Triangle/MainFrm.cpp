// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Triangle.h"

#include "MainFrm.h"
#include "TriangleView.h"
#include "body.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_FRAMEDIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_FRAMEDIALOGBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_INFOBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_INFOBAR, OnUpdateControlBarMenu)
	ON_WM_CREATE()
	ON_COMMAND_EX(CG_ID_VIEW_SKELETENDIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_SKELETENDIALOGBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_BODYTREE, OnSelchangedTree)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_ADDGROUP, OnButtonAddGroup)
	ON_BN_CLICKED(IDC_BUTTON_DELGROUP, OnButtonDelGroup)
	ON_BN_CLICKED(IDC_BUTTON_ADDFRAME, OnButtonAddFrame)
	ON_BN_CLICKED(IDC_BUTTON_DELFRAME, OnButtonDelFrame)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_COMMAND(ID_TOGGLE_ATTRIBUTEBAR, OnToggleAttributebar)
	ON_UPDATE_COMMAND_UI(ID_TOGGLE_ATTRIBUTEBAR, OnUpdateToggleAttributebar)
	ON_COMMAND(ID_TOGGLE_MANIPULATEBAR, OnToggleManipulatebar)
	ON_UPDATE_COMMAND_UI(ID_TOGGLE_MANIPULATEBAR, OnUpdateToggleManipulatebar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static char *BodyTypes[] = 
{
	"body            ",	
	"upper_body      ",
	"head            ",
	"shoulder        ",
	"left_arm        ",
	"right_arm       ",	
	"left_upper_arm  ",
	"right_upper_arm ",	
	"left_lower_arm  ",
	"right_lower_arm ",	
	"left_hand       ",
	"right_hand      ",	
	"lower_body      ",	
	"left_leg        ",
	"right_leg       ",	
	"left_upper_leg  ",
	"right_upper_leg ",	
	"left_lower_leg  ",
	"right_lower_leg ",	
	"left_foot       ",
	"right_foot      ",
	"left_elbow      ",
	"right_elbow     ",
	"left_wrist     ",
	"right_wrist     ",
	"left_knee       ",
	"right_knee      ",
	"left_ankle      ",
	"right_ankle     "
};
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pView = NULL;	
	body_id = BODY;
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
	{
    CView* pView = GetActiveView();
    if (pView) 
		{
        // OnPaletteChanged is not public, so send a message.
        pView->SendMessage(WM_PALETTECHANGED,
                           (WPARAM)(pFocusWnd->GetSafeHwnd()),
                           (LPARAM)0);
		}
	}

BOOL CMainFrame::OnQueryNewPalette() 
	{
	CView* pView = GetActiveView();
    if (pView)
		{
        return pView->SendMessage(WM_QUERYNEWPALETTE,
                                  (WPARAM)0,
                                  (LPARAM)0);
	    }
    return FALSE; 
	}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndManipulateBar.Create(this) ||
		!m_wndManipulateBar.LoadToolBar(IDR_MANIPULATEBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	m_wndManipulateBar.SetBarStyle(m_wndManipulateBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndManipulateBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndManipulateBar);

	if (!m_wndAttributeBar.Create(this) ||
		!m_wndAttributeBar.LoadToolBar(IDR_ATTRIBUTEBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndAttributeBar.SetBarStyle(m_wndAttributeBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndAttributeBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndAttributeBar);

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "Skeleten Dialog Bar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_SKELETENDIALOGBAR
	//   5. Assign the item a Caption: Skeleten Dialog Bar

	// TODO: Change the value of CG_ID_VIEW_SKELETENDIALOGBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndSkeletenDialogBar
		if (!m_wndSkeletenDialogBar.Create(this, CG_IDD_SKELETENDIALOGBAR,
			CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_SKELETENDIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndSkeletenDialogBar\n");
			return -1;		// fail to create
		}

		m_wndSkeletenDialogBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndSkeletenDialogBar);
	}

    CTreeCtrl *pTreeCtrl = (CTreeCtrl*)m_wndSkeletenDialogBar.GetDlgItem(IDC_BODYTREE);
	TV_INSERTSTRUCT temp;
	temp.hParent = NULL;
	temp.hInsertAfter = TVI_LAST;
	temp.item.mask = TVIF_TEXT;
	temp.item.hItem = NULL;
	temp.item.state = 0;
	temp.item.stateMask = 0;
	temp.item.cchTextMax = 12;
	temp.item.iSelectedImage = 0;
	temp.item.cChildren = 0;
	temp.item.lParam = 0;

	temp.item.pszText = "body";
	body = pTreeCtrl->InsertItem(&temp);

	temp.hParent = body;
	temp.item.pszText = "upper_body";
	upper_body = pTreeCtrl->InsertItem(&temp);

	temp.hParent = body;
	temp.item.pszText = "lower_body";
	lower_body = pTreeCtrl->InsertItem(&temp);

	temp.hParent = upper_body;
	temp.item.pszText = "head";
	head = pTreeCtrl->InsertItem(&temp);

	temp.hParent = upper_body;
	temp.item.pszText = "shoulder";
	shoulder = pTreeCtrl->InsertItem(&temp);

	temp.hParent = upper_body;
	temp.item.pszText = "left_arm";
	left_arm = pTreeCtrl->InsertItem(&temp);

	temp.hParent = upper_body;
	temp.item.pszText = "right_arm";
	right_arm = pTreeCtrl->InsertItem(&temp);

	temp.hParent = lower_body;
	temp.item.pszText = "left_leg";
	left_leg = pTreeCtrl->InsertItem(&temp);

	temp.hParent = lower_body;
	temp.item.pszText = "right_leg";
	right_leg = pTreeCtrl->InsertItem(&temp);

	temp.hParent = left_arm;
	temp.item.pszText = "left_upper_arm";
	left_upper_arm = pTreeCtrl->InsertItem(&temp);

	temp.item.pszText = "left_lower_arm";
	left_lower_arm = pTreeCtrl->InsertItem(&temp);

	temp.item.pszText = "left_hand";
	left_hand = pTreeCtrl->InsertItem(&temp);

	temp.hParent = right_arm;
	temp.item.pszText = "right_upper_arm";
	right_upper_arm = pTreeCtrl->InsertItem(&temp);

	temp.item.pszText = "right_lower_arm";
	right_lower_arm = pTreeCtrl->InsertItem(&temp);

	temp.item.pszText = "right_hand";
	right_hand = pTreeCtrl->InsertItem(&temp);

	temp.hParent = left_leg;
	temp.item.pszText = "left_upper_leg";
	left_upper_leg = pTreeCtrl->InsertItem(&temp);

	temp.item.pszText = "left_lower_leg";
	left_lower_leg = pTreeCtrl->InsertItem(&temp);

	temp.item.pszText = "left_foot";
	left_foot = pTreeCtrl->InsertItem(&temp);

	temp.hParent = right_leg;
	temp.item.pszText = "right_upper_leg";
	right_upper_leg = pTreeCtrl->InsertItem(&temp);

	temp.item.pszText = "right_lower_leg";
	right_lower_leg = pTreeCtrl->InsertItem(&temp);

	temp.item.pszText = "right_foot";
	right_foot = pTreeCtrl->InsertItem(&temp);

	CSpinButtonCtrl *pSpin;

	pSpin = (CSpinButtonCtrl*)m_wndSkeletenDialogBar.GetDlgItem(IDC_SPIN_BODYTYPE);
	pSpin->SetRange(0, 1);
	pSpin->SetPos(0);
	
	pSpin = (CSpinButtonCtrl*)m_wndSkeletenDialogBar.GetDlgItem(IDC_SPIN_ORIENTATIONX);
	pSpin->SetRange(0, 1);
	pSpin->SetPos(0);

	pSpin = (CSpinButtonCtrl*)m_wndSkeletenDialogBar.GetDlgItem(IDC_SPIN_ORIENTATIONY);
	pSpin->SetRange(0, 1);
	pSpin->SetPos(0);

	pSpin = (CSpinButtonCtrl*)m_wndSkeletenDialogBar.GetDlgItem(IDC_SPIN_POSITIONY);
	pSpin->SetRange(0, 1);
	pSpin->SetPos(0);

	CString str = "Body Type : ";
	str += (LPCTSTR)BodyTypes[body_id];
	m_wndSkeletenDialogBar.SetDlgItemText(IDC_STATIC_BODYTYPE, (LPCTSTR)str);
	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "Frame Dialog Bar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_FRAMEDIALOGBAR
	//   5. Assign the item a Caption: Frame Dialog Bar

	// TODO: Change the value of CG_ID_VIEW_FRAMEDIALOGBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndFrameDialogBar
		if (!m_wndFrameDialogBar.Create(this, CG_IDD_FRAMEDIALOGBAR,
			CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_FRAMEDIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndFrameDialogBar\n");
			return -1;		// fail to create
		}

		m_wndFrameDialogBar.EnableDocking(CBRS_ALIGN_BOTTOM | CBRS_ALIGN_TOP);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndFrameDialogBar);
	}

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return 0;
}

void CMainFrame::SetRoot(void)
{
   CTreeCtrl *pTreeCtrl = (CTreeCtrl*)m_wndSkeletenDialogBar.GetDlgItem(IDC_BODYTREE);
	pTreeCtrl->SelectItem(pTreeCtrl->GetRootItem());
}

void CMainFrame::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    CTreeCtrl *pTreeCtrl = (CTreeCtrl*)m_wndSkeletenDialogBar.GetDlgItem(IDC_BODYTREE);

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM hNewItem;
	HTREEITEM hOldItem;
    CString str = "Body Type : ";

	hOldItem = pNMTreeView->itemOld.hItem;

	hNewItem = pNMTreeView->itemNew.hItem;

	if(hNewItem != NULL)
	{
	  if(hNewItem == body)
	  {
		  body_id = BODY;
	  }else
	  if(hNewItem == upper_body)
	  {
		  body_id = UPPER_BODY;
	  }else
	  if(hNewItem == lower_body)
	  {
		  body_id = LOWER_BODY;
	  }else
	  if(hNewItem == left_arm)
	  {
		  body_id = LEFT_ARM;
	  }else
	  if(hNewItem == right_arm)
	  {
		  body_id = RIGHT_ARM;
	  }else
	  if(hNewItem == left_leg)
	  {
		  body_id = LEFT_LEG;
	  }else
	  if(hNewItem == right_leg)
	  {
		  body_id = RIGHT_LEG;
	  }else
	  if(hNewItem == left_upper_arm)
	  {
		  body_id = LEFT_UPPER_ARM;
	  }else
	  if(hNewItem == right_upper_arm)
	  {
		  body_id = RIGHT_UPPER_ARM;
	  }else
	  if(hNewItem == left_lower_arm)
	  {
		  body_id = LEFT_LOWER_ARM;
	  }else
	  if(hNewItem == right_lower_arm)
	  {
		  body_id = RIGHT_LOWER_ARM;
	  }else
	  if(hNewItem == left_hand)
	  {
		  body_id = LEFT_HAND;
	  }else
	  if(hNewItem == right_hand)
	  {
		  body_id = RIGHT_HAND;
	  }else
	  if(hNewItem == left_upper_leg)
	  {
		  body_id = LEFT_UPPER_LEG;
	  }else
	  if(hNewItem == right_upper_leg)
	  {
		  body_id = RIGHT_UPPER_LEG;
	  }else
	  if(hNewItem == left_lower_leg)
	  {
		  body_id = LEFT_LOWER_LEG;
	  }else
	  if(hNewItem == right_lower_leg)
	  {
		  body_id = RIGHT_LOWER_LEG;
	  }else
	  if(hNewItem == left_foot)
	  {
		  body_id = LEFT_FOOT;
	  }else
	  if(hNewItem == right_foot)
	  {
		  body_id = RIGHT_FOOT;
	  }else
	if(hNewItem == head)
	{
		body_id = HEAD;
	}else
	if(hNewItem == shoulder)
	{
		body_id = SHOULDER;
	}

	  m_pView->SetActiveBody(body_id);
	  str += (LPCTSTR)BodyTypes[body_id];
	  m_wndSkeletenDialogBar.SetDlgItemText(IDC_STATIC_BODYTYPE, (LPCTSTR)str);
	}
	*pResult = 0;
}

void CMainFrame::SetCurrentBodyToTree(int body_id)
{
	CTreeCtrl *pTreeCtrl = (CTreeCtrl*)m_wndSkeletenDialogBar.GetDlgItem(IDC_BODYTREE);

	switch(body_id)
	{
	  case BODY:
	    pTreeCtrl->SelectItem(body);
	  break;

	  case UPPER_BODY:
		pTreeCtrl->SelectItem(upper_body);
	  break;

	  case HEAD:
		pTreeCtrl->SelectItem(head);
	  break;

	  case SHOULDER:
	    pTreeCtrl->SelectItem(shoulder);
	  break;

	  case LEFT_ARM:
	    pTreeCtrl->SelectItem(left_arm);
	  break;

	  case RIGHT_ARM:
	    pTreeCtrl->SelectItem(right_arm);
	  break;

	  case LEFT_UPPER_ARM:
	    pTreeCtrl->SelectItem(left_upper_arm);
	  break;

	  case RIGHT_UPPER_ARM:
	    pTreeCtrl->SelectItem(right_upper_arm);
	  break;

	  case LEFT_LOWER_ARM:
	    pTreeCtrl->SelectItem(left_lower_arm);
	  break;

	  case RIGHT_LOWER_ARM:
	    pTreeCtrl->SelectItem(right_lower_arm);
	  break;

	  case LEFT_HAND:
	    pTreeCtrl->SelectItem(left_hand);
	  break;

	  case RIGHT_HAND:
	    pTreeCtrl->SelectItem(right_hand);
	  break;

	  case LOWER_BODY:
	    pTreeCtrl->SelectItem(lower_body);
	  break;

	  case LEFT_LEG:
	    pTreeCtrl->SelectItem(left_leg);
	  break;

	  case RIGHT_LEG:
	    pTreeCtrl->SelectItem(right_leg);
	  break;

	  case LEFT_UPPER_LEG:
	    pTreeCtrl->SelectItem(left_upper_leg);
	  break;

	  case RIGHT_UPPER_LEG:
	    pTreeCtrl->SelectItem(right_upper_leg);
	  break;

	  case LEFT_LOWER_LEG:
	    pTreeCtrl->SelectItem(left_lower_leg);
	  break;

	  case RIGHT_LOWER_LEG:
	    pTreeCtrl->SelectItem(right_lower_leg);
	  break;

	  case LEFT_FOOT:
	    pTreeCtrl->SelectItem(left_foot);
	  break;

	  case RIGHT_FOOT:
	    pTreeCtrl->SelectItem(right_foot);
	  break;
	}
}

void CMainFrame::SpinScroll(int ID, UINT updown)
{
	CString str = "Body Type : ";

	switch(ID)
	{
	  case IDC_SPIN_BODYTYPE:
		  if(updown == UP)
		  {
			body_id--;
			if(body_id < BODY)
			{
				body_id = BODY;
			}
		  }else
		  {
			body_id++;
			if(body_id > RIGHT_FOOT)
			{
				body_id = RIGHT_FOOT;
			}
		  }
		  str += (LPCTSTR)BodyTypes[body_id];
		  m_wndSkeletenDialogBar.SetDlgItemText(IDC_STATIC_BODYTYPE, (LPCTSTR)str);
		  m_pView->SetActiveBody(body_id);
		  SetCurrentBodyToTree(body_id);
	  break;

	  case IDC_SPIN_ORIENTATIONX:
		  if(updown == UP)
		  {
		    m_pView->ManipulateBody(-0.01f, 0.0f);
		  }else
		  {
		    m_pView->ManipulateBody(0.01f, 0.0f);
		  }
		  m_pView->Invalidate(FALSE);
	  break;

	  case IDC_SPIN_ORIENTATIONY:
		  if(updown == UP)
		  {
		    m_pView->ManipulateBody(0.0f, -0.001f);
		  }else
		  {
		    m_pView->ManipulateBody(0.0f, 0.001f);
		  }
		  m_pView->Invalidate(FALSE);
	  break;

	  case IDC_SPIN_POSITIONY:
		  if(updown == UP)
		  {
			  m_pView->TranslateBody(-1.0f);
		  }else
		  {
			  m_pView->TranslateBody(1.0f);
		  }
		  m_pView->Invalidate(FALSE);
	  break;
	}
}

void CMainFrame::UpdateOrientation(int body_id, float x, float y)
{
	CString str;

	if(body_id != BODY && body_id != LEFT_ARM &&
        body_id != RIGHT_ARM && body_id != LEFT_LEG &&
		body_id != RIGHT_LEG)
	{
		str.GetBuffer(40);
		str.Format("Orientation X : %f", x);
		m_wndSkeletenDialogBar.SetDlgItemText(IDC_STATIC_ORIENTATIONX, (LPCTSTR)str);

		str.Empty();
		str.GetBuffer(40);
		str.Format("Orientation Y : %f", y);
		m_wndSkeletenDialogBar.SetDlgItemText(IDC_STATIC_ORIENTATIONY, (LPCTSTR)str);
	}else
	{
		str.GetBuffer(40);
		str.Format("Orientation X : None");
		m_wndSkeletenDialogBar.SetDlgItemText(IDC_STATIC_ORIENTATIONX, (LPCTSTR)str);

		str.Empty();
		str.GetBuffer(40);
		str.Format("Orientation Y : None");
		m_wndSkeletenDialogBar.SetDlgItemText(IDC_STATIC_ORIENTATIONY, (LPCTSTR)str);
	}
}

void CMainFrame::UpdatePosition(float height)
{
	CString str;
	str.GetBuffer(40);
	str.Format("Height : %f", height);
	m_wndSkeletenDialogBar.SetDlgItemText(IDC_STATIC_POSITIONY, (LPCTSTR)str);
}

void CMainFrame::UpdateFrame(int iCurrentFrame, int iMaxFrame)
{
	CString str;
	str.GetBuffer(40);
	str.Format("Frame : %d / %d", iCurrentFrame, iMaxFrame);
	m_wndFrameDialogBar.SetDlgItemText(IDC_STATIC_FRAME, (LPCTSTR)str);
}

void CMainFrame::UpdatePlaySpeedInfo(int iPlaySpeed)
{
	CString str;
	str.GetBuffer(40);
	str.Format("Play Speed : %d/30", iPlaySpeed);
	m_wndFrameDialogBar.SetDlgItemText(IDC_STATIC_PLAYSPEED, (LPCTSTR)str);
}

void CMainFrame::AddGroupString(CString *str)
{
	CListBox *pListBox = (CListBox*)m_wndFrameDialogBar.GetDlgItem(IDC_LIST_ANIMGROUP);

	pListBox->AddString(*str);
}

void CMainFrame::DelGroupString(CString *str)
{
	CListBox *pListBox = (CListBox*)m_wndFrameDialogBar.GetDlgItem(IDC_LIST_ANIMGROUP);

	int  index = pListBox->FindStringExact(0, (LPCTSTR)*str);

	if(index == LB_ERR)
	{
		AfxMessageBox("Error occur : Test");
	}else
	{
		pListBox->DeleteString(index);
	}
}

void CMainFrame::SetCurrentAnim(CString *str)
{
	CListBox *pListBox = (CListBox*)m_wndFrameDialogBar.GetDlgItem(IDC_LIST_ANIMGROUP);

	int  index = pListBox->FindStringExact(0, (LPCTSTR)*str);
	if(index == LB_ERR)
	{
		AfxMessageBox("Error occur : Set");
	}else
	{
		pListBox->SetCurSel(index);
	}
}

void CMainFrame::PlaySpeed(int updown)
{
	m_pView->PlaySpeed(updown);
}

void CMainFrame::GetCurrentAnim(CString *str)
{
}

void CMainFrame::ListBoxChange(int  i, CString& str)
{
	m_pView->ChangeCurrentAnimation(i, str);
}

void CMainFrame::ChangeGroupName()
{
	m_pView->ChangeGroupName();
}

void CMainFrame::OnButtonPlay()
{
	m_pView->FramePlay();
}

void CMainFrame::OnButtonStop()
{
	m_pView->FrameStop();
}

void CMainFrame::OnButtonAddGroup()
{
	m_pView->FrameAddGroup();
}

void CMainFrame::OnButtonDelGroup()
{
	m_pView->FrameDelGroup();
}

void CMainFrame::OnButtonAddFrame()
{
	m_pView->FrameAddFrame();
}

void CMainFrame::OnButtonDelFrame()
{
	m_pView->FrameDelFrame();
}

void CMainFrame::OnButtonNext()
{
	m_pView->FrameNext();
}

void CMainFrame::OnButtonPrev()
{
	m_pView->FramePrev();
}

void CMainFrame::OnButtonFirst()
{
	m_pView->FrameFirst();
}

void CMainFrame::OnButtonLast()
{
	m_pView->FrameLast();
}

void CMainFrame::OnToggleAttributebar() 
{
	if(m_wndAttributeBar.IsWindowVisible() == TRUE)
	{
		m_wndAttributeBar.ShowWindow(SW_HIDE);
	}else
	{
		m_wndAttributeBar.ShowWindow(SW_SHOW);
	}

	Invalidate(TRUE);
}

void CMainFrame::OnUpdateToggleAttributebar(CCmdUI* pCmdUI) 
{
	if(m_wndAttributeBar.IsWindowVisible() == TRUE)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}

void CMainFrame::OnToggleManipulatebar() 
{
	if(m_wndManipulateBar.IsWindowVisible() == TRUE)
	{
		m_wndManipulateBar.ShowWindow(SW_HIDE);
	}else
	{
		m_wndManipulateBar.ShowWindow(SW_SHOW);
	}
	Invalidate(TRUE);
}

void CMainFrame::OnUpdateToggleManipulatebar(CCmdUI* pCmdUI) 
{
	if(m_wndManipulateBar.IsWindowVisible() == TRUE)
	{
		pCmdUI->SetCheck(TRUE);
	}else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
		// Erase the icon background when placed over other app window
		DefWindowProc(WM_ICONERASEBKGND, (WORD)dc.m_hDC, 0L);
		
		// Center the icon
		CRect rc;
		GetClientRect(&rc);
		rc.left = (rc.right - ::GetSystemMetrics(SM_CXICON))/2;
		rc.top  = (rc.bottom - ::GetSystemMetrics(SM_CYICON))/2;
		
		// Draw the icon
		dc.DrawIcon(rc.left, rc.top, m_hIcon);
	}
}
