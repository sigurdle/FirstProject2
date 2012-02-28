// UIToolbarButtons.h : Declaration of the CUIToolbarButtons

#ifndef __UITOOLBARBUTTONS_H_
#define __UITOOLBARBUTTONS_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "UICP.h"

class CToolbarButton
{
public:
	long m_id;
	long m_bmIndex;
};

/////////////////////////////////////////////////////////////////////////////
// CUIToolbarButtons
class ATL_NO_VTABLE CUIToolbarButtons : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CUIToolbarButtons, IUIToolbarButtons, &IID_IUIToolbarButtons, &LIBID_UILib>,
	public CComControl<CUIToolbarButtons>,
	public IPersistStreamInitImpl<CUIToolbarButtons>,
	public IOleControlImpl<CUIToolbarButtons>,
	public IOleObjectImpl<CUIToolbarButtons>,
	public IOleInPlaceActiveObjectImpl<CUIToolbarButtons>,
	public IViewObjectExImpl<CUIToolbarButtons>,
	public IOleInPlaceObjectWindowlessImpl<CUIToolbarButtons>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CUIToolbarButtons>,
	public IPersistStorageImpl<CUIToolbarButtons>,
	public ISpecifyPropertyPagesImpl<CUIToolbarButtons>,
	public IQuickActivateImpl<CUIToolbarButtons>,
	public IDataObjectImpl<CUIToolbarButtons>,
	public IProvideClassInfo2Impl<&CLSID_UIToolbarButtons, &DIID__IUIToolbarButtonsEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUIToolbarButtons>,
	public CComCoClass<CUIToolbarButtons, &CLSID_UIToolbarButtons>,
	public CProxy_IUIToolbarButtonsEvents< CUIToolbarButtons >
{
public:
	CUIToolbarButtons()
	{
		m_bWindowOnly = FALSE;

		m_hBitmap = NULL;
		m_nWidth = 0;

		m_dragging = 0;
		m_bInsideRect = FALSE;
	}

	HBITMAP m_hBitmap;
	long m_nWidth;
	CArray<CToolbarButton*,CToolbarButton*> m_buttons;

	int m_dragging;
	BOOL m_bInsideRect;
	CRect m_rect;

DECLARE_REGISTRY_RESOURCEID(IDR_UITOOLBARBUTTONS)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUIToolbarButtons)
	COM_INTERFACE_ENTRY(IUIToolbarButtons)
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

BEGIN_PROP_MAP(CUIToolbarButtons)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BorderVisible", DISPID_BORDERVISIBLE, CLSID_NULL)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	PROP_ENTRY("Picture", DISPID_PICTURE, CLSID_StockPicturePage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CUIToolbarButtons)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IUIToolbarButtonsEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CUIToolbarButtons)
	CHAIN_MSG_MAP(CComControl<CUIToolbarButtons>)
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

	HRESULT OnDraw(ATL_DRAWINFO& di);

	BOOL m_bBorderVisible;
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
	CComPtr<IPictureDisp> m_pPicture;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IUIToolbarButtons,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// IUIToolbarButtons
public:
	STDMETHOD(AddButton)(/*[in]*/ long id, /*[in]*/ long bmIndex);
	STDMETHOD(SetBitmap)(/*[in]*/ HBITMAP hBitmap, /*[in]*/ long nWidth);
};

#endif //__UITOOLBARBUTTONS_H_
