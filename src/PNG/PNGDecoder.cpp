#include "stdafx.h"
#include "PNG.h"
#include "PNGDecoder.h"

namespace System
{
namespace MediaShow
{

ErrorCode CPNGDecoder::Open()
{
	ULONG nRead;

	uint32 format;
	nRead = m_stream->Read(&format, 4);
	if (nRead != 4) return Error;
	if (format != 0x474e5089/*PNG*/ && format != 0x474e4a8b/*JNG*/)
	{
		return Error;
	}

	uint32 value;
	nRead = m_stream->Read(&value, 4);
	if (nRead != 4) return Error;
	if (value != 0x0a1a0a0d) return Error;

	if (format == 0x474e5089)
	{
		m_png = new Imaging::PNGDecoder;
	}
	else
	{
		m_png = new Imaging::JNGDecoder;
	}

	m_png->SetStream(m_stream);
	m_png->ReadHeader();
	m_png->CreateImage();

	return Success;
}

static MSWindows::DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
//	ErrorCode hr;

	CPNGDecoder::OutputPin* p = (CPNGDecoder::OutputPin*)lpParameter;

	IMediaSample* sample;
	p->m_pAllocator->GetBuffer(0, &sample);
	if (sample)
	{
		LSampleData sampledata;
		sample->LockBits(&sampledata);

		p->GetFilter()->m_png->GetImage()->StartScan();

		LONG height = p->GetFilter()->m_png->GetHeight();

		for (LONG row = 0; row < height; row++)
		{
			uint8* dest = sampledata.idata + sampledata.rowbytes*row;

			p->GetFilter()->m_png->GetImage()->ReadScanline(dest);
		}

		sample->UnlockBits();

		p->m_pInputPin->Receive(sample);
	}

	p->ConnectedTo()->EndOfStream();

	return 0;
}

ErrorCode CPNGDecoder::OutputPin::Run(LONGLONG tStart)
{
	m_pFilter->m_tStart = tStart;

	ASSERT(0);
#if 0
	DWORD threadId;
	/*m_hThread =*/ CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(CPNGDecoder::OutputPin*)this, 0, &threadId);
#endif
	return 0;
}

}	// Media
}
