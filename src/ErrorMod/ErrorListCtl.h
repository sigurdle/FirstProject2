// ErrorListCtl.h : Declaration of the CErrorListCtl

#ifndef __ERRORLISTCTL_H_
#define __ERRORLISTCTL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "ErrorModCP.h"


/////////////////////////////////////////////////////////////////////////////
// CErrorListCtl
class ATL_NO_VTABLE CErrorListCtl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CErrorListCtl, IErrorListCtl, &IID_IErrorListCtl, &LIBID_ERRORMODLib>,
	public CComControl<CErrorListCtl>,
	public IPersistStreamInitImpl<CErrorListCtl>,
	public IOleControlImpl<CErrorListCtl>,
	public IOleObjectImpl<CErrorListCtl>,
	public IOleInPlaceActiveObjectImpl<CErrorListCtl>,
	public IViewObjectExImpl<CErrorListCtl>,
	public IOleInPlaceObjectWindowlessImpl<CErrorListCtl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CErrorListCtl>,
	public IPersistStorageImpl<CErrorListCtl>,
	public ISpecifyPropertyPagesImpl<CErrorListCtl>,
	public IQuickActivateImpl<CErrorListCtl>,
	public IDataObjectImpl<CErrorListCtl>,
	public IProvideClassInfo2Impl<&CLSID_ErrorListCtl, &DIID__IErrorListCtlEvents, &LIBID_ERRORMODLib>,
	public IPropertyNotifySinkCP<CErrorListCtl>,
	public CComCoClass<CErrorListCtl, &CLSID_ErrorListCtl>,

	public IDispEventImpl<1, CErrorListCtl, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>,
	public CProxy_IErrorListCtlEvents< CErrorListCtl >
{
public:
	CErrorListCtl()
	{
		m_bWindowOnly = TRUE;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = m_errorListBox.CoCreateInstance(CLSID_UIEdit);
		if (FAILED(hr)) return E_NOINTERFACE;

		return S_OK;
	}

	CAxWindow m_axerrorListBox;
	CComPtr<IUIEdit> m_errorListBox;

	CComQIPtr<IErrorList> m_errorList;

	void FillErrorListBox();

DECLARE_REGISTRY_RESOURCEID(IDR_ERRORLISTCTL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CErrorListCtl)
	COM_INTERFACE_ENTRY(IErrorListCtl)
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

BEGIN_PROP_MAP(CErrorListCtl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CErrorListCtl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IErrorListCtlEvents)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CErrorListCtl)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/4, OnEditDblClick)
END_SINK_MAP()

	void __stdcall OnEditDblClick(long offset, long line, long column);

BEGIN_MSG_MAP(CErrorListCtl)
	CHAIN_MSG_MAP(CComControl<CErrorListCtl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IErrorListCtl,
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

// IErrorListCtl
public:
	STDMETHOD(UpdateList)();
	STDMETHOD(get_errorList)(/*[out, retval]*/ IErrorList* *pVal);
	STDMETHOD(put_errorList)(/*[in]*/ IErrorList* newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		return S_OK;
	}
	OLE_COLOR m_clrBackColor;
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
	OLE_COLOR m_clrForeColor;
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

#endif //__ERRORLISTCTL_H_
