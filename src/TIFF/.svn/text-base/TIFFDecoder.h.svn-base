#ifndef __TIFFDECODER_H_
#define __TIFFDECODER_H_

//#include "resource.h"       // main symbols

//#include "TIFFFile.h"
//#include "TIFFImage.h"

namespace System
{
namespace Media
{

class TIFFDecoder : public BaseFilterImpl
{
public:
	class CInputPin : 
		public BasePinImpl
		//public ILMemInputPin
	{
	public:
		CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
		}

		inline TIFFDecoder* GetFilter() const
		{
			return (TIFFDecoder*)m_pFilter;
		}

		virtual ErrorCode CheckConnect(IPin* pPin)
		{
			// Call base class first
			ErrorCode hr = BasePinImpl::CheckConnect(pPin);
			if (hr < 0) return hr;

			IByteData* stream = dynamic_cast<IByteData*>(pPin);
			if (stream == NULL) return Error_NoInterface;

			GetFilter()->m_stream = new ByteStreamWrapper(stream);

			return Success;
		}

		virtual void BreakConnect()
		{
			// Release what we obtained in CheckConnect
			GetFilter()->m_stream = NULL;
		}

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Stream)
				return Error;

			return Success;
		}

		virtual ErrorCode CompleteConnect(IPin* pPin);
	};

	class OutputPin : public BaseOutputPinImpl
	{
	public:
		OutputPin()
		{
			m_pFilter = NULL;
		//	m_pMediaType = NULL;

		//	m_currentFrame = -1;
		}

		//TIFFDecoder* m_pFilter;
		//CVideoMediaType* m_pMediaType;
		IMemAllocator* m_allocator;

		ErrorCode Seek(long frame);

		Imaging::TIFFImage* m_pImage;

		IMediaSample* m_sample;

		inline TIFFDecoder* GetFilter() const
		{
			return (TIFFDecoder*)m_pFilter;
		}

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Video)
				return Error;

			return Success;
		}

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType)
		{
			if (iPosition == 0)
			{
			//	mediaType.Create(sizeof(LVIDEOINFOHEADER2));

				VideoInfoHeader* vih = new VideoInfoHeader;//((LVIDEOINFOHEADER2*)mediaType.pbFormat);

				//memset(&vih->bmiHeader, 0, sizeof(BITMAPINFOHEADER));
				vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
				vih->vih->bmiHeader.biPlanes = 1;
				vih->vih->bmiHeader.biBitCount = 24;//m_pFilter->m_pInputPin->m_bitcount;
				vih->vih->bmiHeader.biWidth = m_pImage->GetWidth();
				vih->vih->bmiHeader.biHeight = m_pImage->GetHeight();
				//memcpy(((BITMAPINFO*)&vih->bmiHeader)->bmiColors, m_pFilter->m_pInputPin->m_colors, m_pFilter->m_pInputPin->m_numColors*sizeof(RGBQUAD));

				/*
				RGBQUAD* colors = ((BITMAPINFO*)&vih->bmiHeader)->bmiColors;

				for (int i = 0; i < m_numcolors; i++)
				{
					colors[i].rgbRed = m_colors[i].Red;
					colors[i].rgbGreen = m_colors[i].Green;
					colors[i].rgbBlue = m_colors[i].Blue;
				}
				*/

				MediaType* mediaType = new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
			//	mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
				//mediaType.SetFormat(vih);

				*pMediaType = mediaType;

				return Success_True;
			}
			else
			{
				*pMediaType = NULL;
				return Success_False;
			}
		}

		ErrorCode Run(LONGLONG tStart);
	};

	TIFFDecoder()
	{
		m_pInputPin = new CInputPin;
		m_pInputPin->m_id = WSTR("Stream Input");
		m_pInputPin->m_pFilter = this;
		AddPin(m_pInputPin);

#if 0
		m_pImages = new CImages;
		m_pImages->m_id = L"Image Output";
		m_pImages->m_pFilter = this;
		AddPin(m_pImages);
#endif
	}

	System::IO::ISequentialByteStream* m_stream;

	Imaging::TIFFFile* m_pFile;

	CInputPin* m_pInputPin;

	ErrorCode Open();
};

}	// Media
}

#endif //__TIFFDECODER_H_
