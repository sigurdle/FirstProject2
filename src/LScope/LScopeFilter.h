// LScopeFilter.h : Declaration of the CLScopeFilter

#ifndef __LSCOPEFILTER_H_
#define __LSCOPEFILTER_H_

#include "resource.h"       // main symbols

class ATL_NO_VTABLE CLScopeWindow : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IUnknown,
	public CWindowImpl<CLScopeWindow>
{
public:
	CLScopeWindow()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLScopeWindow)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()

BEGIN_MSG_MAP(CLScopeWindow)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CLScopeFilter
class ATL_NO_VTABLE CLScopeFilter : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CLScopeFilter, &CLSID_LScopeFilter>,
	public IDispatchImpl<ILScopeFilter, &IID_ILScopeFilter, &LIBID_LSCOPELib>,
	public CLBaseFilterImpl	// ILMediaFilter
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

			m_pointer = NULL;
			m_dwBytes = 0;
			m_dwActualBytes = 0;
		}

		~CBuffer()
		{
			if (m_pointer)
			{
				GlobalFree(m_pointer);
				m_pointer = NULL;
			}
		}

		BOOL m_bFree;
		CMemAllocator* m_pMemAllocator;

		LPBYTE m_pointer;
		DWORD m_dwBytes;
		DWORD m_dwActualBytes;
	};

	class ATL_NO_VTABLE CSample : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLMediaSampleImpl<ILMediaSample>
	{
	public:
		CSample()
		{
			//m_mediaType = NULL;
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

		CInputPin* m_pInput;
		//ILMediaType* m_mediaType;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CSample)
		COM_INTERFACE_ENTRY(ILMediaSample)
	END_COM_MAP()

	public:
		STDMETHOD(LockBits)(LSampleData* pVal)
		{
			if (m_pBuffer)
			{
				pVal->idata = m_pBuffer->m_pointer;
				return S_OK;
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
				return S_OK;
			}
			else
			{
				ATLASSERT(0);
				return E_FAIL;
			}
		}

		/*
		STDMETHOD(GetMediaType)(ILMediaType **pVal)
		{
			*pVal = m_mediaType;
			(*pVal)->AddRef();
			return S_OK;
		}
		*/

		virtual ULONG __stdcall GetActualDataLength()
		{
			if (m_pBuffer)
			{
				return m_pBuffer->m_dwBytes;
			}
			else
			{
				ATLASSERT(0);
				return 0;
			}
		}
		virtual HRESULT __stdcall SetActualDataLength(ULONG length)
		{
			if (m_pBuffer)
			{
				if (length > m_pBuffer->m_dwBytes)
				{
					return VFW_E_BUFFER_OVERFLOW;
				}

				m_pBuffer->m_dwActualBytes = length;

				return S_OK;
			}
			else
			{
				ATLASSERT(0);
				return E_FAIL;
			}
		}
	};

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

		CArray<CBuffer*,CBuffer*> m_buffers;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CMemAllocator)
		COM_INTERFACE_ENTRY(ILMemAllocator)
	END_COM_MAP()

	public:
		STDMETHOD(GetBuffer)(DWORD dwBytes, ILMediaSample* *pVal)
		{
			EnterCriticalSection(&m_pInputPin->m_pLock);

			CComObject<CSample>* pSample;
			CComObject<CSample>::CreateInstance(&pSample);
			pSample->AddRef();

			/*
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
			*/

			CBuffer* pBuffer = new CBuffer;
			pBuffer->m_pMemAllocator = this;
			pBuffer->m_bFree = FALSE;
			m_buffers.Add(pBuffer);

			pBuffer->m_pointer = (LPBYTE)GlobalAlloc(0, dwBytes);
			pBuffer->m_dwBytes = dwBytes;

			pSample->m_pBuffer = pBuffer;

			*pVal = pSample;

			LeaveCriticalSection(&m_pInputPin->m_pLock);
			return S_OK;
		}

		STDMETHOD(ReleaseBuffer)(ILMediaSample* pBuffer)
		{
			CSample* pSample = static_cast<CSample*>(pBuffer);
			ATLASSERT(pSample->m_pBuffer->m_bFree == FALSE);

			pSample->m_pBuffer->m_bFree = TRUE;
			pSample->m_pBuffer = NULL;
			return S_OK;
		}
	};

	class ATL_NO_VTABLE CInputPin : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLBasePinImpl,
		public ILMemInputPin
	{
	public:
		CInputPin() : CLBasePinImpl(LPINDIR_INPUT)
		{
			m_pFilter = NULL;

			m_duration = LTIME_SCALE * 0.1;
		}

		int FinalConstruct()
		{
			CComObject<CMemAllocator>::CreateInstance(&m_pAllocator);
			m_pAllocator->AddRef();
			m_pAllocator->m_pInputPin = this;

			CComObject<CLScopeWindow>::CreateInstance(&m_pWindow);
			m_pWindow->AddRef();

			InitializeCriticalSection(&m_pLock);

			return 0;
		}

		void FinalRelease()
		{
			if (m_pWindow)
			{
				m_pWindow->Release();
				m_pWindow = NULL;
			}

			if (m_pAllocator)
			{
				m_pAllocator->Release();
				m_pAllocator = NULL;
			}
		}

		LONGLONG m_duration;
		char* m_buffer;

		CComObject<CLScopeWindow>* m_pWindow;

		CRITICAL_SECTION m_pLock;

		CLScopeFilter* m_pFilter;

		CComObject<CMemAllocator>* m_pAllocator;

		virtual HRESULT CheckMediaType(const CLMediaType &mt)
		{
			if (mt->majortype != LMEDIATYPE_Audio)
				return E_FAIL;

			if (mt->subtype != GUID_NULL)	// TODO
				return E_FAIL;

			LPWAVEFORMATEX pwfx = (LPWAVEFORMATEX)mt->pbFormat;
			if (pwfx->wFormatTag != WAVE_FORMAT_PCM)
				return E_FAIL;

			return S_OK;
		}
		//virtual HRESULT SetMediaType(const LMediaType* pmt);
		virtual HRESULT CompleteConnect(ILPin* pPin)
		{
			LPWAVEFORMATEX pwfx = (LPWAVEFORMATEX)m_mt->pbFormat;

			m_buffer = (char*)GlobalAlloc(GMEM_ZEROINIT, pwfx->nSamplesPerSec * m_duration / LTIME_SCALE);

			return 0;
		}

		//virtual void BreakConnect();

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputPin)
		COM_INTERFACE_ENTRY(ILPin)
		COM_INTERFACE_ENTRY(ILMemInputPin)
	END_COM_MAP()

		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}
		//STDMETHOD(EndOfStream)();

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

	CLScopeFilter()
	{
		m_pInputPin = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLBaseFilterImpl::FinalConstruct();
		if (FAILED(hr)) return hr;

		hr = CComObject<CInputPin>::CreateInstance(&m_pInputPin);
		if (FAILED(hr)) return hr;
		m_pInputPin->m_pFilter = this;
		m_pInputPin->m_id = L"Audio Input";
		AddPin(m_pInputPin);

		return 0;
	}

	void FinalRelease()
	{
		CLBaseFilterImpl::FinalRelease();
	}

	CComObject<CInputPin>* m_pInputPin;

DECLARE_REGISTRY_RESOURCEID(IDR_LSCOPEFILTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLScopeFilter)
	COM_INTERFACE_ENTRY(ILScopeFilter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()

// ILScopeFilter
public:
};

#endif //__LSCOPEFILTER_H_
