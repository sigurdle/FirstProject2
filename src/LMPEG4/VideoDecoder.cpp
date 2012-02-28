// VideoDecoder.cpp : Implementation of CVideoDecoder
#include "stdafx.h"
#include "LMPEG4.h"
#include "VideoDecoder.h"

//#include "MP4File.h"
//#include "MP4Track.h"

namespace System
{
namespace MediaShow
{

CVideoDecoder::CVideoDecoder()
{
	m_pTrack = NULL;

	m_pInputPin = NULL;

	m_threadId = 0;
	m_hThread = NULL;

	m_pInputPin = new CInputPin;
	m_pInputPin->m_pFilter = this;
	m_pInputPin->m_id = WSTR("Stream Input");	// ??
	AddPin(m_pInputPin);

	m_pVideo = new CVideoSequence;
	m_pVideo->m_pFilter = this;
	m_pVideo->m_id = WSTR("Video Output");
	AddPin(m_pVideo);

	m_currentFrame = -1;
	m_currentTime = 0;
	m_pCurrentVOP = NULL;
}

void CVideoDecoder::SeekFrame(ULONG frame)
{
	ULONG total = m_pTrack->m_samples.GetSize();
	if (frame > total-1) frame = total-1;

	TRACE("%d - ", frame);

	ULONG from;

	if (frame >= m_currentFrame)
	{
		for (from = frame; from > m_currentFrame; from--)
		{
			if (m_pTrack->m_sampleflags[from])
			{
				if (m_pCurrentVOP)
				{
					delete m_pCurrentVOP;
					m_pCurrentVOP = NULL;
				}
				break;
			}
		}
	}
	else
	{
		if (m_pCurrentVOP)
		{
			delete m_pCurrentVOP;
			m_pCurrentVOP = NULL;
		}

		for (from = frame; from > 0; from--)
		{
			if (m_pTrack->m_sampleflags[from])
				break;
		}
	}

	for (ULONG i = from; i <= frame; i++)
	{
		if (i == m_currentFrame)
			continue;

		IMediaSample* sample;
		m_pVideo->m_pAllocator->GetBuffer(0, &sample);

		m_decoder->m_stream.Seek(m_pTrack->m_samples[i].m_fileOffset, IO::STREAM_SEEK_SET);

	//	TRACE("{\nsamplesize: %d .. ", p->m_pTrack->m_samples[i].m_fileSize);

		LONGLONG duration = TIME_SCALE * m_pTrack->m_samples[i].m_duration / m_pTrack->m_pMovie->m_movieHeader.m_timeScale;

		/*
		LONGLONG timeStart = t;
		LONGLONG timeEnd = t+duration;
		t += duration;
		*/

		IO::CBitStream32 bitstream(new IO::CByteStream(m_decoder->m_stream));
		IO::CBitStream32* pBitStream = &bitstream;

		//m_pBitStream = &bitstream;
		//m_sampleSize = ;

		bitstream.m_bitstreamSize = m_pTrack->m_samples[i].m_fileSize*8;

		try
		{
			int start_code = Mpeg4::next_start_code(pBitStream);
			if (start_code >= 0x100 && start_code <= 0x11F)	// //	video_object_start_code 32 bslbf
			{
				start_code = Mpeg4::next_start_code(pBitStream);
				start_code = m_decoder->m_config->VideoObjectLayer(pBitStream, start_code);

				start_code = Mpeg4::next_start_code(pBitStream);

				while (start_code == 0x1b2/* next_bits()== user_data_start_code*/)
				{
					start_code = Mpeg4::user_data(pBitStream, start_code);
				}

			}
			//	TRACE("left: %d\n", ((pBitStream->m_bitstreamSize+7)/8) - ((pBitStream->m_countBits+7)/8));

			if (start_code == 0x1b6)	// vop_start_code (Video Object Plane)
			{
			//	CVideoObjectPlane* vop = p->m_decoder->ReadFrame(pBitStream);
				Mpeg4::VideoObjectPlane* vop = new Mpeg4::VideoObjectPlane;
				vop->m_pPrevVOP = m_pCurrentVOP;
				vop->m_config = m_decoder->m_config;
				vop->m_mb_cols = (m_decoder->m_config->m_video_object_layer_width+15)/16;
				vop->m_mb_rows = (m_decoder->m_config->m_video_object_layer_height+15)/16;
				vop->m_macroblocks = new Mpeg4::MacroBlock[vop->m_mb_cols*vop->m_mb_rows];
				vop->m_ybuf = (uint8*)calloc(1, (vop->m_mb_rows*16)*(vop->m_mb_cols*16));
				vop->m_crbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
				vop->m_cbbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
				vop->mb_address = 0;

				if (vop->m_pPrevVOP)
				{
					std::memcpy(vop->m_ybuf, vop->m_pPrevVOP->m_ybuf, vop->m_mb_cols*vop->m_mb_rows*16*16);
					std::memcpy(vop->m_crbuf, vop->m_pPrevVOP->m_crbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
					std::memcpy(vop->m_cbbuf, vop->m_pPrevVOP->m_cbbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
				}

				vop->ReadVideoObjectPlane(pBitStream);

				m_pVideo->SetSampleRGBData(sample, vop);

				if (m_pCurrentVOP)
				{
					delete m_pCurrentVOP;
				}
				m_pCurrentVOP = vop;

				LONGLONG timeStart = 0;
				LONGLONG timeEnd = 0;
				sample->SetTime(&timeStart, &timeEnd);

				ErrorCode hr = m_pVideo->m_pInputPin->Receive(sample);
			//	if (hr != S_OK)	// Stop if FAILED or S_FALSE
			//		break;
				sample->Release();
			}
			else
				ASSERT(0);

			if (((pBitStream->m_countBits+7)/8) < ((pBitStream->m_bitstreamSize+7)/8))
			{
				TRACE("eof not reached\n");
			}

		}
		catch(int)
		{
			ASSERT(0);
		}
	}
#if 0
	System::IO::CBitStream bitstream(p->m_decoder->m_stream);
	System::IO::CBitStream32* pBitStream = &bitstream;

	//m_pBitStream = &bitstream;
	//m_sampleSize = ;

	bitstream.m_bitstreamSize = p->m_pTrack->m_samples[i].m_fileSize*8;
#endif

	m_currentFrame = frame;
}

CVideoDecoder::CVideoSequence::CVideoSequence()
{
//	m_pMediaType = NULL;

	/*
	m_file = NULL;

	m_horizontal_size = 0;
	m_vertical_size = 0;
	m_currentFrame = -1;
	*/
}

ErrorCode CVideoDecoder::CVideoSequence::CheckMediaType(MediaType* mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Video)
		return Error;

	return Success;
}

ErrorCode CVideoDecoder::CVideoSequence::GetMediaType(int iPosition, MediaType** pMediaType)
{
	if (iPosition == 0)
	{
		//mediaType.Create(sizeof(LVIDEOINFOHEADER2));

		VideoInfoHeader* vih = new VideoInfoHeader;//((LVIDEOINFOHEADER2*)mediaType.pbFormat);

		//memset(&vih->vih.bmiHeader, 0, sizeof(BitmapInfoHeader));
		vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
		vih->vih->bmiHeader.biPlanes = 1;
		vih->vih->bmiHeader.biBitCount = 24;//m_pFilter->m_pInputPin->m_bitcount;
		vih->vih->bmiHeader.biWidth = GetFilter()->m_decoder->m_config->m_video_object_layer_width;
		vih->vih->bmiHeader.biHeight = GetFilter()->m_decoder->m_config->m_video_object_layer_height;
		//memcpy(((BITMAPINFO*)&vih->bmiHeader)->bmiColors, m_pFilter->m_pInputPin->m_colors, m_pFilter->m_pInputPin->m_numColors*sizeof(RGBQUAD));

		/*
		RGBQUAD* colors = ((BITMAPINFO*)&vih->bmiHeader)->bmiColors;

		for (int i = 0; i < m_numcolors; i++)
		{
			colors[i].rgbRed = m_colors[i].Red;
			colors[i].rgbGreen = m_colors[i].Green;
			colors[i].rgbBlue = m_colors[i].Blue;
		}
		*/

		MediaType* mediaType = new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
	//	mediaType.SetFormat(vih);
		//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

		*pMediaType = mediaType;

		return Success_True;
	}
	else
	{
		*pMediaType = NULL;
		return Success_False;
	}
}

ErrorCode CVideoDecoder::CVideoSequence::Seek(TimeUnit unit, LONGLONG t)
{
	if (unit == TimeFormat_ref)
	{
		LONGLONG t2 = 0;

		int i;
		for (i = 0; i < GetFilter()->m_pTrack->m_samples.GetSize(); i++)
		{
			LONGLONG duration = TIME_SCALE * GetFilter()->m_pTrack->m_samples[i].m_duration / GetFilter()->m_pTrack->m_pMovie->m_movieHeader.m_timeScale;

			if (t <= t2+duration)
				break;

			t2 += duration;
		}

		GetFilter()->m_currentTime = t2;
		GetFilter()->SeekFrame(i);
	}
	else if (unit == TimeFormat_frame)
	{
		if (t < 0) t = 0;
		else if (t > GetFilter()->m_pTrack->m_samples.GetSize()-1) t = GetFilter()->m_pTrack->m_samples.GetSize()-1;

		LONGLONG t2 = 0;
		for (ULONG i = 0; i < t; i++)
		{
			LONGLONG duration = TIME_SCALE * GetFilter()->m_pTrack->m_samples[i].m_duration / GetFilter()->m_pTrack->m_pMovie->m_movieHeader.m_timeScale;

			t2 += duration;
		}

		GetFilter()->m_currentTime = t2;
		GetFilter()->SeekFrame(t);
	}
	else
		return Error;

	return Success;
}

ErrorCode CVideoDecoder::CVideoSequence::GetDuration(TimeUnit unit, LONGLONG* pVal)
{
	if (unit == TimeFormat_ref)
	{
		*pVal = TIME_SCALE * GetFilter()->m_pTrack->m_mediaHeader.m_duration / GetFilter()->m_pTrack->m_mediaHeader.m_timeScale;
	}
	else if (unit == TimeFormat_frame)
	{
		*pVal = GetFilter()->m_pTrack->m_samples.GetSize();
	}
	else
		return Error;

	return Success;
}

ErrorCode CVideoDecoder::CVideoSequence::GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
{
	if (unit == TimeFormat_ref)
	{
		*pVal = GetFilter()->m_currentTime;
	}
	else if (unit == TimeFormat_frame)
	{
		*pVal = GetFilter()->m_currentFrame;
	}
	else
		return Error;

	return Success;
}

void CVideoDecoder::CVideoSequence::SetSampleRGBData(IMediaSample* sample, Mpeg4::VideoObjectPlane* vob)
{
//	if (m_currentFrame >= 0)
	{
		LSampleData sampledata;
		sample->LockBits(&sampledata);

	//	UPOSITION pos = m_pictures.FindIndex(m_currentFrame);
	//	CPicture* pPic = (CPicture*)m_pictures.GetAt(pos);

		int horizontal_size = GetFilter()->m_decoder->m_config->m_video_object_layer_width;
		int vertical_size = GetFilter()->m_decoder->m_config->m_video_object_layer_height;

		for (int y = 0; y < vertical_size; y++)
		{
			uint8* pY = (uint8*)vob->m_ybuf + vob->m_mb_cols*16*y;

			uint8* pCr;
			uint8* pCb;

			if (GetFilter()->m_decoder->m_config->m_chroma_format == 1)
			{
				pCr = vob->m_crbuf + vob->m_mb_cols*8*(y>>1);
				pCb = vob->m_cbbuf + vob->m_mb_cols*8*(y>>1);
			}
			else if (GetFilter()->m_decoder->m_config->m_chroma_format == 2)
			{
				//pCr = pPic->m_crbuf + horizontal_size*y;
				//pCb = pPic->m_cbbuf + horizontal_size/2*y/2;
			}
			else if (GetFilter()->m_decoder->m_config->m_chroma_format == 3)
			{
				//pCr = pPic->m_crbuf + horizontal_size*y;
				//pCb = pPic->m_cbbuf + horizontal_size*y;
			}

			uint8* out = sampledata.idata + sampledata.rowbytes*y;

			for (int x = 0; x < horizontal_size; x++)
			{
				int Y = *pY;

				if (false && ((x % 16)==0 || (y % 16)==0))
				{
						out[0] = 0;
						out[1] = 0;
						out[2] = 255;
				}
				else
				{
					if (true)
					{
						int R_ = Y;
						int G_ = Y;
						int B_ = Y;

						if (R_ < 0) R_ = 0;
						else if (R_ > 255) R_ = 255;

						if (G_ < 0) G_ = 0;
						else if (G_ > 255) G_ = 255;

						if (B_ < 0) B_ = 0;
						else if (B_ > 255) B_ = 255;

						out[0] = R_;
						out[1] = G_;
						out[2] = B_;
					}
					else
					{
						int Cr = *pCr;
						int Cb = *pCb;

						/*
	static short Cr_tab[256],Cb_tab[256]; // Precalculated Cr, Cb tables
	static short Cr_Cb_green_tab[65536];

	void precalculate_Cr_Cb_tables()
	{
	 WORD k;
	 WORD Cr_v,Cb_v;
	 for (k=0;k<=255;k++) Cr_tab[k]=(short)((k-128.0)*1.402);
	 for (k=0;k<=255;k++) Cb_tab[k]=(short)((k-128.0)*1.772);

	 for (Cr_v=0;Cr_v<=255;Cr_v++)
	  for (Cb_v=0;Cb_v<=255;Cb_v++)
		Cr_Cb_green_tab[((WORD)(Cr_v)<<8)+Cb_v]=(int)(-0.34414*(Cb_v-128.0)-0.71414*(Cr_v-128.0));

	}

						*/
						int R_ = 1.164*(Y - 16) + 1.596*(Cr - 128);
						int G_ = 1.164*(Y - 16) - 0.813*(Cr - 128) - 0.392*(Cb - 128);
						int B_ = 1.164*(Y - 16) + 2.017*(Cb - 128);

						/*
						int R_ = (Y) + 1.402*(Cr-128.0);
						int G_ = (Y) - 0.71414*(Cr-128.0) - 0.34414*(Cb-128.0);
						int B_ = (Y) + 1.772*(Cb-128.0);
						*/

						if (R_ < 0) R_ = 0;
						else if (R_ > 255) R_ = 255;

						if (G_ < 0) G_ = 0;
						else if (G_ > 255) G_ = 255;

						if (B_ < 0) B_ = 0;
						else if (B_ > 255) B_ = 255;

						out[0] = R_;
						out[1] = G_;
						out[2] = B_;
					}
				}

				out += sampledata.bitcount>>3;
				pY++;

				if (GetFilter()->m_decoder->m_config->m_chroma_format == 1)
				{
					if (x & 1)
					{
						pCr++;
						pCb++;
					}
				}
				else if (GetFilter()->m_decoder->m_config->m_chroma_format == 2)
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

		sample->UnlockBits();
	}
}

#if 0
ErrorCode CVideoDecoder::Read()
{
	System::IO::CBitStream32 bitstream(m_stream);
	System::IO::CBitStream32* pBitStream = &bitstream;

	try
	{
		m_start_code = next_start_code(pBitStream);
		if (m_start_code >= 0x100 && m_start_code <= 0x11F)
		{
			m_start_code = next_start_code(pBitStream);
			if (m_start_code >= 0x120 && m_start_code <= 0x12F)
			{
				m_config = new CMP4VConfig;

				// TODO
				/*m_start_code =*/ m_config->VideoObjectLayer(pBitStream, m_start_code);

				m_start_code = next_start_code(pBitStream);
			}
			else
			{
				TRACE("Expected video_object_layer_start_code");
				throw E_FAIL;
			}

			////// ready for vop or vop_group
		}
	}
	catch (ErrorCode hr)
	{
		TRACE("\n");
		return hr;
	}

	return S_OK;
}

#endif

static DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
//	CoInitialize(NULL);

	ErrorCode hr;

//	EnterCriticalSection(&pFilter->m_pLock);

	CVideoDecoder* p = (CVideoDecoder*)lpParameter;

	/*
	ULARGE_INTEGER curpos;
	LARGE_INTEGER li;
	li.QuadPart = 0;
	m_stream->Seek(li, STREAM_SEEK_CUR, &curpos);
	*/

//	CComQIPtr<ILMemInputPin> memInput = p->m_pVideo->m_connectedTo;
//	if (memInput)
	{
		ErrorCode hr = Success;

		if (p->m_pTrack)
		{
		//	int count = min(2, m_pTrack->m_chunks.GetSize());
			int count = p->m_pTrack->m_samples.GetSize();

			LONGLONG t = 0;

			Mpeg4::VideoObjectPlane* pPrevVOP;
			/*p->m_decoder->*/ pPrevVOP = NULL;

		//	for (int i = 0; i < 8; i++)
			for (int i = 0; i < count; i++)
			{
			//	TRACE("%d - ", i);
			//	if (i == 64)
			//	Sleep(1500);//MessageBeep(-1);

				p->m_currentFrame = i;
				p->m_currentTime = t;

				IMediaSample* sample;
				p->m_pVideo->m_pAllocator->GetBuffer(0, &sample);

				p->m_decoder->m_stream.Seek(p->m_pTrack->m_samples[i].m_fileOffset, IO::STREAM_SEEK_SET);

			//	TRACE("{\nsamplesize: %d .. ", p->m_pTrack->m_samples[i].m_fileSize);

				LONGLONG duration = TIME_SCALE * p->m_pTrack->m_samples[i].m_duration / p->m_pTrack->m_pMovie->m_movieHeader.m_timeScale;

				LONGLONG timeStart = t;
				LONGLONG timeEnd = t+duration;
				t += duration;

				IO::CBitStream32 bitstream(new IO::CByteStream(p->m_decoder->m_stream));
				IO::CBitStream32* pBitStream = &bitstream;

				//m_pBitStream = &bitstream;
				//m_sampleSize = ;

				bitstream.m_bitstreamSize = p->m_pTrack->m_samples[i].m_fileSize*8;

				try
				{
					int start_code = Mpeg4::next_start_code(pBitStream);
					if (start_code >= 0x100 && start_code <= 0x11F)	// //	video_object_start_code 32 bslbf
					{
						start_code = Mpeg4::next_start_code(pBitStream);
						start_code = p->m_decoder->m_config->VideoObjectLayer(pBitStream, start_code);

						start_code = Mpeg4::next_start_code(pBitStream);

						while (start_code == 0x1b2/* next_bits()== user_data_start_code*/)
						{
							start_code = Mpeg4::user_data(pBitStream, start_code);
						}

					}
					//	TRACE("left: %d\n", ((pBitStream->m_bitstreamSize+7)/8) - ((pBitStream->m_countBits+7)/8));

					if (start_code == 0x1b6)	// vop_start_code (Video Object Plane)
					{
					//	CVideoObjectPlane* vop = p->m_decoder->ReadFrame(pBitStream);
						Mpeg4::VideoObjectPlane* vop = new Mpeg4::VideoObjectPlane;
						vop->m_pPrevVOP = pPrevVOP;
						vop->m_config = p->m_decoder->m_config;
						vop->m_mb_cols = (p->m_decoder->m_config->m_video_object_layer_width+15)/16;
						vop->m_mb_rows = (p->m_decoder->m_config->m_video_object_layer_height+15)/16;
						vop->m_macroblocks = new Mpeg4::MacroBlock[vop->m_mb_cols*vop->m_mb_rows];
						vop->m_ybuf = (uint8*)calloc(1, (vop->m_mb_rows*16)*(vop->m_mb_cols*16));
						vop->m_crbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
						vop->m_cbbuf = (uint8*)calloc(1, (vop->m_mb_rows*8)*(vop->m_mb_cols*8));
						vop->mb_address = 0;

						if (vop->m_pPrevVOP)
						{
							std::memcpy(vop->m_ybuf, vop->m_pPrevVOP->m_ybuf, vop->m_mb_cols*vop->m_mb_rows*16*16);
							std::memcpy(vop->m_crbuf, vop->m_pPrevVOP->m_crbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
							std::memcpy(vop->m_cbbuf, vop->m_pPrevVOP->m_cbbuf, vop->m_mb_cols*vop->m_mb_rows*8*8);
						}

						if (i == 461)
						{
							TRACE("");
						}

						vop->ReadVideoObjectPlane(pBitStream);

						p->m_pVideo->SetSampleRGBData(sample, vop);

						if (pPrevVOP)
						{
							delete pPrevVOP;
						}
						pPrevVOP = vop;

						sample->SetTime(&timeStart, &timeEnd);

						hr = p->m_pVideo->m_pInputPin->Receive(sample);
					//	if (hr != S_OK)	// Stop if FAILED or S_FALSE
					//		break;

						sample->Release();
					}
					else
						ASSERT(0);

					if (((pBitStream->m_countBits+7)/8) < ((pBitStream->m_bitstreamSize+7)/8))
					{
						TRACE("eof not reached\n");
					}

				}
				catch(int)
				{
					ASSERT(0);
				}
			}

			if (pPrevVOP)
			{
				delete pPrevVOP;
			}
		}
		else
		{
			ASSERT(0);
		}

	//	li.QuadPart = curpos.QuadPart;
	//	m_stream->Seek(li, STREAM_SEEK_SET, NULL);

		if (hr >= 0)	// Don't send this if the downstream filter failed in Receive?
			p->m_pVideo->ConnectedTo()->EndOfStream();
	}

//	CoUninitialize();

	return 0;
}

ErrorCode CVideoDecoder::Run(LONGLONG tStart)
{

	m_criticalSection.Lock();

	m_state = State_Running;
	m_tStart = tStart;

	m_criticalSection.Unlock();

	ASSERT(0);
#if 0
	m_hThread = CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(CVideoDecoder*)this, 0, &m_threadId);
#endif
	return Success;
}

}	// Media
}
