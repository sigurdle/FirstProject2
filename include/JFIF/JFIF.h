#ifndef System_Imaging_JFIF_h
#define System_Imaging_JFIF_h

#ifndef JPEGEXT
#define JPEGEXT DECLSPEC_DLLIMPORT
#endif

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#include "Imaging/DecoderInterface.h"

namespace System
{
namespace Imaging
{

#if 0
class JPEGEXT JPEGFormat : public System::Object
{
public:

protected:
	// Eventually remove this class and put it in JPEGDecoder

	CTOR JPEGFormat(System::IO::ISequentialByteStream* stream);
	~JPEGFormat();
};
#endif

class JPEGEXT JFIFException : public Exception
{
public:

	CTOR JFIFException(StringIn reason) : Exception(reason)
	{
	}

	// copy constructor
	CTOR JFIFException(const JFIFException& e) : Exception(e)
	{
	}
};

class JPEGEXT JPEGDecoder : public Object, public IBitmapFormatDecoder
{
public:
	CTOR JPEGDecoder();
	virtual ~JPEGDecoder();

	// IBitmapFormatDecoder
	virtual int ReadHeader(IO::Stream* stream, BitmapFormat* bitmapFormat) override;
	virtual int ReadBitmap(IO::Stream* stream, void* data, int rowbytes) override;

	int Read();

	void StartScans();
	void EndScans();
	void NextScanline();
	void CopyScanline(uint8* r_plane, uint8* g_plane, uint8* b_plane, int colbytes);
	void CopyScanlineGray(uint8* dest_plane, int colbytes);

	static ErrorCode ReadMarker(IO::Stream* stream);
	ErrorCode ReadHeader();

	void DefineHuffmanTable(uint16 length);

	size_t Read(void* pv, size_t len)
	{
		/*
		BYTE* p = (BYTE*)pv;
		for (int i = 0; i < len; i++)
		{
			m_stream->ReadByte(p);
			p++;
		}
		return len;
		*/
		return m_stream->Read(pv, len);
	}

	int GetWidth() const
	{
		return m_imageWidth;
	}

	int GetHeight() const
	{
		return m_imageHeight;
	}

	uint8 GetComponents() const
	{
		return m_components;
	}

	class HuffmanTable
	{
	public:

		uint8 huffsize[256];
		uint16 huffcode[256];
		uint8 huffval[256];
		int lastk;
	};

	class GetByteStream
	{
	public:
		CTOR GetByteStream(IO::Stream* byteStream) : m_byteStream(byteStream)
		{
		}

		_Ptr<IO::Stream> m_byteStream;

		inline uint8 getbyte()
		{
			size_t nRead;
			uint8 byteval;
			nRead = m_byteStream->Read(&byteval, 1);
			if (nRead == 0)
			{
				raise(Exception(L"Read error"));
			}

			if (byteval == 0xff)
			{
				uint8 b2;
				nRead = m_byteStream->Read(&b2, 1);
				if (nRead == 0)
				{
					raise(Exception(L"Read error"));
				}

			//	if (nRead < 1)
			//		THROW(-1);
				if (b2 != 0)
				{
					raise(Exception(L"DNL Marker"));
					// TODO DNL Marker
					ASSERT(0);
				}
			}

			return byteval;
		}
	};

	class BitStream //: public System::IO::BitStreamT<BitStream>
	{
	public:
		CTOR BitStream(IO::Stream* byteStream) : m_t(GetByteStream(byteStream))
		{
		}

		IO::BitStreamT<GetByteStream> m_t;

		int GetCode(HuffmanTable* table)
		{
			int code = 0;
			int len = 0;
			while (len <= 16)
			{
	/*
	Huffman codes are packed starting with the most-
	significant bit of the code
	*/
				code <<= 1;
				code |= (int)m_t.getbit();
				len++;

				for (int i = 0; i < table->lastk; i++)
				{
					if (table->huffsize[i] == len &&
						table->huffcode[i] == code)
					{
						return table->huffval[i];
					}
				}
			}
			raise(JFIFException(L"huffcode error"));
			return -1;
		}

		/*
		void align()
		{
			m_bitcnt = 0;
		}
		*/
	};

	void DecodeMCU(short* mcu_blocks[]);
	void Transform(short* mcu_blocks[], short** buffer);
	void TransformToRGB(short* const buffer[3], uint8* planes[3], int dest_left, int dest_top, int dest_colbytes, int dest_rowbytes);

public:	// TODO protected

	uint8 m_unitsType;/*	 0 = no units, x/y-density specify the aspect ratio instead
	 1 = x/y-density are dots/inch
	 2 = x/y-density are dots/cm
	 */

	uint8 m_thumbnailWidth;
	uint8 m_thumbnailHeight;
	uint16 m_x_density;
	uint16 m_y_density;

protected:

	_Ptr<IO::Stream> m_stream;
	BitStream* m_bitstream;

	uint16 m_imageWidth;
	uint16 m_imageHeight;
	uint8 m_components;
	uint16 m_MCURestart;
	bool m_restartMarkers;

	int m_nMCU;

// SOS
//	ULONGLONG m_SOSDataOffset;

	void block(short* f, uint8 c);

	uint8 QuantTable[4][64];

	uint8 DCTableSelector[4];
	uint8 ACTableSelector[4];
	uint8 m_QuantTableSelector[4];
	uint8 m_horizontalSamplingFactor[4];
	uint8 m_verticalSamplingFactor[4];

	uint8 m_max_horizontalSamplingFactor;
	uint8 m_max_verticalSamplingFactor;

	short m_previousDC[4];

	uint8 m_SStart;
	uint8 m_SEnd;

	HuffmanTable* m_huffmanTable[2][4];	// Up to four tables

protected:

	uint8 m_cury;
	short** m_mcu_blocks;

	short* m_buffers[3];
	uint8* m_planes[3];
};

inline void putbyte(IO::Stream* stream, uint8 byteval)
{
	stream->Write(&byteval, 1);
}

class JPEGEXT JPEGEncoder
{
public:

	class HuffmanTable
	{
	public:

		int BITS[17];
		uint8 codesize[256];

		uint16 codes[256];

		uint8 huffsize[256];
		uint16 huffcode[256];
		uint8 huffval[256];
		int lastk;
	};

	uint8 m_bitcnt;
	uint8 m_curbyte;

	void putbit(IO::Stream* stream, bool bit)
	{
		if (m_bitcnt == 0)
		{
			m_bitcnt = 8;
			m_curbyte = 0;
		}

		m_bitcnt--;

		m_curbyte |= bit<<m_bitcnt;

		if (m_bitcnt == 0)
		{
			if (stream->Write(&m_curbyte, 1) != 1)
				raise(Exception("Write Error"));

			if (m_curbyte == 0xff)
			{
				uint8 zero = 0;
				stream->Write(&zero, 1);
			}
		}
	}

	void putnbits(IO::Stream* stream, int value, int nbits)
	{
		while (nbits--)
		{
			putbit(stream, (value>>nbits) & 1);
			//value >>= 1;
		}
	}

	void byte_align(IO::Stream* m_stream)
	{
		if (m_bitcnt < 8)
		{
			if (m_stream->Write(&m_curbyte, 1) != 1)
				raise(Exception("Write Error"));

			m_bitcnt = 8;
			m_curbyte = 0;
		}
	}

	void EncodeImage(IO::Stream* stream, uint8* image, int width, int height, int rowbytes);

	// Find huffman code sizes
	HuffmanTable* GenerateHuffman(const vector<uint8>& symbols);
};

}	// Imaging
}	// System

#endif // System_Imaging_JFIF_h
