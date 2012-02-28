#ifndef PCXFORMAT_H
#define PCXFORMAT_H

namespace System
{
namespace PCX
{

struct ColorEntry
{
	uint8 red;
	uint8 green;
	uint8 blue;
};

struct PCXHEADER
{
	uint8	Magic;	// Constant 10
	uint8	Version;
	uint8	Encoding;
	uint8	BitsPerPixel;
	uint16	Xmin, Ymin;
	uint16  Xmax, Ymax;
	uint16	HRes, VRes;
	ColorEntry ColorMap[16];
	uint8	Reserved;
	uint8	NPlanes;
	uint16	BytesPerLine;
	uint16	PaletteInfo;
	uint8	Filler[58];
};

}
}

#endif
