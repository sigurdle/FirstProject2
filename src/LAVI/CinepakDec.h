#ifndef __CinepakDec_h__
#define __CinepakDec_h__

#include "MemAllocator.h"

namespace System
{
namespace Media
{

class CinepakDecoder
{
public:

	int Decode(const uint8* ptr, uint32 length, uint8* out, uint32 rowbytes);

protected:

	struct CodeEntry12
	{
		uint8 c[6];
	};

	CodeEntry12 V1[256];
	CodeEntry12 V4[256];
};

class CinepakDec : public BaseFilterImpl
{
public:

	class InputPin :
		public BasePinImpl,
		public IMemInputPin
	{
	public:
		InputPin(CinepakDec* pFilter, System::StringW* id) : BasePinImpl(PINDIR_INPUT)
		{
			m_pFilter = pFilter;
			m_id = id;
			m_pAllocator = new CMemAllocator;
		}

		IBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

		ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Video)
				return Error;

			/*
			if (FOURCCMap(&mt.subtype) != mt.subtype)	// Not a fourcc guid
				return E_FAIL;
				*/

			return Success;
		}

		IMemAllocator* GetAllocator()
		{
			return m_pAllocator;
		}

		ErrorCode CompleteConnect(IPin* pPin);
		bool Receive(IMediaSample *pBuffer);

	//	int Decode(const uint8* ptr, uint32 length, uint8* out, uint32 rowbytes);

		CinepakDec* m_pFilter;
		CMemAllocator* m_pAllocator;

		CinepakDecoder dec;
		uint8* ybuf;
	};

	class OutputPin : public BaseOutputPinImpl, public IMediaSeeking
	{
	public:
		OutputPin(CinepakDec* pFilter, System::StringW* id)
		{
			m_pFilter = pFilter;
			m_id = id;
		}

		IBaseFilter* QueryFilter() const
		{
			return m_pFilter;
		}

		ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Video)
				return Error;

			/*
			if (FOURCCMap(&mt.subtype) != mt.subtype)	// Not a fourcc guid
				return E_FAIL;
				*/

			return Success;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType)
		{
			if (iPosition == 0)
			{
				ASSERT(0);
#if 0
				MediaType mediaType;
				mediaType.Create(sizeof(LVIDEOINFOHEADER2)/*+m_pFilter->m_lpbiOut->biClrUsed*sizeof(RGBQUAD)*/);

				MediaType mt;
				m_pFilter->m_pInput->ConnectionMediaType(&mt);
				memcpy(&((LVIDEOINFOHEADER2*)mediaType.pbFormat)->bmiHeader, &((LVIDEOINFOHEADER2*)mt.pbFormat)->bmiHeader, sizeof(BitmapInfoHeader));

				mediaType.majortype = LMEDIATYPE_Video;
				mediaType.subtype = GUID_NULL,// TODO FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
				//mediaType.Create(AllocFormatBuffer(mediaType->cbFormat = 0;
				//mediaType->pbFormat = (BYTE*)CoTaskMemAlloc();

				//memcpy((*pMediaType)->pbFormat, m_pBitmapInfoHeader

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

	// IMediaSeeking
		ErrorCode Seek(TimeUnit unit, LONGLONG rt)
		{
			IMediaSeeking* peerSeeking = dynamic_cast<IMediaSeeking*>(m_pFilter->m_pInput->ConnectedTo());
			if (peerSeeking == NULL)
				return Error_NoInterface;

			return peerSeeking->Seek(unit, rt);
		}
		ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal)
		{
			if (pVal == NULL) return Error_InvalidArgument;
			IMediaSeeking* peerSeeking = dynamic_cast<IMediaSeeking*>(m_pFilter->m_pInput->ConnectedTo());
			if (peerSeeking == NULL)
				return Error_NoInterface;

			return peerSeeking->GetDuration(unit, pVal);
		}
		ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
		{
			if (pVal == NULL) return Error_InvalidArgument;
			IMediaSeeking* peerSeeking = dynamic_cast<IMediaSeeking*>(m_pFilter->m_pInput->ConnectedTo());
			if (peerSeeking == NULL)
				return Error_NoInterface;

			return peerSeeking->GetCurrentPosition(unit, pVal);
		}

		CinepakDec* m_pFilter;
	};

	CTOR CinepakDec()
	{
		m_pInput = new InputPin(this, WSTR("Video Input"));
		AddPin(m_pInput);

		m_pOutput = new OutputPin(this, WSTR("Video Output"));
		AddPin(m_pOutput);
	}

	InputPin* m_pInput;
	OutputPin* m_pOutput;
};

}
}

#endif // __CinepakDec_h__
