// HelpView.h : Declaration of the CHelpView

#ifndef __HELPVIEW_H_
#define __HELPVIEW_H_

#include "resource.h"       // main symbols
//#import "D:\MMStudio\Extras\UI\UI.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

class CHelpContentsWnd;

/////////////////////////////////////////////////////////////////////////////
// CHelpView
class CHelpView : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public CWindowImpl<CHelpView>
//	public CComCoClass<CHelpView, &CLSID_HelpView>,
//	public IConnectionPointContainerImpl<CHelpView>,
//	public IDispatchImpl<IHelpView, &IID_IHelpView, &LIBID_HELPLib>,
//	public IDispatchImpl<IUIView, &IID_IUIView, &LIBID_UILib>,
//	public IDispatchImpl<IUIWnd, &IID_IUIWnd, &LIBID_UILib>
{
public:
	CHelpView()
	{
		m_splitx = 180;
		m_dragging = 0;

		m_contents = NULL;
	}

	int m_dragging;
	int m_splitx;
	CHelpContentsWnd* m_contents;
	CAxWindow m_axhtml;
	CComPtr<ILHTMLControl> m_html;

	void OnSize();

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_HELPVIEW)
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHelpView)
	COM_INTERFACE_ENTRY(IHelpView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, IHelpView)
	COM_INTERFACE_ENTRY2(IUIView, IHelpView)
	COM_INTERFACE_ENTRY2(IUIWnd, IHelpView)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CHelpView)
END_CONNECTION_POINT_MAP()
*/

BEGIN_MSG_MAP(CHelpView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
END_MSG_MAP()

	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IHelpView
public:
//	STDMETHOD(get_html)(/*[out, retval]*/ IHTMLControl* *pVal);
//	STDMETHOD(put_html)(/*[in]*/ IHTMLControl* newVal);
//	STDMETHOD(get_contents)(/*[out, retval]*/ IHelpContentsWnd* *pVal);
//	STDMETHOD(put_contents)(/*[in]*/ IHelpContentsWnd* newVal);
};

#endif //__HELPVIEW_H_
