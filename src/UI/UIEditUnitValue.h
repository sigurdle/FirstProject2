// UIEditUnitValue.h : Declaration of the CUIEditUnitValue

#ifndef __UIEDITUNITVALUE_H_
#define __UIEDITUNITVALUE_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "UICP.h"


/////////////////////////////////////////////////////////////////////////////
// CUIEditUnitValue
class ATL_NO_VTABLE CUIEditUnitValue : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CUIEditUnitValue, IUIEditUnitValue, &IID_IUIEditUnitValue, &LIBID_UILib>,
	public CComControl<CUIEditUnitValue>,
	public IPersistStreamInitImpl<CUIEditUnitValue>,
	public IOleControlImpl<CUIEditUnitValue>,
	public IOleObjectImpl<CUIEditUnitValue>,
	public IOleInPlaceActiveObjectImpl<CUIEditUnitValue>,
	public IViewObjectExImpl<CUIEditUnitValue>,
	public IOleInPlaceObjectWindowlessImpl<CUIEditUnitValue>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CUIEditUnitValue>,
	public IPersistStorageImpl<CUIEditUnitValue>,
	public ISpecifyPropertyPagesImpl<CUIEditUnitValue>,
	public IQuickActivateImpl<CUIEditUnitValue>,
	public IDataObjectImpl<CUIEditUnitValue>,
	public IProvideClassInfo2Impl<&CLSID_UIEditUnitValue, &DIID__IUIEditUnitValueEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUIEditUnitValue>,
	public CComCoClass<CUIEditUnitValue, &CLSID_UIEditUnitValue>,
	public IDispEventImpl<1, CUIEditUnitValue, &DIID__IUIEditEvents	, &LIBID_UILib, 1, 0>,
	public CProxy_IUIEditUnitValueEvents< CUIEditUnitValue >
{
public:
	CUIEditUnitValue()
	{
		m_bWindowOnly = TRUE;

		m_value = 0;
	}

	CAxWindow m_axedit;
	CComPtr<IUIEdit> m_edit;

	double m_value;

DECLARE_REGISTRY_RESOURCEID(IDR_UIEDITUNITVALUE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUIEditUnitValue)
	COM_INTERFACE_ENTRY(IUIEditUnitValue)
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

BEGIN_PROP_MAP(CUIEditUnitValue)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CUIEditUnitValue)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IUIEditUnitValueEvents)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CUIEditUnitValue)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/2, OnEditChange)
END_SINK_MAP()

	HRESULT __stdcall OnEditChange();

BEGIN_MSG_MAP(CUIEditUnitValue)
	CHAIN_MSG_MAP(CComControl<CUIEditUnitValue>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IUIEditUnitValue,
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

// IUIEditUnitValue
public:
	STDMETHOD(get_value)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_value)(/*[in]*/ double newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : UIEditUnitValue");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
};

#endif //__UIEDITUNITVALUE_H_
