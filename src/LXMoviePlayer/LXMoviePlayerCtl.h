// LXMoviePlayerCtl.h : Declaration of the CLXMoviePlayerCtl

#ifndef __LXMOVIEPLAYERCTL_H_
#define __LXMOVIEPLAYERCTL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

class CLXMoviePlayerCtl;

class ATL_NO_VTABLE CMoviePlayerFilter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CLBaseFilterImpl,
	public ILMediaSeeking
{
public:
	class ATL_NO_VTABLE CVideoSample : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLMediaSampleImpl<ILVideoSample>
	{
	public:
		CVideoSample()
		{
			m_hBitmap = NULL;
			m_lpBmi = NULL;
		}

//		Gdiplus::Bitmap* m_pBitmap;
//		Gdiplus::BitmapData m_bitmapData;

		BITMAPINFOHEADER* m_lpBmi;
		HBITMAP m_hBitmap;
		LPBYTE m_bits;
		int m_rowbytes;

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
			*pVal = 0;//m_pBitmap->GetWidth();
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
			pVal->width = m_lpBmi->biWidth;
			pVal->height = m_lpBmi->biHeight;
			pVal->rowbytes = -m_rowbytes;	// Negative height
			pVal->bitcount = 24;
			pVal->idata = (LPBYTE)m_bits + m_rowbytes*(pVal->height-1);

		/*
			m_pBitmap->LockBits(
				&Gdiplus::Rect(0, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight()),
				Gdiplus::ImageLockModeWrite,
				PixelFormat24bppRGB, &m_bitmapData);

			pVal->width = m_bitmapData.Width;
			pVal->height = m_bitmapData.Height;
			pVal->rowbytes = m_bitmapData.Stride;
			pVal->bitcount = 24;
			pVal->idata = (LPBYTE)m_bitmapData.Scan0;
			*/

			return S_OK;
		}
		STDMETHOD(UnlockBits)()
		{
			//m_pBitmap->UnlockBits(&m_bitmapData);

			return S_OK;
		}
	};

	class ATL_NO_VTABLE CInputPin : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLPinImpl,
		public ILMemInputPin
	{
	public:
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
			STDMETHOD(GetBuffer)(DWORD /*dwBytes*/, ILMediaSample* *pVal)
			{
				EnterCriticalSection(&m_pInputPin->m_pLock);

				CComObject<CVideoSample>* pSample;
				CComObject<CVideoSample>::CreateInstance(&pSample);
				pSample->AddRef();

				CComQIPtr<ILVideoMediaType> videoType = m_pInputPin->m_mediaType;
				long width;
				long height;
				videoType->GetWidth(&width);
				videoType->GetHeight(&height);

				pSample->m_lpBmi = (BITMAPINFOHEADER*)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER));

				pSample->m_lpBmi->biSize = sizeof(BITMAPINFOHEADER);
				pSample->m_lpBmi->biWidth = width;
				pSample->m_lpBmi->biHeight = height;
				pSample->m_lpBmi->biBitCount = 24;
				pSample->m_lpBmi->biPlanes = 1;
				pSample->m_lpBmi->biCompression = BI_RGB;

				pSample->m_rowbytes = ROWBYTES(pSample->m_lpBmi->biWidth, pSample->m_lpBmi->biBitCount);

				pSample->m_hBitmap = CreateDIBSection(NULL, (BITMAPINFO*)pSample->m_lpBmi, DIB_RGB_COLORS, (void**)&pSample->m_bits, NULL, 0);

			//	pSample->m_pBitmap = new Gdiplus::Bitmap(width, height, PixelFormat24bppRGB);

				*pVal = pSample;

				LeaveCriticalSection(&m_pInputPin->m_pLock);

				return S_OK;
			}
		};

		CInputPin()
		{
			m_direction = LPINDIR_INPUT;
			m_pFilter = NULL;

			m_pSample = NULL;
		}

		int FinalConstruct()
		{
			CComObject<CMemAllocator>::CreateInstance(&m_pAllocator);
			m_pAllocator->AddRef();
			m_pAllocator->m_pInputPin = this;

			InitializeCriticalSection(&m_pLock);

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

		CRITICAL_SECTION m_pLock;

		CMoviePlayerFilter* m_pFilter;

		ILVideoMediaType* m_mediaType;

		CComObject<CMemAllocator>* m_pAllocator;

		CVideoSample* m_pSample;

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
			CComQIPtr<ILVideoMediaType> videoType = pMediaType;
			m_mediaType = videoType;

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
		STDMETHOD(Receive)(ILMediaSample *pSample);
	};

	CMoviePlayerFilter()
	{
		m_pMoviePlayer = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLBaseFilterImpl::FinalConstruct();
		if (FAILED(hr)) return hr;

		CComObject<CInputPin>::CreateInstance(&m_pInput);
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);

		return 0;
	}

	void FinalRelease()
	{
		CLBaseFilterImpl::FinalRelease();
	}

	CComObject<CInputPin>* m_pInput;

	CLXMoviePlayerCtl* m_pMoviePlayer;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMoviePlayerFilter)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
	COM_INTERFACE_ENTRY(ILMediaSeeking)
