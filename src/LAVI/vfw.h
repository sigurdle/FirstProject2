#ifndef vfw_h
#define vfw_h

namespace System
{
//typedef uint8 BYTE;
//typedef uint16 WORD;

#if 0

#ifndef WAVE_FORMAT_PCM

/* OLD general waveform format structure (information common to all formats) */
typedef struct waveformat_tag {
    uint16    wFormatTag;        /* format type */
    uint16    nChannels;         /* number of channels (i.e. mono, stereo, etc.) */
    uint32   nSamplesPerSec;    /* sample rate */
    uint32   nAvgBytesPerSec;   /* for buffer estimation */
    uint16    nBlockAlign;       /* block size of data */
} WAVEFORMAT, *PWAVEFORMAT;

/* flags for wFormatTag field of WAVEFORMAT */
#define WAVE_FORMAT_PCM     1


/* specific waveform format structure for PCM data */
typedef struct pcmwaveformat_tag {
	MSWindows::WAVEFORMAT  wf;
   uint16       wBitsPerSample;
} PCMWAVEFORMAT, *PPCMWAVEFORMAT;
#endif /* WAVE_FORMAT_PCM */

#endif

/*
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))
*/

//#include <vfw.h>
//#pragma comment(lib, "vfw32.lib")

/* Macro to make a TWOCC out of two characters */
#ifndef aviTWOCC
#define aviTWOCC(ch0, ch1) ((uint16)(uint8)(ch0) | ((uint16)(uint8)(ch1) << 8))
#endif

/* form types, list types, and chunk types */
#define formtypeAVI             mmioFOURCC('A', 'V', 'I', ' ')
#define listtypeAVIHEADER       mmioFOURCC('h', 'd', 'r', 'l')
#define ckidAVIMAINHDR          mmioFOURCC('a', 'v', 'i', 'h')
#define listtypeSTREAMHEADER    mmioFOURCC('s', 't', 'r', 'l')
#define ckidSTREAMHEADER        mmioFOURCC('s', 't', 'r', 'h')
#define ckidSTREAMFORMAT        mmioFOURCC('s', 't', 'r', 'f')
#define ckidSTREAMHANDLERDATA   mmioFOURCC('s', 't', 'r', 'd')
#define ckidSTREAMNAME		mmioFOURCC('s', 't', 'r', 'n')

#define listtypeAVIMOVIE        mmioFOURCC('m', 'o', 'v', 'i')
#define listtypeAVIRECORD       mmioFOURCC('r', 'e', 'c', ' ')

#define ckidAVINEWINDEX         mmioFOURCC('i', 'd', 'x', '1')

/*
** Stream types for the <fccType> field of the stream header.
*/
#define streamtypeVIDEO         mmioFOURCC('v', 'i', 'd', 's')
#define streamtypeAUDIO         mmioFOURCC('a', 'u', 'd', 's')
#define streamtypeMIDI		mmioFOURCC('m', 'i', 'd', 's')
#define streamtypeTEXT          mmioFOURCC('t', 'x', 't', 's')

/* Basic chunk types */
#define cktypeDIBbits           aviTWOCC('d', 'b')
#define cktypeDIBcompressed     aviTWOCC('d', 'c')
#define cktypePALchange         aviTWOCC('p', 'c')
#define cktypeWAVEbytes         aviTWOCC('w', 'b')

/* Chunk id to use for extra chunks for padding. */
#define ckidAVIPADDING          mmioFOURCC('J', 'U', 'N', 'K')

/*
** Useful macros
**
** Warning: These are nasty macro, and MS C 6.0 compiles some of them
** incorrectly if optimizations are on.  Ack.
*/

/* Macro to get stream number out of a FOURCC ckid */
#define FromHex(n)	(((n) >= 'A') ? ((n) + 10 - 'A') : ((n) - '0'))

/*
#define StreamFromFOURCC(fcc) ((WORD) ((FromHex(LOBYTE(LOWORD(fcc))) << 4) + \
                                             (FromHex(HIBYTE(LOWORD(fcc))))))
*/
// Not tested
inline uint16 StreamFromFOURCC(uint32 fcc)
{
	return ((FromHex(fcc & 0xff)) << 4) + (FromHex((fcc >> 8) & 0xff));
//	return ((FromHex(LOBYTE(LOWORD(fcc))) << 4) + (FromHex(HIBYTE(LOWORD(fcc)))));
}

/* Macro to get TWOCC chunk type out of a FOURCC ckid */
#define TWOCCFromFOURCC(fcc)    HIWORD(fcc)

/* Macro to make a ckid for a chunk out of a TWOCC and a stream number
** from 0-255.
*/
#define ToHex(n)	((BYTE) (((n) > 9) ? ((n) - 10 + 'A') : ((n) + '0')))
#define MAKEAVICKID(tcc, stream) \
        MAKELONG((ToHex((stream) & 0x0f) << 8) | \
			    (ToHex(((stream) & 0xf0) >> 4)), tcc)

/*
** Main AVI File Header
*/	
		
/* flags for use in <dwFlags> in AVIFileHdr */
#define AVIF_HASINDEX		0x00000010	// Index at end of file?
#define AVIF_MUSTUSEINDEX	0x00000020
#define AVIF_ISINTERLEAVED	0x00000100
#define AVIF_WASCAPTUREFILE	0x00010000
#define AVIF_COPYRIGHTED	0x00020000

/* The AVI File Header LIST chunk should be padded to this size */
#define AVI_HEADERSIZE  2048                    // size of AVI header list

struct MainAVIHeader
{
    uint32 dwMicroSecPerFrame;	// frame display rate (or 0L)
    uint32 dwMaxBytesPerSec;	// max. transfer rate
    uint32 dwPaddingGranularity;	// pad to multiples of this
                                                // size; normally 2K.
    uint32 dwFlags;		// the ever-present flags
    uint32 dwTotalFrames;		// # frames in file
    uint32 dwInitialFrames;
    uint32 dwStreams;
    uint32 dwSuggestedBufferSize;

