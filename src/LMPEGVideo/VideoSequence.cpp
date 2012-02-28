#include "stdafx.h"
#include "LMPEGVideo.h"

#include <stdio.h>
#include <stdlib.h>

template<class T> T* find(T* begin, T* end, T p)
{
	T* it = begin;
	while (it != end)
	{
		if (*it == p)
			return it;

		++it;
	}

	return NULL;
}

namespace System
{
namespace MediaShow
{

static uint8 intra_default[8*8] =
{
	8,	16,	19,	22,	26,	27,	29,	34,
	16,	16,	22,	24,	27,	29,	34,	37,
	19,	22,	26,	27,	29,	34,	34,	38,
	22,	22,	26,	27,	29,	34,	37,	40,
	22,	26,	27,	29,	32,	35,	40,	48,
	26,	27,	29,	32,	35,	40,	48,	58,
	26,	27,	29,	34,	38,	46,	56,	69,
	27,	29,	35,	38,	46,	56,	69,	83,
};

static uint8 non_intra_default[8*8] =
{
	16,	16,	16,	16,	16,	16,	16,	16,
	16,	16,	16,	16,	16,	16,	16,	16,
	16,	16,	16,	16,	16,	16,	16,	16,
	16,	16,	16,	16,	16,	16,	16,	16,
	16,	16,	16,	16,	16,	16,	16,	16,
	16,	16,	16,	16,	16,	16,	16,	16,
	16,	16,	16,	16,	16,	16,	16,	16,
	16,	16,	16,	16,	16,	16,	16,	16,
};

double tab_frame_rate_value[] =
{
	0,	// forbidden
	/*24 000÷1001*/ 23.976,
	24,
	25,
	/*30 000÷1001*/ 29.97,
	30,
	50,
	/*60 000÷1001*/ 59.94,
	60,
};

ErrorCode MpegVideoSequenceFormat::video_sequence()
{
	ASSERT(m_file);
	ASSERT(m_file->m_next_code == 0x01b3);

/*
In the case that the lower layer conforms to ISO/IEC 11172-2 (and not this
specification), sequence_extension() is not present in the lower layer, and
the following values shall be assumed for the decoding process.
*/
	m_progressive_sequence = 1;
	m_chroma_format = 1;// 4:2:0
//	horizontal_size_extension	= 0;
//	vertical_size_extension		= 0;
//	bit_rate_extension		= 0;
//	vbv_buffer_size_extension	= 0;
//	low_delay			= 0;
//	frame_rate_extension_n		= 0;
//	frame_rate_extension_d		= 0;
/*
In the case that the lower layer conforms to ISO/IEC 11172-2 (and not this specification) then picture_coding_extension() is not present in the lower layer and the following values shall be assumed for the decoding process:
*/
/*
f_code[0][0]	=	forward_f_code in the lower layer or 15
f_code[0][1]		=	forward_f_code in the lower layer or 15
f_code[1][0]	=	backward_f_code in the lower layer or 15
f_code[1][1]	=	backward_f_code in the lower layer or 15
*/
//	m_intra_dc_precision	= 0;
//	m_picture_structure = PictureStructure_Frame_picture;
/*
top_field_first			=	0
*/
//	m_frame_pred_frame_dct	= 1;
//	m_concealment_motion_vectors = 0;
//	m_intra_vlc_format = 0;
/*
repeat_first_field		=	0
chroma_420_type		=	1
progressive_frame		=	1
composite_display_flag		=	0
*/

	TRY
	{
		sequence_header();

		if (m_file->m_next_code == 0x1b5)	// extension_start_code
		{
			m_mpeg1 = false;
			sequence_extension();
		}
		else
		{
			/* ISO/IEC 11172-2 */ // (MPEG-1)
			m_mpeg1 = true;
		}

	//	m_mpeg1 = false;

		/*
		m_bitrate = m_file->getnbits(18);	// bitrate
		if (m_bitrate == 0x3FFFF)
		{
			TRACE("Bitrate: variable\n");
		}
		else
		*/
		{
			TRACE("Bitrate: %g Kbit/s\n", m_bitrate*400 / 1000.0);
		}

		{
			MessageBeep(-1);
#if 0
		// Create video media type
			ATLASSERT(m_pMediaType == NULL);

			CComObject<CVideoMediaType>::CreateInstance(&m_pMediaType);
			m_pMediaType->AddRef();
			m_pMediaType->m_pVideoOut = this;
#endif
		}
	}
	CATCH(int)
	{
		return Error;
	}

	return Success;
}

struct vtab2
{
	int len;
	uint32 mask;
	int index;
};

int compare3( const void *arg1, const void *arg2 )
{
   /* Compare all of both strings: */
   if (((vtab2*)arg1)->mask > ((vtab2*)arg2)->mask)
		return 1;
	else if (((vtab2*)arg1)->mask < ((vtab2*)arg2)->mask)
		return -1;
	else
		ASSERT(0);
		/*if (((vtab2*)arg1)->mask > ((vtab2*)arg2)->mask)
		return 1;
	else
		return -1;
		*/
}

extern char* str_tab_B1[];
extern char* str_tab_B9[512];
extern char* str_tab_B10[2048];
extern char* str_tab_B12[];
extern char* str_tab_B13[];
extern char* str_tab_B14[];
extern char* str_macroblock_types_P[];
extern char* str_macroblock_types_B[];

extern char* _str_tab_B14[];

extern char* str_tab_B14[];
extern char* str_tab_B15[];

#if 0
void CVideoSequence::Frame()
{
	Picture* pic = new Picture;

	PictureDecoder* pPicture = new PictureDecoder(this, m_file);
	pPicture->m_pic = pic;

	m_currentFrame++;

	{
		pPicture->m_quantiser_scale_code = m_quantiser_scale_code;
		/*
		for (int i = 0; i < 64; i++)
		{
			pPicture->m_intra_quantiser_matrix[i] = m_intra_quantiser_matrix[i];
			pPicture->m_non_intra_quantiser_matrix[i] = m_non_intra_quantiser_matrix[i];
		}
		*/
	}

	/*
	ASSERT(m_file->is_byte_aligned());
	pic->m_datapos = m_file->m_countBits / 8;//m_byteStream->Seek(0, STREAM_SEEK_CUR);

	pic->m_temporal_reference = m_file->getnbits(10);

	if (pic->m_temporal_reference == 0)
	{
		m_temporal_offset = m_displayPictures.GetCount();
	}

	pic->m_temporal_reference_abs = pic->m_temporal_reference + m_temporal_offset;

	pic->m_picture_coding_type = m_file->getnbits(3);	// I=1, P=2, B=3
	if (pic->m_picture_coding_type != 1 && pic->m_picture_coding_type != 2 && pic->m_picture_coding_type != 3)
	{
		ASSERT(0);
		THROW(-1);
	}
	*/

	pPicture->picture_header();

	if (!m_mpeg1)
	{
		pPicture->picture_coding_extension();
		pPicture->extension_and_user_data(2);
	}

//	pPicture->CreateBuffers();

	/*
	if (m_pictures.GetSize() == 1)
	{
		FillMemory(pPicture->m_ybuf, m_mb_width*16 * ((m_vertical_size+15)/16) * 16, 255);
//		CopyMemory(pPicture->m_ybuf, m_pictures[0]->m_ybuf, m_mb_width*16 * (m_vertical_size+15)/16 * 16);
	}
	*/

//	pic->m_datapos = m_file->m_byteStream->Seek(0, STREAM_SEEK_CUR);

#if 0
	m_pictures.AddTail(pic);

// Insert into display order piclist
	{
		UPOSITION pos = m_displayPictures.GetHeadPosition();
		while (pos)
		{
			UPOSITION _pos = pos;
			Picture* pic2 = (Picture*)m_displayPictures.GetNext(pos);
			if (pic->m_temporal_reference_abs < pic2->m_temporal_reference_abs)
			{
				m_displayPictures.InsertBefore(_pos, pic);
				goto inserted;
			}
		}
		m_displayPictures.AddTail(pic);
inserted:
		;
	}
#endif

	pPicture->m_pos = m_groupPictures.AddTail(pPicture);

// Insert sorted
	{
		UPOSITION pos = piclist.GetHeadPosition();
		while (pos)
		{
			UPOSITION _pos = pos;
			PictureDecoder* pPic = (PictureDecoder*)piclist.GetNext(pos);
			if (pPicture->m_pic->m_temporal_reference < pPic->m_pic->m_temporal_reference)
			{
				piclist.InsertBefore(_pos, pPicture);
				goto inserted2;
			}
		}
		piclist.AddTail(pPicture);
inserted2:
		;
	}

	if (buffers[nbuffer] == NULL)
	{
		int mb_rows = (m_vertical_size + 15)/16;

		buffers[nbuffer] = new ImageBuffer;
		buffers[nbuffer]->m_buf[0] = (uint8*)calloc(1, (m_mb_width*16+8)*(mb_rows*16+8));
		buffers[nbuffer]->m_buf[1] = (uint8*)calloc(1, (m_mb_width*8+8)*(mb_rows*8+8));
		buffers[nbuffer]->m_buf[2] = (uint8*)calloc(1, (m_mb_width*8+8)*(mb_rows*8+8));
		nbuffers = MAX(nbuffer, nbuffers);
	}

	pPicture->m_ybuf = buffers[nbuffer]->m_buf[0];
	pPicture->m_crbuf = buffers[nbuffer]->m_buf[1];
	pPicture->m_cbbuf = buffers[nbuffer]->m_buf[2];
	nbuffer++;

	//pPicture->CreateBuffers();
	pPicture->picture_data(TRUE);

//	TRACE("frame count: %d : picture_coding_type: %d\n", m_pictures.GetCount(), pPicture->m_picture_coding_type);

	{
		{
			m_quantiser_scale_code = pPicture->m_quantiser_scale_code;
			/*
			for (int i = 0; i < 64; i++)
			{
				m_intra_quantiser_matrix[i] = pPicture->m_intra_quantiser_matrix[i];
				m_non_intra_quantiser_matrix[i] = pPicture->m_non_intra_quantiser_matrix[i];
			}
			*/
		}
	}

	/*
	if (pPicture->m_picture_coding_type == 3)
	{
		m_pictures.RemoveAt(pPicture->m_pos);
	}
	else
	*/
	{
	//	pPicture->CreateBuffers();
	}

	if (pPicture->m_pic->m_picture_coding_type != 3)
	{
		UPOSITION pos = piclist.GetHeadPosition();
		while (pos)
		{
			UPOSITION _pos = pos;
			PictureDecoder* pPic = (PictureDecoder*)piclist.GetNext(pos);

			if (pPic->m_pic->m_temporal_reference < pPicture->m_pic->m_temporal_reference)
			{
				TRACE("display: %d\n", pPic->m_pic->m_temporal_reference);
				piclist.RemoveAt(_pos);

				ShowFrame(pPic);
			}
		}
	}
}
#endif

#if 0
void CVideoSequence::ShowFrame(PictureDecoder* pPicture)
{
	IMediaSample* sample;
	m_pAllocator->GetBuffer(0, &sample);

	double frameRate = tab_frame_rate_value[m_mpeg_video->m_frame_rate_code];

	LONGLONG t = pPicture->m_pic->m_temporal_reference_abs * LTIME_SCALE / frameRate;

	LONGLONG tStart = t;
	LONGLONG tEnd = t + LTIME_SCALE / frameRate;

	sample->SetTime(&tStart, &tEnd);

	SetSampleRGBData(pPicture, sample);

//	Sleep(500);

//	count++;

	bool bContinue = m_pInputPin->Receive(sample);
	if (!bContinue)//hr != S_OK)	// Stop if FAILED or S_FALSE
		ASSERT(0);//break;

	sample->Release();
}
#endif

/*
void CVideoSequence::ShowFrames()
{
}
*/

void CVideoSequence::Scan()
{
#ifdef _DEBUG
	char* (*table) = NULL;//_str_tab_B14;

	if (table)
	{
		int maxlen = 15;

		int count = 0;
		while (table[count])
		{
			count++;
		}

		int len = 0;

		vtab2 vtable[10000];

		/*
		int n = 0;
		vtable[n].mask = 0;
		vtable[n].index = 0;
		vtable[n].len = len2;
		*/

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
			ASSERT(len2 <= maxlen);

			vtable[i].mask = mask << (maxlen-len2);
			vtable[i].index = i;
			vtable[i].len = len2;

			i++;
		}

		qsort(vtable, count, sizeof(vtab2), compare3);

		//vtable[i].len = 12;
		vtable[i].mask = 1<<maxlen;

		std::FILE* fp = std::fopen("C:\\mpeg_tab.cpp", "wb");
		{
			int code = 0;

			while (code < vtable[0].mask)
			{
				std::fprintf(fp, "%d, %d,\n", vtable[0].len, vtable[0].index);
				code++;
			}

			for (int i = 0; i < count; i++)
			{
				ASSERT(code == vtable[i].mask);

				while (code < vtable[i+1].mask)
				{
					std::fprintf(fp, "%d, %d,\n", vtable[i].len, vtable[i].index);
					code++;
				}
			}
			//ASSERT(code == 4096);

			/*
			for (int i = 0; i < count; i++)
			{
			}
			*/
		}

		std::fclose(fp);

		return;
	}
#endif

#if 0
	try
	{
		m_time = 0;

		m_temporal_offset = 0;

		int count = 0;

		nbuffer = 0;
		nbuffers = 0;
		memset(buffers, 0, 4*1024);

		if (!m_mpeg1)	// MPEG 2
		{

			do
			{
				extension_and_user_data(0);

				do
				{
					if (m_file->m_next_code == 0x1b8)	// group start code
					{
						TRACE("group\n");

						ShowFrames();

						nbuffer = 0;

						m_groupPictures.RemoveAll();

						group_of_pictures_header();
						extension_and_user_data(1);
					}

					Frame();
					//m_currentFrame = m_pictures.GetCount()-1;

				//	delete pPicture->m_ybuf;

	#ifdef _DEBUG
				//	if (pPicture->m_picture_coding_type != 3)
				//		Sleep(1000);
					/*
					Sleep(500);
					if (m_pictures.GetCount() >= 3)
						return S_OK;//break;
						*/
#endif
				}
				while (m_file->m_next_code == 0x1b8 || m_file->m_next_code == 0x100);	// group or picture
			}
			while (m_file->m_next_code != 0x1b7);	// end-code

			//TRACE("total frames: %d\n", m_groupPictures.GetCount());
		}
		else
		{
			extension_and_user_data(0);

			do
			{
				do
				{
					if (m_file->m_next_code == 0x1b8)	// group start code
					{
						TRACE("group\n");

						UPOSITION pos = piclist.GetHeadPosition();
						while (pos)
						{
							UPOSITION _pos = pos;
							PictureDecoder* pPic = (PictureDecoder*)piclist.GetNext(pos);

						//	if (pPic->m_temporal_reference < pPicture->m_temporal_reference)
							{
								TRACE("display: %d\n", pPic->m_pic->m_temporal_reference);
								piclist.RemoveAt(_pos);

							//	if (pPic->m_picture_coding_type != 3)
								{

								ShowFrame(pPic);

								}
							}
						}

						nbuffer = 0;
						m_groupPictures.RemoveAll();

						group_of_pictures_header();
						extension_and_user_data(1);	// ???
					}

					//if (m_next_code == 0x100)	// picture start code
					{

						Frame();
	#ifdef _DEBUG
				//		if (m_pictures.GetCount() >= 1)
				//			return S_OK;//break;
	#endif
					}
				}
				while (m_file->m_next_code == 0x1b8 || m_file->m_next_code == 0x100);	// group or picture
			}
			while (m_file->m_next_code != 0x1b7);	// end-code
		}
	}
	catch(int)
	{
		/*
		if (m_pictures.GetCount() > 0)
		{
			return S_FALSE;	// Partial success
		}
		else
			return E_FAIL;
			*/
		return S_FALSE;
	}

