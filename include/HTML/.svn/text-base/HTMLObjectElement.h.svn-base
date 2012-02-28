#ifndef HTMLObjectElement_h
#define HTMLObjectElement_h

#if 0

//#include "resource.h"       // main symbols

#include "LHTMLElementImpl.h"
//#include "LElementEditASImpl.h"
#include "LElementEditVALImpl.h"
#include "LElementCSSInlineStyleImpl.h"

class COleObjectSite : 
	public CComObjectRootEx<CComMultiThreadModel>,
//	public CComObjectRootEx<CComSingleThreadModel>,
	public IServiceProviderImpl<COleObjectSite>,
//	public IDispatchImpl<IDispatch, &IID_IDispatch>,
	public IOleClientSite,// &IID_IOleClientSite>,
	//public IOleWindow,// &IID_IOleWindow>,
//	public IOleInPlaceSite, // IOleWindow// &IID_IOleInPlaceSite>,
//	public IOleInPlaceSiteEx, // IOleInPlaceSite// &IID_IOleInPlaceSiteEx>,
	public IOleInPlaceSiteWindowless, // IOleInPlaceSiteEx, IOleInPlaceSite  // &IID_IOleInPlaceSiteWindowless>,
//	public IDispatchImpl<IPropertyBag, &IID_IPropertyBag>,
//	public IDispatchImpl<IErrorLog, &IID_IErrorLog>,
//	public IDispatchImpl<IPersistMoniker, &IID_IPersistMoniker>
	public /*IDispatchImpl<*/IAdviseSink//, &IID_IAdviseSink>
{
public:
// state
	unsigned long m_bInPlaceActive:1;
	unsigned long m_bUIActive:1;
	unsigned long m_bMDIApp:1;
	unsigned long m_bWindowless:1;
	unsigned long m_bCapture:1;
	unsigned long m_bHaveFocus:1;
	unsigned long m_bReleaseAll:1;
	unsigned long m_bLocked:1;

// Ambient property storage
	unsigned long m_bCanWindowlessActivate:1;
	unsigned long m_bUserMode:1;
	unsigned long m_bDisplayAsDefault:1;
	unsigned long m_bMessageReflect:1;
	unsigned long m_bSubclassed:1;
	unsigned long m_bAllowContextMenu:1;
	unsigned long m_bAllowShowUI:1;

public:

	COleObjectSite()
	{
		m_pDocument = NULL;

		m_bInPlaceActive = FALSE;
		m_bWindowless = FALSE;
		m_bCanWindowlessActivate = TRUE;
		m_bUIActive = FALSE;
		m_bReleaseAll = FALSE;
		m_dwAdviseSink = 0xCDCDCDCD;

		m_hWndParent = NULL;
#if 0
		m_pWindow = NULL;
#endif
	}

	ILDOMDocument* m_pDocument;

	HWND m_hWndParent;
#if 0
	CHTMLWindow* m_pWindow;
#endif

	CLSID	m_clsid;

	CComPtr<IUnknown> m_spUnknown;
	CComPtr<IOleObject> m_spOleObject;

#if 0
	CComPtr<IOleInPlaceFrame> m_spInPlaceFrame;
	CComPtr<IOleInPlaceUIWindow> m_spInPlaceUIWindow;
#endif
	CComPtr<IViewObjectEx> m_spViewObject;
	CComPtr<IOleInPlaceObjectWindowless> m_spInPlaceObjectWindowless;
	CComPtr<IDispatch> m_spExternalDispatch;

	IID m_iidSink;
	DWORD m_dwViewObjectType;
	DWORD m_dwAdviseSink;

	DWORD m_dwOleObject;
	DWORD m_dwMiscStatus;
	SIZEL m_hmSize;
	SIZEL m_pxSize;
	RECT m_rcPos;
	RECT m_rcClip;

	HRESULT Connect(bool bInited, IStream* pStream);
	HRESULT ActivateAx(HWND hWndParent/*bool bInited, IStream* pStream*/);

	void ReleaseAll();

	void OnSize(RECT& rcpos, RECT& rcclip)
	{
		m_rcPos = rcpos;	// Remember it
		m_rcClip = rcclip;

	//	m_rcPos.right = m_rcPos.left + nWidth;
	//	m_rcPos.bottom = m_rcPos.top + nHeight;

		m_pxSize.cx = m_rcPos.right - m_rcPos.left;
		m_pxSize.cy = m_rcPos.bottom - m_rcPos.top;
		AtlPixelToHiMetric(&m_pxSize, &m_hmSize);

		if (m_spOleObject)
			m_spOleObject->SetExtent(DVASPECT_CONTENT, &m_hmSize);

		if (m_spInPlaceObjectWindowless)
			m_spInPlaceObjectWindowless->SetObjectRects(&m_rcPos, &m_rcClip);

		//	if (m_bWindowless)
	//		InvalidateRect(NULL, TRUE);
	}

BEGIN_COM_MAP(COleObjectSite)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSite, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSiteEx, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY_BREAK(IAdviseSink)
	//COM_INTERFACE_ENTRY_BREAK(IOleItemContainer)

	COM_INTERFACE_ENTRY(IServiceProvider)
END_COM_MAP()

BEGIN_SERVICE_MAP(COleObjectSite)
//	SERVICE_ENTRY(SID_SHlinkFrame)

	ATLASSERT(0);
#if 0
	if (::InlineIsEqualGUID(guidService, SID_SBindHost))
			return m_pDocument->QueryInterface(riid, ppvObject);
#endif
	/*
	if (::InlineIsEqualGUID(guidService, SID_IBindHost))
			return QueryInterface(riid, ppvObject);
*/
END_SERVICE_MAP()

public:
// IOleClientSite
	STDMETHOD(SaveObject)()
	  {
	MessageBox(NULL, "", "", MB_OK);
		return S_OK;
	  }
	  
	STDMETHOD(GetMoniker)( 
		  /* [in] */ DWORD dwAssign,
		  /* [in] */ DWORD dwWhichMoniker,
		  /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
	  {
	MessageBox(NULL, "", "", MB_OK);
		  return S_OK;
	  }
	  
	STDMETHOD(GetContainer)( 
		  /* [out] */ IOleContainer __RPC_FAR *__RPC_FAR *ppContainer)
	  {
		  MessageBox(NULL, "GetContainer", "", MB_OK);
		  return S_OK;
	  }
	  
	STDMETHOD(ShowObject)()
	  {
	// TODO
		  return S_OK;
	  }
	  
	STDMETHOD(OnShowWindow)( 
		  /* [in] */ BOOL fShow)
	  {
		// TODO ??
			//MessageBox(NULL, "", "", MB_OK);
		  return S_OK;
	  }
	  
	STDMETHOD(RequestNewObjectLayout)()
	  {
	MessageBox(NULL, "", "", MB_OK);
		  return S_OK;
	  }

// IAdviseSink
	STDMETHOD_(void, OnDataChange)(FORMATETC* /*pFormatetc*/, STGMEDIUM* /*pStgmed*/)
	{
	MessageBox(NULL, "", "", MB_OK);
	}
	STDMETHOD_(void, OnViewChange)(DWORD /*dwAspect*/, LONG /*lindex*/)
	{
	MessageBox(NULL, "", "", MB_OK);
	}
	STDMETHOD_(void, OnRename)(IMoniker* /*pmk*/)
	{
	MessageBox(NULL, "", "", MB_OK);
	}
	STDMETHOD_(void, OnSave)()
	{
	MessageBox(NULL, "", "", MB_OK);
	}
	STDMETHOD_(void, OnClose)()
	{
	MessageBox(NULL, "", "", MB_OK);
	}

// IOleWindow
	STDMETHOD(GetWindow)(/* [out] */ HWND __RPC_FAR *phwnd);
	STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);

// IOleInPlaceSite
	STDMETHOD(CanInPlaceActivate)();
   STDMETHOD(OnInPlaceActivate)();
	STDMETHOD(OnUIActivate)();
	STDMETHOD(GetWindowContext)( 
            /* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame,
            /* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc,
            /* [out] */ LPRECT lprcPosRect,
            /* [out] */ LPRECT lprcClipRect,
            /* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo);
	STDMETHOD(Scroll)(/* [in] */ SIZE scrollExtant);
	STDMETHOD(OnUIDeactivate)(/* [in] */ BOOL fUndoable);
	STDMETHOD(OnInPlaceDeactivate)();
	STDMETHOD(DiscardUndoState)();
	STDMETHOD(DeactivateAndUndo)();
	STDMETHOD(OnPosRectChange)(/* [in] */ LPCRECT lprcPosRect);

// IOleInPlaceSiteEx

	STDMETHOD(OnInPlaceActivateEx)(BOOL* pfNoRedraw, DWORD dwFlags);
	STDMETHOD(OnInPlaceDeactivateEx)(BOOL fNoRedraw);
	STDMETHOD(RequestUIActivate)();
 
// IOleInPlaceSiteWindowless

	STDMETHOD(CanWindowlessActivate)();
	STDMETHOD(GetCapture)();
	STDMETHOD(SetCapture)(BOOL fCapture);
	STDMETHOD(GetFocus)();
	STDMETHOD(SetFocus)(BOOL /*fFocus*/);
	STDMETHOD(GetDC)(LPCRECT /*pRect*/, DWORD /*grfFlags*/, HDC* phDC);
	STDMETHOD(ReleaseDC)(HDC hDC);
	STDMETHOD(InvalidateRect)(LPCRECT pRect, BOOL fErase);
	STDMETHOD(InvalidateRgn)(HRGN hRGN, BOOL fErase);
	STDMETHOD(ScrollRect)(INT /*dx*/, INT /*dy*/, LPCRECT /*pRectScroll*/, LPCRECT /*pRectClip*/);
	STDMETHOD(AdjustRect)(LPRECT /*prc*/);
	STDMETHOD(OnDefWindowMessage)(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT* plResult);
};

