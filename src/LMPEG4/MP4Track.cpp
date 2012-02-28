#include "stdafx.h"
#include "LMPEG4.h"

#if AMIGA
#define TRACE printf
#endif

/*
#include "MP4Track.h"

#include "MP4File.h"

//using namespace System;
//using namespace System::IO;

#include "BIFSDec.h"
#include "VideoDec.h"
//#include "BIFS.h"
*/

#if 0
#include "ODDecoder.h"
#endif

namespace System
{
namespace Mpeg4
{

StringW* ReadString(System::IO::CBitStream32* pBitStream);

//int next_start_code(System::IO::CBitStream32* pBitStream);	// For MP4Video

/*
List of Class Tags for Descriptors

0x00 Forbidden
0x01 ObjectDescrTag
0x02 InitialObjectDescrTag
0x03 ES_DescrTag
0x04 DecoderConfigDescrTag
0x05 DecSpecificInfoTag
0x06 SLConfigDescrTag
0x07 ContentIdentDescrTag
0x08 SupplContentIdentDescrTag
0x09 IPI_DescrPointerTag
0x0A IPMP_DescrPointerTag
0x0B IPMP_DescrTag
0x0C QoS_DescrTag
0x0D RegistrationDescrTag
0x0E ES_ID_IncTag
0x0F ES_ID_RefTag
0x10 MP4_IOD_Tag
0x11 MP4_OD_Tag
0x12 IPL_DescrPointerRefTag
0x13 ExtendedProfileLevelDescrTag
0x14 profileLevelIndicationIndexDescrTag
0x15-0x3F Reserved for ISO use
0x40 ContentClassificationDescrTag
0x41 KeyWordDescrTag
0x42 RatingDescrTag
0x43 LanguageDescrTag
0x44 ShortTextualDescrTag
0x45 ExpandedTextualDescrTag
0x46 ContentCreatorNameDescrTag
0x47 ContentCreationDateDescrTag
0x48 OCICreatorNameDescrTag
0x49 OCICreationDateDescrTag
0x4A SmpteCameraPositionDescrTag
0x4B-0x5F Reserved for ISO use (OCI extensions)
0x60-0xBF Reserved for ISO use
0xC0-0xFE User private
0xFF Forbidden
*/

/*
List of Class Tags for Commands

0x00 forbidden
0x01 ObjectDescrUpdateTag
0x02 ObjectDescrRemoveTag
0x03 ES_DescrUpdateTag
0x04 ES_DescrRemoveTag
0x05 IPMP_DescrUpdateTag
0x06 IPMP_DescrRemoveTag
0x07 ES_DescrRemoveRefTag
0x08-0xBF Reserved for ISO (command tags)
0xC0-0xFE User private
0xFF forbidden
*/


class SampleEntry
{
public:
	void Read(Stream& stream)
	{
		ULONG nRead;

		uint8 reserved[6];
		nRead = stream.Read(reserved, 6);

		nRead = stream.Read(&data_reference_index, 2);
		data_reference_index = BigEndian16(data_reference_index);
	}

	uint16 data_reference_index;
};

class JPEGDecoderConfig : public DecoderSpecificInfo// extends DecoderSpecificInfo : bit(8) tag=DecSpecificInfoTag
{
public:
	virtual void Read(IO::CByteStream* stream)
	{
		IO::CBitStream32 bitstream(stream);
		IO::CBitStream32* pBitStream = &bitstream;

		headerLength = pBitStream->getnbits(16);
		Xdensity = pBitStream->getnbits(16);
		Ydensity = pBitStream->getnbits(16);
		numComponents = pBitStream->getnbits(8);
	}

	uint16 headerLength;
	uint16 Xdensity;
	uint16 Ydensity;
	uint8 numComponents;
};

class BIFSConfig : public DecoderSpecificInfo// : bit(8) tag=DecSpecificInfoTag
{
public:
	//int	m_nodeIDbits : 5,
	//		m_routeIDbits : 5;

	virtual void Read(Stream& stream, BIFSConfiguration* pConfig)
	{
	//	System::IO::CBitStream bitstream(stream);
	//	System::IO::CBitStream32* pBitStream = &bitstream;

		IO::BitStream bitstream(stream);

		pConfig->use3DmeshCoding = false;
		pConfig->nodeIDbits = bitstream.getnbits(5);
		pConfig->routeIDbits = bitstream.getnbits(5);

		int isCommandStream = bitstream.getbit();
		if (isCommandStream)
		{
			int pixelMetric = bitstream.getbit();	// 1 meter is set to be
																		// equal to the distance between two pixels. This applies to both the horizontal (x-axis) and vertical (y-axis) directions.

			bool hasSize = bitstream.getbit();

			if (hasSize)
			{
				uint16 pixelWidth = bitstream.getnbits(16);
				uint16 pixelHeight = bitstream.getnbits(16);
			}
		}
		else
		{
			ASSERT(0);
			/*
			bit(1) randomAccess;
			AnimationMask animMask();
			*/
		}
	}
};

class BIFSv2Config : public BIFSConfig//CDecoderSpecificInfo
{
public:

	/*
	int	m_use3DmeshCoding : 1,
			m_nodeIDbits : 5,
			m_routeIDbits : 5,
			m_PROTOIDbits : 5;
			*/

