#include "stdafx.h"
#include "LXMLEditor2.h"
#include "NavigatorOptionsDlg.h"

namespace System
{

static NamedRGBColor Colors[] =
{
	NamedRGBColor(WSTR("Custom"), LDraw::Color()), // Custom
#if 0
	_T("Light Blue"), RGB(74, 132, 255),	// Light Blue
	_T("Light Red"), RGB(255, 74, 74),		// Light Red
	_T("Green"), RGB(74, 255, 74),		// Green
	_T("Medium Blue"), RGB(74, 74, 255),		// Medium Blue
	_T("Yellow"), RGB(255, 255, 74),	// Yellow
	_T("Magenta"), RGB(255, 74, 255),	// Magenta
	_T("Cyan"), RGB(74, 255, 255),	// Cyan
	_T("Light Gray"), RGB(230, 230, 230),	// Light Gray
	_T("Black"), RGB(0, 0, 0),	// Black
#endif
};

#define NCOLORS (sizeof(Colors)/sizeof(NamedRGBColor))

#if 0

/////////////////////////////////////////////////////////////////////////////
// CNavigatorOptionsDlg

void CNavigatorOptionsDlg::SetColorIndex()
{
	Colors[0].color = m_color;
	for (int i = NCOLORS-1; i >= 0; i--)
	{
		if (m_color == Colors[i].color)
		{
			SendDlgItemMessage(IDC_NAV_COLORLIST, CB_SETCURSEL, i, 0);
			break;
		}
	}
}

LRESULT CNavigatorOptionsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hWndList = GetDlgItem(IDC_NAV_COLORLIST);

	for (int i = 0; i < NCOLORS; i++)
	{
		::SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM)Colors[i].name);
	}

	SetColorIndex();

	return 1;  // Let the system set the focus
}

LRESULT CNavigatorOptionsDlg::OnColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CColorDialog dlg(m_color, CC_FULLOPEN | CC_RGBINIT);

	if (dlg.DoModal() == IDOK)
	{
		m_color = dlg.GetColor();
		::InvalidateRect(GetDlgItem(IDC_NAV_COLOR), NULL, TRUE);

		SetColorIndex();
	}

	return 0;
}

LRESULT CNavigatorOptionsDlg::OnChangeColorList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = SendDlgItemMessage(IDC_NAV_COLORLIST, CB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		m_color = Colors[index].color;
		::InvalidateRect(GetDlgItem(IDC_NAV_COLOR), NULL, TRUE);
	}

	return 0;
}

LRESULT CNavigatorOptionsDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT idCtl = (UINT) wParam;             // control identifier 
	LPDRAWITEMSTRUCT lpDrawItemStruct = (LPDRAWITEMSTRUCT) lParam; // item-drawing information 

	CDCHandle	pDC = lpDrawItemStruct->hDC;
	CRect rc = lpDrawItemStruct->rcItem;

	if (idCtl == IDC_NAV_COLOR)
	{
		pDC.DrawEdge(&rc, (lpDrawItemStruct->itemState & ODS_SELECTED)? EDGE_SUNKEN : EDGE_RAISED, BF_RECT | BF_ADJUST);

		rc.InflateRect(-1,-1);
		pDC.FillSolidRect(&rc, m_color);
	}
	else
	{
		int	w = 12;
		int	h = 12;
		
		int id = lpDrawItemStruct->itemID;

		if (id >= 0)
		{
			COLORREF	ref;

			if (lpDrawItemStruct->itemState & ODS_SELECTED)
				ref = ::GetSysColor(COLOR_HIGHLIGHT);
			else
				ref = ::GetSysColor(COLOR_WINDOW);

		//	pDC->FillSolidRect(rc.left+1, rc.top+1, rc.Width()-1, rc.Height()-1, ref);
			pDC.FillSolidRect(&rc, ref);

			if (lpDrawItemStruct->itemState & ODS_FOCUS)
				pDC.DrawFocusRect(&rc);

			if (id >= 1)
			{
				HBRUSH hOldBrush = pDC.SelectBrush((HBRUSH)GetStockObject(NULL_BRUSH));
				pDC.Rectangle(rc.left+1, rc.top+1, rc.left+w+3, rc.top+h+3);
				pDC.SelectBrush(hOldBrush);

				CBrush brush;
				brush.CreateSolidBrush(Colors[id].color);

	/*
	#define MyFillRect(x, y, w, h, br) \
				r.left = x; r.top = y; r.right = x+w; r.bottom = y+h; \
				pDC->FillRect(&r, br)
	*/
				CRect	r(rc.left+2, rc.top+2, rc.left+2+w, rc.top+2+h);
				pDC.FillRect(&r, brush);
			}

			if (lpDrawItemStruct->itemState & ODS_SELECTED)
			{
				pDC.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
				pDC.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			}
			else
			{
				pDC.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
				pDC.SetBkColor(::GetSysColor(COLOR_WINDOW));
			}

			pDC.TextOut(rc.left+((id >= 1)? (w+6): 4), rc.top+2, (LPCTSTR)lpDrawItemStruct->itemData);
		}
	}
	
	return 0;
}

#endif

}
