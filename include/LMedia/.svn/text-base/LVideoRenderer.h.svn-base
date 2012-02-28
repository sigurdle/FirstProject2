#ifndef __LVIDEORENDERER_H_
#define __LVIDEORENDERER_H_

//#include "resource.h"       // main symbols

#if 0

#include "LMediaImpl.h"

#include <ddraw.h>
#pragma comment(lib, "ddraw.lib")

namespace LMedia
{

class CLVideoRenderer : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CLVideoRenderer, &CLSID_LVideoRenderer>,
	public ILVideoRenderer,
	public CLBaseFilterImpl,
	public ILBasicVideo,
	public ILMediaSeeking,
	public CWindowImpl<CLVideoRenderer>
{
public:

class CMemAllocator;
class CInputPin;

class CBuffer
{
public:
	CBuffer()
	{
		m_bFree = TRUE;
		m_pMemAllocator = NULL;
	}

	BOOL m_bFree;

	CMemAllocator* m_pMemAllocator;

	CComPtr<IDirectDrawSurface7> m_ddsurf;

	HRESULT LockBits(LSampleData *pVal)
	{
		DDSURFACEDESC2	sd = {0};
		sd.dwSize = sizeof(sd);
		HRESULT hr = m_ddsurf->Lock(NULL/*rect*/, &sd, DDLOCK_WRITEONLY | DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL);
		if (FAILED(hr))
			return hr;
		
		pVal->width = sd.dwWidth;
		pVal->height = sd.dwHeight;
		pVal->rowbytes = sd.lPitch;
		pVal->bitcount = sd.ddpfPixelFormat.dwRGBBitCount;
		pVal->idata = (LPBYTE)sd.lpSurface;

		return S_OK;
	}
	
	HRESULT UnlockBits()
	{
		HRESULT hr = m_ddsurf->Unlock(NULL);
		//m_pBitmap->UnlockBits(&m_bitmapData);

		return hr;
	}
};

class ATL_NO_VTABLE CVideoSample : 
	public CLMediaSampleImpl<ILVideoSample>
{
public:
	CVideoSample()
	{
		m_pBuffer = NULL;
	}

	void FinalRelease()
	{
		if (m_pBuffer)
		{
			m_pBuffer->m_pMemAllocator->ReleaseBuffer(this);
		}
	}

	CBuffer* m_pBuffer;

public:

	STDMETHOD(GetMediaType)(LMediaType* *pVal)
	{
		*pVal = NULL;
		return S_OK;
	}

	STDMETHOD(LockBits)(LSampleData *pVal)
	{
		if (m_pBuffer)
		{
			return m_pBuffer->LockBits(pVal);
		}
		else
		{
			ATLASSERT(0);
			return E_FAIL;
		}
	}
	STDMETHOD(UnlockBits)()
	{
		if (m_pBuffer)
		{
			return m_pBuffer->UnlockBits();
		}
		else
		{
			ATLASSERT(0);
			return E_FAIL;
		}
	}

	virtual ULONG __stdcall GetActualDataLength()
	{
		return 0;	// TODO ??
	}
	virtual HRESULT __stdcall SetActualDataLength(ULONG length)
	{
		return E_NOTIMPL;
	}
};

class ATL_NO_VTABLE CMemAllocator : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public ILMemAllocator
{
public:
	CMemAllocator()
	{
		m_pInputPin = NULL;
	}

	CInputPin* m_pInputPin;

	CArray<CBuffer*,CBuffer*> m_buffers;

public:
	STDMETHOD(GetBuffer)(DWORD /*dwBytes*/, ILMediaSample* *pVal)
	{
		EnterCriticalSection(&m_pInputPin->m_pLock);

		CVideoSample* pSample = new CVideoSample;

		for (int i = 0; i < m_buffers.GetSize(); i++)
		{
			if (m_buffers[i]->m_bFree)
			{
				m_buffers[i]->m_bFree = FALSE;
				pSample->m_pBuffer = m_buffers[i];

				*pVal = pSample;

				LeaveCriticalSection(&m_pInputPin->m_pLock);

				return S_OK;
			}
		}

		CBuffer* pBuffer = new CBuffer;
		pBuffer->m_pMemAllocator = this;
		pBuffer->m_bFree = FALSE;
		m_buffers.Add(pBuffer);

		pSample->m_pBuffer = pBuffer;

//		CComQIPtr<ILVideoMediaType> videoType = m_pInputPin->m_mediaType;
		long width;
		long height;
//		videoType->GetWidth(&width);
//		videoType->GetHeight(&height);
		width = ((LVIDEOINFOHEADER2*)m_pInputPin->m_mt->pbFormat)->bmiHeader.biWidth;
		height = ((LVIDEOINFOHEADER2*)m_pInputPin->m_mt->pbFormat)->bmiHeader.biHeight;

		//pBuffer->m_ddsurf = m_pInputPin->m_ddsurf;
		//if (pBuffer->m_ddsurf == NULL)	// Try to create a non-overlay surface
		HRESULT hr;
		{
			DDSURFACEDESC2 sd = {0};
			sd.dwSize = sizeof(sd);
			sd.dwFlags = 0;
			sd.dwFlags |= DDSD_WIDTH | DDSD_HEIGHT;
			//sd.dwFlags |= DDSD_BACKBUFFERCOUNT;
			sd.dwFlags |= DDSD_CAPS;
			//sd.dwFlags |= DDSD_PIXELFORMAT;

			sd.dwWidth = width;
			sd.dwHeight = height;
			sd.dwBackBufferCount = 1;

			if (sd.dwFlags & DDSD_PIXELFORMAT)
			{
				sd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
				sd.ddpfPixelFormat.dwFlags = DDPF_RGB;
				sd.ddpfPixelFormat.dwRGBBitCount = 24;
				sd.ddpfPixelFormat.dwRBitMask = 0xff;
				sd.ddpfPixelFormat.dwGBitMask = 0x00ff;
				sd.ddpfPixelFormat.dwBBitMask = 0x0000ff;
			}

			sd.ddsCaps.dwCaps = 0;//DDSCAPS_FLIP;// | DDSCAPS_COMPLEX;// | DDSCAPS_VIDEOMEMORY;

			hr = m_pInputPin->m_pFilter->m_dd->CreateSurface(&sd, &pBuffer->m_ddsurf, NULL);

			if (FAILED(hr))
			{
				// Try to create it in system memory?
				ATLASSERT(0);
			}
		}

		*pVal = pSample;

		LeaveCriticalSection(&m_pInputPin->m_pLock);

		return S_OK;
	}

	STDMETHOD(ReleaseBuffer)(ILMediaSample* pBuffer)
	{
		CVideoSample* pVideoSample = static_cast<CVideoSample*>(pBuffer);
		ATLASSERT(pVideoSample->m_pBuffer->m_bFree == FALSE);

		pVideoSample->m_pBuffer->m_bFree = TRUE;
		pVideoSample->m_pBuffer = NULL;

		return S_OK;
	}
};

class CInputPin : 
	public CLBasePinImpl,
	public ILMemInputPin
{
public:

	CInputPin() : CLBasePinImpl(LPINDIR_INPUT)
	{
		m_pSample = NULL;

		m_pAllocator = new CMemAllocator;
		m_pAllocator->m_pInputPin = this;

		InitializeCriticalSection(&m_pLock);
	}

	~CInputPin()
	{
		if (m_pAllocator)
		{
			delete m_pAllocator;
			m_pAllocator = NULL;
		}
	}

	CRITICAL_SECTION m_pLock;

	CLVideoRenderer* m_pFilter;

	//ILVideoMediaType* m_mediaType;

	CMemAllocator* m_pAllocator;

	CVideoSample* m_pSample;

	CComPtr<IDirectDrawSurface7> m_ddprimsurf;
	CComPtr<IDirectDrawSurface7> m_ddsurf;
	CComPtr<IDirectDrawSurface7> m_ddoverlaysurf;

	virtual HRESULT CheckMediaType(const CLMediaType &mt)
	{
		if (mt->majortype != LMEDIATYPE_Video)
			return E_FAIL;

		if (mt->subtype != GUID_NULL)	// TODO
			return E_FAIL;

		return S_OK;
	}

	virtual HRESULT CompleteConnect(ILPin* pConnector)
	{
		HRESULT hr;
		hr = CLBasePinImpl::CompleteConnect(pConnector);
		if (FAILED(hr)) return hr;

		//CComQIPtr<ILVideoMediaType> videoType = pMediaType;
		//m_mediaType = videoType;

		long width;
		long height;
		width = ((LVIDEOINFOHEADER2*)m_mt->pbFormat)->bmiHeader.biWidth;
		height = ((LVIDEOINFOHEADER2*)m_mt->pbFormat)->bmiHeader.biHeight;

		//m_mediaType->GetWidth(&width);
		//m_mediaType->GetHeight(&height);

		hr = m_pFilter->m_dd->SetCooperativeLevel(NULL, DDSCL_NORMAL);
		if (FAILED(hr))
			return hr;

		// Get primary surface
		{
			DDSURFACEDESC2  sd;
			memset(&sd, 0, sizeof(sd));
			sd.dwSize = sizeof(sd);
			sd.dwFlags = DDSD_CAPS;
			sd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
			hr = m_pFilter->m_dd->CreateSurface(&sd, &m_ddprimsurf, NULL);
			if (FAILED(hr))
				return hr;

			m_ddprimsurf->GetSurfaceDesc(&sd);

			m_ddprimsurf->SetClipper(m_pFilter->m_ddclipper);
		}

		if (m_pFilter->m_bUseOverlay)
		{
			if ((m_pFilter->m_capsDrv.dwCaps & DDCAPS_OVERLAY))
			{
				DDSURFACEDESC2 sd = {0};
				sd.dwSize = sizeof(sd);
				sd.dwFlags = 0;
				sd.dwFlags |= DDSD_WIDTH | DDSD_HEIGHT;
				sd.dwFlags |= DDSD_BACKBUFFERCOUNT;
				sd.dwFlags |= DDSD_CAPS;
				sd.dwFlags |= DDSD_PIXELFORMAT;

				sd.dwWidth = width;
				sd.dwHeight = height;
				sd.dwBackBufferCount = 1;

				if (sd.dwFlags & DDSD_PIXELFORMAT)
				{
					sd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
					sd.ddpfPixelFormat.dwFlags = DDPF_RGB;
					sd.ddpfPixelFormat.dwRGBBitCount = 24;//32;
					sd.ddpfPixelFormat.dwRBitMask = 0xff;
					sd.ddpfPixelFormat.dwGBitMask = 0x00ff;
					sd.ddpfPixelFormat.dwBBitMask = 0x0000ff;
				}

				sd.ddsCaps.dwCaps = DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_OVERLAY | DDSCAPS_VIDEOMEMORY;

				hr = m_pFilter->m_dd->CreateSurface(&sd, &m_ddoverlaysurf, NULL);
				m_ddsurf = m_ddoverlaysurf;
			}
		}

#if 0
		if (m_ddsurf == NULL)	// Try to create a non-overlay surface
		{
			DDSURFACEDESC2 sd = {0};
			sd.dwSize = sizeof(sd);
			sd.dwFlags = 0;
			sd.dwFlags |= DDSD_WIDTH | DDSD_HEIGHT;
			//sd.dwFlags |= DDSD_BACKBUFFERCOUNT;
			sd.dwFlags |= DDSD_CAPS;
			//sd.dwFlags |= DDSD_PIXELFORMAT;

			sd.dwWidth = width;
			sd.dwHeight = height;
			sd.dwBackBufferCount = 1;

			if (sd.dwFlags & DDSD_PIXELFORMAT)
			{
				sd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
				sd.ddpfPixelFormat.dwFlags = DDPF_RGB;
				sd.ddpfPixelFormat.dwRGBBitCount = 24;
				sd.ddpfPixelFormat.dwRBitMask = 0xff;
				sd.ddpfPixelFormat.dwGBitMask = 0x00ff;
				sd.ddpfPixelFormat.dwBBitMask = 0x0000ff;
			}

			sd.ddsCaps.dwCaps = 0;//DDSCAPS_FLIP;// | DDSCAPS_COMPLEX;// | DDSCAPS_VIDEOMEMORY;

			hr = m_pFilter->m_dd->CreateSurface(&sd, &m_ddsurf, NULL);

			if (FAILED(hr))
			{
				// Try to create it in system memory?
				ATLASSERT(0);
			}
		}
#endif

		if (FAILED(hr))
			return hr;

		if (m_ddoverlaysurf)
		{
			CRect rect(0, 0, width, height);
			hr = m_ddoverlaysurf->UpdateOverlay(&rect, m_ddprimsurf, &rect, DDOVER_SHOW, NULL);
		}

		return S_OK;
	}

	ILBaseFilter* QueryFilter() const
	{
		return m_pFilter;
	}

// ILMemInputPin
	ILMemAllocator* GetAllocator()
	{
		return m_pAllocator;
	}
	bool Receive(ILMediaSample *pSample)
	{
		EnterCriticalSection(&m_pLock);
		/*

		while (1)
		{
			EnterCriticalSection(&m_pFilter->m_pLock);
			if (m_pFilter->m_state == LState_Running)
				break;
			LeaveCriticalSection(&m_pFilter->m_pLock);
		}
		LeaveCriticalSection(&m_pFilter->m_pLock);

		*/

		LONGLONG timeStart;
		LONGLONG timeEnd;
		pSample->GetTime(&timeStart, &timeEnd);

	// Wait until it's time to display the sample
		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, timeStart/*streamTime*/, hEvent, NULL);
		WaitForSingleObject(hEvent, INFINITE);

		CloseHandle(hEvent);

		if (m_pSample)
		{
			//m_pSample->Release();
			delete m_pSample;
			m_pSample = NULL;
		}

		m_pSample = static_cast<CVideoSample*>(pSample);
	//	m_pSample->AddRef();

		if (m_pFilter->m_hWnd)
		{
			m_pFilter->PostMessage(WM_USER+100, 0, 0);
		}

		LeaveCriticalSection(&m_pLock);

		return true;
	}
};