	if (m_file->m_next_code == 0x1b7)
		return S_OK;
	else
		return S_FALSE;	// partal success
#endif

	ULONG nframes = 0;

	ASSERT(m_mpeg_video->m_file->is_byte_aligned());
	LONGLONG countBits = m_mpeg_video->m_file->m_countBits;
//	int bitcnt = m_mpeg_video->m_file->m_bitcnt;
	LONGLONG pos = m_mpeg_video->m_file->GetBytePos();//m_byteStream->Seek(0, System::IO::STREAM_SEEK_CUR);// - m_mpeg_video->m_file->m_byteStream->m_nstacked;

	m_temporal_offset = 0;
	int iGroup = -1;
	int index = 0;

	TRY
	{
		while (1)
		{
			ULONG start_code = m_mpeg_video->m_file->getnbits(8);
			if (start_code == 0)
			{
				start_code = m_mpeg_video->m_file->getnbits(8);
				if (start_code == 0)
				{
					start_code = m_mpeg_video->m_file->getnbits(8);
					if (start_code == 1)
					{
						start_code = m_mpeg_video->m_file->getnbits(8) | 0x100;
					}
					else
					{
						m_mpeg_video->m_file->ungetbits(16);
						continue;
					}
				}
				else
				{
					m_mpeg_video->m_file->ungetbits(8);
					continue;
				}
			}
			else
				continue;

		//	if (m_mpeg_video->m_file->looknbits(24) == 1)
			{
		//		ULONG start_code = m_mpeg_video->m_file->getnbits(32);

				if (start_code == 0x1b8)	// group
				{
					/*int time_code =*/ m_mpeg_video->m_file->skipnbits(25);	// not used for decoding
					int closed_gop = m_mpeg_video->m_file->getbit();
					int broken_link = m_mpeg_video->m_file->getbit();

					m_temporal_offset = m_displayPictures.size();
					iGroup++;

				//	m_mpeg_video->m_file->skipnbits(7);
				//	start_code = m_mpeg_video->m_file->getnbits(32);
					start_code = m_mpeg_video->m_file->next_start_code();

					m_mpeg_video->extension_and_user_data(1);
				}

				if (start_code == 0x100)
				{
					Picture* pic = new Picture;
					pic->m_iGroup = iGroup;
					//m_mpeg_video->m_file->m_byteStream->m_byteStream->Seek(0, System::IO::STREAM_SEEK_CUR);

					pic->m_datapos = m_mpeg_video->m_file->GetBytePos();//m_byteStream->m_bytepos;//m_mpeg_video->m_file->m_byteStream->Seek(0, System::IO::STREAM_SEEK_CUR);//countBits / 8;//m_byteStream->Seek(0, STREAM_SEEK_CUR);
				//	if (m_mpeg_video->m_file->m_bitcnt != 32)
				//		pic->m_datapos--;

				//	pic->m_bitcnt = 32-m_mpeg_video->m_file->m_bitcnt;

					pic->m_temporal_reference = m_mpeg_video->m_file->getnbits(10);

					/*
					if (pic->m_temporal_reference == 0)
					{
						m_temporal_offset = m_displayPictures.GetCount();
					}
					*/

					pic->m_index = index++;
					pic->m_temporal_reference_abs = pic->m_temporal_reference + m_temporal_offset;

					TRACE("%d abs(%d)\n", pic->m_temporal_reference, pic->m_temporal_reference_abs);

					pic->m_picture_coding_type = m_mpeg_video->m_file->getnbits(3);	// I=1, P=2, B=3
					if (pic->m_picture_coding_type != 1 && pic->m_picture_coding_type != 2 && pic->m_picture_coding_type != 3)
					{
						ASSERT(0);
						THROW(-1);
					}

					m_pictures.Add(pic);

				// Insert into display order piclist
					{
						Picture** pos = m_displayPictures.begin();//GetHeadPosition();
						while (pos != m_displayPictures.end())
						{
							Picture** _pos = pos;
							Picture* pic2 = *pos++;//m_displayPictures.GetNext(pos);
							if (pic->m_temporal_reference_abs < pic2->m_temporal_reference_abs)
							{
								m_displayPictures.InsertAt(_pos - m_displayPictures.begin(), pic);
								goto inserted;
							}
						}
						m_displayPictures.Add(pic);
				inserted:
						;
					}

					nframes++;
					m_mpeg_video->m_file->skipnbits(3);	// byte-align
					ASSERT(m_mpeg_video->m_file->is_byte_aligned());
				}
			}
		//	else
			{
		//		m_mpeg_video->m_file->skipnbits(8);
			}
		}
	}
	CATCH(int)
	{
	}

#if 0
	m_mpeg_video->m_file->m_byteStream->m_bytepos = pos;
#endif
	m_mpeg_video->m_file->SetBytePos(pos);
//	m_mpeg_video->m_file->m_bitcnt = bitcnt;
	m_mpeg_video->m_file->m_countBits = countBits;
#if 0
	m_mpeg_video->m_file->m_byteStream->m_nstacked = 0;
#endif
}

MpegVideoSequenceFormat::MpegVideoSequenceFormat()
{
	m_file = NULL;

	m_horizontal_size = 0;
	m_vertical_size = 0;
}

bool MpegVideoSequenceFormat::Open(System::IO::CByteStream* byteStream)
{
	ASSERT(m_file == NULL);
	m_file = new BitStreamEx(byteStream);

	TRY
	{
		m_file->next_start_code();
		return true;
	}
	CATCH(int)
	{
		delete m_file;
		m_file = NULL;
		return false;
	}
}

void MpegVideoSequenceFormat::sequence_header()
{
	ASSERT(m_file->m_next_code == 0x01b3);

	m_horizontal_size = m_file->getnbits(12);
	m_vertical_size = m_file->getnbits(12);
	m_aspect_ratio_information = m_file->getnbits(4);
	m_frame_rate_code = m_file->getnbits(4);

	if (m_frame_rate_code == 0)	// forbidden
		m_frame_rate_code = 1;

	m_bitrate = m_file->getnbits(18);	// bitrate

	m_file->getmarkerbit();	// marker
	m_file->getnbits(10);	// vbv_buffer_size_value
	m_file->getbit();	// constrained_parameters_flag

	m_mb_width = (m_horizontal_size + 15)/16;

	int load_intra_quantiser_matrix = m_file->getbit();
	if (load_intra_quantiser_matrix)
	{
		for (int i = 0; i < 64; i++)
		{
			m_intra_quantiser_matrix[i] = m_file->getnbits(8);
			m_chroma_intra_quantiser_matrix[i] = m_intra_quantiser_matrix[i];
		}
	}
	else
	{
		for (int i = 0; i < 64; i++)
		{
			m_intra_quantiser_matrix[i] = intra_default[i];
			m_chroma_intra_quantiser_matrix[i] = m_intra_quantiser_matrix[i];
		}
	}

	int load_non_intra_quantiser_matrix = m_file->getbit();
	if (load_non_intra_quantiser_matrix)
	{
		for (int i = 0; i < 64; i++)
		{
			m_non_intra_quantiser_matrix[i] = m_file->getnbits(8);
			m_chroma_non_intra_quantiser_matrix[i] = m_non_intra_quantiser_matrix[i];
		}
	}
	else
	{
		for (int i = 0; i < 64; i++)
		{
			m_non_intra_quantiser_matrix[i] = non_intra_default[i];
			m_chroma_non_intra_quantiser_matrix[i] = m_non_intra_quantiser_matrix[i];
		}
	}

	m_file->next_start_code();
}

ErrorCode MpegVideoSequenceFormat::sequence_extension()
{
	ASSERT(m_file->m_next_code == 0x1b5);

	/*extension_start_code_identifier*/	m_file->getnbits(4);
	m_profile_and_level_indication = m_file->getnbits(8);

	uint8 profile_identification = (m_profile_and_level_indication >> 4) & 0x7;
	uint8 level_identification = (m_profile_and_level_indication) & 0xf;

	m_progressive_sequence = m_file->getbit();
	m_chroma_format = m_file->getnbits(2);
	if (m_chroma_format == 0)	// Reserved
	{
		ASSERT(0);
		return Error;
	}
	unsigned int horizontal_size_extension = m_file->getnbits(2);
	unsigned int vertical_size_extension = m_file->getnbits(2);
	unsigned int bit_rate_extension = m_file->getnbits(12);

	m_horizontal_size |= horizontal_size_extension<<12;
	m_vertical_size |= vertical_size_extension<<12;
	m_bitrate |= bit_rate_extension<<18;

	/*marker_bit*/	m_file->getmarkerbit();
	/*vbv_buffer_size_extension*/	m_file->getnbits(8);
	/*low_delay*/ 	m_file->getbit();
	/*frame_rate_extension_n*/	m_file->getnbits(2);
	/*frame_rate_extension_d*/	m_file->getnbits(5);

	m_file->next_start_code();

	return Success;
}

void MpegVideoSequenceFormat::extension_and_user_data(int i)
{
	while ((m_file->m_next_code == 0x1b5/*extension_start_code*/) ||
			(m_file->m_next_code == 0x1b2/*user_data_start_code*/))
	{
		if (i != 1)
		{
			if (m_file->m_next_code == 0x1b5/*extension_start_code*/)
				extension_data(i);
		}

		if (m_file->m_next_code == 0x1b2/*user_data_start_code*/)
		{
			user_data();
		}
	}
}

void MpegVideoSequenceFormat::user_data()
{
	ASSERT(m_file->m_next_code == 0x1b2);

	while (m_file->getnbits(24) != 1/*'0000 0000 0000 0000 0000 0001'*/ )
	{
		m_file->ungetbits(24-8);	//	user_data 8
	}

	m_file->ungetbits(24);

	m_file->next_start_code();
}

void MpegVideoSequenceFormat::extension_data(int i)
{
	while (m_file->m_next_code == 0x1b5)
	{
		if (i == 0)	/* follows sequence_extension() */
		{
			if (m_file->getnbits(4) == 0x2/*"Sequence Display Extension ID"*/ )
			{
				ASSERT(0);
				//sequence_display_extension();
			}
			else
				m_file->ungetbits(4);

			if (m_file->getnbits(4) == 0x5/*"Sequence Scalable Extension ID"*/)
			{
				ASSERT(0);
				//sequence_scalable_extension();
			}
			else
				m_file->ungetbits(4);
		}

	/* Note: extension never follows a group_of_pictures_header() */
		if (i == 2)	/* follows picture_coding_extension() */
		{
			//....
		}
	}
}

void MpegVideoSequenceFormat::group_of_pictures_header()
{
	int time_code = m_file->getnbits(25);
	int closed_gop = m_file->getbit();
	int broken_link = m_file->getbit();

	m_file->next_start_code();
}

uint8 toR[256][256];
uint8 toB[256][256];
short CrCb[256][256];
short YTab[256];
bool bInitedTabs = false;

CVideoSequence::CVideoSequence()
{
//	m_pFilter = NULL;

	m_currentFrame = -1;

//	nbuffer = 0;
	nbuffers = 0;
	std::memset(buffers, 0, 4*1024);

	m_mpeg_video = new MpegVideoSequenceFormat;
}

void CVideoSequence::SetSampleRGBData(PictureDecoder* pPic, LSampleData* sampledata)
{
	if (!bInitedTabs)
	{
		bInitedTabs = true;

		{
			for (int i = 0; i < 256; i++)
			{
				YTab[i] = 1.164*(i - 16);
			}
		}

		{
			for (int Y = 0; Y < 256; Y++)
			{
				for (int Cr = 0; Cr < 256; Cr++)
				{
					int value = YTab[Y] + 1.596*(Cr - 128);

					if (value < 0) value = 0;
					else if (value > 255) value = 255;

					toR[Y][Cr] = value;
				}
			}
		}

		{
			for (int Y = 0; Y < 256; Y++)
			{
				for (int Cb = 0; Cb < 256; Cb++)
				{
					int value = YTab[Y] + 2.017*(Cb - 128);

					if (value < 0) value = 0;
					else if (value > 255) value = 255;

					toB[Y][Cb] = value;
				}
			}
		}

		for (int Cr = 0; Cr < 256; Cr++)
		{
			for (int Cb = 0; Cb < 256; Cb++)
			{
				CrCb[Cr][Cb] = - 0.813*(Cr - 128) - 0.392*(Cb - 128);
			}
		}
	}

//	if (m_currentFrame >= 0)
	{

	//	UPOSITION pos = m_pictures.FindIndex(m_currentFrame);
	//	PictureDecoder* pPic = (PictureDecoder*)m_pictures.GetAt(pos);

		int pixelBytes = 4;	// TODO, sometimes 3

		for (int y = 0; y < m_mpeg_video->m_vertical_size; y++)
		{
			uint8* pY = pPic->m_ybuf + m_mpeg_video->m_mb_width*16*y;

			uint8* pCr;
			uint8* pCb;

			if (m_mpeg_video->m_chroma_format == 1)
			{
				pCr = pPic->m_crbuf + m_mpeg_video->m_mb_width*8*(y/2);
				pCb = pPic->m_cbbuf + m_mpeg_video->m_mb_width*8*(y/2);
			}
			else if (m_mpeg_video->m_chroma_format == 2)
			{
				pCr = pPic->m_crbuf + m_mpeg_video->m_horizontal_size*y;
				pCb = pPic->m_cbbuf + m_mpeg_video->m_horizontal_size/2*y/2;
			}
			else if (m_mpeg_video->m_chroma_format == 3)
			{
				pCr = pPic->m_crbuf + m_mpeg_video->m_horizontal_size*y;
				pCb = pPic->m_cbbuf + m_mpeg_video->m_horizontal_size*y;
			}

			uint8* out = sampledata->idata + sampledata->rowbytes*y;

			for (int x = 0; x < m_mpeg_video->m_horizontal_size; x++)
			{
				if (false)
				{
					uint8 Y = *pY;

					uint8 R_ = Y;
					uint8 G_ = Y;
					uint8 B_ = Y;

					/*
					if (R_ < 0) R_ = 0;
					else if (R_ > 255) R_ = 255;

					if (G_ < 0) G_ = 0;
					else if (G_ > 255) G_ = 255;

					if (B_ < 0) B_ = 0;
					else if (B_ > 255) B_ = 255;
					*/

					out[0] = R_;
					out[1] = G_;
					out[2] = B_;
				}
				else
				{
					uint8 Y = *pY;
					int Cr = *pCr;
					uint8 Cb = *pCb;

					uint8 R_ = toR[Y][Cr];//YTab[Y] + 1.596*(Cr - 128);
					int G_ = YTab[Y] + CrCb[Cr][Cb];//- 0.813*(Cr - 128) - 0.392*(Cb - 128);
					uint8 B_ = toB[Y][Cb];//int B_ = YTab[Y] + 2.017*(Cb - 128);

					/*
					if (R_ < 0) R_ = 0;
					else if (R_ > 255) R_ = 255;
					*/

					if (G_ < 0) G_ = 0;
					else if (G_ > 255) G_ = 255;

					/*
					if (B_ < 0) B_ = 0;
					else if (B_ > 255) B_ = 255;
					*/

					out[0] = R_;
					out[1] = G_;
					out[2] = B_;
				}

				out += pixelBytes;
				pY++;

				if (m_mpeg_video->m_chroma_format == 1)
				{
					if (x & 1)
					{
						pCr++;
						pCb++;
					}
				}
				else if (m_mpeg_video->m_chroma_format == 2)
				{
					pCr++;

					if (x & 1)
					{
						pCb++;
					}
				}
				else
				{
					pCr++;
					pCb++;
				}
			}
		}
	}
}

//PictureDecoder* g_pPictureDecoder;

void CVideoSequence::SeekFrame(long frame)
{
#if 0
	bool bGroup;

	if (m_currentFrame >= 0)
	{
		UPOSITION pos = m_displayPictures.FindIndex(frame);
		Picture* pic = (Picture*)m_displayPictures.GetAt(pos);
		int group1 = pic->m_iGroup;

		UPOSITION pos2 = m_displayPictures.FindIndex(m_currentFrame);
		Picture* pic2 = (Picture*)m_displayPictures.GetAt(pos2);
		int group2 = pic2->m_iGroup;

		bGroup = group1 != group2;
	}
	else
		bGroup = true;

	/*
	if (frame < m_currentFrame)
	{
		UPOSITION pos = m_displayPictures.FindIndex(frame);

		for (int i = frame; i <= m_currentFrame; i++)
		{
			Picture* pic = (Picture*)m_displayPictures.GetNext(pos);
			if (pic->m_bGroup)
			{
				bGroup = true;
				break;
			}
		}
	}
	else
	{
		UPOSITION pos = m_displayPictures.FindIndex(frame);
		Picture* pic = (Picture*)m_displayPictures.GetAt(pos);

		pos = m_pictures.Find(pic);

		for (int i = frame; i > m_currentFrame; i--)
		{
			Picture* pic = (Picture*)m_pictures.GetPrev(pos);
			if (pic->m_bGroup)
			{
				bGroup = true;
				break;
			}
		}
	}
	*/

	if (bGroup)
	{
		//MessageBeep(-1);
		nbuffer = 0;
		{
			UPOSITION pos = m_mpeg_video->m_groupPictures.GetHeadPosition();
			while (pos)
			{
				PictureDecoder* pPictureDecoder = (PictureDecoder*)m_mpeg_video->m_groupPictures.GetNext(pos);
				pPictureDecoder->m_pic->m_decoder = NULL;
				delete pPictureDecoder;
			}
			m_mpeg_video->m_groupPictures.RemoveAll();
		}
	}
#endif

	list<Picture*> piclist;

	// Figure out which pictures that must be decoded to get at the target frame
	Picture* pPicture = m_displayPictures[frame];

	if (pPicture->m_temporal_reference_abs != frame)
	{
		TRACE("%s(%d): pPicture->m_temporal_reference_abs(%d) != frame(%d)\n", __FILE__, __LINE__, pPicture->m_temporal_reference_abs, frame);
	}

	if (pPicture->m_picture_coding_type == PictureType_I)
	{
		pPicture->m_keepAliveCount = 2;
		piclist.push_back(pPicture);	// This is all we need
	}
	else if (pPicture->m_picture_coding_type == PictureType_P)
	{
		// Find the last previous I- or decoded P frame (we include this picture in the search)

		Picture** pos = find(m_pictures.begin(), m_pictures.end(), pPicture);

		while (1)
		{
			Picture* pPicture = *pos--;
			if (pPicture->m_picture_coding_type == PictureType_I)
			{
				pPicture->m_keepAliveCount = 2;
				piclist.push_front(pPicture);
				break;
			}

			if (pPicture->m_picture_coding_type == PictureType_P)
			{
				pPicture->m_keepAliveCount = 2;
				piclist.push_front(pPicture);
				if (pPicture->m_decoder)	// Already decoded, we can start from here
				{
					break;
				}
			}
		}
	}
	else if (pPicture->m_picture_coding_type == PictureType_B)
	{
		pPicture->m_keepAliveCount = 1;
		piclist.push_front(pPicture);

		// Find the last two previous I- or decoded P-frames in encoding order  (we include this picture in the search)
		Picture** pos = find(m_pictures.begin(), m_pictures.end(), pPicture);

		while (1)//pos != m_pictures.rend())
		{
			Picture* pPicture = *pos--;
			if (pPicture->m_picture_coding_type == PictureType_I)
			{
				pPicture->m_keepAliveCount = 2;
				piclist.push_front(pPicture);
				break;
			}

			if (pPicture->m_picture_coding_type == PictureType_P)
			{
				pPicture->m_keepAliveCount = 2;
				piclist.push_front(pPicture);
				if (pPicture->m_decoder)	// Already decoded, we can start from here
				{
					break;
				}
			}

			if (pos == m_pictures.begin()-1)
				break;
		}

	//	if (piclist.GetCount() < 2)
		if (pos != m_pictures.begin()-1)
		{
			while (1)
			{
				Picture* pPicture = *pos--;
				if (pPicture->m_picture_coding_type == PictureType_I)
				{
					// Why am I not setting keepAliveCount = 3 ???

					pPicture->m_keepAliveCount = 2;
					piclist.push_front(pPicture);
					break;
				}

				if (pPicture->m_picture_coding_type == PictureType_P)
				{
					// Why am I not setting keepAliveCount = 2 ???

					// Not setting keepAliveCount = 3, because
					// B-frames aren't referenced by other frames

					pPicture->m_keepAliveCount = 2;
					piclist.push_front(pPicture);
					if (pPicture->m_decoder)	// Already decoded, we can start from here
					{
						break;
					}
				}

				if (pos == m_pictures.begin()-1)
					break;
			}
		}
	}
	else
		ASSERT(0);

	// Now remove all cached pictures that are not in the piclist we just built
	{
		list<PictureDecoder*>::iterator pos = m_mpeg_video->m_groupPictures.begin();//GetHeadPosition();
		while (pos != m_mpeg_video->m_groupPictures.end())
		{
			list<PictureDecoder*>::iterator/*UPOSITION*/ pos2 = pos;
			PictureDecoder* pPictureDecoder = *pos;//(PictureDecoder*)m_mpeg_video->m_groupPictures.GetNext(pos);
			++pos;

			VERIFY(pPictureDecoder->m_pic->m_keepAliveCount >= 0);

			/*
			if (pPictureDecoder->m_pic->m_temporal_reference_abs < pPicture2->m_temporal_reference_abs)
			*/
		//	if (piclist.find(pPictureDecoder->m_pic) == piclist.end())
		//	if (pPictureDecoder->m_pic->m_keepAliveCount > 0)
			{

			//	if (pPictureDecoder->m_pic->m_keepAliveCount > 0)
				{
					--pPictureDecoder->m_pic->m_keepAliveCount;

					//ASSERT(pPictureDecoder->m_pic->m_keepAliveCount >= 0);

					if (pPictureDecoder->m_pic->m_keepAliveCount == -1)
					{
					//	m_mpeg_video->m_groupPictures.RemoveAt(pos2);
						m_mpeg_video->m_groupPictures.erase(pos2);
						pPictureDecoder->m_buffer->m_bInUse = false;
						pPictureDecoder->m_pic->m_decoder = NULL;
						delete pPictureDecoder;
					}
				}
			}
		}
	//	m_mpeg_video->m_groupPictures.RemoveAll();
	}

	//TRACE("%d, %d\n", m_mpeg_video->m_groupPictures.GetCount(), piclist.GetCount());

	/*
	{
		piclist.RemoveAll();
		int n = 0;
		for (int i = 0; i < m_displayPictures.size(); i++)
		{
			if (m_displayPictures[i]->m_picture_coding_type == 1)
			{
				if (n == 4)
				{
					piclist.AddTail(m_displayPictures[i]);
					break;
				}
				n++;
			}
		}
	}
	*/

	PictureDecoder* pPictureDecoder;

//	m_groupPictures.RemoveAll();

	{
		list<Picture*>::iterator pos = piclist.begin();//GetHeadPosition();
		while (pos != piclist.end())
		{
			pPicture = *pos;//piclist.GetNext(pos);
			++pos;

			if (pPicture->m_decoder == NULL)
			{
		// Seek to datapart of picture
				m_mpeg_video->m_file->SetBytePos(pPicture->m_datapos);//, System::IO::STREAM_SEEK_SET);
			//	m_mpeg_video->m_file->m_bitcnt = 0;
			//	m_mpeg_video->m_file->getnbits(pPicture->m_bitcnt);

				int temporal_reference = m_mpeg_video->m_file->getnbits(10);
				int picture_type = m_mpeg_video->m_file->getnbits(3);

				ASSERT(pPicture->m_temporal_reference == temporal_reference);
				ASSERT(pPicture->m_picture_coding_type == picture_type);

				pPictureDecoder = new PictureDecoder(m_mpeg_video, m_mpeg_video->m_file);
				pPictureDecoder->m_pic = pPicture;

			// Insert sorted
				{
					list<PictureDecoder*, System::__gc_allocator>::iterator pos = m_mpeg_video->m_groupPictures.begin();//GetHeadPosition();
					while (pos != m_mpeg_video->m_groupPictures.end())
					{
						list<PictureDecoder*, System::__gc_allocator>::iterator _pos = pos;
						PictureDecoder* pPic = *pos;//(PictureDecoder*)m_mpeg_video->m_groupPictures.GetNext(pos);
						++pos;

						if (pPictureDecoder->m_pic->m_index < pPic->m_pic->m_index)
						{
						//	piclist.InsertBefore(_pos, pPicture);

#if 0
							pPictureDecoder->m_pos = m_mpeg_video->m_groupPictures.InsertBefore(_pos, pPictureDecoder);
#endif
							pPictureDecoder->m_pos = m_mpeg_video->m_groupPictures.insert(_pos, pPictureDecoder);
							goto inserted2;
						}
					}
				//	piclist.AddTail(pPicture);
				VERIFY(pPictureDecoder->m_pic->m_keepAliveCount > 0);
				pPictureDecoder->m_pos = m_mpeg_video->m_groupPictures.insert(m_mpeg_video->m_groupPictures.end(), pPictureDecoder);
			inserted2:
					;
				}

				{
					int nbuffer;

					for (nbuffer = 0; nbuffer < 512; nbuffer++)
					{
						if (buffers[nbuffer] == NULL)
						{
							int mb_rows = (m_mpeg_video->m_vertical_size + 15)/16;

							buffers[nbuffer] = new ImageBuffer;
							buffers[nbuffer]->m_buf[0] = (uint8*)calloc(1, (m_mpeg_video->m_mb_width*16+8)*(mb_rows*16+8));
							buffers[nbuffer]->m_buf[1] = (uint8*)calloc(1, (m_mpeg_video->m_mb_width*8+8)*(mb_rows*8+8));
							buffers[nbuffer]->m_buf[2] = (uint8*)calloc(1, (m_mpeg_video->m_mb_width*8+8)*(mb_rows*8+8));
							nbuffers = MAX(nbuffer, nbuffers);
						}

						if (!buffers[nbuffer]->m_bInUse)
						{
							break;
						}
					}

					VERIFY(nbuffer < 512);
					buffers[nbuffer]->m_bInUse = true;
					pPictureDecoder->m_buffer = buffers[nbuffer];
					pPictureDecoder->m_ybuf = buffers[nbuffer]->m_buf[0];
					pPictureDecoder->m_crbuf = buffers[nbuffer]->m_buf[1];
					pPictureDecoder->m_cbbuf = buffers[nbuffer]->m_buf[2];
				}

//				g_pPictureDecoder = pPictureDecoder;

				TRY
				{
					pPictureDecoder->picture_header();

					if (!m_mpeg_video->m_mpeg1)
					{
						pPictureDecoder->picture_coding_extension();
						pPictureDecoder->extension_and_user_data(2);
					}

					pPictureDecoder->picture_data();

				}
				CATCH(int)
				{
					TRACE("error\n");
				}

				pPicture->m_decoder = pPictureDecoder;
			}
			else
				pPictureDecoder = pPicture->m_decoder;
		}
	}

//	ShowFrame(pPictureDecoder);

	m_currentFrame = frame;
}

}	// MediaShow
}	// System
