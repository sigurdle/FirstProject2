#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PagesDlg.h"

//#include "PageDesignerApp.h"
//#include "PageDesignerFrame.h"

#include "PDDocumentView.h"

static SIZE pageSize[] =
{
	12,			18,
	12*1.33,		18*1.33,
	12*1.66,		18*1.66,
	12*2,			18*2,
};

//extern CPageDesignerApp* gApp;

static DrawPage(HDC hDC, CRect rc, int spine, bool bSelected)
{
	BeginPath(hDC);

	if (spine == 0)
	{
		MoveToEx(hDC, rc.left+4, rc.top, NULL);
		LineTo(hDC, rc.right, rc.top);
		LineTo(hDC, rc.right, rc.bottom);
		LineTo(hDC, rc.left, rc.bottom);
		LineTo(hDC, rc.left, rc.top+4);
		LineTo(hDC, rc.left+4, rc.top);
		LineTo(hDC, rc.left+4, rc.top+4);
		LineTo(hDC, rc.left, rc.top+4);
	}
	else
	{
		MoveToEx(hDC, rc.right-4, rc.top, NULL);
		LineTo(hDC, rc.left, rc.top);
		LineTo(hDC, rc.left, rc.bottom);
		LineTo(hDC, rc.right, rc.bottom);
		LineTo(hDC, rc.right, rc.top+4);
		LineTo(hDC, rc.right-4, rc.top);
		LineTo(hDC, rc.right-4, rc.top+4);
		LineTo(hDC, rc.right, rc.top+4);
	}

	HBRUSH hBrush;

	if (bSelected)
		hBrush = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
	else
		hBrush = CreateSolidBrush(RGB(255, 255, 255));

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	EndPath(hDC);
	StrokeAndFillPath(hDC);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}

/////////////////////////////
// CSpreadsWnd

LRESULT CSpreadsWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CSpreadsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	::RegisterDragDrop(m_hWnd, static_cast<IDropTarget*>(this));
	return 0;
}

LRESULT CSpreadsWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CSpreadsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	::RevokeDragDrop(m_hWnd);
	return 0;
}

LRESULT CSpreadsWnd::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	if (m_view != NULL)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		HFONT hFont = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

		SetBkMode(hDC, TRANSPARENT);

		if (IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
		{
			SetViewportOrgEx(hDC, m_areaRect.left, m_areaRect.top - scrollposY, NULL);

			CComPtr<IObjectMap> spreads;
			m_view->m_document->get_spreads(&spreads);

			int pageCount = 1;

			long nspreads;
			spreads->get_length(&nspreads);

			int y = 4;

			CComPtr<IPDSection> section;
			m_view->m_document->get_firstSection(&section);

			for (int nspread = 0; nspread < nspreads; nspread++)
			{
				CComPtr<IPDSpreadDocument> spread;
				spreads->item(nspread, (IUnknown**)&spread);

				long spine;
				spread->get_spine(&spine);

				CComPtr<IObjectMap> pages;
				spread->get_pages(&pages);

				long npages;
				pages->get_length(&npages);

				MoveToEx(hDC, m_areaRect.Width()/2, y-3, NULL);
				LineTo(hDC, m_areaRect.Width()/2, y+pageSize[m_iconSize].cy+3);

				int x = m_areaRect.Width()/2 - spine*pageSize[m_iconSize].cx;

				CRect src;
				src.left = x;
				src.right = x + npages*pageSize[m_iconSize].cx;

				for (int npage = 0; npage < npages; npage++)
				{
					CComPtr<IPDPage> page;
					pages->item(npage, (IUnknown**)&page);

					if (pageCount > 1)
					{
						section.Release();
						page->get_section(&section);
					}

					BOOL selected = m_view->IsPageSelected(page);

					CRect rc(x, y, x+pageSize[m_iconSize].cx, y+pageSize[m_iconSize].cy);

					if (section)
					{
						HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));
						HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));

						POINT pts[3] =
						{
							rc.left + rc.Width()/2-2, rc.top-4,
							rc.left + rc.Width()/2+2+1, rc.top-4,
							rc.left + rc.Width()/2, rc.top+1,
						};

						Polygon(hDC, pts, 3);

						SelectObject(hDC, hOldBrush);
						SelectObject(hDC, hOldPen);
					}

					DrawPage(hDC, rc, (npage >= spine), selected? true: false);

					CComPtr<IPDSpreadMaster> masterSpread;
					page->get_baseMaster(&masterSpread);

					if (masterSpread)
					{
						BSTR bprefix;
						masterSpread->get_prefix(&bprefix);
						_bstr_t prefix = _bstr_t(bprefix, false);

						rc.InflateRect(-2, -4, -2, 2);

						SetTextColor(hDC, RGB(0, 0, 0));
						DrawText(hDC, prefix, prefix.length(), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					}

					x += pageSize[m_iconSize].cx;
				}

				y += pageSize[m_iconSize].cy;

				src.top = y+1;
				src.bottom = y+14-1;

				CUString str;
				VARIANT_BOOL keepSpreadTogether;
				spread->get_keepSpreadTogether(&keepSpreadTogether);

				if (keepSpreadTogether) str += L"[";

				if (npages > 1)
				{
					CUString str2;
					str2.Format("%d-%d", pageCount, pageCount+npages-1);
					str += str2;
				}
				else
				{
					CUString str2;
					str2.Format("%d", pageCount);
					str += str2;
				}

				if (keepSpreadTogether) str += L"]";

				BOOL bActiveSpread = IsUnknownEqualUnknown(m_view->m_activeSpread, spread);

				SetTextColor(hDC, bActiveSpread? RGB(255, 255, 255): RGB(0,0,0));
				FillSolidRect(hDC, &src, bActiveSpread? RGB(0, 0, 0): RGB(255, 255, 255));

				DrawText(hDC, str, str.GetLength(), &src, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				pageCount += npages;

				y += 14;
			}
		}

		SelectObject(hDC, hOldFont);
		DeleteObject(hFont);
	}

	EndPaint(&ps);
	return 0;
}

