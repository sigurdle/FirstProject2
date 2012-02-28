#include "resource.h"       // main symbols

//class CPDDocument;
class CPDDocumentView;

#include "..\UIT\UIT.h"

extern bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

class CSpreadsWndBase
{
public:
	int m_iconSize;

	CComObject<CPDDocumentView>* m_view;

	CRect m_areaRect;
	CAxWindow m_axvert;
	CComQIPtr<IUIScrollBar> m_vert;

	long m_selectedPageIndex;

	CSpreadsWndBase()
	{
		m_view = NULL;
		m_iconSize = 1;
		m_selectedPageIndex = -1;
	}

};

class ATL_NO_VTABLE CSpreadsWnd : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CWindowImpl<CSpreadsWnd>,
	public IDropTarget,
	public CSpreadsWndBase,
	public IDispEventImpl<1, CSpreadsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CSpreadsWnd, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>
{
public:
	CSpreadsWnd()
	{
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
		if (FAILED(hr)) return hr;
		m_vert->put_direction(1);

		return S_OK;
	}

	void OnSize();

BEGIN_COM_MAP(CSpreadsWnd)
	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

BEGIN_SINK_MAP(CSpreadsWnd)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(3, DIID__IPDDocumentEvents, /*dispid*/2, OnPageSelectedChanged)
END_SINK_MAP()

	HRESULT __stdcall OnVertScroll(long code, long pos);
	void __stdcall OnPageSelectedChanged(IPDPage* page, VARIANT_BOOL selected);

BEGIN_MSG_MAP(CSpreadsWnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
};

///

class ATL_NO_VTABLE CMastersWnd : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CWindowImpl<CMastersWnd>,
	public IUnknown,
	public CSpreadsWndBase,
	public IDispEventImpl<1, CMastersWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CMastersWnd, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>
{
public:
	CMastersWnd()
	{
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
		if (FAILED(hr)) return hr;
		m_vert->put_direction(1);

		return S_OK;
	}

	void OnSize();

BEGIN_COM_MAP(CMastersWnd)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()

BEGIN_SINK_MAP(CMastersWnd)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(3, DIID__IPDDocumentEvents, /*dispid*/2, OnPageSelectedChanged)
END_SINK_MAP()

	HRESULT __stdcall OnVertScroll(long code, long pos);
	void __stdcall OnPageSelectedChanged(IPDPage* page, VARIANT_BOOL selected);

BEGIN_MSG_MAP(CMastersWnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

/////////////////////////////////////////////////////////////////////////////
// CPagesDlg
class ATL_NO_VTABLE CPagesDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPagesDlg, &CLSID_PagesDlg>,
//	public IConnectionPointContainerImpl<CPagesDlg>,
	public IDispatchImpl<IPagesDlg, &IID_IPagesDlg, &LIBID_PAGEDESIGNERLib>,

	public CUIDialogImpl<CPagesDlg, CWindowImpl<CPagesDlg> >,
//	public CWindowImpl<CPagesDlg>,
	public CUIEventHandlerImpl,
	public ProcessTargetCommands

//	public IDispEventImpl<1, CPagesDlg, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>
//	public IDispEventImpl<2, CPagesDlg, &DIID__IESvgDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>,
//	public IDispEventImpl<3, CPagesDlg, &DIID__IWebEditControlEvents, &LIBID_WEBEDITORLib, 1, 0>
{
public:
	CPagesDlg()
	{
		m_mastersWnd = NULL;
		m_spreadsWnd = NULL;
		m_view = NULL;

		m_splity = 60;
		m_dragging = 0;

		m_windowOnTop = 1;
		m_resize = 2;
	}

	int FinalConstruct();

	void FinalRelease()
	{                                                     
	}

	CComObject<CPDDocumentView>* m_view;

	CComObject<CMastersWnd>* m_mastersWnd;
	CComObject<CSpreadsWnd>* m_spreadsWnd;

	int m_splity;
	int m_dragging;

	int m_resize;
	int m_windowOnTop;

	CRect m_oldClientRect;

	void OnSize();

DECLARE_REGISTRY_RESOURCEID(IDR_PAGESDLG)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPagesDlg)
	COM_INTERFACE_ENTRY(IPagesDlg)
	COM_INTERFACE_ENTRY2(IDispatch, IPagesDlg)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPagesDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CPagesDlg)
   //SINK_ENTRY_EX(1, DIID__IUIManagerEvents, /*dispid*/1, OnActivatedObject)
	//SINK_ENTRY_EX(1, DIID__IUIManagerEvents, /*dispid*/2, OnDeactivatedObject)
//   SINK_ENTRY_EX(2, DIID__IESvgDocumentEvents, /*dispid*/1, OnDOMEvent)
//   SINK_ENTRY_EX(3, DIID__IWebEditControlEvents, /*dispid*/1, OnChangeViewBox)
END_SINK_MAP()

//	HRESULT __stdcall OnActivatedObject(IUnknown* object);
//	HRESULT __stdcall OnDeactivatedObject(IUnknown* object);
//	HRESULT __stdcall OnDOMEvent(IDOMEvent* evt);

	HRESULT __stdcall OnChangeViewBox();

BEGIN_MSG_MAP(CPagesDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CPagesDlg)

	LRESULT OnInsertPages(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnInsertPagesUpdate(long iid, IUICmdUpdate * pCmdUI);
	LRESULT OnSectionOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnSectionOptionsUpdate(long iid, IUICmdUpdate * pCmdUI);
	LRESULT OnKeepSpreadTogether(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnKeepSpreadTogetherUpdate(long iid, IUICmdUpdate * pCmdUI);
	LRESULT OnPaletteOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IPagesDlg
public:

// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Pages");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};
