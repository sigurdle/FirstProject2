#pragma once

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CSVGListViewItem
{
public:
	CSVGListViewItem()
	{
		m_thumbnailBitmap = NULL;
		m_thumbnailBits = NULL;
		m_element = NULL;
	}

	System::StringW* m_name;
	LDraw::Bitmap* m_thumbnailBitmap;
	uint8 * m_thumbnailBits;
	//ILDOMElement* m_element;
	uint m_element;
};

class CSVGElementListView :
public UI::Control//CWindowImpl<CSVGElementListView>

//	public IDispEventImpl<1, CSVGElementListView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGElementListView()
	{
		m_multiSelect = true;
		m_view = 0;
	}

	long m_view;
	bool m_multiSelect;

	LDraw::BBoxi m_areaRect;

	Web::Document* m_xmlDocument;
//	CArray<ILSVGElement*,ILSVGElement*> m_items;
	Array<CSVGListViewItem*> m_items;

	int m_selectedItemIndex;
	Array<CSVGListViewItem*> m_selectedItems;

//	CAxWindow m_axvert;
//	CComPtr<IUIScrollBar>	m_vert;

//	HFONT m_hFont;

	void RemoveItems();

	ErrorCode AddItem(uint element, WCHAR * name = NULL);
//	ErrorCode AddItem(ILDOMElement* element, BSTR name = NULL);
	ErrorCode DeleteItem(long index);
	bool IsItemSelected(CSVGListViewItem* item);
	void DeselectItem(CSVGListViewItem* item);
	void DeselectAll();
	void SelectItem(int index/*ILSVGElement* item*/);

	ErrorCode SetView(long view);
	ErrorCode GetView(long* pVal);

#if 0
	void ButtonDown(UINT nFlags, CPoint point);
#endif
	void ResetVScrollBar();

#if 0
BEGIN_SINK_MAP(CSVGElementListView)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()
#endif
	void __stdcall OnVertScroll(long code, long pos);

/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/
};

}
}
