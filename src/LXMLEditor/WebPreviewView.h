#include "resource.h"       // main symbols

class CWebXMLViewGroup;

/////////////////////////////////////////////////////////////////////////////
// CSiteFilesView
class ATL_NO_VTABLE CWebPreviewView : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CWebPreviewView, &CLSID_WebPreviewView>,
	public IConnectionPointContainerImpl<CWebPreviewView>,
	public IDispatchImpl<IWebPreviewView, &IID_IWebPreviewView, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CWebPreviewView, CWindowImpl<CWebPreviewView> >,

	public IOleDocumentSite,
	public IOleClientSite,
	public IOleInPlaceSite,	// IOleWindow
	public IAdviseSink,
	public IOleInPlaceUIWindow, // IOleWindow

	public IXMLDocumentInMemoryProvider
{
public:
	CWebPreviewView()
	{
		m_modifiedSinceLast = -1;
	}

	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
	}

	long m_modifiedSinceLast;

	CComQIPtr<IEXMLDocument> m_document;
	CWebXMLViewGroup* m_viewGroup;

// Container
	CComPtr<IUnknown> m_spUnknown;
	CComQIPtr<IOleObject> m_spOleObject;
	CComQIPtr<IOleDocument> m_spOleDocument;
	CComQIPtr<IOleInPlaceObject> m_pIOleIPObject;

	CComQIPtr<IOleDocumentView> m_pIOleDocView;

	DWORD m_dwAdvise;

	void OnSize();

//DECLARE_REGISTRY_RESOURCEID(IDR_WEBPREVIEWVIEW)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWebPreviewView)
	COM_INTERFACE_ENTRY(IWebPreviewView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, IWebPreviewView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)

	COM_INTERFACE_ENTRY(IOleDocumentSite)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceUIWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceSite)
	COM_INTERFACE_ENTRY(IAdviseSink)
	COM_INTERFACE_ENTRY(IOleInPlaceUIWindow)

//	COM_INTERFACE_ENTRY(ILDocHostUIHandler)
	COM_INTERFACE_ENTRY(IXMLDocumentInMemoryProvider)

END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CWebPreviewView)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CSiteFilesView)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

//DECLARE_CMD_MAP(CSiteFilesView)

// IXMLDocumentInMemoryProvider,
	STDMETHODIMP GetInMemoryDocument(BSTR uri, ILDOMDocument* *pVal);

// IWebPreviewView
public:
// IUIDlg
	STDMETHOD(OnActivate)(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView);
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Preview");
		return S_OK;
	}
	/*
// ICommandTarget
	STDMETHOD(OnCmdMsg)(GUID * iid, IUICmdUpdate * pCmdUI, BOOL * bHandled)
	{
		CComQIPtr<ICommandTarget> target;
		
	// Try document first
		target = m_pDocument;
		target->OnCmdMsg(iid, pCmdUI, bHandled);
		if (*bHandled) return S_OK;

	// Then try us
		return ProcessTargetCommands::OnCmdMsg(iid, pCmdUI, bHandled);
	}
*/

// IAdviseSink
     virtual /* [local] */ void STDMETHODCALLTYPE OnDataChange( 
         /* [unique][in] */ FORMATETC __RPC_FAR *pFormatetc,
         /* [unique][in] */ STGMEDIUM __RPC_FAR *pStgmed)
	{
		  ::MessageBox(NULL, "ActivateMe", "", MB_OK);
	}
     
     virtual /* [local] */ void STDMETHODCALLTYPE OnViewChange( 
         /* [in] */ DWORD dwAspect,
         /* [in] */ LONG lindex)
	{
		  ::MessageBox(NULL, "OnViewChange", "", MB_OK);
	}
     
     virtual /* [local] */ void STDMETHODCALLTYPE OnRename( 
         /* [in] */ IMoniker __RPC_FAR *pmk)
	{
		  ::MessageBox(NULL, "OnRename", "", MB_OK);
	}
     
     virtual /* [local] */ void STDMETHODCALLTYPE OnSave( void)
	{
		  ::MessageBox(NULL, "OnSave", "", MB_OK);
	}
     
     virtual /* [local] */ void STDMETHODCALLTYPE OnClose( void)
	{
		  ::MessageBox(NULL, "OnClose", "", MB_OK);
	}

// IOleDocumentSite

	  virtual HRESULT STDMETHODCALLTYPE ActivateMe( 
            /* [in] */ IOleDocumentView __RPC_FAR *pViewToActivate);