	virtual void Read(Stream& stream, BIFSConfiguration* pConfig)
	{
		IO::BitStream bitstream(stream);

		pConfig->use3DmeshCoding = bitstream.getbit();

		int reserved = bitstream.getbit();

		pConfig->nodeIDbits = bitstream.getnbits(5);
		pConfig->routeIDbits = bitstream.getnbits(5);
		pConfig->PROTOIDbits = bitstream.getnbits(5);

		int isCommandStream = bitstream.getbit();
		if (isCommandStream)
		{
			int pixelMetric = bitstream.getbit();

			int hasSize = bitstream.getbit();
			if (hasSize)
			{
				int pixelWidth = bitstream.getnbits(16);
				int pixelHeight = bitstream.getnbits(16);
			}
		}
		else
		{
			ASSERT(0);
/*
			bit(1) randomAccess;
			AnimationMask animMask();
			*/
		}
	}
};

///////////////////////////////////////////////////////////////////////
// CSLConfigDescriptor

void SLConfigDescriptor::Read(Stream& stream)
{
	IO::BitStream bitstream(stream);
	IO::BitStream* pBitStream = &bitstream;

	int predefined = pBitStream->getnbits(8);
	if (predefined == 0)
	{
		useAccessUnitStartFlag = pBitStream->getbit();
		useAccessUnitEndFlag = pBitStream->getbit();
		useRandomAccessPointFlag = pBitStream->getbit();
		hasRandomAccessUnitsOnlyFlag = pBitStream->getbit();
		usePaddingFlag = pBitStream->getbit();
		useTimeStampsFlag = pBitStream->getbit();
		useIdleFlag = pBitStream->getbit();
		durationFlag = pBitStream->getbit();
		timeStampResolution = pBitStream->getnbits(32);
		OCRResolution = pBitStream->getnbits(32);
		timeStampLength = pBitStream->getnbits(8); // must be . 64
		OCRLength = pBitStream->getnbits(8); // must be . 64
		AU_Length = pBitStream->getnbits(8); // must be . 32
		instantBitrateLength = pBitStream->getnbits(8);
		degradationPriorityLength = pBitStream->getnbits(4);
		AU_seqNumLength = pBitStream->getnbits(5); // must be . 16
		packetSeqNumLength = pBitStream->getnbits(5); // must be . 16

		int reserved = pBitStream->getnbits(2);//=0b11;
		ASSERT(reserved == 0x3);
	}
	else if (predefined == 1)
	{
		useAccessUnitStartFlag = 0;
		useAccessUnitEndFlag = 0;
		useRandomAccessPointFlag = 0;
		usePaddingFlag = 0;
		useTimeStampsFlag = 0;
		useIdleFlag = 0;
		//DurationFlag - 0
		timeStampResolution = 1000;
		//OCRResolution - -
		timeStampLength = 32;
		//OCRlength - 0
		AU_Length = 0;
		//InstantBitrateLength - 0
		degradationPriorityLength = 0;
		AU_seqNumLength = 0;
		packetSeqNumLength = 0;
		//TimeScale - -
		//AccessUnitDuration - -
		//CompositionUnitDuration - -
		//StartDecodingTimeStamp - -
		//StartCompositionTimeStamp - -
	}
	else if (predefined == 2)
	{
		useAccessUnitStartFlag = 0;
		useAccessUnitEndFlag = 0;
		useRandomAccessPointFlag = 0;
		usePaddingFlag = 0;
		useTimeStampsFlag = 1;
		useIdleFlag = 0;
		durationFlag = 0;
		//TimeStampResolution 1000 -
		//OCRResolution - -
		timeStampLength = 0;
		OCRLength = 0;
		AU_Length = 0;
		instantBitrateLength = 0;
		degradationPriorityLength = 0;
		AU_seqNumLength = 0;
		packetSeqNumLength = 0;
		//TimeScale - -
		//AccessUnitDuration - -
		//CompositionUnitDuration - -
		//StartDecodingTimeStamp - -
		//StartCompositionTimeStamp - -
	}
	else
	{
		ASSERT(0);
		throw L"Unknown value for predefined in SL Descriptor";
	}

	if (durationFlag)
	{
		timeScale = pBitStream->getnbits(32);
		accessUnitDuration = pBitStream->getnbits(16);
		compositionUnitDuration = pBitStream->getnbits(16);
	}

	if (!useTimeStampsFlag)
	{
		startDecodingTimeStamp = pBitStream->getnbits(timeStampLength);
		startCompositionTimeStamp = pBitStream->getnbits(timeStampLength);
	}
}

class SLPacketHeader
{
public:
	void Read(System::IO::CBitStream32* pBitStream, SLConfigDescriptor* SL)
	{
		int accessUnitStartFlag;
		int accessUnitEndFlag;
		int OCRflag;
		int idleFlag;

		int packetSequenceNumber;
		int DegPrioflag;
		int degradationPriority;
		int objectClockReference;

		if (SL->useAccessUnitStartFlag)
			accessUnitStartFlag = pBitStream->getbit();

		if (SL->useAccessUnitEndFlag)
			accessUnitEndFlag = pBitStream->getbit();

		if (SL->OCRLength>0)
			OCRflag = pBitStream->getbit();

		if (SL->useIdleFlag)
			idleFlag = pBitStream->getbit();

		int paddingFlag;
		if (SL->usePaddingFlag)
			paddingFlag = pBitStream->getbit();

		int paddingBits;
		if (paddingFlag)
			paddingBits = pBitStream->getnbits(3);

		if (!idleFlag && (!paddingFlag || paddingBits != 0))
		{
			if (SL->packetSeqNumLength > 0)
				packetSequenceNumber = pBitStream->getnbits(SL->packetSeqNumLength);

			if (SL->degradationPriorityLength > 0)
				DegPrioflag = pBitStream->getbit();

			if (DegPrioflag)
				degradationPriority = pBitStream->getnbits(SL->degradationPriorityLength);

			if (OCRflag)
				objectClockReference = pBitStream->getnbits(SL->OCRLength);

			if (accessUnitStartFlag)
			{
#if 0	// TODO, have this
				if (SL->useRandomAccessPointFlag)
					bit(1) randomAccessPointFlag;

				if (SL->AU_seqNumLength >0)
					bit(SL.AU_seqNumLength) AU_sequenceNumber;

				if (SL->useTimeStampsFlag)
				{
					bit(1) decodingTimeStampFlag;
					bit(1) compositionTimeStampFlag;
				}

				if (SL->instantBitrateLength>0)
					bit(1) instantBitrateFlag;

				if (decodingTimeStampFlag)
					bit(SL->timeStampLength) decodingTimeStamp;

				if (compositionTimeStampFlag)
					bit(SL->timeStampLength) compositionTimeStamp;
				
				if (SL->AU_Length > 0)
					bit(SL->AU_Length) accessUnitLength;

				if (instantBitrateFlag)
					bit(SL->instantBitrateLength) instantBitrate;
#endif
			}
		}
	}
};

/*
ObjectTypeIndication

0x00 Forbidden
0x01 Systems ISO/IEC 14496-1 a
0x02 Systems ISO/IEC 14496-1 b
0x03-0x1F reserved for ISO use
0x20 Visual ISO/IEC 14496-2 c
0x21-0x3F reserved for ISO use
0x40 Audio ISO/IEC 14496-3 d
0x41-0x5F reserved for ISO use
0x60 Visual ISO/IEC 13818-2 Simple Profile
0x61 Visual ISO/IEC 13818-2 Main Profile
0x62 Visual ISO/IEC 13818-2 SNR Profile
0x63 Visual ISO/IEC 13818-2 Spatial Profile
0x64 Visual ISO/IEC 13818-2 High Profile
0x65 Visual ISO/IEC 13818-2 422 Profile
0x66 Audio ISO/IEC 13818-7 Main Profile
0x67 Audio ISO/IEC 13818-7 LowComplexity Profile
0x68 Audio ISO/IEC 13818-7 Scaleable Sampling Rate Profile
0x69 Audio ISO/IEC 13818-3
0x6A Visual ISO/IEC 11172-2
0x6B Audio ISO/IEC 11172-3
0x6C Visual ISO/IEC 10918-1
0x6D - 0xBF reserved for ISO use
0xC0 - 0xFE user private
0xFF no object type specified
*/

/*
StreamType

0x00 Forbidden
0x01 ObjectDescriptorStream (see 8.5)
0x02 ClockReferenceStream (see 10.2.5)
0x03 SceneDescriptionStream (see 9.2.1)
0x04 VisualStream
0x05 AudioStream
0x06 MPEG7Stream
0x07 IPMPStream (see 8.3.2)
0x08 ObjectContentInfoStream (see 8.4.2)
0x09 MPEGJStream
0x0A - 0x1F reserved for ISO use
0x20 - 0x3F user private
*/

////////////////////////////////////////////////////////////////////////
// CDecoderConfigDescriptor

DecoderConfigDescriptor::DecoderConfigDescriptor()
{
	m_pDecoderSpecificInfo = NULL;
}

DecoderConfigDescriptor::~DecoderConfigDescriptor()
{
	if (m_pDecoderSpecificInfo)
	{
		delete m_pDecoderSpecificInfo;
		m_pDecoderSpecificInfo = NULL;
	}
}

void DecoderConfigDescriptor::Read(Stream& stream, BaseDescriptor* pDescriptor, Track* pTrack, SampleDescription* pSD)
{
	/*
	System::IO::CBitStream bitstream(stream);
	System::IO::CBitStream32* pBitStream = &bitstream;
	*/

	m_objectTypeIndication = ReadByte(stream);
	m_streamType = ReadByte(stream);
	m_upStream = (m_streamType>>1) & 1;//pBitStream->getbit();
	int reserved = m_streamType & 1;//pBitStream->getbit();	//const bit(1) reserved=1;
	ASSERT(reserved == 1);
	m_streamType >>= 2;

	m_bufferSizeDB = ReadByte(stream)<<16;
	m_bufferSizeDB |= ReadByte(stream)<<8;
	m_bufferSizeDB |= ReadByte(stream);

	m_maxBitrate = ReadByte(stream)<<24;
	m_maxBitrate |= ReadByte(stream)<<16;
	m_maxBitrate |= ReadByte(stream)<<8;
	m_maxBitrate |= ReadByte(stream);

	m_avgBitrate = ReadByte(stream)<<24;
	m_avgBitrate |= ReadByte(stream)<<16;
	m_avgBitrate |= ReadByte(stream)<<8;
	m_avgBitrate |= ReadByte(stream);

	TRACE("streamType: %d\n", m_streamType);

	if (m_streamType == 0x03)	// SceneDescriptionStream
	{
		BaseDescriptor descriptor;
		descriptor.Descend(stream);
		if (descriptor.m_tag == 0x5) // DecSpecificInfoTag
		{
			BIFSDec* pBIFSDecoder = new BIFSDec;
			if (pBIFSDecoder)
			{
				pBIFSDecoder->m_pTrack = pTrack;
				ASSERT(0);
				//pBIFSDecoder->m_stream = stream.Clone();

				pTrack->m_pBIFSDecoder = pBIFSDecoder;

#if 0
				pSD->m_decoder = pBIFSDecoder;	// This AddRefs
#endif
			//	pTrack->m_pMovie->m_pFilterGraph->AddFilter(pSD->m_decoder);

#if 0	// Had this
				pTrack->m_pMovie->AddPin(pTrack);	// ??
#endif
#if 0
				// TODO, don't have this here
				{
					CComPtr<ILBaseFilter> sceneRenderer;
					sceneRenderer.CoCreateInstance(L"LX3D.OGLSceneRenderer");
					if (sceneRenderer)
					{
						pTrack->m_pMovie->m_pFilterGraph->AddFilter(sceneRenderer);

					// Connect the bifs decoders output pin to the scene renderers input pin
						CComPtr<ILPin> pin;
						sceneRenderer->GetPin(0, &pin);
						pBIFSDecoder->m_pOutputPin->Connect(pin, NULL);
					}
				}
#endif

			//	pBIFSDecoder->m_config = new CBIFSConfiguration;

				if (m_objectTypeIndication == 0x1)
				{
					BIFSConfig* pBIFSConfig = new BIFSConfig;
					pBIFSConfig->Read(stream, pBIFSDecoder->m_pBIFSConfig);
#if 0
					m_pDecoderSpecificInfo = pBIFSConfig;
#endif
				}
				else if (m_objectTypeIndication == 0x2)
				{
					BIFSv2Config* pBIFSConfig = new BIFSv2Config;
					pBIFSConfig->Read(stream, pBIFSDecoder->m_pBIFSConfig);
	#if 0

					m_pDecoderSpecificInfo = pBIFSConfig;
	#endif
				}
				else
					ASSERT(0);
			}
		}
		else
			ASSERT(0);

		descriptor.Ascend(stream);
	}
	else if (m_streamType == 0x01)	// ObjectDescriptionStream
	{
		// No decoder specific info

		MessageBeep(-1);	// TODO
#if 0

		CODDecoder* pODDecoder = new CODDecoder;
	//	CComObject<CODDecoder>::CreateInstance(&pODDecoder);
		if (pODDecoder)
		{
			pODDecoder->m_pTrack = pTrack;
			pODDecoder->m_stream = stream->Clone();

#if 0
			pSD->m_decoder = pODDecoder;	// This AddRefs
#endif
		}
#endif

#if 0
		if (pDescriptor->More(pBitStream))
		{
			MessageBeep(-1);
		}
#endif
	}
	else if (m_streamType == 0x4)	// Visual
	{
		if (m_objectTypeIndication == 0x6c)	// JPEG
		{
		/*
			CBaseDescriptor descriptor;
			descriptor.Descend(pBitStream);
			if (descriptor.m_tag == 0x5) // DecSpecificInfoTag
			{
				CJPEGDecoderConfig jpegDecoderConfig;
				jpegDecoderConfig.Read(stream);
			}
			descriptor.Ascend(pBitStream);
			*/
			MessageBeep(-1);
		}
		else if (m_objectTypeIndication == 0x20)	// MPEG4 Video
		{
			VideoDec* pMP4VideoDecoder = new VideoDec;
			if (pMP4VideoDecoder)
			{
#if 0
				pMP4VideoDecoder->m_pSampleDescription = (MP4VSampleDescription*)pSD;
#endif

				pTrack->m_decoder = pMP4VideoDecoder;	// ??
			//	pMP4VideoDecoder->m_pTrack = pTrack;
				ASSERT(0);
				//pMP4VideoDecoder->m_stream = stream.Clone();

#if 0
				pSD->m_decoder = pMP4VideoDecoder;	// This AddRefs
#endif
			//	pTrack->m_pMovie->m_pFilterGraph->AddFilter(pSD->m_decoder);

				BaseDescriptor descriptor;
				descriptor.Descend(stream);
				if (descriptor.m_tag == 0x5) // DecSpecificInfoTag
				{
					pMP4VideoDecoder->m_config = new MP4VConfig;

					uint8* data = new uint8[descriptor.m_sizeOfInstance];
					stream.Read(data, descriptor.m_sizeOfInstance);

					IO::CBitStream32* pBitStream = new IO::CBitStream32(new IO::CByteStream(Stream(new IO::MemoryStream(data, descriptor.m_sizeOfInstance))));

					int start_code = next_start_code(pBitStream);
					if (start_code >= 0x100 && start_code <= 0x11F)
					{
						start_code = next_start_code(pBitStream);
						if (start_code >= 0x120 && start_code <= 0x12F)
						{
							pMP4VideoDecoder->m_config->VideoObjectLayer(pBitStream, start_code);
						}
						else
							ASSERT(0);
					}
					else if (start_code == 0x1B0)
					{
						pMP4VideoDecoder->VisualObjectSequence(pBitStream, start_code);
					}

					delete[] data;
					// TODO, don't have this ???

#if 0
					ASSERT(0);
#if 0
					pTrack->m_pMovie->m_pFilterGraph->AddFilter(pMP4VideoDecoder);
					ErrorCode hr = pTrack->Connect(pMP4VideoDecoder->m_pInputPin, MediaType());
					ASSERT(SUCCEEDED(hr));
#endif
					ASSERT(0);
#if 0
					pTrack->m_pMovie->AddPin(pTrack);	// ??
#endif
#endif
				}
				descriptor.Ascend(stream);
			}
		}
		else
		{
			MessageBeep(-1);
		}
	}

#if 0
	DecoderSpecificInfo decSpecificInfo[0 .. 1];
	profileLevelIndicationIndexDescriptor profileLevelIndicationIndexDescr [0..255];
#endif
}

///////////////////////////////////////////////////////////////////////
// CESDescriptor

void ESDescriptor::Read(Stream& stream, BaseDescriptor* pDescriptor, Track* pTrack, SampleDescription* pSD)
{
//	System::IO::CBitStream bitstream(stream);
//	System::IO::CBitStream32* pBitStream = &bitstream;

	m_ES_ID = ReadByte(stream)<<8;
	m_ES_ID |= ReadByte(stream);

	uint8 flags = ReadByte(stream);

	int streamDependenceFlag = flags & 1;
	m_URL_Flag = (flags>>1) & 1;
	m_OCRstreamFlag = (flags>>2) & 1;
	m_streamPriority = (flags>>3);
	if (streamDependenceFlag)
	{
		m_dependsOn_ES_ID = ReadByte(stream)<<8;
		m_dependsOn_ES_ID |= ReadByte(stream);

		if (m_dependsOn_ES_ID == 0)
		{
			ASSERT(0);
			throw L"dependsOn_ES_ID is 0";
		}
	}
	else
	{
		m_dependsOn_ES_ID = 0;
	}

	//ASSERT(pBitStream->is_byte_aligned());

	if (m_URL_Flag)
	{
		ULONG nRead;

		uint8 URLlength = ReadByte(stream);

		m_URLstring = new uint8[URLlength+1];
		nRead = stream.Read(m_URLstring, URLlength);

		m_URLstring[URLlength] = 0;
	}

	if (m_OCRstreamFlag)
	{
		m_OCR_ES_Id = ReadByte(stream)<<8;
		m_OCR_ES_Id |= ReadByte(stream);
	}

/*
	DecoderConfigDescriptor decConfigDescr;
	SLConfigDescriptor slConfigDescr;
	IPI_DescrPointer ipiPtr[0 .. 1];
	IP_IdentificationDataSet ipIDS[0 .. 255];
	IPMP_DescriptorPointer ipmpDescrPtr[0 .. 255];
	LanguageDescriptor langDescr[0 .. 255];
	QoS_Descriptor qosDescr[0 .. 1];
	RegistrationDescriptor regDescr[0 .. 1];
	ExtensionDescriptor extDescr[0 .. 255];
*/

	BaseDescriptor descriptor;

	ASSERT(pDescriptor->More(stream));
	descriptor.Descend(stream);
	if (descriptor.m_tag == 0x04)	// DecoderConfigDescrTag
	{
		m_decoderConfigDescriptor.Read(stream, &descriptor, pTrack, pSD);
	}
	else
	{
		ASSERT(0);
		throw L"Expected DecoderConfigDescrTag";
	}
	descriptor.Ascend(stream);

	ASSERT(pDescriptor->More(stream));
	descriptor.Descend(stream);
	if (descriptor.m_tag == 0x6)	// SLConfigDescrTag
	{
		m_SLConfigDescr.Read(stream);
	}
	else
	{
		ASSERT(0);
	//	throw L"Expected SLConfigDescrTag";
	}
	descriptor.Ascend(stream);

	while (pDescriptor->More(stream))
	{
		BaseDescriptor descriptor;

		descriptor.Descend(stream);

		TRACE("CESDescriptor: descrTag: %d, size: %d\n", descriptor.m_tag, descriptor.m_sizeOfInstance);

		descriptor.Ascend(stream);
	}
}

///////////

////////////////////////////////////////////////////////////////////////
// CTrack

Track::Track()
{
	m_pMovie = NULL;

	m_config = NULL;
	m_pSampleDescription = NULL;
	m_decoder = NULL;
	m_pBIFSDecoder = NULL;
	m_sampleflags = NULL;
}

ErrorCode Track::ReadTrackReference(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize)
{
	while (1)
	{
		{
			LONGLONG pos = stream.Seek(0, System::IO::STREAM_SEEK_CUR);

			if (pos >= (atomStartPos + atomSize))
			{
				ASSERT(pos == (atomStartPos + atomSize));
				return Success_False;
			}
		}

		Atom ck;
		if (ck.Descend(stream) == Success_False)
			return Success_False;

		TRACE("\t\ttatomType: %4.4s, size: %d\n", &ck.m_atomtype, (uint32)ck.m_size);

		{
			ULONG nRead;

			LONGLONG curpos = stream.Seek(0, IO::STREAM_SEEK_CUR);

			uint nids = (uint32)ck.m_contentsize/4;

			for (uint i = 0; i < nids; i++)
			{
				uint32 reftrackID;
				nRead = stream.Read(&reftrackID, 4);
				reftrackID = BigEndian32(reftrackID);

				if (ck.m_atomtype == ID_mpod)
				{
					m_mpod.Add(reftrackID);
				}
			}
		}

#if 0
		switch (ck.m_atomtype)
		{
			/* // Sub-track ??
		case ID_trak:
			{
				// Read children atoms
				ReadAtom(stream, ck.pos, ck.ulsize);
			}
			break;
			*/

		case ID_tkhd:
			{
				m_header.Read(stream);
			}
			break;

		case ID_tref:
			{
				ReadTrackReference(stream, ck.m_pos, ck.m_ulsize);
				//m_header.Read(stream);
			}
			break;

		case ID_mdia:
			{
				ReadTrackMedia(stream, ck.m_pos, ck.m_ulsize);
			}
			break;
		}
#endif

		ck.Ascend(stream);
	}

	return Success;
}

ErrorCode Track::Read(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize)
{
	while (1)
	{
		{
			LONGLONG pos = stream.Seek(0, IO::STREAM_SEEK_CUR);

			if (pos >= (atomStartPos + atomSize))
			{
				ASSERT(pos == (atomStartPos + atomSize));
				return Success_False;
			}
		}

		Atom ck;
		if (ck.Descend(stream) == Success_False)
			return Success_False;

		TRACE("\tatomType: %4.4s, size: %d\n", &ck.m_atomtype, (uint32)ck.m_size);

		switch (ck.m_atomtype)
		{
			/* // Sub-track ??
		case ID_trak:
			{
				// Read children atoms
				ReadAtom(stream, ck.pos, ck.ulsize);
			}
			break;
			*/

		case ID_tkhd:
			{
				m_trackHeader.Read(stream);
			}
			break;

		case ID_tref:
			{
				ReadTrackReference(stream, ck.m_pos, ck.m_size);
				//m_header.Read(stream);
			}
			break;

		case ID_mdia:
			{
				ReadTrackMedia(stream, ck.m_pos, ck.m_size);
			}
			break;
		}

		ck.Ascend(stream);
	}

	return Success;
}

TrackHeader::TrackHeader()
{
	m_trackID = 0;
	m_duration = 0;
}

ErrorCode TrackHeader::Read(Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags >> 24);
	uint32 flags = verflags & 0xffffff;

