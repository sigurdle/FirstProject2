#include "stdafx.h"
#include "TIFF.h"
#include "TIFFFile.h"
#include "TIFFImage.h"

namespace System
{
namespace Imaging
{

TIFFFile::TIFFFile()
{
}

TIFFFile::~TIFFFile()
{
}

// static
int TIFFFile::ReadMarker(IO::Stream* stream, int* PCByteOrder)
{
	size_t nRead;

	uint32 header;
	nRead = stream->Read(&header, 4);
	if (nRead != 4)
	{
		return -1;
	}

	int m_PCByteOrder;

	if ((header & 0xffff) == 0x4949)
	{
		m_PCByteOrder = true;
	}
	else if ((header & 0xffff) == 0x4d4d)
	{
		m_PCByteOrder = false;
	}
	else
		return -1;	// Not a TIFF file

	if (m_PCByteOrder)
	{
		if (LittleEndian16((uint16)(header >> 16)) != 0x002a)
		{
			return -1;	// Not a TIFF file
		}
	}
	else
	{
		if (BigEndian16((uint16)(header >> 16)) != 0x002a)
		{
			return -1;	// Not a TIFF file
		}
	}

	if (PCByteOrder) *PCByteOrder = m_PCByteOrder;

	return 0;
}

int TIFFFile::ReadHeader(IO::Stream* stream, BitmapFormat* bitmapFormat)
{
	VerifyArgumentNotNull(bitmapFormat);

	if (ReadMarker(stream, &m_PCByteOrder) < 0)
		return -1;

	m_stream = stream;

	do
	{
		uint32 offset;
		if (!ReadLong(&offset))
		{
			return Error;
		}

		if (offset == 0)	// No more image directories
		{
			break;
		}

		m_stream->Seek(offset, IO::STREAM_SEEK_SET);

		TIFFImage* pImage = new TIFFImage;
		if (pImage)
		{
			pImage->m_file = this;

			if (pImage->ReadDirectory())
			{
				m_images.push_back(pImage);
			}
			else
				delete pImage;
		}
	}
	while (1);

	if (m_images.size() == 0) return -1;

	TIFFImage* image = m_images[0];

	bitmapFormat->width = image->get_Width();
	bitmapFormat->height = image->get_Height();

	/*
	if (image->m_bitsPerSample == 1)	// Bilevel
	{
		raise(Exception("Unsupported pixelformat"));
	}
	else
	*/
	if (image->get_PhotoMetricInterpretation() <= 1)	// Grayscale
	{
		bitmapFormat->pixelFormat = PixelFormat_A8_UNORM;
	}
	else if (image->get_PhotoMetricInterpretation() == 3)	// Paletted image
	{
		bitmapFormat->pixelFormat = PixelFormat_R8G8B8A8_UNORM;
	}
	else if (image->get_PhotoMetricInterpretation() == 2)	// RGB
	{
		bitmapFormat->pixelFormat = PixelFormat_R8G8B8A8_UNORM;
	}
	else
	{
		raise(Exception("Unsupported pixelformat"));
	}

	return 0;
}

int TIFFFile::ReadBitmap(IO::Stream* stream, void* data, int rowbytes)
{
	TIFFImage* image = m_images[0];
	return image->ReadImage(data, rowbytes, image->get_Height(), 32) > 0;
}

ErrorCode TIFFFile::Open(_Ptr<IO::Stream> stream)
{
	m_stream = stream;

	size_t nRead;

	if (ReadMarker(stream, &m_PCByteOrder) < 0)
		return -1;
/*
	uint32 header;
	nRead = m_stream->Read(&header, 4);
	if (nRead != 4)
	{
		return Error;
	}

	if ((header & 0xffff) == 0x4949)
	{
		m_PCByteOrder = true;
	}
	else if ((header & 0xffff) == 0x4d4d)
	{
		m_PCByteOrder = false;
	}
	else
		return Error;	// Not a TIFF file

	if (EndianWord((uint16)(header >> 16)) != 0x002a)
	{
		return Error;	// Not a TIFF file
	}
*/
	do
	{
		uint32 offset;
		if (!ReadLong(&offset))
		{
			return Error;
		}

		if (offset == 0)	// No more image directories
		{
			break;
		}

		m_stream->Seek(offset, IO::STREAM_SEEK_SET);

		TIFFImage* pImage = new TIFFImage;
		if (pImage)
		{
			pImage->m_file = this;

			if (pImage->ReadDirectory())
			{
				m_images.push_back(pImage);
			}
			else
				delete pImage;
		}
	}
	while (1);

	return Success;
}

}	// Imaging
}
