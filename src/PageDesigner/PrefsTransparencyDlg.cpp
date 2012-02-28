// PrefsTransparencyDlg.cpp : Implementation of CPrefsTransparencyDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PrefsTransparencyDlg.h"

int gridSize[][2] =
{
	4, 4,
	8, 8,
	16, 16,
	32, 32,
};

static COLORREF gridColors[][2] =
{
	0, 0,	// Custom
	{RGB(255, 255, 255), RGB(255, 255, 255)},
	{RGB(255, 255, 255), RGB(194, 194, 194)},
	{RGB(137, 137, 137), RGB(83, 83, 83)},
	{RGB(36, 36, 36), RGB(83, 83, 83)},
	{RGB(255, 255, 255), RGB(255, 194, 194)},
	{RGB(255, 255, 255), RGB(255, 208, 177)},
	{RGB(255, 255, 255), RGB(194, 222, 194)},
	{RGB(255, 255, 255), RGB(194, 218, 247)},
	{RGB(255, 255, 255), RGB(213, 194, 247)},
};

/////////////////////////////////////////////////////////////////////////////
// CPrefsTransparencyDlg

void CPrefsTransparencyDlg::SetColorIndex()
{
	gridColors[0][0] = m_gridColor0;
	gridColors[0][1] = m_gridColor1;

	for (int i = 9; i >= 0; i--)
	{
		if (	(m_gridColor0 == gridColors[i][0]) &&
				(m_gridColor1 == gridColors[i][1]))
		{
			::SendMessage(GetDlgItem(IDC_PREFSTRANSP_GRIDCOLORS), CB_SETCURSEL, i, 0);
			break;
		}
	}
}

void CPrefsTransparencyDlg::FillPreviewBitmap()
{
		/*
	if (m_gridSize >= 0)
	{
		int	gridX = gridSize[m_gridSize][0];
		int	gridY = gridSize[m_gridSize][1];
		int	cols = (m_previewRect.Width()+gridX-1)/gridX;
		int	rows = (m_previewRect.Height()+gridY-1)/gridY;

		for (int row = 0; row < rows; row++)
		{
			int	y = row*gridY;

			for (int col = 0; col < cols; col++)
			{
				int	x = col*gridX;

				COLORREF	ref;

				if (col+row & 1)
					ref = RGB(0, 0, 0);
				else
					ref = RGB(255, 255, 255);

				m_dc2.FillSolidRect(x, y, gridX, gridY, ref);
			}
		}
	}
	*/
}

LRESULT CPrefsTransparencyDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hCombo;
	
	hCombo = GetDlgItem(IDC_PREFSTRANSP_GRIDSIZE);
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Tiny"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Small"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Medium"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Large"));

	hCombo = GetDlgItem(IDC_PREFSTRANSP_GRIDCOLORS);
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Custom"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("White"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Light"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Medium"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Dark"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Red"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Orange"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Green"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Blue"));
	::SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)_T("Purple"));

	m_targetObject->get_transpGridColor0(&m_gridColor0);
	m_targetObject->get_transpGridColor1(&m_gridColor1);

	SetColorIndex();

	long gridSizeX;
	m_targetObject->get_transpGridSizeX(&gridSizeX);
	for (m_gridSize = 0; m_gridSize < 4-1; m_gridSize++)
	{
		if (gridSize[m_gridSize][0] >= gridSizeX)
			break;
	}

	::SendMessage(GetDlgItem(IDC_PREFSTRANSP_GRIDSIZE), CB_SETCURSEL, m_gridSize, 0);

	FillPreviewBitmap();

	return 1;  // Let the system set the focus
}

BOOL CPrefsTransparencyDlg::OnApply()
{
	m_targetObject->setTranspGrid(gridSize[m_gridSize][0], gridSize[m_gridSize][1], m_gridColor0, m_gridColor1);

	return TRUE;
}

