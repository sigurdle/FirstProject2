// EMediaClipDocument.h : Declaration of the CEMediaClipDocument

#ifndef __EMEDIACLIPDOCUMENT_H_
#define __EMEDIACLIPDOCUMENT_H_

#include "resource.h"       // main symbols

#include "WebDocumentImpl.h"

//#import "..\LHTML\LHTML.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids

class ATL_NO_VTABLE CVideoSample : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CLMediaSampleImpl<ILVideoSample>
{
public:
	CVideoSample()
	{
		m_pBitmap = NULL;
	}

	Gdiplus::Bitmap* m_pBitmap;
	Gdiplus::BitmapData m_bitmapData;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVideoSample)
	COM_INTERFACE_ENTRY(ILMediaSample)
	COM_INTERFACE_ENTRY(ILVideoSample)
END_COM_MAP()

public:

	STDMETHOD(GetMediaType)(ILMediaType* *pVal)
	{
		return S_OK;
	}
#if 0
	STDMETHOD(GetWidth)(long* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_pBitmap->GetWidth();
		return S_OK;
	}

	STDMETHOD(GetHeight)(long* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_pBitmap->GetHeight();
		return S_OK;
	}
#endif

	STDMETHOD(LockBits)(LVideoSampleData *pVal)
	{
		m_pBitmap->LockBits(
			&Gdiplus::Rect(0, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight()),
			Gdiplus::ImageLockModeWrite,
			PixelFormat24bppRGB, &m_bitmapData);

		pVal->width = m_bitmapData.Width;
		pVal->height = m_bitmapData.Height;
		pVal->rowbytes = m_bitmapData.Stride;
		pVal->bitcount = 24;
		pVal->idata = (LPBYTE)m_bitmapData.Scan0;

		return S_OK;
	}
	STDMETHOD(UnlockBits)()
	{
		m_pBitmap->UnlockBits(&m_bitmapData);

		return S_OK;
	}
};

class CMediaClipView;
class CAudioClipView;

class CEMediaClipDocument;

class ATL_NO_VTABLE CMediaStream :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CLBaseFilterImpl,
	public ILMediaSeeking
{
public:
	class CInputPin;

	class ATL_NO_VTABLE CMemAllocator : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public ILMemAllocator
	{
	public:
		CMemAllocator()
		{
			m_pInputPin = NULL;
		}

		CInputPin* m_pInputPin;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CMemAllocator)
		COM_INTERFACE_ENTRY(ILMemAllocator)
	END_COM_MAP()

	public:
		STDMETHOD(GetBuffer)(ILMediaSample* *pVal)
		{
			CComObject<CVideoSample>* pSample;
			CComObject<CVideoSample>::CreateInstance(&pSample);
			pSample->AddRef();

			CComQIPtr<ILVideoMediaType> videoType = m_pInputPin->m_mediaType;
			long width;
			long height;
			videoType->GetWidth(&width);
			videoType->GetHeight(&height);

			pSample->m_pBitmap = new Gdiplus::Bitmap(width, height, PixelFormat24bppRGB);

			*pVal = pSample;

			return S_OK;
		}
	};

	class ATL_NO_VTABLE CInputPin : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLPinImpl,
		public ILMemInputPin
	{
	public:
		CInputPin()
		{
			m_direction = LPINDIR_INPUT;
			m_pFilter = NULL;
		}

		int FinalConstruct()
		{
			CComObject<CMemAllocator>::CreateInstance(&m_pAllocator);
			m_pAllocator->AddRef();
			m_pAllocator->m_pInputPin = this;

			return 0;
		}

		void FinalRelease()
		{
			if (m_pAllocator)
			{
				m_pAllocator->Release();
				m_pAllocator = NULL;
			}
		}

		CMediaStream* m_pFilter;

		ILMediaType* m_mediaType;

		CComObject<CMemAllocator>* m_pAllocator;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputPin)
		COM_INTERFACE_ENTRY(ILPin)
		COM_INTERFACE_ENTRY(ILMemInputPin)
	END_COM_MAP()

	public:
		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}

		STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType)
		{
			CLPinImpl::ReceiveConnection(pConnector, pMediaType);
			m_mediaType = pMediaType;

			return S_OK;
		}

	// ILMemInputPin
		STDMETHOD(GetAllocator)(ILMemAllocator* *ppAllocator)
		{
			if (ppAllocator == NULL) return E_POINTER;
			*ppAllocator = m_pAllocator;
			(*ppAllocator)->AddRef();
			return S_OK;
		}
		STDMETHOD(Receive)(ILMediaSample *pSample)
		{
			m_pFilter->m_pSample = static_cast<CVideoSample*>(pSample);
			return S_OK;
		}
	};

	CMediaStream()
	{
		m_pInputPin = NULL;

		m_pSample = NULL;

		m_pDocument = NULL;

		m_wavFormat = NULL;
		m_wavBuffer = NULL;
		m_nSamples = 0;
	}

	int FinalConstruct()
	{
		CComObject<CInputPin>::CreateInstance(&m_pInputPin);
		m_pInputPin->AddRef();
		m_pInputPin->m_pFilter = this;

		return 0;
	}

	void FinalRelease()
	{
		if (m_pInputPin)
		{
			m_pInputPin->Release();
			m_pInputPin = NULL;
		}
	}

	CComObject<CInputPin>* m_pInputPin;

	CVideoSample* m_pSample;

	LPWAVEFORMATEX m_wavFormat;
	LPSTR m_wavBuffer;
	LONGLONG m_nSamples;

	CEMediaClipDocument* m_pDocument;
	CComQIPtr<ILMediaStream> m_stream;

	CComPtr<IUIDlg> m_view;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMediaStream)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
	COM_INTERFACE_ENTRY(ILMediaSeeking)
