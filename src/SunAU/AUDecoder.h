// AUDecoder.h : Declaration of the CAUDecoder

#ifndef __AUDECODER_H_
#define __AUDECODER_H_

#include "resource.h"       // main symbols

#include "aufmt.h"

/////////////////////////////////////////////////////////////////////////////
// CAUDecoder
class ATL_NO_VTABLE CAUDecoder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAUDecoder, &CLSID_AUDecoder>,
	public IAUDecoder,

	public CLBaseFilterImpl
{
public:
	class ATL_NO_VTABLE CInputPin : 
		public CComObjectRootEx<CComSingleThreadModel>,
		public CLPinImpl
		//public ILMemInputPin
	{
	public:
		CInputPin()
		{
			m_direction = LPINDIR_INPUT;
			m_pFilter = NULL;
		}

		CAUDecoder* m_pFilter;

		CComQIPtr<ILByteStream> m_stream;

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

		STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType)
		{
			m_connectedTo = pConnector;
			m_stream = m_connectedTo;
			if (m_stream == NULL) return E_FAIL;
			return m_pFilter->m_pAudioOut->Parse();
		}
	};

	class ATL_NO_VTABLE CAudioOut : 
		public CComObjectRootEx<CComSingleThreadModel>,
	//	public ILAudio,
		public CLPinImpl,
		public ILMediaSeeking
	{
	public:
		class ATL_NO_VTABLE CAudioMediaType :
			public CComObjectRootEx<CComSingleThreadModel>,
			public ILAudioMediaType	// ILMediaType
		{
		public:
			CAudioMediaType()
			{
				m_pAudioOut = NULL;
			}

			CAudioOut* m_pAudioOut;

		//	WAVEFORMATEX m_wavfmt;

			BEGIN_COM_MAP(CAudioMediaType)
				COM_INTERFACE_ENTRY(ILMediaType)
				COM_INTERFACE_ENTRY(ILAudioMediaType)
			END_COM_MAP()

		public:
			STDMETHOD(GetType)(long *pVal)
			{
				*pVal = 2;	// Audio
				return S_OK;
			}
			STDMETHOD(GetFormat)(WAVEFORMATEX* pVal)
			{
				pVal->wFormatTag = WAVE_FORMAT_PCM;
				pVal->nChannels = m_pAudioOut->m_hdr.channels;
				pVal->wBitsPerSample = m_pAudioOut->m_wBitsPerSample;
				pVal->nSamplesPerSec = m_pAudioOut->m_hdr.sampleRate;
				pVal->nBlockAlign = m_pAudioOut->m_nBlockAlign;
				pVal->cbSize = 0;

			/*
				pVal->wFormatTag = WAVE_FORMAT_PCM;
				pVal->nChannels = m_pAudioOut->m_nChannels;
				pVal->wBitsPerSample = m_pAudioOut->m_sxhd.SampleDepth;
				pVal->nSamplesPerSec = m_pAudioOut->m_sxhd.PlayFreq;
				pVal->nBlockAlign = m_pAudioOut->m_nBlockAlign;
				pVal->cbSize = 0;
				*/

				return S_OK;
			}

			STDMETHOD(GetSamples)(ULONG *pVal)
			{
				*pVal = 2000;//m_pAudioOut->m_hdr.sampleRate*4;	// 4 seconds
				return S_OK;
			}
		};

		CAudioOut()
		{
			m_direction = LPINDIR_OUTPUT;

			m_pFilter = NULL;
			//m_file = NULL;

			/*
			memset(&m_sxhd, 0, sizeof(m_sxhd));
			m_nChannels = 0;
			m_nBlockAlign = 0;
			m_nSamples = 0;
			*/
		}

		CAUDecoder* m_pFilter;

		CComPtr<ILMemAllocator> m_allocator;

		CComObject<CAudioMediaType>* m_pMediaType;

		AuHeader m_hdr;
		int m_wBitsPerSample;
		int m_nBlockAlign;
		ULONG m_nSamples;
		/*
		AnimSoundHeader m_sxhd;
		WORD m_nChannels;
		WORD m_nBlockAlign;

		LONGLONG m_nSamples;

		CUPtrList m_audioChunks;
		*/

		/*
		void Init();

		HRESULT ReadChunk(CAudioChunk* f, LPSTR buffer, ULONG startSample, ULONG nsamples);
		*/

		HRESULT Parse();

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CAudioOut)
		COM_INTERFACE_ENTRY(ILMediaSeeking)
		COM_INTERFACE_ENTRY(ILPin)
	END_COM_MAP()

	public:

		STDMETHOD(QueryFilter)(ILBaseFilter* *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = m_pFilter;
			(*pVal)->AddRef();
			return S_OK;
		}

		STDMETHOD(Connect)(ILPin* pReceivePin, ILMediaType* mediaType)
		{
			if (pReceivePin == NULL) return E_POINTER;
			if (m_connectedTo != NULL) return E_UNEXPECTED;	// Already connected

			//CComPtr<ILMediaType> mediaType;
			//GetMediaType(&mediaType);

			CComQIPtr<ILMemInputPin> memInput = pReceivePin;
			if (memInput)
			{
				memInput->GetAllocator(&m_allocator);
			}

			HRESULT hr = pReceivePin->ReceiveConnection(this, m_pMediaType);
			if (SUCCEEDED(hr))
			{
				m_connectedTo = pReceivePin;
			}

			return hr;
		}

	// ILAudio
		STDMETHOD(GetSamples)(LONGLONG *pVal);
		STDMETHOD(GetChunkSize)(long nchunk, ULONG* pVal);
		STDMETHOD(ReadChunk)(long nchunk, LPSTR buffer, ULONG nsamples);

		STDMETHOD(GetStreamType)(LStreamType *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = LStreamType_Audio;
			return S_OK;
		}

	// ILMediaSeeking
		STDMETHOD(Seek)(double seconds);
		STDMETHOD(GetCurrentPosition)(double* pVal);
		STDMETHOD(GetDuration)(double* pVal);
	};

	CAUDecoder()
	{
//		m_nSamples = 0;

		m_hAudioThread = NULL;
		m_audioThreadId = 0L;
	}

	int FinalConstruct()
	{
		CLBaseFilterImpl::FinalConstruct();

		CComObject<CInputPin>::CreateInstance(&m_pInput);
		m_pInput->m_pFilter = this;
		AddPin(m_pInput);

		CComObject<CAudioOut>::CreateInstance(&m_pAudioOut);
		m_pAudioOut->m_pFilter = this;
		AddPin(m_pAudioOut);

		return 0;
	}

	void FinalRelease()
	{
		CLBaseFilterImpl::FinalRelease();
	}

	CComObject<CInputPin>* m_pInput;
	CComObject<CAudioOut>* m_pAudioOut;

	HANDLE m_hAudioThread;
	DWORD m_audioThreadId;

	//CComPtr<IStream> m_stream;

