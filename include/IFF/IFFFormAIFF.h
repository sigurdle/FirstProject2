#pragma once

#include "IFFParser.h"

namespace System
{
namespace MediaShow
{

class IFFFormAIFF : 
//	public IIFFForm,
//	public ILAudio,
//	public ILMediaSeeking,
	public BaseFilterImpl
{
public:
	class CInputPin : 
		public BasePinImpl
		//public ILMemInputPin
	{
	public:
		CTOR CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
			m_pFilter = NULL;
		}

		IBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

		ErrorCode CheckMediaType(MediaType * mt)
		{
			return Error;
		}

#if 0
		STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType)
		{
			m_connectedTo = pConnector;
			m_pIFFParser = m_connectedTo;
			if (m_pIFFParser == NULL) return E_FAIL;
			return m_pFilter->Parse();
		}
#endif

		IFFFormAIFF* m_pFilter;
		IFFParser* m_pIFFParser;
	};

	CTOR IFFFormAIFF();

	ErrorCode Parse();
	IFFRESULT ReadAIFFForm();

	void Init();

// IAudio
	int GetSamples(LONGLONG *pVal);
	int GetFormat(MSWindows::WAVEFORMATEX *pVal);
	int GetChunkSize(long nchunk, ULONG* pVal);
	int ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples);

	/*
// ILMediaSeeking
	STDMETHOD(Seek)(double seconds);
	STDMETHOD(GetDuration)(double* pVal);
	*/

public:

	CInputPin* m_pInputPin;

	ULONGLONG m_bodyPos;
	ULONG m_bodySize;

	CommonHeader m_comm;
	SoundDataChunk	m_ssnd;
	ULONG m_sampleRate;

	LONGLONG m_nSamples;

	list<void*> m_chunks;
};

}	// MediaShow
}