// IOleClientSite
        virtual HRESULT STDMETHODCALLTYPE SaveObject( void)
	{
		  ::MessageBox(NULL, "SaveObject", "", MB_OK);
		 return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE GetMoniker( 
            /* [in] */ DWORD dwAssign,
            /* [in] */ DWORD dwWhichMoniker,
            /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
	{
    return E_NOTIMPL;
	 ::MessageBox(NULL, "GetMoniker", "", MB_OK);
		 return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE GetContainer( 
            /* [out] */ IOleContainer __RPC_FAR *__RPC_FAR *ppContainer)
	{
	  		*ppContainer=NULL;
//		 MessageBox(NULL, "GetContainer", "", MB_OK);
		 return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE ShowObject( void)
	{
			  return S_OK;
			  ::MessageBox(NULL, "ShowObject", "", MB_OK);
		 return S_OK;
	}

        virtual HRESULT STDMETHODCALLTYPE OnShowWindow( 
            /* [in] */ BOOL fShow)
	{
			  return S_OK;
			  ::MessageBox(NULL, "OnShowWindow", "", MB_OK);
		 return S_OK;
	}

        virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout( void)
	{
	    return E_NOTIMPL;
		 ::MessageBox(NULL, "RequestNewObjectLayout", "", MB_OK);
		 return S_OK;
	}

		// IOleWindow
        virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow( 
            /* [out] */ HWND __RPC_FAR *phwnd)
	{
		  get_hwnd(phwnd);
		 return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp( 
            /* [in] */ BOOL fEnterMode)
	{
			  ::MessageBox(NULL, "ContextSensitiveHelp", "", MB_OK);
		 return S_OK;
	}

	// IOleInPlaceSite
        virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate( void)
	{
		 return S_OK;
		 ::MessageBox(NULL, "CanInPlaceActivate", "", MB_OK);
		 return S_OK;
	}

   virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate( void);
        

/*
 * CImpIOleInPlaceSite::OnUIActivate
 *
 * Purpose:
 *  Informs the container that the object is going to start munging
 *  around with user interface, like replacing the menu.  The
 *  container should remove any relevant UI in preparation.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */
    virtual HRESULT STDMETHODCALLTYPE OnUIActivate( void)
	{
		 //MessageBox(NULL, "OnUIActivate", "", MB_OK);
		 return S_OK;
	}
        
	 virtual HRESULT STDMETHODCALLTYPE GetWindowContext( 
		 /* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame,
		 /* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc,
		 /* [out] */ LPRECT lprcPosRect,
		 /* [out] */ LPRECT lprcClipRect,
		 /* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo);
        
        virtual HRESULT STDMETHODCALLTYPE Scroll( 
            /* [in] */ SIZE scrollExtant)
	{
		 ::MessageBox(NULL, "Scroll", "", MB_OK);
		 return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate( 
            /* [in] */ BOOL fUndoable)
	{
			  ::MessageBox(NULL, "OnUIDeactivate", "", MB_OK);
		 return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate( void)
	{
			  ::MessageBox(NULL, "OnInPlaceDeactivate", "", MB_OK);
		 return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE DiscardUndoState( void)
	{
			  ::MessageBox(NULL, "DiscardUndoState", "", MB_OK);
		 return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo( void)
	{
			  ::MessageBox(NULL, "DeactivateAndUndo", "", MB_OK);
		 return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE OnPosRectChange( 
            /* [in] */ LPCRECT lprcPosRect)
	{
			  ::MessageBox(NULL, "OnPosRectChange", "", MB_OK);
		 return S_OK;
	}

// IOleInPlaceUIWindow
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetBorder( 
         /* [out] */ LPRECT lprectBorder)
	  {
		  GetClientRect(lprectBorder);
		  return S_OK;
	  }
     
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE RequestBorderSpace( 
         /* [unique][in] */ LPCBORDERWIDTHS pborderwidths)
	  {
	//Framer has no border space restrictions
	return NOERROR;
	  }
     
     virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetBorderSpace( 
         /* [unique][in] */ LPCBORDERWIDTHS pborderwidths)
	  {
		  ::MessageBox(NULL, "IOleInPlaceUIWindow::SetBorderSpace", "", MB_OK);

		  CRect rc;
		  GetClientRect(&rc);
	     m_pIOleDocView->SetRect(&rc);
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE SetActiveObject( 
         /* [unique][in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
         /* [unique][string][in] */ LPCOLESTR pszObjName)
	  {
		  ATLASSERT(0);
//			m_pIOleIPActiveObject = pActiveObject;

		 // MessageBox(NULL, "IOleInPlaceUIWindow::SetActiveObject", "", MB_OK);
		  return S_OK;
	  }

#if 0
// IOleWindow
private:
	STDMETHOD(GetWindow)(HWND *phwnd)
	{
		 *phwnd = m_hWnd;
		return S_OK;
	}

   STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode) {return E_NOTIMPL;}

// IOleInPlaceSite
private:
	STDMETHOD(CanInPlaceActivate)() {return S_OK;}

	STDMETHOD(OnInPlaceActivate)()
	{
		  m_bInPlaceActive = TRUE;
		  return S_OK;
	}

	STDMETHOD(GetWindowContext)(IOleInPlaceFrame** ppFrame,
								IOleInPlaceUIWindow** ppDoc,
								LPRECT lprcPosRect,
								LPRECT lprcClipRect,
								LPOLEINPLACEFRAMEINFO lpFrameInfo)
	{
		GetClientRect(lprcPosRect);
		GetClientRect(lprcClipRect);
		return S_OK;
	}

	STDMETHOD(OnInPlaceDeactivate)()
	{
		m_bInPlaceActive = FALSE;
		return S_OK;
	}

	STDMETHOD(OnUIActivate)() {return E_NOTIMPL;}
	STDMETHOD(Scroll)(SIZE scrollExtant) {return E_NOTIMPL;}
	STDMETHOD(OnUIDeactivate)(BOOL fUndoable) {return E_NOTIMPL;}
	STDMETHOD(DiscardUndoState)() {return E_NOTIMPL;}
	STDMETHOD(DeactivateAndUndo)( void) {return E_NOTIMPL;}
	STDMETHOD(OnPosRectChange)(LPCRECT lprcPosRect) {return E_NOTIMPL;}

// IOleClientSite Methods
private:
	STDMETHOD(SaveObject)(void) {return E_NOTIMPL;}
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) {return E_NOTIMPL;}
	STDMETHOD(GetContainer)(IOleContainer **ppContainer) {return E_NOTIMPL;}
	STDMETHOD(ShowObject)(void) {return E_NOTIMPL;}
	STDMETHOD(OnShowWindow)(BOOL fShow) {return E_NOTIMPL;}
	STDMETHOD(RequestNewObjectLayout)(void) {return E_NOTIMPL;}
#endif
};
