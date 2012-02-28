#ifndef __LMPEGDEMULTIPLEXER_H_
#define __LMPEGDEMULTIPLEXER_H_

#include "MPEGDemultiplexer.h"

namespace System
{
namespace MediaShow
{

class CLMPEGDemultiplexer;

/*
class IByteStream
{
public:
	virtual ErrorCode Read(void *pv, ULONG cb, ULONG *pcbRead) = 0;
	virtual ErrorCode Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition) = 0;
};
*/

#if 0
class CFileStream : public IByteStream
{
public:
	CFileStream(IStream* stream)
	{
		m_stream = stream;
	}

	CComPtr<IStream> m_stream;//CLMPEGDemultiplexer* m_decoder;

	ErrorCode Read( 
            /* [length_is][size_is][out] */ void *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead)
	{
		/*
		CopyMemory(pv, m_buffer + m_pos, cb);
		m_pos += cb;
		if (pcbRead)
			*pcbRead = cb;
		return S_OK;
		*/

		return m_stream->Read(pv, cb, pcbRead);
	}

	ErrorCode Seek(
            /* [in] */ LARGE_INTEGER dlibMove,
            /* [in] */ DWORD dwOrigin,
            /* [out] */ ULARGE_INTEGER *plibNewPosition)
	{
		/*
		if (dwOrigin == STREAM_SEEK_SET)
			m_pos = dlibMove.QuadPart;
		else if (dwOrigin == STREAM_SEEK_CUR)
			m_pos += dlibMove.QuadPart;
		else
			m_pos = m_size + dlibMove.QuadPart;

		if (plibNewPosition)
			(*plibNewPosition).QuadPart = m_pos;

		return S_OK;
*/
		return m_stream->Seek(dlibMove, dwOrigin, plibNewPosition);
	}
};
#endif


/*
class CMPEGStream : public IMPEGStream
{
public:
	CMPEGStream()
	{
	}

	virtual ErrorCode ReadBitStream(CBitStream* bitstream) = 0;
};
*/

#if 0
class CVideoSequence;

class ATL_NO_VTABLE CMPEGVideoStream :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CMPEGStream,
//	public ILMediaStream,
	public ILMediaSeeking,
	public ILVideo,
	public ILStreamInfo,
	public ILVideoStreamInfo
{
public:
	CMPEGVideoStream()
	{
		m_pVideoSequence = NULL;
	}

//	CComObject<CVideoSequence>* m_pVideoSequence;

	ErrorCode ReadBitStream(CBitStream* bitstream);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMPEGVideoStream)
	COM_INTERFACE_ENTRY(IMPEGStream)
	COM_INTERFACE_ENTRY(ILMediaStream)
	COM_INTERFACE_ENTRY(ILMediaSeeking)
	COM_INTERFACE_ENTRY(ILVideo)
	COM_INTERFACE_ENTRY(ILStreamInfo)
	COM_INTERFACE_ENTRY(ILVideoStreamInfo)
END_COM_MAP()

// ILMediaStream
	STDMETHOD(GetStreamType)(LStreamType* pVal);
//	STDMETHOD(GetUnknown)(IUnknown* *pVal);

// ILMediaSeeking
	STDMETHOD(Seek)(double seconds);
	STDMETHOD(GetDuration)(double* pVal);

// ILVideo
	STDMETHOD(GetWidth)(long *pVal);
	STDMETHOD(GetHeight)(long *pVal);
	STDMETHOD(GetSample)(ILVideoSample* *pVal);
	STDMETHOD(SetSample)(ILVideoSample* newVal);

//	ILStreamInfo
	STDMETHOD(GetBitRate)(long* pVal);
	STDMETHOD(GetCodec)(BSTR *pVal);

// ILVideoStreamInfo
	STDMETHOD(GetFrameRate)(double* pVal);
};

class CAudioSequence;

class ATL_NO_VTABLE CMPEGAudioStream :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CMPEGStream,
	public ILBaseOutputPin,
	public ILMediaSeeking,
{
public:
	CMPEGAudioStream()
	{
		m_pAudioSequence = NULL;
	}

	CAudioSequence* m_pAudioSequence;

	ErrorCode ReadBitStream(CBitStream* bitstream);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMPEGAudioStream)
	COM_INTERFACE_ENTRY(IMPEGStream)
	COM_INTERFACE_ENTRY(ILMediaStream)
	COM_INTERFACE_ENTRY(ILPin)
	COM_INTERFACE_ENTRY(ILMediaSeeking)
END_COM_MAP()

// ILMediaStream
	STDMETHOD(GetStreamType)(LStreamType* pVal);
//	STDMETHOD(GetUnknown)(IUnknown* *pVal);

// ILMediaSeeking
	STDMETHOD(Seek)(LONGLONG t);
	STDMETHOD(GetDuration)(LONGLONG* pVal);

// ILAudio
	STDMETHOD(GetSamples)(LONGLONG *pVal);
	STDMETHOD(GetFormat)(WAVEFORMATEX *pVal);
	STDMETHOD(GetChunkSize)(long nchunk, ULONG* pVal);
	STDMETHOD(ReadChunk)(long nchunk, LPSTR buffer, ULONG nsamples);
};
#endif