	/* Flags (Quicktime only?)

	Track enabled 
	Indicates that the track is enabled. Flag value is 0x0001.

	Track in movie
	Indicates that the track is used in the movie. Flag value is 0x0002.

	Track in preview
	Indicates that the track is used in the movie’s preview. Flag value is 0x0004.

	Track in poster
	Indicates that the track is used in the movie’s poster. Flag value is 0x0008.
	*/

	if (version == 1)
	{
		LONGLONG creationTime;
		nRead = stream.Read(&creationTime, 8);

		LONGLONG modificationTime;
		nRead = stream.Read(&modificationTime, 8);

		nRead = stream.Read(&m_trackID, 4);

		uint32 reserved;
		nRead = stream.Read(&reserved, 4);

		nRead = stream.Read(&m_duration, 8);
		m_duration = BigEndian32(m_duration);
	}
	else if (version == 0)
	{
		uint32 creationTime;
		nRead = stream.Read(&creationTime, 4);

		uint32 modificationTime;
		nRead = stream.Read(&modificationTime, 4);

		nRead = stream.Read(&m_trackID, 4);

		uint32 reserved;
		nRead = stream.Read(&reserved, 4);

		uint32 duration;
		nRead = stream.Read(&duration, 4);
		m_duration = BigEndian32(duration);
	}
	else
	{
		ASSERT(0);
		throw L"Unsupported version in atom";
	}