LRESULT CSpreadsWnd::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	if (m_view != NULL)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		point.y += scrollposY;

		long pageIndex = -1;

		CComPtr<IObjectMap> spreads;
		m_view->m_document->get_spreads(&spreads);

		long nspreads;
		spreads->get_length(&nspreads);

		int count = 0;

		int y = 4;

		for (int nspread = 0; nspread < nspreads; nspread++)
		{
			CComPtr<IPDSpread> spread;
			spreads->item(nspread, (IUnknown**)&spread);

			long spine;
			spread->get_spine(&spine);

			CComPtr<IObjectMap> pages;
			spread->get_pages(&pages);

			long npages;
			pages->get_length(&npages);

			int x = m_areaRect.Width()/2 - spine*pageSize[m_iconSize].cx;

			for (int npage = 0; npage < npages; npage++)
			{
				CComPtr<IPDPage> page;
				pages->item(npage, (IUnknown**)&page);

				BOOL selected = m_view->IsPageSelected(page);

				CRect rc(x, y, x+pageSize[m_iconSize].cx, y+pageSize[m_iconSize].cy);

				if (rc.PtInRect(point))
				{
					pageIndex = count;
					break;
				}

				count++;

				x += pageSize[m_iconSize].cx;
			}

			y += pageSize[m_iconSize].cy+14;
		}

		if (pageIndex >= 0)
		{
			CComPtr<IObjectMap> pages;
			m_view->m_document->get_pages(&pages);

			long npages;
			pages->get_length(&npages);

			CComPtr<IPDPage> page;
			pages->item(pageIndex, (IUnknown**)&page);

			BOOL bSelected = m_view->IsPageSelected(page);

			if (wParam & MK_CONTROL)	// Toggle selected
			{
				if (m_selectedPageIndex != pageIndex)	// Unless...
				{
					if (bSelected)
						m_view->DeselectPage(page);
					else
						m_view->SelectPage(page);

					m_selectedPageIndex = pageIndex;
				}
			}
			else
			{
				long startSel, endSel;

				if (!(nFlags & MK_SHIFT) || (m_selectedPageIndex == -1))
				{
					startSel = endSel = pageIndex;
				}
				else if (pageIndex > m_selectedPageIndex)
				{
					startSel = m_selectedPageIndex;
					endSel = pageIndex;
				}
				else
				{
					startSel = pageIndex;
					endSel = m_selectedPageIndex;
				}

				m_view->m_selectedPages.RemoveAll();

			// Select/Deselect all pages
				for (long i = startSel; i <= endSel; i++)
				{
					CComPtr<IPDPage> page;
					pages->item(i, (IUnknown**)&page);

					m_view->SelectPage(page);
				}

				if (m_selectedPageIndex == -1 || !(wParam & MK_SHIFT))
				{
					m_selectedPageIndex = pageIndex;
				}
			}

			InvalidateRect(&m_areaRect);

			if (m_selectedPageIndex >= 0)
			{
				CComPtr<ILDOMDocument> document;
				document.CoCreateInstance(CLSID_LDOMDocument);

				VARIANT_BOOL success;
				document->loadXML(L"<pages/>", &success);

				/*
				CComQIPtr<IDOMElement> documentElement;
				document->get_documentElement(&documentElement);

				documentElement->setAttribute(L"fromtable", m_table->Name);

				for (long i = 0; i < m_columns.GetSize(); i++)
				{
					if (m_columns[i]->m_bSelected)
					{
						CComQIPtr<IDOMElement> element;
						document->createElement(L"column", &element);
						element->setAttribute(L"name", m_table->Columns->Item[_variant_t(index)]->Name);
						documentElement->appendChild(element, NULL);
					}
				}
				*/

				BSTR text;
				document->saveXML(NULL, &text);
				int len = SysStringLen(text);

				HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, (len+1)*2);

				if (hData)
				{
					WCHAR* p = (WCHAR*)GlobalLock(hData);
					CopyMemory(p, text, (len+1)*2);
					GlobalUnlock(hData);

					CMyDropSource*  dropSource = new CMyDropSource;
					CMyDataObject* dataObject = new CMyDataObject;

					STGMEDIUM	stg = {0};
					stg.tymed = TYMED_HGLOBAL;
					stg.hGlobal = hData;
					stg.pUnkForRelease = NULL;
					
					FORMATETC	etc = {0};
					etc.cfFormat = CF_UNICODETEXT;//CF_UNICODETEXT;//49285;//RegisterClipboardFormat(CFSTR_SHELLURL);//CF_TEXT;
					etc.tymed = TYMED_HGLOBAL;
					etc.ptd = NULL;
					etc.dwAspect = DVASPECT_CONTENT;
					etc.lindex = -1;

					dataObject->SetData(&etc, &stg, TRUE);

					DWORD dropEffect = 0;
					HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

					if (hr == DRAGDROP_S_DROP)
					{
						if (dropEffect/* & DROPEFFECT_MOVE*/)
						{
						}
					}

					GlobalFree(hData);

				//	delete dataObject;
				//	delete dropSource;

		#if 0
					COleDataSource source;
					source.CacheGlobalData(CF_HDROP, hData, NULL);

					if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_COPY)
					{
					}

					source.Empty();
		#endif
				}
			}
		}
	}

	return 0;
}

