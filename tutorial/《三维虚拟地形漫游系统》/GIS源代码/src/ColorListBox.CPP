#include "stdafx.h"
#include "ColorListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorListBox

CColorListBox::CColorListBox()
{
}

CColorListBox::~CColorListBox()
{
}


BEGIN_MESSAGE_MAP(CColorListBox, CListBox)
	//{{AFX_MSG_MAP(CColorListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorListBox message handlers




void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpdis) 
{
if (lpdis->itemID < 0)
return; 
	COLORREF cr=(COLORREF)lpdis->itemData;//RGB in item data
COLORREF cvText;
COLORREF cvBack;
CString itemString; 

if ((lpdis->itemState & ODS_SELECTED) && // if item has been selected
(lpdis->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 


if (!(lpdis->itemState & ODS_SELECTED) && // if item has been deselected
(lpdis->itemAction & ODA_SELECT))
DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 


if(lpdis->itemData) // if color information is present
cvText = SetTextColor(lpdis->hDC, RGB(0,0,0));
else // if no color information, use default system colors
cvText = SetTextColor(lpdis->hDC, RGB(255,255,255));//GetSysColor((lpdis->itemState & ODS_SELECTED)
//? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT)); 

// always use system colors for background
cvBack = SetBkColor(lpdis->hDC, cr);//GetSysColor((lpdis->itemState & ODS_SELECTED)
//? COLOR_HIGHLIGHT : COLOR_WINDOW)); 

// get and display item text
GetText(lpdis->itemID, itemString );
DrawText(lpdis->hDC, itemString, -1, &lpdis->rcItem, DT_LEFT | DT_SINGLELINE); 

// restore DC colors
SetTextColor(lpdis->hDC, cvText); 
SetBkColor(lpdis->hDC,cr); 
 


	CDC*pDC=CDC::FromHandle(lpdis->hDC);



	if(lpdis->itemAction & ODA_DRAWENTIRE)
	{
		CBrush br(cr);
		pDC->FillRect(&lpdis->rcItem,&br);

	}

    if((lpdis->itemState & ODS_SELECTED)&&
       (lpdis->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
    {
         COLORREF crHilite=RGB(255-GetRValue(cr),255-GetGValue(cr),255-GetBValue(cr ));
         CBrush br( crHilite);
         pDC->FrameRect( &lpdis->rcItem,&br );
    }
	
    if(!(lpdis->itemState&ODS_SELECTED)&&(lpdis->itemAction&ODA_SELECT))
	{
		CBrush br( cr);
        pDC->FrameRect(&lpdis->rcItem,&br);
	}
} 


//***********************************************
// original AddString() method
//
// purpose: Add a string to the listbox
//
// parameters: 
// lpszItem: pointer to item text
//
// remarks:
// provided because CListBox::AddString is 
// NOT virtual
//
// return: item index
//***********************************************
int CColorListBox::AddString( LPCTSTR lpszItem)
{
return ((CListBox*)this)->AddString(lpszItem);
} 


//***********************************************
// new AddString() method
//
// purpose: Add a string to the listbox
//
// parameters: 
// lpszItem: pointer to item text
// rgb: text color as a COLORREF
//
// return: item index
//***********************************************
int CColorListBox::AddString( LPCTSTR lpszItem,COLORREF rgb )
{
	  
int item = AddString(lpszItem);
if(item >=0)
SetItemData(item,rgb);
return item;
} 


//***********************************************
// new InsertString() method
//
// purpose: Insert a string to the listbox
//
// parameters: 
// nIndex: index of inserted item
// lpszItem: pointer to item text
// rgb: text color as a COLORREF
//
// return: item index
//***********************************************
int CColorListBox::InsertString( int nIndex, LPCTSTR lpszItem, COLORREF rgb)
{
int item = ((CListBox*)this)->InsertString(nIndex,lpszItem);
if(item >=0)
SetItemData(item,rgb);
return item; 

}

//void CColorListBox::AddColorItem(COLORREF color)
//{
//  //Listbox does not have the LBS_HASSTRINGS style£¬so the
//  
//	//normal listbox string is used to store an RGB color
//     
//int item=AddString((LPCTSTR) color);
// 
//	
//    
//}
//
#define COLOR_ITEM_HEIGHT     20
void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{ 
	 AfxMessageBox("1");
         lpMIS->itemHeight =COLOR_ITEM_HEIGHT;
}

//void CColorListBox::Drawltem(LPDRAWITEMSTRUCT lpDIS)
//{
//	 
//
//	CDC*pDC=CDC::FromHandle(lpDIS->hDC);
//
//	COLORREF cr=(COLORREF)lpDIS->itemData;//RGB in item data
//
//	if(lpDIS->itemAction & ODA_DRAWENTIRE)
//	{
//		CBrush br(cr);
//		pDC->FillRect(&lpDIS->rcItem,&br);
//
//	}
//
//    if((lpDIS->itemState & ODS_SELECTED)&&
//       (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
//    {
//         COLORREF crHilite=RGB(255-GetRValue(cr),255-GetGValue(cr),255-GetBValue(cr ));
//         CBrush br( crHilite);
//         pDC->FrameRect( &lpDIS->rcItem,&br );
//    }
//	
//    if(!(lpDIS->itemState&ODS_SELECTED)&&(lpDIS->itemAction&ODA_SELECT))
//	{
//		CBrush br( cr);
//        pDC->FrameRect(&lpDIS->rcItem,&br);
//	}
//}


//int CColorListBox::Compareltem(LPCOMPAREITEMSTRUCT lpCIS)
//{	 AfxMessageBox("3");
//
//	COLORREF cr1=(COLORREF)lpCIS->itemData1;
//
//	COLORREF cr2=(COLORREF)lpCIS->itemData2;
//
//	if(cr1== cr2)  return 0;//exact match
//
//	int intensity1=GetRValue(cr1)+GetGValue(cr1)+GetBValue(cr1);
//
//	int intensity2=GetRValue(cr2)+GetGValue(cr2)+GetBValue(cr2);
//
//	if(intensity1<intensity2)
//           return-1;//lower intensity goes first
//    else if(intensity1>intensity2)
//           return 1;//higher intensity goes second
//    if(GetBValue(cr1)>GetBValue(cr2))
//          return -1;
//    else if(GetGValue(cr1)>GetGValue(cr2))
//          return -3;
//    else if(GetRValue(cr1)>GetRValue(cr2))
//          return -1;
//    else
//         return 1;
//}
