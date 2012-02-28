#pragma once

//#include "resource.h"       // main symbols

#include "IFFILBM.h"

namespace System
{
namespace MediaShow
{

class IFFFormANIM :
	public BaseFilterImpl
{
public:
	class CIFFAnimVideo;
	class CIFFAnimAudio;

	class CInputPin : 
		public BasePinImpl
	{
	public:
		CInputPin();

		IFFParser* m_pIFFParser;
		ByteStreamWrapper* m_stream;

		inline IFFFormANIM* GetFilter() const
		{
			return (IFFFormANIM*)m_pFilter;
		}

		virtual ErrorCode CheckConnect(IPin* pPin);

		virtual void BreakConnect();

		virtual ErrorCode CheckMediaType(MediaType * mt);

		virtual ErrorCode CompleteConnect(IPin *pPin);
	};

	class CIFFAnimVideo : 
		public BaseOutputPinImpl,
		public IMediaSeeking
	{
	public:

		CTOR CIFFAnimVideo();

		IFFANIM* m_pAnim;

		virtual ErrorCode Pause();

		inline IFFFormANIM* GetFilter() const
		{
			return (IFFFormANIM*)m_pFilter;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);

		virtual ErrorCode CheckMediaType(MediaType* mt);

	// IMediaSeeking
		virtual ErrorCode Seek(TimeUnit unit, LONGLONG seconds);
		virtual ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal);
		virtual ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal);

		LONGLONG m_currentPosition;

		HANDLE m_hThread;
		MSWindows::DWORD m_threadId;
	};

	class CIFFAnimAudio : 
		public BaseOutputPinImpl,
		public IMediaSeeking
	{
	public:

		CIFFAnimAudio();

		IFFANIM* m_pAnim;

#if WIN32
		HANDLE m_hThread;
		MSWindows::DWORD m_threadId;
#else
		ULONG m_hThread;
#endif

		ErrorCode Pause();

		ErrorCode ReadChunk(CAudioChunk* f, uint8* buffer, ULONG startSample, ULONG nsamples);

		IFFFormANIM* GetFilter() const
		{
			return (IFFFormANIM*)m_pFilter;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);

		ErrorCode CheckMediaType(MediaType * mt);

#if 0	// Had this
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

			ErrorCode hr = pReceivePin->ReceiveConnection(this, m_pMediaType);
			if (SUCCEEDED(hr))
			{
				m_connectedTo = pReceivePin;
			}

			return hr;
		}
#endif

#if 0
	// ILAudio
		STDMETHOD(GetSamples)(LONGLONG *pVal);
		STDMETHOD(GetFormat)(WAVEFORMATEX *pVal);
		STDMETHOD(GetChunkSize)(long nchunk, ULONG* pVal);
		STDMETHOD(ReadChunk)(long nchunk, LPSTR buffer, ULONG nsamples);

		STDMETHOD(GetStreamType)(LStreamType *pVal)
		{
			if (pVal == NULL) return E_POINTER;
			*pVal = LStreamType_Audio;
			return S_OK;
		}
#endif

	// IMediaSeeking
		ErrorCode Seek(TimeUnit unit, LONGLONG t);
		ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal);
		ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal);
	};

	CTOR IFFFormANIM();

	CInputPin* m_pInputPin;

	CIFFAnimVideo* m_pVideo;
	CIFFAnimAudio* m_pAudio;

	int GetNextFrame();

	ErrorCode Parse();

	IFFANIM* m_pAnim;
};

}	// MediaShow
}
