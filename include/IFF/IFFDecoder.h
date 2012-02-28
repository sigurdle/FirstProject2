// IFFDecoder.h : Declaration of the CIFFDecoder

#ifndef __IFFDECODER_H_
#define __IFFDECODER_H_

#if 0

#include "resource.h"       // main symbols

#include "iffparse.h"


namespace LMedia
{

/////////////////////////////////////////////////////////////////////////////
// CIFFDecoder
class CIFFDecoder : 
	public CLBaseFilterImpl	// ILMediaFilter
{
public:

	class CInputPin : 
		public CLBasePinImpl
		//public ILMemInputPin
	{
	public:
		CInputPin() : CLBasePinImpl(LPINDIR_INPUT)
		{
			m_pFilter = NULL;
		}

		CIFFDecoder* m_pFilter;

		ILBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

		HRESULT CheckMediaType(const CLMediaType &mt)
		{
			return E_FAIL;
		}

#if 0
		STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType);
#endif

		//STDMETHOD(Receive)(ILVideoSample *pSample);
	};

	class COutputPin : 
		public CLBasePinImpl,
		public IIFFParser
	{
	public:
		COutputPin() : CLBasePinImpl(LPINDIR_OUTPUT)
		{
			m_pFilter = NULL;
			//m_pOutSample = NULL;
		}

		CIFFDecoder* m_pFilter;

		ILByteStream* m_stream;

		//CComObject<CVideoSample>* m_pOutSample;

		ILBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

		HRESULT CheckMediaType(const CLMediaType &mt)
		{
			return E_FAIL;
		}

// ILByteStream
	/*
		STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead)
		{
			return m_pFilter->m_stream->Read(pv, cb, pcbRead);
		}
		STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
		{
			return m_pFilter->m_stream->Seek(dlibMove, dwOrigin, plibNewPosition);
		}
		*/

		virtual HRESULT SetFilePos(LARGE_INTEGER move, DWORD dwOrigin, ULARGE_INTEGER* pos);
		virtual IFFRESULT IFFErrorText(IFFRESULT errorcode, LPTSTR lpszDesc, DWORD cbDesc);
		virtual IFFRESULT IFFDescendChunk(LPIFFCHUNK lpck);
		virtual LONG IFFCreateChunk(LPIFFCHUNK lpck);
		virtual IFFRESULT IFFAscendChunk(LPIFFCHUNK lpck);
		virtual DWORD IFFReadChunkBytes(LPVOID lpBuffer, DWORD dwBytes);
		virtual DWORD IFFWriteChunkBytes(LPVOID lpBuffer, DWORD dwBytes);
	};

	CIFFDecoder()
	{
		m_pInputPin = new CInputPin;
		m_pInputPin->m_pFilter = this;

		m_pOutputPin = new COutputPin;
		m_pOutputPin->m_pFilter = this;
	}

	/*
	void FinalRelease()
	{
		if (m_pInputPin)
		{
			m_pInputPin->Release();
			m_pInputPin = NULL;
		}

		if (m_pOutputPin)
		{
			m_pOutputPin->Release();
			m_pOutputPin = NULL;
		}
	}
	*/

	//CIFFParser* m_pIFFParser;

	CInputPin* m_pInputPin;
	COutputPin* m_pOutputPin;

	IIFFForm* m_iffForm;

	//CComPtr<ILByteStream> m_stream;

	HRESULT Open();

#if 0
	STDMETHOD(GetPinCount)(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = 2;
		return S_OK;
	}
	STDMETHOD(GetPin)(long index, ILPin* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;
		if (index == 0)
			(*pVal = m_pInputPin)->AddRef();
		else if (index == 1)
			(*pVal = m_pOutputPin)->AddRef();
		return S_OK;
	}
#endif
};

}	// LMedia

#endif //__IFFDECODER_H_

#endif