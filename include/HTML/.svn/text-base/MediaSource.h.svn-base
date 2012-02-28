namespace System
{
namespace Web
{

class HTMLEXT MediaSource
{
public:

#if 0
	class HTMLEXT VideoFilter :
	//	public CComObjectRootEx<CComSingleThreadModel>,
		public MediaShow::BaseFilterImpl,
		public MediaShow::IMediaSeeking
	{
	public:
		class HTMLEXT VideoSample : 
	//		public CComObjectRootEx<CComSingleThreadModel>,
			public MediaShow::MediaSampleImpl<MediaShow::IMediaSample>
		{
		public:
			CTOR VideoSample()
			{
				m_pBitmap = NULL;
			}

			Graphics::Bitmap* m_pBitmap;
			Graphics::BitmapData m_bitmapData;

		//	CComPtr<ILMediaType> m_mediaType;

			/*
		DECLARE_PROTECT_FINAL_CONSTRUCT()

		BEGIN_COM_MAP(CVideoSample)
			COM_INTERFACE_ENTRY(ILMediaSample)
		//	COM_INTERFACE_ENTRY(ILVideoSample)
		END_COM_MAP()
		*/

		public:
			ErrorCode LockBits(MediaShow::LSampleData* pVal)
			{
				ASSERT(0);
#if 0
				if (m_pBitmap->LockBits(
					&Gdiplus::Rect(0, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight()),
					Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite,
					PixelFormat24bppRGB, &m_bitmapData) == 0)
				{
					pVal->width = m_bitmapData.Width;
					pVal->height = m_bitmapData.Height;
					pVal->bitcount = 24;
					pVal->rowbytes = m_bitmapData.Stride;
					pVal->idata = (LPBYTE)m_bitmapData.Scan0;

					return S_OK;
				}
				else
#endif
					return Error;
			}

			ErrorCode UnlockBits()
			{
				ASSERT(0);
#if 0
				m_pBitmap->UnlockBits(&m_bitmapData);
#endif
				return Success;
			}

			/*
			STDMETHOD(GetMediaType)(ILMediaType* *pVal)
			{
				*pVal = m_mediaType;
				return S_OK;
			}
			*/

			/*
			STDMETHOD(GetPalette)(ILPalette* *pVal)
			{
				if (pVal == NULL) return E_POINTER;
				*pVal = NULL;
				return S_OK;
			}
			*/
		};

		class HTMLEXT InputPin : 
		//	public CComObjectRootEx<CComSingleThreadModel>,
			public MediaShow::BasePinImpl,
			public MediaShow::IMemInputPin
		{
		public:
			class MemAllocator : 
			//	public CComObjectRootEx<CComSingleThreadModel>,
				public MediaShow::IMemAllocator
			{
			public:
				CTOR MemAllocator()
				{
					m_pInputPin = NULL;
				}

				InputPin* m_pInputPin;

				/*
			DECLARE_PROTECT_FINAL_CONSTRUCT()

			BEGIN_COM_MAP(CMemAllocator)
				COM_INTERFACE_ENTRY(ILMemAllocator)
			END_COM_MAP()
			*/

			public:
				ErrorCode GetBuffer(ULONG /*dwBytes*/, MediaShow::IMediaSample* *pVal)
				{
					CriticalSectionLock lock (m_pInputPin->m_pLock);

					VideoSample* pSample = NULL;//new CVideoSample;
					//CVideoSample>::CreateInstance(&pSample);

					ASSERT(0);
#if 0
					CComQIPtr<ILVideoMediaType> videoType = m_pInputPin->m_mediaType;
					long width;
					long height;
					videoType->GetWidth(&width);
					videoType->GetHeight(&height);

					/*
					pSample->m_lpBmi = (BITMAPINFOHEADER*)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER));

					pSample->m_lpBmi->biSize = sizeof(BITMAPINFOHEADER);
					pSample->m_lpBmi->biWidth = width;
					pSample->m_lpBmi->biHeight = height;
					pSample->m_lpBmi->biBitCount = 24;
					pSample->m_lpBmi->biPlanes = 1;
					pSample->m_lpBmi->biCompression = BI_RGB;

					pSample->m_rowbytes = ROWBYTES(pSample->m_lpBmi->biWidth, pSample->m_lpBmi->biBitCount);

					pSample->m_hBitmap = CreateDIBSection(NULL, (BITMAPINFO*)pSample->m_lpBmi, DIB_RGB_COLORS, (void**)&pSample->m_bits, NULL, 0);
					*/

					pSample->m_pBitmap = new Gdiplus::Bitmap(width, height, PixelFormat24bppRGB);

					*pVal = pSample;
#endif

				//	m_pInputPin->m_pLock.Unlock();

					return Success;
				}
				ErrorCode ReleaseBuffer(MediaShow::IMediaSample* pBuffer)
				{
					ASSERT(0);
					return Success;
				}
			};

			CTOR InputPin() : BasePinImpl(MediaShow::PINDIR_INPUT)
			{
				m_pFilter = NULL;

				m_pSample = NULL;

				m_pAllocator = new MemAllocator;
				m_pAllocator->m_pInputPin = this;
			}

			/*
			void FinalRelease()
			{
				if (m_pAllocator)
				{
					m_pAllocator->Release();
					m_pAllocator = NULL;
				}
			}
			*/

			CriticalSection m_pLock;

			VideoFilter* m_pFilter;

			//ILVideoMediaType* m_mediaType;

			MemAllocator* m_pAllocator;

			VideoSample* m_pSample;

			virtual ErrorCode CheckMediaType(MediaShow::MediaType* mt)
			{
				ASSERT(0);
#if 0
				if (mt->GetMajorType() != LMEDIATYPE_Video)
					return Error;
#endif
				return Success;
			}

		public:
			MediaShow::IBaseFilter* QueryFilter() const
			{
				return m_pFilter;
			}

		// ILMemInputPin
			MediaShow::IMemAllocator* GetAllocator()
			{
				return m_pAllocator;
			}
			ErrorCode Receive(MediaShow::IMediaSample *pSample)
			{
				CriticalSectionLock lock (m_pLock);

				LONGLONG timeStart;
				LONGLONG timeEnd;
				pSample->GetTime(&timeStart, &timeEnd);

#if 0
				HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

				m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, timeStart/*streamTime*/, hEvent, NULL);

				WaitForSingleObject(hEvent, INFINITE);

				CloseHandle(hEvent);
#endif

				m_pSample = static_cast<VideoSample*>(pSample);

			//	m_pFilter->m_pMoviePlayer->m_cwnd.PostMessage(WM_USER+100, 0, 0);

			//	m_pLock.Unlock();

				return Success_True;
			}
		};

		CTOR VideoFilter()
		{
			m_pInput = new InputPin;
			m_pInput->m_pFilter = this;
			AddPin(m_pInput);
		}

		InputPin* m_pInput;

		MediaSource* m_pMediaSource;

		ErrorCode GetBitmap(Graphics::Bitmap** pVal);

	public:
	// ILMediaSeeking
		ErrorCode Seek(LONGLONG t)
		{
			ASSERT(0);
			return 0;
#if 0
			CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
			if (peerSeeking == NULL)
				return E_NOINTERFACE;
			return peerSeeking->Seek(t);
#endif
		}

		ErrorCode GetCurrentPosition(LONGLONG *pVal)
		{
			/*
			CComQIPtr<ILMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
			if (peerSeeking == NULL)
				return E_NOINTERFACE;

			return peerSeeking->Seek(seconds);
			*/
			return Success;
		}

		ErrorCode GetDuration(LONGLONG *pVal)
		{
			ASSERT(0);
			return 0;
#if 0
			CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
			if (peerSeeking == NULL)
				return E_NOINTERFACE;

			return peerSeeking->GetDuration(pVal);
#endif
		}
	};

	class HTMLEXT AudioFilter :
	//	public CComObjectRootEx<CComSingleThreadModel>,
		public MediaShow::BaseFilterImpl,
		public MediaShow::IMediaSeeking
	{
	public:
		class HTMLEXT InputPin : 
		//	public CComObjectRootEx<CComSingleThreadModel>,
			public MediaShow::BasePinImpl,
			public MediaShow::IMemInputPin
		{
		public:
			class HTMLEXT MemAllocator : 
			//	public CComObjectRootEx<CComSingleThreadModel>,
				public MediaShow::IMemAllocator
			{
			public:
				class HTMLEXT AudioSample : 
				//	public CComObjectRootEx<CComSingleThreadModel>,
					public MediaShow::MediaSampleImpl<MediaShow::IMediaSample>
				{
				public:
					CTOR AudioSample()
					{
						m_pointer = NULL;
					}

					void FinalRelease()
					{
						if (m_pointer)
						{
							delete m_pointer;
							m_pointer = NULL;
						}
					}

				//	CComPtr<ILMediaType> m_mediaType;

					uint8* m_pointer;
					ULONG m_dwBytes;

				public:
					ErrorCode LockBits(MediaShow::LSampleData* pData)
					{
						pData->idata = m_pointer;
						return Success;
					}

					ErrorCode UnlockBits()
					{
						return Success;
					}

					/*
					STDMETHOD(GetMediaType)(ILMediaType* *pVal)
					{
						*pVal = m_mediaType;
						return S_OK;
					}
					*/
				};

				CTOR MemAllocator()
				{
					m_pInputPin = NULL;
				}

				InputPin* m_pInputPin;

			public:
				ErrorCode GetBuffer(ULONG dwBytes, MediaShow::IMediaSample* *pVal)
				{
					CriticalSectionLock lock (m_pInputPin->m_pLock);

					ASSERT(0);
					AudioSample* pSample = NULL;//new CAudioSample;
					//CComObject<CAudioSample>::CreateInstance(&pSample);

					//ULONG nSamples;
					//m_pInputPin->m_mediaType->GetSamples(&nsamples);

#ifndef __LERSTAD__
					pSample->m_pointer = new uint8[dwBytes];
#endif
					pSample->m_dwBytes = dwBytes;

					*pVal = pSample;

				//	m_pInputPin->m_pLock.Unlock();

					return Success;
				}
				ErrorCode ReleaseBuffer(MediaShow::IMediaSample* pBuffer)
				{
					ASSERT(0);
					return Success;
				}
			};

			CTOR InputPin() : BasePinImpl(MediaShow::PINDIR_INPUT)
			{
				m_pFilter = NULL;

		//		m_pSample = NULL;

				m_nSample = 0;

				m_pAllocator = new MemAllocator;
				m_pAllocator->m_pInputPin = this;
			}

			/*
			void FinalRelease()
			{
				if (m_pAllocator)
				{
					m_pAllocator->Release();
					m_pAllocator = NULL;
				}
			}
			*/

			CriticalSection m_pLock;

			AudioFilter* m_pFilter;

		//	ILAudioMediaType* m_mediaType;

			MemAllocator* m_pAllocator;

			//CAudioSample* m_pSample;

			ULONG m_nSample;

			virtual ErrorCode CheckMediaType(const MediaShow::MediaType* mt)
			{
				ASSERT(0);
#if 0
				if (mt->GetMajorType() != LMEDIATYPE_Audio)
					return Error;
#endif
				return Success;
			}

		public:
			MediaShow::IBaseFilter* QueryFilter() const
			{
				return m_pFilter;
			}

		// ILMemInputPin
			MediaShow::IMemAllocator* GetAllocator()
			{
				return m_pAllocator;
			}
			ErrorCode Receive(MediaShow::IMediaSample *pSample);
		};

		class HTMLEXT OutputPin : 
		//	public CComObjectRootEx<CComSingleThreadModel>,
		//	public ILAudio,
			public MediaShow::BaseOutputPinImpl,
			public MediaShow::IMediaSeeking
		{
		public:
#if 0
			class CAudioMediaType :
				public CComObjectRootEx<CComSingleThreadModel>,
				public ILAudioMediaType	// ILMediaType
			{
			public:
				CAudioMediaType()
				{
					m_pOutput = NULL;
				}

				OutputPin* m_pOutput;

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
					m_pOutput->m_pFilter->m_pInput->m_mediaType->GetFormat(pVal);
					/*
					pVal->wFormatTag = WAVE_FORMAT_PCM;
					pVal->nChannels = m_pAudioOut->m_hdr.channels;
					pVal->wBitsPerSample = m_pAudioOut->m_wBitsPerSample;
					pVal->nSamplesPerSec = m_pAudioOut->m_hdr.sampleRate;
					pVal->nBlockAlign = m_pAudioOut->m_nBlockAlign;
					pVal->cbSize = 0;
					*/

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
					return m_pOutput->m_pFilter->m_pInput->m_mediaType->GetSamples(pVal);
					//*pVal = 2000;//m_pAudioOut->m_hdr.sampleRate*4;	// 4 seconds
					return S_OK;
				}
			};
#endif

			CTOR OutputPin()
			{
			//	m_direction = LPINDIR_OUTPUT;

				m_pFilter = NULL;
				//m_file = NULL;

				/*
				memset(&m_sxhd, 0, sizeof(m_sxhd));
				m_nChannels = 0;
				m_nBlockAlign = 0;
				m_nSamples = 0;
				*/
			}

			AudioFilter* m_pFilter;

			MediaShow::IMemAllocator* m_allocator;

		//	CComObject<CAudioMediaType>* m_pMediaType;

		//	AuHeader m_hdr;
		//	int m_wBitsPerSample;
		//	int m_nBlockAlign;
		//	ULONG m_nSamples;
			/*
			AnimSoundHeader m_sxhd;
			WORD m_nChannels;
			WORD m_nBlockAlign;

			LONGLONG m_nSamples;

			CUPtrList m_audioChunks;
			*/

			/*
			void Init();

			ErrorCode ReadChunk(CAudioChunk* f, LPSTR buffer, ULONG startSample, ULONG nsamples);
			*/

			//ErrorCode Parse();

			virtual ErrorCode CheckMediaType(const MediaShow::MediaType& mt)
			{
				ASSERT(0);
#if 0
				if (mt.GetMajorType() != LMEDIATYPE_Audio)
					return Error;
#endif
				return Success;
			}

		public:

			MediaShow::IBaseFilter* QueryFilter() const
			{
				return m_pFilter;
			}

			ErrorCode Connect(MediaShow::IPin* pReceivePin, MediaShow::MediaType* mediaType)
			{
				ASSERT(0);
				return 0;
#if 0
				if (pReceivePin == NULL) return E_POINTER;
				if (m_connectedTo != NULL) return E_UNEXPECTED;	// Already connected

				//CComPtr<ILMediaType> mediaType;
				//GetMediaType(&mediaType);

				CComQIPtr<ILMemInputPin> memInput = pReceivePin;
				if (memInput)
				{
					memInput->GetAllocator(&m_allocator);
				}

				ASSERT(0);
				return E_FAIL;
#if 0
				ErrorCode hr = pReceivePin->ReceiveConnection(this, m_pMediaType);
				if (SUCCEEDED(hr))
				{
					m_connectedTo = pReceivePin;
				}

				return hr;
#endif
#endif
			}

		// ILMediaSeeking
			ErrorCode Seek(LONGLONG t)
			{
				ASSERT(0);
				return 0;
#if 0
				CComQIPtr<ILMediaSeeking> peerSeeking = m_pFilter->m_pInput->m_connectedTo;
				if (peerSeeking == NULL)
					return E_NOINTERFACE;

				return peerSeeking->Seek(t);
#endif
			}

			ErrorCode GetCurrentPosition(LONGLONG *pVal)
			{
				return Success;
			}

			ErrorCode GetDuration(LONGLONG *pVal)
			{
				ASSERT(0);
				return 0;
#if 0
				CComQIPtr<ILMediaSeeking> peerSeeking = m_pFilter->m_pInput->m_connectedTo;
				if (peerSeeking == NULL)
					return E_NOINTERFACE;

				return peerSeeking->GetDuration(pVal);
#endif
			}
		};

		CTOR AudioFilter()
		{
			m_pInput = NULL;
			m_pOutput = NULL;

			m_pElement = NULL;

			ASSERT(0);
			/*
			CComObject<InputPin>::CreateInstance(&m_pInput);
			m_pInput->m_pFilter = this;
			AddPin(m_pInput);

			CComObject<OutputPin>::CreateInstance(&m_pOutput);
			m_pOutput->m_pFilter = this;
			AddPin(m_pOutput);
			*/
		}

		InputPin* m_pInput;
		OutputPin* m_pOutput;

		MediaSource* m_pMediaSource;

		ElementTime* m_pElement;

public:
	// IMediaSeeking
		ErrorCode Seek(LONGLONG t)
		{
			ASSERT(0);
			return 0;
#if 0
			CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
			if (peerSeeking == NULL)
				return E_NOINTERFACE;
			return peerSeeking->Seek(t);
#endif
		}

		ErrorCode GetCurrentPosition(LONGLONG *pVal)
		{
			/*
			CComQIPtr<ILMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
			if (peerSeeking == NULL)
				return E_NOINTERFACE;

			return peerSeeking->Seek(seconds);
			*/
			return Success;
		}

		ErrorCode GetDuration(LONGLONG *pVal)
		{
			ASSERT(0);
			return 0;
#if 0
			CComQIPtr<ILMediaSeeking> peerSeeking = m_pInput->m_connectedTo;
			if (peerSeeking == NULL)
				return E_NOINTERFACE;

			return peerSeeking->GetDuration(pVal);
#endif
		}
	};
#endif

	CTOR MediaSource()
	{
		/*
		m_pVideoFilter = NULL;
		m_pAudioFilter = NULL;

		m_wavFormat = NULL;	// TODO remove
		m_wavBuffer = NULL;	// TODO remove
		m_nSamples = 0;	// TODO remove
		*/
	}

//	VideoFilter* m_pVideoFilter;
//	AudioFilter* m_pAudioFilter;

	void LoadFile(StringIn filename);
	void Seek(double simpleTime);

	DShow::VideoPlayer* m_pVideo;
};

}	// Web
}	// System
