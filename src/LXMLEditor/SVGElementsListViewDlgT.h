#pragma once

namespace System
{

class CSVGElementsListViewDlgTBase
{
public:
	CSVGElementsListViewDlgTBase()
	{
		m_multiSelect = true;
		m_view = 0;

//		m_hFont = NULL;
	}

	int m_view;

	CRect m_areaRect;

	CComPtr<ILDOMDocument> m_xmlDocument;
	CArray<ILSVGElement*,ILSVGElement*> m_items;

	int m_selectedItemIndex;
	CArray<ILSVGElement*,ILSVGElement*> m_selectedItems;

//	HFONT m_hFont;

	bool m_multiSelect;

	bool IsItemSelected(ILSVGElement* item)
	{
		for (int i = 0; i < m_selectedItems.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(item, m_selectedItems[i]))
			{
				return true;
			}
		}

		return false;
	}

	void DeselectItem(ILSVGElement* swatch)
	{
		for (int i = 0; i < m_selectedItems.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(swatch, m_selectedItems[i]))
			{
				m_selectedItems[i]->Release();
				m_selectedItems.RemoveAt(i);
			}
		}
	}

	void DeselectAll()
	{
		for (int i = m_selectedItems.GetSize()-1; i >= 0; i--)
		{
			m_selectedItems[i]->Release();
			m_selectedItems.RemoveAt(i);
		}
	}

	void SelectItem(ILSVGElement* item)
	{
		ATLASSERT(!IsItemSelected(item));

		item->AddRef();
		m_selectedItems.Add(item);
	}

	void ButtonDown(UINT nFlags, CPoint point)
	{
		int itemHeight = (m_view == 0 || m_view == 2)? 31: 62;

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
			CComPtr<ILSVGElement> item = m_items[itemIndex];

			BOOL bSelected = IsItemSelected(item);

			if (!m_multiSelect)
			{
				if (!bSelected)
				{
					DeselectAll();

					SelectItem(item);
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
						DeselectItem(item);
					}
					else
					{
						SelectItem(item);
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
						CComPtr<ILSVGElement> item = m_items[i];

						SelectItem(item);
					}

					if (!(nFlags & MK_SHIFT) || (m_selectedItemIndex == -1))
						m_selectedItemIndex = itemIndex;

					//Fire_ClickSwatch(swatch);
				}
			}
		}
	}
};

template <class T> class ATL_NO_VTABLE CSVGElementsListViewDlgT :
	public CUIDialogImpl<T, CWindowImpl<T> >,
	public CSVGElementsListViewDlgTBase,
	public ILDOMEventListener
{
public:
	CSVGElementsListViewDlgT()
	{
	}

	virtual void BuildItems() = 0;

	void SetView(int view)
	{
		m_view = view;
		InvalidateRect(&m_areaRect);
	// TODO, reset scrollbar
	}

	void RemoveItems()
	{
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = m_items[i];
			eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);
		}
		m_items.RemoveAll();
	}

// ILDOMEventListener
	STDMETHOD(handleEvent)(ILDOMEvent* evt)
	{
		BSTR btype;
		evt->get_type(&btype);
		_bstr_t type = _bstr_t(btype, false);

		BOOL bUpdate = FALSE;

		if (!wcscmp(type, L"DOMNodeInserted"))
		{
			BuildItems();
			bUpdate = TRUE;
		}
		else if (!wcscmp(type, L"DOMNodeRemovedFromDocument"))
		{
			CComQIPtr<ILDOMMutationEvent> mut = evt;

			CComPtr<ILDOMEventTarget> target;
			mut->get_target(&target);
			CComQIPtr<ILDOMNode> node = target;

			for (int i = 0; i < m_items.GetSize(); i++)
			{
				if (m_items[i] == node)
				{
					CComQIPtr<ILDOMEventTarget> eventTarget = m_items[i];
					eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);

					m_items.RemoveAt(i);
					break;
				}
			}

			bUpdate = TRUE;
		}

		if (bUpdate)
		{
			if (m_hWnd)
			{
				Invalidate();
			}
		}

		return S_OK;
	}

// Message handlers

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect client;
		GetClientRect(&client);

		m_areaRect = client;

		return 0;
	}
};

}
