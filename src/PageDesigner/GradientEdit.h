// GradientEdit.h : Declaration of the CGradientEdit

#ifndef __GRADIENTEDIT_H_
#define __GRADIENTEDIT_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "PageDesignerCP.h"


/////////////////////////////////////////////////////////////////////////////
// CGradientEdit
class ATL_NO_VTABLE CGradientEdit : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CGradientEdit, IGradientEdit, &IID_IGradientEdit, &LIBID_PAGEDESIGNERLib>,
	public CComControl<CGradientEdit>,
	public IPersistStreamInitImpl<CGradientEdit>,
	public IOleControlImpl<CGradientEdit>,
	public IOleObjectImpl<CGradientEdit>,
	public IOleInPlaceActiveObjectImpl<CGradientEdit>,
	public IViewObjectExImpl<CGradientEdit>,
	public IOleInPlaceObjectWindowlessImpl<CGradientEdit>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CGradientEdit>,
	public IPersistStorageImpl<CGradientEdit>,
	public ISpecifyPropertyPagesImpl<CGradientEdit>,
	public IQuickActivateImpl<CGradientEdit>,
	public IDataObjectImpl<CGradientEdit>,
	public IProvideClassInfo2Impl<&CLSID_GradientEdit, &DIID__IGradientEditEvents, &LIBID_PAGEDESIGNERLib>,
	public IPropertyNotifySinkCP<CGradientEdit>,
	public CComCoClass<CGradientEdit, &CLSID_GradientEdit>,
	public CProxy_IGradientEditEvents< CGradientEdit >,

	public CNotifyGetImpl<CGradientEdit>
{
public:
	CGradientEdit()
	{
		m_bWindowOnly = TRUE;

		m_dragging = 0;

		m_clrBackColor = GetSysColor(COLOR_BTNFACE);
	}

	void FinalRelease();

	int m_dragging;
	CComPtr<IPDGradient> m_gradient;

	CComPtr<IPDGradientStop> m_stop;

DECLARE_REGISTRY_RESOURCEID(IDR_GRADIENTEDIT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGradientEdit)
	COM_INTERFACE_ENTRY(IGradientEdit)
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

	COM_INTERFACE_ENTRY(INotifyGet)
END_COM_MAP()

BEGIN_PROP_MAP(CGradientEdit)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CGradientEdit)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IGradientEditEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CGradientEdit)
	CHAIN_MSG_MAP(CComControl<CGradientEdit>)
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


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IGradientEdit,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

	HRESULT OnDraw(ATL_DRAWINFO& di);

	OLE_COLOR m_clrBackColor;
	BOOL m_bEnabled;

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		if (m_hWnd)
		{
			Invalidate();
		}
		return S_OK;
	}

// IGradientEdit
public:
	STDMETHOD(get_gradient)(/*[out, retval]*/ IPDGradient* *pVal);
	STDMETHOD(put_gradient)(/*[in]*/ IPDGradient* newVal);
};

#endif //__GRADIENTEDIT_H_
