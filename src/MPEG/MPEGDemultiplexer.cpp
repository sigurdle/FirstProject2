#include "StdAfx.h"
#include <stdio.h>
#include "MPEG.h"
#include "MPEGDemultiplexer.h"

#if _DEBUG
#include <stdlib.h>
#endif

namespace System
{
namespace MediaShow
{

struct vtab2
{
	int len;
	uint32 mask;
	int index;
};

#ifdef _DEBUG
int compare( const void *arg1, const void *arg2 )
{
   /* Compare all of both strings: */
   if (((vtab2*)arg1)->len > ((vtab2*)arg2)->len)
		return 1;
	else if (((vtab2*)arg1)->len < ((vtab2*)arg2)->len)
		return -1;
	else
		return 0;
}
#endif

ErrorCode MpegDemultiplexer::Open()
{
#ifdef _DEBUG
	if (false)
	{
		FILE* fp = fopen("C:\\mpeg_tab.cpp", "wb");

		char* (*table) = NULL;//macroblock_types_B;

		int count = 0;
		while (table[count])
		{
			count++;
		}

		int len = 0;

		vtab2 vtable[1024];

		int i = 0;
		while (table[i])
		{
			int mask = 0;
			char* p = table[i];
			while (*p)
			{
				ASSERT(*p == '0' || *p == '1');

				mask <<= 1;
				if (*p == '1') mask |= 1;
				p++;
			}

			int len2 = p - table[i];

			vtable[i].mask = mask;
			vtable[i].index = i;
			vtable[i].len = len2;

			i++;
		}

		qsort(vtable, count, sizeof(vtab2), compare);

		{
			for (int i = 0; i < count; i++)
			{
				fprintf(fp, "%d, %d, %d,\n", vtable[i].len, vtable[i].mask, vtable[i].index);
			}
		}

		fclose(fp);

		return 0;
	}
#endif

//	m_data = NULL;

//	m_stream = stream;

	m_file = new BitStreamEx(new System::IO::CByteStream(new ByteStreamWrapper(m_stream)));
//	m_file->m_stream = m_stream;
	/*
	{
		LARGE_INTEGER li;

		ULARGE_INTEGER size;

		li.QuadPart = 0;
		m_stream->Seek(li, STREAM_SEEK_END, &size);

		m_file->m_size = size.QuadPart;

		li.QuadPart = 0;
		m_stream->Seek(li, STREAM_SEEK_SET, NULL);

		m_file->m_buffer = (LPBYTE)GlobalAlloc(0, m_file->m_size);
		m_stream->Read(m_file->m_buffer, m_file->m_size, NULL);

		m_file->m_pos = 0;
	}
	*/

	//m_file->m_bitcnt = 8;

	TRY
	{
		m_file->next_start_code();
	}
	CATCH(int)
	{
		return Error;
	}

	/*
	if (m_file->m_next_code == 0x01b3)	// Only video stream
	{
		CComObject<CMPEGVideoStream>* pStream;
		CComObject<CMPEGVideoStream>::CreateInstance(&pStream);
		pStream->AddRef();

		m_streams.AddTail((IMPEGStream*)pStream);

		m_file->ungetbits(32);

		HRESULT hr = pStream->ReadBitStream(m_file);	// Using same bitStream
	}
	else
		*/
		if (m_file->m_next_code == 0x01ba)	// Systems stream
	{
		do
		{
			TRY
			{
				pack();
			}
			CATCH(int code)
			{
				break;
			}
		}
		while (m_file->m_next_code == 0x01ba);

		if (m_file->m_next_code != 0x1b9)	// end-code
		{
#if WIN32
			MessageBoxA(NULL, "Missing end-code", "MPEG Demultiplexer", MB_OK);
#else
			printf("MPEG Demultiplexer: Missing end-code\n");
#endif
		}

		list<MpegStream*>::iterator pos = m_streams.begin();
		while (pos != m_streams.end())
		{
			MpegStream* pStream = *pos;
			++pos;

			//pStream->m_bytestream = am* pByteStream = new CStreamByteStream(pStream);

#if !STREAM_MEMORY_BUFFER
#else
			pStream->m_buffer = new uint8[pStream->m_byteLength];
			pStream->m_size = pStream->m_byteLength;

			uint8* p = pStream->m_buffer;

			list<CPacket*>::iterator pos2 = pStream->m_packets.begin();
			while (pos2 != pStream->m_packets.end())
			{
				CPacket* pPacket = *pos2;//(CPacket*)pStream->m_packets.GetNext(pos2);
				++pos2;

				/*
				LARGE_INTEGER li;
				li.QuadPart = pPacket->m_byteOffset;
				m_stream->Seek(li, STREAM_SEEK_SET, NULL);
				*/
				m_stream->Read(p, pPacket->m_byteOffset, pPacket->m_byteLength);

				p += pPacket->m_byteLength;
			}
#endif

#if 0
			pStream->Connect(pStream->m_connectedTo, NULL);
#endif

			//CBitStream* pBitStream = new CBitStream(pByteStream);

#if 0	// Have this
			HRESULT hr = pStream->Open(pBitStream);
#endif
		}
	}
	else
		return Error;

	return Success;
}

MpegStream* MpegDemultiplexer::FindStream(uint8 stream_id)
{
	list<MpegStream*>::iterator pos = m_streams.begin();
	while (pos != m_streams.end())
	{
		MpegStream* pStream = *pos;
		++pos;

		if (pStream->m_stream_id == stream_id)
		{
			return pStream;
		}
	}

	return NULL;
}

void MpegDemultiplexer::pack()
{
	ASSERT(m_file->m_next_code == 0x01ba);

	pack_header();

	if (m_mpeg1)	// mpeg1
	{
	//	m_file->next_start_code();
		while (m_file->m_next_code >= 0x1bc && m_file->m_next_code <= 0x1ff)
		{
			packet_mpeg1();
		//	m_file->next_start_code();
		}
	}
	else	// mpeg2
	{
	//	pack_header();

	//	m_file->next_start_code();
		while (m_file->m_next_code != 0x1ba && m_file->m_next_code != 0x1b9)
		{
			PES_packet();
		}

#if 0
		while (m_file->m_next_code == 0x1bc/* && m_file->m_next_code <= 0x1ff*/)
		{
			program_stream_map_mpeg2();
		}
#endif
	}
}

void MpegDemultiplexer::pack_header()
{
// 	pack_start_code	32 

// TODO, check here for MPEG1 or MPEG2
	// MPEG2 is '01'	2

	int stuff = m_file->getnbits(2);
	if (stuff == 1)
	{
		m_mpeg1 = false;
	}
	else
	{
		int stuff = m_file->getnbits(2);	// '0010'
		ASSERT(stuff == 2);

		m_mpeg1 = true;
	}

	m_file->getnbits(3);//system_clock_reference_base [32..30]	3
	m_file->getmarkerbit();//marker_bit	1
	m_file->getnbits(15);//system_clock_reference_base [29..15]	15
	m_file->getmarkerbit();//marker_bit	1
	m_file->getnbits(15);//system_clock_reference_base [14..0]	15
	m_file->getmarkerbit();//marker_bit	1

	if (!m_mpeg1)	// mpeg2
	{
		m_file->getnbits(9);//system_clock_reference_extension	9
		m_file->getmarkerbit();//marker_bit	1
		m_file->getnbits(22);//Program_mux_rate	22
		m_file->getmarkerbit();//marker_bit	1
		m_file->getmarkerbit();//marker_bit	1

		m_file->getnbits(5);//Reserved	5
		int pack_stuffing_length = m_file->getnbits(3);
		for (int i = 0; i < pack_stuffing_length; i++)
		{
			m_file->getnbits(8);//stuffing_byte	8
		}
	}
	else	// mpeg1
	{
		m_file->getmarkerbit();//marker_bit	1
		m_file->getnbits(22);//Program_mux_rate	22
		m_file->getmarkerbit();//marker_bit	1
	}

//	if (nextbits() == system_header_start_code)
	m_file->next_start_code();
	if (m_file->m_next_code == 0x000001bb)
	{
		system_header();
	}
}

void MpegDemultiplexer::system_header()
{
	ASSERT(m_file->m_next_code == 0x000001bb);

	uint16 header_length = m_file->getnbits(16);
	m_file->getmarkerbit();
	m_file->getnbits(22);//rate_bound	22
	m_file->getmarkerbit();
	m_file->getnbits(6);//audio_bound	6
	m_file->getbit();//fixed_flag	1
	m_file->getbit();//CSPS_flag	1
	m_file->getbit();//system_audio_lock_flag	1
	m_file->getbit();//system_video_lock_flag	1
	m_file->getmarkerbit();
	m_file->getnbits(5);//video_bound	5

	if (m_mpeg1)
	{
		uint8 reserved_byte = m_file->getnbits(8);
		ASSERT(reserved_byte == 0xFF);
	}
	else
	{
		int packet_rate_restriction_flag = m_file->getbit();

		uint8 reserved_bits = m_file->getnbits(7);
		ASSERT(reserved_bits == 0x7F);
	}

	int nbits = 48;

	while (m_file->looknbits(1) == 1)
	{
		int stream_id = m_file->getnbits(8);
		int filler = m_file->getnbits(2);//'11'	2
		ASSERT(filler == 3);

		if ((stream_id & 0xf0) == 0xe0)	// video stream
		{
			if (FindStream(stream_id) == NULL)
			{
				MpegStream* pStream = new MpegStream;
				pStream->m_pFilter = this;
				pStream->m_stream_id = stream_id;

				m_streams.push_back(pStream);
			}
		}
		else if ((stream_id & 0xe0) == 0xc0)	// audio stream
		{
			if (FindStream(stream_id) == NULL)
			{
				MpegStream* pStream = new MpegStream;
				pStream->m_pFilter = this;
				pStream->m_stream_id = stream_id;

				m_streams.push_back(pStream);
			}

#if 0
			if (FindStream(stream_id) == NULL)
			{
				CMPEGStream* pStream = new CMPEGStream;
				//CComObject<CMPEGStream>::CreateInstance(&pStream);
				//pStream->AddRef();
				pStream->m_pFilter = this;
				pStream->m_id = L"Stream Output";
				pStream->m_stream_id = stream_id;

#if 0
			// Don't actually connect yet
			pStream->m_connectedTo.CoCreateInstance(L"LMPEGAudio.LMPEGAudioDecoder");
#endif

				m_streams.AddTail((CMPEGStream*)pStream);
				AddPin(pStream);
			}
#endif
		}

		int P_STD_buffer_bound_scale = m_file->getnbits(1);
		int P_STD_buffer_size_bound = m_file->getnbits(13);

		nbits += 1+7+2+1+13;
	}
	//m_file->ungetbits(1);

	int nbytes = (nbits + 7)/8;

	int N = header_length - nbytes;
	ASSERT(N == 0);

	m_file->next_start_code();
}

void MpegDemultiplexer::packet_mpeg1()
{
	int stream_id = m_file->m_next_code & 0xff;

	MpegStream* pStream = FindStream(stream_id);

	CPacket* pPacket = NULL;

	if (pStream)
	{
		pPacket = new CPacket;
		pPacket->m_pStream = pStream;

		pStream->m_packets.push_back(pPacket);
	}

	uint16 packet_length = m_file->getnbits(16);

//	TRACE("packet_mpeg1, stream_id: %x\n", stream_id);

	m_file->m_countBits = 0;

	if (stream_id != 0xbf/*private-stream2*/)
	{
		// stuffing bytes
		while (m_file->getnbits(8) == 0xff)
			;
		m_file->ungetbits(8);

		if ((m_file->m_countBits/8) < packet_length)	// ??
		{
			int nextbits;

			nextbits = m_file->getnbits(2);
			if (nextbits == 1)//‘01’
			{
				int STD_buffer_scale = m_file->getnbits(1);
				int STD_buffer_size = m_file->getnbits(13);
			}
			else
				m_file->ungetbits(2);

			nextbits = m_file->getnbits(4);	// 4 ?

			if (nextbits == 2)//‘0010’
			{
				m_file->getnbits(3);//presentation-time-stamp[ 32..30]
				m_file->getmarkerbit();//marker-bit
				m_file->getnbits(15);//presentation-time-stamp[ 29..15]
				m_file->getmarkerbit();//marker-bit
				m_file->getnbits(15);//presentation-time-stamp[ 14..0]
				m_file->getmarkerbit();//marker-bit
			}
			else if (nextbits == 3)// ‘0011’
			{
				m_file->getnbits(3);//presentation-time-stamp[ 32..30]
				m_file->getmarkerbit();//marker-bit
				m_file->getnbits(15);//presentation-time-stamp[ 29..15]
				m_file->getmarkerbit();//marker-bit
				m_file->getnbits(15);//presentation-time-stamp[ 14..0]
				m_file->getmarkerbit();//marker-bit
				int filler = m_file->getnbits(4);//‘0001’
				ASSERT(filler == 1);

				m_file->getnbits(3);//decoding-time-stamp[ 32..30]
				m_file->getmarkerbit();//marker-bit
				m_file->getnbits(15);//decoding_time_stamp[29..15]
				m_file->getmarkerbit();//marker-bit
				m_file->getnbits(15);//decoding-time-stamp[ 14..0]
				m_file->getmarkerbit();//marker-bit
			}
			else
			{
				ASSERT(nextbits == 0);
				nextbits = m_file->getnbits(4);//‘0000 1111’
				ASSERT(nextbits == 0xf);
			}
		}
	}

	ASSERT(m_file->is_byte_aligned());
	ASSERT((m_file->m_countBits/8)*8 == m_file->m_countBits);	// packet is hole number of bytes

	int nbytes = (m_file->m_countBits)/8;

	int N = packet_length - nbytes;

	if (pPacket)
	{
	// Remember file offset of start of this packet

		pPacket->m_byteOffset = m_file->GetBytePos();//(m_file->m_byteStream->GetPos()<<2) - ((m_file->m_bitcnt)>>3);//m_byteStream->Seek(0, STREAM_SEEK_CUR);
		//ASSERT(m_file->m_byteStream->Seek(0, STREAM_SEEK_CUR)/*-m_file->m_nstacked*/ == pPacket->m_byteOffset);

	// Remember length of this packet in bytes
		pPacket->m_byteLength = N;

		pStream->m_byteLength += pPacket->m_byteLength;
	}

#if 0
	if (stream_id == 0xbe)	// padding stream
	{
		for (int i = 0; i < N; i++)
		{
			/*
			BYTE byte;
			m_file->m_byteStream->Read(&byte, 1);
			*/
		//	ASSERT(byte == 0xff);
		}
	}
	else
#endif
	{
		//m_file->skipnbits(N*8);

	//	m_file->SetBytePos->Seek(N, STREAM_SEEK_CUR);
		//m_file->m_byteStream->Seek(N>>2, STREAM_SEEK_CUR);
	//	m_file->m_byteStream->Seek(m_file->m_byteStream->m_bytepos+N)>>2, STREAM_SEEK_SET);
	//	m_file->getnbits((N & 3) << 3);

		//m_file->Seek(N
		m_file->SetBytePos(m_file->GetBytePos() + N);

	//	m_file->m_nstacked = 0;
	}

	m_file->next_start_code();
}

void MpegDemultiplexer::PES_packet()
{
	int stream_id = m_file->m_next_code & 0xff;
	uint16 PES_packet_length = m_file->getnbits(16);
	m_file->m_countBits = 0;

	switch (stream_id)
	{
	case 0xbc/*program_stream_map*/:
		{
			ASSERT(0);
		}
		break;

	case 0xbf/*private-stream2*/:
		{
			/*m_file->m_bytepos =*/ m_file->SetBytePos(m_file->GetBytePos() + PES_packet_length);
			//m_file->m_nstacked = 0;
		}
		break;
		
	case 0xbe/*padding*/:
		{
			// Maybe check that all bytes are 0xFF
			/*m_file->m_bytepos =*/ m_file->SetBytePos(m_file->GetBytePos() + PES_packet_length);
			//m_file->m_nstacked = 0;
		}
		break;
		
	default:
		{
			int fill = m_file->getnbits(2);
			ASSERT(fill == 2);

			int PES_scrambling_control = m_file->getnbits(2);// bslbf
			int PES_priority = m_file->getbit();// bslbf
			int data_alignment_indicator = m_file->getbit();// bslbf
			int copyright = m_file->getbit();// bslbf
			int original_or_copy = m_file->getbit();// bslbf
			int PTS_DTS_flags = m_file->getnbits(2);// bslbf
			int ESCR_flag = m_file->getbit();// bslbf
			int ES_rate_flag = m_file->getbit();// bslbf
			int DSM_trick_mode_flag = m_file->getbit();// bslbf
			int additional_copy_info_flag = m_file->getbit();// bslbf
			int PES_CRC_flag = m_file->getbit();// bslbf
			int PES_extension_flag = m_file->getbit();// bslbf
			uint8 PES_header_data_length = m_file->getnbits(8);

			if (PTS_DTS_flags == 2)
			{
				int fill = m_file->getnbits(4);//	'0010' 4 bslbf
				ASSERT(fill == 2);
				
				m_file->getnbits(3);//PTS [32..30] 3 bslbf
				m_file->getmarkerbit();//marker_bit 1 bslbf
				m_file->getnbits(15);//PTS [29..15] 15 bslbf
				m_file->getmarkerbit();// 1 bslbf
				m_file->getnbits(15);//PTS [14..0] 15 bslbf
				m_file->getmarkerbit();// 1 bslbf
			}
			else if (PTS_DTS_flags == 3)
			{
				int fill = m_file->getnbits(4);//
				ASSERT(fill == 3);//'0011' 4 bslbf
				m_file->getnbits(3);//PTS [32..30] 3 bslbf
				m_file->getmarkerbit();//marker_bit 1 bslbf
				m_file->getnbits(15);//PTS [29..15] 15 bslbf
				m_file->getmarkerbit();//marker_bit 1 bslbf
				m_file->getnbits(15);//PTS [14..0] 15 bslbf
				m_file->getmarkerbit();//marker_bit 1 bslbf
				fill = m_file->getnbits(4);//marker_bit 1 bslbf
				ASSERT(fill == 1);//'0001' 4 bslbf
				m_file->getnbits(3);//DTS [32..30] 3 bslbf
				m_file->getmarkerbit();//marker_bit 1 bslbf
				m_file->getnbits(15);//DTS [29..15] 15 bslbf
				m_file->getmarkerbit();//marker_bit 1 bslbf
				m_file->getnbits(15);//DTS [14..0] 15 bslbf
				m_file->getmarkerbit();//marker_bit 1 bslbf
			}

			if (ESCR_flag == 1)
			{
				ASSERT(0);
				/*
			reserved 2 bslbf
			ESCR_base[32..30] 3 bslbf
			marker_bit 1 bslbf
			ESCR_base[29..15] 15 bslbf
			marker_bit 1 bslbf
			ESCR_base[14..0] 15 bslbf
			marker_bit 1 bslbf
			ESCR_extension 9 uimsbf
			marker_bit 1 bslbf
			*/
			}

			if (ES_rate_flag == 1)
			{
				ASSERT(0);
				/*
marker_bit 1 bslbf
ES_rate 22 uimsbf
marker_bit 1 bslbf
*/
			}

			if (DSM_trick_mode_flag == 1)
			{
				ASSERT(0);
				/*
				trick_mode_control 3 uimsbf
				if ( trick_mode_control = = fast_forward )
				{
				field_id 2 bslbf
				intra_slice_refresh 1 bslbf
				frequency_truncation 2 bslbf
				}
				else if ( trick_mode_control = = slow_motion )
				{
				rep_cntrl 5 uimsbf
				}
				else if ( trick_mode_control = = freeze_frame )
				{
				field_id 2 uimsbf
				reserved 3 bslbf
				}
				else if ( trick_mode_control = = fast_reverse )
				{
				field_id 2 bslbf
				intra_slice_refresh 1 bslbf
				frequency_truncation 2 bslbf
				}
				else if ( trick_mode_control = = slow_reverse )
				{
					rep_cntrl 5 uimsbf
				}
				else
					reserved 5 bslbf
			*/
			}

			if (additional_copy_info_flag == 1)
			{
				m_file->getmarkerbit();// 1 bslbf
				int additional_copy_info = m_file->getnbits(7);// bslbf
			}

			if (PES_CRC_flag == 1)
			{
				int previous_PES_packet_CRC = m_file->getnbits(16);// bslbf
			}

			if (PES_extension_flag == 1)
			{
				int PES_private_data_flag = m_file->getbit();// bslbf
				int pack_header_field_flag = m_file->getbit();// 1 bslbf
				int program_packet_sequence_counter_flag = m_file->getbit();// 1 bslbf
				int P_STD_buffer_flag = m_file->getnbits(1);// 1 bslbf
				m_file->getnbits(3);//reserved 3 bslbf
				int PES_extension_flag_2 = m_file->getbit();// 1 bslbf
				if ( PES_private_data_flag == 1)
				{
					m_file->skipnbits(128);
					//PES_private_data 128 bslbf
				}
				if (pack_header_field_flag == 1)
				{
					int pack_field_length = m_file->getnbits(8);// uimsbf
					pack_header();
				}
				if (program_packet_sequence_counter_flag == 1)
				{
					ASSERT(0);
					/*
					marker_bit 1 bslbf
						program_packet_sequence_counter 7 uimsbf
						marker_bit 1 bslbf
						MPEG1_MPEG2_identifier 1 bslbf
						original_stuff_length 6 uimsbf
						*/
				}
				if (P_STD_buffer_flag == 1)
				{
					int fill = m_file->getnbits(2);//'01' 2 bslbf
					ASSERT(fill == 1);

					int P_STD_buffer_scale = m_file->getbit();//1 bslbf
					int P_STD_buffer_size = m_file->getnbits(13);//13 uimsbf
				}
				if (PES_extension_flag_2 == 1)
				{
					m_file->getmarkerbit();// 1 bslbf
					uint8 PES_extension_field_length = m_file->getnbits(7);// uimsbf
					for (int i = 0; i < PES_extension_field_length; i++)
					{
						//reserved 8 bslbf
						uint8 reserved = m_file->getnbits(8);
					}
				}
			}

			int i;

			ASSERT((m_file->m_countBits & 0x3) == 0);
			int n = (m_file->m_countBits >> 3);

			int N1 = n - (PES_header_data_length+3);
			int N2 = PES_packet_length - n;

			for (i = 0; i < N1; i++)
			{
				m_file->getnbits(8);//stuffing_byte 8 bslbf
			}

			MpegStream* pStream = FindStream(stream_id);

			if (pStream == NULL)	// ???
			{
				pStream = new MpegStream;
				pStream->m_pFilter = this;
				pStream->m_stream_id = stream_id;

				m_streams.push_back(pStream);
			}

			CPacket* pPacket = NULL;
			if (pStream)
			{
				pPacket = new CPacket;
				pPacket->m_pStream = pStream;

				pStream->m_packets.push_back(pPacket);
			}

			pPacket->m_byteOffset = m_file->GetBytePos();
			pPacket->m_byteLength = N2;

			pStream->m_byteLength += pPacket->m_byteLength;

			m_file->SetBytePos(pPacket->m_byteOffset + N2);

			/*
			for (i = 0; i < N2; i++)
			{
				m_file->getnbits(8);//PES_packet_data_byte 8 bslbf
			}
			*/
		}
		break;
	}

	m_file->next_start_code();
}

void MpegDemultiplexer::program_stream_map_mpeg2()
{
	int i;

//	packet_start_code_prefix	24
//	map_stream_id	8
	int map_stream_id = m_file->m_next_code & 0xff;
	ASSERT(map_stream_id == 0xbc);

	uint16 program_stream_map_length = m_file->getnbits(16);
	bool current_next_indicator = m_file->getbit();
	m_file->getnbits(2);//Reserved	2
	m_file->getnbits(5);//program_stream_map_version	5
	m_file->getnbits(7);//Reserved	7
	m_file->getmarkerbit();

	int program_stream_info_length = m_file->getnbits(16);
	for (i = 0; i < program_stream_info_length; i++)
	{
		ASSERT(0);
	//	descriptor()
	}

	int elementary_stream_map_length	= m_file->getnbits(16);
	for (i = 0; i < elementary_stream_map_length; i++)
	{
		int stream_type = m_file->getnbits(8);
		int Elementary_stream_id = m_file->getnbits(8);
		int Elementary_stream_info_length = m_file->getnbits(16);
		for (i = 0; i < Elementary_stream_info_length; i++)
		{
			ASSERT(0);
		//	descriptor()
		}
	}
	uint32 CRC_32 = m_file->getnbits(32);
}

}	// MediaShow
}
