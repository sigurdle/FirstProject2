#ifndef __Mpeg4_SampleDescription_h__
#define __Mpeg4_SampleDescription_h__

namespace System
{
namespace Mpeg4
{

class SampleDescription
{
public:
	uint16 data_reference_index;

//	ILBaseFilter* m_decoder;
};

class DecoderSpecificInfo// : bit(8) tag=DecSpecificInfoTag
{
public:
	virtual ~DecoderSpecificInfo();

	//virtual void Read(IStream* stream) = 0;
};

class DecoderConfigDescriptor// tag=DecoderConfigDescrTag
{
public:

	CTOR DecoderConfigDescriptor();
	~DecoderConfigDescriptor();

	void Read(Stream& stream, BaseDescriptor* pDescriptor, Track* pTrack, SampleDescription* pSD);

	DecoderSpecificInfo* m_pDecoderSpecificInfo;
	ULONG m_maxBitrate;
	ULONG m_avgBitrate;

	uint8 m_objectTypeIndication;

	int	m_streamType : 6,
			m_upStream : 1,
			m_bufferSizeDB : 24;
};

// SL = Sync Layer

class SLConfigDescriptor// extends BaseDescriptor : bit(8) tag=SLConfigDescrTag {
{
public:
	//CSLConfigDescriptor();

	void Read(Stream& stream);

	int useAccessUnitStartFlag;
	int useAccessUnitEndFlag;
	int useRandomAccessPointFlag;
	int hasRandomAccessUnitsOnlyFlag;
	int usePaddingFlag;
	int useTimeStampsFlag;
	int useIdleFlag;
	int durationFlag;
	int timeStampResolution;
	int OCRResolution;
	int timeStampLength;
	int OCRLength;
	int AU_Length;
	int instantBitrateLength;
	int degradationPriorityLength;
	int AU_seqNumLength;
	int packetSeqNumLength;

	int timeScale;
	int accessUnitDuration;
	int compositionUnitDuration;
	int startDecodingTimeStamp;
	int startCompositionTimeStamp;
};

class ESDescriptor
{
public:
	CTOR ESDescriptor();
	~ESDescriptor();

	void Read(Stream& stream, BaseDescriptor* pDescriptor, Track* pTrack, SampleDescription* pSD);

	uint16 m_ES_ID;
	uint16 m_dependsOn_ES_ID;
	uint8* m_URLstring;
	uint16 m_OCR_ES_Id;

	//BYTE	m_streamDependenceFlag : 1,
	uint8	m_URL_Flag : 1,
			m_OCRstreamFlag : 1,
			m_streamPriority : 5;

	DecoderConfigDescriptor m_decoderConfigDescriptor;
	SLConfigDescriptor m_SLConfigDescr;
};

class MP4VSampleDescription : public SampleDescription
{
public:
	ESDescriptor es_descriptor;
//	VideoDec* m_decoder;	// ??
};

class MP4ASampleDescription : public SampleDescription
{
public:
	ESDescriptor es_descriptor;
};


}	// Mpeg4
}

#endif // __Mpeg4_SampleDescription_h__