namespace LHTML
{

class HTMLEXT HTMLObjectElement : 
//	public CComCoClass<HTMLObjectElement, &CLSID_LHTMLObjectElement>,

	public HTMLElement,
	public CLElementCSSInlineStyleImpl<HTMLObjectElement>,
//	public CLElementEditASImpl<HTMLObjectElement>,
	public CLElementEditVALImpl<HTMLObjectElement>,

	public ILElementCSSInlineStyle,
	public ILElementEditVAL,	// ILNodeEditVAL

	public IPropertyBag,
	public IErrorLog,

	public CNotifyGetImpl<HTMLObjectElement>,
	public CNotifySendImpl<HTMLObjectElement>
{
public:
	typedef HTMLObjectElement T;

	CTOR HTMLObjectElement()
	{
		m_pOleObjectSite = NULL;
		m_contentDocument = NULL;
	}

	~HTMLObjectElement()
	{
	}


	void FinalRelease()
	{
//		m_contentDocument.Release();

	}

	CComObject<COleObjectSite>* m_pOleObjectSite;
	Document* m_contentDocument;

	HRESULT LoadComObject(REFCLSID clsid);
	HRESULT Load();

	STDMETHOD(get__object)(/*[out, retval]*/ IUnknown* *pVal);
	sysstring get_data();
	void put_data(const sysstring& newVal);
	sysstring get_type();
	void put_type(const sysstring& newVal);
	STDMETHOD(get_declare)(/*[out, retval]*/ bool *pVal);
	STDMETHOD(put_declare)(/*[in]*/ bool newVal);
	STDMETHOD(get_contentDocument)(/*[out, retval]*/ Document* *pVal);

// IPropertyBag
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Read( 
		/* [in] */ LPCOLESTR pszPropName,
		/* [out][in] */ VARIANT *pVar,
		/* [in] */ IErrorLog *pErrorLog);

	virtual HRESULT STDMETHODCALLTYPE Write( 
		/* [in] */ LPCOLESTR pszPropName,
		/* [in] */ VARIANT *pVar);

// IErrorLog
	virtual HRESULT STDMETHODCALLTYPE AddError( 
		/* [in] */ LPCOLESTR pszPropName,
		/* [in] */ EXCEPINFO *pExcepInfo);

};

}	// Web

#endif

#endif // HTMLObjectElement_h
