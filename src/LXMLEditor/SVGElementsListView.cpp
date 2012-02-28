#include "stdafx.h"
#include "LXMLEditor2.h"

#include "SVGElementsListView.h"

#define SMALL	21
#define LARGE	42

#if 0

/////////////////////////////////////////////////////////////////////
// CSVGElementListView

HRESULT CSVGElementListView::SetView(long view)
{
	m_view = view;

	InvalidateRect(&m_areaRect);

	ResetVScrollBar();

	return S_OK;
}

HRESULT CSVGElementListView::GetView(long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_view;
	return S_OK;
}

void CSVGElementListView::RemoveItems()
{
	DeselectAll();

#if 0
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		CComQIPtr<ILDOMEventTarget> eventTarget = m_items[i];
		eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
	}
#endif
	m_items.RemoveAll();

	if (m_hWnd)
	{
		InvalidateRect(&m_areaRect);
		ResetVScrollBar();
	}
}

HRESULT CSVGElementListView::AddItem(DWORD/*ILDOMElement* */ element, BSTR name/* = NULL*/)
{
	CSVGListViewItem* pItem = new CSVGListViewItem;
	if (name)
	{
		pItem->m_name = name;
	}
#if 0
	else
	{
		CComBSTR id;
		element->getAttribute(L"id", &id);
		pItem->m_name = id;
	}
#endif
	pItem->m_element = element;
	m_items.Add(pItem);

	if (m_hWnd)
	{
		InvalidateRect(&m_areaRect);
		ResetVScrollBar();
	}

	return S_OK;
}

HRESULT CSVGElementListView::DeleteItem(long index)
{
	m_items.RemoveAt(index);

	InvalidateRect(&m_areaRect);
	ResetVScrollBar();

	return S_OK;
}

bool CSVGElementListView::IsItemSelected(CSVGListViewItem* pItem)
{
	for (int i = 0; i < m_selectedItems.GetSize(); i++)
	{
		if (pItem == m_selectedItems[i])
		{
			return true;
		}
	}

	return false;
}

void CSVGElementListView::DeselectItem(CSVGListViewItem* pItem)
{
	for (int i = 0; i < m_selectedItems.GetSize(); i++)
	{
		if (pItem == m_selectedItems[i])
		{
			m_selectedItems.RemoveAt(i);

			InvalidateRect(&m_areaRect);
			return;
		}
	}
}

void CSVGElementListView::DeselectAll()
{
	if (m_selectedItems.GetSize() > 0)
	{
		for (int i = m_selectedItems.GetSize()-1; i >= 0; i--)
		{
			m_selectedItems.RemoveAt(i);
		}

		InvalidateRect(&m_areaRect);
	}
}

void CSVGElementListView::SelectItem(int index/*ILSVGElement* item*/)
{
	CSVGListViewItem* pItem = m_items[index];

	ATLASSERT(!IsItemSelected(pItem));

	m_selectedItems.Add(pItem);

	InvalidateRect(&m_areaRect);
}

LRESULT CSVGElementListView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT hr;

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return -1;
	m_vert->put_direction(1);

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CSVGElementListView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	return 0;
}

LRESULT CSVGElementListView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CSVGElementListView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	m_axvert.DestroyWindow();
	m_vert.Release();

	return 0;
}

LRESULT CSVGElementListView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.right -= 16;

	m_axvert.MoveWindow(m_areaRect.right, m_areaRect.top, 16, m_areaRect.Height());

	ResetVScrollBar();

	return 0;
}

void CSVGElementListView::ResetVScrollBar()
{
	int itemHeight = (m_view == 0 || m_view == 2)? SMALL: LARGE;

	if (m_view == 0 || m_view == 1)
	{
		int ncolumns = m_areaRect.Width()/itemHeight;
		if (ncolumns == 0) ncolumns = 1;

		int nrows = (m_items.GetSize()+ncolumns-1)/ncolumns;

		int height = nrows*itemHeight;

		m_vert->SetInfo(0, height, m_areaRect.Height());
	}
	else
	{
		m_vert->SetInfo(0, itemHeight*m_items.GetSize(), m_areaRect.Height());
	}
};

LRESULT CSVGElementListView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	ButtonDown(nFlags, point);

	::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GWL_ID), BN_CLICKED), (LPARAM)m_hWnd);

	return 0;
}

LRESULT CSVGElementListView::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GWL_ID), BN_DBLCLK), (LPARAM)m_hWnd);

	return 0;
}

