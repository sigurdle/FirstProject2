// LHTMLActiveDocument.h : Declaration of the CLHTMLActiveDocument

#ifndef __LHTMLACTIVEDOCUMENT_H_
#define __LHTMLACTIVEDOCUMENT_H_

#include "resource.h"       // main symbols
#include "LHTMLCP.h"

#include "..\LXFramework\edoc.h"

class CLHTMLDocumentView;
class CLHTMLWindow2;
//class CHTMFrame;

#include <Hlink.h>

class CNamedItem
{
public:
	_bstr_t m_name;
	IDispatch* m_pDisp;
};

class ATL_NO_VTABLE CLDOMErrorHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILDOMErrorHandler
{
public:

BEGIN_COM_MAP(CLDOMErrorHandler)
	COM_INTERFACE_ENTRY(ILDOMErrorHandler)
END_COM_MAP()

#if 0
	STDMETHOD(warn)( 
            /* [in] */ ILDOMLocator __RPC_FAR *where,
            /* [in] */ BSTR how,
            /* [in] */ BSTR why);
	STDMETHOD(fatalError)( 
            /* [in] */ ILDOMLocator __RPC_FAR *where,
            /* [in] */ BSTR how,
            /* [in] */ BSTR why);
	STDMETHOD(error)(
            /* [in] */ ILDOMLocator __RPC_FAR *where,
            /* [in] */ BSTR how,
            /* [in] */ BSTR why);
#endif
	STDMETHOD(handleError)(ILDOMError* pError, VARIANT_BOOL* pVal);
};

class CLHTMLActiveDocument;

class CCommands
{
public:
	CCommands()
	{
		m_pActiveDocument = NULL;
	}

	CLHTMLActiveDocument* m_pActiveDocument;

	void OnPurchase();

BEGIN_MSG_MAP(CCommands)
	COMMAND_ID_HANDLER(ID_SVG_ZOOMIN, OnZoomIn)
	COMMAND_ID_HANDLER(ID_SVG_ZOOMOUT, OnZoomOut)
	COMMAND_ID_HANDLER(ID_SVG_ORIGINALVIEW, OnOriginalView)
	COMMAND_ID_HANDLER(ID_SVG_PLAY, OnPlay)
	COMMAND_ID_HANDLER(ID_SVG_VIEWSOURCE, OnViewSource)
	COMMAND_ID_HANDLER(ID_EDIT_COPY, OnEditCopy)
	COMMAND_ID_HANDLER(ID_SVG_SAVEAS, OnSaveAs)
	COMMAND_ID_HANDLER(ID_SVG_PREFERENCES, OnPreferences)
	COMMAND_ID_HANDLER(ID_SVG_HELP, OnHelp)
	COMMAND_ID_HANDLER(ID_SVG_ABOUT, OnAbout)
	COMMAND_ID_HANDLER(ID_SVG_PURCHASE, OnPurchase)
END_MSG_MAP()

