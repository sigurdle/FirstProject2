#include "StdAfx.h"
#include "LMPEGAudio.h"
#include "LMPEGAudioDecoder.h"

#include "AudioSequence.h"

namespace System
{
namespace MediaShow
{

MPEGAudioDecoder::InputPin::InputPin() : BasePinImpl(PINDIR_INPUT)
{
}

ErrorCode MPEGAudioDecoder::InputPin::CheckConnect(IPin* pPin)
{
	// Call base class first
	ErrorCode hr = BasePinImpl::CheckConnect(pPin);
	if (hr < 0) return hr;

	IByteData* stream = dynamic_cast<IByteData*>(pPin);
	if (stream == NULL) return Error_NoInterface;

	GetFilter()->m_stream = new ByteStreamWrapper(stream);

	return Success;
}

void MPEGAudioDecoder::InputPin::BreakConnect()
{
	// Release what we obtained in CheckConnect
	GetFilter()->m_stream = NULL;
}

ErrorCode MPEGAudioDecoder::InputPin::CheckMediaType(MediaType* mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Stream)
		return Error;

	return Success;
}

ErrorCode MPEGAudioDecoder::InputPin::CompleteConnect(IPin *pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

	GetFilter()->m_pBitStream = new System::IO::CBitStream32(new System::IO::CByteStream(GetFilter()->m_stream));

	GetFilter()->m_pOutputPin->m_mpeg_audio->m_file = GetFilter()->m_pBitStream;

	GetFilter()->m_pOutputPin->m_mpeg_audio->header();
	GetFilter()->m_pOutputPin->m_mpeg_audio->m_file->ungetbits(32);

	return Success;
}

MPEGAudioDecoder::MPEGAudioDecoder()
{
	m_pInputPin = NULL;
	m_pOutputPin = NULL;

	m_pInputPin = new InputPin;
	m_pInputPin->m_pFilter = this;
	m_pInputPin->m_id = WSTR("Stream Input");
	AddPin(m_pInputPin);

	m_pOutputPin = new AudioSequence;
	m_pOutputPin->m_pFilter = this;
	m_pOutputPin->m_id = WSTR("Audio Output");
	AddPin(m_pOutputPin);
}

}	// MediaShow
}
