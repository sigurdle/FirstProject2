#include "stdafx.h"
#include "LMPEG4.h"

namespace System
{
namespace MediaShow
{

MPEG4Filter::CInputPin::CInputPin() : BasePinImpl(PINDIR_INPUT)
{
}

ErrorCode MPEG4Filter::CInputPin::CheckConnect(IPin* pPin)
{
	// Call base class first
	ErrorCode hr = BasePinImpl::CheckConnect(pPin);
	if (hr < 0) return hr;

	IByteData* stream = dynamic_cast<IByteData*>(pPin);
	if (stream == NULL) return Error_NoInterface;

	GetFilter()->m_stream = new ByteStreamWrapper(stream);

	return Success;
}

void MPEG4Filter::CInputPin::BreakConnect()
{
	// Release what we obtained in CheckConnect
	GetFilter()->m_stream = NULL;
}

ErrorCode MPEG4Filter::CInputPin::CheckMediaType(MediaType* mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Stream)
		return Error;

	return Success;
}

ErrorCode MPEG4Filter::CInputPin::CompleteConnect(IPin* pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

//	GetFilter()->m_pMovie->m_stream = GetFilter()->m_stream;

	LONGLONG pos = GetFilter()->m_stream.Seek(0, IO::STREAM_SEEK_CUR);
	LONGLONG size = 0xfffffffffff;
	hr = GetFilter()->m_pMovie->ReadFile(GetFilter()->m_stream, pos, size);
	if (hr >= 0)
	{
		for (int i = 0; i < GetFilter()->m_pMovie->m_tracks.GetSize(); i++)
		{
			Mpeg4::Track* track = GetFilter()->m_pMovie->m_tracks[i];

			if (track->m_decoder)
			{
				COutputPin* pV = new COutputPin;
				pV->m_pTrack = track;
				CVideoDecoder* pVideo = new CVideoDecoder;
				pVideo->m_pTrack = track;
				pVideo->m_decoder = track->m_decoder;
				m_pFilter->m_pFilterGraph->AddFilter(pVideo);
				ErrorCode hr = pV->Connect(pVideo->m_pInputPin, NULL);
				ASSERT(hr >= 0);

				m_pFilter->AddPin(pV);
			}
			else if (track->m_pBIFSDecoder)
			{
				COutputPin* pV = new COutputPin;
				pV->m_pTrack = track;
				CBIFSDecoder* pFilter = new CBIFSDecoder;
			//	pVideo->m_pTrack = track;
				pFilter->m_pDec = track->m_pBIFSDecoder;
				m_pFilter->m_pFilterGraph->AddFilter(pFilter);
				ErrorCode hr = pV->Connect(pFilter->m_pInputPin, NULL);
				ASSERT(hr >= 0);

				m_pFilter->AddPin(pV);
			}
		}

		return Success;
	}
	else
		return hr;

#if 0
	ASSERT(m_pFilter->m_pVideo == NULL);
	CComObject<CVideoSequence>::CreateInstance(&m_pFilter->m_pVideo);
	m_pFilter->m_pVideo->m_pFilter = m_pFilter;
	m_pFilter->AddPin(m_pFilter->m_pVideo);

	m_pFilter->m_pVideo->m_file = new CBitStream(stream);
	m_pFilter->m_pVideo->m_file->next_start_code();

	return m_pFilter->m_pVideo->video_sequence();
#endif
	return -1;
}

#if 0
// ILBaseFilter
STDMETHODIMP MPEG4Filter::Run(LONGLONG tStart)
{
	m_criticalSection.Lock();

	m_state = LState_Running;
	m_tStart = tStart;

	for (int i = 0; i < m_initialObjectDescriptor.m_trackID.GetSize(); i++)
	{
		CTrack* pTrack = GetTrackById(m_initialObjectDescriptor.m_trackID[i]);
		if (pTrack)
		{
			if (pTrack->m_sampleDescriptions[0]->m_decoder)
			{
				pTrack->m_sampleDescriptions[0]->m_decoder->Run(tStart);
			}
		}
	}

	m_criticalSection.Unlock();

	return S_OK;
}
#endif

}	// Media
}
