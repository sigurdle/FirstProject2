// UIListControl.h : Declaration of the CUIListControl

#ifndef __UILISTCONTROL_H_
#define __UILISTCONTROL_H_

#include "resource.h"       // main symbols
#include "UICP.h"

/////////////////////////////////////////////////////////////////////////////
// CUIListControl
class ATL_NO_VTABLE CUIListControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComControl<CUIListControl>,

	public IConnectionPointContainerImpl<CUIListControl>,
	public IDispatchImpl<IUIListControl, &IID_IUIListControl, &LIBID_UILib>,

	public IPersistStreamInitImpl<CUIListControl>,
	public IOleControlImpl<CUIListControl>,
	public IOleObjectImpl<CUIListControl>,
	public IOleInPlaceActiveObjectImpl<CUIListControl>,
	public IViewObjectExImpl<CUIListControl>,
	public IOleInPlaceObjectWindowlessImpl<CUIListControl>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CUIListControl>,
	public ISpecifyPropertyPagesImpl<CUIListControl>,
	public IQuickActivateImpl<CUIListControl>,
	public IDataObjectImpl<CUIListControl>,
	public IProvideClassInfo2Impl<&CLSID_UIListControl, &DIID__IUITreeControlEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUIListControl>,

	public CComCoClass<CUIListControl, &CLSID_UIListControl>,
	public CProxy_IUIListControlEvents< CUIListControl >,

	public IDispEventImpl<1, CUIListControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CUIListControl()
	{
		m_bWindowOnly = TRUE;

		m_cursel = -1;
		m_nCheckStyle = 0;
		m_multipleSelect = FALSE;

		m_itemHeight = 16;
	}

	int FinalConstruct()
	{
		m_vert.CoCreateInstance(CLSID_UIScrollBar);
		m_vert->put_direction(1);
		IDispEventImpl<1, CUIListControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

		return S_OK;
	}

	void FinalRelease()
	{
		IDispEventImpl<1, CUIListControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	}

	CAxWindow	m_axvert;
	CAxWindow	m_axhorz;

	CComQIPtr<IUIScrollBar> m_vert;
	CComQIPtr<IUIScrollBar> m_horz;

	BOOL m_multipleSelect;
	DWORD m_nCheckStyle;

	int m_itemHeight;

	long m_cursel;
	CArray<CListEntry*, CListEntry*> m_listEntries;

	//CComQIPtr<ICustomDraw> m_customDraw;

	void OnSize();

DECLARE_REGISTRY_RESOURCEID(IDR_UILISTCONTROL)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUIListControl)
	COM_INTERFACE_ENTRY(IUIListControl)
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

BEGIN_CONNECTION_POINT_MAP(CUIListControl)
	CONNECTION_POINT_ENTRY(DIID__IUIListControlEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_PROP_MAP(CUIListControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_SINK_MAP(CUIListControl)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	HRESULT __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CUIListControl)
	CHAIN_MSG_MAP(CComControl<CUIListControl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IUIListControl,
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

	HRESULT OnDraw(ATL_DRAWINFO& di);

// IUIListControl
public:
	STDMETHOD(get_multipleSelect)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_multipleSelect)(/*[in]*/ BOOL newVal);
	STDMETHOD(GetCheck)(/*[in]*/ long index, /*[out,retval]*/ DWORD* check);
	STDMETHOD(SetCheck)(/*[in]*/ long index, /*[in]*/ DWORD check);
	STDMETHOD(get_CheckStyle)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_CheckStyle)(/*[in]*/ DWORD newVal);
	STDMETHOD(GetItemText)(/*[in]*/ unsigned long index, /*[out,retval]*/ BSTR* pVal);
	//STDMETHOD(SetCustomDraw)(/*[in]*/ ICustomDraw* custom);
	STDMETHOD(ResetContent)();
	STDMETHOD(GetItemData)(/*[in]*/ long index, /*[out,retval]*/ DWORD* data);
	STDMETHOD(SetItemData)(/*[in]*/ long index, /*[in]*/ DWORD data);
	STDMETHOD(get_cursel)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_cursel)(/*[in]*/ long newVal);
	STDMETHOD(AddString)(/*[in]*/ BSTR string, /*[out,retval]*/ long* index);
};

#endif //__UILISTCONTROL_H_
