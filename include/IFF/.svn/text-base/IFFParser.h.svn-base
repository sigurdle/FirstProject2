#ifndef IFFParser_h
#define IFFParser_h

#ifndef IFFEXT
#define IFFEXT DECLSPEC_DLLIMPORT
#endif

#if 0
/* Convert between intel and motorola */
#define ENDIANWORD(x)	((WORD)((((WORD)(x) & 0x00ff)<<8) |       (((WORD)(x) & 0xff00)>>8)))
#define ENDIANLONG(x)	((((uint32)(x) & 0x000000ff)<<24) |    (((uint32)(x) & 0x0000ff00)<<8) |   (((uint32)(x) & 0x00ff0000)>>8) |    (((uint32)(x) & 0xff000000)>>24))
#endif


namespace System
{

typedef int	IFFRESULT;
typedef uint32	ID;

#define MakeID(a,b,c,d)	(((uint32)a<<24) | ((uint32)b<<16) | ((uint32)c<<8) | (uint32)d)

#define ID_FORM	MakeID('F','O','R','M')
#define ID_LIST	MakeID('L','I','S','T')
#define ID_PROP	MakeID('P','R','O','P')
#define ID_CAT		MakeID('C','A','T',' ')

#define ID_PBM		MakeID('P','B','M',' ')
#define ID_ILBM	MakeID('I','L','B','M')
#define ID_ANIM	MakeID('A','N','I','M')
#define ID_8SVX	MakeID('8','S','V','X')
#define ID_AIFF	MakeID('A','I','F','F')
#define ID_SMUS	MakeID('S','M','U','S')
#define ID_FTXT	MakeID('F','T','X','T')

#define ID_BMHD	MakeID('B','M','H','D')
#define ID_ANHD	MakeID('A','N','H','D')
#define ID_CAMG	MakeID('C','A','M','G')
#define ID_CMAP	MakeID('C','M','A','P')
#define ID_CRNG	MakeID('C','R','N','G')
#define ID_CCRT	MakeID('C','C','R','T')
#define ID_BODY	MakeID('B','O','D','Y')
#define ID_DLTA	MakeID('D','L','T','A')
#define ID_CHRS	MakeID('C','H','R','S')

#define ID_VHDR	MakeID('V','H','D','R')

#define ID_SXHD	MakeID('S','X','H','D')
#define ID_SBDY	MakeID('S','B','D','Y')

#define ID_COMM	MakeID('C','O','M','M')
#define ID_SSND	MakeID('S','S','N','D')
#define ID_MARK	MakeID('M','A','R','K')

#define ID_NAME	MakeID('N','A','M','E')
#define ID_AUTH	MakeID('A','U','T','H')
#define ID_ANNO	MakeID('A','N','N','O')
#define ID_Copyright	MakeID('(','c',')',' ')

#define MAXPLANES	33

#pragma pack(push, 2)

class IFFCHUNK
{
public:
	CTOR IFFCHUNK()
	{
		ckSize = 0;
	}