LRESULT CSpreadsWnd::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_view != NULL)
	{
		if (m_selectedPageIndex >= 0)
		{
			CComPtr<IObjectMap> pages;
			m_view->m_document->get_pages(&pages);

			CComPtr<IPDPage> page;
			pages->item(m_selectedPageIndex, (IUnknown**)&page);

			CComPtr<IPDSpread> spread;
			page->get_ownerSpread(&spread);

			m_view->put_activeSpread(spread);
			// TODO remove
			{
				OnSize();
				Invalidate();
			}
		}
	}

	return 0;
}

LRESULT CSpreadsWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(&m_areaRect);

	return 0;
}

void CSpreadsWnd::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.right -= 16;

	m_axvert.MoveWindow(m_areaRect.right, 0, 16, m_areaRect.bottom);
	if (m_view)
	{
		CComPtr<IObjectMap> spreads;
		m_view->m_document->get_spreads(&spreads);

		long nspreads;
		spreads->get_length(&nspreads);

		int height = 4 + nspreads*(pageSize[m_iconSize].cy+14) + 4;

		m_vert->SetInfo(0, height, m_areaRect.Height());
	}
	else
	{
		m_vert->SetInfo(0, 0, m_areaRect.Height());
	}
}

STDMETHODIMP CSpreadsWnd::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CSpreadsWnd::DragOver(DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	POINT point;
	point.x = ptl.x;
	point.y = ptl.y;
	ScreenToClient(&point);

	long scrollposY; m_vert->get_pos(&scrollposY);

	point.y += scrollposY;

	if (m_view != NULL)
	{
		long pageIndex = -1;

		CComPtr<IObjectMap> spreads;
		m_view->m_document->get_spreads(&spreads);

		long nspreads;
		spreads->get_length(&nspreads);

		int count = 0;

		int y = 4;

		for (int nspread = 0; nspread < nspreads; nspread++)
		{
			CComPtr<IPDSpread> spread;
			spreads->item(nspread, (IUnknown**)&spread);

			long spine;
			spread->get_spine(&spine);

			CComPtr<IObjectMap> pages;
			spread->get_pages(&pages);

			long npages;
			pages->get_length(&npages);

			int x = m_areaRect.Width()/2 - spine*pageSize[m_iconSize].cx;

			for (int npage = 0; npage < npages; npage++)
			{
				CComPtr<IPDPage> page;
				pages->item(npage, (IUnknown**)&page);

				BOOL selected = m_view->IsPageSelected(page);

				CRect rc(x, y, x+pageSize[m_iconSize].cx, y+pageSize[m_iconSize].cy);

				if (rc.PtInRect(point))
				{
					pageIndex = count;
					break;
				}

				count++;

				x += pageSize[m_iconSize].cx;
			}

			y += pageSize[m_iconSize].cy+14;
		}

		if (pageIndex >= 0)
		{
			*pdwEffect = DROPEFFECT_COPY;
		}
	}

	return S_OK;
}

