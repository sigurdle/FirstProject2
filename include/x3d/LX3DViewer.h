// LX3DViewer.h : Declaration of the CLX3DViewer

#ifndef __LX3DVIEWER_H_
#define __LX3DVIEWER_H_

#include "resource.h"       // main symbols
//#include <atlctl.h>

//class CLSAIScene;

class CLX3DViewer;

//class CLViewpoint;

class CMoviePlayerFilter : 
	//public CComObjectRootEx<CComSingleThreadModel>,
	public CLBaseFilterImpl,
	public ILMediaSeeking
{
public:
	class CVideoSample : 
		//public CComObjectRootEx<CComSingleThreadModel>,
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

		/*
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CVideoSample)
		COM_INTERFACE_ENTRY(ILMediaSample)
		COM_INTERFACE_ENTRY(ILVideoSample)
	END_COM_MAP()
	*/

	public:

		/*
		STDMETHOD(GetMediaType)(ILMediaType* *pVal)
		{
			return S_OK;
		}
		*/
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

		STDMETHOD(LockBits)(LSampleData *pVal)
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

	class CInputPin : 
	//	public CComObjectRootEx<CComSingleThreadModel>,
		public CLBasePinImpl,
		public ILMemInputPin
	{
	public:
		class CMemAllocator : 
		//	public CComObjectRootEx<CComSingleThreadModel>,
			public ILMemAllocator
		{
		public:
			CMemAllocator()
			{
				m_pInputPin = NULL;
			}

			CInputPin* m_pInputPin;

			/*
		DECLARE_PROTECT_FINAL_CONSTRUCT()

		BEGIN_COM_MAP(CMemAllocator)
			COM_INTERFACE_ENTRY(ILMemAllocator)
		END_COM_MAP()
		*/

		public:
			STDMETHOD(GetBuffer)(DWORD /*dwBytes*/, ILMediaSample* *pVal)
			{
#if 0
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
#endif

				return S_OK;
			}
			STDMETHOD(ReleaseBuffer)(ILMediaSample* pBuffer)
			{
				return E_NOTIMPL;
			}
		};

		CInputPin() : CLBasePinImpl(LPINDIR_INPUT)
		{
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

//		CMoviePlayerFilter* m_pFilter;

		//ILVideoMediaType* m_mediaType;

		CComObject<CMemAllocator>* m_pAllocator;

		CVideoSample* m_pSample;

		virtual HRESULT CheckMediaType(const CLMediaType &mt)
		{
			ATLASSERT(0);
			return E_FAIL;
		}

		/*
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputPin)
		COM_INTERFACE_ENTRY(ILPin)
		COM_INTERFACE_ENTRY(ILMemInputPin)
	END_COM_MAP()
	*/

	public:
		inline CMoviePlayerFilter* GetFilter()
		{
			return (CMoviePlayerFilter*)m_pFilter;
		}

		STDMETHOD(ReceiveConnection)(ILPin* pConnector, LMediaType* pmt)
		{
			CLBasePinImpl::ReceiveConnection(pConnector, pmt);
			//CComQIPtr<ILVideoMediaType> videoType = pMediaType;
			//m_mediaType = videoType;

			return S_OK;
		}

	// ILMemInputPin
		STDMETHOD(GetAllocator)(ILMemAllocator* *ppAllocator)
		{
			return E_NOTIMPL;
#if 0
			if (ppAllocator == NULL) return E_POINTER;
			*ppAllocator = m_pAllocator;
			(*ppAllocator)->AddRef();
			return S_OK;
#endif
		}
		bool Receive(ILMediaSample *pSample);
	};

	CMoviePlayerFilter()
	{
		m_pMoviePlayer = NULL;

		m_pInput = new CInputPin;
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);
	}

	CInputPin* m_pInput;

	CLX3DViewer* m_pMoviePlayer;

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMoviePlayerFilter)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
	COM_INTERFACE_ENTRY(ILMediaSeeking)
END_COM_MAP()
*/

