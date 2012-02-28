#include "stdafx.h"
#include "IFF.h"
//#include "IFFDecoder.h"

#include "IFFForm8SVX.h"

namespace System
{
namespace MediaShow
{

////////////////////////////////////////////
// IFFForm8SVX

IFFForm8SVX::IFFForm8SVX()
{
	// m_file = NULL;
	m_pInputPin = NULL;

	m_bodyPos = 0;
	m_bodySize = 0;

	m_nSamples = 0;
	m_foundVHDR = false;

	m_pInputPin = new CInputPin;
	m_pInputPin->m_pFilter = this;
	AddPin(m_pInputPin);
}

IFFRESULT IFFForm8SVX::Read8SVXForm()
{
	IFFRESULT	iffresult;

	IFFCHUNK	ck;

	while (m_pInputPin->m_pIFFParser->IFFDescendChunk(&ck) == IFF_OK)
	{
		switch (ck.ckID)
		{
			case ID_VHDR:
			{
				m_foundVHDR = true;
				VoiceHeader	*vhdr = &m_vhdr;

				if ((iffresult = m_pInputPin->m_pIFFParser->IFFReadChunkBytes(vhdr, sizeof(VoiceHeader))) == sizeof(VoiceHeader))
				{
					vhdr->vh_SamplesPerSec = BigEndian16(vhdr->vh_SamplesPerSec);
				}
				else iffresult = IFFERR_READWRITE;
			}
			break;

			case ID_BODY:
			{
				if (m_foundVHDR)
				{
					VoiceHeader	*vhdr = &m_vhdr;

					if (vhdr->vh_sCompression != 0)
					{
						char errorMsg[256];
						sprintf_s(errorMsg, "Unsupported 8SVX compression %d", vhdr->vh_sCompression);
						MessageBoxA(NULL, errorMsg, "IFF/8SVX", MB_OK);
						iffresult = IFFERR_COMPRESS;
					}
					else
					{
						m_nSamples = ck.ckSize;

					//	m_svxOffset = g->GetFilePos(g->file);

						ULONGLONG pos;
						pos = m_pInputPin->m_pIFFParser->SetFilePos(0, System::IO::STREAM_SEEK_CUR);

						LONGLONG count = 0;
						while (count < m_nSamples)
						{
							CAudioChunk* pChunk = new CAudioChunk;

							pChunk->m_soundDataOffset = pos + count*1;//nbytesPerSample;

							pChunk->m_soundDataLength = 2000;
							if (count+pChunk->m_soundDataLength > m_nSamples)
								pChunk->m_soundDataLength = (ULONG)(m_nSamples - count);

							count += pChunk->m_soundDataLength;

							m_chunks.push_back(pChunk);
						}
					}
				}
				else
					iffresult = -2;
			}
			break;
		}

		if (iffresult < 0) break;

		iffresult = m_pInputPin->m_pIFFParser->IFFAscendChunk(&ck);
	}

	return iffresult;
}

ErrorCode IFFForm8SVX::Parse()
{
	IFFRESULT iffresult = Read8SVXForm();
	//if (iffresult 
	return Success;
}

#if 0
STDMETHODIMP IFFForm8SVX::GetDuration(double* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = (double)m_nSamples / m_vhdr.vh_SamplesPerSec;
	return Success;
}

STDMETHODIMP IFFForm8SVX::Seek(double seconds)
{
	return Success;
}
#endif

#if 0	// Had this
// ILAudio
STDMETHODIMP IFFForm8SVX::GetSamples(LONGLONG *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_nSamples;
	return Success;
}

STDMETHODIMP IFFForm8SVX::GetFormat(WAVEFORMATEX *pVal)
{
	if (pVal == NULL) return E_POINTER;

	pVal->wFormatTag = WAVE_FORMAT_PCM;
	pVal->nChannels = 1;
	pVal->wBitsPerSample = 8;
	pVal->nSamplesPerSec = m_vhdr.vh_SamplesPerSec;
	pVal->nBlockAlign = 1;
	pVal->cbSize = 0;

	return Success;
}

STDMETHODIMP IFFForm8SVX::GetChunkSize(long nchunk, ULONG* pVal)
{
	if (nchunk < m_chunks.GetCount())
	{
		CAudioChunk* f = (CAudioChunk*)m_chunks.GetAt(m_chunks.FindIndex(nchunk));

	// Number of samples in chunk
		*pVal = f->m_soundDataLength / 1;

		return Success;
	}
	else
		return S_FALSE;
}

STDMETHODIMP IFFForm8SVX::ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples)
{
	if (nchunk < m_chunks.GetCount())
	{
		CAudioChunk* f = (CAudioChunk*)m_chunks.GetAt(m_chunks.FindIndex(nchunk));

		LARGE_INTEGER li;
		li.QuadPart = f->m_soundDataOffset;
		m_pInputPin->m_pIFFParser->SetFilePos(li, STREAM_SEEK_SET);

		DWORD nbytes = nsamples*1;
		m_pInputPin->m_pIFFParser->IFFReadChunkBytes(buffer, nbytes);

	// Make unsigned
		char *p = (char*)buffer;
		int len = nbytes;

		while (len--)
		{
			*p = *p + 128;
			p++;
		}
	}

	return Success;
}
#endif

}	// MediaShow
}