	m_trackID = BigEndian32(m_trackID);

	TRACE("trackID: %d\n", m_trackID);

	uint32 reserved0[3];
	nRead = stream.Read(reserved0, 4*2);
	ASSERT(reserved0[0] == 0);
	ASSERT(reserved0[1] == 0);

	uint16 layer;	// Quicktime only
	nRead = stream.Read(&layer, 2);
	layer = BigEndian16(layer);

	uint16 alternateGroup;	// Quicktime only
	nRead = stream.Read(&alternateGroup, 2);
	alternateGroup = BigEndian16(alternateGroup);

	uint16 volume;	// Quicktime only
	nRead = stream.Read(&volume, 2);
	volume = BigEndian16(volume);

	uint16 reserved1;
	nRead = stream.Read(&reserved1, 2);
	ASSERT(reserved1 == 0);

	// Matrix (Quicktime only)
	uint32 reserved2[9];
	nRead = stream.Read(reserved2, 4*9);
	reserved2[0] = BigEndian32(reserved2[0]);
	reserved2[4] = BigEndian32(reserved2[4]);
	reserved2[8] = BigEndian32(reserved2[8]);

	VERIFY(reserved2[0] == 0x00010000);
	VERIFY(reserved2[1] == 0x0);
	VERIFY(reserved2[2] == 0x0);
	VERIFY(reserved2[3] == 0x0);
	VERIFY(reserved2[4] == 0x00010000);
	VERIFY(reserved2[5] == 0x0);
	VERIFY(reserved2[6] == 0x0);
	VERIFY(reserved2[7] == 0x0);
	VERIFY(reserved2[8] == 0x40000000);

