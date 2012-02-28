#include "stdafx.h"
#include "PNG.h"

#include "PNGDecoder.h"	// TODO remove

#include "MNGDecoder.h"

//#include "../LMedia/ZLIBDecoder.h"

namespace System
{
using namespace IO;

namespace MediaShow
{

/////////////////////////////////////////////////////////////////////////////
// CMNGDecoder

#define CK_IHDR	0x49484452	// 73 72 68 82
#define CK_PLTE	0x504C5445	// 80 76 84 69
#define CK_IDAT	0x49444154	// 73 68 65 84
#define CK_IEND	0x49454e44	// 73 69 78 68

#define CK_MHDR	0x4D484452
#define CK_FRAM	0x4652414D
#define CK_TERM	0x5445524D
#define CK_BACK	0x4241434B
#define CK_bKGD	0x624B4744

struct Chunk
{
	uint32 id;
	uint32 len;
	LONGLONG pos;
};


ErrorCode CMNGDecoder::Open()
{
	ULONG nRead;

	uint32 value;

	nRead = m_stream->Read(&value, 4);
	if (nRead != 4) return Error;
	if (value != 0x474e4d8a) return Error;

	nRead = m_stream->Read(&value, 4);
	if (nRead != 4) return Error;
	if (value != 0x0a1a0a0d) return Error;

	while (1)
	{
		ULONG length;
		nRead = m_stream->Read(&length, 4);
		if (nRead != 4) break;
		length = BigEndian32(length);

		uint32 type;
		nRead = m_stream->Read(&type, 4);
		type = BigEndian32(type);
		TRACE("%4.4s %X\n", &type, type);

		LONGLONG ppos = m_stream->Seek(0, STREAM_SEEK_CUR);

		switch (type)
		{
		case CK_MHDR:
			{
			}
			break;

		case CK_FRAM:
			{
			}
			break;

		case CK_IHDR:
			{
				if (length != sizeof(m_ihdr)) return Error;
				nRead = m_stream->Read(&m_ihdr, length);
				if (nRead != length) return Error;

				m_ihdr.Width = BigEndian32(m_ihdr.Width);
				m_ihdr.Height = BigEndian32(m_ihdr.Height);
			}
			break;

		case CK_PLTE:
			{
				m_paletteEntry = new Imaging::NGFormat::PaletteEntry[256];
				nRead = m_stream->Read(m_paletteEntry, length);
				if (nRead != length) return Error;
			}
			break;

		case CK_IDAT:
			{
				m_idata_length = length;
				m_idata_offset = 0;

				/*
				if (false)
				{
					BYTE* source = new BYTE[length];
					m_stream->Read(source, length, &nRead);

					BYTE* dest = new BYTE[length*16];

					unsigned long destLen = length*16;
					uncompress(dest, &destLen, source, length);
				}
				*/

			//	return 0;
			}
			break;
		}

		//li.QuadPart = ppos.QuadPart+length;
		m_stream->Seek(ppos+length, STREAM_SEEK_SET);

		uint32 crc;
		nRead = m_stream->Read(&crc, 4);
		crc = BigEndian32(crc);

		/*
		if (type == CK_IEND)
		{
			break;
		}
		*/
	}

	return Success;
}

static MSWindows::DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
//	ErrorCode hr;

	CMNGDecoder::OutputPin* p = (CMNGDecoder::OutputPin*)lpParameter;

