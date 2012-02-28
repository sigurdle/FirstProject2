#pragma once

class CDOMTreeView :
	public CWindowImpl<CDOMTreeView>,

	public IDispEventImpl<1, CDOMTreeView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CDOMTreeView()
	{
		m_multiSelect = true;
		m_view = 0;
	}

	long m_view;
	bool m_multiSelect;

	CRect m_areaRect;

	CComPtr<ILDOMDocument> m_xmlDocument;
//	CArray<ILSVGElement*,ILSVGElement*> m_items;
	CArray<CSVGListViewItem*,CSVGListViewItem*> m_items;

	int m_selectedItemIndex;
	CArray<CSVGListViewItem*,CSVGListViewItem*> m_selectedItems;

	CAxWindow m_axvert;
	CComPtr<IUIScrollBar>	m_vert;

//	HFONT m_hFont;

	void RemoveItems();

	HRESULT AddItem(ILDOMElement* element, BSTR name = NULL);
	HRESULT DeleteItem(long index);
	bool IsItemSelected(CSVGListViewItem* item);
	void DeselectItem(CSVGListViewItem* item);
	void DeselectAll();
	void SelectItem(int index/*ILSVGElement* item*/);

	HRESULT SetView(long view);
	HRESULT GetView(long* pVal);

	void ButtonDown(UINT nFlags, CPoint point);

	void ResetVScrollBar();

BEGIN_SINK_MAP(CDOMTreeView)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	void __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CDOMTreeView)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
