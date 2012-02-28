#include "stdafx.h"
//#include <stdio.h>
#include "IFF.h"
#include "IFFFormANIM.h"

namespace System
{
namespace MediaShow
{

bool decode_op5(BitMapHeader *bmhd, AnimationHeader *anhd, LONG deltadata[], uint8* planes[]);
bool decode_op7(BitMapHeader *bmhd, AnimationHeader *anhd, LONG deltadata[], uint8* planes[]);
bool decode_op8(BitMapHeader *bmhd, AnimationHeader *anhd, LONG deltadata[], uint8* planes[]);

SEQDATA::SEQDATA()
{
	m_currentFrame = -1;
	m_cPlanes = NULL;
	m_cPlanes2 = NULL;
	memset(m_planes1, 0, sizeof(uint8*) * 33);
}

IFFFormANIM::CInputPin::CInputPin() : BasePinImpl(PINDIR_INPUT)
{
}

ErrorCode IFFFormANIM::CInputPin::CheckConnect(IPin* pPin)
{
	// Call base class first
	ErrorCode hr = BasePinImpl::CheckConnect(pPin);
	if (hr < 0) return hr;

	IByteData* stream = dynamic_cast<IByteData*>(pPin);
	if (stream == NULL) return Error_NoInterface;

	m_stream = new ByteStreamWrapper(stream);

	return Success;
}

void IFFFormANIM::CInputPin::BreakConnect()
{
	// Release what we obtained in CheckConnect
	m_stream = NULL;
}

ErrorCode IFFFormANIM::CInputPin::CheckMediaType(MediaType * mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Stream)
		return Error;

	return Success;
}

////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////
// IFFFormANIM::CIFFAnimVideo

IFFFormANIM::CIFFAnimVideo::CIFFAnimVideo()
{
	m_hThread = NULL;
	m_threadId = 0;
}

ErrorCode IFFFormANIM::CIFFAnimVideo::CheckMediaType(MediaType * mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Video)
		return Error;

	return Success;
}

//void IFFFormANIM::CIFFAnimVideo::Init()
void IFFANIM::Init()
{
// Create video media type
	//ASSERT(0);
#if 0	// Had this
	CComObject<CVideoMediaType>::CreateInstance(&m_pMediaType);
	m_pMediaType->AddRef();
	m_pMediaType->m_pVideoOut = this;

	if (TRUE)	// TODO (check if paletted video
	{
		CComObject<CVideoMediaType::CPalette>::CreateInstance(&m_pMediaType->m_pPalette);
		m_pMediaType->m_pPalette->AddRef();
		m_pMediaType->m_pPalette->m_pMediaType = m_pMediaType;
	}
#endif

// Allocate all planes in one memory chunk
	m_planes0[0] = new uint8[m_planeSize*m_bmhd.bmh_Planes];
	m_planes1[0] = new uint8[m_planeSize*m_bmhd.bmh_Planes];

	for (int i = 1; i < m_bmhd.bmh_Planes; i++)
	{
		m_planes0[i] = m_planes0[0]+m_planeSize*i;
		m_planes1[i] = m_planes1[0]+m_planeSize*i;
	}

	m_cPlanes = m_planes0;

	m_currentFrame = -1;
#if 0
	m_currentPosition = -1;
#endif

	unsigned int reltime = 0;
	list<CAnimFrame*>::iterator pos = m_frameList.begin();
	while (pos != m_frameList.end())
	{
		CAnimFrame* pFrame = *pos;
		++pos;

		pFrame->m_timeStart = TIME_SCALE * reltime/60.0;
		pFrame->m_timeDur = TIME_SCALE * pFrame->m_anhd.ah_RelTime/60.0;

		reltime += pFrame->m_anhd.ah_RelTime;
	}
}

// virtual
ErrorCode IFFFormANIM::CIFFAnimVideo::GetMediaType(int iPosition, MediaType** pMediaType)
{
	if (iPosition == 0)
	{
		//mediaType.Create(sizeof(LVIDEOINFOHEADER2)+m_numcolors*sizeof(RGBQUAD));

		VideoInfoHeader* vih = new VideoInfoHeader(m_pAnim->m_numcolors);//((LVIDEOINFOHEADER2*)mediaType.pbFormat);

		//memset(&vih->bmiHeader, 0, sizeof(BITMAPINFOHEADER));
		vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
		vih->vih->bmiHeader.biPlanes = 1;
		// TODO
		vih->vih->bmiHeader.biBitCount = 32;//m_pFilter->m_pInputPin->m_bitcount;
	//	vih->vih->bmiHeader.biBitCount = 24;//m_pFilter->m_pInputPin->m_bitcount;
		vih->vih->bmiHeader.biWidth = m_pAnim->m_bmhd.bmh_Width;
		vih->vih->bmiHeader.biHeight = m_pAnim->m_bmhd.bmh_Height;
		//memcpy(((BITMAPINFO*)&vih->bmiHeader)->bmiColors, m_pFilter->m_pInputPin->m_colors, m_pFilter->m_pInputPin->m_numColors*sizeof(RGBQUAD));

		RGBQuad* colors = ((BitmapInfo*)&vih->vih->bmiHeader)->bmiColors;

		for (int i = 0; i < m_pAnim->m_numcolors; i++)
		{
			colors[i].rgbRed = m_pAnim->m_colors[i].Red;
			colors[i].rgbGreen = m_pAnim->m_colors[i].Green;
			colors[i].rgbBlue = m_pAnim->m_colors[i].Blue;
		}

		MediaType* mediaType = new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
	//	mediaType.SetMajorType(LMEDIATYPE_Video);
		//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
	//	mediaType.SetFormat(vih);

		*pMediaType = mediaType;

		return Success_True;
	}
	else
	{
		*pMediaType = NULL;
		return Success_False;
	}
}

