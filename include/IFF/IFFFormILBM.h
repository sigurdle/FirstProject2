#pragma once

//#include "resource.h"       // main symbols

#include "IFFILBM.h"

namespace System
{
namespace MediaShow
{

class IFFFormILBM : 
	public BaseFilterImpl
{
public:
	class COutputPin;

	class CInputPin : 
		public BasePinImpl
		//public ILMemInputPin
	{
	public:
		CInputPin();

		IFFParser* m_pIFFParser;
		ByteStreamWrapper* m_stream;

		inline IFFFormILBM* GetFilter() const
		{
			return (IFFFormILBM*)m_pFilter;
		}

		virtual ErrorCode CheckConnect(IPin* pPin);

		virtual void BreakConnect();

		virtual ErrorCode CheckMediaType(MediaType * mt);

		virtual ErrorCode CompleteConnect(IPin *pPin);
#if 0
		STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType)
		{
			m_connectedTo = pConnector;
			m_pIFFParser = m_connectedTo;
			m_pFilter->m_pImage->m_pIFFParser = m_pIFFParser;
			if (m_pIFFParser == NULL) return E_FAIL;
			ErrorCode hr = m_pFilter->Parse();

			if (SUCCEEDED(hr))
			{
				CComObject<CMediaType>::CreateInstance(&m_pFilter->m_pImage->m_pMediaType);
				m_pFilter->m_pImage->m_pMediaType->AddRef();
				m_pFilter->m_pImage->m_pMediaType->m_pILBM = m_pFilter->m_pImage;

				CComObject<CMediaType::CPalette>::CreateInstance(&m_pFilter->m_pImage->m_pMediaType->m_pPalette);
				m_pFilter->m_pImage->m_pMediaType->m_pPalette->AddRef();
				m_pFilter->m_pImage->m_pMediaType->m_pPalette->m_pMediaType = m_pFilter->m_pImage->m_pMediaType;
			}

			return hr;
		}
#endif
	};

	class COutputPin : 
		public CIFFILBM,
		public BaseOutputPinImpl
	{
	public:
		COutputPin();

	//	IFFFormILBM* m_pFilter;
		//CComObject<CMediaType>* m_pMediaType;
	//	CComPtr<ILMemAllocator> m_allocator;

		ErrorCode ReadImage(IMediaSample* pSample);

		inline IFFFormILBM* GetFilter() const
		{
			return (IFFFormILBM*)m_pFilter;
		}

		virtual ErrorCode CheckMediaType(MediaType * mt);

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);

		virtual ErrorCode Run(LONGLONG tStart);

#if 0
		virtual void GetMediaType(ILMediaType* *pVal)
		{
			*pVal = m_pMediaType;
			(*pVal)->AddRef();
		}

		STDMETHOD(Connect)(ILPin* pReceivePin, ILMediaType* mediaType)
		{
			if (pReceivePin == NULL) return E_POINTER;
			if (m_connectedTo != NULL) return E_UNEXPECTED;	// Already connected

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
	};

	CTOR IFFFormILBM();
	~IFFFormILBM();

	CInputPin* m_pInputPin;
	COutputPin* m_pImage;

	IFFRESULT ReadILBMForm(bool bInitRead);

	ULONGLONG m_bodyPos;
	ULONG m_bodySize;

	ErrorCode Parse();

	void Init();
};

}	// MediaShow
}
