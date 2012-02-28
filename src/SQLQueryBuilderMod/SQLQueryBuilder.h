// SQLQueryBuilder.h : Declaration of the CSQLQueryBuilder

#ifndef __SQLQUERYBUILDER_H_
#define __SQLQUERYBUILDER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

class CSQLQueryTables;
class CSQLQueryTablesScroll;

class CSQLQueryFields;

/////////////////////////////////////////////////////////////////////////////
// CSQLQueryBuilder
class ATL_NO_VTABLE CSQLQueryBuilder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CSQLQueryBuilder, ISQLQueryBuilder, &IID_ISQLQueryBuilder, &LIBID_SQLQUERYBUILDERMODLib>,
	public CComControl<CSQLQueryBuilder>,
	public IPersistStreamInitImpl<CSQLQueryBuilder>,
	public IOleControlImpl<CSQLQueryBuilder>,
	public IOleObjectImpl<CSQLQueryBuilder>,
	public IOleInPlaceActiveObjectImpl<CSQLQueryBuilder>,
	public IViewObjectExImpl<CSQLQueryBuilder>,
	public IOleInPlaceObjectWindowlessImpl<CSQLQueryBuilder>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSQLQueryBuilder>,
	public IPersistStorageImpl<CSQLQueryBuilder>,
	public ISpecifyPropertyPagesImpl<CSQLQueryBuilder>,
	public IQuickActivateImpl<CSQLQueryBuilder>,
	public IDataObjectImpl<CSQLQueryBuilder>,
	public IProvideClassInfo2Impl<&CLSID_SQLQueryBuilder, &DIID__ISQLQueryBuilderEvents, &LIBID_SQLQUERYBUILDERMODLib>,
	public IPropertyNotifySinkCP<CSQLQueryBuilder>,
	public CComCoClass<CSQLQueryBuilder, &CLSID_SQLQueryBuilder>
{
public:
	CSQLQueryBuilder()
	{
		m_bWindowOnly = TRUE;

		m_tablesWnd = NULL;
		m_fieldsWnd = NULL;

		m_splity = 200;
		m_dragging = 0;
	}

	int m_dragging;

	_bstr_t m_connstr;
	ADODB::_ConnectionPtr m_conn;
	ADOX::_CatalogPtr m_catalog;

	CComObject<CSQLQueryTablesScroll>* m_tablesWnd;
	CComObject<CSQLQueryFields>* m_fieldsWnd;

	int m_splity;

	void OnSize();

DECLARE_REGISTRY_RESOURCEID(IDR_SQLQUERYBUILDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSQLQueryBuilder)
	COM_INTERFACE_ENTRY(ISQLQueryBuilder)
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
END_COM_MAP()

BEGIN_PROP_MAP(CSQLQueryBuilder)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CSQLQueryBuilder)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CSQLQueryBuilder)
	CHAIN_MSG_MAP(CComControl<CSQLQueryBuilder>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
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
			&IID_ISQLQueryBuilder,
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

// ISQLQueryBuilder
public:
	STDMETHOD(get_connstr)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_connstr)(/*[in]*/ BSTR newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di);
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

#endif //__SQLQUERYBUILDER_H_
