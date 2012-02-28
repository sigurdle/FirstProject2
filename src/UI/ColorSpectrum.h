// ColorSpectrum.h : Declaration of the CColorSpectrum

#ifndef __COLORSPECTRUM_H_
#define __COLORSPECTRUM_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "UICP.h"


/////////////////////////////////////////////////////////////////////////////
// CColorSpectrum
class ATL_NO_VTABLE CColorSpectrum : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CColorSpectrum, IColorSpectrum, &IID_IColorSpectrum, &LIBID_UILib>,
	public CComControl<CColorSpectrum>,
	public IPersistStreamInitImpl<CColorSpectrum>,
	public IOleControlImpl<CColorSpectrum>,
	public IOleObjectImpl<CColorSpectrum>,
	public IOleInPlaceActiveObjectImpl<CColorSpectrum>,
	public IViewObjectExImpl<CColorSpectrum>,
	public IOleInPlaceObjectWindowlessImpl<CColorSpectrum>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CColorSpectrum>,
	public IPersistStorageImpl<CColorSpectrum>,
	public ISpecifyPropertyPagesImpl<CColorSpectrum>,
	public IQuickActivateImpl<CColorSpectrum>,
	public IDataObjectImpl<CColorSpectrum>,
	public IProvideClassInfo2Impl<&CLSID_ColorSpectrum, &DIID__IColorSpectrumEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CColorSpectrum>,
	public CComCoClass<CColorSpectrum, &CLSID_ColorSpectrum>,
	public CProxy_IColorSpectrumEvents< CColorSpectrum >
{
public:
	CColorSpectrum()
	{
		m_dragging = 0;
	}

	int m_dragging;

	void OnMouseMove(CPoint point, UINT nFlags);

DECLARE_REGISTRY_RESOURCEID(IDR_COLORSPECTRUM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CColorSpectrum)
	COM_INTERFACE_ENTRY(IColorSpectrum)
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

BEGIN_PROP_MAP(CColorSpectrum)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BorderColor", DISPID_BORDERCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("BorderVisible", DISPID_BORDERVISIBLE, CLSID_NULL)
	PROP_ENTRY("BorderWidth", DISPID_BORDERWIDTH, CLSID_NULL)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CColorSpectrum)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IColorSpectrumEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CColorSpectrum)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	CHAIN_MSG_MAP(CComControl<CColorSpectrum>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IColorSpectrum,
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

// IColorSpectrum
public:

	HRESULT OnDraw(ATL_DRAWINFO& di);
	OLE_COLOR m_clrBorderColor;
	BOOL m_bBorderVisible;
	LONG m_nBorderWidth;
	BOOL m_bEnabled;
};

#endif //__COLORSPECTRUM_H_
