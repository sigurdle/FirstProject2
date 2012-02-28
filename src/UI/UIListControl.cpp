// UIListControl.cpp : Implementation of CUIListControl
#include "stdafx.h"
#include "UI.h"
#include "UIListControl.h"

/////////////////////////////////////////////////////////////////////////////
// CUIListControl

HRESULT CUIListControl::OnDraw(ATL_DRAWINFO& di)
{
	if (m_hWnd)
	{
		HDC hDC = di.hdcDraw;

		HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));
		CRect client;
		GetClientRect(&client);
	//	FillSolidRect(hDC, &client, RGB(190, 190, 190));

	//	DrawEdge(hDC, &client, EDGE_ETCHED, BF_RECT);
		Draw3DRect(hDC, 0, 0, client.Width(), client.Height(), RGB(190, 190, 190), RGB(190, 190, 190));
		Draw3DRect(hDC, 1, 1, client.Width()-2, client.Height()-2, RGB(0, 0, 0), RGB(190, 190, 190));

		int state = SaveDC(hDC);
		IntersectClipRect(hDC, 2, 2, client.right-2, client.bottom-2);

		long scrollposY; m_vert->get_pos(&scrollposY);

		POINT oldOrg;
		OffsetViewportOrgEx(hDC, 2, 2 - scrollposY, &oldOrg);

		int y = 0;

		for (int i = 0; i < m_listEntries.GetSize(); i++)
		{
			CListEntry* pEntry = m_listEntries[i];

			CRect itemrect(0, y, client.right, y+16);

			/*
			if (m_customDraw != NULL)
			{
				m_customDraw->Draw(1, NULL, reinterpret_cast<IUnknown*>(this), hDC, i, pEntry->m_data, (i == m_cursel)? 1: 0, itemrect);
			}
			else
			*/
			{
				if (i == m_cursel)
				{
					SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
					SetBkColor(hDC, GetSysColor(COLOR_HIGHLIGHT));
					SetBkMode(hDC, OPAQUE);

					FillSolidRect(hDC, &itemrect, GetSysColor(COLOR_HIGHLIGHT));
				}
				else
				{
					SetTextColor(hDC, GetSysColor(COLOR_BTNTEXT));
					SetBkMode(hDC, TRANSPARENT);
				}

				CRect trect = itemrect;
				if (m_nCheckStyle)
				{
					CRect cbrect(0, y, 16, y+16);
					DrawFrameControl(hDC, &cbrect, DFC_BUTTON, DFCS_BUTTONCHECK | (pEntry->m_check?DFCS_CHECKED: 0));

					trect.left += 18;
				}

				DrawText(hDC, pEntry->m_string, pEntry->m_string.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
			}

			y += m_itemHeight;
		}

		RestoreDC(hDC, state);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		SelectObject(hDC, hOldFont);
	}

	return 0;
}

LRESULT CUIListControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = m_hWnd;

	IUnknown* p;
	CRect rc(0,0,0,0);

//	m_axhorz.Create(hwnd, rc, NULL, WS_CHILD | WS_VISIBLE);
//	m_axhorz.AttachControl(m_horz, &p);

	m_axvert.Create(hwnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	return 0;
}

long CUIListControl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_hWnd)
	{
		int cx = m_rcPos.right - m_rcPos.left;
		int cy = m_rcPos.bottom - m_rcPos.top;

		int sbWidth = GetSystemMetrics(SM_CYHSCROLL);
		int sbHeight = 0;//GetSystemMetrics(SM_CXVSCROLL);

		::MoveWindow(m_axvert.m_hWnd, cx-sbWidth-2, 2, sbWidth, cy-sbHeight-2, TRUE);
		::ShowWindow(m_axvert.m_hWnd, SW_SHOW);

		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return 0;
}

void CUIListControl::OnSize()
{
	int cy = m_rcPos.bottom - m_rcPos.top-4;

	m_vert->SetInfo(0, m_listEntries.GetSize()*m_itemHeight, cy);
}

