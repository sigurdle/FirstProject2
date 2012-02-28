#include "StdAfx.h"
#include "MPEG.h"
#include "LMPEGDemultiplexer.h"

namespace System
{
namespace MediaShow
{

MPEGDemultiplexer::MPEGDemultiplexer()
{
//	m_videoSequence = NULL;
	m_stream = NULL;

	m_pInputPin = new InputPin;
	m_pInputPin->m_pFilter = this;
	m_pInputPin->m_id = WSTR("Stream Input");
	AddPin(m_pInputPin);
}

/////////////////////////////////////////////////////////////////////////////
// InputPin

MPEGDemultiplexer::InputPin::InputPin() : BasePinImpl(PINDIR_INPUT)
{
}

ErrorCode MPEGDemultiplexer::InputPin::CheckConnect(IPin* pPin)
{
	// Call base class first
	ErrorCode hr = BasePinImpl::CheckConnect(pPin);
	if (hr < 0) return hr;

	IByteData* stream = dynamic_cast<IByteData*>(pPin);
	if (stream == NULL) return Error_NoInterface;

	GetFilter()->m_stream = stream;

	return Success;
}

void MPEGDemultiplexer::InputPin::BreakConnect()
{
	// Release what we obtained in CheckConnect
	GetFilter()->m_stream = NULL;
}

ErrorCode MPEGDemultiplexer::InputPin::CheckMediaType(MediaType* mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Stream)
		return Error_Failed;

	return Success;
}

ErrorCode MPEGDemultiplexer::InputPin::CompleteConnect(IPin* pConnector)
{
	ErrorCode hr;

	hr = BasePinImpl::CompleteConnect(pConnector);
	if (hr < 0) return hr;

//	CComQIPtr<ILByteStream> stream = m_connectedTo;

#if 0
	m_pFilter->m_pOutputPin->m_stream = stream;
#endif

	GetFilter()->m_mpeg_program = new MpegDemultiplexer;
	GetFilter()->m_mpeg_program->m_stream = GetFilter()->m_stream;

	hr = GetFilter()->m_mpeg_program->Open();

	list<MpegStream*>::iterator pos = GetFilter()->m_mpeg_program->m_streams.begin();
	while (pos != GetFilter()->m_mpeg_program->m_streams.end())
	{
		MpegStream* p = *pos;
		++pos;

		CMPEGStream* pStream = new CMPEGStream;
		pStream->m_mpeg_stream = p;
		pStream->m_pFilter = m_pFilter;
		pStream->m_id = WSTR("Stream Output");
		m_pFilter->AddPin(pStream);
	}

#if 0
	CComObject<CMediaType>::CreateInstance(&m_pFilter->m_pOutputPin->m_pMediaType);
	m_pFilter->m_pOutputPin->m_pMediaType->AddRef();
	m_pFilter->m_pOutputPin->m_pMediaType->m_pFilter = m_pFilter;
#endif

	return hr;
}


/////////////////////////////////////////////
// IMediaSeeking

/*
STDMETHODIMP CLMPEGDemultiplexer::Seek(double seconds)
{
	UPOSITION pos = m_streams.GetHeadPosition();
	while (pos)
	{
		IMPEGStream* stream = (IMPEGStream*)m_streams.GetNext(pos);

		CComQIPtr<ILMediaSeeking> seeking = stream;
		if (seeking)
		{
			seeking->Seek(seconds);
		}
	}

	return Success;
}

STDMETHODIMP CLMPEGDemultiplexer::GetDuration(double* pVal)
{
	if (pVal == NULL) return E_POINTER;
	double maxdur = 0;

	UPOSITION pos = m_streams.GetHeadPosition();
	while (pos)
	{
		IMPEGStream* stream = (IMPEGStream*)m_streams.GetNext(pos);

		CComQIPtr<ILMediaSeeking> seeking = stream;
		if (seeking)
		{
			double dur;
			seeking->GetDuration(&dur);

			maxdur = max(dur, maxdur);
		}
	}

	*pVal = maxdur;
	return Success;
}
*/

/////////////////////////////////////////////
// CStreamByteStream

#if !STREAM_MEMORY_BUFFER
ErrorCode CStreamByteStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	int nbytesRead = 0;
	LPBYTE p = (LPBYTE)pv;

	CPacket* pPacket = (CPacket*)m_pStream->m_packets.GetAt(m_pcurpos);

	LARGE_INTEGER li;
	li.QuadPart = pPacket->m_byteOffset + m_packetOffset;
	m_pStream->m_decoder->m_file->m_byteStream->Seek(li, STREAM_SEEK_SET, NULL);

