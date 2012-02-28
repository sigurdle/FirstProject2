// HSLColorWheel.h : Declaration of the CUIHSLColorWheel

#ifndef __HSLCOLORWHEEL_H_
#define __HSLCOLORWHEEL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>


/////////////////////////////////////////////////////////////////////////////
// CUIHSLColorWheel
class ATL_NO_VTABLE CUIHSLColorWheel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CUIHSLColorWheel, IUIHSLColorWheel, &IID_IUIHSLColorWheel, &LIBID_UILib>,
//	public IDispatchImpl<IUIHSLColorWheel, &IID_IUIHSLColorWheel, &LIBID_UILib>,
	public CComControl<CUIHSLColorWheel>,
	public IPersistStreamInitImpl<CUIHSLColorWheel>,
	public IOleControlImpl<CUIHSLColorWheel>,
	public IOleObjectImpl<CUIHSLColorWheel>,
	public IOleInPlaceActiveObjectImpl<CUIHSLColorWheel>,
	public IViewObjectExImpl<CUIHSLColorWheel>,
	public IOleInPlaceObjectWindowlessImpl<CUIHSLColorWheel>,
	public IConnectionPointContainerImpl<CUIHSLColorWheel>,
	public IPersistStorageImpl<CUIHSLColorWheel>,
	public ISpecifyPropertyPagesImpl<CUIHSLColorWheel>,
	public IQuickActivateImpl<CUIHSLColorWheel>,
	public IDataObjectImpl<CUIHSLColorWheel>,
	public IProvideClassInfo2Impl<&CLSID_UIHSLColorWheel, &DIID__IUIHSLColorWheelEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUIHSLColorWheel>,
	public CComCoClass<CUIHSLColorWheel, &CLSID_UIHSLColorWheel>
{
public:
	CUIHSLColorWheel()
	{
		m_bWindowOnly = FALSE;

		m_dragging = 0;
		m_hue = 0;
		m_sat = 0;
		m_lum = 0;
	}

	int m_dragging;
	double m_hue;	// 0..360
	long m_sat;	// 0..255
	long m_lum;	// 0..255

DECLARE_REGISTRY_RESOURCEID(IDR_UIHSLCOLORWHEEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUIHSLColorWheel)
	COM_INTERFACE_ENTRY(IUIHSLColorWheel)
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
END_COM_MAP()

BEGIN_PROP_MAP(CUIHSLColorWheel)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CUIHSLColorWheel)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CUIHSLColorWheel)
	CHAIN_MSG_MAP(CComControl<CUIHSLColorWheel>)
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

	HRESULT OnDraw(ATL_DRAWINFO& di);

	BOOL m_bEnabled;

// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// IHSLColorWheel
public:
	STDMETHOD(get_lum)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_lum)(/*[in]*/ long newVal);
	STDMETHOD(get_sat)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_sat)(/*[in]*/ long newVal);
	STDMETHOD(get_hue)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_hue)(/*[in]*/ long newVal);
};

#endif //__HSLCOLORWHEEL_H_