END_COM_MAP()

// ILMediaSeeking
	STDMETHOD(Seek)(double seconds)
	{
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->Seek(seconds);
	}

	STDMETHOD(GetCurrentPosition)(double *pVal)
	{
		/*
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->Seek(seconds);
		*/
	}

	STDMETHOD(GetDuration)(double *pVal)
	{
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->GetDuration(pVal);
	}

// ILBaseFilter
	STDMETHOD(GetPinCount)(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = 1;
		return S_OK;
	}
	STDMETHOD(GetPin)(long index, ILPin* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		if (index == 0)
			(*pVal = m_pInputPin)->AddRef();

		return S_OK;
	}
};

class ATL_NO_VTABLE CMediaStreamsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CMediaClipView, &CLSID_MediaClipView>,
//	public IConnectionPointContainerImpl<CMediaClipView>,
//	public IDispatchImpl<IMediaClipView, &IID_IMediaClipView, &LIBID_WEBEDITORLib>,

	public CUIDialogImpl<CMediaStreamsDlg, CWindowImpl<CMediaStreamsDlg> >,

//	public IEViewGroup,

	public IDispEventImpl<1, CMediaStreamsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CMediaStreamsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public ProcessTargetCommands
//	public IDropTarget
{
public:
//	DECLARE_WND_CLASS(NULL)

	CMediaStreamsDlg()
	{
		m_hFont = NULL;

		m_pDocument = NULL;
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

//	CComPtr<IEXMLViewGroup> m_viewGroup;
//	CComQIPtr<IEXMLDocument> m_document;
	CComQIPtr<IUIScrollBar>	m_horz;
	CComQIPtr<IUIScrollBar>	m_vert;

	CEMediaClipDocument* m_pDocument;

	HFONT m_hFont;

//	CComPtr<IEViewGroupSite> m_spViewGroupSite;

	void OnSize();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMediaStreamsDlg)
//	COM_INTERFACE_ENTRY(IMediaClipView)

//	COM_INTERFACE_ENTRY(IEViewGroup)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)

	COM_INTERFACE_ENTRY(ICommandTarget)

//	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

/*
BEGIN_CONNECTION_POINT_MAP(CMediaStreamsDlg)
END_CONNECTION_POINT_MAP()
*/

BEGIN_SINK_MAP(CMediaStreamsDlg)
  // SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
 //  SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(3, DIID__IWebXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
END_SINK_MAP()

/*
	HRESULT __stdcall OnHorzScroll(long code, long pos);
	HRESULT __stdcall OnVertScroll(long code, long pos);
	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);
*/

BEGIN_MSG_MAP(CMediaStreamsDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);

END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CMediaStreamsDlg)

// IDropTarget
/*
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
*/
// IMediaClipView
public:
//	STDMETHOD(get_document)(/*[out, retval]*/ IWebXMLDocument* *pVal);
//	STDMETHOD(put_document)(/*[in]*/ IWebXMLDocument* newVal);

