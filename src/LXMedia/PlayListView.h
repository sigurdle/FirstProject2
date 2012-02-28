// PlayListView.h : Declaration of the CPlayListView

#ifndef __PLAYLISTVIEW_H_
#define __PLAYLISTVIEW_H_

#include "resource.h"       // main symbols

class CEPlayListDocument;

/////////////////////////////////////////////////////////////////////////////
// CPlayListView
class ATL_NO_VTABLE CPlayListView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CPlayListView, &CLSID_PlayListView>,
	public IConnectionPointContainerImpl<CPlayListView>,
//	public IDispatchImpl<IPlayListView, &IID_IPlayListView, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CPlayListView, CWindowImpl<CPlayListView> >,

	public IUITreeControlSite,

	public IDispEventImpl<4, CPlayListView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<3, CPlayListView, &DIID__IEXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>,
//	public IDispEventImpl<5, CPlayListView, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>,
	public ProcessTargetCommands
//	public IDropTarget
{
public:
//	DECLARE_WND_CLASS(NULL)

	CPlayListView()
	{
		m_pDocument = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CAxWindow	m_axtreeCtl;
	CComPtr<IUITreeControl> m_treeCtl;

	CEPlayListDocument* m_pDocument;

//	HFONT m_hFont;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPlayListView)
//	COM_INTERFACE_ENTRY(IPlayListView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY2(IDispatch, IPlayListView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)

	COM_INTERFACE_ENTRY(ICommandTarget)

//	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPlayListView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CPlayListView)
  // SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
 //  SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(3, DIID__IWebXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

/*
	HRESULT __stdcall OnHorzScroll(long code, long pos);
	HRESULT __stdcall OnVertScroll(long code, long pos);
	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);
*/

BEGIN_MSG_MAP(CPlayListView)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);

END_MSG_MAP()

//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
/*
//	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

DECLARE_CMD_MAP(CPlayListView)

	LRESULT OnEditFrame(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IDropTarget
/*
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
*/
// IPlayListView
public:
//	STDMETHOD(get_document)(/*[out, retval]*/ IWebXMLDocument* *pVal);
//	STDMETHOD(put_document)(/*[in]*/ IWebXMLDocument* newVal);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"PlayList");
		return S_OK;
	}
// IUITreeControlSite
	STDMETHOD(GetItemText)(ULONG itemdata, LONG column, BSTR * pVal);

// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

#endif //__PLAYLISTVIEW_H_
