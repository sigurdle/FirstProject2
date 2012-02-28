// LACMWrapper.h : Declaration of the CLACMWrapper

#ifndef __LACMWRAPPER_H_
#define __LACMWRAPPER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLACMWrapper
class ATL_NO_VTABLE CLACMWrapper : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLACMWrapper, &CLSID_LACMWrapper>,
	public ILACMWrapper,
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

			m_has = NULL;

		//	m_bInit = FALSE;
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

		//BOOL m_bInit;

		CLACMWrapper* m_pFilter;

//		ILMediaType* m_mediaType;	// TODO AddRef??

		CComObject<CMemAllocator>* m_pAllocator;

		HACMSTREAM m_has;
		ACMSTREAMHEADER m_ash;

		virtual HRESULT CheckMediaType(const CLMediaType &mt);
		virtual HRESULT SetMediaType(const LMediaType* pmt);
		//virtual HRESULT CompleteConnect(ILPin* pPin);
		virtual void BreakConnect();

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
		//STDMETHOD(ReceiveConnection)(ILPin* pConnector, LMediaType* pmt);
		STDMETHOD(EndOfStream)();

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

	class ATL_NO_VTABLE COutputPin :
		public CComObjectRootEx<CComSingleThreadModel>,

		public CLBaseOutputPinImpl,
		public ILMediaSeeking
	{
	public:

		COutputPin()
		{
			m_pFilter = NULL;
		}

		int FinalConstruct()
		{
			return 0;
		}

		void FinalRelease()
		{
		}

		CLACMWrapper* m_pFilter;

		virtual HRESULT CheckMediaType(const CLMediaType &mt)
		{
			if (mt->majortype != LMEDIATYPE_Audio)
				return E_FAIL;

			return S_OK;
		}

		virtual HRESULT GetMediaType(int iPosition, LMediaType* *pMediaType)
		{
			if (iPosition == 0)
			{
				CLMediaType mediaType;
				mediaType.Create(sizeof(WAVEFORMATEX)+m_pFilter->m_pwfxDst->cbSize);

				memcpy(mediaType->pbFormat, m_pFilter->m_pwfxDst, sizeof(WAVEFORMATEX)+m_pFilter->m_pwfxDst->cbSize);

				mediaType->majortype = LMEDIATYPE_Audio;
				mediaType->subtype = GUID_NULL,

				*pMediaType = mediaType.Detach();

				return S_OK;
			}
			else
			{
				pMediaType = NULL;
				return S_FALSE;
			}
		}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(COutputPin)
		COM_INTERFACE_ENTRY(ILPin)
		COM_INTERFACE_ENTRY(ILMediaSeeking)
	END_COM_MAP()

	// ILPin
		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}

	// ILMediaSeeking
		STDMETHOD(Seek)(LONGLONG seconds)
		{
			ATLASSERT(0);
			return E_NOTIMPL;
		}
		STDMETHOD(GetDuration)(LONGLONG* pVal)
		{
			if (pVal == NULL) return E_POINTER;
			//*pVal = (double)((LONGLONG)m_pAVIStream->m_aviStreamHeader.dwLength * m_pAVIStream->m_aviStreamHeader.dwScale / m_pAVIStream->m_aviStreamHeader.dwRate);

			return S_OK;
		}
		STDMETHOD(GetCurrentPosition)(LONGLONG* pVal)
		{
			ATLASSERT(0);
			return E_NOTIMPL;
		}
	};

	CLACMWrapper()
	{
		m_pwfxSrc = NULL;
		m_pwfxDst = NULL;

		m_pInputPin = NULL;
		m_pOutputPin = NULL;
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

		hr = CComObject<COutputPin>::CreateInstance(&m_pOutputPin);
		if (FAILED(hr)) return hr;
		m_pOutputPin->m_pFilter = this;
		m_pOutputPin->m_id = L"Audio Output";
		AddPin(m_pOutputPin);

		return 0;
	}

	void FinalRelease()
	{
		CLBaseFilterImpl::FinalRelease();
	}

	CComObject<CInputPin>* m_pInputPin;
	CComObject<COutputPin>* m_pOutputPin;

	LPWAVEFORMATEX m_pwfxSrc;
	LPWAVEFORMATEX m_pwfxDst;

DECLARE_REGISTRY_RESOURCEID(IDR_LACMWRAPPER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLACMWrapper)
	COM_INTERFACE_ENTRY(ILACMWrapper)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()

// ILACMWrapper
public:
};

#endif //__LACMWRAPPER_H_
