#include "stdafx.h"
#include "SQLQueryBuilderMod.h"

#include "SQLTableWnd.h"

///////////////////////////////
// CSQLTableWnd

LRESULT CSQLTableWnd::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	CRect client;
	GetClientRect(&client);

	HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

	int y = 0;
	int x = 0;

	for (long i = 0; i < m_columns.GetSize(); i++)
	{
		CTableColumn* column = m_columns[i];

		_bstr_t name = column->m_name;
		if (column->m_bSelected)
		{
			SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
			SetBkColor(hDC, GetSysColor(COLOR_HIGHLIGHT));
		}
		else
		{
			SetTextColor(hDC, RGB(0,0,0));
			SetBkColor(hDC, RGB(255, 255, 255));
		}

		CRect rc(0, y, client.right, y+16);
		DrawText(hDC, name, name.length(), &rc, DT_SINGLELINE | DT_END_ELLIPSIS | DT_VCENTER);

		y += 16;
	}

	SelectObject(hDC, hOldFont);

	EndPaint(&ps);
	return 0;
}

LRESULT CSQLTableWnd::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (!(wParam & MK_SHIFT))
	{
		for (int i = 0; i < m_columns.GetSize(); i++)
		{
			m_columns[i]->m_bSelected = false;
		}
	}

	long index = point.y/16;

	if (index >= 0 && index < m_table->Columns->Count)
	{
		m_columns[index]->m_bSelected = true;

		Invalidate();
		UpdateWindow();

		CComQIPtr<ILDOMDocument> document;
		document.CoCreateInstance(CLSID_LDOMDocument);

		VARIANT_BOOL success;
		document->loadXML(L"<columns/>", &success);

		CComQIPtr<ILDOMElement> documentElement;
		document->get_documentElement(&documentElement);

		documentElement->setAttribute(L"fromtable", m_table->Name);

		for (long i = 0; i < m_columns.GetSize(); i++)
		{
			if (m_columns[i]->m_bSelected)
			{
				CComQIPtr<ILDOMElement> element;
				document->createElement(L"column", &element);
				element->setAttribute(L"name", m_table->Columns->Item[_variant_t(index)]->Name);
				documentElement->appendChild(element, NULL);
			}
		}

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

		SysFreeString(text);
	}
	else
	{
		Invalidate();
	}

	return 0;
}

LRESULT CSQLTableWnd::OnMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::InvalidateRect(GetParent(), NULL, TRUE);

	::SendMessage(::GetParent(GetParent()), WM_SIZE, 0, 0);

	return 0;
}

LRESULT CSQLTableWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::InvalidateRect(GetParent(), NULL, TRUE);

	::SendMessage(::GetParent(GetParent()), WM_SIZE, 0, 0);

	return 0;
}