END_COM_MAP()

// ILMediaSeeking
	STDMETHOD(Seek)(double seconds)
	{
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
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
		return S_OK;
	}

	STDMETHOD(GetDuration)(double *pVal)
	{
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->GetDuration(pVal);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CLXMoviePlayerCtl
class ATL_NO_VTABLE CLXMoviePlayerCtl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ILXMoviePlayerCtl, &IID_ILXMoviePlayerCtl, &LIBID_LXMOVIEPLAYERLib>,
	public CComControl<CLXMoviePlayerCtl>,
	public IPersistStreamInitImpl<CLXMoviePlayerCtl>,
	public IPersistPropertyBagImpl<CLXMoviePlayerCtl>,
	public IOleControlImpl<CLXMoviePlayerCtl>,
	public IOleObjectImpl<CLXMoviePlayerCtl>,
	public IOleInPlaceActiveObjectImpl<CLXMoviePlayerCtl>,
	public IViewObjectExImpl<CLXMoviePlayerCtl>,
	public IOleInPlaceObjectWindowlessImpl<CLXMoviePlayerCtl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLXMoviePlayerCtl>,
	public IPersistStorageImpl<CLXMoviePlayerCtl>,
	public ISpecifyPropertyPagesImpl<CLXMoviePlayerCtl>,
	public IQuickActivateImpl<CLXMoviePlayerCtl>,
	public IDataObjectImpl<CLXMoviePlayerCtl>,
	public IProvideClassInfo2Impl<&CLSID_LXMoviePlayerCtl, &DIID__ILXMoviePlayerCtlEvents, &LIBID_LXMOVIEPLAYERLib>,
	public IPropertyNotifySinkCP<CLXMoviePlayerCtl>,
	public CComCoClass<CLXMoviePlayerCtl, &CLSID_LXMoviePlayerCtl>
{
public:

	CLXMoviePlayerCtl() : m_cwnd("static", this, 1)
	{
		m_pFilter = NULL;
		m_duration = 0;

		m_dragging = 0;
	}

	int FinalConstruct()
	{
		m_cwnd.Create(NULL, CRect(0,0,0,0), NULL, WS_POPUP);
		ATLASSERT(m_cwnd.m_hWnd);
		if (m_cwnd.m_hWnd == NULL)
			return E_FAIL;

		return 0;
	}

	void FinalRelease()
	{
	}

	CComBSTR m_src;

	CComObject<CMoviePlayerFilter>* m_pFilter;

	CComPtr<ILFilterGraph> m_filterGraph;

	CContainedWindow m_cwnd;

	CRect m_videoRect;
	CRect m_playRect;
	CRect m_sliderRect;
	CRect m_knobRect;

	double m_duration;

	int m_dragging;

DECLARE_REGISTRY_RESOURCEID(IDR_LXMOVIEPLAYERCTL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXMoviePlayerCtl)
	COM_INTERFACE_ENTRY(ILXMoviePlayerCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IPersistPropertyBag)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CLXMoviePlayerCtl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("src", 8/*DISPID_ACTIVEDOCUMENT_SRC*/, CLSID_NULL/*clsid*/)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CLXMoviePlayerCtl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CLXMoviePlayerCtl)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)

	CHAIN_MSG_MAP(CComControl<CLXMoviePlayerCtl>)
	DEFAULT_REFLECTION_HANDLER()

	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_USER+100, OnReceiveVideoSample)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnReceiveVideoSample(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
		return 0;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_ILXMoviePlayerCtl,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (ATL::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ILXMoviePlayerCtl
public:
	STDMETHOD(get_src)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_src)(/*[in]*/ BSTR newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di);
};

#endif //__LXMOVIEPLAYERCTL_H_
