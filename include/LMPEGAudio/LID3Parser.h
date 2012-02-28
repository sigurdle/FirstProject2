#ifndef __LID3PARSER_H_
#define __LID3PARSER_H_

#if 0

//#include "resource.h"       // main symbols

#include "..\MPEG\MPEGBitStream.h"

namespace MediaShow
{

class CLID3Parser : 
	public CLBaseFilterImpl
{
public:
	class CInputPin : 
		public CLBasePinImpl
	{
	public:
		CInputPin() : CLBasePinImpl(LPINDIR_INPUT)
		{
			m_pFilter = NULL;
		}

		CLID3Parser* m_pFilter;
		CComPtr<ILByteStream> m_stream;
		DWORD m_dataOffset;	// Offset of data after ID3 tag

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

		ILBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}
	};

	class COutputPin : 
		public CLBasePinImpl,
		public ILByteStream
	{
	public:
		COutputPin() : CLBasePinImpl(LPINDIR_OUTPUT)
		{
			m_pFilter = NULL;
		}

		CLID3Parser* m_pFilter;
		//CComPtr<ILByteStream> m_stream;
		//DWORD m_dataOffset;	// Offset of data after ID3 tag

		/*
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
		*/

		virtual HRESULT CheckMediaType(const MediaType& mt)
		{
			if (mt.majortype != LMEDIATYPE_Stream)
				return E_FAIL;

			return S_OK;
		}

		virtual HRESULT GetMediaType(int iPosition, MediaType* pMediaType)
		{
			if (iPosition == 0)
			{
				HRESULT hr;

				MediaType mediaType;
				hr = mediaType.Create();
				if (FAILED(hr)) return hr;

				mediaType.majortype = LMEDIATYPE_Stream;

				*pMediaType = mediaType;

				return S_OK;
			}
			else
			{
				//pMediaType = NULL;
				return S_FALSE;
			}
		}

	//	virtual HRESULT CompleteConnect(ILPin *pPin);

		ILBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

		STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead)
		{
			return m_pFilter->m_pInputPin->m_stream->Read(pv, cb, pcbRead);
		}
		STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
		{
			HRESULT hr;

			if (dwOrigin == STREAM_SEEK_SET)
			{
				dlibMove.QuadPart += m_pFilter->m_pInputPin->m_dataOffset;
				hr = m_pFilter->m_pInputPin->m_stream->Seek(dlibMove, dwOrigin, plibNewPosition);
				if (plibNewPosition)
				{
					plibNewPosition->QuadPart -= m_pFilter->m_pInputPin->m_dataOffset;
				}
			}
			else if (dwOrigin == STREAM_SEEK_CUR)
			{
				hr = m_pFilter->m_pInputPin->m_stream->Seek(dlibMove, dwOrigin, plibNewPosition);
				if (plibNewPosition)
				{
					plibNewPosition->QuadPart -= m_pFilter->m_pInputPin->m_dataOffset;
				}
			}
			else if (dwOrigin == STREAM_SEEK_END)
			{
				dlibMove.QuadPart += m_pFilter->m_pInputPin->m_dataOffset;
				hr = m_pFilter->m_pInputPin->m_stream->Seek(dlibMove, dwOrigin, plibNewPosition);
				if (plibNewPosition)
				{
					plibNewPosition->QuadPart -= m_pFilter->m_pInputPin->m_dataOffset;
				}
			}
			else
			{
				ATLASSERT(0);
				hr = E_INVALIDARG;
			}

			return hr;
		}
		STDMETHOD(Clone)(ILByteStream* *ppstm)
		{
			ATLASSERT(0);
			return E_NOTIMPL;
		}
	};

	CLID3Parser()
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
		m_pOutputPin->m_id = L"Stream Output";
		AddPin(m_pOutputPin);

		return 0;
	}

	void FinalRelease()
	{
		CLBaseFilterImpl::FinalRelease();
	}

	CComObject<CInputPin>* m_pInputPin;
	CComObject<COutputPin>* m_pOutputPin;

DECLARE_REGISTRY_RESOURCEID(IDR_LID3PARSER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLID3Parser)
	COM_INTERFACE_ENTRY(ILID3Parser)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILMediaFilter)
	COM_INTERFACE_ENTRY(ILBaseFilter)
END_COM_MAP()

// ILID3Parser
public:
};

}	// MediaShow

#endif

#endif //__LID3PARSER_H_
