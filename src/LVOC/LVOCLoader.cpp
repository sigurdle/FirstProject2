#include "stdafx.h"
#include "LVOC.h"
#include "LVOCLoader.h"

namespace System
{
namespace MediaShow
{

// 43726561 74697665 20566F69 63652046 696C65 = "Creative Voice File"

/////////////////////////////////////////////////////////////////////////////
// CLVOCLoader

CLVOCLoader::CInputPin::CInputPin() : BasePinImpl(PINDIR_INPUT)
{
}

ErrorCode CLVOCLoader::CInputPin::CheckConnect(IPin* pPin)
{
	// Call base class first
	ErrorCode hr = BasePinImpl::CheckConnect(pPin);
	if (hr < 0) return hr;

	IByteData* stream = dynamic_cast<IByteData*>(pPin);
	if (stream == NULL) return Error_NoInterface;

	m_stream = new ByteStreamWrapper(stream);

	return Success;
}

void CLVOCLoader::CInputPin::BreakConnect()
{
	// Release what we obtained in CheckConnect
	m_stream = NULL;
}

ErrorCode CLVOCLoader::CInputPin::CheckMediaType(MediaType* mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Stream)
		return Error;

	return Success;
}

ErrorCode CLVOCLoader::CInputPin::CompleteConnect(IPin *pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);	// Call base class
	if (hr < 0) return hr;

	return Success;
}

CLVOCLoader::COutputPin::COutputPin()
{
//	m_pFilter = NULL;

	m_threadId = 0;
	m_hThread = NULL;
}

ErrorCode CLVOCLoader::COutputPin::CheckMediaType(MediaType* mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Audio)
		return Error_Failed;

	return Success;
}

ErrorCode_Bool CLVOCLoader::COutputPin::GetMediaType(int iPosition, MediaType** pMediaType)
{
	if (iPosition == 0)
	{
		//mediaType.Create(sizeof(WAVEFORMATEX)+GetFilter()->m_voc->m_wfx.cbSize);

		WaveFormat* wf = new WaveFormat;
		*wf->wf = GetFilter()->m_voc->m_wfx;//, sizeof(WAVEFORMATEX)+GetFilter()->m_voc->m_wfx.cbSize);

		MediaType* mediaType = new MediaType(LMEDIATYPE_Audio, GUID_NULL, GUID_NULL, wf);
	//	mediaType.SetMajorType(LMEDIATYPE_Audio);
		//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
	//	mediaType.SetFormat(wf);

		*pMediaType = mediaType;//.Detach();

		return Success_True;
	}
	else
	{
		pMediaType = NULL;
		return Success_False;
	}
}

//static
DWORD WINAPI CLVOCLoader::COutputPin::AudioRunProc(LPVOID lpParameter)
{
	COutputPin* p = (COutputPin*)lpParameter;

	ErrorCode hr = Success;

	LONGLONG nSamples = 0;

	ASSERT(0);
#if 0
	for (int i = 0; i < p->m_pFilter->m_pInputPin->m_chunks.GetCount(); i++)
	{
	//	UPOSITION pos = p->m_pFilter->m_pInputPin->m_chunks.FindIndex(i);
	//	CChunk* pChunk = (CChunk*)p->m_pFilter->m_pInputPin->m_chunks.GetAt(pos);
	//	p->m_pFilter->m_pInputPin->m_stream->Seek(pChunk->m_fileOffset, STREAM_SEEK_SET);

		ILMediaSample* sample;

		if (p->m_pFilter->m_voc->m_compression == 4)	// PCM
		{
			DWORD nBytesToRead = pChunk->m_nSamples * p->m_wfx.nBlockAlign;

			hr = p->m_pAllocator->GetBuffer(nBytesToRead, &sample);
			if (FAILED(hr))
				break;

			LONGLONG timeStart = LTIME_SCALE * nSamples / p->m_wfx.nSamplesPerSec;
			nSamples += pChunk->m_nSamples;
			LONGLONG timeEnd = LTIME_SCALE * nSamples / p->m_wfx.nSamplesPerSec;

			sample->SetTime(&timeStart, &timeEnd);

			LSampleData sampledata;
			if (SUCCEEDED(sample->LockBits(&sampledata)))
			{
				/*
				LARGE_INTEGER li;
				li.QuadPart = pChunk->m_fileOffset;
				m_stream->Seek(li, STREAM_SEEK_SET, NULL);
				*/

				ULONG nRead;
				nRead = p->m_pFilter->m_pInputPin->m_stream->Read(sampledata.idata, nBytesToRead);
				ATLASSERT(nBytesToRead == nRead);

				hr = S_OK;

				sample->UnlockBits();
			}
		}
		else	// u-Law / A-Law
		{
			ATLASSERT(0);
		}

		//LONGLONG sampleDuration = LTIME_SCALE * p->m_pAVIStream->m_aviStreamHeader.dwScale / p->m_pAVIStream->m_aviStreamHeader.dwRate;

		//LONGLONG timeStart = sampleDuration*i;//p->m_currentFrame;
		//LONGLONG timeEnd = timeStart+sampleDuration;

		//sample->SetTime(&timeStart, &timeEnd);

		hr = p->m_pInputPin->Receive(sample);
#if 0
		if (hr != S_OK)	// Stop on either failure or S_FALSE
			break;
#endif
	}
#endif

#if 0
	if (SUCCEEDED(hr))
#endif
		p->m_connectedTo->EndOfStream();

//	CoUninitialize();

	return 0;
}

ErrorCode CLVOCLoader::COutputPin::Run(LONGLONG tStart)
{
	ASSERT(0);
#if 0
	m_hThread = CreateThread(NULL, NULL, AudioRunProc, (LPVOID)(COutputPin*)this, 0, &m_threadId);
	if (m_hThread == NULL)
		return E_FAIL;
#endif
	return Success;
}

}	// Media
}
