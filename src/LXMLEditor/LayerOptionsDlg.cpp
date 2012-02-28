// LayerOptionsDlg.cpp : Implementation of CLayerOptionsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "LayerOptionsDlg.h"

namespace System
{

extern NamedRGBColor gLayerColors[];
extern int gNumLayerColors;

#if 0

/////////////////////////////////////////////////////////////////////////////
// CLayerOptionsDlg

void CLayerOptionsDlg::SetColorIndex()
{
//	gLayerColors[0].color = m_color;
	for (int i = 0; i < gNumLayerColors; i++)
	{
		if (m_color == gLayerColors[i].color)
		{
			SendDlgItemMessage(IDC_LAYER_COLORLIST, CB_SETCURSEL, i, 0);
			return;
		}
	}

// Other
	SendDlgItemMessage(IDC_LAYER_COLORLIST, CB_SETCURSEL, i, 0);
}

LRESULT CLayerOptionsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_isLayer == 2 /*BST_INDETERMINATE*/)
	{
		CWindow wnd(GetDlgItem(IDC_LAYER_ISLAYER));
		wnd.ModifyStyle(0, BS_AUTO3STATE);
	}

	CheckDlgButton(IDC_LAYER_ISLAYER, m_isLayer);

	HWND hWndList = GetDlgItem(IDC_LAYER_COLORLIST);

	for (int i = 0; i < gNumLayerColors; i++)
	{
		::SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM)gLayerColors[i].name);
	}

	::SendMessage(hWndList, CB_ADDSTRING, 0, (LPARAM)_T("Other"));

	SetColorIndex();

	return 1;  // Let the system set the focus
}

LRESULT CLayerOptionsDlg::OnColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CColorDialog dlg(m_color, CC_FULLOPEN | CC_RGBINIT);

	if (dlg.DoModal() == IDOK)
	{
		m_color = dlg.GetColor();
		::InvalidateRect(GetDlgItem(IDC_LAYER_COLOR), NULL, TRUE);

		SetColorIndex();
	}

	return 0;
}

LRESULT CLayerOptionsDlg::OnChangeColorList(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = SendDlgItemMessage(IDC_LAYER_COLORLIST, CB_GETCURSEL, 0, 0);
	if (index >= 0)
	{
		if (index < gNumLayerColors)
		{
			m_color = gLayerColors[index].color;
			::InvalidateRect(GetDlgItem(IDC_LAYER_COLOR), NULL, TRUE);
		}
		else
		{
			CColorDialog dlg(m_color, CC_FULLOPEN | CC_RGBINIT);

			if (dlg.DoModal() == IDOK)
			{
				m_color = dlg.GetColor();
				::InvalidateRect(GetDlgItem(IDC_LAYER_COLOR), NULL, TRUE);

				SetColorIndex();
			}
		}
	}

	return 0;
}

LRESULT CLayerOptionsDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT idCtl = (UINT) wParam;             // control identifier 
	LPDRAWITEMSTRUCT lpDrawItemStruct = (LPDRAWITEMSTRUCT) lParam; // item-drawing information 

	CDCHandle pDC = lpDrawItemStruct->hDC;
	CRect rc = lpDrawItemStruct->rcItem;

	if (idCtl == IDC_LAYER_COLOR)
	{
		pDC.DrawEdge(&rc, (lpDrawItemStruct->itemState & ODS_SELECTED)? EDGE_SUNKEN : EDGE_RAISED, BF_RECT | BF_ADJUST);

		rc.InflateRect(-1,-1);
		pDC.FillSolidRect(&rc, m_color);
	}
	else
	{
		int w = 12;
		int h = 12;

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

			if (id < gNumLayerColors)
			{
				HBRUSH hOldBrush = pDC.SelectBrush((HBRUSH)GetStockObject(NULL_BRUSH));
				pDC.Rectangle(rc.left+1, rc.top+1, rc.left+w+3, rc.top+h+3);
				pDC.SelectBrush(hOldBrush);

				CBrush brush;
				brush.CreateSolidBrush(gLayerColors[id].color);

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

			pDC.TextOut(rc.left+((id < gNumLayerColors)? (w+6): 4), rc.top+2, (LPCTSTR)lpDrawItemStruct->itemData);
		}
	}
	
	return 0;
}

#endif

}