ErrorCode IFFFormANIM::CIFFAnimAudio::GetMediaType(int iPosition, MediaType** pMediaType)
{
	if (iPosition == 0)
	{
		WaveFormat* wf = new WaveFormat;//((WAVEFORMATEX*)mediaType.pbFormat);
		wf->wf->wFormatTag = WAVE_FORMAT_PCM;
		wf->wf->nChannels = m_pAnim->m_nChannels;
		wf->wf->nSamplesPerSec = m_pAnim->m_sxhd.PlayFreq;
		wf->wf->wBitsPerSample = m_pAnim->m_sxhd.SampleDepth;
		wf->wf->nBlockAlign = m_pAnim->m_nBlockAlign;
		wf->wf->nAvgBytesPerSec = wf->wf->nSamplesPerSec * wf->wf->nBlockAlign;
		wf->wf->cbSize = 0;

		MediaType* mediaType = new MediaType(LMEDIATYPE_Audio, GUID_NULL, GUID_NULL, wf);
	//	mediaType.SetMajorType(LMEDIATYPE_Audio);
		//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
	//	mediaType.SetFormat(wf);
		*pMediaType = mediaType;

		return Success_True;
	}
	else
	{
		*pMediaType = NULL;
		return Success_False;
	}
}

IFFRESULT IFFANIM::ReadDLTA(CAnimFrame* f, uint32 ckSize)
{
	ASSERT(f);

	SEQDATA* seqdata = this;//(SEQDATA*)r->seq_data;
	ASSERT(seqdata);

	IFFRESULT	iffresult = IFF_OK;	// Assume success

	BitMapHeader		*bmhd = &m_bmhd;
	AnimationHeader	*anhd = &f->m_anhd;

	uint8*	ckdata = NULL;	// Buffer holding the body chunk data
	uint8*	planeptr = NULL;	// Buffer containing planeptrs for one scanline

// Allocate mem and read in the entire body data
	ckdata = new uint8[ckSize];
	if (ckdata == NULL) return IFFERR_MEMORY;

	if (m_pIFFParser->IFFReadChunkBytes(ckdata, ckSize) != ckSize)
	{
		delete[] ckdata;
		return IFFERR_READWRITE;
	}

	bool error;

	switch (anhd->ah_Operation)
	{
		case 5:
			error = decode_op5(bmhd, anhd, (long*)ckdata, m_cPlanes);
			break;

		case 7:
			error = decode_op7(bmhd, anhd, (long*)ckdata, m_cPlanes);
			break;

//		case 8:
//		break;

//		case 'J':
//		break;

		default:
			iffresult = IFFERR_COMPRESS;
			;//AfxMessageBox("unknown opcode");
	}

	if (!iffresult)
	{
		if (error)
			iffresult = IFFERR_CORRUPTED;
	}

	delete[] ckdata;

	return iffresult;
}

ErrorCode IFFANIM::ReadFrameData(CAnimFrame* f)
{
	if (f->m_cmapPos)	// Palette change
	{
		m_pIFFParser->SetFilePos(f->m_cmapPos, System::IO::STREAM_SEEK_SET);

		m_pIFFParser->IFFReadChunkBytes(m_colors, f->m_cmapSize);
	}

	if (f->m_bodyPos)
	{
		m_pIFFParser->SetFilePos(f->m_bodyPos, System::IO::STREAM_SEEK_SET);

		ReadBODY(f->m_bodySize);	// Reads into m_planes[0]

	// Copy all planes
		memcpy(m_planes1[0], m_planes0[0], m_planeSize*m_bmhd.bmh_Planes);
	}
	else if (f->m_dltaPos)
	{
		m_pIFFParser->SetFilePos(f->m_dltaPos, System::IO::STREAM_SEEK_SET);

		ReadDLTA(f, f->m_dltaSize);
	}

	//	result = ReadILBMForm(f, FALSE);

	m_cPlanes2 = m_cPlanes;

// Delta is two frames back
	if (/*i != 1 &&*/ ((f->m_anhd.ah_Interleave == 0) || (f->m_anhd.ah_Interleave == 2)))
	{
		if (m_cPlanes == m_planes0)
			m_cPlanes = m_planes1;
		else
			m_cPlanes = m_planes0;
	}

	return Success;
}

