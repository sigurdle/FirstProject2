namespace System
{
namespace Gui
{

#define HIMETRIC_PER_INCH   2540
#define MAP_PIX_TO_LOGHIM(x,ppli)   MulDiv(HIMETRIC_PER_INCH, (x), (ppli))
#define MAP_LOGHIM_TO_PIX(x,ppli)   MulDiv((ppli), (x), HIMETRIC_PER_INCH)

/////////////////////////////////////////////////////////////////////////////
// Windowing : Conversion helpers

#ifndef __LERSTAD__

inline void AtlHiMetricToPixel(const SIZEL* lpSizeInHiMetric, LPSIZEL lpSizeInPix)
{
//	ATLENSURE_THROW(lpSizeInHiMetric!=NULL, E_POINTER);
//	ATLENSURE_THROW(lpSizeInPix!=NULL, E_POINTER);	
	int nPixelsPerInchX;    // Pixels per logical inch along width
	int nPixelsPerInchY;    // Pixels per logical inch along height

	HDC hDCScreen = GetDC(NULL);
//	ATLASSUME(hDCScreen != NULL);
	nPixelsPerInchX = GetDeviceCaps(hDCScreen, LOGPIXELSX);
	nPixelsPerInchY = GetDeviceCaps(hDCScreen, LOGPIXELSY);
	ReleaseDC(NULL, hDCScreen);

	lpSizeInPix->cx = MAP_LOGHIM_TO_PIX(lpSizeInHiMetric->cx, nPixelsPerInchX);
	lpSizeInPix->cy = MAP_LOGHIM_TO_PIX(lpSizeInHiMetric->cy, nPixelsPerInchY);
}

inline void AtlPixelToHiMetric(const SIZEL * lpSizeInPix, LPSIZEL lpSizeInHiMetric)
{
//	ATLENSURE_THROW(lpSizeInPix!=NULL, E_POINTER);
//	ATLENSURE_THROW(lpSizeInHiMetric!=NULL, E_POINTER);	
	int nPixelsPerInchX;    // Pixels per logical inch along width
	int nPixelsPerInchY;    // Pixels per logical inch along height

	HDC hDCScreen = GetDC(NULL);
//	ATLASSUME(hDCScreen != NULL);
	nPixelsPerInchX = GetDeviceCaps(hDCScreen, LOGPIXELSX);
	nPixelsPerInchY = GetDeviceCaps(hDCScreen, LOGPIXELSY);
	ReleaseDC(NULL, hDCScreen);

	lpSizeInHiMetric->cx = MAP_PIX_TO_LOGHIM(lpSizeInPix->cx, nPixelsPerInchX);
	lpSizeInHiMetric->cy = MAP_PIX_TO_LOGHIM(lpSizeInPix->cy, nPixelsPerInchY);
}

class OleContainer : public Object,
		public IOleContainer,
		//public IOleInPlaceUIWindow
		public IOleInPlaceFrame	// IOleInPlaceUIWindow
{
public:

	CTOR OleContainer() : m_refCount(0)
	{
	}

	HWND GetWindow()
	{
		if (m_window && m_window->get_PWindow())
		{
			return m_window->get_PWindow()->get_Handle();
		}
		else
			return NULL;
	}

    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        /* [in] */ const ::IID& riid,
        /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if (ppvObject == nullptr)
		{
			return E_POINTER;
		}

		if (riid == IID_IUnknown)
		{
			*ppvObject = static_cast<IOleContainer*>(this);
		}
		else if (riid == __uuidof(IOleContainer))
		{
			*ppvObject = static_cast<IOleContainer*>(this);
		}
		else if (riid == __uuidof(IOleWindow))
		{
			*ppvObject = static_cast<IOleWindow*>(this);
		}
		else if (riid == __uuidof(IOleInPlaceUIWindow))
		{
			*ppvObject = static_cast<IOleInPlaceUIWindow*>(this);
		}
		else if (riid == __uuidof(IOleInPlaceFrame))
		{
			*ppvObject = static_cast<IOleInPlaceFrame*>(this);
		}
		else
		{
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}

		AddRef();
		return S_OK;
	}

	virtual ULONG __stdcall AddRef()
	{
		return ++m_refCount;
	}

	virtual ULONG __stdcall Release()
	{
		if (--m_refCount == 0)
		{
			//operator::delete();

			return 0;
		}
		return m_refCount;
	}

	// IOleContainer
		// IParseDisplayName
        virtual HRESULT STDMETHODCALLTYPE ParseDisplayName( 
            /* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
            /* [in] */ __RPC__in LPOLESTR pszDisplayName,
            /* [out] */ __RPC__out ULONG *pchEaten,
            /* [out] */ __RPC__deref_out_opt IMoniker **ppmkOut)
		{
		return S_OK;
		}

    virtual HRESULT STDMETHODCALLTYPE EnumObjects( 
        /* [in] */ DWORD grfFlags,
        /* [out] */ __RPC__deref_out_opt IEnumUnknown **ppenum)
	{
		return S_OK;
	}

    virtual HRESULT STDMETHODCALLTYPE LockContainer( 
        /* [in] */ BOOL fLock)
	{
		return S_OK;
	}

// IOleWindow

	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow( 
		/* [out] */ __RPC__deref_out_opt HWND *phwnd)
	{
		if (phwnd == nullptr) return E_POINTER;
		*phwnd = GetWindow();
		return S_OK;
	}
    
    virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp( 
        /* [in] */ BOOL fEnterMode)
	{
		return S_OK;
	}

	// IOleInPlaceUIWindow
        virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetBorder( 
            /* [out] */ __RPC__out LPRECT lprectBorder)
		{
			return S_OK;
		}
        
        virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE RequestBorderSpace( 
            /* [unique][in] */ __RPC__in_opt LPCBORDERWIDTHS pborderwidths)
		{
			return INPLACE_E_NOTOOLSPACE;
		}
        
        virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetBorderSpace( 
            /* [unique][in] */ __RPC__in_opt LPCBORDERWIDTHS pborderwidths)
		{
			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE SetActiveObject( 
            /* [unique][in] */ __RPC__in_opt IOleInPlaceActiveObject *pActiveObject,
            /* [unique][string][in] */ __RPC__in_opt LPCOLESTR pszObjName)
		{
			m_pActiveObject = pActiveObject;
			return S_OK;
		}

		// IOleInPlaceFrame
        virtual HRESULT STDMETHODCALLTYPE InsertMenus( 
            /* [in] */ __RPC__in HMENU hmenuShared,
            /* [out][in] */ __RPC__inout LPOLEMENUGROUPWIDTHS lpMenuWidths)
		{
			return S_OK;
		}
        
        virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetMenu( 
            /* [in] */ __RPC__in HMENU hmenuShared,
            /* [in] */ __RPC__in HOLEMENU holemenu,
            /* [in] */ __RPC__in HWND hwndActiveObject)
		{
			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE RemoveMenus( 
            /* [in] */ __RPC__in HMENU hmenuShared)
		{
			return S_OK;
		}
        
        virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetStatusText( 
            /* [unique][in] */ __RPC__in_opt LPCOLESTR pszStatusText)
		{
			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable)
		{
			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ __RPC__in LPMSG lpmsg,
            /* [in] */ WORD wID)
		{
			return S_FALSE;
		}

public:

	Window* m_window;
	IOleInPlaceActiveObject* m_pActiveObject;
	//pszObjName;
	ULONG m_refCount;
};

class OleControlSite : public Object,
	public IOleClientSite,
	public IOleControlSite,
	public IOleInPlaceSiteWindowless	// IOleInPlaceSiteEx,IOleInPlaceSite,IOleWindow
{
public:

	CTOR OleControlSite() :
		m_refCount(0),
		m_bInPlaceActive(false),
		m_bWindowless(false)
	{
	}

	HRESULT CoCreateInstance(StringIn progid, __in_opt IUnknown* pUnkOuter, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER)
	{
		CLSID clsid;
		CLSIDFromProgID(progid.c_strw(), &clsid);
		return CoCreateInstance(clsid, pUnkOuter, dwClsContext);
	}

	HRESULT CoCreateInstance(__in  const ::IID& rclsid, __in_opt IUnknown* pUnkOuter, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER)
	{
		ThrowHr hr;
		
		hr = m_spOleObject.CoCreateInstance(rclsid, pUnkOuter, dwClsContext);

		AddRef();

		m_spOleObject.QueryInterface(&m_spWindow);
		m_spOleObject.QueryInterface(&m_spInPlaceObject);
		m_spOleObject.QueryInterface(&m_spViewObject);
//		m_spOleObject.QueryInterface(&m_spInPlaceObjectWindowless);
		m_spOleObject.QueryInterface(&m_spExternalDispatch);

		return hr;
	}

	virtual IUnknown* GetControllingUnknown()
	{
		return static_cast<IOleClientSite*>(this);
	}

	HWND GetWindow()
	{
		return m_container->m_window->get_PWindow()->get_Handle();
	}

	HRESULT InPlaceActivate()
	{
		ThrowHr hr;

		hr = m_spOleObject->GetMiscStatus(DVASPECT_CONTENT, &m_dwMiscStatus);
		if (m_dwMiscStatus & OLEMISC_SETCLIENTSITEFIRST)
		{
		//	ComQIPtr<IOleClientSite> spClientSite(GetControllingUnknown());
			hr = m_spOleObject->SetClientSite(this);
		}

		ComPtr<IPersistStreamInit> spPSI;
		m_spOleObject.QueryInterface(&spPSI);

		if (spPSI)
		{
		//	if (pStream)
		//		hr = spPSI->Load(pStream);
		//	else
				hr = spPSI->InitNew();
		}
		/*
		else if (pStream)
		{
			CComQIPtr<IPersistStream> spPS(m_spOleObject);
			if (spPS)
				hr = spPS->Load(pStream);
		}
		*/

		if ((m_dwMiscStatus & OLEMISC_SETCLIENTSITEFIRST) == 0)
		{
		//	ComQIPtr<IOleClientSite> spClientSite(GetControllingUnknown());
			hr = m_spOleObject->SetClientSite(this);
		}

		hr = m_spOleObject->SetHostNames(L"GUIAxHost", NULL);

		if ((m_dwMiscStatus & OLEMISC_INVISIBLEATRUNTIME) == 0)
		{
		//	m_texture.

		//	D3D10_RESOURCE_MISC_GDI_COMPATIBLE

			//GetClientRect(&m_rcPos);
			m_pxSize.cx = m_rcPos.right - m_rcPos.left;
			m_pxSize.cy = m_rcPos.bottom - m_rcPos.top;
			AtlPixelToHiMetric(&m_pxSize, &m_hmSize);
			hr = m_spOleObject->SetExtent(DVASPECT_CONTENT, &m_hmSize);
			hr = m_spOleObject->GetExtent(DVASPECT_CONTENT, &m_hmSize);
			AtlHiMetricToPixel(&m_hmSize, &m_pxSize);
			m_rcPos.right = m_rcPos.left + m_pxSize.cx;
			m_rcPos.bottom = m_rcPos.top + m_pxSize.cy;

			ComPtr<IOleClientSite> spClientSite;
			GetControllingUnknown()->QueryInterface(__uuidof(IOleClientSite), (void**)&spClientSite);
			hr = m_spOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, spClientSite, 0, GetWindow(), &m_rcPos);
		//	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_INTERNALPAINT | RDW_FRAME);

			/*
			HWND hwnd;
			m_spWindow->GetWindow(&hwnd);
			UINT dwStyle = GetWindowLong(hwnd, GWL_STYLE);
			ASSERT(dwStyle & WS_VISIBLE);
			*/
		}

		ComPtr<IObjectWithSite> spSite;
		m_spOleObject.QueryInterface(&spSite);
		if (spSite != nullptr) spSite->SetSite(GetControllingUnknown());

		return S_OK;
	}

	HRESULT UIActivate()
	{
		HRESULT hr;
		ComPtr<IOleClientSite> spClientSite;
		GetControllingUnknown()->QueryInterface(__uuidof(IOleClientSite), reinterpret_cast<void**>(&spClientSite));
		hr = m_spOleObject->DoVerb(OLEIVERB_UIACTIVATE, nullptr, spClientSite, 0, GetWindow(), &m_rcPos);

		return hr;
	}

#if 0
	HRESULT DoVerb( 
		  LONG iVerb,          //Value representing verb to be performed
		  LPMSG lpmsg,         //Pointer to structure that describes Windows 
							   // message
		//  IOleClientSite *pActiveSite,
							   //Pointer to active client site
		//  LONG lindex,         //Reserved
		//  HWND hwndParent,     //Handle of window containing the object
		LDraw::RectI posRect  //Pointer to object's display rectangle
		)
	{
		RECT rcPosRect;
		rcPosRect.left = posRect.GetLeft();
		rcPosRect.top = posRect.GetTop();
		rcPosRect.right = posRect.GetRight();
		rcPosRect.bottom = posRect.GetBottom();

		HRESULT hr = m_spOleObject->DoVerb(iVerb, NULL, this,
			0,	// lindex,         //Reserved
			m_container->m_window->m_platformWindow->get_Handle(), &rcPosRect);
		return hr;
	}
#endif

    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        /* [in] */ const ::IID& riid,
        /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject) override
	{
		if (ppvObject == nullptr)
		{
			return E_POINTER;
		}

		if (riid == IID_IUnknown)
		{
			*ppvObject = static_cast<IOleClientSite*>(this);
		}
		else if (riid == __uuidof(IOleClientSite))
		{
			*ppvObject = static_cast<IOleClientSite*>(this);
		}
		else if (riid == __uuidof(IOleControlSite))
		{
			*ppvObject = static_cast<IOleControlSite*>(this);
		}
		else if (riid == __uuidof(IOleWindow))
		{
			*ppvObject = static_cast<IOleWindow*>(this);
		}
		else if (riid == __uuidof(IOleInPlaceSite))
		{
			*ppvObject = static_cast<IOleInPlaceSite*>(this);
		}
		else if (riid == __uuidof(IOleInPlaceSiteWindowless))
		{
			*ppvObject = static_cast<IOleInPlaceSiteWindowless*>(this);
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}

		AddRef();
		return S_OK;
	}

	virtual ULONG __stdcall AddRef() override
	{
		return ++m_refCount;
	}

	virtual ULONG __stdcall Release() override
	{
		if (--m_refCount == 0)
		{
			//operator::delete();

			return 0;
		}
		return m_refCount;
	}

// IOleClientSite
	STDMETHOD(SaveObject)() override
	  {
	MessageBoxA(NULL, "", "", MB_OK);
		return S_OK;
	  }
	  
	STDMETHOD(GetMoniker)( 
		  /* [in] */ DWORD dwAssign,
		  /* [in] */ DWORD dwWhichMoniker,
		  /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk) override
	  {
	MessageBoxA(NULL, "", "", MB_OK);
		  return S_OK;
	  }
	  
	STDMETHOD(GetContainer)( 
		  /* [out] */ IOleContainer __RPC_FAR *__RPC_FAR *ppContainer) override
	  {
		  if (m_container)
		  {
			*ppContainer = m_container;
			(*ppContainer)->AddRef();

		 // MessageBoxA(NULL, "GetContainer", "", MB_OK);
			  return S_OK;
		  }
		  else
			  return E_FAIL;
	  }
	  
	STDMETHOD(ShowObject)() override
	{
		HDC hdc = nullptr;
		  /*
		HDC hdc = CWindowImpl<CAxHostWindow>::GetDC();
		if (hdc == NULL)
			return E_FAIL;
			*/
		if (m_spViewObject)
		{
		//	m_spViewObject->Draw(DVASPECT_CONTENT, -1, NULL, NULL, NULL, hdc, (RECTL*)&m_rcPos, (RECTL*)&m_rcPos, NULL, NULL); 
		}
		/*
		CWindowImpl<CAxHostWindow>::ReleaseDC(hdc);
		*/
		  // if we are also embedded, call ShowObject on our container
		return S_OK;
	  }
	  
	STDMETHOD(OnShowWindow)(BOOL fShow) override
	{
	// TODO ??
		//MessageBox(NULL, "", "", MB_OK);
		return S_OK;
	}
	  
	STDMETHOD(RequestNewObjectLayout)()
	{
		MessageBoxA(NULL, "", "", MB_OK);
		return S_OK;
	}

// IOleControlSite

    virtual HRESULT STDMETHODCALLTYPE OnControlInfoChanged( void) override
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE LockInPlaceActive(BOOL fLock) override
   	{
		return E_NOTIMPL;
	}

    virtual HRESULT STDMETHODCALLTYPE GetExtendedControl( 
        /* [out] */ __RPC__deref_out_opt IDispatch **ppDisp) override
	{
		if (ppDisp == NULL) return E_POINTER;

		*ppDisp = NULL;
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE TransformCoords( 
        /* [out][in] */ __RPC__inout POINTL *pPtlHimetric,
        /* [out][in] */ __RPC__inout POINTF *pPtfContainer,
        /* [in] */ DWORD dwFlags) override
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
        /* [in] */ __RPC__in MSG *pMsg,
        /* [in] */ DWORD grfModifiers) override
	{
		return E_NOTIMPL;
	}
    
    virtual HRESULT STDMETHODCALLTYPE OnFocus( 
        /* [in] */ BOOL fGotFocus) override
	{
		return S_OK;
	}
    
    virtual HRESULT STDMETHODCALLTYPE ShowPropertyFrame( void) override
	{
		return E_NOTIMPL;
	}

	// IOleWindow
        virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow( 
            /* [out] */ __RPC__deref_out_opt HWND *phwnd) override
	{
		if (phwnd == NULL) return E_POINTER;
		*phwnd = GetWindow();
		return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp( 
            /* [in] */ BOOL fEnterMode) override
	{
		return E_NOTIMPL;
	}

	// IOleInPlaceSite

		virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate( void) override
		{
			DebugTrace("CanInPlaceActivate()\n");
			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate( void) override
		{
			DebugTrace("OnInPlaceActivate()\n");

			// should only be called once the first time control is inplace-activated
			ASSERT(m_bInPlaceActive == false);
			ASSERT(m_spInPlaceObjectWindowless == NULL);

			m_bInPlaceActive = true;
			OleLockRunning(m_spOleObject, TRUE, FALSE);
			m_bWindowless = false;
			m_spOleObject->QueryInterface(__uuidof(IOleInPlaceObject), (void**)&m_spInPlaceObjectWindowless);

			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE OnUIActivate( void) override
	{
		DebugTrace("OnUIActivate()\n");
		return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE GetWindowContext( 
            /* [out] */ __RPC__deref_out_opt IOleInPlaceFrame **ppFrame,
            /* [out] */ __RPC__deref_out_opt IOleInPlaceUIWindow **ppDoc,
            /* [out] */ __RPC__out LPRECT lprcPosRect,
            /* [out] */ __RPC__out LPRECT lprcClipRect,
            /* [out][in] */ __RPC__inout LPOLEINPLACEFRAMEINFO lpFrameInfo) override
	{
		DebugTrace("GetWindowContext()\n");

		if (ppFrame) *ppFrame = m_container;
		if (ppDoc) *ppDoc = NULL;

		if (lprcPosRect)
		{
			lprcPosRect->left = 0;
			lprcPosRect->top = 0;
			lprcPosRect->right = 600;
			lprcPosRect->bottom= 500;
		}

		if (lprcClipRect)
		{
			lprcClipRect->left = 0;
			lprcClipRect->top = 0;
			lprcClipRect->right = 600;
			lprcClipRect->bottom= 500;
		}

		if (lpFrameInfo)
		{
			lpFrameInfo->fMDIApp = false;
			lpFrameInfo->haccel = NULL;
			lpFrameInfo->cAccelEntries = 0;
			lpFrameInfo->hwndFrame = m_container->GetWindow();
		}

		return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE Scroll( 
            /* [in] */ SIZE scrollExtant) override
	{
		DebugTrace("Scroll()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate( 
            /* [in] */ BOOL fUndoable) override
	{
		DebugTrace("OnUIDeactivate()\n");
		return E_NOTIMPL;
	}
       
        virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate( void) override
	{
		DebugTrace("OnInPlaceDeactivate()\n");
		return E_NOTIMPL;
	}
        
    virtual HRESULT STDMETHODCALLTYPE DiscardUndoState( void) override
	{
		DebugTrace("DiscardUndoState()\n");
		return E_NOTIMPL;
	}
        
    virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo( void) override
	{
		DebugTrace("DeactivateAndUndo()\n");
		return E_NOTIMPL;
	}

    virtual HRESULT STDMETHODCALLTYPE OnPosRectChange( 
            /* [in] */ __RPC__in LPCRECT lprcPosRect) override
	{
		DebugTrace("OnPosRectChange()\n");
		return E_NOTIMPL;
	}

	// IOleInPlaceSiteEx
        virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivateEx( 
            /* [out] */ __RPC__out BOOL *pfNoRedraw,
            /* [in] */ DWORD dwFlags) override
	{
		// should only be called once the first time control is inplace-activated
		ASSERT(m_bInPlaceActive == false);
		ASSERT(m_spInPlaceObjectWindowless == NULL);

		m_bInPlaceActive = true;
		OleLockRunning(m_spOleObject, TRUE, FALSE);
		HRESULT hr = E_FAIL;
		if (dwFlags & ACTIVATE_WINDOWLESS)
		{
			m_bWindowless = true;
			hr = m_spOleObject->QueryInterface(__uuidof(IOleInPlaceObjectWindowless), (void**)&m_spInPlaceObjectWindowless);
		}
		if (FAILED(hr))
		{
			m_bWindowless = false;
			hr = m_spOleObject->QueryInterface(__uuidof(IOleInPlaceObject), (void**)&m_spInPlaceObjectWindowless);
		}
		if (m_spInPlaceObjectWindowless)
			m_spInPlaceObjectWindowless->SetObjectRects(&m_rcPos, &m_rcPos);

		return S_OK;
	}

        virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivateEx( 
            /* [in] */ BOOL fNoRedraw) override
	{
		DebugTrace("OnInPlaceDeactivateEx()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE RequestUIActivate( void) override
	{
		DebugTrace("RequestUIActivate()\n");
		return E_NOTIMPL;
	}

		// IOleInPlaceSiteWindowless
        virtual HRESULT STDMETHODCALLTYPE CanWindowlessActivate( void) override
	{
	//	DebugTrace("CanWindowlessActivate()\n");
		return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE GetCapture( void) override
	{
		DebugTrace("GetCapture()\n");
		return m_bCapture? S_OK: S_FALSE;
	}
        
        virtual HRESULT STDMETHODCALLTYPE SetCapture( 
            /* [in] */ BOOL fCapture) override
	{
		DebugTrace("SetCapture()\n");
		m_bCapture = !!fCapture;
		return S_OK;
	}
        
        virtual HRESULT STDMETHODCALLTYPE GetFocus( void) override
	{
		DebugTrace("GetFocus()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE SetFocus( 
            /* [in] */ BOOL fFocus) override
	{
		DebugTrace("SetFocus()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE GetDC( 
            /* [unique][in] */ __RPC__in_opt LPCRECT pRect,
            /* [in] */ DWORD grfFlags,
            /* [out] */ __RPC__deref_out_opt HDC *phDC) override
	{
		DebugTrace("GetDC()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseDC( 
            /* [in] */ __RPC__in HDC hDC) override
	{
		DebugTrace("ReleaseDC()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE InvalidateRect( 
            /* [unique][in] */ __RPC__in_opt LPCRECT pRect,
            /* [in] */ BOOL fErase) override
	{
		DebugTrace("InvalidateRect()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE InvalidateRgn( 
            /* [in] */ __RPC__in HRGN hRGN,
            /* [in] */ BOOL fErase) override
	{
		DebugTrace("InvalidateRgn()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE ScrollRect( 
            /* [in] */ INT dx,
            /* [in] */ INT dy,
            /* [in] */ __RPC__in LPCRECT pRectScroll,
            /* [in] */ __RPC__in LPCRECT pRectClip) override
	{
		DebugTrace("ScrollRect()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE AdjustRect( 
            /* [out][in] */ __RPC__inout LPRECT prc) override
	{
		DebugTrace("AdjustRect()\n");
		return E_NOTIMPL;
	}
        
        virtual HRESULT STDMETHODCALLTYPE OnDefWindowMessage( 
            /* [in] */ UINT msg,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam,
            /* [out] */ __RPC__out LRESULT *plResult) override
	{
		DebugTrace("OnDefWindowMessage()\n");
		return E_NOTIMPL;
	}

// IAdviseSink
	STDMETHOD_(void, OnDataChange)(FORMATETC* /*pFormatetc*/, STGMEDIUM* /*pStgmed*/)
	{
	MessageBoxA(NULL, "", "", MB_OK);
	}
	STDMETHOD_(void, OnViewChange)(DWORD /*dwAspect*/, LONG /*lindex*/)
	{
	MessageBoxA(NULL, "", "", MB_OK);
	}
	STDMETHOD_(void, OnRename)(IMoniker* /*pmk*/)
	{
	MessageBoxA(NULL, "", "", MB_OK);
	}
	STDMETHOD_(void, OnSave)()
	{
	MessageBoxA(NULL, "", "", MB_OK);
	}
	STDMETHOD_(void, OnClose)()
	{
	MessageBoxA(NULL, "", "", MB_OK);
	}

public:

	ComPtr<IOleObject> m_spOleObject;

#if 0
	CComPtr<IOleInPlaceFrame> m_spInPlaceFrame;
#endif
	ComPtr<IOleWindow> m_spWindow;
	ComPtr<IOleInPlaceObject> m_spInPlaceObject;
//	ComPtr<IOleInPlaceUIWindow> m_spInPlaceUIWindow;
	ComPtr<IViewObjectEx> m_spViewObject;
	ComPtr<IOleInPlaceObjectWindowless> m_spInPlaceObjectWindowless;
	ComPtr<IDispatch> m_spExternalDispatch;

	ComPtr<ID3D10Texture2D> m_texture2D;

	RECT m_rcPos;
	SIZE m_pxSize;
	SIZE m_hmSize;

	OleContainer* m_container;

	DWORD m_dwMiscStatus;

	bool m_bInPlaceActive : 1;
	bool m_bWindowless : 1;
	bool m_bCapture : 1;

	long m_refCount;
};
#else
typedef Object OleControlSite;
#endif

class GUIEXT ActiveXHostVisual : public UIElement
{
public:

	CTOR ActiveXHostVisual();

#ifndef __LERSTAD__
	CTOR ActiveXHostVisual(StringIn progId, __in_opt IUnknown* pUnkOuter = NULL, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER);
	CTOR ActiveXHostVisual(const ::IID& rclsid, __in_opt IUnknown* pUnkOuter = NULL, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER);
#endif

	virtual void Render(ManagedRenderContext renderContext) override;
	virtual void OnSetRoot(IRootVisual* root) override;

	DEPENDENCY_PROPERTY(String, CLSID)
	DEPENDENCY_PROPERTY(String, ProgID)

	DEPENDENCY_CLASS(ActiveXHostVisual, UIElement)

	OleControlSite* m_site;

private:

	HBITMAP m_hBitmap;
	byte* m_bitmapBits;
	Graphics::Bitmap* m_bitmap;
	bool m_bDrawValid;
};

#if 0
class GUIEXT ActiveXHostElement : public UIElement
{
public:

	CTOR ActiveXHostElement();
//	CTOR ActiveXControlHost(StringIn progId, __in_opt IUnknown* pUnkOuter = NULL, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER);
//	CTOR ActiveXControlHost(const ::IID& rclsid, __in_opt IUnknown* pUnkOuter = NULL, __in DWORD dwClsContext = CLSCTX_INPROC_SERVER);

	DEPENDENCY_CLASS(ActiveXHostElement, UIElement)

	DEPENDENCY_PROPERTY(ImmutableString<wchar_t>*, CLSID)
	DEPENDENCY_PROPERTY(ImmutableString<wchar_t>*, ProgID)

protected:

	virtual Visual* CreateVisual();
};
#endif

}	// Gui
}	// System