	CLVideoRenderer()
	{
		memset(&m_capsDrv, 0, sizeof(m_capsDrv));

		m_pInput = NULL;

		m_hOwner = NULL;
		m_style = WS_OVERLAPPED | WS_VISIBLE;
		m_rect = CRect(0,0,0,0);

		m_bUseOverlay = FALSE;

		m_pInput = new CInputPin;
		m_pInput->m_pFilter = this;
		m_pInput->m_id = L"Video Input";
		AddPin(m_pInput);

		HRESULT hr;

		CComPtr<IDirectDraw> dd;
		hr = DirectDrawCreate(NULL, &dd, NULL);
		if (FAILED(hr)) THROW(-1);
		
		hr = dd->QueryInterface(IID_IDirectDraw7, (void**)&m_dd);
		if (FAILED(hr)) THROW(-1);

		hr = m_dd->CreateClipper(0, &m_ddclipper, NULL);
		if (FAILED(hr)) THROW(-1);

		m_capsDrv.dwSize = sizeof(m_capsDrv);
		hr = dd->GetCaps(&m_capsDrv, NULL);
		if (FAILED(hr))
			THROW(-1);
	}

	~CLVideoRenderer()
	{
		m_dd.Release();
	}

	CInputPin* m_pInput;

	CComPtr<IDirectDraw7> m_dd;
	CComPtr<IDirectDrawClipper> m_ddclipper;
	DDCAPS m_capsDrv;

