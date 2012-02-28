#include "stdafx.h"
#include "LPCX.h"
#include "PCXParser.h"

#include <memory>

namespace System
{
namespace Imaging
{

void PlanarToChunky(uint8* dst_bits, int dst_bitcount, uint8* src_planes[], int width, uint8 src_bitsperpixel, uint8 src_nplanes, PCX::ColorEntry* colorMap)
{
	if (src_bitsperpixel == 8)
	{
		if (src_nplanes == 1)	// source is 8-bit indexed
		{
			if (dst_bitcount == 8)
			{
				uint8* src_bits = src_planes[0];
				for (int x = 0; x < width; ++x)
				{
					*dst_bits++ = *src_bits++;
				}
			}
			else if (dst_bitcount == 24)
			{
				uint8* src_bits = src_planes[0];

				for (int x = 0; x < width; ++x)
				{
					*dst_bits++ = colorMap[*src_bits].blue;
					*dst_bits++ = colorMap[*src_bits].green;
					*dst_bits++ = colorMap[*src_bits].red;

					src_bits++;
				}
			}
			else if (dst_bitcount == 32)
			{
				uint8* src_bits = src_planes[0];

				for (int x = 0; x < width; ++x)
				{
					*dst_bits++ = colorMap[*src_bits].blue;
					*dst_bits++ = colorMap[*src_bits].green;
					*dst_bits++ = colorMap[*src_bits].red;
					dst_bits++;

					src_bits++;
				}
			}
			else
				ASSERT(0);
		}
		else if (src_nplanes == 3)	// source is 24bit
		{
			if (dst_bitcount == 24)
			{
				for (int plane = 0; plane < 3; plane++)
				{
					uint8* bitptr = dst_bits + (2-plane);
					uint8* srcptr = src_planes[plane];

					for (int x = 0; x < width; ++x)
					{
						*bitptr = *srcptr;

						bitptr += 3;
						srcptr++;
					}
				}
			}
			else if (dst_bitcount == 32)
			{
				for (int plane = 0; plane < 3; plane++)
				{
					uint8* bitptr = dst_bits + (2-plane);
					uint8* srcptr = src_planes[plane];

					for (int x = 0; x < width; ++x)
					{
						*bitptr = *srcptr;

						bitptr += 4;
						srcptr++;
					}
				}
			}
			else
				ASSERT(0);
		}
		else
			ASSERT(0);
	}
	else if (src_bitsperpixel == 1)
	{
		if (src_nplanes == 1 && dst_bitcount == 1)
		{
			int nbytes = (width+7)/8;

			uint8* src_bits = src_planes[0];
			for (int n = 0; n < nbytes; n++)
			{
				*dst_bits++ = *src_bits++;
			}
		}
		else
		{
			ASSERT(src_nplanes >= 1 && src_nplanes <= 8);

			uint8* planeptr[8];
			int plane;
			int bit = 7;
			int x;

			for (plane = 0; plane < src_nplanes; plane++)
				planeptr[plane] = src_planes[plane];

			for (x = 0; x < width; x++)
			{
				uint8 color = 0;
				uint8 bitmask = 1<<bit;

				for (plane = 0; plane < src_nplanes; plane++)
				{
					if (*planeptr[plane] & bitmask) color |= (1<<plane);
				}

				if (dst_bitcount == 4)
				{
					if (x & 1)
					{
						*dst_bits |= color;
						dst_bits++;
					}
					else
					{
						*dst_bits = color<<4;
					}
				}
				else if (dst_bitcount == 8)
				{
					*dst_bits++ = color;
				}
				else if (dst_bitcount == 24)
				{
					*dst_bits++ = colorMap[color].blue;
					*dst_bits++ = colorMap[color].green;
					*dst_bits++ = colorMap[color].red;
				}
				else
					ASSERT(0);

				if (--bit == -1)
				{
					for (plane = 0; plane < src_nplanes; plane++)
						planeptr[plane]++;

					bit = 7;
				}
			}
		}
	}
	else
		ASSERT(0);
}

bool Decode(ubyte* destptr, ubyte* &srcptr, int totalBytes)
{
	while (totalBytes > 0)
	{
		ubyte value = *srcptr++;

		if ((value & 0xc0) == 0xc0)	// Are the two top bits set?
		{
			int count = (value & ~0xc0);	// Clear the two top bits

			if ((totalBytes -= count) < 0) return false;

			value = *srcptr++;

			while (count--)
			{
				*destptr++ = value;
			}
		}
		else
		{
			if (--totalBytes < 0) return false;

			*destptr++ = value;
		}
	}

	return true;
}

PCXParser::PCXParser() :
	m_colorMap(NULL),
	m_colorMapBuf(NULL)
{
}

PCXParser::~PCXParser()
{
	if (m_colorMapBuf)
	{
		delete [] m_colorMapBuf;
		m_colorMapBuf = NULL;
	}
}

int PCXParser::ReadHeader(IO::Stream* stream, BitmapFormat* bitmapFormat)
{
	ULONG nRead;
	nRead = stream->Read(&m_hdr, sizeof(m_hdr));
	if (nRead < sizeof(m_hdr))
		return E_FAIL;

	if (m_hdr.Magic != 10)
	{
		return -1;
	}

	if (m_hdr.Version != 0 && //= Version 2.5 of PC Paintbrush 
		m_hdr.Version != 2 && //= Version 2.8 w/palette information 
		m_hdr.Version != 3 && //= Version 2.8 w/o palette information 
		m_hdr.Version != 4 && //= PC Paintbrush for Windows(Plus for
                                  //Windows uses Ver 5) 
		m_hdr.Version != 5) //= Version 3.0 and > of PC Paintbrush
	{
		return -1;
	}

	if (m_hdr.Encoding != 1)
	{
		return -1;
	}

	m_width = m_hdr.Xmax-m_hdr.Xmin+1;
	m_height = m_hdr.Ymax-m_hdr.Ymin+1;
	m_bitcount = m_hdr.BitsPerPixel*m_hdr.NPlanes;

	if (m_bitcount <= 1)
		;
	else if (m_bitcount <= 4)
		m_bitcount = 4;
	else if (m_bitcount <= 8)
		m_bitcount = 8;

	if (m_bitcount == 1)
		;//g->mode = IMODE_MONO;
	else if (m_bitcount == 4)
		;//g->mode = IMODE_INDEXED4;
	else if (m_bitcount == 8)
		;//g->mode = IMODE_INDEXED8;
	else if (m_bitcount == 24)
		;//g->mode = IMODE_BGR8;
	else
	{
		//strcpy(g->errorMsg, "Unknown depth");
		//return PLUGIN_MSG;
		return -1;
	}

	m_fileSize = stream->GetSize32();

	stream->Seek(sizeof(PCX::PCXHEADER), System::IO::STREAM_SEEK_SET);

	m_numColors = 0;
	if (m_bitcount < 24)	// Check for palette
	{
		//ColorEntry* colorMap = NULL;
		//ColorEntry* colorMapBuf = NULL;

		if (m_hdr.Version == 5)	// Check for the existence of 256 colors at end of file
		{
			stream->Seek(-769, System::IO::STREAM_SEEK_END);

			uint8 isPalette;
			stream->Read(&isPalette, 1);

			if (isPalette == 0x0c)	// 256 colors
			{
				int colorMapSize = 256*3;

				m_colorMapBuf = new PCX::ColorEntry[256];

				if (m_colorMapBuf)//*)GlobalAlloc(0, colorMapSize))
				{
					m_numColors = 256;
					stream->Read(m_colorMapBuf, colorMapSize);

					m_fileSize -= colorMapSize;
				}
			}
			else	// 16 colors
			{
				m_numColors = 16;
			}

			stream->Seek(sizeof(PCX::PCXHEADER), System::IO::STREAM_SEEK_SET);	// Restore file pointer
		}
		else	// Use the 16 colors in the header
		{
			m_numColors = 16;
		}

		if (m_numColors == 256)
			m_colorMap = m_colorMapBuf;
		else
			m_colorMap = m_hdr.ColorMap;

		/*
		if (colorMap)
		{
			m_colors = (RGBQUAD*)GlobalAlloc(0, sizeof(RGBQUAD)*m_numColors);

			for (int i = 0; i < m_numColors; i++)
			{
				m_colors[i].rgbRed = colorMap[i].red;
				m_colors[i].rgbGreen = colorMap[i].green;
				m_colors[i].rgbBlue = colorMap[i].blue;
			}
		}
		*/
	}

	return 0;
}

#if 0
ErrorCode CLPCXParser::COutputPin::GetMediaType(int iPosition, MediaType **pMediaType)
{
	if (iPosition == 0)
	{
		//mediaType.Create(sizeof(LVIDEOINFOHEADER2)+GetFilter()->m_pInputPin->m_numColors*sizeof(RGBQUAD));

		VideoInfoHeader* vih = new VideoInfoHeader(GetFilter()->m_pInputPin->m_numColors);

	//	memset(&vih->bmiHeader, 0, sizeof(BITMAPINFOHEADER));
		vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
		vih->vih->bmiHeader.biPlanes = 1;
		vih->vih->bmiHeader.biBitCount = GetFilter()->m_pInputPin->m_bitcount;
		vih->vih->bmiHeader.biWidth = GetFilter()->m_pInputPin->m_width;
		vih->vih->bmiHeader.biHeight = GetFilter()->m_pInputPin->m_height;
		//memcpy(((BITMAPINFO*)&vih->bmiHeader)->bmiColors, m_pFilter->m_pInputPin->m_colors, m_pFilter->m_pInputPin->m_numColors*sizeof(RGBQUAD));

		RGBQuad* colors = ((BitmapInfo*)&vih->vih->bmiHeader)->bmiColors;

		for (int i = 0; i < GetFilter()->m_pInputPin->m_numColors; i++)
		{
			colors[i].rgbRed = GetFilter()->m_pInputPin->m_colorMap[i].red;
			colors[i].rgbGreen = GetFilter()->m_pInputPin->m_colorMap[i].green;
			colors[i].rgbBlue = GetFilter()->m_pInputPin->m_colorMap[i].blue;
		}

		MediaType* mediaType = new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
		//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
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
#endif

int PCXParser::ReadBitmap(IO::Stream* stream, void* data, int rowbytes)
{
	ErrorCode hr = 0;

	uint fileSize = stream->GetSize32();

// Seek to beginning of image data
	stream->Seek(sizeof(PCX::PCXHEADER), System::IO::STREAM_SEEK_SET);

#if 0
	if (m_bitcount < 24)	// No palette if 24-bit
	{
		if (m_hdr.Version == 5)	// Check for the existence of 256 colors at end of file
		{
			LARGE_INTEGER li;
			li.QuadPart = -769;
			m_stream->Seek(li, STREAM_SEEK_END, NULL);

			BYTE isPalette;
			m_stream->Read(&isPalette, 1, NULL);

			if (isPalette == 0x0c)	// 256 colors
			{
				WORD colorMapSize = 256*3;

				if (colorMapBuf = (ColorEntry*)GlobalAlloc(0, colorMapSize))
				{
					numColors = 256;
					m_stream->Read(colorMapBuf, colorMapSize, NULL);

					fileSize -= colorMapSize;
				}
			}
			else	// 16 colors
			{
				numColors = 16;
			}

			li.QuadPart = sizeof(PCXHEADER);
			m_stream->Seek(li, STREAM_SEEK_SET, NULL);	// Restore file pointer
		}
		else	// Use the 16 colors in the header
		{
			numColors = 16;
		}

		if (numColors == 256)
			colorMap = colorMapBuf;
		else
			colorMap = m_hdr.ColorMap;

		if (colorMap)
		{
#if 0
			PixelDef* pPalette = g->pPalette8;

			for (int i = 0; i < numColors; i++)
			{
				pPalette[i].red = colorMap[i*3+0];
				pPalette[i].green = colorMap[i*3+1];
				pPalette[i].blue = colorMap[i*3+2];
			}
#endif
		}
	}
#endif

	std::unique_ptr<ubyte> fileBuffer(new ubyte[m_fileSize]);
	stream->Read(fileBuffer.get(), m_fileSize);	// Read the file into the buffer

	ubyte* srcptr = fileBuffer.get();
	uint totalBytes = m_hdr.BytesPerLine*m_hdr.NPlanes;	// Total bytes in one row

	ubyte* planeBuffer = (ubyte*)_alloca(totalBytes);
	ubyte* planePtr[8];

	for (int iPlane = 0; iPlane < m_hdr.NPlanes; ++iPlane)
	{
		planePtr[iPlane] = planeBuffer+m_hdr.BytesPerLine*iPlane;
	}

	for (int y = 0; y < m_height; ++y)
	{
		ubyte* bitptr = ((ubyte*)data + rowbytes*y);

		if (!Decode(planeBuffer, srcptr, totalBytes))
		{
			raise(Exception("Decoding error on line " + String::FromNumber(y)));
		}

		int bitcount = 32;	// TODO
		PlanarToChunky(bitptr, bitcount, planePtr, m_width, /*m_hdr.BytesPerLine,*/ m_hdr.BitsPerPixel, m_hdr.NPlanes, m_colorMap);
	}

	return hr;
}

}	// Imaging
}	// System