	uint32 trackWidth;	// Quicktime only
	nRead = stream.Read(&trackWidth, 4);
	trackWidth = BigEndian32(trackWidth);

	uint32 trackHeight;	// Quicktime only
	nRead = stream.Read(&trackHeight, 4);
	trackHeight = BigEndian32(trackHeight);

#if 0
	const bit(16)reserved = { if track_is_audio 0x0100 else 0};
	const unsigned int(16) reserved = 0;
	const bit(32)[9] reserved =
	{ 0x00010000, 0, 0, 0, 0x00010000, 0, 0, 0, 0x40000000 };
	const bit(32)reserved = {
	if track_is_visual 0x01400000 else 0 };
	const bit(32)reserved = {
	if track_is_visual 0x00F00000 else 0};
#endif

	return Success;
};

MediaHeader::MediaHeader()
{
	m_timeScale = 0;
	m_duration = 0;
}

ErrorCode MediaHeader::Read(Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags>>24);

	if (version == 1)
	{
		ULONGLONG creationTime;
		nRead = stream.Read(&creationTime, 8);

		ULONGLONG modificationTime;
		nRead = stream.Read(&modificationTime, 8);

		nRead = stream.Read(&m_timeScale, 4);
		m_timeScale = BigEndian32(m_timeScale);

		nRead = stream.Read(&m_duration, 8);
		m_duration = BigEndian32(m_duration);
	}
	else if (version == 0)
	{
		uint32 creationTime;
		nRead = stream.Read(&creationTime, 4);

		uint32 modificationTime;
		nRead = stream.Read(&modificationTime, 4);

		nRead = stream.Read(&m_timeScale, 4);
		m_timeScale = BigEndian32(m_timeScale);

		uint32 duration;
		nRead = stream.Read(&duration, 4);
		m_duration = BigEndian32(duration);
	}
	else
		ASSERT(0);

	if (m_timeScale == 0)
	{
		TRACE("Invalid TimeScale value (0)");
		return Error;
	}

	/*
	bit(1) pad = 0;
	unsigned int(5)[3] language; // packed ISO-639-2/T language code
	const unsigned int(16) reserved = 0;
	*/

	return Success;
}

ErrorCode Track::ReadTrackMedia(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize)
{
	while (1)
	{
		{
			LONGLONG pos = stream.Seek(0, System::IO::STREAM_SEEK_CUR);

			if (pos >= (atomStartPos + atomSize))
			{
				ASSERT(pos == (atomStartPos + atomSize));
				return Success_False;
			}
		}

		Atom ck;
		if (ck.Descend(stream) == Success_False)
			return Success_False;

		TRACE("atomType: %4.4s, size: %d\n", &ck.m_atomtype, (uint32)ck.m_size);

		switch (ck.m_atomtype)
		{
		case ID_mdhd:
			{
				m_mediaHeader.Read(stream);
			}
			break;

		case ID_hdlr:
			{
				ReadHandler(stream);
			}
			break;

		case ID_minf:
			{
				ReadMediaInformation(stream, ck.m_pos, ck.m_size);
			}
			break;
		}

		ck.Ascend(stream);
	}
}

/*
handler-type - is an integer containing one of the following values:
‘odsm’ ObjectDescriptorStream
‘crsm’ ClockReferenceStream
‘sdsm’ SceneDescriptionStream
‘vide’ VisualStream
‘soun’ AudioStream
‘m7sm’ MPEG7Stream
‘ocsm’ ObjectContentInfoStream
‘ipsm’ IPMP Stream
‘mjsm’ MPEG-J Stream
‘hint’ Hint track

*/

ErrorCode Track::ReadHandler(Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags>>24);

//const unsigned int(32) reserved = 0;
//unsigned int(32) handler-type;
//const unsigned int(8)[12] reserved = 0;
//string name;

	/*
Component type 
A four-character code that identifies the type of the handler.
Only two values are valid for this field:
'mhlr' for media handlers and 'dhlr' for data handlers. 
*/
	uint32 componentType;
	nRead = stream.Read(&componentType, 4);

	nRead = stream.Read(&m_handlerType, 4);

	TRACE("\thandlerType: %4.4s\n", &m_handlerType);

	return Success;
}

ErrorCode Track::ReadMediaInformation(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize)
{
	while (1)
	{
		{
			LONGLONG pos = stream.Seek(0, System::IO::STREAM_SEEK_CUR);

			if (pos >= (atomStartPos + atomSize))
			{
				ASSERT(pos == (atomStartPos + atomSize));
				return Success_False;
			}
		}

		Atom ck;
		if (ck.Descend(stream) == Success_False)
			return Success_False;

		TRACE("atomType: %4.4s, size: %d\n", &ck.m_atomtype, (uint32)ck.m_size);

		switch (ck.m_atomtype)
		{
		case ID_dinf:
			{
				// Read children atoms
				//ReadAtom(stream, ck.pos, ck.ulsize);
				// TODO
			}
			break;

		case ID_stbl:
			{
				// Read children atoms
				ReadSampleTable(stream, ck.m_pos, ck.m_size);
			}
			break;
		}

		ck.Ascend(stream);
	}
}

