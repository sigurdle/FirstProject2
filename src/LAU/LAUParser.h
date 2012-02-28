// LAUParser.h : Declaration of the CLAUParser

#ifndef __LAUPARSER_H_
#define __LAUPARSER_H_

#include "resource.h"       // main symbols

#include "aufmt.h"

/////////////////////////////////////////////////////////////////////////////
// CLAUParser
class ATL_NO_VTABLE CLAUParser : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CLAUParser, &CLSID_LAUParser>,
	public ILAUParser,
	public CLBaseFilterImpl	// ILMediaFilter
{
public:
	class ATL_NO_VTABLE CInputPin : 
		public CComObjectRootEx<CComMultiThreadModel>,
		public CLBasePinImpl
	{
	public:
		CInputPin() : CLBasePinImpl(LPINDIR_INPUT)
		{
			m_pFilter = NULL;
		}

		CLAUParser* m_pFilter;
		CComPtr<ILByteStream> m_stream;

		AuHeader m_hdr;
		int m_wBitsPerSample;
		int m_nBlockAlign;
		ULONG m_nSamples;

		virtual HRESULT CheckConnect(ILPin* pPin)
		{
			// Call base class first
			HRESULT hr = CLBasePinImpl::CheckConnect(pPin);
			if (FAILED(hr)) return hr;

			CComQIPtr<ILByteStream> stream = pPin;
			if (stream == NULL) return E_NOINTERFACE;

			m_stream = stream;

			return S_OK;
		}

		virtual void BreakConnect()
		{
			// Release what we obtained in CheckConnect
			m_stream = NULL;
		}

		virtual HRESULT CheckMediaType(const CLMediaType& mt)
		{
			if (mt->majortype != LMEDIATYPE_Stream)
				return E_FAIL;

			return S_OK;
		}

		virtual HRESULT CompleteConnect(ILPin *pPin);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputPin)
		COM_INTERFACE_ENTRY(ILPin)
	END_COM_MAP()

		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}
	};

	class ATL_NO_VTABLE COutputPin :
		public CComObjectRootEx<CComMultiThreadModel>,
		public CLBaseOutputPinImpl,
		public ILMediaSeeking
	{
	public:
		COutputPin()
		{
			m_pFilter = NULL;

			m_threadId = 0;
			m_hThread = NULL;
		}

		int FinalConstruct()
		{
			return 0;
		}

		void FinalRelease()
		{
		}

		CLAUParser* m_pFilter;

		//WAVEFORMATEX m_wfx;
		//int m_compression;

		DWORD m_threadId;
		HANDLE m_hThread;

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
				mediaType.Create(sizeof(WAVEFORMATEX));

				LPWAVEFORMATEX wfx = (LPWAVEFORMATEX)mediaType->pbFormat;
				wfx->wFormatTag = WAVE_FORMAT_PCM;
				wfx->nChannels = (WORD)m_pFilter->m_pInputPin->m_hdr.channels;
				wfx->nSamplesPerSec = m_pFilter->m_pInputPin->m_hdr.sampleRate;
				wfx->nBlockAlign = m_pFilter->m_pInputPin->m_nBlockAlign;
				wfx->wBitsPerSample = m_pFilter->m_pInputPin->m_wBitsPerSample;
				wfx->nAvgBytesPerSec = wfx->nSamplesPerSec*wfx->nBlockAlign;
				wfx->cbSize = 0;

				//memcpy(mediaType->pbFormat, &m_wfx, sizeof(WAVEFORMATEX)+m_wfx.cbSize);

				mediaType->majortype = LMEDIATYPE_Audio;
				mediaType->subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

				*pMediaType = mediaType.Detach();

				return S_OK;
			}
			else
			{
				*pMediaType = NULL;
				return S_FALSE;
			}
		}

		virtual HRESULT Run(LONGLONG tStart);

		static DWORD WINAPI AudioRunProc(LPVOID lpParameter);

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
		STDMETHOD(Seek)(LONGLONG t)
		{
			ATLASSERT(0);
			return E_NOTIMPL;
		}
		STDMETHOD(GetDuration)(LONGLONG* pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter->m_pInputPin->m_nSamples * LTIME_SCALE / m_pFilter->m_pInputPin->m_hdr.sampleRate;
			return S_OK;
		}
		STDMETHOD(GetCurrentPosition)(LONGLONG* pVal)
		{
			ATLASSERT(0);
			return E_NOTIMPL;
		}
	};

	CLAUParser()
	{
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
		m_pInputPin->m_id = L"Stream Input";
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

DECLARE_REGISTRY_RESOURCEID(IDR_LAUPARSER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLAUParser)
	COM_INTERFACE_ENTRY(ILAUParser)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()

// ILAUParser
public:
};

#endif //__LAUPARSER_H_