void CSVGElementListView::ButtonDown(UINT nFlags, CPoint point)
{
	long scrollposY; m_vert->get_pos(&scrollposY);

	point.x += -m_areaRect.left;
	point.y += -m_areaRect.top + scrollposY;

	int itemHeight = (m_view == 0 || m_view == 2)? SMALL: LARGE;

	int itemIndex;

	if (m_view == 0 || m_view == 1)	// Small/Large Thumbnails
	{
		int ncolumns = m_areaRect.Width()/itemHeight;
		if (ncolumns == 0) ncolumns = 1;

		itemIndex = (point.y / itemHeight)*ncolumns + point.x/itemHeight;
	}
	else	// Small/Large ListView
	{
		itemIndex = (point.y / itemHeight);
	}

	if (itemIndex >= 0 && itemIndex < m_items.GetSize())
	{
		CSVGListViewItem* pItem = m_items[itemIndex];
		//CComPtr<ILSVGElement> item = m_items[itemIndex]->m_element;

		BOOL bSelected = IsItemSelected(pItem);

		if (!m_multiSelect)
		{
			if (!bSelected)
			{
				DeselectAll();

				SelectItem(itemIndex/*pItem*/);
				m_selectedItemIndex = itemIndex;

				//Fire_ClickSwatch(swatch);
			}
		}
		else
		{
			if (nFlags & MK_CONTROL)	// Toggle selected
			{
				if (bSelected)
				{
					DeselectItem(pItem);
				}
				else
				{
					SelectItem(itemIndex);
					if (m_selectedItemIndex == -1) m_selectedItemIndex = itemIndex;

					//Fire_ClickSwatch(swatch);
				}
			}
			else
			{
				long startSel, endSel;

				if (!(nFlags & MK_SHIFT) || (m_selectedItemIndex == -1))
				{
					startSel = endSel = itemIndex;
				}
				else if (itemIndex > m_selectedItemIndex)
				{
					startSel = m_selectedItemIndex;
					endSel = itemIndex;
				}
				else
				{
					startSel = itemIndex;
					endSel = m_selectedItemIndex;
				}

				DeselectAll();

				for (long i = startSel; i <= endSel; i++)
				{
					//CComPtr<ILSVGElement> item = m_items[i]->m_element;
					SelectItem(i);
				}

				if (!(nFlags & MK_SHIFT) || (m_selectedItemIndex == -1))
					m_selectedItemIndex = itemIndex;

				//Fire_ClickSwatch(swatch);
			}
		}

		InvalidateRect(&m_areaRect);
	}
}

LRESULT CSVGElementListView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	long scrollposY; m_vert->get_pos(&scrollposY);

	if (dc.IntersectClipRect(&m_areaRect) > NULLREGION)
	{
		dc.SetViewportOrg(m_areaRect.left, m_areaRect.top -scrollposY);

		HFONT hOldFont = dc.GetCurrentFont();

		CFont font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		LOGFONT lf;
		font.GetLogFont(&lf);
		lf.lfWeight = FW_BOLD;

		CFont boldFont;
		boldFont.CreateFontIndirect(&lf);

		dc.SetBkMode(TRANSPARENT);

		int itemHeight = (m_view == 0 || m_view == 2)? SMALL: LARGE;

		int ncolumns = m_areaRect.Width()/itemHeight;
		if (ncolumns == 0) ncolumns = 1;

		for (int i = 0; i < m_items.GetSize(); i++)
		{
			int x, y;
			int x2, y2;
			int twidth, theight;

			if (m_view == 0 || m_view == 1)	// Small/Large Thumbnails
			{
				x = i%ncolumns *itemHeight;
				y = i/ncolumns *itemHeight;

				x2 = x+3;
				y2 = y+3;

				twidth = itemHeight-6;
				theight = itemHeight-6;
			}
			else	// Small/Large ListView
			{
				x = 0;
				y = i*itemHeight;

				x2 = x+3;
				y2 = y+3;

				twidth = itemHeight-6;
				theight = itemHeight-6;
			}

			bool bSelected = IsItemSelected(m_items[i]);

			_bstr_t id;
			/*
			if (m_items[i]->m_element)
			{
				BSTR bid;
				m_items[i]->m_element->getAttribute(L"id", &bid);
				id = _bstr_t(bid, false);
			}
			else
				*/
			{
				id = m_items[i]->m_name;
			}

			if (m_view == 2 || m_view == 3)	// Small/Large Listview, display id
			{
				dc.MoveTo(0, y);
				dc.LineTo(m_areaRect.Width(), y);

				dc.FillSolidRect(0, y+1, m_areaRect.Width(), itemHeight-1, GetSysColor(COLOR_WINDOW));

				dc.Draw3dRect(x2-1, y2-1, twidth+2, theight+2, RGB(0, 0, 0), RGB(0, 0, 0));

				if (bSelected)
				{
					dc.SelectFont(boldFont);
					dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
					dc.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));

					dc.FillSolidRect(0, y+2, m_areaRect.Width(), itemHeight-3, dc.GetBkColor());
				}
				else
				{
					dc.SelectFont(font);
					dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
					dc.SetBkColor(GetSysColor(COLOR_WINDOW));
				}

				CRect trect(itemHeight+2, y+3, m_areaRect.Width(), y+itemHeight-3);
				dc.DrawText(id, id.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
			}
			else	// Thumbnails
			{
				dc.Draw3dRect(x, y, itemHeight, itemHeight, RGB(0, 0, 0), RGB(0, 0, 0));

				if (bSelected)
				{
					dc.Draw3dRect(x+2, y+2, itemHeight-4, itemHeight-4, RGB(0,0,0), RGB(0,0,0));
				}
			}

			DRAWITEMSTRUCT dis;
			dis.hDC = dc.m_hDC;
			dis.rcItem = CRect(x2, y2, x2+twidth, y2+theight);
			dis.itemData = (ULONG_PTR)m_items[i];
			::SendMessage(GetParent(), WM_DRAWITEM, 0, (LPARAM)&dis);
		}

		dc.SelectFont(hOldFont);
	}

	return 0;
}

void __stdcall CSVGElementListView::OnVertScroll(long code, long pos)
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

	ScrollWindow(0, oldPos-pos, &rect, &rect);
}

#endif