#include "stdafx.h"
#include "MSVideo1Dec.h"

namespace System
{
namespace Media
{

struct PixelRGB
{
	uint8 b;
	uint8 g;
	uint8 r;
};

int MSVideo1Decoder::Decode(const uint8* ptr, uint32 buflength, int width, int height, uint8* out, int rowbytes)
{
	ASSERT(ptr != NULL);
	ASSERT(out != NULL);
	ASSERT(width > 0 && height > 0);

	uint32 length = buflength;

	// bottom-up
	out += (height-1) * rowbytes;
	rowbytes = -rowbytes;

	int nblock = 0;

	int cols = (width+3) / 4;
	int rows = (height+3) / 4;
	int totalblocks = rows*cols;

	while (nblock < totalblocks)
	{
		if (length < 2)
		{
			TRACE("Buffer not large enough");
			return -1;
		}

		uint8 byte_a = *ptr++;
		uint8 byte_b = *ptr++;
		length -= 2;

	//	if (byte_a == 0 && byte_b == 0)
	//		break;

		if (byte_b >= 0x84 && byte_b < 0x88)	// skip blocks
		{
			int n = ((byte_b - 0x84)<<8) + byte_a;
		
			nblock += n;
		}
		else if (byte_b < 0x80)
		{
			int y = (nblock / cols) * 4;
			int x = (nblock % cols) * 4;

			if (length < 4)
			{
				TRACE("Buffer not large enough");
				return -1;
			}

			uint16 word_a = *ptr++;
			word_a |= (*ptr++)<<8;

			uint16 word_b = *ptr++;
			word_b |= (*ptr++)<<8;

			length -= 4;

			PixelRGB color_a;
			color_a.r = (word_a & 0x1F)<<3;
			color_a.g = ((word_a>>5) & 0x1F)<<3;
			color_a.b = ((word_a>>10) & 0x1F)<<3;

			PixelRGB color_b;
			color_b.r = (word_b & 0x1F)<<3;
			color_b.g = ((word_b>>5) & 0x1F)<<3;
			color_b.b = ((word_b>>10) & 0x1F)<<3;

			uint8* pix = out + y*rowbytes + x*3;

			if (word_a & (1<<15))	// 8-color scheme
			{
				if (length < 12)
				{
					TRACE("Buffer not large enough");
					return -1;
				}

				uint16 word;
				
				PixelRGB color_q1_a;
				word = *ptr++;
				word |= (*ptr++)<<8;
				color_q1_a.r = (word & 0x1F)<<3;
				color_q1_a.g = ((word>>5) & 0x1F)<<3;
				color_q1_a.b = ((word>>10) & 0x1F)<<3;

				PixelRGB color_q1_b;
				word = *ptr++;
				word |= (*ptr++)<<8;
				color_q1_b.r = (word & 0x1F)<<3;
				color_q1_b.g = ((word>>5) & 0x1F)<<3;
				color_q1_b.b = ((word>>10) & 0x1F)<<3;

				PixelRGB color_q2_a;
				word = *ptr++;
				word |= (*ptr++)<<8;
				color_q2_a.r = (word & 0x1F)<<3;
				color_q2_a.g = ((word>>5) & 0x1F)<<3;
				color_q2_a.b = ((word>>10) & 0x1F)<<3;

				PixelRGB color_q2_b;
				word = *ptr++;
				word |= (*ptr++)<<8;
				color_q2_b.r = (word & 0x1F)<<3;
				color_q2_b.g = ((word>>5) & 0x1F)<<3;
				color_q2_b.b = ((word>>10) & 0x1F)<<3;

				PixelRGB color_q3_a;
				word = *ptr++;
				word |= (*ptr++)<<8;
				color_q3_a.r = (word & 0x1F)<<3;
				color_q3_a.g = ((word>>5) & 0x1F)<<3;
				color_q3_a.b = ((word>>10) & 0x1F)<<3;

				PixelRGB color_q3_b;
				word = *ptr++;
				word |= (*ptr++)<<8;
				color_q3_b.r = (word & 0x1F)<<3;
				color_q3_b.g = ((word>>5) & 0x1F)<<3;
				color_q3_b.b = ((word>>10) & 0x1F)<<3;

				length -= 12;

				// quad1
				if (byte_a & 1)
					*((PixelRGB*)(pix + rowbytes*0 + 0)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*0 + 0)) = color_b;

				if (byte_a & 2)
					*((PixelRGB*)(pix + rowbytes*0 + 3)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*0 + 3)) = color_b;

				if (byte_a & 16)
					*((PixelRGB*)(pix + rowbytes*1 + 0)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*1 + 0)) = color_b;

				if (byte_a & 32)
					*((PixelRGB*)(pix + rowbytes*1 + 3)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*1 + 3)) = color_b;

