// MediaClipView.h : Declaration of the CMediaClipView

#ifndef __MEDIACLIPVIEW_H_
#define __MEDIACLIPVIEW_H_

#include "resource.h"       // main symbols

class CMediaStream;
class CEMediaClipDocument;

/////////////////////////////////////////////////////////////////////////////
// CMediaClipView
class ATL_NO_VTABLE CMediaClipView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CMediaClipView, &CLSID_MediaClipView>,
	public IConnectionPointContainerImpl<CMediaClipView>,
//	public IDispatchImpl<IMediaClipView, &IID_IMediaClipView, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CMediaClipView, CWindowImpl<CMediaClipView> >,

	public IDispEventImpl<1, CMediaClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CMediaClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<3, CMediaClipView, &DIID__IEXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>,
//	public IDispEventImpl<5, CMediaClipView, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>,

//	public IEViewGroup,
	
	public ProcessTargetCommands
//	public IDropTarget
{
public:
//	DECLARE_WND_CLASS(NULL)

	CMediaClipView()
	{
		m_hFont = NULL;

		m_dragging = 0;

	//	m_pDocument = NULL;
		m_pStream = NULL;
	}

	int FinalConstruct()
	{
		m_horz.CoCreateInstance(CLSID_UIScrollBar);
		m_vert.CoCreateInstance(CLSID_UIScrollBar);

		return S_OK;
	}

	void FinalRelease()
	{
	}

	CComQIPtr<IUIScrollBar>	m_horz;
	CComQIPtr<IUIScrollBar>	m_vert;

	CMediaStream* m_pStream;

	HFONT m_hFont;

	Gdiplus::Rect m_videoRect;
	CRect m_bottomRect;
	CRect m_sliderRect;

	long m_dragging;
	CPoint m_oldpt;

	void DrawSecondTicks(HDC hDC);

	void OnSize();

	void OnMouseMove(CPoint point, UINT nFlags);

	HRESULT GetBitmap(Gdiplus::Bitmap** pVal);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMediaClipView)
//	COM_INTERFACE_ENTRY(IMediaClipView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY2(IDispatch, IMediaClipView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)

	COM_INTERFACE_ENTRY(ICommandTarget)

//	COM_INTERFACE_ENTRY(IEViewGroup)

//	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CMediaClipView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CMediaClipView)
  // SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
 //  SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(3, DIID__IWebXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

/*
	HRESULT __stdcall OnHorzScroll(long code, long pos);
	HRESULT __stdcall OnVertScroll(long code, long pos);
	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);
*/

BEGIN_MSG_MAP(CMediaClipView)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);

END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
/*
//	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

DECLARE_CMD_MAP(CMediaClipView)

	LRESULT OnEditFrame(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IDropTarget
/*
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
*/
// IMediaClipView
public:

// IEViewGroup
	STDMETHOD(OnActivate)(BOOL bActivate)
	{
		return S_OK;
	}

//	STDMETHOD(get_document)(/*[out, retval]*/ IWebXMLDocument* *pVal);
//	STDMETHOD(put_document)(/*[in]*/ IWebXMLDocument* newVal);
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Clip");
		return S_OK;
	}
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

#endif //__MEDIACLIPVIEW_H_