ErrorCode IFFANIM::SeekFrame(int frame)
{
	int result = 1;

	int start;
	int to;

	if (frame > m_currentFrame)
	{
		start = m_currentFrame+1;
		to = frame;
	}
	else
	{
		start = 0;
		to = frame;
	}

	m_cPlanes2 = NULL;

	list<CAnimFrame*>::iterator it = m_frameList.begin();
	for (int i = 0; i < start; i++)
	{
		++it;
	}
	//UPOSITION pos = m_frameList.FindIndex(start);

	for (int i = start; i <= to; i++)
	{
		CAnimFrame* f = *it;//(CAnimFrame*)m_frameList.GetNext(pos);
		++it;

		ASSERT(f);

		ReadFrameData(f);
	}

	m_currentFrame = frame;

	result = 0;

	return result;
}

ErrorCode IFFFormANIM::CIFFAnimVideo::GetDuration(TimeUnit unit, LONGLONG* pVal)
{
	if (pVal == NULL) return Error_NullPointerArgument;

	if (unit == TimeFormat_ref)
	{
		long reltime = 0;

		list<CAnimFrame*>::iterator pos = m_pAnim->m_frameList.begin();
		while (pos != m_pAnim->m_frameList.end())
		{
			CAnimFrame* pFrame = *pos;
			++pos;

			reltime += pFrame->m_anhd.ah_RelTime;
		}

		LONGLONG videoDuration = reltime * TIME_SCALE / 60;

		*pVal = videoDuration;
		return Success;
	}
	else if (unit == TimeFormat_frame)
	{
		*pVal = m_pAnim->m_frameList.size();
		return Success;
	}
	else
	{
		ASSERT(0);
	}
	return Error;
}

ErrorCode IFFFormANIM::CIFFAnimVideo::Seek(TimeUnit unit, LONGLONG t)
{
	int nframe = 0;

	if (unit == TimeFormat_ref)
	{
		m_currentPosition = t;

		/*
		if (m_sample == NULL)
		{
			m_allocator->GetBuffer(0, (ILMediaSample**)&m_sample);
		}
		*/

	// Find the frame to seek to
		unsigned int reltime = 0;

		list<CAnimFrame*>::iterator pos = m_pAnim->m_frameList.begin();
		while (pos != m_pAnim->m_frameList.end())
		{
			CAnimFrame* pFrame = *pos;
			++pos;

			//if (pos == NULL) break;

			reltime += pFrame->m_anhd.ah_RelTime;
			LONGLONG s = TIME_SCALE * reltime/60.0;

			if (s >= t)
				break;

			nframe++;
		}
	}
	else if (unit == TimeFormat_frame)
	{
		nframe = unit;

		// TODO, set m_currentPosition
	}

	if (nframe != m_pAnim->m_currentFrame)
	{
		m_pAnim->SeekFrame(nframe);

		IMediaSample* sample;
		m_pAllocator->GetBuffer(0, &sample);

		m_pAnim->PlanarToChunky(m_pAnim->m_cPlanes2, sample);

		m_pInputPin->Receive(sample);

		sample->Release();

		//ASSERT(0);
#if 0	// Had this
		if (m_sample)
		{
			PlanarToChunky(m_cPlanes2);

		// ???
			CComQIPtr<ILMemInputPin> memInput = m_connectedTo;
			if (memInput)
			{
				memInput->Receive(m_sample);
			}
		}
#endif
	}

	return Success;
}

ErrorCode IFFFormANIM::CIFFAnimVideo::GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
{
	if (pVal == NULL) return Error_NullPointerArgument;
	if (unit == TimeFormat_ref)
	{
		*pVal = m_currentPosition;
	}
	else if (unit == TimeFormat_frame)
	{
		*pVal = m_pAnim->m_currentFrame;
	}
	else
	{
		ASSERT(0);
		return Error;
	}

	return Success;
}

/////////////////////////////////////////////////////////
// IFFFormANIM::CIFFAnimAudio

/*
IFFAnimAudio::IFFAnimAudio()
{
	memset(&m_sxhd, 0, sizeof(m_sxhd));
	m_nChannels = 0;
	m_nBlockAlign = 0;
	m_nSamples = 0;
}
*/

IFFFormANIM::CIFFAnimAudio::CIFFAnimAudio()
{
#if WIN32
	m_hThread = NULL;
	m_threadId = 0;
#else
	m_hThread = NULL;
#endif
}

ErrorCode IFFFormANIM::CIFFAnimAudio::CheckMediaType(MediaType * mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Audio)
		return Error;

	return Success;
}