DECLARE_REGISTRY_RESOURCEID(IDR_AUDECODER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAUDecoder)
	COM_INTERFACE_ENTRY(IAUDecoder)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()

// IAUDecoder
public:
// ILMediaFilter
	STDMETHOD(Run)(double tStart);
	STDMETHOD(Stop)();

// ILMediaLoader
	/*
	STDMETHOD(Open)(IStream *stream);

	STDMETHOD(EnumStreams)(IEnumUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		return S_OK;
	}

	STDMETHOD(GetVideo)(ILVideo* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		return S_OK;
	}
	STDMETHOD(GetAudio)(ILAudio* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = this;
		(*pVal)->AddRef();
		return S_OK;
	}

// ILMediaSeeking
	STDMETHOD(Seek)(double seconds);
	STDMETHOD(GetDuration)(double* pVal);

// ILAudio
	STDMETHOD(GetStreamType)(LStreamType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = LStreamType_Audio;
		return S_OK;
	}

	STDMETHOD(GetSamples)(LONGLONG *pVal);
	STDMETHOD(GetFormat)(WAVEFORMATEX *pVal);
	STDMETHOD(GetChunkSize)(long nchunk, ULONG* pVal);
	STDMETHOD(ReadChunk)(long nchunk, LPSTR buffer, ULONG nsamples);
*/
};

#endif //__AUDECODER_H_