void Track::ReadSampleDescription(Atom& ck, Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags >> 24);

	uint32 numberOfEntries;
	nRead = stream.Read(&numberOfEntries, 4);
	numberOfEntries = BigEndian32(numberOfEntries);

	for (uint i = 0; i < numberOfEntries; ++i)
	{
		SampleDescription* pSampleDescription = NULL;

		Atom subck;
		subck.Descend(stream);
		TRACE("\tatomType: %4.4s, size: %d\n", &subck.m_atomtype, (uint32)subck.m_size);

		SampleEntry sampleEntry;
		sampleEntry.Read(stream);

		switch (m_handlerType)
		{
		case ID_vide:
			{
				if (subck.m_atomtype == ID_mp4v)
				{
					MP4VSampleDescription* pSD = new MP4VSampleDescription;
					pSampleDescription = pSD;

					uint32 reserved0[4];
					nRead = stream.Read(reserved0, 4*4);

					uint32 reserved1[4];
					nRead = stream.Read(reserved1, 4*4);
					reserved1[0] = BigEndian32(reserved1[0]);
					reserved1[1] = BigEndian32(reserved1[1]);
					reserved1[2] = BigEndian32(reserved1[2]);
					reserved1[3] = BigEndian32(reserved1[3]);
#if 0	// TODO, what are these??
					if (reserved1[0] != 0x014000F0) throw L"Unexpected reserved value";
					if (reserved1[1] != 0x00480000) throw L"Unexpected reserved value";
					if (reserved1[2] != 0x00480000) throw L"Unexpected reserved value";
					if (reserved1[3] != 0x00000000) throw L"Unexpected reserved value";
#endif

					//const unsigned int(16) reserved = 1;
					uint16 frameCountPerSample;	// A 16-bit integer that indicates how many frames of compressed data are stored in each sample. Usually set to 1. 
					nRead = stream.Read(&frameCountPerSample, 2);
					frameCountPerSample = BigEndian16(frameCountPerSample);
					if (frameCountPerSample != 1)
					{
						raise(Exception(L"frameCountPerSample != 1 not supported"));
					}

				//	const unsigned int(8)[32] reserved = 0;
					uint8 reserved2[32];
					nRead = stream.Read(reserved2, 32);

					uint16 depth;
					nRead = stream.Read(&depth, 2);
					depth = BigEndian16(depth);
					if (depth != 24)
					{
						raise(Exception(L"depth != 24 not supported"));
					}

					//const int(16)reserved = -1;
					short reserved3;
					nRead = stream.Read(&reserved3, 2);
					reserved3 = BigEndian16(reserved3);
					if (reserved3 != -1)
					{
						raise(Exception(L"Unexpected reserved value"));
					}

					//	ESDAtom ES;
					Atom esdatom;
					esdatom.Descend(stream);
					ASSERT(esdatom.m_atomtype == ID_esds);
					if (esdatom.m_atomtype == ID_esds)
					{
						uint32 verflags;
						nRead = stream.Read(&verflags, 4);
						verflags = BigEndian32(verflags);

						// ESDescriptor
					//	System::IO::CBitStream bitstream(stream);
						BaseDescriptor descriptor;
						descriptor.Descend(stream);
						if (descriptor.m_tag == 0x03)// ES_DescrTag
						{
							pSD->es_descriptor.Read(stream, &descriptor, this, pSD);

							m_streamType = pSD->es_descriptor.m_decoderConfigDescriptor.m_streamType;

						//	if (m_streamType == 0x3)
							{
							}
						}
						else
							ASSERT(0);
						descriptor.Ascend(stream);
					}
					else
					{
						ASSERT(0);
					}

					esdatom.Ascend(stream);
				}
				else
					ASSERT(0);
			}
			break;

		case ID_soun:
			{
				if (subck.m_atomtype == ID_mp4a)
				{
					MP4ASampleDescription* pSD = new MP4ASampleDescription;

					pSampleDescription = pSD;

					uint16 version;
					nRead = stream.Read(&version, 2);

					uint16 revision;
					nRead = stream.Read(&revision, 2);

					uint16 vendor;
					nRead = stream.Read(&vendor, 4);

					uint16 channels;
					nRead = stream.Read(&channels, 2);
					channels = BigEndian16(channels);
					ASSERT(channels == 2);

					uint16 sampleSize;
					nRead = stream.Read(&sampleSize, 2);
					sampleSize = BigEndian16(sampleSize);
					ASSERT(sampleSize == 16);

					uint16 compressionID;
					nRead = stream.Read(&compressionID, 2);
					ASSERT(compressionID == 0);

					uint16 packetSize;
					nRead = stream.Read(&packetSize, 2);
					ASSERT(packetSize == 0);

					uint16 timeScale;	// copied from track
					nRead = stream.Read(&timeScale, 2);
					timeScale = BigEndian16(timeScale);

					uint16 timeScaleFract;
					nRead = stream.Read(&timeScaleFract, 2);
					timeScaleFract = BigEndian16(timeScaleFract);
					ASSERT(timeScaleFract == 0);

					Atom esdatom;
					esdatom.Descend(stream);
					ASSERT(esdatom.m_atomtype == ID_esds);
					if (esdatom.m_atomtype == ID_esds)
					{
						uint32 verflags;
						nRead = stream.Read(&verflags, 4);
						verflags = BigEndian32(verflags);

						// ESDescriptor
					//	System::IO::CBitStream bitstream(stream);
						BaseDescriptor descriptor;
						descriptor.Descend(stream);
						if (descriptor.m_tag == 0x03)// ES_DescrTag
						{
							pSD->es_descriptor.Read(stream, &descriptor, this, pSD);

							m_streamType = pSD->es_descriptor.m_decoderConfigDescriptor.m_streamType;
						}
						descriptor.Ascend(stream);
					}
					else
					{
						ASSERT(0);
					}

					esdatom.Ascend(stream);
				}
				else
					ASSERT(0);
			}
			break;

		case ID_hint:
			{
				MessageBeep(-1);
				// TODO
			}
			break;

		case ID_odsm:
			{
				if (subck.m_atomtype == ID_mp4s)
				{
					MP4SSampleDescription* pSD = new MP4SSampleDescription;

					pSampleDescription = pSD;

					Atom esdatom;
					esdatom.Descend(stream);
					ASSERT(esdatom.m_atomtype == ID_esds);
					if (esdatom.m_atomtype == ID_esds)
					{
						uint32 verflags;
						nRead = stream.Read(&verflags, 4);
						verflags = BigEndian32(verflags);

						// ESDescriptor
					//	System::IO::CBitStream bitstream(stream);
						BaseDescriptor descriptor;
						descriptor.Descend(stream);
						if (descriptor.m_tag == 0x03)// ES_DescrTag
						{
							pSD->es_descriptor.Read(stream, &descriptor, this, pSD);

							m_streamType = pSD->es_descriptor.m_decoderConfigDescriptor.m_streamType;

							if (m_streamType == 0x3)
							{
								ASSERT(0);
#if 0
								CBIFSDecoder* pBIFSDecoder = new CBIFSDecoder;

#if 0
								if (pSD->es_descriptor.m_decoderConfigDescriptor.m_objectTypeIndication == 0x1)
								{
									CBIFSConfig* pBIFSConfig = (CBIFSConfig*)pSD->es_descriptor.m_decoderConfigDescriptor.m_pDecoderSpecificInfo;

									pBIFSDecoder->m_pBIFSConfig->use3DmeshCoding = FALSE;
									pBIFSDecoder->m_pBIFSConfig->nodeIDbits = pBIFSConfig->m_nodeIDbits;
									pBIFSDecoder->m_pBIFSConfig->routeIDbits = pBIFSConfig->m_routeIDbits;
								}
								else if (pSD->es_descriptor.m_decoderConfigDescriptor.m_objectTypeIndication == 0x2)
								{
									CBIFSv2Config* pBIFSConfig = (CBIFSv2Config*)pSD->es_descriptor.m_decoderConfigDescriptor.m_pDecoderSpecificInfo;

									pBIFSDecoder->m_pBIFSConfig->use3DmeshCoding = pBIFSConfig->m_use3DmeshCoding;
									pBIFSDecoder->m_pBIFSConfig->nodeIDbits = pBIFSConfig->m_nodeIDbits;
									pBIFSDecoder->m_pBIFSConfig->routeIDbits = pBIFSConfig->m_routeIDbits;
								}
								else
									ASSERT(0);
#endif

								pBIFSDecoder->m_pTrack = this;
								pBIFSDecoder->m_stream = dynamic_cast<ISequentialByteStream*>(stream->Clone());

#if 0
								m_decoder = pBIFSDecoder;	// This AddRefs
#endif
#endif
							}
						}
						descriptor.Ascend(stream);
					}
					else
					{
						ASSERT(0);
					}

					esdatom.Ascend(stream);
				}
				else
					ASSERT(0);
			}
			break;

		default:
			{
				if (subck.m_atomtype == ID_mp4s)
				{
					MP4SSampleDescription* pSD = new MP4SSampleDescription;

					pSampleDescription = pSD;

					Atom esdatom;
					esdatom.Descend(stream);
					ASSERT(esdatom.m_atomtype == ID_esds);
					if (esdatom.m_atomtype == ID_esds)
					{
						uint32 verflags;
						nRead = stream.Read(&verflags, 4);
						verflags = BigEndian32(verflags);

						// ESDescriptor
					//	System::IO::CBitStream bitstream(stream);
						BaseDescriptor descriptor;
						descriptor.Descend(stream);
						if (descriptor.m_tag == 0x03)// ES_DescrTag
						{
							pSD->es_descriptor.Read(stream, &descriptor, this, pSD);

							m_streamType = pSD->es_descriptor.m_decoderConfigDescriptor.m_streamType;

#if 0
							if (m_streamType == 0x3)
							{
								CComObject<CBIFSDecoder>* pBIFSDecoder;
								CComObject<CBIFSDecoder>::CreateInstance(&pBIFSDecoder);
								//pTrack->m_pBIFSDecoder->AddRef();

#if 0
								if (pSD->es_descriptor.m_decoderConfigDescriptor.m_objectTypeIndication == 0x1)
								{
									CBIFSConfig* pBIFSConfig = (CBIFSConfig*)pSD->es_descriptor.m_decoderConfigDescriptor.m_pDecoderSpecificInfo;

									pBIFSDecoder->m_pBIFSConfig->use3DmeshCoding = FALSE;
									pBIFSDecoder->m_pBIFSConfig->nodeIDbits = pBIFSConfig->m_nodeIDbits;
									pBIFSDecoder->m_pBIFSConfig->routeIDbits = pBIFSConfig->m_routeIDbits;
								}
								else if (pSD->es_descriptor.m_decoderConfigDescriptor.m_objectTypeIndication == 0x2)
								{
									CBIFSv2Config* pBIFSConfig = (CBIFSv2Config*)pSD->es_descriptor.m_decoderConfigDescriptor.m_pDecoderSpecificInfo;

									pBIFSDecoder->m_pBIFSConfig->use3DmeshCoding = pBIFSConfig->m_use3DmeshCoding;
									pBIFSDecoder->m_pBIFSConfig->nodeIDbits = pBIFSConfig->m_nodeIDbits;
									pBIFSDecoder->m_pBIFSConfig->routeIDbits = pBIFSConfig->m_routeIDbits;
								}
								else
									ASSERT(0);
#endif

								pBIFSDecoder->m_pTrack = this;
								stream;

#if 0
								m_decoder = pBIFSDecoder;	// This AddRefs
#endif
							}
#endif
						}
						else
							ASSERT(0);

						descriptor.Ascend(stream);
					}
					else
						ASSERT(0);

					esdatom.Ascend(stream);
				}
				else
					ASSERT(0);
			}
			break;
		}

		subck.Ascend(stream);

		if (pSampleDescription)
		{
			pSampleDescription->data_reference_index = sampleEntry.data_reference_index;
			m_sampleDescriptions.Add(pSampleDescription);
		}
	}
}