STDMETHODIMP CSpreadsWnd::DragLeave()
{
	return S_OK;
}

STDMETHODIMP CSpreadsWnd::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	POINT point;
	point.x = ptl.x;
	point.y = ptl.y;
	ScreenToClient(&point);

	long scrollposY; m_vert->get_pos(&scrollposY);

	point.y += scrollposY;

	if (m_view != NULL)
	{
		long pageIndex = -1;

		CComPtr<IObjectMap> spreads;
		m_view->m_document->get_spreads(&spreads);

		long nspreads;
		spreads->get_length(&nspreads);

		int count = 0;

		int y = 4;

		for (int nspread = 0; nspread < nspreads; nspread++)
		{
			CComPtr<IPDSpread> spread;
			spreads->item(nspread, (IUnknown**)&spread);

			long spine;
			spread->get_spine(&spine);

			CComPtr<IObjectMap> pages;
			spread->get_pages(&pages);

			long npages;
			pages->get_length(&npages);

			int x = m_areaRect.Width()/2 - spine*pageSize[m_iconSize].cx;

			for (int npage = 0; npage < npages; npage++)
			{
				CComPtr<IPDPage> page;
				pages->item(npage, (IUnknown**)&page);

				BOOL selected = m_view->IsPageSelected(page);

				CRect rc(x, y, x+pageSize[m_iconSize].cx, y+pageSize[m_iconSize].cy);

				if (rc.PtInRect(point))
				{
					pageIndex = count;
					break;
				}

				count++;

				x += pageSize[m_iconSize].cx;
			}

			y += pageSize[m_iconSize].cy+14;
		}

		if (pageIndex >= 0)
		{
			CComPtr<IObjectMap> pages;
			m_view->m_document->get_pages(&pages);

			CComPtr<IPDPage> page;
			pages->item(pageIndex, (IUnknown**)&page);

			COleDataObjectWrapper dataObject;
			dataObject.Attach(pDataObject);

			HGLOBAL hData;

			if (hData = dataObject.GetGlobalData(CF_UNICODETEXT))
			{
				WCHAR* p = (WCHAR*)GlobalLock(hData);

				CComPtr<ILDOMDocument> document;
				document.CoCreateInstance(CLSID_LDOMDocument);

				VARIANT_BOOL success;
				document->loadXML(p, &success);
				if (success)
				{
					CComPtr<ILDOMElement> documentElement;
					document->get_documentElement(&documentElement);
					if (documentElement)
					{
						BSTR btagName;
						documentElement->get_tagName(&btagName);
						if (!wcscmp(btagName, L"master_spread"))
						{
							BSTR bprefix;
							documentElement->getAttribute(L"prefix", &bprefix);
							_bstr_t prefix = _bstr_t(bprefix, false);

							BSTR bname;
							documentElement->getAttribute(L"name", &bname);
							_bstr_t name = _bstr_t(bname, false);

							CComPtr<IPDSpreadMaster> masterSpread;
							m_view->m_document->getMasterSpreadByName(prefix, name, &masterSpread);
							if (masterSpread)
							{
								page->put_baseMaster(masterSpread);

								*pdwEffect = DROPEFFECT_COPY;

								Invalidate();	// TODO, remove this
							}
						}
						SysFreeString(btagName);
					}
				}

				GlobalUnlock(hData);
			}
		}
	}

	return S_OK;
}

HRESULT __stdcall CSpreadsWnd::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);

	return S_OK;
}

void __stdcall CSpreadsWnd::OnPageSelectedChanged(IPDPage* page, VARIANT_BOOL selected)
{
	Invalidate();
}

/////////////////////////////
// CMastersWnd

LRESULT CMastersWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CMastersWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	return 0;
}

LRESULT CMastersWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CMastersWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	return 0;
}

LRESULT CMastersWnd::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

