// LHTMLDocumentView.h : Declaration of the CLHTMLDocumentView

#ifndef __LHTMLDOCUMENTVIEW_H_
#define __LHTMLDOCUMENTVIEW_H_

#if 0

#include "resource.h"       // main symbols

//class CHTMLWindow;
#include "LHTMLWindow.h"

class CLHTMLActiveDocument;

//#include "SafeWinImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CLHTMLDocumentView
class ATL_NO_VTABLE CLHTMLDocumentView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IConnectionPointContainerImpl<CLHTMLDocumentView>,
//	public IDispatchImpl<IMMSXHTMLDocumentView, &IID_IMMSXHTMLDocumentView, &LIBID_SVGLib>,

	public ILHTMLActiveView,

	public IOleDocumentView,
	public IOleInPlaceObject, // IOleWindow

	public IPrint,
	public IOleCommandTarget,

	public IDropTarget,

	public IViewObject,

	public CHTMLWindowSite,

	public CWindowImpl<CLHTMLDocumentView>
//	public CWindowImplSafe<CLHTMLDocumentView, CWindow, CControlWinTraits>
{
public:
	CLHTMLDocumentView();
	~CLHTMLDocumentView();

	void FinalRelease();

	VARIANT_BOOL m_framesDesign;

	CLHTMLActiveDocument* m_pDocument;
	CComPtr<IOleInPlaceSite> m_spInPlaceSite;

	CRect m_rect;

//	CActiveXFrame* m_oleFrame;

	CComPtr<ILPresentation> m_view;
	CComObject<CLHTMLWindow2>* m_pWindow;

//	CArray<IHTMLEditorSite*,IHTMLEditorSite*> m_editors;

//	bool m_bAlt;

//	int m_dragging;
//	CHTMFrame* m_pSizeFrame;
	//CHTMFrameNode* m_pSizeFrame;

	HRESULT Init(CLHTMLActiveDocument* pDocument, IOleInPlaceSite* spInPlaceSite);

	void OnSize();

//
	CComPtr<IHlink> m_hlink;
	DWORD m_grfHLNF;
	CComPtr<IBindCtx> m_bc;
	CComPtr<IBindStatusCallback> m_bsc;

	virtual HRESULT OnLink(BSTR href, BSTR target);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLHTMLDocumentView)
	COM_INTERFACE_ENTRY(ILHTMLActiveView)
//	COM_INTERFACE_ENTRY(IMMSXHTMLDocumentView)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(IOleDocumentView)
	COM_INTERFACE_ENTRY(IOleWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY(IPrint)
	COM_INTERFACE_ENTRY(IOleCommandTarget)

	COM_INTERFACE_ENTRY(IViewObject)

	COM_INTERFACE_ENTRY(IDropTarget)

END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLHTMLDocumentView)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CLHTMLDocumentView)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)

	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
	MESSAGE_HANDLER(WM_SYSKEYDOWN, OnSysKeyDown)
	MESSAGE_HANDLER(WM_SYSKEYUP, OnSysKeyUp)
	MESSAGE_HANDLER(WM_CHAR, OnChar)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
//	MESSAGE_HANDLER(WM_USER+1024, OnAdvancePlay)

//	CHAIN_MSG_MAP(CComControl<CHTMLControl>)
//	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

//	LRESULT OnAdvancePlay(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ILHTMLActiveView
public:
	STDMETHOD(GetHTMLWindow)(/*[out,retval]*/ ILHTMLWindow* *pVal);
	STDMETHOD(get_framesDesign)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_framesDesign)(/*[in]*/ VARIANT_BOOL newVal);

// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);

// IOleDocumentView
	STDMETHOD(SetInPlaceSite)(IOleInPlaceSite __RPC_FAR *pIPSite);
	STDMETHOD(GetInPlaceSite)(IOleInPlaceSite __RPC_FAR *__RPC_FAR *ppIPSite);
	STDMETHOD(GetDocument)(IUnknown __RPC_FAR *__RPC_FAR *ppunk);
	STDMETHOD(SetRect)(LPRECT prcView);
	STDMETHOD(GetRect)(LPRECT prcView);
	STDMETHOD(SetRectComplex)(LPRECT prcView, LPRECT prcHScroll, LPRECT prcVScroll, LPRECT prcSizeBox);
	STDMETHOD(Show)(BOOL fShow);
	STDMETHOD(UIActivate)(BOOL fUIActivate);
	STDMETHOD(Open)(void);
	STDMETHOD(CloseView)(DWORD dwReserved);
	STDMETHOD(SaveViewState)(LPSTREAM pstm);
	STDMETHOD(ApplyViewState)(LPSTREAM pstm);
	STDMETHOD(Clone)(IOleInPlaceSite __RPC_FAR *pIPSiteNew, IOleDocumentView __RPC_FAR *__RPC_FAR *ppViewNew);