ErrorCode Track::ReadSampleTable(Stream& stream, LONGLONG atomStartPos, LONGLONG atomSize)
{
	AtomCollection atoms;

	HRESULT_throw hr(Success);

	while (1)
	{
		{
			LONGLONG pos = stream.Seek(0, IO::STREAM_SEEK_CUR);

			if (pos >= (atomStartPos + atomSize))
			{
				ASSERT(pos == (atomStartPos + atomSize));
				break;//return S_FALSE;
			}
		}

		Atom atom;
		if (atom.Descend(stream) == Success_False)
			return Success_False;

		TRACE("atomType: %4.4s, size: %d\n", &atom.m_atomtype, (uint32)atom.m_size);

		atoms.Add(atom);

		atom.Ascend(stream);
	}

	Atom* pAtom;

	pAtom = atoms.GetAtom(ID_stsd);
	if (pAtom == NULL)
	{
		return Error;
	}
	hr = pAtom->Seek(stream);
	ReadSampleDescription(*pAtom, stream);

	pAtom = atoms.GetAtom(ID_stco);
	if (pAtom == NULL)
	{
		return Error;
	}
	hr = pAtom->Seek(stream);
	ReadChunkOffset(stream);	// This builds the chunks list

	pAtom = atoms.GetAtom(ID_stsz);
	if (pAtom == NULL)
	{
		return Error;
	}
	hr = pAtom->Seek(stream);
	ReadSampleSize(stream);	// This builds the samples list

	pAtom = atoms.GetAtom(ID_stsc);
	if (pAtom == NULL)
	{
		return Error;
	}
	hr = pAtom->Seek(stream);
	ReadSampleToChunk(*pAtom, stream);	// This associates samples to chunks and sample descriptions

	pAtom = atoms.GetAtom(ID_stts);
	if (pAtom == NULL)
	{
		return Error;
	}
	hr = pAtom->Seek(stream);
	ReadTimeToSample(*pAtom, stream);

	pAtom = atoms.GetAtom(ID_stss);
	if (pAtom == NULL)
	{
		return Error;
	}
	hr = pAtom->Seek(stream);
	ReadSyncSample(*pAtom, stream);

#if 0
	// TODO Remove
	if (m_streamType == 4)
	{
#if 0
		CComQIPtr<ILBaseFilter> decoder = m_sampleDescriptions[0]->m_decoder;

		if (decoder)
		{
			decoder->Run(0);
		}
#endif
	}
	else if (m_streamType == 1)
	{
		// Remember current position
		LONGLONG curpos;
		{
			LARGE_INTEGER li;
			li = 0;
			stream->Seek(li, System::IO::STREAM_SEEK_CUR, &curpos);
		}

		// Seek to position of sample data
		LARGE_INTEGER li;
		li = m_chunks[0].m_offset;
		stream->Seek(li, System::IO::STREAM_SEEK_SET, NULL);


		// Reset pos
		li = curpos;
		stream->Seek(li, System::IO::STREAM_SEEK_SET, NULL);
	}
#endif

	return Success;
	/*
		case ID_ctts:
			{
				ASSERT(0);
			}
			break;
	*/
}

