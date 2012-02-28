#ifndef MPEG4Movie_h
#define MPEG4Movie_h

namespace System
{

inline uint8 ReadByte(Stream& stream)
{
	uint8 byteval;
	stream.Read(&byteval, 1);
	return byteval;
}

namespace Mpeg4
{

#if WIN32

#define BigEndian64(x)	((((LONGLONG)(x) & 0x00000000000000ff)<<56) |  	 (((LONGLONG)(x) & 0x000000000000ff00)<<48) |   (((LONGLONG)(x) & 0x0000000000ff0000)<<40) | 			(((LONGLONG)(x) & 0x00000000ff000000)<<32) |	 (((LONGLONG)(x) & 0x000000ff00000000)>>32) | (((LONGLONG)(x) & 0x0000ff0000000000)>>40) |   (((LONGLONG)(x) & 0x00ff000000000000)>>48) | 		 (((LONGLONG)(x) & 0xff00000000000000)>>56))

#define MakeID(a,b,c,d)	((ULONG)a | ((ULONG)b<<8) | ((ULONG)c<<16) | ((ULONG)d<<24))

#else

#define BigEndian64(x)	(x)

#define MakeID(a,b,c,d)	((ULONG)d | ((ULONG)c<<8) | ((ULONG)b<<16) | ((ULONG)a<<24))

#endif


#define ID_moov	MakeID('m', 'o', 'o', 'v')
#define ID_cmov	MakeID('c', 'm', 'o', 'v')
#define ID_dcom	MakeID('d', 'c', 'o', 'm')
#define ID_cmvd	MakeID('c', 'm', 'v', 'd')
#define ID_mdat	MakeID('m', 'd', 'a', 't')
#define ID_uuid	MakeID('u', 'u', 'i', 'd')
#define ID_mvhd	MakeID('m', 'v', 'h', 'd')
#define ID_iods	MakeID('i', 'o', 'd', 's')
#define ID_trak	MakeID('t', 'r', 'a', 'k')
#define ID_tref	MakeID('t', 'r', 'e', 'f')
#define ID_mpod	MakeID('m', 'p', 'o', 'd')
#define ID_tkhd	MakeID('t', 'k', 'h', 'd')
#define ID_mdia	MakeID('m', 'd', 'i', 'a')
#define ID_mdhd	MakeID('m', 'd', 'h', 'd')
#define ID_hdlr	MakeID('h', 'd', 'l', 'r')
#define ID_minf	MakeID('m', 'i', 'n', 'f')
#define ID_dinf	MakeID('d', 'i', 'n', 'f')
#define ID_stbl	MakeID('s', 't', 'b', 'l')
#define ID_stsc	MakeID('s', 't', 's', 'c')
#define ID_stsd	MakeID('s', 't', 's', 'd')
#define ID_stts	MakeID('s', 't', 't', 's')
#define ID_ctts	MakeID('c', 't', 't', 's')
#define ID_stsz	MakeID('s', 't', 's', 'z')
#define ID_stco	MakeID('s', 't', 'c', 'o')
#define ID_stss	MakeID('s', 't', 's', 's')
#define ID_esds	MakeID('e', 's', 'd', 's')
#define ID_mp4s	MakeID('m', 'p', '4', 's')
#define ID_mp4v	MakeID('m', 'p', '4', 'v')
#define ID_mp4a	MakeID('m', 'p', '4', 'a')

// handler types
#define ID_soun	MakeID('s', 'o', 'u', 'n')
#define ID_vide	MakeID('v', 'i', 'd', 'e')
#define ID_hint	MakeID('h', 'i', 'n', 't')
#define ID_odsm	MakeID('o', 'd', 's', 'm')

enum
{
	AppleDataCompressorSubType	= MakeID('a','d','e','c'),
	zlibDataCompressorSubType	= MakeID('z','l','i','b'),
};

class MPEG4EXT Atom
{
public:
	ErrorCode Seek(Stream& stream);
	ErrorCode Descend(Stream& stream);
	ErrorCode Ascend(Stream& stream);

	uint32 m_atomtype;
	LONGLONG m_pos;
	LONGLONG m_size;
	LONGLONG m_contentpos;
	LONGLONG m_contentsize;
	GUID m_usertype;
};

class MPEG4EXT AtomCollection
{
public:
	void Add(Atom& atom);

	Atom* GetAtom(uint32 atomtype);

	vector<Atom> m_items;
};

class MPEG4EXT BaseDescriptor
{
public:
	CTOR BaseDescriptor();

	bool More(Stream& pStream);
	ErrorCode Descend(Stream& pStream);
	ErrorCode Ascend(Stream& pStream);

	uint8 m_tag;
	uint32 m_sizeOfInstance;

	LONGLONG m_pos;
};

class MPEG4EXT InitialObjectDescriptor
{
public:

	ErrorCode Read(Stream& stream);

	uint16 m_ObjectDescriptorID;

	vector<uint32> m_trackID;
};

class MPEG4EXT ObjectDescriptor : public Object
{
public:

	Track* m_pTrack;

	uint16 m_ObjectDescriptorID;
	uint16 m_refIndex;
	//CArray<WORD,WORD> m_refIndex;

//	ErrorCode Read(IStream* stream);
};

class MPEG4EXT MovieHeader
{
public:

	ErrorCode Read(Stream& stream);

	uint32 m_timeScale;
};

class MPEG4EXT Movie : public Object
{
public:

	CTOR Movie();

	bool ReadFile(StringIn filename);
	bool ReadFile(Stream& stream);

	ErrorCode ReadFile(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize);
	ErrorCode ReadMovie(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize);
	ErrorCode ReadCompressedMovie(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize);

	vector<Track*>& get_Tracks()
	{
		return m_tracks;
	}

	Track* GetTrackById(uint32 trackID);

	ErrorCode ReceiveObjectDescriptorUpdate(Track* pTrack, int ODid, uint16 refIndex);

//	Stream m_stream;

	MovieHeader m_movieHeader;
	InitialObjectDescriptor m_initialObjectDescriptor;
	vector<ObjectDescriptor*> m_od;
	vector<Track*> m_tracks;
};

}	// Mpeg4
}

#endif // MPEG4Movie_h