	BOOL m_bUseOverlay;

BEGIN_MSG_MAP(CLVideoRenderer)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_USER+100, OnDisplaySample)
	MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_ddclipper->SetHWnd(0, m_hWnd);

		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_ddclipper->SetHWnd(0, NULL);
		return 0;
	}

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPaintDC dc(m_hWnd);

#if 0
		if (m_pInput->m_sample)//->m_ddsurf)
		{
			CRect rect;
			GetWindowRect(&rect);
			m_pInput->m_ddprimsurf->Blt(&rect, m_pInput->m_sample->m_pBuffer->ddsurf, NULL/*srcRect*/, 0, NULL);
		}
#endif

		OnDisplaySample(0,0,0, bHandled);

		return 0;
	}

	LRESULT OnDisplaySample(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
	//	Invalidate();
		if (m_pInput->m_pSample)//->m_ddsurf)
		{
			ATLASSERT(m_pInput->m_pSample->m_pBuffer);

			CRect rect;
			GetWindowRect(&rect);
			m_pInput->m_ddprimsurf->Blt(&rect, m_pInput->m_pSample->m_pBuffer->m_ddsurf, NULL/*srcRect*/, 0, NULL);
		}

		return 0;
	}

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return TRUE;
	}

	LRESULT OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LPWINDOWPOS lpwp = (LPWINDOWPOS)lParam;

		CRect rect;
		GetWindowRect(&rect);

		if (m_pInput->m_ddoverlaysurf)
		{
			m_pInput->m_ddoverlaysurf->SetOverlayPosition(rect.left, rect.top);
		}

		return 0;
	}

