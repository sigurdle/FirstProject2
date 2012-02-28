#ifndef __GIFDECODER_H_
#define __GIFDECODER_H_

#include "GIFFile.h"

namespace System
{
namespace MediaShow
{

class CGIFDecoder : public BaseFilterImpl
{
public:
	class CInputPin : public BasePinImpl
	{
	public:
		CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
		}

		inline CGIFDecoder* GetFilter() const
		{
			return (CGIFDecoder*)m_pFilter;
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

	class CImages : 
		public BaseOutputPinImpl,
		public IMediaSeeking
	{
	public:
		CImages()
		{
			m_pFilter = NULL;
		}

	//	ErrorCode Seek(long frame);

		inline CGIFDecoder* GetFilter() const
		{
			return (CGIFDecoder*)m_pFilter;
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

				vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
				vih->vih->bmiHeader.biPlanes = 1;
				vih->vih->bmiHeader.biBitCount = 24;//m_pFilter->m_pInputPin->m_bitcount;
				vih->vih->bmiHeader.biWidth = GetFilter()->m_gifFile->GetWidth();//m_pFilter->m_config->m_video_object_layer_width;
				vih->vih->bmiHeader.biHeight = GetFilter()->m_gifFile->GetHeight();//m_pFilter->m_config->m_video_object_layer_height;
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
				*pMediaType = mediaType;//.Detach();

				return Success_True;
			}
			else
			{
				//*pMediaType = NULL;
				return Success_False;
			}
		}

	// ILMediaSeeking
		virtual ErrorCode Seek(TimeUnit unit, LONGLONG t);
		virtual ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal);
		virtual ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
		{
			ASSERT(0);
			return -1;
		}

		ErrorCode Run(LONGLONG tStart);
	};

	CGIFDecoder()
	{
		m_pInputPin = new CInputPin;
		m_pInputPin->m_id = WSTR("Stream Input");
		m_pInputPin->m_pFilter = this;
		AddPin(m_pInputPin);

		m_pImages = new CImages;
		m_pImages->m_id = WSTR("Image Output");
		m_pImages->m_pFilter = this;
		AddPin(m_pImages);

		m_currentFrame = -1;
	}

	~CGIFDecoder();

	CInputPin* m_pInputPin;
	CImages* m_pImages;

	System::IO::ISequentialByteStream* m_stream;

	Imaging::GIFFormat* m_gifFile;

	uint8* m_imageBits;
	int m_rowbytes;

#if 0
	int m_last_byte;		/* # of bytes in code_buf */
	int m_last_bit;			/* # of bits in code_buf */
	int m_cur_bit;			/* next bit index to read */
	BOOL	m_out_of_blocks;	/* TRUE if hit terminator data block */

	char m_input_code_size;		/* codesize given in GIF file */
	int m_clear_code, m_end_code;	/* values for Clear and End codes */

	int m_code_size;		/* current actual code size */
	int m_limit_code;		/* 2^code_size */
	int m_max_code;	  	/* first unused code value */
	BOOL m_first_time;  	/* flags first call to LZWReadByte */

/* Private state for LZWReadByte */
	int m_oldcode;			/* previous LZW symbol */
	int m_firstcode;		/* first byte of oldcode's expansion */

/* LZW symbol table and expansion stack */

	WORD	*m_symbol_head;	// => table of prefix symbols
	BYTE	*m_symbol_tail;	// => table of suffix bytes
	BYTE	*m_symbol_stack;	// => stack for symbol expansions
	BYTE	*m_sp;		// stack pointer
#endif


//	ErrorCode Seek(long frame);

	long m_currentFrame;

	ErrorCode Disconnect();

	ErrorCode Seek(long frame);

	ErrorCode Open();

};

}	// Media
}

#endif //__GIFDECODER_H_
