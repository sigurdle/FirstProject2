#ifndef Imaging_BitmapLoader_h
#define Imaging_BitmapLoader_h

namespace System
{

namespace Imaging
{

	/*
class ImagingExt Bitmap
{
public:
	uint8* m_data;
	int width;
	int height;
	int components;
};
*/

#define alignment_(width, b)	(((width)+(b-1)) & ~(b-1))
#define alignment2(width)		alignment_(width, 2)
#define alignment4(width)		alignment_(width, 4)
#define alignment8(width)		alignment_(width, 8)
#define alignment16(width)		alignment_(width, 16)

class ImagingExt BitmapLoader : public DispatcherObject
{
public:
	CTOR BitmapLoader();
	virtual ~BitmapLoader();

#ifndef __LERSTAD__	// TODO, fix a cpp_exp_parse bug gLastScope != ...
	void* Load(StringIn filename, BitmapFormat* bitmapFormat, void* (*allocmem)(size_t size), void (*freemem)(void* pv) = NULL);
	void* Load(IO::Stream* stream, BitmapFormat* bitmapFormat, void* (*allocmem)(size_t size), void (*freemem)(void* pv) = NULL);
#endif

	static ClassType* DetermineDecoder(IO::Stream* stream);

//	static LDraw::Bitmap* FromFile(StringIn filename);

	void GetPaletteRGB(uint8 palette[][3], uint count);

//	LDraw::Bitmap* GetBitmap();

//	LDraw::Bitmap* m_bitmap;
	int m_lastStatus;
};

}	// Imaging
}	// System

#endif // Imaging_BitmapLoader_h
