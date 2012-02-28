#ifndef PCXParser_h
#define PCXParser_h

namespace System
{
namespace Imaging
{

class PCXParser : public Object, public IBitmapFormatDecoder
{
public:
	CTOR PCXParser();
	virtual ~PCXParser();

	virtual int ReadHeader(IO::Stream* stream, BitmapFormat* bitmapFormat) override;
	virtual int ReadBitmap(IO::Stream* stream, void* data, int rowbytes) override;

//	ErrorCode ReadHeader();
//	ErrorCode ReadImage(IMediaSample* sample);

//	_Ptr<IO::Stream> m_stream;

	PCX::PCXHEADER m_hdr;
	int m_width;
	int m_height;
	int m_bitcount;
	int m_numColors;
	PCX::ColorEntry* m_colorMap;
	PCX::ColorEntry* m_colorMapBuf;

	uint m_fileSize;
};

}	// Imaging
}	// System

#endif	// PCXParser_h
