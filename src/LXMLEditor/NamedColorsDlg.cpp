// NamedColorsDlg.cpp : Implementation of CNamedColorsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "NamedColorsDlg.h"

#include "../LXML/NamedColors.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CNamedColorsDlg

int CNamedColorsDlg::FinalConstruct()
{
	HRESULT hr;

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);

	return S_OK;
}

void CNamedColorsDlg::FinalRelease()
{
	m_vert.Release();
}

LRESULT CNamedColorsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CNamedColorsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

//	m_scroll.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_VISIBLE | WS_CHILD | SBS_VERT);

	return 0;
}

LRESULT CNamedColorsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	IDispEventImpl<1, CNamedColorsDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[0]);
	IDispEventImpl<2, CNamedColorsDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[1]);
	IDispEventImpl<3, CNamedColorsDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[2]);
//	IDispEventImpl<4, CNamedColorsDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[3]);

	for (int i = 0; i < 4; i++)
	{
		m_slider[i].Release();
	}
#endif

	return 0;
}

LRESULT CNamedColorsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	client.InflateRect(-GetSystemMetrics(SM_CXEDGE),-GetSystemMetrics(SM_CYEDGE));

	m_areaRect = client;
	m_areaRect.right -= 16;	// Make room for scrollbar

	m_axvert.MoveWindow(m_areaRect.right, m_areaRect.top, 16, m_areaRect.Height());
	m_vert->SetInfo(0, NamedColorsCount, (m_areaRect.Height()+16-1)/16);

	/*
	m_scroll.MoveWindow(m_areaRect.right, m_areaRect.top, 16, m_areaRect.Height());

	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_PAGE | SIF_RANGE;
	si.nMin = 0;
	si.nMax = NamedColorsCount;
	si.nPage = (m_areaRect.Height())/16;

	m_scroll.SetScrollInfo(&si, TRUE);
*/

	return 0;
}

LRESULT CNamedColorsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

//	long pos;
//	m_vert->get_pos(&pos);
//	pos = m_scroll.GetScrollPos();

//	CString str;
//	str.Format("%d", pos);

//	dc.TextOut(0, 0, str, str.GetLength());

	CRect client;
	GetClientRect(&client);

	dc.DrawEdge(&client, EDGE_SUNKEN, BF_RECT/*, BF_ADJUST*/);

	if (dc.IntersectClipRect(m_areaRect) > NULLREGION)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);
		//long scrollposY = m_scroll.GetScrollPos();

		dc.SetBkMode(TRANSPARENT);
		HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

		CPoint oldOrg;
		dc.SetViewportOrg(m_areaRect.left, m_areaRect.top -scrollposY*16, &oldOrg);

		int y = 0;

		for (int i = 0; i < NamedColorsCount; i++)
		{
			CRect itemrect(0, y, m_areaRect.Width(), y+16);

			CRect crect = itemrect;
			crect.right = 20;
			crect.InflateRect(-1, -1);
			dc.FillSolidRect(&crect, ColorNames[i].clr);

			CRect trect = itemrect;
			trect.left = 20;

			dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));

			if (m_index == i)
			{
				if (m_color == ColorNames[i].clr)
				{
					dc.FillSolidRect(&trect, GetSysColor(COLOR_HIGHLIGHT));
					dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
				}
				else
				{
					dc.DrawFocusRect(&trect);
				}
			}

			trect.left += 2;
			trect.InflateRect(-1, -1);

			_bstr_t name = ColorNames[i].name;
			dc.DrawText(name, name.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

			y += 16;
		}

		dc.SetViewportOrg(oldOrg.x, oldOrg.y, NULL);
		dc.SelectFont(hOldFont);
	}

	long pos; m_vert->get_pos(&pos);
//	long pos = m_scroll.GetScrollPos();

	dc.SetBkMode(OPAQUE);

	CString str;
	str.Format("%d pos: %d", NamedColorsCount, pos);

	dc.TextOut(0, 0, str, str.GetLength());

	return 0;
}

LRESULT CNamedColorsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	point.x -= m_areaRect.left;
	point.y -= m_areaRect.top;
	point.y += scrollposY*16;

	int index = point.y/16;

	if (index >= 0 && index < NamedColorsCount)
	{
		COLORREF clr = ColorNames[index].clr;
		m_site->SetRGBColorValue(GetRValue(clr), GetGValue(clr), GetBValue(clr));
	}

	return 0;
}

int CNamedColorsDlg::FindClosest(COLORREF clr)
{
	int diff = 9999999;
	int index = -1;

	for (int i = 0; i < NamedColorsCount; i++)
	{
		int d = clr-ColorNames[i].clr;
		if (d == 0)	// Exact match
		{
			return i;
		}
		else
		{
			d = abs(d);
			if (d < diff)
			{
				diff = d;
				index = i;
			}
		}
	}

	return index;
}

STDMETHODIMP CNamedColorsDlg::SetRGBColorValue(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue)
{
	if (red >= 0 && red <= 255 &&
		green >= 0 && green <= 255 &&
		blue >= 0 && blue <= 255)
	{
		m_color =  RGB(red, green, blue);
		m_index = FindClosest(m_color);
	}
	else
	{
		m_color = -1;
		m_index = -1;
	}

	if (m_hWnd)
	{
		InvalidateRect(&m_areaRect);
	}

	return S_OK;
}

void __stdcall CNamedColorsDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	/*
	if (m_edit)
	{
		CRect wrect;
		::GetWindowRect(m_edit, &wrect);
		ScreenToClient((LPPOINT)&wrect.left);
		ScreenToClient((LPPOINT)&wrect.right);
		::SetWindowPos(m_edit, NULL, wrect.left, wrect.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOREDRAW);
	}
	*/

	CRect	rect = m_areaRect;
	m_vert->put_pos(pos);
	//ScrollWindow(0, (oldPos-pos)*16, &rect, &rect);
	Invalidate();
}

LRESULT CNamedColorsDlg::OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nScrollCode = (int) LOWORD(wParam); // scroll bar value 
	int nPos = (short int) HIWORD(wParam);  // scroll box position 

	if (nScrollCode == SB_THUMBTRACK)
	{
		m_scroll.SetScrollPos(nPos);

		Invalidate();
	}

	return 0;
}

#endif