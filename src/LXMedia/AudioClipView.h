// AudioClipView.h : Declaration of the CAudioClipView

#ifndef __AUDIOCLIPVIEW_H_
#define __AUDIOCLIPVIEW_H_

#include "resource.h"       // main symbols

class CMediaStream;
class CEMediaClipDocument;

/////////////////////////////////////////////////////////////////////////////
// CAudioClipView
class ATL_NO_VTABLE CAudioClipView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CAudioClipView, &CLSID_AudioClipView>,
	public IConnectionPointContainerImpl<CAudioClipView>,
//	public IDispatchImpl<IAudioClipView, &IID_IAudioClipView, &LIBID_LXFrameworkLib>,

	public CUIDialogImpl<CAudioClipView, CWindowImpl<CAudioClipView> >,

	public IDispEventImpl<1, CAudioClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<2, CAudioClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<3, CAudioClipView, &DIID__IEXMLDocumentEvents, &LIBID_LXFrameworkLib, 1, 0>,
//	public IDispEventImpl<5, CAudioClipView, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>,

//	public IEViewGroup,

	public ProcessTargetCommands
//	public IDropTarget
{
public:
//	DECLARE_WND_CLASS(NULL)

	CAudioClipView()
	{
		m_hFont = NULL;

		m_pStream = NULL;
	//	m_pDocument = NULL;

		m_dragging = 0;
		m_bViewAll = TRUE;

		m_markStart = 0;
		m_markEnd = 0;

		m_bPlayMarker = false;
	}

	int FinalConstruct()
	{
		m_horz.CoCreateInstance(CLSID_UIScrollBar);
//		m_vert.CoCreateInstance(CLSID_UIScrollBar);

		return S_OK;
	}

	void FinalRelease()
	{
	}

//	CComPtr<IEViewGroupSite> m_spViewGroupSite;

//	CComPtr<IEXMLViewGroup> m_viewGroup;
//	CComQIPtr<IEXMLDocument> m_document;

	CAxWindow m_axhorz;
	CComPtr<IUIScrollBar>	m_horz;
//	CComQIPtr<IUIScrollBar>	m_vert;

	//CEMediaClipDocument* m_pDocument;
	CMediaStream* m_pStream;

	HFONT m_hFont;

//	Gdiplus::Rect m_videoRect;
//	CRect m_bottomRect;
//	CRect m_sliderRect;

	CRect	m_waveRect;
	LONGLONG	m_totalXPels;
	LONGLONG	m_waveXPels;
	BOOL m_bViewAll;

	double m_startSample;

	double m_markStart;
	double m_markEnd;

	long m_dragging;
	CPoint m_oldpt;

	void DrawSecondTicks(HDC hDC);

	void OnSize();

	void OnMouseMove(UINT nFlags, CPoint point);

	void SetMarkStart(double mark) { m_markStart = mark; }
	void SetMarkEnd(double mark) { m_markEnd = mark; }
	double GetMarkStart() { return m_markStart; }
	double GetMarkEnd() { return m_markEnd; }

	void DrawWaveSelection(HDC hDC);

	bool m_bPlayMarker;
	//int m_playMarkerX;
	double m_playMarker;

	void OnStartPlay();
	void OnPlaying();
	void OnStopPlay();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAudioClipView)
//	COM_INTERFACE_ENTRY(IAudioClipView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY2(IDispatch, IAudioClipView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)

	COM_INTERFACE_ENTRY(ICommandTarget)

//	COM_INTERFACE_ENTRY(IEViewGroup)

//	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAudioClipView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CAudioClipView)
	SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
 //  SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(3, DIID__IWebXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

	void __stdcall OnHorzScroll(long code, long pos);
//	void __stdcall OnVertScroll(long code, long pos);
//	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);


BEGIN_MSG_MAP(CAudioClipView)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CAudioClipView)

	LRESULT OnEditMute(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewSelection(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewZoomIn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewZoomOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewZoom11(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IDropTarget
/*
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
*/
// IAudioClipView
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

#endif //__AUDIOCLIPVIEW_H_