// IEViewGroup
	STDMETHOD(OnActivate)(BOOL bActivate)
	{
		return S_OK;
	}

// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Streams");
		return S_OK;
	}
// ICommandTarget
	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

/////////////////////////////////////////////////////////////////////////////
// CEMediaClipDocument
class ATL_NO_VTABLE CEMediaClipDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEMediaClipDocument, &CLSID_EMediaClipDocument>,
	public IEMediaClipDocument,

	public CEDocumentImpl<CEMediaClipDocument>,

	public IOleObject,
	public IPersistFile,

	public ProcessTargetCommands,
	public CMessageMap
{
public:
	CEMediaClipDocument() : m_cwnd("static", this, 1)
	{
		m_filterGraph = NULL;

		m_nTimerID = 0;
		m_hWaveOut = NULL;

		m_duration = 0;
		m_currentTime = 0;

		m_frameRate = 30;
		m_bPlaying = FALSE;

//		m_pVideoClipView = NULL;
//		m_pAudioClipView = NULL;
	}

	int FinalConstruct()
	{
		m_cwnd.Create(NULL, CRect(0,0,0,0), NULL, WS_POPUP);

		return 0;
	}

	void FinalRelease()
	{
		m_cwnd.DestroyWindow();
	}

	CComQIPtr<ILXMediaApp> m_app;

	CContainedWindow m_cwnd;

	BOOL m_bPlaying;

	CArray<CMediaStream*,CMediaStream*> m_streams;

	CComPtr<ILFilterGraph> m_filterGraph;

	UINT m_nTimerID;
	HWAVEOUT m_hWaveOut;
	WAVEHDR m_wavHdr;

	double m_duration;
	double m_currentTime;
	double m_frameRate;

//	CMediaClipView* m_pVideoClipView;
//	CAudioClipView* m_pAudioClipView;

	CComPtr<ILDOMElement> m_mediaElement;	// smil media, or svg video/audio

	CComPtr<IOleClientSite> m_spClientSite;

	double GetClipBegin()
	{
		if (m_mediaElement)
		{
			CComBSTR bstr;
			m_mediaElement->getAttribute(L"clipBegin", &bstr);
			if (bstr)
				return atof(_bstr_t(bstr));
			else
				return 0;
		}
		else
			return 0;
	}

	double GetClipEnd()
	{
		if (m_mediaElement)
		{
			CComBSTR bstr;
			m_mediaElement->getAttribute(L"clipEnd", &bstr);
			if (bstr)
				return atof(_bstr_t(bstr));
			else
				return m_duration;
		}
		else
			return m_duration;
	}

	void UpdateAllVideoViews();

DECLARE_REGISTRY_RESOURCEID(IDR_EMEDIACLIPDOCUMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEMediaClipDocument)
	COM_INTERFACE_ENTRY(IEMediaClipDocument)
	COM_INTERFACE_ENTRY(IEDocument)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_MSG_MAP(CMediaClipDocument)
	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_USER+100, OnSeekVideo)
		MESSAGE_HANDLER(WOM_DONE, OnWOMDone)
END_MSG_MAP()

	LRESULT OnSeekVideo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnWOMDone(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CMediaClipDocument)

	LRESULT OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

public:
	HRESULT Seek(double seekTo);

	HRESULT SetMediaElement(ILDOMElement* element);
	HRESULT LoadFile(BSTR wszFileName);

// IEMediaClipDocument
public:
// IEDocument
//	STDMETHOD(GetDocumentsClass)(/*[out,retval]*/ IDocumentsClass* *pVal);
	STDMETHOD(Activate)();
//	STDMETHOD(get_undoManager)(/*[out, retval]*/ IOleUndoManager* *pVal);
	STDMETHOD(NewDocument)();
	STDMETHOD(CloseDocument)();
//	STDMETHOD(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);
	STDMETHOD(ShowViews)(IEFrame* pFrame);

   STDMETHOD(SetApp)(ILXAddin* pApp)
	{
		m_app = pApp;
		return S_OK;
	}

// IPersist
   STDMETHOD(GetClassID)(
            /* [out] */ CLSID *pClassID)
	{
		if (pClassID == NULL) return E_POINTER;
		*pClassID = GetObjectCLSID();
		return S_OK;
	}