void IFFANIM::InitAudio()
{
	m_nSamples = 0;

	if (m_nChannels)
	{
		// Build flattened list of all audio chunks found in frames

		list<CAnimFrame*>::iterator it = m_frameList.begin();
		while (it != m_frameList.end())
		{
			CAnimFrame* pFrame = *it;//(CAnimFrame*)GetFilter()->m_pVideo->m_frameList.GetNext(pos);
			++it;

			list<CAudioChunk*>::iterator it2 = pFrame->m_audioChunks.begin();//GetHeadPosition();
			while (it2 != pFrame->m_audioChunks.end())
			{
				CAudioChunk* pAudioChunk = *it2;//(CAudioChunk*)pFrame->m_audioChunks.GetNext(pos2);
				++it2;
				pAudioChunk->m_nSamples = pAudioChunk->m_soundDataLength / m_nBlockAlign;

				m_nSamples += pAudioChunk->m_nSamples;

				m_audioChunks.push_back(pAudioChunk);
			}
		}
	}

#if 0
	if (TRUE)
	{
		CComPtr<ILBaseFilter> filter;
		filter.CoCreateInstance(L"LMedia.LDSoundRender");

		CComPtr<ILPin> inpin;
		filter->GetPin(0, &inpin);

		m_pFilter->m_pFilterGraph->ConnectDirect(this, inpin, NULL);
	}
#endif
}

ErrorCode IFFFormANIM::CIFFAnimAudio::GetDuration(TimeUnit unit, LONGLONG* pVal)
{
	if (pVal == NULL) return Error_NullPointerArgument;
	*pVal = TIME_SCALE * m_pAnim->m_nSamples / m_pAnim->m_sxhd.PlayFreq;
	return Success;
}

ErrorCode IFFFormANIM::CIFFAnimAudio::Seek(TimeUnit unit, LONGLONG t)
{
	return Success;
}

ErrorCode IFFFormANIM::CIFFAnimAudio::GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
{
	if (pVal == NULL) return Error_NullPointerArgument;
	*pVal = 0;
	return Success;
}

#if 0	// Had this
// ILAudio
STDMETHODIMP IFFFormANIM::CIFFAnimAudio::GetSamples(LONGLONG *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_nSamples;
	return Success;
}

STDMETHODIMP IFFFormANIM::CIFFAnimAudio::GetFormat(WAVEFORMATEX *pVal)
{
	if (pVal == NULL) return E_POINTER;

	pVal->wFormatTag = WAVE_FORMAT_PCM;
	pVal->nChannels = m_nChannels;
	pVal->wBitsPerSample = m_sxhd.SampleDepth;
	pVal->nSamplesPerSec = m_sxhd.PlayFreq;
	pVal->nBlockAlign = m_nBlockAlign;
	pVal->cbSize = 0;

	return Success;
}

STDMETHODIMP IFFFormANIM::CIFFAnimAudio::GetChunkSize(long nchunk, ULONG* pVal)
{
#if 0
	if (nchunk < m_chunks.GetCount())
	{
		CAudioChunk* f = (CAudioChunk*)m_chunks.GetAt(m_chunks.FindIndex(nchunk));

	// Number of samples in chunk
		*pVal = f->m_soundDataLength / m_nBlockAlign;

		return Success;
	}
	else
		return S_FALSE;
#endif
	return Error;
}

STDMETHODIMP IFFFormANIM::CIFFAnimAudio::ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples)
{
#if 0
	if (nchunk < m_chunks.GetCount())
	{
		CAudioChunk* f = (CAudioChunk*)m_chunks.GetAt(m_chunks.FindIndex(nchunk));

		m_pFilter->m_pInputPin->m_pIFFParser->SetFilePos(*(LARGE_INTEGER*)&f->m_soundDataOffset, STREAM_SEEK_SET, NULL);

		if (m_nChannels == 1)
		{
			DWORD nbytes = nsamples*m_nBlockAlign;
			m_pFilter->m_pInputPin->m_pIFFParser->IFFReadChunkBytes(buffer, nbytes);
		}
		else if (m_nChannels == 2)
		{
		// Make interleaved instead of all of left and then all of right

			DWORD nbytes = nsamples*m_nBlockAlign/2;

			uint8* tbuffer = (uint8*)GlobalAlloc(0, nbytes);
			if (tbuffer)
			{
			// left channel
				m_pFilter->m_pInputPin->m_pIFFParser->IFFReadChunkBytes(tbuffer, nbytes);

				if (m_sxhd.SampleDepth == 8)
				{
					char *p = (char*)buffer;

					for (int n = 0; n < nsamples; n++)
					{
						p[n*2] = tbuffer[n];
					}
				}
				else if (m_sxhd.SampleDepth == 16)
				{
					WORD *p = (WORD*)buffer;

					for (int n = 0; n < nsamples; n++)
					{
						p[n*2] = tbuffer[n];
					}
				}

			// right channel
				m_pFilter->m_pInputPin->m_pIFFParser->IFFReadChunkBytes(tbuffer, nbytes);

				if (m_sxhd.SampleDepth == 8)
				{
					char *p = (char*)buffer;

					for (int n = 0; n < nsamples; n++)
					{
						p[n*2+1] = tbuffer[n];
					}
				}
				else if (m_sxhd.SampleDepth == 16)
				{
					WORD *p = (WORD*)buffer;

					for (int n = 0; n < nsamples; n++)
					{
						p[n*2+1] = tbuffer[n];
					}
				}

				GlobalFree(tbuffer);
			}
		}

#if 0
		if (m_sxhd.SampleDepth == 8)
		{
			DWORD nbytes = nsamples*m_nBlockAlign;

		// Make unsigned
			char *p = (char*)buffer;
			int len = nbytes;

			while (len--)
			{
				*p = *p + 128;
				p++;
			}
		}
#endif
	}
	return Success;
#endif

	return Error;
}
#endif