	while (nbytesRead < cb)
	{
		int count = cb-nbytesRead;
		if (m_packetOffset+count > pPacket->m_byteLength)
		{
		// Finish reading current packet data
			count = pPacket->m_byteLength - m_packetOffset;

			m_pStream->m_decoder->m_file->m_byteStream->Read(p, count, NULL);

			p += count;
			nbytesRead += count;

		// Place ourselves on next packet
			m_pStream->m_packets.GetNext(m_pcurpos);
			pPacket = (CPacket*)m_pStream->m_packets.GetAt(m_pcurpos);
			m_packetOffset = 0;

			LARGE_INTEGER li;
			li.QuadPart = pPacket->m_byteOffset + m_packetOffset;
			m_pStream->m_decoder->m_file->m_byteStream->Seek(li, STREAM_SEEK_SET, NULL);
		}
		else
		{
			m_packetOffset += count;

			m_pStream->m_decoder->m_file->m_byteStream->Read(p, count, NULL);

			p += count;
			nbytesRead += count;
		}
	}

	m_curOffset += nbytesRead;

	if (pcbRead)
		*pcbRead = nbytesRead;

	return Success;
}

ErrorCode CStreamByteStream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
{
	if (dwOrigin == STREAM_SEEK_SET)
	{
		m_curOffset = dlibMove.QuadPart;
	}
	else if (dwOrigin == STREAM_SEEK_CUR)
	{
		m_curOffset += dlibMove.QuadPart;
	}
	else
		ASSERT(0);//
		//m_curpos = m_size + dlibMove.QuadPart;

// Find packet and offset relative to packet
	ULONGLONG offset = 0;
	UPOSITION pos = m_pStream->m_packets.GetHeadPosition();
	while (pos)
	{
		m_pcurpos = pos;

		CPacket* pPacket = (CPacket*)m_pStream->m_packets.GetNext(pos);

		m_packetOffset = m_curOffset - offset;

		if (offset+pPacket->m_byteLength > m_curOffset)
			break;

		offset += pPacket->m_byteLength;
	}

	if (plibNewPosition)
		(*plibNewPosition).QuadPart = m_curOffset;

	return Success;
}

#else

ULONG MpegStream::Read(void *pv, LONGLONG pos, ULONG cb)
{
	m_pos = pos;

	ULONG bytesToRead = cb;
	if (m_pos+cb > m_size)
		bytesToRead = m_size-m_pos;

	memcpy(pv, m_buffer + m_pos, bytesToRead);
	m_pos += bytesToRead;

	return bytesToRead;
}

MPEGDemultiplexer::CMPEGStream::CMPEGStream()
{
	m_bytestream = NULL;

}

// Overiding this, as we don't use/need meminput on the pin we connect to
ErrorCode MPEGDemultiplexer::CMPEGStream::CheckConnect(IPin* pPin)
{

	return Success;
}

ErrorCode MPEGDemultiplexer::CMPEGStream::CheckMediaType(MediaType * mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Stream)
		return Error_Failed;

	return Success;
}

ErrorCode MPEGDemultiplexer::CMPEGStream::GetMediaType(int iPosition, MediaType ** pMediaType)
{
	if (iPosition == 0)
	{
		ErrorCode hr;

		MediaType* mediaType = new MediaType(LMEDIATYPE_Stream);
	//	mediaType.SetMajorType(LMEDIATYPE_Stream);

		*pMediaType = mediaType;

		return Success_True;
	}
	else
	{
		pMediaType = NULL;
		return Success_False;
	}
}

ULONG MPEGDemultiplexer::CMPEGStream::Read(void *pv, LONGLONG pos, ULONG cb)
{
	return m_mpeg_stream->Read(pv, pos, cb);
}

#if 0
ErrorCode CLMPEGDemultiplexer::CMPEGStream::Seek(
            /* [in] */ LARGE_INTEGER dlibMove,
            /* [in] */ DWORD dwOrigin,
            /* [out] */ ULARGE_INTEGER *plibNewPosition)
{
	if (dwOrigin == STREAM_SEEK_SET)
		m_pos = dlibMove.QuadPart;
	else if (dwOrigin == STREAM_SEEK_CUR)
		m_pos += dlibMove.QuadPart;
	else
		m_pos = m_size + dlibMove.QuadPart;

	if (plibNewPosition)
		(*plibNewPosition).QuadPart = m_pos;

	return Success;
}
#endif
#endif

}	// MediaShow
}