//	CRect client;
//	GetClientRect(&client);

	if (m_view != NULL)
	{
		HFONT hFont = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

		long scrollposY; m_vert->get_pos(&scrollposY);
	
		if (IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
		{
			SetViewportOrgEx(hDC, m_areaRect.left, m_areaRect.top - scrollposY, NULL);

			CComPtr<IObjectMap> spreads;
			m_view->m_document->get_masterSpreads(&spreads);

			long nspreads;
			spreads->get_length(&nspreads);

			int y = 2;

			for (int nspread = 0; nspread < nspreads; nspread++)
			{
				CComPtr<IPDSpreadMaster> spread;
				spreads->item(nspread, (IUnknown**)&spread);

				BSTR bprefix;
				spread->get_prefix(&bprefix);
				_bstr_t prefix = _bstr_t(bprefix, false);

				BSTR bname;
				spread->get_name(&bname);
				_bstr_t name = _bstr_t(bname, false);

				CUString str;
				str.Format("%S-%S", (BSTR)prefix, (BSTR)name);
				TextOut(hDC, 0, y, str, str.GetLength());

				CComPtr<IObjectMap> pages;
				spread->get_pages(&pages);

				long npages;
				pages->get_length(&npages);

				int x = m_areaRect.Width() - 4 - npages*pageSize[m_iconSize].cx;

				for (int npage = 0; npage < npages; npage++)
				{
					CComPtr<IPDPage> page;
					pages->item(npage, (IUnknown**)&page);

					BOOL selected = m_view->IsPageSelected(page);

					DrawPage(hDC, CRect(x, y, x+pageSize[m_iconSize].cx, y+pageSize[m_iconSize].cy), (npage%2), selected? true: false);

					x += pageSize[m_iconSize].cx;
				}

				y += pageSize[m_iconSize].cy+2;
			}
		}

		SelectObject(hDC, hOldFont);
		DeleteObject(hFont);
	}

	EndPaint(&ps);
	return 0;
}

LRESULT CMastersWnd::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	if (m_view != NULL)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		point.y += scrollposY;

		long pageIndex = -1;

		CComPtr<IObjectMap> spreads;
		m_view->m_document->get_masterSpreads(&spreads);

		long nspreads;
		spreads->get_length(&nspreads);

		int count = 0;

		int y = 2;

		for (int nspread = 0; nspread < nspreads; nspread++)
		{
			CComPtr<IPDSpread> spread;
			spreads->item(nspread, (IUnknown**)&spread);

			CComPtr<IObjectMap> pages;
			spread->get_pages(&pages);

			long npages;
			pages->get_length(&npages);

			int x = m_areaRect.Width() - 4 - npages*pageSize[m_iconSize].cx;

			for (int npage = 0; npage < npages; npage++)
			{
				CComPtr<IPDPage> page;
				pages->item(npage, (IUnknown**)&page);

				BOOL selected = m_view->IsPageSelected(page);

				CRect rc(x, y, x+pageSize[m_iconSize].cx, y+pageSize[m_iconSize].cy);

				if (rc.PtInRect(point))
				{
					pageIndex = count;
					break;
				}

				count++;

				x += pageSize[m_iconSize].cx;
			}

			y += pageSize[m_iconSize].cy+2;
		}

		if (pageIndex >= 0)
		{
			CComPtr<IObjectMap> pages;
			m_view->m_document->get_masterPages(&pages);

			long npages;
			pages->get_length(&npages);

			CComPtr<IPDPage> page;
			pages->item(pageIndex, (IUnknown**)&page);

			CComPtr<IPDSpreadMaster> spread;
			page->get_ownerSpread((IPDSpread**)&spread);

			BOOL bSelected = m_view->IsPageSelected(page);

			if (wParam & MK_CONTROL)	// Toggle selected
			{
				if (m_selectedPageIndex != pageIndex)	// Unless...
				{
					if (bSelected)
						m_view->DeselectPage(page);
					else
						m_view->SelectPage(page);

					m_selectedPageIndex = pageIndex;
				}
			}
			else
			{
				long startSel, endSel;

				if (!(nFlags & MK_SHIFT) || (m_selectedPageIndex == -1))
				{
					startSel = endSel = pageIndex;
				}
				else if (pageIndex > m_selectedPageIndex)
				{
					startSel = m_selectedPageIndex;
					endSel = pageIndex;
				}
				else
				{
					startSel = pageIndex;
					endSel = m_selectedPageIndex;
				}

				m_view->m_selectedPages.RemoveAll();

			// Select/Deselect all pages
				for (long i = startSel; i <= endSel; i++)
				{
					CComPtr<IPDPage> page;
					pages->item(i, (IUnknown**)&page);

					m_view->SelectPage(page);
				}

				if (m_selectedPageIndex == -1 || !(wParam & MK_SHIFT))
				{
					m_selectedPageIndex = pageIndex;
				}

				InvalidateRect(&m_areaRect);

				CComPtr<ILDOMDocument> document;
				document.CoCreateInstance(CLSID_LDOMDocument);

				VARIANT_BOOL success;
				document->loadXML(L"<master_spread/>", &success);

				CComPtr<ILDOMElement> documentElement;
				document->get_documentElement(&documentElement);

				BSTR bprefix;
				spread->get_prefix(&bprefix);
				_bstr_t prefix = _bstr_t(bprefix, false);

				BSTR bname;
				spread->get_name(&bname);
				_bstr_t name = _bstr_t(bname, false);

				documentElement->setAttribute(L"prefix", prefix);
				documentElement->setAttribute(L"name", name);

				BSTR text;
				document->saveXML(NULL, &text);
				int len = SysStringLen(text);

				HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, (len+1)*2);

				if (hData)
				{
					WCHAR* p = (WCHAR*)GlobalLock(hData);
					CopyMemory(p, text, (len+1)*2);
					GlobalUnlock(hData);

					CMyDropSource*  dropSource = new CMyDropSource;
					CMyDataObject* dataObject = new CMyDataObject;

					STGMEDIUM	stg = {0};
					stg.tymed = TYMED_HGLOBAL;
					stg.hGlobal = hData;
					stg.pUnkForRelease = NULL;
					
					FORMATETC	etc = {0};
					etc.cfFormat = CF_UNICODETEXT;//CF_UNICODETEXT;//49285;//RegisterClipboardFormat(CFSTR_SHELLURL);//CF_TEXT;
					etc.tymed = TYMED_HGLOBAL;
					etc.ptd = NULL;
					etc.dwAspect = DVASPECT_CONTENT;
					etc.lindex = -1;

					dataObject->SetData(&etc, &stg, TRUE);

					DWORD dropEffect = 0;
					HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

					if (hr == DRAGDROP_S_DROP)
					{
						if (dropEffect/* & DROPEFFECT_MOVE*/)
						{
						}
					}

					GlobalFree(hData);

				//	delete dataObject;
				//	delete dropSource;

		#if 0
					COleDataSource source;
					source.CacheGlobalData(CF_HDROP, hData, NULL);

					if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_COPY)
					{
					}

					source.Empty();
		#endif
				}
			}
		}
	}

	return 0;
}