ErrorCode IFFFormANIM::CIFFAnimAudio::ReadChunk(CAudioChunk* f, uint8* buffer, ULONG startSample, ULONG nsamples)
{
	if (m_pAnim->m_nChannels == 1)
	{
		uint pos = f->m_soundDataOffset + startSample*m_pAnim->m_nBlockAlign;
	//	m_pFilter->m_pInputPin->m_pIFFParser->SetFilePos(li, STREAM_SEEK_SET);

		uint nbytes = nsamples * m_pAnim->m_nBlockAlign;
	//	m_pFilter->m_pInputPin->m_pIFFParser->IFFReadChunkBytes(buffer, nbytes);
		GetFilter()->m_pInputPin->m_stream->GetBaseData()->Read(buffer, pos, nbytes);
	}
	else if (m_pAnim->m_nChannels == 2)
	{
	// Make interleaved instead of all of left and then all of right

		uint startoffset = startSample*m_pAnim->m_nBlockAlign/2;
		uint nbytes = nsamples*m_pAnim->m_nBlockAlign/2;

		uint8* tbuffer = new uint8[nbytes];
		if (tbuffer)
		{
			//LARGE_INTEGER li;

		// left channel
			uint pos = f->m_soundDataOffset + startoffset;
			//m_pFilter->m_pInputPin->m_pIFFParser->SetFilePos(li, STREAM_SEEK_SET);

			//m_pFilter->m_pInputPin->m_pIFFParser->IFFReadChunkBytes(tbuffer, nbytes);
			GetFilter()->m_pInputPin->m_stream->GetBaseData()->Read(tbuffer, pos, nbytes);

			if (m_pAnim->m_sxhd.SampleDepth == 8)
			{
				char *p = (char*)buffer;

				for (int n = 0; n < nsamples; n++)
				{
					p[n*2] = tbuffer[n];
				}
			}
			else if (m_pAnim->m_sxhd.SampleDepth == 16)
			{
				int16 *p = (int16*)buffer;

				for (int n = 0; n < nsamples; n++)
				{
					p[n*2] = tbuffer[n];
				}
			}

		// right channel
			pos = f->m_soundDataOffset + f->m_soundDataLength/2 + startoffset;
			//m_pFilter->m_pInputPin->m_pIFFParser->SetFilePos(li, STREAM_SEEK_SET);

		//	m_pFilter->m_pInputPin->m_pIFFParser->IFFReadChunkBytes(tbuffer, nbytes);
			GetFilter()->m_pInputPin->m_stream->GetBaseData()->Read(tbuffer, pos, nbytes);

			if (m_pAnim->m_sxhd.SampleDepth == 8)
			{
				char *p = (char*)buffer;

				for (int n = 0; n < nsamples; n++)
				{
					p[n*2+1] = tbuffer[n];
				}
			}
			else if (m_pAnim->m_sxhd.SampleDepth == 16)
			{
				int16 *p = (int16*)buffer;

				for (int n = 0; n < nsamples; n++)
				{
					p[n*2+1] = tbuffer[n];
				}
			}

			delete[] tbuffer;
		}
	}

#if 0//WIN32
	if (m_sxhd.SampleDepth == 8)	// Make unsigned
	{
		DWORD nbytes = nsamples*m_nBlockAlign;

		char *p = (char*)buffer;
		int len = nbytes;

		while (len--)
		{
			*p = *p + 128;
			p++;
		}
	}
#endif

	return Success;
}

/////////////////////////////////////////////////////////////////////////////////////
// IFFFormANIM

IFFFormANIM::IFFFormANIM()
{
	m_pInputPin = NULL;

	m_pVideo = NULL;
	m_pAudio = NULL;

	m_pInputPin = new CInputPin;
	m_pInputPin->m_pFilter = this;
	m_pInputPin->m_id = WSTR("Stream Input");
	AddPin(m_pInputPin);
}

