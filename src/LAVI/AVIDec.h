#ifndef __AVIDEC_H_
#define __AVIDEC_H_

//#include "resource.h"       // main symbols

#define MPEG4EXT DECLSPEC_DLLIMPORT

#include "MemAllocator.h"

namespace System
{

DECLSPEC_DLLIMPORT void init_idct();

namespace Media
{

class CAVIDec : 
	public BaseFilterImpl	// IMediaFilter
{
public:
	//class CMemAllocator;
	class CInputPin;

	/*
	class CBuffer
	{
	public:
		CBuffer()
		{
			m_bFree = TRUE;
		}

		~CBuffer()
		{
		}

	};
	*/

	class CInputPin : 
		public BasePinImpl,
		public IMemInputPin
	{
	public:
		CTOR CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
			m_pFilter = NULL;

		//	m_hic = NULL;

			m_outRowbytes = 0;
			m_lpOutBits = NULL;

			m_pAllocator = new CMemAllocator;
			//m_pAllocator->AddRef();
		//	m_pAllocator->m_pInputPin = this;

		//	m_pLock.Init();

			m_config = NULL;
			m_pPrevVOP = NULL;
		}

		~CInputPin()
		{
			if (m_pAllocator)
			{
				//m_pAllocator->Release();
				m_pAllocator = NULL;
			}
		}
	
		Mpeg4::MP4VConfig* m_config;
		Mpeg4::VideoObjectPlane* m_pPrevVOP;

#if 0
		void* m_dec_handle;
#endif

		CAVIDec* m_pFilter;

		CMemAllocator* m_pAllocator;

		uint m_outRowbytes;
		uint8 * m_lpOutBits;

		virtual ErrorCode CheckMediaType(MediaType* mt);
		virtual ErrorCode CompleteConnect(IPin* pPin);
		virtual void BreakConnect();

		IBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}
		ErrorCode EndOfStream();

		// IMemInputPin
		IMemAllocator* GetAllocator()
		{
			return m_pAllocator;
		}
		bool Receive(IMediaSample *pSample);
	};

	class COutputPin :
		public BaseOutputPinImpl,
		public IMediaSeeking
	{
	public:

		CTOR COutputPin()
		{
			m_pFilter = NULL;
		}

		CAVIDec* m_pFilter;

	//	CComObject<CVideoMediaType>* m_pMediaType;
	//	CComPtr<ILMemAllocator> m_allocator;

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Video)
				return E_FAIL;

			return Success;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType)
		{
			if (iPosition == 0)
			{
				VideoInfoHeader* vih = new VideoInfoHeader(m_pFilter->m_lpbiOut->biClrUsed);

				//mediaType.Create(sizeof(LVIDEOINFOHEADER2)+m_pFilter->m_lpbiOut->biClrUsed*sizeof(RGBQUAD));

				memcpy(&vih->vih->bmiHeader, m_pFilter->m_lpbiOut, sizeof(BitmapInfoHeader)+m_pFilter->m_lpbiOut->biClrUsed*sizeof(RGBQuad));

				MediaType* mediaType = new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
				//mediaType.subtype = GUID_NULL,// TODO FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
				//mediaType.Create(AllocFormatBuffer(mediaType->cbFormat = 0;
				//mediaType->pbFormat = (BYTE*)CoTaskMemAlloc();

				//memcpy((*pMediaType)->pbFormat, m_pBitmapInfoHeader
				//mediaType.SetFormat(vih);

				*pMediaType = mediaType;

				return Success_True;
			}
			else
			{
				pMediaType = NULL;
				return Success_False;
			}
		}

		IBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

#if 0
		STDMETHOD(Connect)(ILPin* pReceivePin, LMediaType* pmt)
		{
			if (pReceivePin == NULL) return E_POINTER;

			if (m_connectedTo != NULL)
			{
				ASSERT(0);
				return E_UNEXPECTED;	// Already connected
			}

			//CComPtr<ILMediaType> mediaType;
			//GetMediaType(&mediaType);

			{ // TODO, maybe not do this here
			// Create video media type
			//	ASSERT(m_pMediaType == NULL);

				ASSERT(pmt == NULL);

				ASSERT(0);
				//pmt->pformat = 
				/*
				CComObject<CVideoMediaType>::CreateInstance(&m_pMediaType);
				m_pMediaType->AddRef();
				m_pMediaType->m_pVideoOut = this;
			//	m_pMediaType->m_mt.fourcc = m_pAVIStream->m_aviStreamHeader.fccHandler;
			//	m_pMediaType->m_mt.pformat = (void*)m_pBitmapInfoHeader;
			*/
			}

			CComQIPtr<ILMemInputPin> memInput = pReceivePin;
			if (memInput)
			{
				memInput->GetAllocator(&m_allocator);
			}

			ErrorCode hr = pReceivePin->ReceiveConnection(this, m_mt);
			if (SUCCEEDED(hr))
			{
				m_connectedTo = pReceivePin;
			}

			return hr;
		}
#endif

	// IMediaSeeking
		ErrorCode Seek(TimeUnit unit, LONGLONG rt)
		{
			IMediaSeeking* peerSeeking = dynamic_cast<IMediaSeeking*>(m_pFilter->m_pInputPin->ConnectedTo());
			if (peerSeeking == NULL)
				return Error_NoInterface;

			return peerSeeking->Seek(unit, rt);
		}
		ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal)
		{
			if (pVal == NULL) return Error_InvalidArgument;
			IMediaSeeking* peerSeeking = dynamic_cast<IMediaSeeking*>(m_pFilter->m_pInputPin->ConnectedTo());
			if (peerSeeking == NULL)
				return Error_NoInterface;

			return peerSeeking->GetDuration(unit, pVal);
		}
		ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
		{
			if (pVal == NULL) return Error_InvalidArgument;
			IMediaSeeking* peerSeeking = dynamic_cast<IMediaSeeking*>(m_pFilter->m_pInputPin->ConnectedTo());
			if (peerSeeking == NULL)
				return Error_NoInterface;

			return peerSeeking->GetCurrentPosition(unit, pVal);
		}
	};

	CAVIDec()
	{
		m_pInputPin = NULL;
		m_pOutputPin = NULL;

		m_lpbiIn = NULL;
		m_lpbiOut = NULL;

		m_pInputPin = new CInputPin;
	//	if (FAILED(hr)) return hr;
		m_pInputPin->m_pFilter = this;
		m_pInputPin->m_id = WSTR("Video Input");
		AddPin(m_pInputPin);

		m_pOutputPin = new COutputPin;//>::CreateInstance(&);
	//	if (FAILED(hr)) return hr;
		m_pOutputPin->m_pFilter = this;
		m_pOutputPin->m_id = WSTR("Video Output");
		AddPin(m_pOutputPin);

		init_idct();
	}

	CInputPin* m_pInputPin;
	COutputPin* m_pOutputPin;

//	LPBITMAPINFOHEADER m_lpbiIn;
//	LPBITMAPINFOHEADER m_lpbiOut;

	BitmapInfoHeader* m_lpbiIn;
	BitmapInfoHeader* m_lpbiOut;

//	void SetSampleRGBData(CVideoObjectPlane* pPic, ILMediaSample* m_sample);
};

}	// Media
}

#endif //__AVIDEC_H_