LRESULT CMastersWnd::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_view != NULL)
	{
		if (m_selectedPageIndex >= 0)
		{
			CComPtr<IObjectMap> pages;
			m_view->m_document->get_masterPages(&pages);

			CComPtr<IPDPage> page;
			pages->item(m_selectedPageIndex, (IUnknown**)&page);

			CComPtr<IPDSpread> spread;
			page->get_ownerSpread(&spread);

			m_view->put_activeSpread(spread);
		}
	}

	return 0;
}

LRESULT CMastersWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(&m_areaRect);

	return 0;
}

void CMastersWnd::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.right -= 16;

	m_axvert.MoveWindow(m_areaRect.right, 0, 16, m_areaRect.bottom);

	if (m_view)
	{
		CComPtr<IObjectMap> spreads;
		m_view->m_document->get_masterSpreads(&spreads);

		long nspreads;
		spreads->get_length(&nspreads);

		int height = 4 + nspreads*(pageSize[m_iconSize].cy+2) + 4;

		m_vert->SetInfo(0, height, m_areaRect.Height());
	}
	else
	{
		m_vert->SetInfo(0, 0, m_areaRect.Height());
	}
}

HRESULT __stdcall CMastersWnd::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);

	return S_OK;
}

void __stdcall CMastersWnd::OnPageSelectedChanged(IPDPage* page, VARIANT_BOOL selected)
{
	Invalidate();
}

/////////////////////////////
// CPagesDlg

int CPagesDlg::FinalConstruct()
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_PAGES, &m_menu);

	return S_OK;
}

LRESULT CPagesDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);
	
	CRect client;
	GetClientRect(&client);

	FillSolidRect(hDC, 0, m_splity-3, client.right, 6, GetSysColor(COLOR_BTNFACE));
	Draw3DRect(hDC, 0, m_splity-3, client.right, 6, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

	EndPaint(&ps);
	return 0;
}

LRESULT CPagesDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);

	CComObject<CSpreadsWnd>::CreateInstance(&m_spreadsWnd);
	m_spreadsWnd->AddRef();
	m_spreadsWnd->Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN);

	CComObject<CMastersWnd>::CreateInstance(&m_mastersWnd);
	m_mastersWnd->AddRef();
	m_mastersWnd->Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CPagesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	if (m_mastersWnd)
	{
		m_mastersWnd->DestroyWindow();
		m_mastersWnd->Release();
		m_mastersWnd = NULL;
	}

	if (m_spreadsWnd)
	{
		m_spreadsWnd->DestroyWindow();
		m_spreadsWnd->Release();
		m_spreadsWnd = NULL;
	}

	return 0;
}

LRESULT CPagesDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (!m_dragging)
	{
		if (abs(point.y-m_splity) < 6)
		{
			m_dragging = 1;
			SetCapture();
		}
	}

	return 0;
}

LRESULT CPagesDlg::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}
	return 0;
}

