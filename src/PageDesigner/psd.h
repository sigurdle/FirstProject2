#ifndef __PSDPARSE_H_
#define __PSDPARSE_H_

#include "../Include/Stream.h"

#pragma pack(push, 1)

namespace System
{

/* Convert between intel and motorola */
#define ENDIANWORD(x)	((WORD)((((WORD)(x) & 0x00ff)<<8) |   \
							    (((WORD)(x) & 0xff00)>>8)))

#define ENDIANLONG(x)	((((uint32)(x) & 0x000000ff)<<24) |   \
								 (((uint32)(x) & 0x0000ff00)<<8) |    \
								 (((uint32)(x) & 0x00ff0000)>>8) |    \
								 (((uint32)(x) & 0xff000000)>>24))

/*
4 bytes Signature
Always equal to '8BPS'. Do not try to read the file if the signature does not match this value.

2 bytes Version
Always equal to 1. Do not try to read the file if the version does not match this value.

6 bytes Reserved
Must be zero.

2 bytes Channels
The number of channels in the image, including any alpha channels. Supported range is 1 to 24.

4 bytes Rows
The height of the image in pixels. Supported range is 1 to 30,000.

4 bytes Columns
The width of the image in pixels. Supported range is 1 to 30,000.

2 bytes Depth
The number of bits per channel. Supported values are 1, 8, and 16.

2 bytes Mode
The color mode of the file.
Supported values are:
Bitmap = 0
Grayscale = 1
Indexed Color = 2
RGB Color = 3
CMYK Color = 4
Multichannel = 7
Duotone = 8
Lab Color = 9

*/

//#define MAKEID(a,b,c,d)	((uint32)(d<<24) | (c<<16) | (b<<8) | a)
#define MAKEID(a,b,c,d)	((uint32)(d<<24) | (c<<16) | (b<<8) | a)

#define PSD_SIG	MAKEID('8','B','P','S')

struct PSDHEADER
{
	uint32	signature;	// 8BPS
	uint16 version;		// 1
	uint8	reserved[6];
	uint16 channels;
	uint32	rows;
	uint32	cols;
	uint16 depth;
	uint16 mode;
};

#define MODE_Bitmap		0
#define MODE_Grayscale	1
#define MODE_Indexed		2
#define MODE_RGB			3
#define MODE_CMYK			4
#define MODE_Multi		5
#define MODE_Duotone		8
#define MODE_Lab			9

struct PSDCOLOR
{
	uint8	red, green, blue;
};

struct RECT2
{
	LONG	top, left, bottom, right;
};

struct CHANNELINFO
{
	SHORT	channelID;
	uint32	length;
};

struct LAYERINFO
{
	RECT2	rect;
	uint16 channels;
};

//	BYTE	rec[6];
struct LAYERINFO2
{
	uint32	signature;	// '8BIM'
	uint32	blend;
	uint8	opacity;
	uint8	clipping;	// 0 = base, 1 = non-base
	uint8	flags;
	uint8	pad;
	uint32	extra;
};

struct LAYERMASKINFO
{
	RECT2	rect;
	uint8	defaultColor;
	uint8	flags;
	uint16	pad;
};

struct ADJUSTMENTINFO
{
	uint32	signature;	// Always 8BIM
	uint32	key;
	uint32	length;
};

// Adjustment keys
#define ADJUST_LEVELS			MAKEID('l','e','v','l')
#define ADJUST_CURVES			MAKEID('c','u','r','v')
#define ADJUST_BRIGHTNESS		MAKEID('b','r','i','t')
#define ADJUST_BALANCE			MAKEID('b','l','n','c')
#define ADJUST_HUESAT			MAKEID('h','u','e',' ')
#define ADJUST_SELECTIVE		MAKEID('s','e','l','c')
#define ADJUST_THRESHOLD		MAKEID('t','h','r','s')
#define ADJUST_INVERT			MAKEID('n','v','r','t')
#define ADJUST_POSTERIZE		MAKEID('p','o','s','t')
#define ADJUST_HUESAT2			MAKEID('h','u','e','2')	// 5.0
#define ADJUST_CHANNELMIXER	MAKEID('m','i','x','r')	// 5.0

struct LEVELRECORD
{
	uint16	inputBlack;		// 0..253
	uint16	inputWhite;		// 2..255
	uint16	outputBlack;	// 0.. 255
	uint16	outputWhite;	// 0..255
	uint16	gamma;	// 10...999 (0.1..0.99)
};

struct SELECTIVERECORD
{
	SHORT cyan;
	SHORT magenta;
	SHORT yellow;
	SHORT black;
};

#define ID_8BIM	MAKEID('8','B','I','M')

// Blend key

