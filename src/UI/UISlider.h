// UISlider.h : Declaration of the CUISlider

#ifndef __UISLIDER_H_
#define __UISLIDER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "UICP.h"

/////////////////////////////////////////////////////////////////////////////
// CUISlider
class ATL_NO_VTABLE CUISlider : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CUISlider, IUISlider, &IID_IUISlider, &LIBID_UILib>,
	public CComControl<CUISlider>,
	public IPersistStreamInitImpl<CUISlider>,
	public IOleControlImpl<CUISlider>,
	public IOleObjectImpl<CUISlider>,
	public IOleInPlaceActiveObjectImpl<CUISlider>,
	public IViewObjectExImpl<CUISlider>,
	public IOleInPlaceObjectWindowlessImpl<CUISlider>,
	public IConnectionPointContainerImpl<CUISlider>,
	public IPersistStorageImpl<CUISlider>,
	public ISpecifyPropertyPagesImpl<CUISlider>,
	public IQuickActivateImpl<CUISlider>,
	public IDataObjectImpl<CUISlider>,
	public IProvideClassInfo2Impl<&CLSID_UISlider, &DIID__IUISliderEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUISlider>,
	public CComCoClass<CUISlider, &CLSID_UISlider>,
	public CProxy_IUISliderEvents< CUISlider >
{
public:
	CUISlider()
	{
		m_value = 0;
		m_minValue = 0;
		m_maxValue = 100;

		m_dragging = 0;
	}

	int m_dragging;

	int m_xoffset;

	long m_value;
	long m_minValue;
	long m_maxValue;

DECLARE_REGISTRY_RESOURCEID(IDR_UISLIDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUISlider)
	COM_INTERFACE_ENTRY(IUISlider)
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
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CUISlider)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CUISlider)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IUISliderEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CUISlider)
	CHAIN_MSG_MAP(CComControl<CUISlider>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IUISlider
public:
	STDMETHOD(get_value)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_value)(/*[in]*/ long newVal);
	STDMETHOD(get_maxValue)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_maxValue)(/*[in]*/ long newVal);
	STDMETHOD(get_minValue)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_minValue)(/*[in]*/ long newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di);
	BOOL m_bEnabled;
};

#endif //__UISLIDER_H_