	LRESULT OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnZoomIn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnZoomOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnOriginalView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewSource(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPreferences(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPurchase(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

template<class T> class CCommandsT :
	public CCommands
{
public:
};

/////////////////////////////////////////////////////////////////////////////
// CLHTMLActiveDocument
class ATL_NO_VTABLE CLHTMLActiveDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLHTMLActiveDocument, &CLSID_LHTMLActiveDocument>,

	public IDispatchImpl<ILHTMLActiveDocument, &IID_ILHTMLActiveDocument, &LIBID_LHTMLLib>,
	public IProvideClassInfo2Impl<&CLSID_LHTMLActiveDocument, &DIID__ILHTMLActiveDocumentEvents, &LIBID_LHTMLLib>,

//	public ILXAddin,
	public ILDOMEventListener,

	public ILElementBehavior,
	public ILHTMLPainter,

#if 0	// Removed this
	public CComControl<CLHTMLActiveDocument>,
	public IOleControlImpl<CLHTMLActiveDocument>,
	public IOleObjectImpl<CLHTMLActiveDocument>,
	public IOleInPlaceActiveObjectImpl<CLHTMLActiveDocument>,
	public IViewObjectExImpl<CLHTMLActiveDocument>,
	public IOleInPlaceObjectWindowlessImpl<CLHTMLActiveDocument>,
#endif

	public CMessageMap,

	public IObjectSafety,

	public ISupportErrorInfo,

#if 0
	public IOleDocument,
#endif
	public IPersistFile, // IPersist
//	public IPersistStream, // IPersist
//	public IPersistStreamInitImpl<CLHTMLActiveDocument>,
	public IPersistMoniker, // IPersist

#if 0
	public IPersistPropertyBagImpl<CLHTMLActiveDocument>,
#endif

#if 0
	public IHlinkTarget,
	public IHlinkSite,	// Not sure if that should be on this object
#endif

	public CCommandsT<CLHTMLActiveDocument>,

	public CProxy_ILHTMLActiveDocumentEvents< CLHTMLActiveDocument >,
	public IConnectionPointContainerImpl<CLHTMLActiveDocument>
{
public:
	CLHTMLActiveDocument();
	~CLHTMLActiveDocument();

	int FinalConstruct();
	void FinalRelease();

#if 0
	CComPtr<IOleClientSite> m_spClientSite;
#endif

	CArray<CNamedItem,CNamedItem&> m_namedItems;

	void OnSVGLoad(ILDOMElement* element);

	CContainedWindow m_cwnd;
	double m_frameRate;

	CComPtr<IOleDocumentSite>   m_spDocSite;

	CComObject<CLHTMLWindow2>* m_pWindow;	// When activated as control
#if 0
	CComObject<CLHTMLDocumentView>* m_view;	// TODO remove ?? since there can be more than one view
#endif
	CComPtr<ILPresentation> m_view;

	VARIANT	m_dialogArg;
	CComPtr<ILDOMDocument> m_document;
	CComPtr<ILDOMElement> m_element;

	CComPtr<ILDOMErrorHandler> m_errorHandler;

	CComPtr<IMoniker> m_curMoniker;
	CComBSTR m_friendlyName;
	CComBSTR m_fileName;

	DWORD m_dwRegHBC;
	CComPtr<IHlinkBrowseContext> m_pHBC;

	CComBSTR m_src;
	CComPtr<ITextData> m_textData;

	UINT m_nTimerID;
	DWORD m_threadID;
	HANDLE m_hThread;
	HANDLE m_hEvent;

	double m_currentAudioTime;	// TODO remove
	double m_currentVideoTime;	// TODO remove

#if 0
	CComPtr<IDirectSound8> m_ds8;
	CComQIPtr<IDirectSoundBuffer8, &IID_IDirectSoundBuffer8> m_dsBuffer8;
#endif
	LPSTR m_wavbuffer;	// TODO remove
	WAVEFORMATEX m_wf;	// TODO remove

	CRITICAL_SECTION m_paintCriticalSection;

	void RenderAllAudio(ILDOMElement* element, double tsf, double tlen, ULONG nSamples);

	void AdvancePlay();

	void UpdateAllViews();

	HRESULT StartPlay();
	HRESULT StopPlay();

	STDMETHOD(GotoLocation)(BSTR burl, VARIANT_BOOL *success);

	HRESULT GetHlinkFrame(IHlinkFrame* *pVal);
	HRESULT HaveBrowseContext();

//	HRESULT DoVerbInPlaceActivate(LPCRECT prcPosRect, HWND hwndParent);
	HRESULT OnPostVerbInPlaceActivate();

DECLARE_REGISTRY_RESOURCEID(IDR_LHTMLACTIVEDOCUMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLHTMLActiveDocument)
	COM_INTERFACE_ENTRY(ILHTMLActiveDocument)
	COM_INTERFACE_ENTRY(IDispatch)

//	COM_INTERFACE_ENTRY(ILXAddin)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
	COM_INTERFACE_ENTRY(ILElementBehavior)
	COM_INTERFACE_ENTRY(ILHTMLPainter)

//
//	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
//	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
//	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
//	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
//	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
//	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
//	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
//	COM_INTERFACE_ENTRY_IMPL(IOleControl)
//	COM_INTERFACE_ENTRY_IMPL(IOleObject)
//
//	COM_INTERFACE_ENTRY(IOleDocument)

	COM_INTERFACE_ENTRY2(IPersist, IPersistFile)
	COM_INTERFACE_ENTRY(IPersistFile)
//	COM_INTERFACE_ENTRY(IPersistStream)
//	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY(IPersistMoniker)
//	COM_INTERFACE_ENTRY_BREAK(IPersistStorage)

#if 0
	COM_INTERFACE_ENTRY(IPersistPropertyBag)

	COM_INTERFACE_ENTRY(IHlinkTarget)
	COM_INTERFACE_ENTRY(IHlinkSite)
#endif

	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(IObjectSafety)

/*
	COM_INTERFACE_ENTRY_BREAK(IMoniker)
	COM_INTERFACE_ENTRY_BREAK(IHlinkFrame)

	COM_INTERFACE_ENTRY_BREAK(IDataObject)
	COM_INTERFACE_ENTRY_BREAK(IOleWindow)
	COM_INTERFACE_ENTRY_BREAK(IOleInPlaceObject)
	COM_INTERFACE_ENTRY_BREAK(IOleInPlaceActiveObject)

	COM_INTERFACE_ENTRY_BREAK(IOleDocumentView)
	*/

END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLHTMLActiveDocument)
	CONNECTION_POINT_ENTRY(DIID__ILHTMLActiveDocumentEvents)
END_CONNECTION_POINT_MAP()

#if 0
BEGIN_PROPERTY_MAP(CLHTMLActiveDocument)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("src", 16/*DISPID_ACTIVEDOCUMENT_SRC*/, CLSID_NULL/*clsid*/)
END_PROPERTY_MAP()
#endif

BEGIN_MSG_MAP(CLHTMLActiveDocument)
#if 0
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
	MESSAGE_HANDLER(WM_SYSKEYDOWN, OnSysKeyDown)
	MESSAGE_HANDLER(WM_SYSKEYUP, OnSysKeyUp)
//	MESSAGE_HANDLER(WM_CHAR, OnChar)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
//	MESSAGE_HANDLER(WM_USER+1024, OnAdvancePlay)

	CHAIN_MSG_MAP(CCommands)
	CHAIN_MSG_MAP(CComControl<CLHTMLActiveDocument>)
	DEFAULT_REFLECTION_HANDLER()
#endif

	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_USER+100, OnTimer)
END_MSG_MAP()

#if 0
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
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
#endif
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

#if 0
// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)
#endif

//	CComPtr<ILXAddinSite> m_spAddinSite;

public:
#if 0
// ILXAddin
	STDMETHOD(GetSite)(ILXAddinSite* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_spAddinSite;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(SetSite)(ILXAddinSite* pSite)
	{
		m_spAddinSite = pSite;
		return S_OK;
	}
#endif

	CComPtr<ILXUIElement> m_inplaceElement;
	ILElementBehaviorSite* m_pBehaviorSite;

	STDMETHOD(Show)(ILXUIElement* element);

// ILDOMEventListener
	STDMETHOD(handleEvent)(ILDOMEvent* evt);

// ILElementBehavior
	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
	{
		m_pBehaviorSite = pBehaviorSite;
		return S_OK;
	}

	STDMETHODIMP Detach()
	{
		m_pBehaviorSite = NULL;
		return S_OK;
	}

// ILHTMLPainter
	STDMETHOD(Draw)(/*[in]*/ ILCanvas* canvas);
	STDMETHOD(SetCursor)(/*[in]*/ POINT pt);

// ILHTMLActiveDocument
	STDMETHOD(GetDocument)(/*[out,retval]*/ ILDOMDocument* *pVal);
	STDMETHOD(GetTextData)(/*[out,retval]*/ ITextData* *pVal);
	STDMETHOD(SetElement)(/*[in]*/ ILDOMElement* element);
	STDMETHOD(SetDocument)(ILDOMDocument *document);
	STDMETHOD(get_errorHandler)(/*[out, retval]*/ ILDOMErrorHandler* *pVal);
	STDMETHOD(put_errorHandler)(/*[in]*/ ILDOMErrorHandler* newVal);

	STDMETHOD(getSVGDocument)(/*[out,retval]*/ ILSVGDocument* *pVal);

	STDMETHOD(get_src)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_src)(/*[in]*/ BSTR newVal);

	STDMETHOD(getSrc)(/*[out,retval]*/ BSTR *pVal)
	{
		return get_src(pVal);
	}
	STDMETHOD(setSrc)(/*[in]*/ BSTR newVal)
	{
		return put_src(newVal);
	}

/////////////////////////////////////////////////////////////////
// Scripting
#if 0
// IActiveScriptSite
	STDMETHOD(GetLCID)(/* [out] */ LCID __RPC_FAR *plcid);
	STDMETHOD(GetItemInfo)(/* [in] */ LPCOLESTR pstrName, /* [in] */ DWORD dwReturnMask,/* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiunkItem,/* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppti);
	STDMETHOD(GetDocVersionString)(/* [out] */ BSTR __RPC_FAR *pbstrVersion);
	STDMETHOD(OnScriptTerminate)(/* [in] */ const VARIANT __RPC_FAR *pvarResult,/* [in] */ const EXCEPINFO __RPC_FAR *pexcepinfo);
	STDMETHOD(OnStateChange)(/* [in] */ SCRIPTSTATE ssScriptState);
	STDMETHOD(OnScriptError)(/* [in] */ IActiveScriptError __RPC_FAR *pscripterror);
	STDMETHOD(OnEnterScript)( void);
	STDMETHOD(OnLeaveScript)( void);

// IActiveScriptSiteWindow
	STDMETHOD(GetWindow)(/* [out] */ HWND __RPC_FAR *phwnd);
	STDMETHOD(EnableModeless)(/* [in] */ BOOL fEnable);
#endif

	//HRESULT IOleInPlaceObject_SetObjectRects(LPCRECT prcPos,LPCRECT prcClip);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

#if 0
// IOleDocument
	STDMETHOD(CreateView)(IOleInPlaceSite __RPC_FAR *pIPSite, IStream __RPC_FAR *pstm, DWORD dwReserved, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView);		
	STDMETHOD(GetDocMiscStatus)(DWORD __RPC_FAR *pdwStatus);
	STDMETHOD(EnumViews)(IEnumOleDocumentViews __RPC_FAR *__RPC_FAR *ppEnum, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView);
#endif

// IPersist
	STDMETHOD(GetClassID)(CLSID __RPC_FAR *pClassID)
	{
		if (pClassID == NULL) return E_POINTER;
		*pClassID = GetObjectCLSID();
		return S_OK;
	}

// IPersistFile/IPersistStream
	STDMETHOD(IsDirty)( void);

// IPersistFile
	STDMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode);
	STDMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember);
	STDMETHOD(SaveCompleted)(LPCOLESTR pszFileName);
	STDMETHOD(GetCurFile)(LPOLESTR __RPC_FAR *ppszFileName);
// IPersistStreamInit
	STDMETHOD(Load)(IStream *pStm);
	STDMETHOD(InitNew)()
	{
		ATLTRACE2(atlTraceCOM, 0, _T("IPersistStreamInitImpl::InitNew\n"));
		return S_OK;
	}

// IPersistMoniker
	STDMETHODIMP Load(/* [in] */ BOOL fFullyAvailable, /* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc, /* [in] */ DWORD grfMode);
	STDMETHODIMP Save(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pbc, /* [in] */ BOOL fRemember);
	STDMETHODIMP SaveCompleted(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc);
	STDMETHODIMP GetCurMoniker(/* [out] */ IMoniker **ppimkName);

#if 0
// IHlinkTarget
	STDMETHOD(SetBrowseContext)(IHlinkBrowseContext* pihlbc);
	STDMETHOD(GetBrowseContext)(IHlinkBrowseContext** ppihlbc);
	STDMETHOD(Navigate)(DWORD grfHLNF, LPCWSTR pwzJumpLocation);
	STDMETHOD(GetMoniker)(LPCWSTR pwzLocation, DWORD dwAssign, IMoniker** ppimkLocation);
	STDMETHOD(GetFriendlyName)(LPCWSTR pwzLocation, LPWSTR* ppwzFriendlyName);

// IHlinkSite
	STDMETHOD(QueryService)(DWORD dwSiteData, REFGUID guidService,
		REFIID riid, IUnknown __RPC_FAR *__RPC_FAR *ppiunk);     
	STDMETHOD(GetMoniker)(DWORD dwSiteData, DWORD dwAssign,
		DWORD dwWhich, IMoniker __RPC_FAR *__RPC_FAR *ppimk);     
	STDMETHOD(ReadyToNavigate)(DWORD dwSiteData, DWORD dwReserved); 
	STDMETHOD(OnNavigationComplete)(DWORD dwSiteData, DWORD dwreserved,
		HRESULT hrError, LPCWSTR pwzError);
#endif

// IObjectSafety
	virtual HRESULT __stdcall GetInterfaceSafetyOptions( 
            /* [in]  */ REFIID riid,
            /* [out] */ DWORD __RPC_FAR *pdwSupportedOptions,
            /* [out] */ DWORD __RPC_FAR *pdwEnabledOptions)
	{
		*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		*pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		return S_OK;
	}

