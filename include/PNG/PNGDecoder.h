#ifndef __PNGDECODER_H_
#define __PNGDECODER_H_

#include "../LMedia/LMediaImpl.h"
#include "PNGFormat.h"

namespace System
{
namespace MediaShow
{

class CPNGDecoder : public BaseFilterImpl
{
public:
	class CInputPin : public BasePinImpl
	{
	public:
		CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
		}

		inline CPNGDecoder* GetFilter() const
		{
			return (CPNGDecoder*)m_pFilter;
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

		virtual ErrorCode CompleteConnect(IPin* pPin)
		{
			ErrorCode hr;
			hr = BasePinImpl::CompleteConnect(pPin);
			if (hr < 0) return hr;

			return GetFilter()->Open();
		}
	};

	class OutputPin : 
		public BaseOutputPinImpl
	//	public ILMediaSeeking
	{
	public:
		OutputPin()
		{
		}

		ErrorCode Seek(long frame);

		CPNGDecoder* GetFilter() const
		{
			return (CPNGDecoder*)m_pFilter;
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
				VideoInfoHeader* vih = new VideoInfoHeader;

				//memset(&vih->vih->bmiHeader, 0, sizeof(BitmapInfoHeader));
				vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
				vih->vih->bmiHeader.biPlanes = 1;

				if (GetFilter()->m_png->GetColorType() == 6)	// rgb+alpha
				{
					vih->vih->bmiHeader.biBitCount = 32;
				}
				else if (GetFilter()->m_png->GetColorType() == 4)	// grayscale+alpha
				{
					vih->vih->bmiHeader.biBitCount = 32;
				}
				else
				{
					vih->vih->bmiHeader.biBitCount = 24;//m_pFilter->m_pInputPin->m_bitcount;
				}

				vih->vih->bmiHeader.biWidth = GetFilter()->m_png->GetWidth();
				vih->vih->bmiHeader.biHeight = GetFilter()->m_png->GetHeight();
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
			//	mediaType.SetMajorType(LMEDIATYPE_Video);
			//	//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
			//	mediaType.SetFormat(vih);

				*pMediaType = mediaType;

				return Success_True;
			}
			else
			{
				*pMediaType = NULL;
				return Success_False;
			}
		}
/*
	// ILMediaSeeking
		virtual ErrorCode Seek(LONGLONG seconds);
		virtual ErrorCode GetDuration(LONGLONG* pVal);
		virtual ErrorCode GetCurrentPosition(LONGLONG* pVal)
		{
			ATLASSERT(0);
			return -1;
		}
*/
		ErrorCode Run(LONGLONG tStart);
	};

	CPNGDecoder()
	{
		m_pInputPin = new CInputPin;
		m_pInputPin->m_id = WSTR("Stream Input");
		m_pInputPin->m_pFilter = this;
		AddPin(m_pInputPin);

		m_pOutputPin = new OutputPin;
		m_pOutputPin->m_id = WSTR("Image Output");
		m_pOutputPin->m_pFilter = this;
		AddPin(m_pOutputPin);
	}

	CInputPin* m_pInputPin;
	OutputPin* m_pOutputPin;

	//ILByteStream* m_stream;
	ByteStreamWrapper* m_stream;

	Imaging::NGFormat* m_png;

	ErrorCode Open();
};

}	// Media
}

#endif //__PNGDECODER_H_