ErrorCode IFFFormANIM::CInputPin::CompleteConnect(IPin *pPin)
{
	// Must call base class
	ErrorCode hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

#if 0
	m_connectedTo = pConnector;
	m_pIFFParser = m_connectedTo;
	m_pFilter->m_pImage->m_pIFFParser = m_pIFFParser;
	if (m_pIFFParser == NULL) return Error;
#endif
	m_pIFFParser = new IFFParser(m_stream);
//	m_pFilter->m_pImage->m_pIFFParser = m_pIFFParser;

	IFFCHUNK	formck;// = *(LPIFFCHUNK)r->firstBytes;
	m_pIFFParser->IFFDescendChunk(&formck);

	if (formck.ckID != ID_FORM)
	{
		return Error;
	}

	if (formck.grpID == ID_ANIM)
	{
		hr = GetFilter()->Parse();
	}
	else
	{
		hr = Error;
	}

	return hr;
}

ErrorCode IFFFormANIM::Parse()
{
	m_pAnim = new IFFANIM;

	m_pVideo = new CIFFAnimVideo;
	m_pVideo->m_pAnim = m_pAnim;
	m_pVideo->m_pFilter = this;
	m_pVideo->m_pAnim->m_pIFFParser = m_pInputPin->m_pIFFParser;
	AddPin(m_pVideo);

// Scan all frames
	while (GetNextFrame() == 0)
	{
	}

	if (m_pVideo->m_pAnim->m_nChannels)
	{
		m_pAudio = new CIFFAnimAudio;
		m_pAudio->m_pAnim = m_pAnim;
		m_pAudio->m_pFilter = this;
		AddPin(m_pAudio);
	}

	// Count total number of audio samples
	if (m_pAudio)
	{
		m_pAudio->m_pAnim->InitAudio();
	}

	// Setup decoding
	if (m_pVideo)
	{
		m_pVideo->m_pAnim->Init();
		m_pVideo->m_currentPosition = -1;
	}

	return Success;
}

