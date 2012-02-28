#pragma pack(push, 1)

/* Convert between intel and motorola */
#define ENDIANWORD(x)	((WORD)((((WORD)(x) & 0x00ff)<<8) |   \
							    (((WORD)(x) & 0xff00)>>8)))

#define ENDIANLONG(x)	((((DWORD)(x) & 0x000000ff)<<24) |   \
								 (((DWORD)(x) & 0x0000ff00)<<8) |    \
								 (((DWORD)(x) & 0x00ff0000)>>8) |    \
								 (((DWORD)(x) & 0xff000000)>>24))

typedef struct _CHUNKHDR
{
	long	type;
	long	level;
	long	size;

	long		offset;
	DWORD		dwFlags;
}
CHUNKHDR;

typedef struct _TIME
{
	float nominator, denominator;
}
TIME;

/*
typedef struct _VECTOR
{
	float x,y,z;
};

typedef struct _MATRIX
{
	VECTOR offset;
	VECTOR v1,v2,v3;
}
MATRIX;
*/

#define MakeID(a,b,c,d)	((ULONG)a | ((ULONG)b<<8) | ((ULONG)c<<16) | ((ULONG)d<<24))

#define ID_MC50	MakeID('M','C','5','0')
#define ID_DOK5	MakeID('D','O','K','5')

long ReadVECTOR(IStream* pStream, float vf[3]);
long WriteVECTOR(IStream* pStream, float vf[3]);
long ReadFLOAT(IStream* pStream, float* vf);
long ReadTIME(IStream* pStream, TIME* t);
long WriteTIME(IStream* pStream, TIME* t);
long WriteFLOAT(IStream* pStream, float* vf);

long CreateChunk(IStream* pStream, CHUNKHDR* ckhdr);
long ReadChunkHeader(IStream* pStream, CHUNKHDR* ckhdr);
long LeaveChunk(IStream* pStream, CHUNKHDR* lpck);

#if 0	// Have this
typedef struct _TRACK
{
	DWORD fileOffset;
	CI3DLayer* layerRef;
	_TRACK* next;
}
TRACK;
#endif

// Stream

ULONG Read(IStream* stream, void* pv, ULONG cb);
ULONG Write(IStream* stream, void* pv, ULONG cb);
ULONG GetPos(IStream* stream);
ULONG Seek(IStream* stream, LONG offset, DWORD dwOrigin);

#pragma pack(pop)