// ILMediaSeeking
	STDMETHOD(Seek)(double seconds)
	{
	return E_NOTIMPL;
#if 0
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->Seek(seconds);
#endif
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
		return E_NOTIMPL;
		/*

		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->GetDuration(pVal);
		*/
	}
};

class CPlayerSlider
{
protected:
	double m_maxpos;
	double m_pos;

	CRect m_rect;
	CRect m_knobRect;
	int m_knobWidth;

	int m_dragging;
	int m_offset;

	void UpdateKnobRect()
	{
		int width = m_rect.Width()-4;

		double unitWidth = (width-m_knobWidth) / m_maxpos;
		int x = m_knobWidth/2+(m_pos * unitWidth);

		m_knobRect.SetRect(1+x-m_knobWidth/2, 1, 1+x+m_knobWidth/2, m_rect.Height()-1);
	}

	double PosFromClientX(int x)
	{
		int width = m_rect.Width()-4;
		double unitWidth = (width-m_knobWidth) / m_maxpos;
		double pos = (x-m_rect.left)/unitWidth;

		return pos;
	}

public:
	CPlayerSlider()
	{
		m_maxpos = 100;
		m_pos = 0;
		m_dragging = 0;

		m_knobWidth = 16;
	}

	void SetRect(const RECT& rect)
	{
		m_rect = rect;

		UpdateKnobRect();
	}

	CRect GetRect()
	{
		return m_rect;
	}

	void SetMaxPos(double maxpos)
	{
		ATLASSERT(maxpos != 0);

		if (m_maxpos != maxpos)
		{
			m_maxpos = maxpos;
			UpdateKnobRect();
		}
	}

	void SetPos(double pos)
	{
		if (pos < 0) pos = 0;
		else if (pos > m_maxpos) pos = m_maxpos;

		if (m_pos != pos)
		{
			m_pos = pos;
			UpdateKnobRect();
		}
	}

	void Enable(BOOL bEnable)
	{
		// TODO
	}

	double GetPos()
	{
		return m_pos;
	}

	int OnLButtonDown(CPoint point)
	{
		point.Offset(-m_rect.left, -m_rect.top);

		if (!m_dragging)
		{
			m_dragging = 1;

			if (m_knobRect.PtInRect(point))
			{
				m_offset = point.x-m_knobRect.left;
				return 1;
			}
			else
			{
				SetPos(PosFromClientX(point.x));
				return 2;
			}
		}

		return 0;
	}

	int OnMouseMove(CPoint point)
	{
		point.Offset(-m_rect.left, -m_rect.top);

		if (m_dragging)
		{
			double pos = PosFromClientX(point.x-m_offset);
			SetPos(pos);

			return TRUE;
		}

		return FALSE;
	}

	int OnLButtonUp(CPoint point)
	{
		if (m_dragging)
		{
			m_dragging = 0;
		}
		return 0;
	}

	void Draw(HDC hDC)
	{
		CDCHandle dc(hDC);

		dc.FillSolidRect(&m_rect, RGB(230, 230, 230));

		CRect rect = m_knobRect;
		rect.OffsetRect(m_rect.left, m_rect.top);
		rect.top += 2;
		rect.bottom -= 2;
		dc.Draw3dRect(rect, RGB(200, 200, 210), RGB(20,20,30));

		rect.InflateRect(-1,-1);
		dc.FillSolidRect(rect, RGB(210, 210, 210));
	}
};

