#include "stdafx.h"
#include "HTML2.h"

namespace System
{
namespace Web
{

#if 0
ErrorCode_Bool MediaSource::AudioFilter::InputPin::Receive(MediaShow::IMediaSample *samplein)
{
	CriticalSectionLock lock(m_pLock);

	MemAllocator::AudioSample* pSampleIn = static_cast<MemAllocator::AudioSample*>(samplein);

	MediaShow::IMediaSample* sampleOut;
	m_pFilter->m_pOutput->m_allocator->GetBuffer(pSampleIn->m_dwBytes, &sampleOut);

	MediaShow::LSampleData bufferOut;
	sampleOut->LockBits(&bufferOut);

	uint8* bufferIn = pSampleIn->m_pointer;

//	ULONG nSamples;
//	m_mediaType->GetSamples(&nSamples);

	ASSERT(0);
	LPWAVEFORMATEX wf = NULL;//(LPWAVEFORMATEX)m_mt.pbFormat;

	uint nbytes = pSampleIn->m_dwBytes;//wf.nBlockAlign * nSamples;

	uint nSamplesIn = pSampleIn->m_dwBytes / wf->nBlockAlign;

	uint nSamplesOut = 0;	// TODO

#if 0
	if (TRUE)
	{

#if 0
		ULONG startSample = start_tsp * m_pMedia->m_wavFormat->nSamplesPerSec;
		ULONG nSamples = lent * m_pMedia->m_wavFormat->nSamplesPerSec;

		ATLTRACE("startSample:%d, nSamples:%d\n", startSample, nSamples);
#endif

		double parent_speed = 1;
		double AD = m_pFilter->m_pElement->m_AD;// * m_pMedia->m_wavFormat->nSamplesPerSec;//m_dur;// ? AD=Active Duration?
		double speed = m_pFilter->m_pElement->m_speed->m_value->m_value;
		double acc = m_pFilter->m_pElement->m_accelerate->m_value->m_value;
		double dec = m_pFilter->m_pElement->m_decelerate->m_value->m_value;

		if (acc+dec > 1)	// Ignore both attributes
		{
			acc = 0;
			dec = 0;
		}

		double r = (1 / (1 - acc/2 - dec/2));// * m_pMedia->m_wavFormat->nSamplesPerSec;

		//Let dur be the value of the simple duration as defined by the Timing and Synchronization model.
		// This is the actual simple duration, and not simply the dur attribute.
		//This value does not account for the effect of any time manipulations.
		double dur = m_pFilter->m_pElement->m_dur;// * m_pMedia->m_wavFormat->nSamplesPerSec;

		// pThis->m_simpleDur has accounted for autoReverse
		double dur_ = m_pFilter->m_pElement->m_simpleDur;// * m_pMedia->m_wavFormat->nSamplesPerSec;

		double dacc = acc*dur;
		double ddec = dec*dur;

		DWORD startSample = m_nSample;

		for (ULONG n = 0; n < nSamplesOut; n++)
		{
			//DWORD insample = n+startSample;

			//if (speed == 0) speed = 0 ??

			double tau = (startSample + n) * (1.0/wf.nSamplesPerSec);//tps - m_pCurrentInterval->m_begin;

			double taf;

			if (speed > 0) // i.e. if the local speed is forwards 
				taf = tau * speed;
			else //  i.e. if the local speed is backwards 
				taf = AD - tau * fabs(speed);

			double tsu = REMAINDER(taf, dur_);

		// Account for autoReverse behavior.
			double tsu_;

			if (m_pFilter->m_pElement->m_autoReverse->m_value->m_value != VARIANT_TRUE)
			{
				tsu_ = tsu;
			}
			else
			{
				if (tsu < dur)
					tsu_ = tsu;
				else
					//tsu_ = /*dur - (tsu - dur) =*/ 2*dur - tsu;
					tsu_ = 2*dur - tsu;
			}

		// Calculate filtered time (tsf)

		// Account for acceleration/deceleration
			double tsf;

			if (tsu_ < dacc)
			{
				double rt = r * (tsu_ / dacc);

				tsf = tsu_ * rt / 2;
			}
			else if (tsu_ > (dur - ddec))
			{
				double rt = r * (dur - tsu_) / ddec;

				double tdec =  tsu_ - (dur - ddec);
				double pd =  tdec / ddec;

				tsf = r * (dur - dacc / 2 - ddec + tdec * (2 - pd) / 2);
			}
			else
			{
				tsf = r * (tsu_ - dacc / 2);
			}

			//ULONG tsf = tsf;

			DWORD nSampleIn = tsf*wf.nSamplesPerSec;

			//ASSERT(nSample >= 0 && nSample < m_pMedia->m_nSamples);

			for (int nb = 0; nb < wf.nBlockAlign; nb++)
			{
				bufferOut[n*wf.nBlockAlign+nb] = bufferIn[nSampleIn*wf.nBlockAlign+nb];
			}
		}
	}
#if 0
	else
	{
		CopyMemory(buffer, pSampleIn->m_pointer, nbytes);
	}
#endif
#endif

	sampleOut->UnlockBits();

	ASSERT(0);
#if 0
	CComQIPtr<ILMemInputPin> memInput = m_pFilter->m_pOutput->m_connectedTo;
	memInput->Receive(sampleOut);
#endif

#if 0
	double timeStart;
	double timeEnd;
	pSample->GetTime(&timeStart, &timeEnd);

#if 0
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, timeStart/*streamTime*/, hEvent, NULL);

