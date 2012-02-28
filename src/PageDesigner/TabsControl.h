// TabsControl.h : Declaration of the CTabsControl

#ifndef __TABSCONTROL_H_
#define __TABSCONTROL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "PageDesignerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CTabsControl
class ATL_NO_VTABLE CTabsControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CTabsControl, ITabsControl, &IID_ITabsControl, &LIBID_PAGEDESIGNERLib>,
	public CComControl<CTabsControl>,
	public IPersistStreamInitImpl<CTabsControl>,
	public IOleControlImpl<CTabsControl>,
	public IOleObjectImpl<CTabsControl>,
	public IOleInPlaceActiveObjectImpl<CTabsControl>,
	public IViewObjectExImpl<CTabsControl>,
	public IOleInPlaceObjectWindowlessImpl<CTabsControl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CTabsControl>,
	public IPersistStorageImpl<CTabsControl>,
	public ISpecifyPropertyPagesImpl<CTabsControl>,
	public IQuickActivateImpl<CTabsControl>,
	public IDataObjectImpl<CTabsControl>,
	public IProvideClassInfo2Impl<&CLSID_TabsControl, &DIID__ITabsControlEvents, &LIBID_PAGEDESIGNERLib>,
	public IPropertyNotifySinkCP<CTabsControl>,
	public CComCoClass<CTabsControl, &CLSID_TabsControl>,

	public IPersistPropertyBagImpl<CTabsControl>,
	public CProxy_ITabsControlEvents< CTabsControl >
{
public:
	CTabsControl()
	{
		m_magnify = 1.0;

		m_bWindowOnly = TRUE;

		m_pageWidth = 160;

		m_dragging = 0;

		m_tbAlign = 0;

		m_selected = 0;
		m_bDeletingTab = false;

		m_clrBackColor = RGB(255,255,255);
		m_clrForeColor = RGB(0,0,0);

		m_scrollposX = 0;
	}

	int FinalConstruct()
	{
		FONTDESC	fd;
		fd.cbSizeofstruct = sizeof(fd);
		fd.lpstrName = L"Small Fonts";
		fd.cySize.Hi = -11;
		fd.cySize.Lo = 0xffff;
		fd.sWeight = 0;
		fd.sCharset = 0;
		fd.fItalic = FALSE;
		fd.fUnderline = FALSE;
		fd.fStrikethrough = FALSE;

		HRESULT hr = OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&m_pFont);
		ATLASSERT(SUCCEEDED(hr));

		return S_OK;
	}

	void FinalRelease()
	{
	}

	CComPtr<IPDTextPara> m_textPara;

	int m_dragging;
	int m_selected;

	long m_tbAlign;

	bool m_bDeletingTab;

	double m_magnify;

	double m_pageWidth;

	CPoint m_startpoint;
	CPoint m_oldpoint;

	int m_scrollposX;
	int m_initialscrollposX;

	CRect m_areaRect;

DECLARE_REGISTRY_RESOURCEID(IDR_TABSCONTROL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTabsControl)
	COM_INTERFACE_ENTRY(ITabsControl)
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

	COM_INTERFACE_ENTRY(IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CTabsControl)
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

BEGIN_CONNECTION_POINT_MAP(CTabsControl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__ITabsControlEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CTabsControl)
	CHAIN_MSG_MAP(CComControl<CTabsControl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);;
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_ITabsControl,
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

// ITabsControl
public:
	STDMETHOD(get_tbAlign)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_tbAlign)(/*[in]*/ long newVal);
	STDMETHOD(get_selected)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_selected)(/*[in]*/ long newVal);
	STDMETHOD(get_textPara)(/*[out, retval]*/ IPDTextPara* *pVal);
	STDMETHOD(put_textPara)(/*[in]*/ IPDTextPara* newVal);
	STDMETHOD(get_pageWidth)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_pageWidth)(/*[in]*/ double newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di);

	OLE_COLOR m_clrBackColor;
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
	OLE_COLOR m_clrForeColor;
};

#endif //__TABSCONTROL_H_
