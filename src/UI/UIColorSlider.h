// UIColorSlider.h : Declaration of the CUIColorSlider

#ifndef __UICOLORSLIDER_H_
#define __UICOLORSLIDER_H_

#include "resource.h"       // main symbols
#include "UICP.h"

/////////////////////////////////////////////////////////////////////////////
// CUIColorSlider
class ATL_NO_VTABLE CUIColorSlider : 
	public CComObjectRootEx<CComSingleThreadModel>,

	public CComControl<CUIColorSlider>,

	public CStockPropImpl<CUIColorSlider, IUIColorSlider, &IID_IUIColorSlider, &LIBID_UILib>,

	public IPersistPropertyBagImpl<CUIColorSlider>,

	public IConnectionPointContainerImpl<CUIColorSlider>,
	public IPersistStreamInitImpl<CUIColorSlider>,
	public IOleControlImpl<CUIColorSlider>,
	public IOleObjectImpl<CUIColorSlider>,
	public IOleInPlaceActiveObjectImpl<CUIColorSlider>,
	public IViewObjectExImpl<CUIColorSlider>,
	public IOleInPlaceObjectWindowlessImpl<CUIColorSlider>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CUIColorSlider>,
	public ISpecifyPropertyPagesImpl<CUIColorSlider>,
	public IQuickActivateImpl<CUIColorSlider>,
	public IDataObjectImpl<CUIColorSlider>,
	public IProvideClassInfo2Impl<&CLSID_UIColorSlider, &DIID__IUIColorSliderEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUIColorSlider>,

//	public IDispatchImpl<IUIColorSlider, &IID_IUIColorSlider, &LIBID_UILib>,
	public CComCoClass<CUIColorSlider, &CLSID_UIColorSlider>,

	public CProxy_IUIColorSliderEvents< CUIColorSlider >
{
public:
	CUIColorSlider()
	{
		m_bWindowOnly = FALSE;

		//m_ddc = NULL;
		m_dragging = 0;
		m_type = 3;
		m_channel = 0;
		m_colorMode = 2;	// RGB

		m_pos = 0;
	}

	int FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	//HDRAWDIB	m_ddc;
	long m_colorMode;
	long	m_channel;
	WORD	m_dragging;
	int	m_type;

	DWORD m_fromValue;
	DWORD m_toValue;
	long m_pos;

DECLARE_REGISTRY_RESOURCEID(IDR_UICOLORSLIDER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUIColorSlider)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIColorSlider)

	COM_INTERFACE_ENTRY(IPersistPropertyBag)

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

BEGIN_CONNECTION_POINT_MAP(CUIColorSlider)
	CONNECTION_POINT_ENTRY(DIID__IUIColorSliderEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_PROP_MAP(CUIColorSlider)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_DATA_ENTRY("channel", m_channel, VT_UI4)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CUIColorSlider)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)

	CHAIN_MSG_MAP(CComControl<CUIColorSlider>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IUIColorSlider,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	BOOL m_bEnabled;

	HRESULT OnDraw(ATL_DRAWINFO& di);

// IUIColorSlider
public:
	STDMETHOD(get_pos)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_pos)(/*[in]*/ long newVal);
	STDMETHOD(get_toValue)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_toValue)(/*[in]*/ DWORD newVal);
	STDMETHOD(get_fromValue)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_fromValue)(/*[in]*/ DWORD newVal);
	STDMETHOD(get_colorMode)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_colorMode)(/*[in]*/ long newVal);
	STDMETHOD(get_rgb)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_rgb)(/*[in]*/ DWORD newVal);
	STDMETHOD(get_channel)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_channel)(/*[in]*/ long newVal);
};

#endif //__UICOLORSLIDER_H_