	ID ckID;
	uint32 ckSize;
	ID grpID;
	uint32 flags;
	uint32 dataOffset;
//	uint64 dataOffset;
};

#define IFFCHUNKSIZE		8L

// BMHD
#define mskNone 						0
#define mskHasMask					1
#define mskHasTransparentColor	2
#define mskLasso						3

#define cmpNone						0
#define cmpByteRun1					1

typedef struct
{
	uint16	bmh_Width, bmh_Height;
	short	bmh_Left, bmh_Top;
	uint8	bmh_Planes;
	uint8	bmh_Masking;
	uint8	bmh_Compression;
	uint8	bmh_Pad;
	uint16	bmh_TransparentColor;
	uint8	bmh_XAspect, bmh_YAspect;
	short	bmh_PageWidth, bmh_PageHeight;
}
BitMapHeader;

#define ROWBYTES_DWORDAligned(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

#define RowBytes(width)	((((width)+15) >> 3) & 0xfffe)

// ANHD
typedef struct
{
	uint8 ah_Operation;
	uint8 ah_Mask;
	uint16 ah_Width, ah_Height;
	int16 ah_Left, ah_Top;
	uint32 ah_AbsTime;
	uint32 ah_RelTime;
	uint8 ah_Interleave;
	uint8 ah_Pad0;
	uint32 ah_Flags;
	uint8 ah_Pad[16];
}
AnimationHeader;

// CRNG
#define RNG_ACTIVE	1
#define RNG_REVERSE	2

typedef struct
{
	short	pad1;
	short	Rate;
	short	Flags;
	uint8	Low, High;
}
ColorRange;

// CCRT
typedef struct
{
	short	Direction;
	uint8	Start, End;
	int32	Seconds;
	int32	Micros;
	uint16	pad;
}
CycleInfo;

// CMAP
typedef struct
{
	uint8	Red, Green, Blue;
}
ColorRegister;

// CAMG
#define AMIGA_HAM		0x800	// Hold and Modify
#define AMIGA_EHB		0x80	// Extra halfbrite
#define AMIGA_HIRES	0x8000
#define AMIGA_LACED	0x4

// GRAB
typedef struct
{
	short	x, y;
}
Point2D;

// VHDR
#define sCmpNone		0
#define sCmpFibDelta	1

#define MAXVOLUME	0x1000L

typedef struct
{
	uint32	vh_OneShotHiSamples;
	uint32	vh_RepeatHiSamples;
	uint32	vh_SamplesPerHiCycle;
	uint16	vh_SamplesPerSec;
	uint8	vh_ctOctave;
	uint8	vh_sCompression;
	int32	vh_Volume;
}
VoiceHeader;

// Anim with sound

// SXHD
typedef struct
{
	uint8 SampleDepth; /* depth of the Sample in unit Bits, most common is 8
                      but all others from 1 Bit up to 32 Bits are
                      (theoretical) possible
							 */
	uint8 FixedVolume; /* Amiga-typical unit for playback-volume, 0 is off and
                      64 is maximum
							 */
	ULONG Length;   /*    length of a SBDY-chunk of ONE frame. This length is
                      calculated for a constant playbackspeed. If speed
                      varies from frame to frame the length of the
                      SBDY-samplechunk also varies and this value is
                      invalid and/or set to 0
							 */
	//uint8 pad;

	LONG PlayRate;  /*    Amiga-typical unit for playback-speed; if you like to
                      use the duration of sampleplayback for the synchroni-
                      sation of the anim-playrate or if you use a soundcard,
                      you better should use "PlayFreq"
							*/
	LONG CompressionMethod;/*   has to be =0 in anims everytime, because the
                      AnimPlayer became slower and Dolby-Surround®-
                      informations will be destroyed by all known
                      compressions
							 */
	uint8 UsedChannels;/* Flag for number and type of channels saved in the
                      SBDY-chunk:
                          1 - Channel left
                          2 - Channel right
                          4 - Channel center
                      Left and right together or center are supported this
                      time, but following channels are theoretical also
                      possible:
                          8 - Surroundchannel or surround left
                         16 - Surround right
                         32 - Subwoofer effectchannel
								 */
	uint8 UsedMode;/*     says, wich soundmode has to be used:
                          1: Mode Mono (center-channel only)
                          2: Mode Stereo (channels left and right)
                      Following modes are also possible but not supported
                      yet:
                          3 - 3.0 3Channel
                          4 - 4.0 DTS®-Quadro
                          5 - 4.0 DolbySurround®
                          6 - 5.0 DTS® / AC-3®
                          7 - 5.1 DTS® / AC-3®
								  */
	LONG PlayFreq; /*     play-/samplefrequency, spezifies the correct playspeed
						*/
	uint16 Loop;     /*    Number of loops; says how often anim has to be repeated
*                     after first playback
*                     Loop=0 - No loop, leave the anim with the last frame
*                     Loop>0 - Loop, repeat the anim for "Loop" times
*                     NOTE: if it is a looped anim, the first two frames
*                           have been appended to the end of the anim AND
*                           these frames include sounddata!
*/
}
AnimSoundHeader;

// COMM (AIFF)
//typedef uint8	EXTENDED[10];
typedef union
{
	char	v[10];
	uint16 w[5];
	struct
	{
		uint16	w0;
		uint32 dw0;
		uint32 dw1;
	}
	test;

	struct
	{
		unsigned short
				negative : 1,
				exponent:15,
				mantissa0:1,
				mantissa1:16,
				mantissa2:16,
				mantissa3:15;
	}
	little_endian;

	struct
	{
		unsigned short
			mantissa3:1,
			mantissa4:5,
			mantissa0:16,
			mantissa1:11,
			mantissa2:15,
			exponent:15,
			negative : 1;
	}
	big_endian;
}
EXTENDED;

inline EXTENDED ENDIANEXTENDED(EXTENDED& ext)
{
//	long double d;

	ASSERT(sizeof(EXTENDED) == 10);
	ASSERT(sizeof(ext.v) == 10);
	ASSERT(sizeof(ext.little_endian) == 10);
	ASSERT(sizeof(ext.big_endian) == 10);

	EXTENDED ext2;

	/*
	ext2.w[0] = ext.w[4];
	ext2.w[1] = ext.w[3];
	ext2.w[2] = ext.w[2];
	ext2.w[3] = ext.w[1];
	ext2.w[4] = ext.w[0];
	*/

	/*
	ext2.v[0] = ext.v[1];
	ext2.v[1] = ext.v[0];

	ext2.v[2] = ext.v[3];
	ext2.v[3] = ext.v[4];

	ext2.v[4] = ext.v[5];
	ext2.v[5] = ext.v[4];

	ext2.v[6] = ext.v[7];
	ext2.v[7] = ext.v[6];

	ext2.v[8] = ext.v[9];
	ext2.v[9] = ext.v[8];
	*/

/*
	ext2.v[0] = ext.v[9];
	ext2.v[1] = ext.v[8];
	ext2.v[2] = ext.v[7];
	ext2.v[3] = ext.v[6];
	ext2.v[4] = ext.v[5];
	ext2.v[5] = ext.v[4];
	ext2.v[6] = ext.v[3];
	ext2.v[7] = ext.v[2];
	ext2.v[8] = ext.v[1];
	ext2.v[9] = ext.v[0];
*/

	ext2.test.dw1 = BigEndian32(ext.test.dw0);
	ext2.test.dw0 = BigEndian32(ext.test.dw1);
	ext2.test.w0 = BigEndian16(ext.test.w0);

	return ext2;
}

typedef struct
{
	short	numChannels;
	uint32	numSampleFrames;
	short	sampleSize;
	EXTENDED sampleRate;
}
CommonHeader;

// SSND
typedef struct
{
	uint32	offset;
	uint32	blockSize;
}
SoundDataChunk;

// IFF functions

// IFF error codes
#define IFF_OK						0		// No error
#define IFF_BASE					-256
#define IFF_EOF 					(IFF_BASE-0)	// End of file
#define IFF_EOC	 	  			(IFF_BASE-1)	// End of context
#define IFFERR_UNKNOWN			(IFF_BASE-2)	// huh?
#define IFFERR_CORRUPTED		(IFF_BASE-3)	// Corrupted file
#define IFFERR_READWRITE		(IFF_BASE-4)	// File read/write error
#define IFFERR_MEMORY			(IFF_BASE-5)	// Memory
#define IFFERR_CLIENT			(IFF_BASE-6)	// Client error
#define IFFERR_COMPRESS			(IFF_BASE-7)	// Unknown compression

/*
// IFF function prototypes
LONG IFFErrorText(IFFRESULT errorcode, LPTSTR lpszDesc, uint32 cbDesc);
LONG IFFCreateChunk(LPFORMATRECORD r, LPIFFCHUNK lpck);
LONG IFFDescendChunk(LPFORMATRECORD r, LPIFFCHUNK lpck);
LONG IFFAscendChunk(LPFORMATRECORD r, LPIFFCHUNK lpck);
uint32 IFFReadChunkBytes(LPFORMATRECORD r, LPVOID lpBuffer, uint32 dwBytes);
uint32 IFFWriteChunkBytes(LPFORMATRECORD r, LPVOID lpBuffer, uint32 dwBytes);
*/

#pragma pack(pop)
/*
struct IIFFParser : public Object
{
public:
	virtual HRESULT SetFilePos(LARGE_INTEGER move, uint32 dwOrigin, ULARGE_INTEGER* pos) = 0;
	virtual IFFRESULT IFFErrorText(IFFRESULT errorcode, LPTSTR lpszDesc, uint32 cbDesc) = 0;
	virtual IFFRESULT IFFDescendChunk(LPIFFCHUNK lpck) = 0;
	virtual LONG IFFCreateChunk(LPIFFCHUNK lpck) = 0;
	virtual IFFRESULT IFFAscendChunk(LPIFFCHUNK lpck) = 0;
	virtual uint32 IFFReadChunkBytes(LPVOID lpBuffer, uint32 dwBytes) = 0;
	virtual uint32 IFFWriteChunkBytes(LPVOID lpBuffer, uint32 dwBytes) = 0;
};
*/

class IFFEXT IFFParser : public Object
{
public:

	CTOR IFFParser(IO::ISequentialByteStream* stream);

	LONGLONG SetFilePos(LONGLONG move, IO::SeekOrigin origin);
//	IFFRESULT IFFErrorText(IFFRESULT errorcode, LPTSTR lpszDesc, uint32 cbDesc);
	IFFRESULT IFFDescendChunk(IFFCHUNK* lpck);
	LONG IFFCreateChunk(IFFCHUNK* lpck);
	IFFRESULT IFFAscendChunk(IFFCHUNK* lpck);
	uint32 IFFReadChunkBytes(void* lpBuffer, uint32 dwBytes);
	uint32 IFFWriteChunkBytes(const void* lpBuffer, uint32 dwBytes);

	IO::ISequentialByteStream* m_stream;
};

}

#endif	// IFFParser_h