// IOleObject
     virtual HRESULT STDMETHODCALLTYPE SetClientSite( 
         /* [unique][in] */ IOleClientSite __RPC_FAR *pClientSite)
	  {
		  m_spClientSite = pClientSite;

		//  CComQIPtr<IOleObject> spOleObject = m_document;
		  //return spOleObject->SetClientSite(pClientSite);
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetClientSite( 
         /* [out] */ IOleClientSite __RPC_FAR *__RPC_FAR *ppClientSite)
	  {
		  *ppClientSite = m_spClientSite;
		  if (*ppClientSite) (*ppClientSite)->AddRef();
		  return S_OK;

		  //CComQIPtr<IOleObject> spOleObject = m_document;
		  //return spOleObject->GetClientSite(ppClientSite);
	  }

     virtual HRESULT STDMETHODCALLTYPE SetHostNames( 
         /* [in] */ LPCOLESTR szContainerApp,
         /* [unique][in] */ LPCOLESTR szContainerObj)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE Close( 
         /* [in] */ DWORD dwSaveOption)
	  {
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE SetMoniker( 
         /* [in] */ DWORD dwWhichMoniker,
         /* [unique][in] */ IMoniker __RPC_FAR *pmk)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetMoniker( 
         /* [in] */ DWORD dwAssign,
         /* [in] */ DWORD dwWhichMoniker,
         /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE InitFromData( 
         /* [unique][in] */ IDataObject __RPC_FAR *pDataObject,
         /* [in] */ BOOL fCreation,
         /* [in] */ DWORD dwReserved)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetClipboardData( 
         /* [in] */ DWORD dwReserved,
         /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDataObject)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE DoVerb( 
         /* [in] */ LONG iVerb,
         /* [unique][in] */ LPMSG lpmsg,
         /* [unique][in] */ IOleClientSite __RPC_FAR *pActiveSite,
         /* [in] */ LONG lindex,
         /* [in] */ HWND hwndParent,
         /* [unique][in] */ LPCRECT lprcPosRect)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE EnumVerbs( 
         /* [out] */ IEnumOLEVERB __RPC_FAR *__RPC_FAR *ppEnumOleVerb)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE Update( void)
  	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE IsUpToDate( void)
	  {
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetUserClassID( 
         /* [out] */ CLSID __RPC_FAR *pClsid)
 	  {
		  //CComQIPtr<IOleObject> spOleObject = m_document;
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetUserType( 
         /* [in] */ DWORD dwFormOfType,
         /* [out] */ LPOLESTR __RPC_FAR *pszUserType)
	  {
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE SetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ SIZEL __RPC_FAR *psizel)
	  {
		  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE GetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [out] */ SIZEL __RPC_FAR *psizel)
	  {
		  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE Advise( 
         /* [unique][in] */ IAdviseSink __RPC_FAR *pAdvSink,
         /* [out] */ DWORD __RPC_FAR *pdwConnection)
	  {
		  return S_OK;
	  }

		virtual HRESULT STDMETHODCALLTYPE Unadvise( 
         /* [in] */ DWORD dwConnection)
	  {
		  return S_OK;
	  }

		virtual HRESULT STDMETHODCALLTYPE EnumAdvise( 
         /* [out] */ IEnumSTATDATA __RPC_FAR *__RPC_FAR *ppenumAdvise)
	  {
	  return S_OK;
	  }
     
     virtual HRESULT STDMETHODCALLTYPE GetMiscStatus( 
         /* [in] */ DWORD dwAspect,
         /* [out] */ DWORD __RPC_FAR *pdwStatus)
	  {
	  return S_OK;
	  }

     virtual HRESULT STDMETHODCALLTYPE SetColorScheme( 
         /* [in] */ LOGPALETTE __RPC_FAR *pLogpal)
	  {
	  return S_OK;
	  }

// IPersistFile
	STDMETHOD(IsDirty)( void)
	{
		return S_FALSE;
	}
	STDMETHOD(Load)(/*[in]*/ LPCOLESTR pszFileName, /*[in]*/ DWORD dwMode);
	STDMETHOD(Save)(/*[unique][in]*/ LPCOLESTR pszFileName, /*[in]*/ BOOL fRemember)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(SaveCompleted)(/*[unique][in]*/ LPCOLESTR pszFileName)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetCurFile)(/*[out]*/ LPOLESTR *ppszFileName)
	{
		return E_NOTIMPL;
	}
};

#endif //__EMEDIACLIPDOCUMENT_H_
