/*
longword	field		description
--------	-----		-----------
    0		magic number	the value 0x2e736e64 (ASCII ".snd")

    1		data offset	the offset, in octets, to the data part.
				The minimum valid number is 24 (decimal).

    2		data size	the size in octets, of the data part.
				If unknown, the value 0xffffffff should
				be used.

    3		encoding	the data encoding format:

				    value	format
				      1		8-bit ISDN u-law
				      2		8-bit linear PCM [REF-PCM]
				      3		16-bit linear PCM
				      4		24-bit linear PCM
				      5		32-bit linear PCM
				      6		32-bit IEEE floating point
				      7		64-bit IEEE floating point
				     23		8-bit ISDN u-law compressed
						using the CCITT G.721 ADPCM
						voice data encoding scheme.

    4		sample rate	the number of samples/second (e.g., 8000)

    5		channels	the number of interleaved channels (e.g., 1)
*/

#pragma pack(push, 1)

typedef struct tagAuHeader
{
	DWORD	magic;
	DWORD	offset;
	LONG	size;
	DWORD	encoding;
	DWORD	sampleRate;
	DWORD	channels;
}
AuHeader;

#define AU_MAGIC	0x2e736e64 //(ASCII ".snd")

#define ENC_ULAW			1	//	8-bit ISDN u-law
#define ENC_PCM8			2	//	8-bit linear PCM [REF-PCM]
#define ENC_PCM16			3	//	16-bit linear PCM
#define ENC_PCM24			4	//	24-bit linear PCM
#define ENC_PCM32			5	//	32-bit linear PCM
#define ENC_IEEE32		6	//	32-bit IEEE floating point
#define ENC_IEEE64		7	//	64-bit IEEE floating point
#define ENC_ULAWADPCM8	23	//	8-bit ISDN u-law compressed
									//	using the CCITT G.721 ADPCM
									// voice data encoding scheme.
#define ENC_ALAW			27	//	8-bit ISDN a-law

/* Convert between intel and motorola */
#define ENDIANWORD(x)	((WORD)((((WORD)(x) & 0x00ff)<<8) |   \
							    (((WORD)(x) & 0xff00)>>8)))

#define ENDIANLONG(x)	((((DWORD)(x) & 0x000000ff)<<24) |   \
								 (((DWORD)(x) & 0x0000ff00)<<8) |    \
								 (((DWORD)(x) & 0x00ff0000)>>8) |    \
								 (((DWORD)(x) & 0xff000000)>>24))

#pragma pack (pop)