	IMediaSample* sample;
	p->m_pAllocator->GetBuffer(0, &sample);
	if (sample)
	{
		LSampleData sampledata;
		sample->LockBits(&sampledata);

		ZLIBDecoder* decoder = new ZLIBDecoder(p->GetFilter());

	//	decoder->start();
	//	decoder->start_block();

		unsigned int pixelBytes;
		if (p->GetFilter()->m_ihdr.ColorType == 0)	// grayscale
		{
			pixelBytes = 1;
		}
		else if (p->GetFilter()->m_ihdr.ColorType == 2)	// rgb
		{
			pixelBytes = 3;
		}
		else if (p->GetFilter()->m_ihdr.ColorType == 3)	// indexed
		{
			pixelBytes = 1;
		}
		else if (p->GetFilter()->m_ihdr.ColorType == 4)	// grayscale with alpha
		{
			pixelBytes = 2;
		}
		else if (p->GetFilter()->m_ihdr.ColorType == 6)	// rgb with alpha
		{
			pixelBytes = 4;
		}
		else
			ASSERT(0);

		unsigned int scanlineBytes = pixelBytes * p->GetFilter()->m_ihdr.Width;

		// We use two buffers for two scanlines, and we reserve a pixel to left of the start of the scanline
		uint8* scanlineBuffer[2];
		scanlineBuffer[0] = new uint8[scanlineBytes+pixelBytes];
		scanlineBuffer[1] = new uint8[scanlineBytes+pixelBytes];
		// clear the 'previous' scanline to zero
		std::memset(scanlineBuffer[1], 0, scanlineBytes+pixelBytes);
		std::memset(scanlineBuffer[0], 0, pixelBytes);	// clear the pixel before the start of the scanline to zero

		uint8* scanlinePtr[2];
		scanlinePtr[0] = scanlineBuffer[0]+pixelBytes;
		scanlinePtr[1] = scanlineBuffer[1]+pixelBytes;

		unsigned int width = p->GetFilter()->m_ihdr.Width;
		unsigned int height = p->GetFilter()->m_ihdr.Height;
		unsigned int curscan = 0;

		for (unsigned int row = 0; row < height; row++)
		{
			uint8* dest = sampledata.idata + sampledata.rowbytes*row;

			// filter byte
			uint8 filterType;
			decoder->Read(&filterType, 1);

			decoder->Read(scanlinePtr[curscan], scanlineBytes);

			switch (filterType)
			{
			case 0:	// None
				// Do nothing
				break;

			case 1:	// Sub
				{
					uint8* curx = scanlinePtr[curscan];
					uint8* recona = curx - pixelBytes;
					unsigned int x;
					switch (pixelBytes)
					{
					case 4:
						for (x = 0; x < width; x++)
						{
							*curx++ += *recona++;
							*curx++ += *recona++;
							*curx++ += *recona++;
							*curx++ += *recona++;
						}
						break;

					case 3:
						for (x = 0; x < width; x++)
						{
							*curx++ += *recona++;
							*curx++ += *recona++;
							*curx++ += *recona++;
						}
						break;

					case 2:
						for (x = 0; x < width; x++)
						{
							*curx++ += *recona++;
							*curx++ += *recona++;
						}
						break;

					case 1:
						for (x = 0; x < width; x++)
						{
							*curx++ += *recona++;
						}
						break;
					}
				}
				break;

			case 2:	// Up
				{
					uint8* curx = scanlinePtr[curscan];
					uint8* reconb = scanlinePtr[!curscan];
					unsigned int x;
					switch (pixelBytes)
					{
					case 4:
						for (x = 0; x < width; x++)
						{
							*curx++ += *reconb++;
							*curx++ += *reconb++;
							*curx++ += *reconb++;
							*curx++ += *reconb++;
						}
						break;

					case 3:
						for (x = 0; x < width; x++)
						{
							*curx++ += *reconb++;
							*curx++ += *reconb++;
							*curx++ += *reconb++;
						}
						break;

					case 2:
						for (x = 0; x < width; x++)
						{
							*curx++ += *reconb++;
							*curx++ += *reconb++;
						}
						break;

					case 1:
						for (x = 0; x < width; x++)
						{
							*curx++ += *reconb++;
						}
						break;
					}
				}
				break;

			case 3:	// Average
				{
					uint8* curx = scanlinePtr[curscan];
					uint8* recona = curx - pixelBytes;
					uint8* reconb = scanlinePtr[!curscan];
					unsigned int x;
					switch (pixelBytes)
					{
					case 4:
						for (x = 0; x < width; x++)
						{
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
						}
						break;

					case 3:
						for (x = 0; x < width; x++)
						{
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
						}
						break;

					case 2:
						for (x = 0; x < width; x++)
						{
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
						}
						break;

					case 1:
						for (x = 0; x < width; x++)
						{
							*curx++ += ((int)*recona++ + (int)*reconb++) / 2;
						}
						break;
					}
				}
				break;

			case 4:	// Paeth
				{
					uint8* curx = scanlinePtr[curscan];
					uint8* recona = curx - pixelBytes;
					uint8* reconb = scanlinePtr[!curscan];
					uint8* reconc = reconb - pixelBytes;
					for (unsigned int x = 0; x < width*pixelBytes; x++)
					{
						*curx++ += Imaging::PaethPredictor(*recona++, *reconb++, *reconc++);
					}
				}
				break;

			default:
				ASSERT(0);
			}

			uint8* src = scanlinePtr[curscan];

			if (p->GetFilter()->m_ihdr.ColorType == 2)	// rgb
			{
				for (unsigned int x = 0; x < width; x++)
				{
					dest[0] = src[2];
					dest[1] = src[1];
					dest[2] = src[0];

					dest += 3;
					src += 3;
				}
			}
			else if (p->GetFilter()->m_ihdr.ColorType == 3)	// indexed color
			{
				for (unsigned int x = 0; x < width; x++)
				{
					dest[0] = p->GetFilter()->m_paletteEntry[*src].b;
					dest[1] = p->GetFilter()->m_paletteEntry[*src].g;
					dest[2] = p->GetFilter()->m_paletteEntry[*src].r;

					dest += 3;
					src += 1;
				}
			}
			else if (p->GetFilter()->m_ihdr.ColorType == 6)	// rgb+alpha
			{
				for (unsigned int x = 0; x < width; x++)
				{
					// premultiply
					dest[0] = src[2] * (int)src[3] / 255;
					dest[1] = src[1] * (int)src[3] / 255;
					dest[2] = src[0] * (int)src[3] / 255;
					dest[3] = src[3];
					dest += 4;
					src += 4;
				}
			}

			curscan = !curscan;	// swap between the two scanline buffers
		}

		delete [] scanlineBuffer[0];
		delete [] scanlineBuffer[1];

		sample->UnlockBits();

		p->m_pInputPin->Receive(sample);
	}

	p->ConnectedTo()->EndOfStream();

	return 0;
}

ErrorCode CMNGDecoder::OutputPin::Run(LONGLONG tStart)
{
//	m_pFilter->m_tStart = tStart;

	ASSERT(0);
#if 0
	DWORD threadId;
	/*m_hThread =*/ CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(CMNGDecoder::OutputPin*)this, 0, &threadId);
#endif
	return 0;
}

}	// Media
}
