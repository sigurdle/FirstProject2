// UIScrollBar.h : Declaration of the CUIScrollBar

#ifndef __UISCROLLBAR_H_
#define __UISCROLLBAR_H_

#include "resource.h"       // main symbols
#include "UICP.h"

/////////////////////////////////////////////////////////////////////////////
// CUIScrollBar
class ATL_NO_VTABLE CUIScrollBar : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComControl<CUIScrollBar>,

	public IConnectionPointContainerImpl<CUIScrollBar>,
	public IPersistStreamInitImpl<CUIScrollBar>,
	public IOleControlImpl<CUIScrollBar>,
	public IOleObjectImpl<CUIScrollBar>,
	public IOleInPlaceActiveObjectImpl<CUIScrollBar>,
	public IViewObjectExImpl<CUIScrollBar>,
	public IOleInPlaceObjectWindowlessImpl<CUIScrollBar>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CUIScrollBar>,
	public ISpecifyPropertyPagesImpl<CUIScrollBar>,
	public IQuickActivateImpl<CUIScrollBar>,
	public IDataObjectImpl<CUIScrollBar>,
	public IProvideClassInfo2Impl<&CLSID_UIScrollBar, &DIID__IUIScrollBarEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUIScrollBar>,

	public CComCoClass<CUIScrollBar, &CLSID_UIScrollBar>,
	public IDispatchImpl<IUIScrollBar, &IID_IUIScrollBar, &LIBID_UILib>,
	public CProxy_IUIScrollBarEvents< CUIScrollBar >
{
public:
	CUIScrollBar()
	{
		m_bWindowOnly = FALSE;

		m_pos = m_visible = m_min = m_max = 0;
		m_dir = 0;

		m_dragging = 0;

		m_hUxThemeLib = NULL;
		m_hTheme = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	HINSTANCE m_hUxThemeLib;
	HTHEME m_hTheme;

	long m_pos;
	long m_min;
	long m_max;
	long m_visible;

	long m_dir;
	WORD m_dragging;

	CRect m_leftR;
	CRect m_rightR;
	CRect m_slidR;
	CRect m_knobR;
	int m_ptoffset;
	BOOL m_bIsInside;

	void SetIt();
	void OnSize(RECT& rcPos);

DECLARE_REGISTRY_RESOURCEID(IDR_UISCROLLBAR)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUIScrollBar)
	COM_INTERFACE_ENTRY(IUIScrollBar)

	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)

	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUIScrollBar)
	CONNECTION_POINT_ENTRY(DIID__IUIScrollBarEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_PROP_MAP(CUIScrollBar)
//	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
//	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CUIScrollBar)
	CHAIN_MSG_MAP(CComControl<CUIScrollBar>)
	DEFAULT_REFLECTION_HANDLER()
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()

//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IUIScrollBar,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(0/*VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE*/)

	HRESULT OnDraw(ATL_DRAWINFO& di);

// IUIScrollBar
public:
	STDMETHOD(get_minv)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_maxv)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_visible)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_direction)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_direction)(/*[in]*/ long newVal);
	STDMETHOD(SetInfo)(/*[in]*/ long minv, /*[in]*/ long maxv, /*[in]*/ long visible);
	STDMETHOD(get_pos)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_pos)(/*[in]*/ long newVal);
};

#endif //__UISCROLLBAR_H_
