// HelpContentsWnd.h : Declaration of the CHelpContentsWnd

#ifndef __HELPCONTENTSWND_H_
#define __HELPCONTENTSWND_H_

#include "resource.h"       // main symbols
//#import "D:\MMStudio\Extras\UI\UI.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

#include "..\WebEditor\item.h"

class CTocEntry : public C2Obj
{
public:
	CUString m_url;

	void BuildNode(ILDOMElement* xmlnode);
};

class CHelpView;

/////////////////////////////////////////////////////////////////////////////
// CHelpContentsWnd
class /*ATL_NO_VTABLE*/ CHelpContentsWnd : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CHelpContentsWnd, &CLSID_HelpContentsWnd>,
//	public IConnectionPointContainerImpl<CHelpContentsWnd>,
//	public IDispatchImpl<IHelpContentsWnd, &IID_IHelpContentsWnd, &LIBID_HELPLib>,
//	public IDispatchImpl<IUIControl, &IID_IUIControl, &LIBID_UILib>,
//	public IDispatchImpl<IUIWnd, &IID_IUIWnd, &LIBID_UILib>,
	public CWindowImpl<CHelpContentsWnd>,
	public IDispEventImpl<1, CHelpContentsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CHelpContentsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CHelpContentsWnd()
	{
		m_pTreeItem = NULL;
		m_hIconsBitmap = NULL;

		m_view = NULL;
	}

	/*
	int FinalConstruct()
	{
		m_horz.CoCreateInstance(CLSID_UIScrollBar);
		m_vert.CoCreateInstance(CLSID_UIScrollBar);

		IDispEventImpl<1, CHelpContentsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
		IDispEventImpl<2, CHelpContentsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

		return S_OK;
	}

	void FinalRelease()
	{
		IDispEventImpl<1, CHelpContentsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
		IDispEventImpl<2, CHelpContentsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	}
	*/

	CHelpView* m_view;

	CComPtr<IUIScrollBar> m_vert;
	CComPtr<IUIScrollBar> m_horz;

	CTocEntry* m_pTreeItem;

	CUString	m_tocFilePathName;
	CUString	m_tocPathName;

	HBITMAP	m_hIconsBitmap;

	void OnSize();


	/*
BEGIN_COM_MAP(CHelpContentsWnd)
	COM_INTERFACE_ENTRY(IHelpContentsWnd)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, IHelpContentsWnd)
	COM_INTERFACE_ENTRY2(IUIControl, IHelpContentsWnd)
	COM_INTERFACE_ENTRY2(IUIWnd, IHelpContentsWnd)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CHelpContentsWnd)
END_CONNECTION_POINT_MAP()
*/

BEGIN_SINK_MAP(CHelpContentsWnd)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	HRESULT __stdcall OnHorzScroll(long code, long pos);
	HRESULT __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CHelpContentsWnd)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()

	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
/*
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/
// IHelpContentsWnd
public:
	STDMETHOD(LoadTOC)(/*[in]*/ BSTR pathName, /*[out,retval]*/ BOOL* success);
};

#endif //__HELPCONTENTSWND_H_