void Track::ReadSampleToChunk(Atom& ck, Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags >> 24);

	if (version == 0)
	{
		uint32 entry_count;
		nRead = stream.Read(&entry_count, 4);
		entry_count = BigEndian32(entry_count);

		if (entry_count < 1)
		{
			throw L"Error in SampleToChunk atom";
		}

		SampleToChunk stcprev;
		ASSERT(sizeof(stcprev) == 12);
		nRead = stream.Read(&stcprev, sizeof(stcprev));
		stcprev.first_chunk = BigEndian32(stcprev.first_chunk);
		stcprev.samples_per_chunk = BigEndian32(stcprev.samples_per_chunk);
		stcprev.sample_description_index = BigEndian32(stcprev.sample_description_index);

		int nchunk = 0;
		int nsample = 0;

		for (uint i = 1; i < entry_count; i++)
		{
			SampleToChunk stc;
			ASSERT(sizeof(stc) == 12);
			nRead = stream.Read(&stc, sizeof(stc));
			stc.first_chunk = BigEndian32(stc.first_chunk);
			stc.samples_per_chunk = BigEndian32(stc.samples_per_chunk);
			stc.sample_description_index = BigEndian32(stc.sample_description_index);

			// Number of chunks with the above settings
			uint nchunks = stc.first_chunk - stcprev.first_chunk;

			for (int n = 0; n < nchunks; n++)
			{
				m_chunks[nchunk].m_sampleCount = stcprev.samples_per_chunk;

				ULONGLONG fileOffset = m_chunks[nchunk].m_offset;
				for (int k = 0; k < stcprev.samples_per_chunk; k++)
				{
					m_samples[nsample].m_fileOffset = fileOffset;
					fileOffset += m_samples[nsample].m_fileSize;

					nsample++;
				}

				nchunk++;
			}

			stcprev = stc;
		}

		// Settings of the remaining chunks
		uint nchunks = m_chunks.GetSize() - (stcprev.first_chunk-1);

		for (uint n = 0; n < nchunks; n++)
		{
			m_chunks[nchunk].m_sampleCount = stcprev.samples_per_chunk;

			ULONGLONG fileOffset = m_chunks[nchunk].m_offset;
			for (int k = 0; k < stcprev.samples_per_chunk; k++)
			{
				m_samples[nsample].m_fileOffset = fileOffset;
				fileOffset += m_samples[nsample].m_fileSize;

				nsample++;
			}

			nchunk++;
		}
	}
	else
	{
		throw L"Unknown version in SampleToChunk atom";
	}
}

void Track::ReadSyncSample(Atom& ck, Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags >> 24);

	m_sampleflags = new uint8[m_samples.GetSize()];
	std::memset(m_sampleflags, 0, sizeof(uint8)*m_samples.GetSize());

	if (version == 0)
	{
		uint32 entry_count;
		nRead = stream.Read(&entry_count, 4);
		entry_count = BigEndian32(entry_count);

		for (uint n = 0; n < entry_count; n++)
		{
			ULONG sample_number;
			nRead = stream.Read(&sample_number, 4);
			sample_number = BigEndian32(sample_number);
			sample_number -= 1;

			m_syncsamples.Add(sample_number);
			m_sampleflags[sample_number] = 1;
		}
	}
	else
	{
		raise(Exception(L"Unknown version in SyncSample atom"));
	}
}

void Track::ReadTimeToSample(Atom& ck, Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags >> 24);

	if (version == 0)
	{
		uint32 entry_count;
		nRead = stream.Read(&entry_count, 4);
		entry_count = BigEndian32(entry_count);

		uint nsample = 0;

		for (uint i = 0; i < entry_count; i++)
		{
			TimeToSample tts;
			ASSERT(sizeof(tts) == 8);
			nRead = stream.Read(&tts, sizeof(tts));
			tts.sample_count = BigEndian32(tts.sample_count);
			tts.sample_delta = BigEndian32(tts.sample_delta);

			if (nsample+tts.sample_count > m_samples.GetSize())
			{
				raise(Exception(L"Too many sample entries in TimeToSample atom"));
			}

			for (uint n = 0; n < tts.sample_count; n++)
			{
				m_samples[nsample++].m_duration = tts.sample_delta;
			}
		}
	}
	else
	{
		raise(Exception(L"Unknown version in TimeToSample atom"));
	}
}

void Track::ReadSampleSize(Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags >> 24);

	if (version == 0)
	{
		uint32 sample_size;
		nRead = stream.Read(&sample_size, 4);
		sample_size = BigEndian32(sample_size);

		uint32 sample_count;
		nRead = stream.Read(&sample_count, 4);
		sample_count = BigEndian32(sample_count);

		TRACE("sample_count: %d\n", sample_count);

		if (sample_size == 0)	// Each sample has a different size
		{
			for (uint i = 0; i < sample_count; i++)
			{
				uint32 entry_size;
				nRead = stream.Read(&entry_size, 4);
				entry_size = BigEndian32(entry_size);

				//unsigned int(32) entry-size;

				Sample sample;
				sample.m_fileSize = entry_size;

				m_samples.Add(sample);
			}
		}
		else	// All the samples have the same size
		{
			for (uint i = 0; i < sample_count; i++)
			{
				Sample sample;
				sample.m_fileSize = sample_size;

				m_samples.Add(sample);
			}
		}
	}
	else
	{
		throw L"Unknown version in SampleSize atom";
	}
}

void Track::ReadChunkOffset(Stream& stream)
{
	ULONG nRead;

	uint32 verflags;
	nRead = stream.Read(&verflags, 4);
	verflags = BigEndian32(verflags);
	uint8 version = (uint8)(verflags >> 24);

	if (version == 0)
	{
		uint32 entry_count;
		nRead = stream.Read(&entry_count, 4);
		entry_count = BigEndian32(entry_count);

		TRACE("\tchunk_count: %d\n", entry_count);

		for (uint i = 0; i < entry_count; i++)
		{
			uint32 chunk_offset;
			nRead = stream.Read(&chunk_offset, 4);
			chunk_offset = BigEndian32(chunk_offset);

			Chunk chunk;
			chunk.m_offset = chunk_offset;
			m_chunks.Add(chunk);
		}
	}
	else
	{
		throw L"Unknown version in ChunkOffset atom";
	}
}

/*
STDMETHODIMP CTrack::Render(ILPin *ppinOut, ILGraphBuilder *pGraph)
{
	CComPtr<ILEnum
	m_sampleDescriptions[0]->m_decoder->EnumPins(;

	return S_OK;
}
*/

#if 0
ILBaseFilter* CTrack::QueryFilter() const
{
	return m_pMovie;
}
#endif

}	// Media
}
