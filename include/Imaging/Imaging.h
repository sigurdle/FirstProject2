#ifndef Imaging_h
#define Imaging_h

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#ifdef __LERSTAD__
#import "JFIF/JFIF.h"
#else
#include "JFIF/JFIF.h"
#endif

#ifdef __LERSTAD__
#import "PNG/PNG.h"
#else
#include "PNG/PNG.h"
#endif

#ifndef ImagingExt
#define ImagingExt DECLSPEC_DLLIMPORT
#endif

#define ROWBYTES_DWORD(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

#include "DecoderInterface.h"
#include "BitmapLoader.h"

namespace System
{
namespace Imaging
{

class ImagingExt BMPDecoder : public Object, public IBitmapFormatDecoder
{
public:
	CTOR BMPDecoder();

	static ErrorCode ReadMarker(IO::Stream* stream);

	virtual int ReadHeader(IO::Stream* stream, BitmapFormat* bitmapFormat);
	virtual int ReadBitmap(IO::Stream* stream, void* data, int rowbytes);

//#pragma pack(push, 2)

	struct BITMAPFILEHEADER
	{
	//	uint16    bfType;
		uint32 bfSize;
		uint16 bfReserved1;
		uint16 bfReserved2;
		uint32 bfOffBits;
	};

	//#pragma pack(pop)

	struct BITMAPINFOHEADER
	{
		uint32 biSize;
		int32 biWidth;
		int32 biHeight;
		uint16 biPlanes;
		uint16 biBitCount;
		uint32 biCompression;
		uint32 biSizeImage;
		int32 biXPelsPerMeter;
		int32 biYPelsPerMeter;
		uint32 biClrUsed;
		uint32 biClrImportant;
	};

	struct RGBQUAD
	{
		uint8 rgbBlue;
		uint8 rgbGreen;
		uint8 rgbRed;
		uint8 rgbReserved;
	};

	BITMAPINFOHEADER m_bih;

};

}	// Imaging
}	// System

#endif	// Imaging_h