/////////////////////////////////////////////////////////////////////////////
// CLX3DViewer
class ATL_NO_VTABLE CLX3DViewer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ILX3DViewer, &IID_ILX3DViewer, &LIBID_LX3DLib>,
	public CComControl<CLX3DViewer>,
	public IPersistStreamInitImpl<CLX3DViewer>,
	public IOleControlImpl<CLX3DViewer>,
	public IOleObjectImpl<CLX3DViewer>,
	public IOleInPlaceActiveObjectImpl<CLX3DViewer>,
	public IViewObjectExImpl<CLX3DViewer>,
	public IOleInPlaceObjectWindowlessImpl<CLX3DViewer>,
	public IConnectionPointContainerImpl<CLX3DViewer>,
	public IPersistStorageImpl<CLX3DViewer>,
	public ISpecifyPropertyPagesImpl<CLX3DViewer>,
	public IQuickActivateImpl<CLX3DViewer>,
	public IDataObjectImpl<CLX3DViewer>,
	public IProvideClassInfo2Impl<&CLSID_LX3DViewer, &DIID__ILX3DViewerEvents, &LIBID_LX3DLib>,
	public IPropertyNotifySinkCP<CLX3DViewer>,
	public CComCoClass<CLX3DViewer, &CLSID_LX3DViewer>,

	public IPersistPropertyBagImpl<CLX3DViewer>,

	public IObjectSafety,

	public ILSAIBrowser
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC, -1/*COLOR_BTNFACE*/)

	CLX3DViewer()
	{
//		m_scene = NULL;
//		m_pFilter = NULL;

		m_nTimerID = 0;
		m_threadID = 0;
		m_hThread = NULL;

		m_frameRate = 8;
		m_currentVideoTime = 0;

		m_duration = 0;

		m_nRunTimer = 0;

		m_dragging = 0;

#if 0
		m_hDC = NULL;
		m_hBitmap = NULL;
		m_hOldBitmap = NULL;
#endif

		m_bWindowOnly = TRUE;	//
	}

	int FinalConstruct();
	void FinalRelease();

//	CComPtr<ILSAIScene> m_scene;
//	CComObject<CLSAIScene>* m_scene;	// TODO Remove

//	CComPtr<IMP4File> m_file;	// TODO remove

//	CComObject<CMoviePlayerFilter>* m_pFilter;

	CLFilterGraph* m_filterGraph;

	CPlayerSlider m_slider;

	CComBSTR m_src;

	UINT m_nRunTimer;

	int m_dragging;

#if 0
	HDC m_hDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
#endif

	UINT m_nTimerID;
	DWORD m_threadID;
	HANDLE m_hThread;

	double m_frameRate;
	double m_currentVideoTime;

	CComPtr<ILBasicVideo> m_basicVideo;

	//CRect m_sliderRect;
	//CRect m_knobRect;

	double m_duration;
	double m_currentPosition;

	HRESULT StartPlay();



BEGIN_MSG_MAP(CLX3DViewer)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)

	COMMAND_ID_HANDLER(ID_BROWSER_DISPLAY_SMOOTH, OnBrowserDisplaySmooth)
	COMMAND_ID_HANDLER(ID_BROWSER_DISPLAY_FLAT, OnBrowserDisplayFlat)
	COMMAND_ID_HANDLER(ID_BROWSER_DISPLAY_WIREFRAME, OnBrowserDisplayWireframe)
	COMMAND_ID_HANDLER(ID_BROWSER_DISPLAY_POINTS, OnBrowserDisplayPoints)
	COMMAND_ID_HANDLER(ID_BROWSER_HEADLIGHT, OnBrowserHeadlight)

	MESSAGE_HANDLER(WM_USER+100, OnAdvance)

	CHAIN_MSG_MAP(CComControl<CLX3DViewer>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//
	LRESULT OnBrowserDisplaySmooth(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBrowserDisplayFlat(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBrowserDisplayWireframe(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBrowserDisplayPoints(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBrowserHeadlight(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnAdvance(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	HRESULT OnDraw(ATL_DRAWINFO& di);
	HRESULT OnPostVerbInPlaceActivate();

// ILX3DViewer
public:
	STDMETHOD(replaceWorld)(/*[in]*/ ILX3DScene* scene);
	STDMETHOD(get_src)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_src)(/*[in]*/ BSTR newVal);

// ILSAIBrowser
	STDMETHOD(createX3DFromStream)(IStream* stream, /*[out,retval]*/ ILX3DScene* *pVal);
	STDMETHOD(getCurrentSpeed)(/*[out,retval]*/ double *pVal);

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
};

#endif //__LX3DVIEWER_H_