	virtual HRESULT __stdcall SetInterfaceSafetyOptions( 
            /* [in] */ REFIID riid,
            /* [in] */ DWORD dwOptionSetMask,
            /* [in] */ DWORD dwEnabledOptions)
	{
		return S_OK;
	}

// IOleObject

	bool m_bDocObject;

	CComPtr<IDispatch> m_containerScriptDispatch;

#if 0
// Override SetClientSite
	HRESULT IOleObject_SetClientSite(IOleClientSite *pClientSite)
	{
		// If we currently have a document site pointer, release it.
		m_spDocSite.Release();
		m_bDocObject=false;

		if (pClientSite != NULL)
		{
			if (TRUE)
			{
				CComPtr<IOleContainer> pContainer = NULL;
				CComPtr<IHTMLDocument2> pDoc = NULL;

				pClientSite->GetContainer(&pContainer);
				if (pContainer != NULL)
				{
					pContainer->QueryInterface(IID_IHTMLDocument2, (void**)&pDoc );

					if (pDoc)
					{
						pDoc->get_Script(&m_containerScriptDispatch);
					}
				}

				/*
				CComPtr<IServiceProvider> sp;
				pClientSite->QueryInterface(IID_IServiceProvider,
			                    (void **)&sp);

				if (sp)
				{
					CComPtr<IWebBrowserApp> app;
					sp->QueryService(SID_SWebBrowserApp, IID_IWebBrowserApp,
                        (void **)&app));

					if (app)
					{
					}
				}
				*/
			}

			pClientSite->QueryInterface(&m_spDocSite);
			if (m_spDocSite != NULL)
				m_bDocObject = true;
		}
		return CComControlBase::IOleObject_SetClientSite(pClientSite);
	}

