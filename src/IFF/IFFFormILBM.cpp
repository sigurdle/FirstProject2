#include "stdafx.h"
#include "IFF.h"
//#include "IFFDecoder.h"

#include "IFFFormILBM.h"

namespace System
{
namespace MediaShow
{

////////////////////////////////////////////////////////////////////////
// IFFFormILBM::COutputPin

IFFFormILBM::COutputPin::COutputPin()
{
}

ErrorCode IFFFormILBM::COutputPin::CheckMediaType(MediaType* mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Video)
		return Error;

	return Success;
}

ErrorCode IFFFormILBM::COutputPin::ReadImage(IMediaSample* pSample)
{
	GetFilter()->m_pInputPin->m_pIFFParser->SetFilePos(GetFilter()->m_bodyPos, System::IO::STREAM_SEEK_SET);

	uint8* planes = new uint8[m_planeSize*m_bmhd.bmh_Planes];
	if (planes)
	{
		for (int i = 0; i < m_bmhd.bmh_Planes; i++)
		{
			m_planes0[i] = planes+m_planeSize*i;
		}

		ReadBODY(GetFilter()->m_bodySize);

		PlanarToChunky(m_planes0, pSample);

		delete[] planes;

		return Success;
	}
	else
		return Error;
}

////////////////////////////////////////////////////////////////////////
// IFFFormILBM

IFFFormILBM::CInputPin::CInputPin() : BasePinImpl(PINDIR_INPUT)
{
}

ErrorCode IFFFormILBM::CInputPin::CheckConnect(IPin* pPin)
{
	// Call base class first
	ErrorCode hr = BasePinImpl::CheckConnect(pPin);
	if (hr < 0) return hr;

	IByteData* stream = dynamic_cast<IByteData*>(pPin);
	if (stream == NULL) return Error_NoInterface;

	m_stream = new ByteStreamWrapper(stream);

	return Success;
}

void IFFFormILBM::CInputPin::BreakConnect()
{
	// Release what we obtained in CheckConnect
	m_stream = NULL;
}

ErrorCode IFFFormILBM::CInputPin::CheckMediaType(MediaType * mt)
{
	if (mt->GetMajorType() != LMEDIATYPE_Stream)
		return Error;

	return Success;
}

ErrorCode IFFFormILBM::CInputPin::CompleteConnect(IPin *pPin)
{
#if 0
	m_connectedTo = pConnector;
	m_pIFFParser = m_connectedTo;
	m_pFilter->m_pImage->m_pIFFParser = m_pIFFParser;
	if (m_pIFFParser == NULL) return Error;
#endif
	m_pIFFParser = new IFFParser(m_stream);
	GetFilter()->m_pImage->m_pIFFParser = m_pIFFParser;

	IFFCHUNK	formck;// = *(LPIFFCHUNK)r->firstBytes;
	m_pIFFParser->IFFDescendChunk(&formck);

	if (formck.ckID != ID_FORM)
	{
		return Error;
	}

	ErrorCode hr;

	if (formck.grpID == ID_ILBM)
	{
		hr = GetFilter()->Parse();
	}
	else
		hr = Error;

#if 0
	if (SUCCEEDED(hr))
	{
		CComObject<CMediaType>::CreateInstance(&m_pFilter->m_pImage->m_pMediaType);
		m_pFilter->m_pImage->m_pMediaType->AddRef();
		m_pFilter->m_pImage->m_pMediaType->m_pILBM = m_pFilter->m_pImage;

		CComObject<CMediaType::CPalette>::CreateInstance(&m_pFilter->m_pImage->m_pMediaType->m_pPalette);
		m_pFilter->m_pImage->m_pMediaType->m_pPalette->AddRef();
		m_pFilter->m_pImage->m_pMediaType->m_pPalette->m_pMediaType = m_pFilter->m_pImage->m_pMediaType;
	}
#endif

	return hr;
}

// virtual
ErrorCode IFFFormILBM::COutputPin::GetMediaType(int iPosition, MediaType** pMediaType)
{
	if (iPosition == 0)
	{
	//	mediaType.Create(sizeof(LVIDEOINFOHEADER2)+m_numcolors*sizeof(RGBQUAD));

		VideoInfoHeader* vih = new VideoInfoHeader(m_numcolors);//((LVIDEOINFOHEADER2*)mediaType.pbFormat);

		vih->vih->bmiHeader.biSize = sizeof(BitmapInfoHeader);
		vih->vih->bmiHeader.biPlanes = 1;
		vih->vih->bmiHeader.biBitCount = 24;//m_pFilter->m_pInputPin->m_bitcount;
		vih->vih->bmiHeader.biWidth = m_bmhd.bmh_Width;
		vih->vih->bmiHeader.biHeight = m_bmhd.bmh_Height;
		//memcpy(((BITMAPINFO*)&vih->bmiHeader)->bmiColors, m_pFilter->m_pInputPin->m_colors, m_pFilter->m_pInputPin->m_numColors*sizeof(RGBQUAD));

		RGBQuad* colors = ((BitmapInfo*)&vih->vih->bmiHeader)->bmiColors;

		for (int i = 0; i < m_numcolors; i++)
		{
			colors[i].rgbRed = m_colors[i].Red;
			colors[i].rgbGreen = m_colors[i].Green;
			colors[i].rgbBlue = m_colors[i].Blue;
		}

		MediaType* mediaType = new MediaType(LMEDIATYPE_Video, GUID_NULL, GUID_NULL, vih);
	//	mediaType.SetMajorType(LMEDIATYPE_Video);
	//	mediaType.SetFormat(vih);
		//mediaType.subtype = GUID_NULL;//FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

		*pMediaType = mediaType;

		return Success;
	}
	else
	{
		*pMediaType = NULL;
		return Success_False;
	}
}

IFFFormILBM::IFFFormILBM()
{
	m_pInputPin = NULL;

	m_bodyPos = 0;
	m_bodySize = 0;

	m_pInputPin = new CInputPin;
	m_pInputPin->m_pFilter = this;
	m_pInputPin->m_id = WSTR("Stream Input");
	AddPin(m_pInputPin);

	m_pImage = new COutputPin;
	m_pImage->m_pFilter = this;
	m_pImage->m_id = WSTR("Image Output");
	AddPin(m_pImage);
}

IFFFormILBM::~IFFFormILBM()
{
	m_pInputPin = NULL;
	m_pImage = NULL;
}

IFFRESULT IFFFormILBM::ReadILBMForm(bool bInitRead)
{
	IFFRESULT iffresult;

	IFFCHUNK	ck;

	while ((iffresult = m_pInputPin->m_pIFFParser->IFFDescendChunk(&ck)) == IFF_OK)
	{
		switch (ck.ckID)
		{
			case ID_BMHD:
			{
				iffresult = m_pImage->BMHDChunk(&ck);
			}
			break;

			case ID_CMAP:
			{
				if (bInitRead)
				{
					iffresult = m_pImage->CMAPChunk(&ck);
				}
			}
			break;

			case ID_CAMG:
			{
				if (bInitRead)
				{
					iffresult = m_pImage->CAMGChunk(&ck);
				}
			}
			break;

			case ID_BODY:
			{
				if (bInitRead)
				{
					m_bodyPos = m_pInputPin->m_pIFFParser->SetFilePos(0, System::IO::STREAM_SEEK_CUR);
					m_bodySize = ck.ckSize;

					m_pImage->BODYChunk(&ck);
				}
#if 0
				else	// Read Frame
				{
					DWORD	camg = m_camg;
					BitMapHeader	*bmhd = &m_bmhd;

					int numcolors = m_numcolors;
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

					iffresult = ReadBODY(ck.ckSize);	// Reads into m_planes[0]
				}
#endif
			}
			break;


			default:
				TRACE("%4.4s\n", &ck.ckID);
		}

		if (iffresult < 0) break;

		iffresult = m_pInputPin->m_pIFFParser->IFFAscendChunk(&ck);
	}

	return iffresult;
}

ErrorCode IFFFormILBM::Parse()
{
	ReadILBMForm(true);
	return Success;
}

#if WIN32
static MSWindows::DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
	ErrorCode hr;

	IFFFormILBM::COutputPin* p = (IFFFormILBM::COutputPin*)lpParameter;

	IMediaSample* sample;
	p->m_pAllocator->GetBuffer(0, &sample);
	if (sample)
	{
		p->ReadImage(sample);

		p->m_pInputPin->Receive(sample);
	}

	p->ConnectedTo()->EndOfStream();

	return 0;
}
#endif

// virtual
ErrorCode IFFFormILBM::COutputPin::Run(LONGLONG tStart)
{
#if WIN32
	MSWindows::DWORD threadId;
	ASSERT(0);
#if 0
	/*m_hThread =*/ CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(IFFFormILBM::COutputPin*)this, 0, &threadId);
#endif

#endif

	return Success;
}

}	// MediaShow
}