				// quad2
				if (byte_a & 4)
					*((PixelRGB*)(pix + rowbytes*0 + 6)) = color_q1_a;
				else
					*((PixelRGB*)(pix + rowbytes*0 + 6)) = color_q1_b;

				if (byte_a & 8)
					*((PixelRGB*)(pix + rowbytes*0 + 9)) = color_q1_a;
				else
					*((PixelRGB*)(pix + rowbytes*0 + 9)) = color_q1_b;

				if (byte_a & 64)
					*((PixelRGB*)(pix + rowbytes*1 + 6)) = color_q1_a;
				else
					*((PixelRGB*)(pix + rowbytes*1 + 6)) = color_q1_b;

				if (byte_a & 128)
					*((PixelRGB*)(pix + rowbytes*1 + 9)) = color_q1_a;
				else
					*((PixelRGB*)(pix + rowbytes*1 + 9)) = color_q1_b;

			// quad3
				if (byte_b & 1)
					*((PixelRGB*)(pix + rowbytes*2 + 0)) = color_q2_a;
				else
					*((PixelRGB*)(pix + rowbytes*2 + 0)) = color_q2_b;

				if (byte_b & 2)
					*((PixelRGB*)(pix + rowbytes*2 + 3)) = color_q2_a;
				else
					*((PixelRGB*)(pix + rowbytes*2 + 3)) = color_q2_b;

				if (byte_b & 16)
					*((PixelRGB*)(pix + rowbytes*3 + 0)) = color_q2_a;
				else
					*((PixelRGB*)(pix + rowbytes*3 + 0)) = color_q2_b;

				if (byte_b & 32)
					*((PixelRGB*)(pix + rowbytes*3 + 3)) = color_q2_a;
				else
					*((PixelRGB*)(pix + rowbytes*3 + 3)) = color_q2_b;

			// quad4
				if (byte_b & 4)
					*((PixelRGB*)(pix + rowbytes*2 + 6)) = color_q3_a;
				else
					*((PixelRGB*)(pix + rowbytes*2 + 6)) = color_q3_b;

				if (byte_b & 8)
					*((PixelRGB*)(pix + rowbytes*2 + 9)) = color_q3_a;
				else
					*((PixelRGB*)(pix + rowbytes*2 + 9)) = color_q3_b;

				if (byte_b & 64)
					*((PixelRGB*)(pix + rowbytes*3 + 6)) = color_q3_a;
				else
					*((PixelRGB*)(pix + rowbytes*3 + 6)) = color_q3_b;

				if (byte_b & 128)
					*((PixelRGB*)(pix + rowbytes*3 + 9)) = color_q3_a;
				else
					*((PixelRGB*)(pix + rowbytes*3 + 9)) = color_q3_b;
			}
			else	// 	// 2-color scheme
			{
				if (byte_a & 1)
					*((PixelRGB*)(pix + rowbytes*0 + 0)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*0 + 0)) = color_b;