// ILVideoRenderer
public:

	DWORD m_style;
	CRect m_rect;
	HWND m_hOwner;

// ILMediaSeeking
	STDMETHOD(Seek)(LONGLONG t)
	{
		ILMediaSeeking* peerSeeking = dynamic_cast<ILMediaSeeking*>(m_pInput->m_connectedTo);
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->Seek(t);
	}

	STDMETHOD(GetCurrentPosition)(LONGLONG *pVal)
	{
		/*
		CComQIPtr<ILMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->Seek(seconds);
		*/
		return S_OK;
	}

	HRESULT GetDuration(LONGLONG *pVal)
	{
		ILMediaSeeking* peerSeeking = dynamic_cast<ILMediaSeeking*>(m_pInput->m_connectedTo);
		if (peerSeeking == NULL)
			return E_NOINTERFACE;

		return peerSeeking->GetDuration(pVal);
	}

// IBasicVideo
	STDMETHOD(set_WindowStyle)(/*[in]*/ long newVal)
	{
		m_style = newVal;
		if (m_hWnd)
		{
			SetWindowLong(GWL_STYLE, m_style);
		}
		return S_OK;
	}

	STDMETHOD(set_Owner)(/*[in]*/ ULONG_PTR newVal)
	{
		if (newVal)
		{
			if (!::IsWindow((HWND)newVal))
				return E_FAIL;
		}

		m_hOwner = (HWND)newVal;

		if (m_hWnd == NULL)
		{
			HWND hWnd = Create(m_hOwner, m_rect, NULL, m_style, 0);
			if (hWnd == NULL)
				return E_FAIL;
		}
		else
		{
			SetParent(m_hOwner);
		}

		return S_OK;
	}

	STDMETHOD(SetRect)(/*[in]*/ RECT rect)
	{
		m_rect = rect;
		if (m_hWnd)
		{
			MoveWindow(&m_rect, TRUE);
			return S_OK;
		}
		return S_OK;
	}
};

}	// LMedia

#endif

#endif //__LVIDEORENDERER_H_
