#ifndef __MSVideo1Dec_h__
#define __MSVideo1Dec_h__

#include "MemAllocator.h"

namespace System
{
namespace Media
{

class MSVideo1Decoder
{
public:

	int Decode(const uint8* ptr, uint32 length, int width, int height, uint8* out, int rowbytes);

protected:

	/*
	struct CodeEntry12
	{
		uint8 c[6];
	};

	CodeEntry12 V1[256];
	CodeEntry12 V4[256];
	*/
};

class MSVideo1Dec : public BaseFilterImpl
{
public:

	class InputPin :
		public BasePinImpl,
		public IMemInputPin
	{
	public:
		InputPin(MSVideo1Dec* pFilter, System::StringW* id) : BasePinImpl(PINDIR_INPUT)
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
				return E_FAIL;

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

		MSVideo1Dec* m_pFilter;
		CMemAllocator* m_pAllocator;

		MSVideo1Decoder dec;
	//	uint8* ybuf;
	};

	class OutputPin : public BaseOutputPinImpl, public IMediaSeeking
	{
	public:
		OutputPin(MSVideo1Dec* pFilter, System::StringW* id)
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
				return E_FAIL;

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
				//mediaType.Create(sizeof(LVIDEOINFOHEADER2)/*+m_pFilter->m_lpbiOut->biClrUsed*sizeof(RGBQUAD)*/);

				MediaType* mt;
				m_pFilter->m_pInput->ConnectionMediaType(&mt);

				VideoInfoHeader* vih = (VideoInfoHeader*)mt->GetFormat()->Clone();

				//memcpy(&((LVIDEOINFOHEADER2*)mediaType.pbFormat)->bmiHeader, &((LVIDEOINFOHEADER2*)mt.pbFormat)->bmiHeader, sizeof(BitmapInfoHeader));
				vih->vih->bmiHeader.biBitCount = 24;

				MediaType* mediaType = new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
				//mediaType.SetFormat(vih);
				//mediaType.subtype = GUID_NULL,// TODO FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
				//mediaType.Create(AllocFormatBuffer(mediaType->cbFormat = 0;
				//mediaType->pbFormat = (BYTE*)CoTaskMemAlloc();

				//memcpy((*pMediaType)->pbFormat, m_pBitmapInfoHeader

				*pMediaType = mediaType;

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

		MSVideo1Dec* m_pFilter;
	};

	CTOR MSVideo1Dec()
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

#endif // __MSVideo1Dec_h__
