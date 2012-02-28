#pragma once

#include "IFFParser.h"

namespace System
{
namespace MediaShow
{

class IFFForm8SVX : 
//	public IIFFForm,
//	public ILAudio,
	public BaseFilterImpl
//	public ILMediaSeeking
{
public:

	class CInputPin : 
		public BasePinImpl
		//public ILMemInputPin
	{
	public:
		CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
			m_pFilter = NULL;
		}

		IFFForm8SVX* m_pFilter;

		IFFParser* m_pIFFParser;

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
	};

	IFFForm8SVX();

//	CIFFDecoder* m_file;

	CInputPin* m_pInputPin;

	ULONGLONG m_bodyPos;
	ULONG m_bodySize;

	bool m_foundVHDR;
	VoiceHeader	m_vhdr;

	LONGLONG m_nSamples;

	list<CAudioChunk*> m_chunks;

	ErrorCode Parse();
	IFFRESULT Read8SVXForm();

	void Init();

public:

	/*
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

	STDMETHOD(GetStreamType)(LStreamType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = LStreamType_Audio;
		return S_OK;
	}
	*/

#if 0
// ILAudio
	STDMETHOD(GetSamples)(LONGLONG *pVal);
	STDMETHOD(GetFormat)(WAVEFORMATEX *pVal);
	STDMETHOD(GetChunkSize)(long nchunk, ULONG* pVal);
	STDMETHOD(ReadChunk)(long nchunk, LPSTR buffer, ULONG nsamples);
#endif

	/*
// ILMediaSeeking
	STDMETHOD(Seek)(double seconds);
	STDMETHOD(GetDuration)(double* pVal);
	*/
};

}	// MediaShow
}