LRESULT CPagesDlg::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		CRect client;
		GetClientRect(&client);

		int splity = point.y;
		if (splity < 3) splity = 3;
		else if (splity > client.bottom-3) splity = client.bottom-3;

		if (m_splity != splity)
		{
			m_splity = splity;
			OnSize();
			Invalidate();
		}
	}

	return 0;
}

LRESULT CPagesDlg::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	UINT nHittest = LOWORD(lParam);  // hit-test code 
	UINT wMouseMsg = HIWORD(lParam); // mouse-message identifier 

	if (nHittest == HTCLIENT)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (abs(point.y-m_splity) < 6)
		{
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
			return TRUE;
		}
	}

	return 0;
}

LRESULT CPagesDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	Invalidate();
	OnSize();

	CRect client;
	GetClientRect(&client);

	if (client.right > 0) m_oldClientRect = client;

	return 0;
}

void CPagesDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	if (m_resize == 0)	// Proportional resizeing
	{
		m_splity = client.Height()/2;
	}
	else if (m_resize == 1)	// Pages Fixed
	{
		if (m_windowOnTop == 1)	// Masters on Top
		{
			m_splity = client.Height() - (m_oldClientRect.Height()-m_splity);
		}
	}
	else	// Masters Fixed
	{
		if (m_windowOnTop == 0)	// Pages on Top
		{
			m_splity = client.Height() - (m_oldClientRect.Height()-m_splity);
		}
	}

	if (client.right > 0 && m_splity > client.bottom-3) m_splity = client.bottom-3;
	if (m_splity < 3) m_splity = 3;

	if (m_windowOnTop == 0)	// Pages on Top
	{
		m_spreadsWnd->MoveWindow(0, 0, client.right, m_splity-3);
		m_mastersWnd->MoveWindow(0, m_splity+3, client.right, client.bottom-m_splity-3);
	}
	else
	{
		m_mastersWnd->MoveWindow(0, 0, client.right, m_splity-3);
		m_spreadsWnd->MoveWindow(0, m_splity+3, client.right, client.bottom-m_splity-3);
	}
}

STDMETHODIMP CPagesDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocumentView> view = object;
	if (view)
	{
		ATLASSERT(m_view == NULL);

		m_view = static_cast<CComObject<CPDDocumentView>*>(view.p);
		m_view->AddRef();

		m_spreadsWnd->m_view = m_view;
		m_mastersWnd->m_view = m_view;

		m_spreadsWnd->IDispEventImpl<3, CSpreadsWnd, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_view->m_document);
		m_mastersWnd->IDispEventImpl<3, CMastersWnd, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_view->m_document);

		m_spreadsWnd->OnSize();
		m_spreadsWnd->Invalidate();

		m_mastersWnd->OnSize();
		m_mastersWnd->Invalidate();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CPagesDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(cookie == 1);

	m_spreadsWnd->m_view = NULL;
	m_mastersWnd->m_view = NULL;

	m_spreadsWnd->IDispEventImpl<3, CSpreadsWnd, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_view->m_document);
	m_mastersWnd->IDispEventImpl<3, CMastersWnd, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_view->m_document);

	m_spreadsWnd->OnSize();
	m_spreadsWnd->Invalidate();

	m_mastersWnd->OnSize();
	m_mastersWnd->Invalidate();

	m_view->Release();
	m_view = NULL;

	return S_OK;
}

// ICommandTarget
STDMETHODIMP CPagesDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try view
	CComQIPtr<ICommandTarget> view = m_view;
	if (view) view->OnCmdMsg(nID, nCode, pCmdUI, bHandled);

	return S_OK;
}

BEGIN_CMD_MAP(CPagesDlg)
	CMD_HANDLER(ID_PAGES_INSERTPAGES, OnInsertPages)
	CMD_UPDATE(ID_PAGES_INSERTPAGES, OnInsertPagesUpdate)

	CMD_HANDLER(ID_PAGES_SECTIONOPTIONS, OnSectionOptions)
	CMD_UPDATE(ID_PAGES_SECTIONOPTIONS, OnSectionOptionsUpdate)

	CMD_HANDLER(ID_PAGES_KEEPSPREADTOGETHER, OnKeepSpreadTogether)
	CMD_UPDATE(ID_PAGES_KEEPSPREADTOGETHER, OnKeepSpreadTogetherUpdate)

	CMD_HANDLER(ID_PAGES_PALETTEOPTIONS, OnPaletteOptions)
END_CMD_MAP()

#include "SectionOptionsDlg.h"