// IOleWindow
	STDMETHOD(GetWindow)(HWND __RPC_FAR *phwnd);
	STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);

// IOleInPlaceObject
	STDMETHOD(InPlaceDeactivate)(void);
	STDMETHOD(UIDeactivate)(void);
	STDMETHOD(SetObjectRects)(LPCRECT lprcPosRect, LPCRECT lprcClipRect);
	STDMETHOD(ReactivateAndUndo)(void);

// IPrint
	STDMETHOD(SetInitialPageNum)(LONG nFirstPage);
	STDMETHOD(GetPageInfo)(LONG __RPC_FAR *pnFirstPage, LONG __RPC_FAR *pcPages);
	STDMETHOD(Print)(DWORD grfFlags, DVTARGETDEVICE __RPC_FAR *__RPC_FAR *pptd, PAGESET __RPC_FAR *__RPC_FAR *ppPageSet, STGMEDIUM __RPC_FAR *pstgmOptions, IContinueCallback __RPC_FAR *pcallback, LONG nFirstPage, LONG __RPC_FAR *pcPagesPrinted, LONG __RPC_FAR *pnLastPage);

// IOleCommandTarget
	STDMETHOD(QueryStatus)(const GUID __RPC_FAR *pguidCmdGroup, ULONG cCmds, OLECMD __RPC_FAR prgCmds[  ], OLECMDTEXT __RPC_FAR *pCmdText);
	STDMETHOD(Exec)(const GUID __RPC_FAR *pguidCmdGroup, DWORD nCmdID, DWORD nCmdexecopt, VARIANT __RPC_FAR *pvaIn, VARIANT __RPC_FAR *pvaOut);

// IViewObject
     virtual /* [local] */ HRESULT STDMETHODCALLTYPE Draw( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ LONG lindex,
         /* [unique][in] */ void *pvAspect,
         /* [unique][in] */ DVTARGETDEVICE *ptd,
         /* [in] */ HDC hdcTargetDev,
         /* [in] */ HDC hdcDraw,
         /* [in] */ LPCRECTL lprcBounds,
         /* [unique][in] */ LPCRECTL lprcWBounds,
         /* [in] */ BOOL ( STDMETHODCALLTYPE *pfnContinue )( 
             ULONG_PTR dwContinue),
         /* [in] */ ULONG_PTR dwContinue);

     virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetColorSet( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ LONG lindex,
         /* [unique][in] */ void *pvAspect,
         /* [unique][in] */ DVTARGETDEVICE *ptd,
         /* [in] */ HDC hicTargetDev,
         /* [out] */ LOGPALETTE **ppColorSet)
	  {
		  return E_FAIL;
	  }

     virtual /* [local] */ HRESULT STDMETHODCALLTYPE Freeze( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ LONG lindex,
         /* [unique][in] */ void *pvAspect,
         /* [out] */ DWORD *pdwFreeze)
	  {
		  return E_FAIL;
	  }

     virtual HRESULT STDMETHODCALLTYPE Unfreeze( 
         /* [in] */ DWORD dwFreeze)
	  {
		  return E_FAIL;
	  }

     virtual HRESULT STDMETHODCALLTYPE SetAdvise( 
         /* [in] */ DWORD aspects,
         /* [in] */ DWORD advf,
         /* [unique][in] */ IAdviseSink *pAdvSink)
	  {
		  return E_FAIL;
	  }

     virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetAdvise( 
         /* [unique][out] */ DWORD *pAspects,
         /* [unique][out] */ DWORD *pAdvf,
         /* [out] */ IAdviseSink **ppAdvSink)
	  {
		  return E_FAIL;
	  }

};
#endif

#endif //__LHTMLDOCUMENTVIEW_H_