IFFRESULT IFFANIM::ReadILBMForm(CAnimFrame* f, bool bInitRead)
{
	IFFRESULT iffresult;

	IFFCHUNK	ck;

	while ((iffresult = m_pIFFParser->IFFDescendChunk(&ck)) == IFF_OK)
	{
		switch (ck.ckID)
		{
			case ID_BMHD:
			{
				iffresult = BMHDChunk(&ck);
			}
			break;

			case ID_ANHD:
			{
				if (ck.ckSize != sizeof(AnimationHeader))
				{
					iffresult = IFFERR_CORRUPTED;
					break;
				}

				if (bInitRead && f != NULL)
				{
					AnimationHeader	*anhd = &f->m_anhd;

					if ((iffresult = m_pIFFParser->IFFReadChunkBytes(anhd, sizeof(AnimationHeader))) == sizeof(AnimationHeader))
					{
						anhd->ah_Width = BigEndian16(anhd->ah_Width);
						anhd->ah_Height = BigEndian16(anhd->ah_Height);
						anhd->ah_Left = BigEndian16(anhd->ah_Left);
						anhd->ah_Top = BigEndian16(anhd->ah_Top);
						anhd->ah_AbsTime = BigEndian32(anhd->ah_AbsTime);
						anhd->ah_RelTime = BigEndian32(anhd->ah_RelTime);
						anhd->ah_Flags = BigEndian32(anhd->ah_Flags);

						TRACE("%d, %d\n", anhd->ah_AbsTime, anhd->ah_RelTime);

#if 0
						if (g->currentFrame == 1)	// We've already read the first frame
						{
							if (anhd->ah_Operation == 5)			strcat(g->szVideoInfo, "op5");
							else if (anhd->ah_Operation == 7)	strcat(g->szVideoInfo, "op7");
							else if (anhd->ah_Operation == 8)	strcat(g->szVideoInfo, "op8");
							else if (anhd->ah_Operation == 'J')	strcat(g->szVideoInfo, "opJ");
							else
								strcat(g->szVideoInfo, "unkown op");
						}
#endif
					}
					else
						iffresult = IFFERR_READWRITE;
				}
			}
			break;

			case ID_CMAP:
			{
				if (bInitRead)
				{
				//	iffresult = m_pVideo->CMAPChunk(&ck);

					ASSERT(f);

					f->m_cmapPos = m_pIFFParser->SetFilePos(0, System::IO::STREAM_SEEK_CUR);
					f->m_cmapSize = ck.ckSize;
				}
			}
			break;

			case ID_CAMG:
			{
				if (bInitRead)
				{
					iffresult = CAMGChunk(&ck);
				}
			}
			break;

			case ID_DLTA:
			{
				if (bInitRead)
				{
					ASSERT(f);

					f->m_dltaPos = m_pIFFParser->SetFilePos(0, System::IO::STREAM_SEEK_CUR);
					f->m_dltaSize = ck.ckSize;
				}
				else
				{
					/*
					AnimationHeader	*anhd = &f->anhd;

					iffresult = m_pVideo->ReadDLTA(f, ck.ckSize);
					*/
				}
			}
			break;

			case ID_BODY:
			{
				if (bInitRead)
				{
					ASSERT(f);

					f->m_bodyPos = m_pIFFParser->SetFilePos(0, System::IO::STREAM_SEEK_CUR);
					f->m_bodySize = ck.ckSize;

					BODYChunk(&ck);
				}
#if 0
				else	// Read Frame
				{
					DWORD	camg = m_pVideo->m_camg;
					BitMapHeader	*bmhd = &m_pVideo->m_bmhd;

					int numcolors = m_pVideo->m_numcolors;
					//g_numcolors = numcolors;

#if 0
					PixelDef* pPalette = g->pPalette8;

					for (int i = 0; i < numcolors; i++)
					{
						pPalette[i].red = m_colors[i].Red;
						pPalette[i].green = m_colors[i].Green;
						pPalette[i].blue = m_colors[i].Blue;
					}

					if (camg & AMIGA_EHB)	// Make colors 32-63 halfbrites of colors 0-31
					{
						g_numcolors += 32;

						for (WORD i = 0; i < numcolors; i++)
						{
							pPalette[32+i].red = m_colors[i].Red>>1;
							pPalette[32+i].green = m_colors[i].Green>>1;
							pPalette[32+i].blue = m_colors[i].Blue>>1;
						}
					}
#endif

					iffresult = m_pVideo->ReadBODY(&ck);	// Reads into m_planes[0]

					CopyMemory(m_pVideo->m_planes1[0], m_pVideo->m_planes0[0], m_pVideo->m_planeSize*m_pVideo->m_bmhd.bmh_Planes);
				}
#endif
			}
			break;

			case ID_SXHD:
			{
				if (bInitRead)
				{
					//ASSERT(m_pAudio == NULL);
					if (true)
					{
						/*
						if (m_pAudio == NULL)
						{
							m_pAudio = new IFFAnimAudio;
							if (m_pAudio)
							{
							*/
#if 0
								m_pAudio->m_pFilter = this;
								AddPin(m_pAudio);
#endif
								AnimSoundHeader* sxhd = &m_sxhd;

								if (ck.ckSize != sizeof(AnimSoundHeader))
								{
									iffresult = IFFERR_CORRUPTED;
									break;
								}

								if ((iffresult = m_pIFFParser->IFFReadChunkBytes(sxhd, sizeof(AnimSoundHeader))) == sizeof(AnimSoundHeader))
								{
									sxhd->CompressionMethod = BigEndian32(sxhd->CompressionMethod);
									sxhd->PlayRate = BigEndian32(sxhd->PlayRate);
									sxhd->PlayFreq = BigEndian32(sxhd->PlayFreq);

									if (sxhd->UsedChannels & 3)	// Not sure about this
										m_nChannels = 2;
									else
										m_nChannels = 1;

									m_nBlockAlign = m_nChannels * sxhd->SampleDepth/8;
								}
								/*
							}
						}
						*/
					}
				}
			}
			break;

			case ID_SBDY:
				{
					if (bInitRead)
					{
						if (m_nChannels)
						//if (m_pAudio)
						{
							CAudioChunk* pAChunk = new CAudioChunk;
							f->m_audioChunks.push_back(pAChunk);

							pAChunk->m_soundDataOffset = m_pIFFParser->SetFilePos(0, IO::STREAM_SEEK_CUR);
							pAChunk->m_soundDataLength = ck.ckSize;
						}
					}
				}
				break;

			default:
				TRACE("%4.4s\n", &ck.ckID);
		}

		if (iffresult < 0) break;

		iffresult = m_pIFFParser->IFFAscendChunk(&ck);
	}

	return iffresult;
}

int IFFFormANIM::GetNextFrame()
{
	int ret = 1;	// assume no more frames

	IFFCHUNK	ck;
	int iffresult;

	iffresult = m_pInputPin->m_pIFFParser->IFFDescendChunk(&ck);
	if (iffresult == IFF_EOC || iffresult == IFF_OK)
	{
		if ((ck.ckID == ID_FORM) && (ck.grpID == ID_ILBM))
		{
			CAnimFrame* f = new CAnimFrame;

#if 0	// ????
			if (m_currentFrame == 1)
			{
			// Second frame defaults to delta from one frame back
			// unless specified otherwise
				if (f->anhd.ah_Interleave == 0)
				{
					f->anhd.ah_Interleave = 1;
				}
			}
#endif

			f->fileOffset = m_pInputPin->m_pIFFParser->SetFilePos(0, System::IO::STREAM_SEEK_CUR);

			m_pAnim->m_frameList.push_back(f);

			m_pAnim->ReadILBMForm(f, true);

			ret = 0;	// more frames
		}

		iffresult = m_pInputPin->m_pIFFParser->IFFAscendChunk(&ck);
	}

	return ret;
}

#if AMIGA
#define WINAPI
#endif

