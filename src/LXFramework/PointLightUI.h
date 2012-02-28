// PointLightUI.h : Declaration of the CPointLightUI

#ifndef __POINTLIGHTUI_H_
#define __POINTLIGHTUI_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "LXFrameworkCP.h"

/////////////////////////////////////////////////////////////////////////////
// CPointLightUI
class ATL_NO_VTABLE CPointLightUI : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CPointLightUI, IPointLightUI, &IID_IPointLightUI, &LIBID_LXFRAMEWORKLib>,
	public CComControl<CPointLightUI>,
	public IPersistStreamInitImpl<CPointLightUI>,
	public IOleControlImpl<CPointLightUI>,
	public IOleObjectImpl<CPointLightUI>,
	public IOleInPlaceActiveObjectImpl<CPointLightUI>,
	public IViewObjectExImpl<CPointLightUI>,
	public IOleInPlaceObjectWindowlessImpl<CPointLightUI>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPointLightUI>,
	public IPersistStorageImpl<CPointLightUI>,
	public ISpecifyPropertyPagesImpl<CPointLightUI>,
	public IQuickActivateImpl<CPointLightUI>,
	public IDataObjectImpl<CPointLightUI>,
	public IProvideClassInfo2Impl<&CLSID_PointLightUI, &DIID__IPointLightUIEvents, &LIBID_LXFRAMEWORKLib>,
	public IPropertyNotifySinkCP<CPointLightUI>,
	public CComCoClass<CPointLightUI, &CLSID_PointLightUI>,
	public CProxy_IPointLightUIEvents< CPointLightUI >
{
public:
	CPointLightUI()
	{
		m_dragging = 0;

		m_dVec[0] = -0.52;
		m_dVec[1] = -0.66;
		m_dVec[2] = 0.5;
	}

	CPoint m_iLastMouse;

	int m_dragging;

//	double m_dVec[3];              // Vector components
	gmVector3 m_dVec;              // Vector components

	COLORREF CalcLight(gmVector3& dVec, double dx, double dy, double dz);
//	BOOL Normalize();
	void RotateByXandY(double XRot, double YRot);

	void OnMouseMove(CPoint point);

DECLARE_REGISTRY_RESOURCEID(IDR_POINTLIGHTUI)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPointLightUI)
	COM_INTERFACE_ENTRY(IPointLightUI)
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

BEGIN_PROP_MAP(CPointLightUI)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
//	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL) (read-only) Bug that this is inserted?
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CPointLightUI)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IPointLightUIEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CPointLightUI)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	CHAIN_MSG_MAP(CComControl<CPointLightUI>)
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
			&IID_IPointLightUI,
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

// IPointLightUI
public:
	STDMETHOD(get_z)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_y)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_x)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetXYZ)(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double z);

	HRESULT OnDraw(ATL_DRAWINFO& di);

	OLE_COLOR m_clrBackColor;
	BOOL m_bEnabled;
	OLE_COLOR m_clrForeColor;
};

#endif //__POINTLIGHTUI_H_
