#include "stdafx.h"
#include "LMPEGVideo.h"
#include "MPEGVideoDecoder.h"

#include "VideoSequence.h"
#include "Picture.h"

namespace System
{
namespace MediaShow
{

MPEGVideoDecoder::MPEGVideoDecoder()
{
	m_pInputPin = NULL;
	m_pVideo = NULL;

	m_pInputPin = new InputPin;
	m_pInputPin->m_id = WSTR("Stream Input");
	m_pInputPin->m_pFilter = this;
	AddPin(m_pInputPin);

	m_pVideo = new OutputPin;
	m_pVideo->m_id = WSTR("Video Output");
	m_pVideo->m_pFilter = this;
	AddPin(m_pVideo);
}

MPEGVideoDecoder::InputPin::InputPin() : BasePinImpl(PINDIR_INPUT)
{
}

ErrorCode MPEGVideoDecoder::InputPin::CheckConnect(IPin* pPin)
{
	// Call base class first
	ErrorCode hr = BasePinImpl::CheckConnect(pPin);
	if (hr < 0) return hr;

	IByteData* stream = dynamic_cast<IByteData*>(pPin);
	if (stream == NULL) return Error_NoInterface;

	GetFilter()->m_stream = new IO::CByteStream(Stream(new ByteStreamWrapper(stream)));

	return Success;
}

void MPEGVideoDecoder::InputPin::BreakConnect()
{
	// Release what we obtained in CheckConnect
	GetFilter()->m_stream = NULL;
}

ErrorCode MPEGVideoDecoder::InputPin::CheckMediaType(MediaType* mt)
{
//	if (mt->GetMajorType() != LMEDIATYPE_Stream)
//		return Error;

	ASSERT(0);

	return Success;
}

ErrorCode MPEGVideoDecoder::InputPin::CompleteConnect(IPin* pPin)
{
	// Must call base class
	ErrorCode hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

	if (!GetFilter()->m_pVideo->m_p->m_mpeg_video->Open(GetFilter()->m_stream))
		return Error;

	GetFilter()->m_pVideo->m_p->m_mpeg_video->video_sequence();
	GetFilter()->m_pVideo->m_p->Scan();

	return Success;
}

static DWORD WINAPI RunningThreadProc(void* lpParameter)
{
	ErrorCode hr;

	MPEGVideoDecoder* p = (MPEGVideoDecoder*)lpParameter;

	p->m_pVideo->video_sequence_frames();

	p->m_pVideo->ConnectedTo()->EndOfStream();

	return 0;
}

extern double tab_frame_rate_value[];

ErrorCode MPEGVideoDecoder::OutputPin::CheckMediaType(MediaType* mt)
{
	ASSERT(0);
//	if (mt->GetMajorType() != LMEDIATYPE_Video)
//		return Error;

	VideoInfoHeader* vih = static_cast<VideoInfoHeader*>(mt->GetFormat());

	if (vih->vih->bmiHeader.biBitCount != 24 &&
		vih->vih->bmiHeader.biBitCount != 32)
	{
		return Error;
	}

	return Success;
}

ErrorCode MPEGVideoDecoder::OutputPin::GetMediaType(int iPosition, MediaType** pMediaType)
{
	if (iPosition == 0)
	{
		//mediaType.Create(sizeof(LVIDEOINFOHEADER2));

		VideoInfoHeader* vih = new VideoInfoHeader;//((LVIDEOINFOHEADER2*)mediaType.pbFormat);

		//memset(&vih->bmiHeader, 0, sizeof(BitmapInfoHeader));
		vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
		vih->vih->bmiHeader.biPlanes = 1;

	// TODO, have 24, but manage so that output pin can override
		vih->vih->bmiHeader.biBitCount = 32;//m_pFilter->m_pInputPin->m_bitcount;
	//	vih->vih->bmiHeader.biBitCount = 24;

		vih->vih->bmiHeader.biWidth = m_p->m_mpeg_video->m_horizontal_size;
		vih->vih->bmiHeader.biHeight = m_p->m_mpeg_video->m_vertical_size;
		//memcpy(((BITMAPINFO*)&vih->bmiHeader)->bmiColors, m_pFilter->m_pInputPin->m_colors, m_pFilter->m_pInputPin->m_numColors*sizeof(RGBQUAD));

		ASSERT(0);
		MediaType* mediaType = NULL;//new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
	//	mediaType.SetMajorType(LMEDIATYPE_Video);
		//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
	//	mediaType.SetFormat(vih);

		/*
		RGBQUAD* colors = ((BITMAPINFO*)&vih->bmiHeader)->bmiColors;

		for (int i = 0; i < m_numcolors; i++)
		{
			colors[i].rgbRed = m_colors[i].Red;
			colors[i].rgbGreen = m_colors[i].Green;
			colors[i].rgbBlue = m_colors[i].Blue;
		}
		*/

		*pMediaType = mediaType;
		return Success_True;
	}
	else
	{
		*pMediaType = NULL;
		return Success_False;
	}
}

ErrorCode MPEGVideoDecoder::OutputPin::video_sequence_frames()
{
	double frameRate = tab_frame_rate_value[m_p->m_mpeg_video->m_frame_rate_code];

//	for (int i = m_currentFrame+1; i < m_displayPictures.GetCount(); i++)
	unsigned int frame = m_p->m_currentFrame+1;
	unsigned int nskipped = 0;

	unsigned int endOfStream = Success_False;

	while (frame < m_p->m_displayPictures.size())
	{
		/*
		if ((frame & 4))
		{
			frame++;
			continue;
		}
		*/
		Picture** pos = m_p->m_displayPictures.begin() + frame;

		LONGLONG tStart;
		LONGLONG tEnd;

		IMediaSample* sample;
		m_pAllocator->GetBuffer(0, &sample);

		LONGLONG curtime;
		GetFilter()->m_clock->GetTime(&curtime);

		Picture* pPicture;

		while (1)
		{
			pPicture = *pos++;
			if (pPicture == NULL)
			{
				VERIFY(0);
			}

			LONGLONG t = frame/*pPicture->m_temporal_reference_abs*/ * TIME_SCALE / frameRate;

			tStart = t;
			tEnd = t + TIME_SCALE / frameRate;

			frame++;

			break;

			if (m_pFilter->m_tStart+tEnd > curtime+4000)
				break;

			nskipped++;
		}

		//frame = curtime * frameRate / LTIME_SCALE;

		m_p->SeekFrame(frame-1);

		sample->SetTime(&tStart, &tEnd);

		LSampleData sampledata;
		sample->LockBits(&sampledata);

		m_p->SetSampleRGBData(pPicture->m_decoder, &sampledata);

		sample->UnlockBits();

		endOfStream = m_pInputPin->Receive(sample);

		sample->Release();

		if (endOfStream != Success_True)
			break;

	//	ShowFrame(picture->m_decoder);
	}

	if (endOfStream >= 0)
	{
		ConnectedTo()->EndOfStream();
	}

#if 0

	UPOSITION pos = m_displayPictures.find(m_currentFrame);

	while (m_currentFrame < m_displayPictures.GetCount())
	{
		CPicture
	// Seek to datapart of picture
		m_file->m_byteStream->Seek(pPicture->m_datapos, System::IO::STREAM_SEEK_SET);
		m_file->m_nstacked = 0;
		m_file->m_bytepos = 0;
		m_file->m_bitcnt = 0;

		int temporal_reference = m_file->getnbits(10);
		int picture_type = m_file->getnbits(3);

		pPictureDecoder = new PictureDecoder(this, m_file);
		pPictureDecoder->m_pic = pPicture;

		pPictureDecoder->m_pos = m_groupPictures.AddTail(pPictureDecoder);

		{
			if (buffers[nbuffer] == NULL)
			{
				int mb_rows = (m_vertical_size + 15)/16;

				buffers[nbuffer] = new ImageBuffer;
				buffers[nbuffer]->m_buf[0] = (uint8*)calloc(1, (m_mb_width*16+8)*(mb_rows*16+8));
				buffers[nbuffer]->m_buf[1] = (uint8*)calloc(1, (m_mb_width*8+8)*(mb_rows*8+8));
				buffers[nbuffer]->m_buf[2] = (uint8*)calloc(1, (m_mb_width*8+8)*(mb_rows*8+8));
				nbuffers = MAX(nbuffer, nbuffers);
			}

			pPictureDecoder->m_ybuf = buffers[nbuffer]->m_buf[0];
			pPictureDecoder->m_crbuf = buffers[nbuffer]->m_buf[1];
			pPictureDecoder->m_cbbuf = buffers[nbuffer]->m_buf[2];
			nbuffer++;
		}

		pPictureDecoder->picture_header();

		if (!m_mpeg1)
		{
			pPictureDecoder->picture_coding_extension();
			pPictureDecoder->extension_and_user_data(2);
		}

		pPictureDecoder->picture_data(TRUE);

		ShowFrame(pPictureDecoder);
		m_currentFrame++;
	}
#endif
	return Success;
}

ErrorCode MPEGVideoDecoder::OutputPin::Seek(TimeUnit unit, LONGLONG value)
{
	ULONG frame;

	if (unit == TimeFormat_ref)
	{
		double frame_rate_value = tab_frame_rate_value[m_p->m_mpeg_video->m_frame_rate_code];
		frame = value * frame_rate_value / TIME_SCALE;
	}
	else if (unit == TimeFormat_frame)
	{
		frame = value;
	}
	else
	{
		ASSERT(0);
		return Error;
	}

	if (frame < 0) frame = 0;
	else if (frame > m_p->m_pictures.size()-1) frame = m_p->m_pictures.size()-1;

	if (frame != m_p->m_currentFrame)
	{
		m_p->SeekFrame(frame);

		IMediaSample* sample;
		m_pAllocator->GetBuffer(0, &sample);
		if (sample)
		{
			LSampleData sampledata;
			sample->LockBits(&sampledata);

			m_p->SetSampleRGBData(m_p->m_displayPictures[frame]->m_decoder, &sampledata);
			sample->UnlockBits();

			m_pInputPin->Receive(sample);
			sample->Release();
		}
	}

	return Success;
}

ErrorCode MPEGVideoDecoder::OutputPin::GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
{
	if (unit == TimeFormat_ref)
	{
		double frame_rate_value = tab_frame_rate_value[m_p->m_mpeg_video->m_frame_rate_code];
		*pVal = m_p->m_currentFrame * TIME_SCALE / frame_rate_value;
	}
	else if (unit == TimeFormat_frame)
	{
		*pVal = m_p->m_currentFrame;
	}
	else
	{
		return Error;
	}

	return Success;
}

ErrorCode MPEGVideoDecoder::OutputPin::GetDuration(TimeUnit unit, LONGLONG* pVal)
{
	if (unit == TimeFormat_ref)
	{
		double frame_rate_value = tab_frame_rate_value[m_p->m_mpeg_video->m_frame_rate_code];
		ULONG nframes = m_p->m_displayPictures.size();
		*pVal = nframes * TIME_SCALE / frame_rate_value;
	}
	else if (unit == TimeFormat_frame)
	{
		*pVal = m_p->m_displayPictures.size();
	}
	else
	{
		return Error;
	}
	return Success;

}

ErrorCode MPEGVideoDecoder::Run(LONGLONG tStart)
{
	m_criticalSection.Lock();

	m_state = State_Running;
	m_tStart = tStart;

	m_criticalSection.Unlock();

	HANDLE m_hThread = CreateThread(RunningThreadProc, (LPVOID)(MPEGVideoDecoder*)this);

	/*
#if WIN32
	DWORD m_threadId;
	ASSERT(0);
#if 0
	HANDLE m_hThread = CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(MPEGVideoDecoder*)this, 0, &m_threadId);
#endif
#else
	;//CreateThread(RunningThreadProc, (void*)(MPEGVideoDecoder*)this);
#endif
	*/

	return Success;
}

}	// LMedia
}
