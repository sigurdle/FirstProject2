#ifndef __MPEGAUDIODECODER_H_
#define __MPEGAUDIODECODER_H_

#include "MPEG/MPEGBitStream.h"

#include "AudioSequence.h"

namespace System
{
namespace MediaShow
{

class MPEGAudioDecoder : 
	public BaseFilterImpl
{
public:
	class InputPin : 
		public BasePinImpl
	{
	public:
		InputPin();

		virtual ErrorCode CheckConnect(IPin* pPin);

		virtual void BreakConnect();

		virtual ErrorCode CheckMediaType(MediaType * mt);

		virtual ErrorCode CompleteConnect(IPin *pPin);

		inline MPEGAudioDecoder* GetFilter() const
		{
			return (MPEGAudioDecoder*)m_pFilter;
		}
	};

	CTOR MPEGAudioDecoder();

	InputPin* m_pInputPin;
	AudioSequence* m_pOutputPin;

	System::IO::CBitStream32* m_pBitStream;
	System::IO::ISequentialByteStream* m_stream;

};

}	// MediaShow
}

#endif //__MPEGAUDIODECODER_H_
