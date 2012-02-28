#ifndef __MNGDECODER_H_
#define __MNGDECODER_H_

namespace System
{
namespace MediaShow
{

class CMNGDecoder : public BaseFilterImpl, public System::IO::ISequentialByteStream
{
public:
	class CInputPin : public BasePinImpl
	{
	public:
		CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
		}

		inline CMNGDecoder* GetFilter() const
		{
			return (CMNGDecoder*)m_pFilter;
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

		inline CMNGDecoder* GetFilter() const
		{
			return (CMNGDecoder*)m_pFilter;
		}

		ErrorCode Seek(long frame);

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

				//memset(&vih->bmiHeader, 0, sizeof(BitmapInfoHeader));
				vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
				vih->vih->bmiHeader.biPlanes = 1;
				if (GetFilter()->m_ihdr.ColorType == 6)	// rgb+alpha
				{
					vih->vih->bmiHeader.biBitCount = 32;
				}
				else
				{
					vih->vih->bmiHeader.biBitCount = 24;//m_pFilter->m_pInputPin->m_bitcount;
				}
				vih->vih->bmiHeader.biWidth = GetFilter()->m_ihdr.Width;
				vih->vih->bmiHeader.biHeight = GetFilter()->m_ihdr.Height;
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
			//	mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
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
			ASSERT(0);
			return -1;
		}
*/
		ErrorCode Run(LONGLONG tStart);
	};

	CMNGDecoder()
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

	ULONG AddRef()
	{
		return 1;
	}
	ULONG Release()
	{
		return 1;
	}

	CInputPin* m_pInputPin;
	OutputPin* m_pOutputPin;

	ByteStreamWrapper* m_stream;

	Imaging::NGFormat::MHDR m_mhdr;
	Imaging::NGFormat::IHDR m_ihdr;
	Imaging::NGFormat::PaletteEntry* m_paletteEntry;

	uint8 GetByte()
	{
		uint8 byte;
		ULONG nRead = m_stream->Read(&byte, 1);
		return byte;
	}

	int m_idata_offset;
	int m_idata_length;

	virtual ULONG Read(void* pv, ULONG cb)
	{
		uint8* p = (uint8*)pv;

		for (int i = 0; i < cb; i++)
		{
			if (m_idata_offset == m_idata_length)
			{
				ASSERT(0);
			}

			m_idata_offset++;
			*p++ = GetByte();
		}

		return cb;
	}

	virtual LONGLONG Seek(LONGLONG move, ULONG origin)
	{
		ASSERT(0);
		return 0;
	}

	ErrorCode Open();
};

}	// Media
}

#endif //__MNGDECODER_H_
