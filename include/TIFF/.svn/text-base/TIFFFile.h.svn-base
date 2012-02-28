#ifndef Imaging_TIFFFile_h
#define Imaging_TIFFFile_h

namespace System
{
namespace Imaging
{

class TiffExt TIFFFile : public Object, public IBitmapFormatDecoder
{
public:
	CTOR TIFFFile();
	~TIFFFile();

	static int ReadMarker(IO::Stream* stream, int* PCByteOrder = NULL);

	virtual int ReadHeader(IO::Stream* stream, BitmapFormat* bitmapFormat) override;	// IBitmapFormatDecoder
	virtual int ReadBitmap(IO::Stream* stream, void* data, int rowbytes) override;	// IBitmapFormatDecoder

	ErrorCode Open(_Ptr<IO::Stream> stream);

	uint16 EndianWord(uint16 v)
	{
		if (m_PCByteOrder)
			return LittleEndian16(v);
		else
			return BigEndian16(v);
	}

	uint32 EndianLong(uint32 v)
	{
		if (m_PCByteOrder)
			return LittleEndian32(v);
		else
			return BigEndian32(v);
	}

	bool ReadWord(uint16* p)
	{
		ULONG nRead;
		nRead = m_stream->Read(p, 2);
		if (nRead != 2)
		{
			return false;
		}

		*p = EndianWord(*p);
		return true;
	}

	bool ReadLong(uint32* p)
	{
		ULONG nRead;
		nRead = m_stream->Read(p, 4);
		if (nRead != 4)
		{
			return false;
		}

		*p = EndianLong(*p);
		return true;
	}

	_Ptr<IO::Stream> m_stream;
	vector<TIFFImage*> m_images;

protected:

	int m_PCByteOrder;
};

}	// Imaging
}	// System

#endif // Imaging_TIFFFile_h