LRESULT CPrefsTransparencyDlg::OnChangeGridSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_gridSize = ::SendMessage(GetDlgItem(IDC_PREFSTRANSP_GRIDSIZE), CB_GETCURSEL, 0, 0);

	SetModified();

	return 0;
}

LRESULT CPrefsTransparencyDlg::OnChangeGridColors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = ::SendMessage(GetDlgItem(IDC_PREFSTRANSP_GRIDCOLORS), CB_GETCURSEL, 0, 0);

	m_gridColor0 = gridColors[index][0];
	m_gridColor1 = gridColors[index][1];

	SetModified();
/*
	InvalidateRect(m_previewRect);
	InvalidateRect(m_color1Rect);
	InvalidateRect(m_color2Rect);
*/
	return 0;
}

LRESULT CPrefsTransparencyDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	UINT id = (UINT) wParam;             // control identifier 
	LPDRAWITEMSTRUCT lpDrawItemStruct = (LPDRAWITEMSTRUCT) lParam; // item-drawing information 

	int	w = 4;
	int	h = 4;
	
	int itemID = lpDrawItemStruct->itemID;

	if (itemID >= 0)
	{
		CDCHandle	dc = lpDrawItemStruct->hDC;
		CDCHandle* pDC = &dc;
		CRect& rc = (CRect)lpDrawItemStruct->rcItem;

		COLORREF	ref;

		if (lpDrawItemStruct->itemState & ODS_SELECTED)
			ref = ::GetSysColor(COLOR_HIGHLIGHT);
		else
			ref = ::GetSysColor(COLOR_WINDOW);

	//	pDC->FillSolidRect(rc.left+1, rc.top+1, rc.Width()-1, rc.Height()-1, ref);
		pDC->FillSolidRect(&rc, ref);

		if (lpDrawItemStruct->itemState & ODS_FOCUS)
			pDC->DrawFocusRect(&rc);

		if (itemID >= 1)
		{
			CBrush	pOldBrush = pDC->SelectBrush((HBRUSH)GetStockObject(NULL_BRUSH));
			pDC->Rectangle(rc.left+1, rc.top+1, rc.left+w+w+w+3, rc.top+h+h+h+3);
			pDC->SelectBrush(pOldBrush);

			CBrush	brush1;
			brush1.CreateSolidBrush(gridColors[itemID][0]);
			CBrush	brush2;
			brush2.CreateSolidBrush(gridColors[itemID][1]);

			RECT	r;

#define MyFillRect(x, y, w, h, br) \
			r.left = x; r.top = y; r.right = x+w; r.bottom = y+h; \
			pDC->FillRect(&r, br)

			MyFillRect(rc.left+2, rc.top+2, w, h, brush1);
			MyFillRect(rc.left+2+w, rc.top+2, w, h, brush2);
			MyFillRect(rc.left+2+w+w, rc.top+2, w, h, brush1);
			MyFillRect(rc.left+2, rc.top+h+2, w, h, brush2);
			MyFillRect(rc.left+2+w, rc.top+h+2, w, h, brush1);
			MyFillRect(rc.left+2+w+w, rc.top+h+2, w, h, brush2);
			MyFillRect(rc.left+2, rc.top+h+h+2, w, h, brush1);
			MyFillRect(rc.left+2+w, rc.top+h+h+2, w, h, brush2);
			MyFillRect(rc.left+2+w+w, rc.top+h+h+2, w, h, brush1);
		}

		if (lpDrawItemStruct->itemState & ODS_SELECTED)
		{
			pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
			pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		}
		else
		{
			pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
			pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
		}

		TCHAR lbtext[256];
		::SendMessage(lpDrawItemStruct->hwndItem, CB_GETLBTEXT, itemID, (LPARAM)lbtext);
		pDC->TextOut(rc.left+((itemID >= 1)? (w+w+8): 4), rc.top+2, lbtext);
	}

	return 0;
}