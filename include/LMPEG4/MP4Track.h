#ifndef Mpeg4_Track_h
#define Mpeg4_Track_h

#include "SampleDescription.h"

namespace System
{
namespace Mpeg4
{

struct SampleToChunk
{
	uint32 first_chunk;
	uint32 samples_per_chunk;
	uint32 sample_description_index;
};

struct TimeToSample
{
	uint32 sample_count;
	uint32 sample_delta;
};

class Chunk
{
public:
	ULONGLONG m_offset;
	uint32 m_sampleCount;
};

class Sample
{
public:
	/*
	inline CSample()
	{
		m_fileOffset = 0;
		m_fileSize = 0;
		m_duration = 0;
	}
	*/

	ULONGLONG m_fileOffset;
	uint32 m_fileSize;
	uint32 m_duration;
};

class MPEG4EXT MediaHeader
{
public:
	CTOR MediaHeader();

	ErrorCode Read(Stream& stream);

	uint32 m_timeScale;
	LONGLONG m_duration;
};

class MPEG4EXT TrackHeader
{
public:
	CTOR TrackHeader();

	ErrorCode Read(Stream& stream);

	uint32 m_trackID;
	LONGLONG m_duration;
};

class MPEG4EXT Track : public Object
{
public:

	CTOR Track();

	ErrorCode ReadTrackReference(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize);

	ErrorCode Read(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize);
	ErrorCode ReadTrackMedia(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize);
	ErrorCode ReadHandler(Stream& stream);
	ErrorCode ReadMediaInformation(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize);
	ErrorCode ReadSampleTable(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize);

	void ReadSampleDescription(Atom& ck, Stream& stream);
	void ReadTimeToSample(Atom& ck, Stream& stream);
	void ReadSampleToChunk(Atom& ck, Stream& stream);
	void ReadSyncSample(Atom& ck, Stream& stream);

	void ReadSampleSize(Stream& stream);
	void ReadChunkOffset(Stream& stream);

public:

	Movie* m_pMovie;

	uint32 m_handlerType;
	int m_streamType;

	TrackHeader m_trackHeader;

	MediaHeader m_mediaHeader;

	vector<SampleDescription*> m_sampleDescriptions;
	vector<Chunk> m_chunks;
	vector<Sample> m_samples;
	vector<uint32> m_syncsamples;
	uint8* m_sampleflags;

	vector<uint32> m_mpod;

	MP4VConfig* m_config;	// ??
	MP4VSampleDescription* m_pSampleDescription;	// ??
	VideoDec* m_decoder;	// ??
	BIFSDec* m_pBIFSDecoder;
};

}	// Mpeg4
}

#endif // Mpeg4_Track_h