				if (byte_a & 2)
					*((PixelRGB*)(pix + rowbytes*0 + 3)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*0 + 3)) = color_b;

				if (byte_a & 4)
					*((PixelRGB*)(pix + rowbytes*0 + 6)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*0 + 6)) = color_b;

				if (byte_a & 8)
					*((PixelRGB*)(pix + rowbytes*0 + 9)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*0 + 9)) = color_b;

				if (byte_a & 16)
					*((PixelRGB*)(pix + rowbytes*1 + 0)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*1 + 0)) = color_b;

				if (byte_a & 32)
					*((PixelRGB*)(pix + rowbytes*1 + 3)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*1 + 3)) = color_b;

				if (byte_a & 64)
					*((PixelRGB*)(pix + rowbytes*1 + 6)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*1 + 6)) = color_b;

				if (byte_a & 128)
					*((PixelRGB*)(pix + rowbytes*1 + 9)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*1 + 9)) = color_b;

			// b
				if (byte_b & 1)
					*((PixelRGB*)(pix + rowbytes*2 + 0)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*2 + 0)) = color_b;

				if (byte_b & 2)
					*((PixelRGB*)(pix + rowbytes*2 + 3)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*2 + 3)) = color_b;

				if (byte_b & 4)
					*((PixelRGB*)(pix + rowbytes*2 + 6)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*2 + 6)) = color_b;

				if (byte_b & 8)
					*((PixelRGB*)(pix + rowbytes*2 + 9)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*2 + 9)) = color_b;

				if (byte_b & 16)
					*((PixelRGB*)(pix + rowbytes*3 + 0)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*3 + 0)) = color_b;

				if (byte_b & 32)
					*((PixelRGB*)(pix + rowbytes*3 + 3)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*3 + 3)) = color_b;

				if (byte_b & 64)
					*((PixelRGB*)(pix + rowbytes*3 + 6)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*3 + 6)) = color_b;

				if (byte_b & 128)
					*((PixelRGB*)(pix + rowbytes*3 + 9)) = color_a;
				else
					*((PixelRGB*)(pix + rowbytes*3 + 9)) = color_b;
			}

			nblock++;
		}
		else
		{
			int y = (nblock / cols) * 4;
			int x = (nblock % cols) * 4;

			uint8* pix = out + y*rowbytes + x*3;

			PixelRGB color;
			uint16 word = byte_a | (byte_b<<8);
			color.r = (word & 0x1F)<<3;
			color.g = ((word>>5) & 0x1F)<<3;
			color.b = ((word>>10) & 0x1F)<<3;

			*((PixelRGB*)(pix + rowbytes*0 + 0)) = color;
			*((PixelRGB*)(pix + rowbytes*0 + 3)) = color;
			*((PixelRGB*)(pix + rowbytes*0 + 6)) = color;
			*((PixelRGB*)(pix + rowbytes*0 + 9)) = color;
			*((PixelRGB*)(pix + rowbytes*1 + 0)) = color;
			*((PixelRGB*)(pix + rowbytes*1 + 3)) = color;
			*((PixelRGB*)(pix + rowbytes*1 + 6)) = color;
			*((PixelRGB*)(pix + rowbytes*1 + 9)) = color;
			*((PixelRGB*)(pix + rowbytes*2 + 0)) = color;
			*((PixelRGB*)(pix + rowbytes*2 + 3)) = color;
			*((PixelRGB*)(pix + rowbytes*2 + 6)) = color;
			*((PixelRGB*)(pix + rowbytes*2 + 9)) = color;
			*((PixelRGB*)(pix + rowbytes*3 + 0)) = color;
			*((PixelRGB*)(pix + rowbytes*3 + 3)) = color;
			*((PixelRGB*)(pix + rowbytes*3 + 6)) = color;
			*((PixelRGB*)(pix + rowbytes*3 + 9)) = color;

			nblock++;
		}
	}

	return buflength - length;
}

ErrorCode MSVideo1Dec::InputPin::CompleteConnect(IPin* pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

#if 0
	LVIDEOINFOHEADER2* vih = (LVIDEOINFOHEADER2*)m_mt.GetFormat();
#endif

//	ybuf = new uint8[vih->bmiHeader.biWidth * vih->bmiHeader.biHeight];

	return Success;
}

bool MSVideo1Dec::InputPin::Receive(IMediaSample *pBuffer)
{
	ULONG length;
	length = pBuffer->GetActualDataLength();

	LSampleData buffersampledata;
	if (pBuffer->LockBits(&buffersampledata) >= 0)
	{
		IMediaSample* videoSample;
		m_pFilter->m_pOutput->m_pAllocator->GetBuffer(0, &videoSample);
		if (videoSample)
		{
			LSampleData sampledata;
			videoSample->LockBits(&sampledata);

			dec.Decode(buffersampledata.idata, length, sampledata.width, sampledata.height, sampledata.idata, sampledata.rowbytes);

			videoSample->UnlockBits();

			m_pFilter->m_pOutput->m_pInputPin->Receive(videoSample);

			videoSample->Release();
		}

		pBuffer->UnlockBits();
	}

	return true;
}

}	// Media
}