LRESULT CPagesDlg::OnSectionOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_view)
	{
		if (m_spreadsWnd->m_view->m_selectedPages.GetSize() == 1)
		{
			CComPtr<IPDPage> page = m_spreadsWnd->m_view->m_selectedPages[0];

			CComPtr<IPDSection> section;
			page->get_section(&section);

			CSectionOptionsDlg dlg;

			dlg.m_bSection = TRUE;
			if (section)
			{
				section->get_pageNumbering(&dlg.m_pageNumbering);
				section->get_pageNumberingStartAt(&dlg.m_pageNumberingStartAt);
			}

			if (dlg.DoModal(GetMainHwnd()) == IDOK)
			{
				if (dlg.m_bSection)
				{
					if (section == NULL)
					{
						m_view->m_document->createSection(&section);
						page->put_section(section);
					}

					section->put_pageNumbering(dlg.m_pageNumbering);
					section->put_pageNumberingStartAt(dlg.m_pageNumberingStartAt);
				}
				else
				{
					if (section)
					{
						page->put_section(NULL);
					}
				}

				m_spreadsWnd->OnSize();
				m_spreadsWnd->Invalidate();
			}
		}
	}

	return 0;
}

void CPagesDlg::OnSectionOptionsUpdate(long iid, IUICmdUpdate * pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_view)
	{
		if (m_spreadsWnd->m_view->m_selectedPages.GetSize() == 1)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

#include "PagesOptionsDlg.h"

LRESULT CPagesDlg::OnPaletteOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CPagesOptionsDlg dlg;

	dlg.m_pagesIconSize = m_spreadsWnd->m_iconSize;
	dlg.m_mastersIconSize = m_mastersWnd->m_iconSize;
	dlg.m_resize = m_resize;
	dlg.m_windowOnTop = m_windowOnTop;

	if (dlg.DoModal(GetMainHwnd()) == IDOK)
	{
		m_spreadsWnd->m_iconSize = dlg.m_pagesIconSize;
		m_mastersWnd->m_iconSize = dlg.m_mastersIconSize;
		m_resize = dlg.m_resize;
		m_windowOnTop = dlg.m_windowOnTop;

		OnSize();

		m_spreadsWnd->OnSize();
		m_spreadsWnd->Invalidate();

		m_mastersWnd->OnSize();
		m_mastersWnd->Invalidate();
	}

	return 0;
}

LRESULT CPagesDlg::OnKeepSpreadTogether(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_view)
	{
		if (m_view->m_activeSpread)
		{
			CComQIPtr<IPDSpreadDocument> spread = m_view->m_activeSpread;
			if (spread)
			{
				VARIANT_BOOL keepSpreadTogether;
				spread->get_keepSpreadTogether(&keepSpreadTogether);

				spread->put_keepSpreadTogether(keepSpreadTogether? VARIANT_FALSE: VARIANT_TRUE);

				// TODO remove
				{
					m_spreadsWnd->OnSize();
					m_spreadsWnd->Invalidate();

					m_mastersWnd->OnSize();
					m_mastersWnd->Invalidate();
				}
			}
		}
	}

	return 0;
}

void CPagesDlg::OnKeepSpreadTogetherUpdate(long iid, IUICmdUpdate * pCmdUI)
{
	BOOL bEnable = FALSE;

	if (m_view)
	{
		if (m_view->m_activeSpread)
		{
			CComQIPtr<IPDSpreadDocument> spread = m_view->m_activeSpread;
			if (spread)
			{
				VARIANT_BOOL keepSpreadTogether;
				spread->get_keepSpreadTogether(&keepSpreadTogether);

				pCmdUI->SetCheck(keepSpreadTogether);

				bEnable = TRUE;
			}
		}
	}

	pCmdUI->Enable(bEnable);
}

#include "InsertPagesDlg.h"

LRESULT CPagesDlg::OnInsertPages(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_view && m_spreadsWnd->m_selectedPageIndex >= 0)
	{
		CInsertPagesDlg dlg;

		dlg.m_document = m_view->m_document;

		dlg.m_numPages = 1;
		dlg.m_insert = 0;	// After page
		dlg.m_insertAt = m_spreadsWnd->m_selectedPageIndex;

		if (dlg.DoModal(GetMainHwnd(), NULL) == IDOK)
		{
			CComPtr<IPDDocument> document = m_view->m_document;

			if (dlg.m_insert == 0)
			{
				document->insertPagesAfter(dlg.m_numPages, dlg.m_insertAt);
			}
			else if (dlg.m_insert == 1)
			{
				document->insertPagesBefore(dlg.m_numPages, dlg.m_insertAt);
			}

			// TODO remove
			{
				m_spreadsWnd->OnSize();
				m_spreadsWnd->Invalidate();

				m_mastersWnd->OnSize();
				m_mastersWnd->Invalidate();
			}
		}
	}

	return 0;
}

void CPagesDlg::OnInsertPagesUpdate(long iid, IUICmdUpdate * pCmdUI)
{
	pCmdUI->Enable(m_view != NULL);
}