#define BLEND_NORM	MAKEID('n','o','r','m')
#define BLEND_DARK	MAKEID('d','a','r','k')
#define BLEND_LITE	MAKEID('l','i','t','e')
#define BLEND_HUE		MAKEID('h','u','e',' ')
#define BLEND_SAT		MAKEID('s','a','t',' ')
#define BLEND_COLR	MAKEID('c','o','l','r')
#define BLEND_LUM		MAKEID('l','u','m',' ')
#define BLEND_MUL		MAKEID('m','u','l',' ')
#define BLEND_SCRN	MAKEID('s','c','r','n')
#define BLEND_DISS	MAKEID('d','i','s','s')
#define BLEND_OVER	MAKEID('o','v','e','r')
#define BLEND_HLIT	MAKEID('h','L','i','t')
#define BLEND_SLIT	MAKEID('s','L','i','t')
#define BLEND_DIFF	MAKEID('d','i','f','f')

// Flags
#define TRANS_PROTECTED	(1<<0)
//#define VISIBLE	(1<<1)

struct GLOBALLAYERMASKINFO
{
	uint16 overlayColorSpace;	// Undocumented
	uint8	colorComponents[8];
	uint16 opacity;	// 0 = transparent, 100 = opaque
	uint8	kind;		// 128 prefered
	uint8	filler;
};

class ILayer
{
public:
	virtual void GetLayerInfo(LAYERINFO* playerinfo) const = 0;
	virtual void GetLayerInfo2(LAYERINFO2* playerinfo2) const = 0;
	virtual System::StringA* GetName() const = 0;
	virtual void ReadPSDLayerChannel(long channelID, long imageRowBytes, uint8 * imagebits) const = 0;
};

class ILayeredFile
{
public:
	virtual void Load(System::IO::ISequentialByteStream* stream) = 0;
	virtual void GetFileInfo(PSDHEADER* pinfo) const = 0;
	virtual unsigned int GetNumLayers() const = 0;
	virtual ILayer* GetNLayer(unsigned int index) const = 0;
};

class PSDFile;

class PSDLayer : public ILayer
{
public:

// ILayer

//	HRESULT ReadPSDLayerImage(int imode, int imageRowBytes, LPBYTE imagebits);

	System::StringA* GetName() const
	{
		return new System::StringA(System::string_copy(layername));
	}

	void GetLayerInfo(LAYERINFO* playerinfo) const
	{
		if (playerinfo == NULL) throw -1;
		*playerinfo = layerinfo;
	}

	void GetLayerInfo2(LAYERINFO2* playerinfo2) const
	{
		if (playerinfo2 == NULL) throw -1;
		*playerinfo2 = layerinfo2;
	}

	void ReadPSDLayerChannel(long channelID, long imageRowBytes, uint8 * imagebits) const;

protected:

	friend PSDFile;

	LAYERINFO		layerinfo;
	LAYERINFO2		layerinfo2;
	LAYERMASKINFO	layermaskinfo;
	CHANNELINFO    channelinfo[8];

	char layername[256];

	PSDFile* m_file;
};

class PSDFile : public ILayeredFile
{
public:
	uint32	m_ctableLength;
	uint8	m_colortable[3][256];

	void ReadPSDHeader();
	void ReadColorTable(uint32* CTableLength, uint8 * colortable);
	void ParsePSDLayers();
	void SkipPSDResources();
	LONG ReadImageResource(int imode, uint32 imageRowBytes, uint8 * imagebits);
//	LONG ReadPSDLayerImage(int layerIndex, int imode, int imageRowBytes, LPBYTE imagebits);

	LONG ReadPSDResources();

// ILayeredFile
	unsigned int GetNumLayers() const
	{
		return m_layerList.GetSize();
	}

	ILayer* GetNLayer(unsigned int index) const
	{
		if (/*index >= 0 &&*/ index < m_layerList.GetSize())
		{
			return m_layerList[index];
		}
		else
			throw -1;
		return NULL;
	}

	void GetFileInfo(PSDHEADER* pinfo) const
	{
		if (pinfo == NULL) throw -1;
		*pinfo = m_hdr;
	}

	void Load(System::IO::ISequentialByteStream* stream);

protected:

	friend PSDLayer;

	PSDHEADER m_hdr;

	System::IO::ISequentialByteStream* m_file;

	ULONGLONG m_resOffset;
	uint32	m_layermaskLength;
	ULONGLONG m_layermaskStartPos;

	ULONGLONG m_layerDataStartPos;

	uint32	m_layerinfoLength;
	ULONGLONG m_layerinfoStartPos;

	SHORT m_numLayers;
	bool	m_bHasMergedImage;

	vector<PSDLayer*> m_layerList;
};

int UnpackRowByteRun1(char** pSource, char** pDest, int srcBytes, int dstBytes);

//void FreePSDFile(PSDFILE* psdfile, LPFORMATRECORD r);
//long ParsePSDLayers(PSDFILE* psdfile, LPFORMATRECORD r);

#pragma pack(pop)

}

#endif	// __PSDPARSE_H_