MSWindows::DWORD WINAPI RunningThreadProc(void* lpParameter)
{
	IFFFormANIM::CIFFAnimVideo* pVideo = (IFFFormANIM::CIFFAnimVideo*)lpParameter;

	list<CAnimFrame*>::iterator it = pVideo->m_pAnim->m_frameList.begin();
	for (int i = 0; i < pVideo->m_pAnim->m_currentFrame+1; i++)
	{
		++it;
	}

	ErrorCode hr = Success_False;

	for (int i = pVideo->m_pAnim->m_currentFrame+1; i < pVideo->m_pAnim->m_frameList.size(); i++)
	{
		CAnimFrame* pFrame = *it;
		++it;

		IMediaSample* sample = NULL;
		pVideo->m_pAllocator->GetBuffer(0, &sample);
		if (sample)
		{
			pVideo->m_pAnim->SeekFrame(i);
			pVideo->m_pAnim->PlanarToChunky(pVideo->m_pAnim->m_cPlanes2, sample);

			LONGLONG timeStart = pFrame->m_timeStart;
			LONGLONG timeEnd = pFrame->m_timeStart+pFrame->m_timeDur;
			sample->SetTime(&timeStart, &timeEnd);

			pVideo->m_currentPosition = timeStart;

			hr = pVideo->m_pInputPin->Receive(sample);

			sample->Release();

			if (hr != Success_True)
			{
				break;
			}
		}

	//	if (pVideo->GetFilter()->GetState() != LState_Running)
	//		return 0;
	}

	if (hr >= 0)	// Don't send this if the downstream filter failed in Receive?
	{
		pVideo->ConnectedTo()->EndOfStream();
	}

	return 0;
}

MSWindows::DWORD WINAPI RunningAudioThreadProc(void* lpParameter)
{
	IFFFormANIM::CIFFAnimAudio* p = (IFFFormANIM::CIFFAnimAudio*)lpParameter;

	ErrorCode hr;

	IMemInputPin* memInput = dynamic_cast<IMemInputPin*>(p->ConnectedTo());
	if (memInput)
	{
		LONGLONG t = 0;

		IMediaSample* sample = NULL;
		LSampleData buffer;
		ULONG total = p->m_pAnim->m_sxhd.PlayFreq*4;

		ULONG sofar = 0;

		list<CAudioChunk*>::iterator pos = p->m_pAnim->m_audioChunks.begin();
		while (pos != p->m_pAnim->m_audioChunks.end())
		{
			CAudioChunk* pAChunk = *pos;
			++pos;

			if (sample == NULL)
			{
				p->m_pAllocator->GetBuffer(total*2, &sample);
				sample->LockBits(&buffer);
			}

			//while (sofar < total)
			{
				ULONG count = pAChunk->m_nSamples;

				if (sofar+count > total)
				{
					count = total - sofar;
				}

				p->ReadChunk(pAChunk, buffer.idata+sofar*p->m_pAnim->m_nBlockAlign, 0, count);

				sofar += count;

				if (sofar == total || pos == NULL)	// Filled the buffer, send it
				{
					sample->UnlockBits();

					sample->SetActualDataLength(sofar * p->m_pAnim->m_nBlockAlign);

					LONGLONG t2 = t + sofar * TIME_SCALE / p->m_pAnim->m_sxhd.PlayFreq;

					LONGLONG timeStart = t;//pFrame->m_timeStart;
					LONGLONG timeEnd = t2;//pFrame->m_timeStart+pFrame->m_timeDur;
					sample->SetTime(&timeStart, &timeEnd);

					t = timeEnd;

				//	printf("Sending\n");

					hr = memInput->Receive(sample);
					/*
					if (FAILED(hr) || hr == S_FALSE)
					{
						break;
					}
					*/
					sample->Release();
					sample = NULL;
					//buffer = NULL;
					sofar = 0;
				}

			//	if (p->GetFilter()->GetState() != LState_Running)
			//		return 0;
			}
		}
	}

	//printf("Done Sending\n");

	/*
	if (SUCCEEDED(hr))	// Don't send this if the downstream filter failed in Receive?
		*/
	p->ConnectedTo()->EndOfStream();

	return 0;
}

ErrorCode IFFFormANIM::CIFFAnimVideo::Pause()
{
#if WIN32
	if (m_hThread == NULL)
	{
		m_hThread = MSWindows::CreateThread(NULL, NULL, RunningThreadProc, (void*)(IFFFormANIM::CIFFAnimVideo*)this, 0, &m_threadId);
	}
#elif AMIGA
	CreateThread(RunningThreadProc, (void*)(IFFFormANIM::CIFFAnimVideo*)this);
#endif
	return Success;
}

ErrorCode IFFFormANIM::CIFFAnimAudio::Pause()
{
#if WIN32
	if (m_hThread == NULL)
	{
		m_hThread = MSWindows::CreateThread(NULL, NULL, RunningAudioThreadProc, (LPVOID)(IFFFormANIM::CIFFAnimAudio*)this, 0, &m_threadId);
	}
#else
	CreateThread(RunningAudioThreadProc, (LPVOID)(IFFFormANIM::CIFFAnimAudio*)this);
#endif
	return Success;
}

}	// MediaShow
}
