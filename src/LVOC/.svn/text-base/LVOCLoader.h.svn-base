#ifndef __LVOCLOADER_H_
#define __LVOCLOADER_H_

//#include "resource.h"       // main symbols

#include "VOCLoader.h"

namespace System
{
namespace MediaShow
{

#define CHUNKSAMPLES	16000	// Some reasonable value

class CChunk
{
public:
	ULONGLONG m_fileOffset;
	ULONG m_nSamples;
};

//"Mmreg.h"

class CLVOCLoader : 
	public BaseFilterImpl	// ILMediaFilter
{
public:
	class CInputPin : 
		public BasePinImpl
	{
	public:
		CInputPin();

		ByteStreamWrapper* m_stream;

		//VOCHEADER m_hdr;

		list<CChunk*> m_chunks;
		LONGLONG m_nSamples;

		virtual ErrorCode CheckConnect(IPin* pPin);

		virtual void BreakConnect();

		virtual ErrorCode CheckMediaType(MediaType* mt);

		virtual ErrorCode CompleteConnect(IPin *pPin);

		inline CLVOCLoader* GetFilter() const
		{
			return (CLVOCLoader*)m_pFilter;
		}
	};

	class COutputPin :
		public BaseOutputPinImpl,
		public IMediaSeeking
	{
	public:
		COutputPin();

	//	WAVEFORMATEX m_wfx;
	//	int m_compression;

		DWORD m_threadId;
		HANDLE m_hThread;

		virtual ErrorCode CheckMediaType(MediaType* mt);

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);

		virtual ErrorCode Run(LONGLONG tStart);

		static DWORD WINAPI AudioRunProc(LPVOID lpParameter);

		inline CLVOCLoader* GetFilter() const
		{
			return (CLVOCLoader*)m_pFilter;
		}

	// IMediaSeeking
		ErrorCode Seek(TimeUnit unit, LONGLONG t)
		{
			ASSERT(0);
			return Error_NotImplemented;
		}
		ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal)
		{
			if (pVal == NULL) throw Error;
			*pVal = GetFilter()->m_pInputPin->m_nSamples * TIME_SCALE / GetFilter()->m_voc->m_wfx.nSamplesPerSec;
			return Success;
		}
		ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
		{
			ASSERT(0);
			return Error_NotImplemented;
		}
	};

	CLVOCLoader()
	{
		m_pInputPin = NULL;
		m_pOutputPin = NULL;

		m_pInputPin = new CInputPin;
		m_pInputPin->m_pFilter = this;
		m_pInputPin->m_id = WSTR("Stream Input");
		AddPin(m_pInputPin);

		m_pOutputPin = new COutputPin;
		m_pOutputPin->m_pFilter = this;
		m_pOutputPin->m_id = WSTR("Audio Output");
		AddPin(m_pOutputPin);
	}

	VOCLoader* m_voc;

	CInputPin* m_pInputPin;
	COutputPin* m_pOutputPin;
};

}	// Media
}

#endif //__LVOCLOADER_H_
