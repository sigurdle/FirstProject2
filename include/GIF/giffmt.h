#ifndef __GIFFMT_H_
#define __GIFFMT_H_

namespace System
{
namespace Imaging
{

#pragma pack(push, 1)

struct GIFFILEHEADER
{
	uint8	gifSignature[3];	// GIF
	uint8	gifVersion[3];		// 87a or 89a
};

struct GIFSCREENDESCR
{
	uint16 gifWidth;
	uint16 gifHeight;

	unsigned	char	gifGlobalCTableSize	: 3,  // -1
						gifSortFlag				: 1,
						gifColorRes          : 3,	// bitcount-1
						gifGlobalCTable		: 1;	// If there is a global colortable right after this structure

	uint8	gifBgColor;
	uint8	gifPixelAspect;
};

#define GIFCOLORRES(x)	((x<<4)>>5)

struct GIFIMAGEDESCR
{
	uint16 gifLeft;
	uint16 gifTop;
	uint16 gifWidth;
	uint16 gifHeight;

	unsigned	char	gifLocalCTableSize	: 3,
						gifReserved				: 2,
						gifSortFlag				: 1,
						gifInterlaced			: 1,
						gifLocalCTable			: 1;
};

struct GIFCONTROL
{
	unsigned	char	Transparent : 1,
						UserInput : 1,
						Disposal : 3,
						Reserved : 3;

	uint16	DelayTime;	// unit (1/100 seconds)
	uint8	TransparentIndex;
};

struct GIFLOOP
{
	uint8 gifLoop;
	uint16 gifIterations;
};

struct GIFCOLORTRIPLET
{
	uint8 Red;
	uint8 Green;
	uint8 Blue;
};

#pragma pack(pop)

}	// Imaging
}

#endif	// __GIFFMT_H_