HRESULT __stdcall CUIListControl::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect client;
	GetClientRect(&client);

	int sbWidth = GetSystemMetrics(SM_CYHSCROLL);
	int sbHeight = GetSystemMetrics(SM_CXVSCROLL);

	CRect rect(2, 2,
		client.Width() - sbWidth, client.bottom-2);

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);

	return S_OK;
}

long CUIListControl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_hWnd)
	{
		POINT point;
		point.x = (short)LOWORD(lParam);
		point.y = (short)HIWORD(lParam);

		long scrollposY; m_vert->get_pos(&scrollposY);

		point.y -= 2;	// Border
		point.y += scrollposY;

		int index = point.y / 16;

		if (index < 0) index = 0;
		else if (index > m_listEntries.GetSize()-1) index = m_listEntries.GetSize()-1;

		m_cursel = index;

		Fire_curselchange();

		if (m_nCheckStyle)
		{
			if (point.x < 16)
			{
				m_listEntries[index]->m_check = !m_listEntries[index]->m_check;
				Fire_checkitem();
			}
		}

		InvalidateRect(NULL, TRUE);
	}

	return 0;
}

STDMETHODIMP CUIListControl::AddString(BSTR string, long *index)
{
	if (index == NULL) return E_POINTER;

	CListEntry* pEntry = new CListEntry;
	pEntry->m_string = string;
	pEntry->m_data = 0;

	*index = m_listEntries.Add(pEntry);

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CUIListControl::get_cursel(long *pVal)
{
	*pVal = m_cursel;
	return S_OK;
}

STDMETHODIMP CUIListControl::put_cursel(long newVal)
{
	m_cursel = newVal;
	InvalidateRect(NULL, TRUE);
	return S_OK;
}

STDMETHODIMP CUIListControl::SetItemData(long index, DWORD data)
{
	m_listEntries[index]->m_data = data;
	return S_OK;
}

STDMETHODIMP CUIListControl::GetItemData(long index, DWORD *data)
{
	*data = m_listEntries[index]->m_data;
	return S_OK;
}

STDMETHODIMP CUIListControl::ResetContent()
{
	for (int i = 0; i < m_listEntries.GetSize(); i++)
	{
		CListEntry* pEntry = m_listEntries[i];
		delete pEntry;
	}

	m_listEntries.RemoveAll();

	InvalidateRect(NULL, TRUE);
	OnSize();

	m_cursel = -1;
	Fire_curselchange();

	return S_OK;
}

/*
STDMETHODIMP CUIListControl::SetCustomDraw(ICustomDraw *custom)
{
	m_customDraw = custom;
	return S_OK;
}
*/

STDMETHODIMP CUIListControl::GetItemText(unsigned long index, BSTR *pVal)
{
	if (index >= 0 && index < m_listEntries.GetSize())
	{
		*pVal = SysAllocString(m_listEntries[index]->m_string);
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CUIListControl::get_CheckStyle(DWORD *pVal)
{
	*pVal = m_nCheckStyle;

	return S_OK;
}

STDMETHODIMP CUIListControl::put_CheckStyle(DWORD newVal)
{
	m_nCheckStyle = newVal;

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CUIListControl::SetCheck(long index, DWORD check)
{
	m_listEntries[index]->m_check = check;
	InvalidateRect(NULL, TRUE);

	return S_OK;
}

STDMETHODIMP CUIListControl::GetCheck(long index, DWORD *check)
{
	if (check == NULL) return E_POINTER;
	*check = m_listEntries[index]->m_check;

	return S_OK;
}

STDMETHODIMP CUIListControl::get_multipleSelect(BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_multipleSelect;
	return S_OK;
}

STDMETHODIMP CUIListControl::put_multipleSelect(BOOL newVal)
{
	m_multipleSelect = newVal;
	return S_OK;
}
