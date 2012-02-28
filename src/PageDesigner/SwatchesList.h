// SwatchesList.h : Declaration of the CSwatchesList

#ifndef __SWATCHESLIST_H_
#define __SWATCHESLIST_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "PageDesignerCP.h"

extern bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

/////////////////////////////////////////////////////////////////////////////
// CSwatchesList
class ATL_NO_VTABLE CSwatchesList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CSwatchesList, ISwatchesList, &IID_ISwatchesList, &LIBID_PAGEDESIGNERLib>,
	public CComControl<CSwatchesList>,
	public IPersistStreamInitImpl<CSwatchesList>,
	public IOleControlImpl<CSwatchesList>,
	public IOleObjectImpl<CSwatchesList>,
	public IOleInPlaceActiveObjectImpl<CSwatchesList>,
	public IViewObjectExImpl<CSwatchesList>,
	public IOleInPlaceObjectWindowlessImpl<CSwatchesList>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSwatchesList>,
	public IPersistStorageImpl<CSwatchesList>,
	public ISpecifyPropertyPagesImpl<CSwatchesList>,
	public IQuickActivateImpl<CSwatchesList>,
	public IDataObjectImpl<CSwatchesList>,
	public IProvideClassInfo2Impl<&CLSID_SwatchesList, &DIID__ISwatchesListEvents, &LIBID_PAGEDESIGNERLib>,
	public IPropertyNotifySinkCP<CSwatchesList>,
	public CComCoClass<CSwatchesList, &CLSID_SwatchesList>,
	public CProxy_ISwatchesListEvents< CSwatchesList >,

	public IDispEventImpl<1, CSwatchesList, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,

	public CNotifyGetImpl<CSwatchesList>
{
public:
	CSwatchesList()
	{
		m_bWindowOnly = TRUE;

		m_selectedSwatchIndex = -1;

		m_bEnabled = TRUE;
		m_multiSelect = VARIANT_FALSE;

		m_itemHeight = 20;
	}

	int FinalConstruct()
	{
		HRESULT hr;
		hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
		if (FAILED(hr)) return hr;
		m_vert->put_direction(1);

		return S_OK;
	}

	void FinalRelease()
	{
		DeselectAll();

		if (m_swatches)
		{
			CComQIPtr<INotifySend> cp = m_swatches;
			cp->Unadvise(this);
		}

		if (m_vert)
		{
			m_vert.Release();
		}
	}

	int m_itemHeight;
	VARIANT_BOOL m_multiSelect;

	CComPtr<IPDSwatches> m_swatches;

	int m_selectedSwatchIndex;
	CArray<IPDSwatch*,IPDSwatch*> m_selectedSwatches;

	CRect m_areaRect;

	CAxWindow m_axvert;
	CComPtr<IUIScrollBar> m_vert;

	void OnSize();

	bool IsSwatchSelected(IPDSwatch* swatch)
	{
		for (int i = 0; i < m_selectedSwatches.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(swatch, m_selectedSwatches[i]))
			{
				return true;
			}
		}

		return false;
	}

	void DeselectSwatch(IPDSwatch* swatch)
	{
		for (int i = 0; i < m_selectedSwatches.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(swatch, m_selectedSwatches[i]))
			{
				m_selectedSwatches[i]->Release();
				m_selectedSwatches.RemoveAt(i);
			}
		}
	}

	void DeselectAll()
	{
		for (int i = m_selectedSwatches.GetSize()-1; i >= 0; i--)
		{
			m_selectedSwatches[i]->Release();
			m_selectedSwatches.RemoveAt(i);
		}
	}

	void SelectSwatch(IPDSwatch* swatch)
	{
		ATLASSERT(!IsSwatchSelected(swatch));

		swatch->AddRef();
		m_selectedSwatches.Add(swatch);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SWATCHESLIST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSwatchesList)
	COM_INTERFACE_ENTRY(ISwatchesList)
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

BEGIN_PROP_MAP(CSwatchesList)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CSwatchesList)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__ISwatchesListEvents)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CSwatchesList)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	HRESULT __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CSwatchesList)
	CHAIN_MSG_MAP(CComControl<CSwatchesList>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_ISwatchesList,
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

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		for (int i = m_selectedSwatches.GetSize()-1; i >= 0; i--)
		{
			CComPtr<IPDSwatches> swatches;
			m_selectedSwatches[i]->get_parent(&swatches);
			if (!IsUnknownEqualUnknown(swatches, m_swatches))
			{
				int refcount = m_selectedSwatches[i]->Release();
				m_selectedSwatches.RemoveAt(i);
			}
		}

		if (m_hWnd)
		{
			OnSize();
			InvalidateRect(&m_areaRect);
		}

		return S_OK;
	}

// ISwatchesList
public:
	STDMETHOD(get_showSwatchGradient)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_showSwatchGradient)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_showSwatchColor)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_showSwatchColor)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_showSwatchNone)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_showSwatchNone)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_multiSelect)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_multiSelect)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(getNextSelectedSwatch)(/*[in]*/ long index, /*[out,retval]*/ IPDSwatch* *pVal);
	STDMETHOD(selectSwatch)(/*[in]*/ IPDSwatch* swatch);
	STDMETHOD(get_swatches)(/*[out, retval]*/ IPDSwatches* *pVal);
	STDMETHOD(put_swatches)(/*[in]*/ IPDSwatches* newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di);
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
};

#endif //__SWATCHESLIST_H_