     virtual HRESULT STDMETHODCALLTYPE GetClientSite(
         /* [out] */ IOleClientSite __RPC_FAR *__RPC_FAR *ppClientSite)
	  {
		  return CComControlBase::IOleObject_GetClientSite(ppClientSite);
	  }
#endif

     virtual HRESULT STDMETHODCALLTYPE SetMoniker( 
         /* [in] */ DWORD dwWhichMoniker,
         /* [unique][in] */ IMoniker __RPC_FAR *pmk);
     
#if 0
     virtual HRESULT STDMETHODCALLTYPE InitFromData( 
         /* [unique][in] */ IDataObject __RPC_FAR *pDataObject,
         /* [in] */ BOOL fCreation,
         /* [in] */ DWORD dwReserved)
	  {
#ifdef _DEBUG
		  ::MessageBox(NULL, "InitFromData()", "", MB_OK);
#endif
		  return IOleObjectImpl<CLHTMLActiveDocument>::InitFromData(pDataObject, fCreation, dwReserved);
	  }

     STDMETHOD(DoVerb)( 
         /* [in] */ LONG iVerb,
         /* [unique][in] */ LPMSG lpmsg,
         /* [unique][in] */ IOleClientSite __RPC_FAR *pActiveSite,
         /* [in] */ LONG lindex,
         /* [in] */ HWND hwndParent,
         /* [unique][in] */ LPCRECT lprcPosRect);


	HRESULT OnDraw(ATL_DRAWINFO& di);
#endif
};

#endif //__LHTMLACTIVEDOCUMENT_H_
