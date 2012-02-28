// LWAVEParser.cpp : Implementation of CLWAVEParser
#include "stdafx.h"
#include "LAVI.h"
#include "LWAVEParser.h"

namespace System
{
namespace Media
{

/////////////////////////////////////////////////////////////////////////////
// CLWAVEParser

ErrorCode CLWAVEParser::CInputPin::CompleteConnect(IPin *pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);	// Call base class
	if (hr < 0) return hr;

	Riff::CChunk ck;
	ck.Descend(m_stream);

	if (ck.m_id == mmioFOURCC('R','I','F','F'))
	{
		if (ck.m_grpid == mmioFOURCC('W','A','V','E'))
		{
			return m_pFilter->ReadWAVE();
		}
		else
			return Error;	// Unknown formtype
	}
	else
		return Error;	// Not a RIFF file

// Don't ascend out of this one, as that would require a Seek to the end of this chunk //	ck.Ascend(m_pFilter->m_stream);

	return -1;
}

// static
MSWindows::DWORD WINAPI CLWAVEParser::COutputPin::AudioRunProc(LPVOID lpParameter)
{
//	CoInitialize(NULL);//Ex(NULL, COINIT_MULTITHREADED);

	CLWAVEParser::COutputPin* p = (CLWAVEParser::COutputPin*)lpParameter;

#if 0
	ErrorCode hr = S_OK;

	for (int i = 0; i < p->m_pAVIStream->m_aviStreamHeader.dwLength; i++)
	{
		CComPtr<ILMediaSample> sample;
		hr = p->m_pAVIStream->GetSample(i, &sample);
		if (FAILED(hr))
			break;

		if (sample == NULL)
			break;

		ATLASSERT(sample);

		LONGLONG sampleDuration = LTIME_SCALE * p->m_pAVIStream->m_aviStreamHeader.dwScale / p->m_pAVIStream->m_aviStreamHeader.dwRate;

		LONGLONG timeStart = sampleDuration*i;//p->m_currentFrame;
		LONGLONG timeEnd = timeStart+sampleDuration;

		sample->SetTime(&timeStart, &timeEnd);

		hr = p->m_pInputPin->Receive(sample);
		if (FAILED(hr))
			break;
	}

	if (SUCCEEDED(hr))
		p->m_connectedTo->EndOfStream();	

#endif
//	CoUninitialize();

	return 0;
}

ErrorCode CLWAVEParser::ReadWAVE()
{
	ULONG nRead;

	while (1)
	{
		Riff::CChunk ck;
		if (ck.Descend(m_pInputPin->m_stream) != Success)
			break;

		if (ck.m_id == mmioFOURCC('f','m','t',' '))
		{
			if (ck.m_size < sizeof(MSWindows::WAVEFORMAT))
			{
				TRACE("fmt chunk is too small");
				return Error;
			}

			/*
			m_fmtsize = ck.m_size;
			m_fmtbuffer = malloc(m_fmtsize);
			if (m_fmtbuffer == NULL)
			{
				return E_OUTOFMEMORY;
			}

			m_stream->Read(m_fmtbuffer, m_fmtsize, &nRead);
			*/
		}
		else if (ck.m_id == mmioFOURCC('d','a','t','a'))
		{
			MessageBeep(-1);
		}

		ck.Ascend(m_pInputPin->m_stream);
	}

	return Success;
}

}	// Media
}
