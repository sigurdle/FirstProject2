#ifndef __LWAVEPARSER_H_
#define __LWAVEPARSER_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Media
{

class CLWAVEParser : 
	public BaseFilterImpl	// ILMediaFilter
{
public:

	class CInputPin : 
		public BasePinImpl
	{
	public:
		CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
			m_pFilter = NULL;
		}

		CLWAVEParser* m_pFilter;

		System::IO::ISequentialByteStream* m_stream;

		virtual ErrorCode CheckConnect(IPin* pPin)
		{
			// Call base class first
			ErrorCode hr = BasePinImpl::CheckConnect(pPin);
			if (hr < 0) return hr;

			IByteData* stream = dynamic_cast<IByteData*>(pPin);
			if (stream == NULL) return E_NOINTERFACE;

			m_stream = new ByteStreamWrapper(stream);

			return Success;
		}

		virtual void BreakConnect()
		{
			// Release what we obtained in CheckConnect
			m_stream = NULL;
		}

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Stream)
				return Error;

			return Success;
		}

		virtual ErrorCode CompleteConnect(IPin *pPin);

		IBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}
	};

	class COutputPin :
		public BaseOutputPinImpl,
		public IMediaSeeking
	{
	public:

		static MSWindows::DWORD WINAPI AudioRunProc(LPVOID lpParameter);

		COutputPin()
		{
			m_pFilter = NULL;

			m_pWaveFormat = NULL;

			m_threadId = 0;
			m_hThread = NULL;
		}

		/*
		int FinalConstruct()
		{
			return 0;
		}

		void FinalRelease()
		{
		}
		*/

		CLWAVEParser* m_pFilter;

		MSWindows::LPWAVEFORMATEX m_pWaveFormat;
		MSWindows::DWORD m_threadId;
		HANDLE m_hThread;

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Audio)
				return Error;

			return Success;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType)
		{
			if (iPosition == 0)
			{
				ASSERT(0);
#if 0
				MediaType mediaType;
				mediaType.Create(sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

				memcpy(mediaType.pbFormat, m_pWaveFormat, sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

				mediaType.majortype = LMEDIATYPE_Audio;
				//mediaType->subtype = FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

				*pMediaType = mediaType;
#endif
				return Success_True;
			}
			else
			{
				pMediaType = NULL;
				return Success_False;
			}
		}

		virtual ErrorCode Run(LONGLONG tStart)
		{
			ASSERT(0);
#if 0
			m_hThread = CreateThread(NULL, NULL, AudioRunProc, (LPVOID)(COutputPin*)this, 0, &m_threadId);
#endif
			if (m_hThread == NULL)
				return E_FAIL;

			return Success;
		}

	// ILPin
		IBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

	// IMediaSeeking
		ErrorCode Seek(TimeUnit unit, LONGLONG t)
		{
			ASSERT(0);
			return Error_NotImplemented;
		}
		ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal)
		{
			if (pVal == NULL) return Error_InvalidArgument;
			//*pVal = ((LONGLONG)m_pAVIStream->m_aviStreamHeader.dwLength * m_pAVIStream->m_aviStreamHeader.dwScale / m_pAVIStream->m_aviStreamHeader.dwRate);
			return Success;
		}
		ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
		{
			ASSERT(0);
			return Error_NotImplemented;
		}
	};

	CLWAVEParser()
	{
		m_pInputPin = new CInputPin;
		m_pInputPin->m_pFilter = this;
		m_pInputPin->m_id = WSTR("Stream Input");
		AddPin(m_pInputPin);

		m_pOutputPin = new COutputPin;
		m_pOutputPin->m_pFilter = this;
		m_pOutputPin->m_id = WSTR("Audio Output");
		AddPin(m_pOutputPin);
	}

	CInputPin* m_pInputPin;
	COutputPin* m_pOutputPin;

	// TODO, have on output pin?
//	ULONG m_fmtsize;
//	void* m_fmtbuffer;

	ErrorCode ReadWAVE();

};

}	// Media
}

#endif //__LWAVEPARSER_H_
