#include "stdafx.h"
#include "LJPEG.h"
#include "LJPEGDecoder.h"

namespace System
{
namespace MediaShow
{

ErrorCode JPEGDecoder::CInputPin::CompleteConnect(IPin *pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);	// Call base class
	if (hr < 0) return hr;

	GetFilter()->m_jfif = new Imaging::JPEGDecoder(m_stream);
	if (GetFilter()->m_jfif->Read() != 0)
		return Error;

	return Success;
}

/*
ErrorCode JPEGDecoder::CInputPin::ReadHeader()
{



#if 0
	if ((CbH>YH)||(CrH>YH)) exit_func("Vertical sampling factor for Y should be >= sampling factor for Cb,Cr");
	if ((CbV>YV)||(CrV>YV)) exit_func("Horizontal sampling factor for Y should be >= sampling factor for Cb,Cr");
	
	if ((CbH>=2)||(CbV>=2)) exit_func("Cb sampling factors should be = 1");
	if ((CrV>=2)||(CrV>=2)) exit_func("Cr sampling factors should be = 1");
	
	// Restricting sampling factors for Y,Cb,Cr should give us 4 possible cases for sampling factors
	// YHxYV,CbHxCbV,CrHxCrV: 2x2,1x1,1x1;  1x2,1x1,1x1; 2x1,1x1,1x1;
	// and 1x1,1x1,1x1 = no upsampling needed
	
	Hmax=YH,Vmax=YV;
	if ( m_imageWidth%(Hmax*8)==0) X_round= m_imageWidth; // X_round = Multiple of Hmax*8
	else X_round=(m_imageWidth/(Hmax*8)+1)*(Hmax*8);
	if ( m_imageHeight%(Vmax*8)==0) Y_round=m_imageHeight; // Y_round = Multiple of Vmax*8
	else Y_round=(m_imageHeight/(Vmax*8)+1)*(Vmax*8);
	
	im_buffer=(BYTE *)malloc(X_round*Y_round*4);
	if (im_buffer==NULL) exit_func("Not enough memory for storing the JPEG image");
#endif
	return S_OK;
}
*/

ErrorCode JPEGDecoder::CInputPin::ReadImage(IMediaSample* sample)
{
	LSampleData sampledata;
	if (sample->LockBits(&sampledata) >= 0)
	{
		GetFilter()->m_jfif->StartScans();

		int height = GetFilter()->m_jfif->GetHeight();

		for (int y = 0; y < height; y++)
		{
			GetFilter()->m_jfif->NextScanline();

			uint8* dest = sampledata.idata + sampledata.rowbytes*y;

			if (true)
			{
				GetFilter()->m_jfif->CopyScanline(dest, dest+1, dest+2, 3);
			}
			else
			{
				GetFilter()->m_jfif->CopyScanlineGray(dest, 1);
			}
		}

		GetFilter()->m_jfif->EndScans();

		sample->UnlockBits();
	}

	return Success;
}

ErrorCode JPEGDecoder::COutputPin::GetMediaType(int iPosition, MediaType** pMediaType)
{
	if (iPosition == 0)
	{
		VideoInfoHeader* vih = new VideoInfoHeader;

		vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
		vih->vih->bmiHeader.biPlanes = 1;
		vih->vih->bmiHeader.biBitCount = GetFilter()->m_jfif->GetComponents()*8;//m_pFilter->m_pInputPin->m_bitcount;
		vih->vih->bmiHeader.biWidth = GetFilter()->m_jfif->GetWidth();
		vih->vih->bmiHeader.biHeight = GetFilter()->m_jfif->GetHeight();
		//memcpy(((BITMAPINFO*)&vih->bmiHeader)->bmiColors, m_pFilter->m_pInputPin->m_colors, m_pFilter->m_pInputPin->m_numColors*sizeof(RGBQUAD));

		MediaType* mediaType = new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
	//	mediaType.SetMajorType(LMEDIATYPE_Video);
		//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);
	//	mediaType.SetFormat(vih);

		*pMediaType = mediaType;

		return Success_True;
	}
	else
	{
//		*pMediaType = NULL;
		return Success_False;
	}
}

static MSWindows::DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
//	ErrorCode hr;

//	EnterCriticalSection(&pFilter->m_pLock);

	JPEGDecoder::COutputPin* p = (JPEGDecoder::COutputPin*)lpParameter;

	IMediaSample* sample;
	p->m_pAllocator->GetBuffer(0, &sample);
	if (sample)
	{
		//sample->SetTime(&tStart, &tStart);

		p->GetFilter()->m_pInputPin->ReadImage(sample);

		p->m_pInputPin->Receive(sample);

		sample->Release();

		p->ConnectedTo()->EndOfStream();
	}

	return 0;
}

ErrorCode JPEGDecoder::COutputPin::Run(LONGLONG tStart)
{
	//m_pFilter->m_tStart = tStart;

	MSWindows::DWORD threadId;
	ASSERT(0);
#if 0
	/*m_hThread =*/ MSWindows::CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(JPEGDecoder::COutputPin*)this, 0, &threadId);
#endif

	return 0;
}

}	// Media
}