	WaitForSingleObject(hEvent, INFINITE);

	CloseHandle(hEvent);
#endif

	m_pSample = static_cast<CVideoSample*>(pSample);

//	m_pFilter->m_pMoviePlayer->m_cwnd.PostMessage(WM_USER+100, 0, 0);
#endif

//	m_pLock.Unlock();

	return Success_True;
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
// CMediaSource

void MediaSource::LoadFile(StringIn wszFileName)
{
	ASSERT(0);
#if 0
	ErrorCode hr = 0//m_filterGraph.CoCreateInstance(CLSID_LFilterGraph);
	if (SUCCEEDED(hr))
	{
		hr = m_filterGraph->LoadURL(wszFileName);
		if (SUCCEEDED(hr))
		{
			CComPtr<DispILStreams> streams;
			m_filterGraph->get_Streams(&streams);

			ASSERT(0);
#if 0
			if (TRUE)	// Video
			{
				CComPtr<ILMediaStream> stream;
				streams->Item(0, (DispILMediaStream**)&stream);
				if (stream)	// Connect video renderer
				{
					CComObject<CVideoFilter>::CreateInstance(&m_pVideoFilter);
					m_pVideoFilter->m_pMediaSource = this;
					m_filterGraph->AddFilter(m_pVideoFilter);

					CComPtr<ILPin> pin;
					stream->GetPin(&pin);
					m_filterGraph->ConnectDirect(pin, m_pVideoFilter->m_pInput, NULL);
				}
			}

			if (FALSE)	// Audio
			{
				CComPtr<DispILCollection> filters;
				m_filterGraph->get_Filters((IDispatch**)&filters);

				long nfilters;
				filters->get_Count(&nfilters);

				CComPtr<DispILFilter> filter;
				filters->Item(nfilters-1, (IUnknown**)&filter);
				CComPtr<ILBaseFilter> pfilter;
				filter->get_filter((IUnknown**)&pfilter);

				CComPtr<ILPin> outpin;
				pfilter->GetPin(1, &outpin);

			//
				CComObject<CAudioFilter>::CreateInstance(&m_pAudioFilter);
				m_pAudioFilter->m_pMediaSource = this;
				m_filterGraph->AddFilter(m_pAudioFilter);

				m_filterGraph->ConnectDirect(outpin, m_pAudioFilter->m_pInput, NULL);

			// Connect Audio renderer
				CComPtr<ILBaseFilter> audioRenderFilter;
				audioRenderFilter.CoCreateInstance(CLSID_LDSoundRender);

				CComPtr<ILPin> inpin;
				audioRenderFilter->GetPin(0, &inpin);

				m_filterGraph->AddFilter(audioRenderFilter);
				m_filterGraph->ConnectDirect(m_pAudioFilter->m_pOutput, inpin, NULL);
			}
#endif

		//	CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
		//	seeking->GetDuration(&m_duration);
#if 0
			CComQIPtr<ILVideo> video;
			m_movie->GetVideo(&video);
			if (video)
			{
				long width;
				long height;
				video->GetWidth(&width);
				video->GetHeight(&height);

				CComObject<CVideoSample>::CreateInstance(&m_pSample);

				m_pSample->m_pBitmap = new Gdiplus::Bitmap(width, height, PixelFormat24bppRGB);

				video->SetSample(m_pSample);
			}
#endif

#if 0
			CComQIPtr<ILAudio> audio;
			m_movie->GetAudio(&audio);
			if (audio)
			{
				audio->GetSamples(&m_nSamples);

				if (m_nSamples > 0)
				{
					m_wavFormat = (LPWAVEFORMATEX)GlobalAlloc(0, sizeof(WAVEFORMATEX));
					audio->GetFormat(m_wavFormat);

					m_wavBuffer = (LPSTR)GlobalAlloc(0, (DWORD)(m_nSamples*m_wavFormat->nBlockAlign));
					if (m_wavBuffer)
					{
						LPSTR buffer = m_wavBuffer;

						int i = 0;
						ULONG chunksamples;
						while (audio->GetChunkSize(i, &chunksamples) == S_OK)
						{
							audio->ReadChunk(i, buffer, chunksamples);

							buffer += chunksamples*m_wavFormat->nBlockAlign;

							i++;
						}
					}
				}

#if 0
				m_wavfmt.nAvgBytesPerSec = m_wavfmt.nSamplesPerSec * m_wavfmt.nBlockAlign;

				ULONG nSamples;
				audio->GetChunkSize(0, &nSamples);

				{
					//PCMWAVEFORMAT pcmwf; 
					DSBUFFERDESC dsbdesc; 
					ErrorCode hr; 
					
					// Set up wave format structure. 
					//memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT)); 
					//pcmwf = *(PCMWAVEFORMAT*)&m_wavfmt;
					/*
					pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM; 
					pcmwf.wf.nChannels = m_wavfmt.nChannels; 
					pcmwf.wf.nSamplesPerSec = 22050; 
					pcmwf.wf.nBlockAlign = 4; 
					pcmwf.wf.nAvgBytesPerSec = 
						pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign; 
					pcmwf.wBitsPerSample = 16; 
					*/
					
					// Set up DSBUFFERDESC structure. 
					
					memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
					dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
					dsbdesc.dwFlags = 
						DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY; 
					
					dsbdesc.dwBufferBytes = nSamples * m_wavfmt.nBlockAlign;//3 * pcmwf.wf.nAvgBytesPerSec; 
					dsbdesc.lpwfxFormat = &m_wavfmt;//(LPWAVEFORMATEX)&pcmwf; 
					
					// Create buffer. 
					
					CComPtr<IDirectSoundBuffer> dsBuffer;
					hr = m_ds8->CreateSoundBuffer(&dsbdesc, &dsBuffer, NULL); 
					m_dsBuffer8 = dsBuffer;
					if (SUCCEEDED(hr))
					{ 
						LPSTR pbuffer;
						DWORD dwbuffer;
						if (SUCCEEDED(m_dsBuffer8->Lock(0, nSamples * m_wavfmt.nBlockAlign, (void**)&pbuffer, &dwbuffer, NULL, NULL, 0)))
						{
							audio->ReadChunk(0, pbuffer, nSamples);

							m_dsBuffer8->Unlock(0, nSamples * m_wavfmt.nBlockAlign, NULL, 0);
						}

						// IDirectSoundBuffer interface is in *lplpDsb. 
						// Use QueryInterface to obtain IDirectSoundBuffer8.
						//return TRUE; 
					} 
					else 
					{ 
						ASSERT(0);
						/*
						// Failed. 
						*lplpDsb = NULL; 
						return FALSE; 
						*/
					} 

				}

			// We load the first chunk, even before starting playing, so there's no delay if and when we should play
#endif
			}
#endif
		}
	}

	return hr;
#endif
}

void MediaSource::Seek(double simpleTime)
{
	/*
	if (m_pSrcBitmap)
	{
		delete m_pSrcBitmap;
		m_pSrcBitmap = NULL;
	}
	*/

//	m_mpegfile->Seek(simpleTime);

	ASSERT(0);
#if 0
	CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
	seeking->Seek(simpleTime*LTIME_SCALE);
#endif
}

#if 0
ErrorCode MediaSource::VideoFilter::GetBitmap(Graphics::Bitmap** pVal)
{
	*pVal = NULL;

	if (m_pInput->m_pSample)
	{
		*pVal = m_pInput->m_pSample->m_pBitmap;
	}
	return Success;
}
#endif

}	// Web
}	// System