    uint32 dwWidth;
    uint32 dwHeight;

    uint32 dwReserved[4];
};

/*
** Stream header
*/

#define AVISF_DISABLED			0x00000001

#define AVISF_VIDEO_PALCHANGES		0x00010000

struct AVIRECT
{
	int32 left, top, right, bottom;
};

typedef uint32 FOURCC;

struct AVIStreamHeader{
    FOURCC fccType;
    FOURCC fccHandler;
    uint32 dwFlags;	/* Contains AVITF_* flags */
    uint16 wPriority;
    uint16 wLanguage;
    uint32 dwInitialFrames;
    uint32 dwScale;	
    uint32 dwRate;	/* dwRate / dwScale == samples/second */
    uint32 dwStart;
    uint32 dwLength; /* In units above... */
    uint32 dwSuggestedBufferSize;
    uint32 dwQuality;
    uint32 dwSampleSize;
    AVIRECT	rcFrame;
};

/* Flags for index */
#define AVIIF_LIST          0x00000001L // chunk is a 'LIST'
#define AVIIF_KEYFRAME      0x00000010L // this frame is a key frame.
#define AVIIF_FIRSTPART     0x00000020L // this frame is the start of a partial frame.
#define AVIIF_LASTPART      0x00000040L // this frame is the end of a partial frame.
#define AVIIF_MIDPART       (AVIIF_LASTPART|AVIIF_FIRSTPART)

#define AVIIF_NOTIME	    0x00000100L // this frame doesn't take any time
#define AVIIF_COMPUSE       0x0FFF0000L // these bits are for compressor use

struct AVIINDEXENTRY
{
    uint32 ckid;
    uint32 dwFlags;
    uint32 dwChunkOffset;		// Position of chunk
    uint32 dwChunkLength;		// Length of chunk
};

struct WIN_BITMAPINFOHEADER
{
	uint32     biSize;
	int32       biWidth;
	int32       biHeight;
	uint16    biPlanes;
	uint16 biBitCount;
	uint32 biCompression;
	uint32 biSizeImage;
	int32       biXPelsPerMeter;
	int32       biYPelsPerMeter;
	uint32      biClrUsed;
	uint32      biClrImportant;
};

}

#endif // vfw_h
