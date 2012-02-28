#include "MPEGBitStream.h"

#define STREAM_MEMORY_BUFFER	1

namespace System
{
namespace MediaShow
{

class MpegDemultiplexer;
class CPacket;

class MpegStream :
	public IByteData
{
public:
	CTOR MpegStream()
	{
		m_stream_id = 0;
		m_bytestream = NULL;

		m_byteLength = 0;

// IByteStream
#if !STREAM_MEMORY_BUFFER
		m_curOffset = 0;
		m_packetOffset = 0;
		m_pcurpos = pStream->m_packets.GetHeadPosition();
#else
		m_pos = 0;
		m_buffer = NULL;
		m_size = NULL;
#endif
	}

//	CStreamByteStream* m_stream;

	list<CPacket*> m_packets;	// packets in this stream

	ULONGLONG m_byteLength;

	uint8 m_stream_id;
	IByteData* m_bytestream;

	MpegDemultiplexer* m_pFilter;

#if 0
	// Overiding this, as we don't use/need meminput on the pin we connect to
	virtual ErrorCode CheckConnect(IPin* pPin)
	{
		/*
		CComQIPtr<ILMemInputPin> memInput = pPin;
		if (memInput == NULL) return E_NOINTERFACE;

		m_pInputPin = memInput;
		*/

		return Success;
	}
#endif

// IByteStream
//	CMPEGStream* m_pStream;

#if !STREAM_MEMORY_BUFFER
	ULONGLONG m_curOffset;	// position relative to entire stream
	ULONG m_packetOffset;	// position relative to packet
	UPOSITION m_pcurpos;	// pointer to current packet
#else
	long m_pos;
	uint8* m_buffer;
	ULONGLONG m_size;
#endif

	ULONG Read(void *pv, LONGLONG pos, ULONG cb);
	//STDMETHOD(Seek)(LONGLONG dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
	/*
	STDMETHOD(Clone)(IByteStream* *pVal)
	{
		ATLASSERT(0);
		return E_NOTIMPL;
	}
	*/
	LONGLONG GetSize()
	{
		return -1;	// Unknown
	}
};

class CPacket
{
public:
	CTOR CPacket()
	{
		m_pStream = NULL;
	}

	MpegStream* m_pStream;	// The owning stream

	ULONGLONG m_byteOffset;
	//BYTE m_bitOffset;

	ULONG m_byteLength;
};

class MpegDemultiplexer
{
public:
	CTOR MpegDemultiplexer()
	{
		m_file = NULL;
	}

	void pack();
	void pack_header();
	void system_header();
	void program_stream_map_mpeg2();
	void packet_mpeg1();
	void PES_packet();

	MpegStream* FindStream(uint8 stream_id);

	ErrorCode Open();

public:

	IByteData* m_stream;
	BitStreamEx* m_file;

	list<MpegStream*> m_streams;	// Streams in this file

	bool m_mpeg1;
};

}	// MediaShow
}
