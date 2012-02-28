#pragma once

#include "resource.h"

class CMemberItem
{
public:
	_bstr_t m_name;
	int m_dispid;
	int m_type;
	_bstr_t m_helpString;
};

class CAutoListMembersWindow :
	public CComObjectRootEx<CComSingleThreadModel>,

	public IDispatchImpl<IUIAutoListWindow, &IID_IUIAutoListWindow, &LIBID_UILib>,
	public CWindowImpl<CAutoListMembersWindow>,

	public IDispEventImpl<1, CAutoListMembersWindow, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	DECLARE_WND_CLASS_EX(NULL, CS_SAVEBITS, COLOR_WINDOW)

	CAutoListMembersWindow()
	{
		m_memberImageList = NULL;

		m_selectedIndex = -1;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
		if (FAILED(hr)) return hr;
		m_vert->put_direction(1);

		return S_OK;
	}

	void FinalRelease()
	{
	}

protected:
	int m_selectedIndex;
	
	CAxWindow	m_axvert;
	CComPtr<IUIScrollBar> m_vert;

	CArray<CMemberItem*,CMemberItem*> m_members;
	CRect m_areaRect;

public:

	HIMAGELIST m_memberImageList;

	_bstr_t GetStringAt(long index)
	{
		return m_members[index]->m_name;
	}

	void SetCurSel(long index);
	long GetCurSel()
	{
		return m_selectedIndex;
	}

	int GetVisibleLines()
	{
		return m_areaRect.Height()/16;
	}

	void SetDispatch(IDispatch* pDisp);
	void ClearMemberItems();
	void OnSize();

	_bstr_t m_str;

	int FindMatch(BSTR str, int len);

//	_bstr_t GetString();

	HWND Create(HWND hParent, CPoint pt)
	{
		CDC dc;
		dc.CreateCompatibleDC(NULL);
		HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

		int width = 0;

		for (int i = 0; i < m_members.GetSize(); i++)
		{
			CSize size;
			dc.GetTextExtent(m_members[i]->m_name, m_members[i]->m_name.length(), &size);

			width = max(width, size.cx);
		}

		int height = min(m_members.GetSize(), 16)*16;

		width += 20;	// icon
		width += 2;		// some padding
		width += 16;	// scrollbar

		dc.SelectFont(hOldFont);
		dc.DeleteDC();

		CRect rc(0, 0, width, height);
		rc.OffsetRect(pt);

		CRect border(0,0,0,0);
		AdjustWindowRect(&border, WS_DLGFRAME, FALSE);

		rc.left += border.left;
		rc.right += border.right;

		rc.bottom -= border.top;	// Yes, it's correct
		rc.bottom += border.bottom;

		HWND hWnd = CWindowImpl<CAutoListMembersWindow>::Create(hParent, rc,  NULL, WS_DLGFRAME | WS_POPUP, 0, 0);
		ATLASSERT(hWnd == m_hWnd);

		return hWnd;
	}

BEGIN_COM_MAP(CAutoListMembersWindow)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIAutoListWindow)
END_COM_MAP()

BEGIN_SINK_MAP(CAutoListMembersWindow)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	void __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CAutoListMembersWindow)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
/*
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	*/
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	STDMETHOD(AddString)(/*[in]*/ long iImage, /*[in]*/ BSTR string, /*[out,retval]*/ long* pVal);

	//long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