#if 0
class CStreamByteStream : public IByteStream
{
public:
	CStreamByteStream(CMPEGStream* pStream)
	{
		m_pStream = pStream;

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

	CMPEGStream* m_pStream;

#if !STREAM_MEMORY_BUFFER
	ULONGLONG m_curOffset;	// position relative to entire stream
	ULONG m_packetOffset;	// position relative to packet
	UPOSITION m_pcurpos;	// pointer to current packet
#else
	long m_pos;
	LPBYTE m_buffer;
	ULONGLONG m_size;
#endif

	ErrorCode Read(void *pv, ULONG cb, ULONG *pcbRead);
	ErrorCode Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
};
#endif

class MPEGDemultiplexer : 
	public BaseFilterImpl	// ILMediaFilter
{
public:

	class InputPin : public BasePinImpl
	{
	public:
		CTOR InputPin();
		virtual ErrorCode CheckConnect(IPin* pPin);

		virtual void BreakConnect();

		virtual ErrorCode CheckMediaType(MediaType * mt);

		virtual ErrorCode CompleteConnect(IPin* pConnector);

		inline MPEGDemultiplexer* GetFilter() const
		{
			return (MPEGDemultiplexer*)m_pFilter;
		}

		//STDMETHOD(ReceiveConnection)(ILPin* pConnector, ILMediaType* pMediaType);

		//STDMETHOD(Receive)(ILVideoSample *pSample);
	};

	class CMPEGStream : 
		//public IMPEGStream,
		public BaseOutputPinImpl,
		public IByteData
	{
	public:
		CTOR CMPEGStream();

	//	CStreamByteStream* m_stream;

		MpegStream* m_mpeg_stream;

		IByteData* m_bytestream;

		// Overiding this, as we don't use/need meminput on the pin we connect to
		virtual ErrorCode CheckConnect(IPin* pPin);

		virtual ErrorCode CheckMediaType(MediaType * mt);

		virtual ErrorCode GetMediaType(int iPosition, MediaType ** pMediaType);

		inline MPEGDemultiplexer* GetFilter() const
		{
			return (MPEGDemultiplexer*)m_pFilter;
		}

		CMPEGStream* m_pStream;

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

	MPEGDemultiplexer();

	InputPin* m_pInputPin;

	IByteData* m_stream;

//	CVideoSequence* m_videoSequence;

	/*
	CMPEGStream* FindStream(uint8 stream_id)
	{
		UPOSITION pos = m_streams.GetHeadPosition();
		while (pos)
		{
			CMPEGStream* pStream = (CMPEGStream*)m_streams.GetNext(pos);
			if (pStream->m_stream_id == stream_id)
			{
				return pStream;
			}
		}

		return NULL;
	}
	*/

	MpegDemultiplexer* m_mpeg_program;

};

}	// MediaShow
}

#endif //__LMPEGDEMULTIPLEXER_H_
