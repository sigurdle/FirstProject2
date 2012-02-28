// AUDecoder.cpp : Implementation of CAUDecoder
#include "stdafx.h"
#include "SunAU.h"
#include "AUDecoder.h"

static short mulaw[256]=
{
  -8031,-7775,-7519,-7263,-7007,-6751,-6495,-6239,-5983,-5727,
  -5471,-5215,-4959,-4703,-4447,-4191,-3999,-3871,-3743,-3615,
  -3487,-3359,-3231,-3103,-2975,-2847,-2719,-2591,-2463,-2335,
  -2207,-2079,-1983,-1919,-1855,-1791,-1727,-1663,-1599,-1535,
  -1471,-1407,-1343,-1279,-1215,-1151,-1087,-1023,-975, -943,
  -911, -879, -847, -815, -783, -751, -719, -687, -655, -623,
  -591, -559, -527, -495, -471, -455, -439, -423, -407, -391,
  -375, -359, -343, -327, -311, -295, -279, -263, -247, -231,
  -219, -211, -203, -195, -187, -179, -171, -163, -155, -147,
  -139, -131, -123, -115, -107, -99,  -93,  -89,  -85,  -81,
  -77,  -73,  -69,  -65,  -61,  -57,  -53,  -49,  -45,  -41,
  -37,  -33,  -30,  -28,  -26,  -24,  -22,  -20,  -18,  -16,
  -14,  -12,  -10,  -8,   -6,   -4,   -2,   0,   8031,  7775,
  7519, 7263, 7007, 6751, 6495, 6239, 5983, 5727, 5471, 5215,
  4959, 4703, 4447, 4191, 3999, 3871, 3743, 3615, 3487, 3359,
  3231, 3103, 2975, 2847, 2719, 2591, 2463, 2335, 2207, 2079,
  1983, 1919, 1855, 1791, 1727, 1663, 1599, 1535, 1471, 1407, 1343, 1279, 1215, 1151, 1087, 1023, 
  975,  943,  911,  879,  847,  815,  783,  751,  719,  687,  655,  623,  591,  559,  527,  495,  
  471,  455,  439,  423,  407,  391,  375,  359,  343,  327,  311,  295,  279,  263,  247,  231,   // <480, =207- (sig-224)/16  
  219,  211,  203,  195,  187,  179,  171,  163,  155,  147,  139,  131,  123,  115,  107,  99,    // <224, =223- (sig-96)/8
  93,   89,   85,   81,   77,   73,   69,   65,   61,   57,   53,   49,   45,   41,   37,   33,    // <96,  =239- (sig-32)/4    for 224-239
  30,   28,   26,   24,   22,   20,   18,   16,   14,   12,   10,   8,    6,    4,    2,    0    // <32,  =255-sig/2          for 240-255
};

static short alaw[256]=
{-688,-656,-752,-720,-560,-528,-624,-592,-944,-912,-1008,-976,
-816,-784,-880,-848,-344,-328,-376,-360,-280,-264,-312,-296,
-472,-456,-504,-488,-408,-392,-440,-424,-2752,-2624,-3008,-2880,
-2240,-2112,-2496,-2368,-3776,-3648,-4032,-3904,-3264,-3136,
-3520,-3392,-1376,-1312,-1504,-1440,-1120,-1056,-1248,-1184,
-1888,-1824,-2016,-1952,-1632,-1568,-1760,-1696,-43,-41,-47,-45,
-35,-33,-39,-37,-59,-57,-63,-61,-51,-49,-55,-53,-11,-9,-15,
-13,-3,-1,-7,-5,-27,-25,-31,-29,-19,-17,-23,-21,-172,-164,
-188,-180,-140,-132,-156,-148,-236,-228,-252,-244,-204,-196,
-220,-212,-86,-82,-94,-90,-70,-66,-78,-74,-118,-114,-126,-122,
-102,-98,-110,-106,688,656,752,720,560,528,624,592,944,912,
1008,976,816,784,880,848,344,328,376,360,280,264,312,296,472,
456,504,488,408,392,440,424,2752,2624,3008,2880,2240,2112,
2496,2368,3776,3648,4032,3904,3264,3136,3520,3392,1376,1312,
1504,1440,1120,1056,1248,1184,1888,1824,2016,1952,1632,1568,
1760,1696,43,41,47,45,35,33,39,37,59,57,63,61,51,49,55,53,
11,9,15,13,3,1,7,5,27,25,31,29,19,17,23,21,172,164,188,
180,140,132,156,148,236,228,252,244,204,196,220,212,
86,82,94,90,70,66,78,74,118,114,126,122,102,98,110,106};

/////////////////////////////////////////////////////////////////////////////
// CAUDecoder::CAudioOut

HRESULT CAUDecoder::CAudioOut::Parse()
{
	ULONG nRead;
	m_pFilter->m_pInput->m_stream->Read(&m_hdr, sizeof(m_hdr), &nRead);
	if (nRead != sizeof(m_hdr))
		return E_FAIL;

	m_hdr.magic = ENDIANLONG(m_hdr.magic);
	m_hdr.encoding = ENDIANLONG(m_hdr.encoding);
	m_hdr.channels = ENDIANLONG(m_hdr.channels);
	m_hdr.offset = ENDIANLONG(m_hdr.offset);
	m_hdr.size = ENDIANLONG(m_hdr.size);
	m_hdr.sampleRate = ENDIANLONG(m_hdr.sampleRate);

	if (m_hdr.magic != AU_MAGIC) return E_FAIL;

// Only these encodings are currently supported
	if (!((m_hdr.encoding == ENC_ULAW) ||
			(m_hdr.encoding == ENC_ALAW) ||
			(m_hdr.encoding == ENC_PCM8) ||
			(m_hdr.encoding == ENC_PCM16)))
/*
			(h.encoding == ENC_PCM24) ||
			(h.encoding == ENC_PCM32) ||
			(h.encoding == ENC_IEEE32) ||
			(h.encoding == ENC_IEEE64) ||
			(h.encoding == ENC_ULAWADPCM8)*/
	{
		return E_FAIL;
		//return FORMAT_UNKNOWN;	// FORMAT_CONTINUE;
		//sprintf(r->errorMsg, "Unknown encoding scheme %d", h.encoding);

//		return PLUGIN_MSG;
	}

	if ((m_hdr.channels != 1) && (m_hdr.channels != 2))
	{
		return E_FAIL;//FORMAT_UNKNOWN;	// FORMAT_CONTINUE
	}

	if (m_hdr.offset < 24) return E_FAIL;//FORMAT_CORRUPTED_FILE;

	if ((m_hdr.size <= 0) || (m_hdr.size == 0xffffffff))
	{
	// Get size of file
		LARGE_INTEGER li;
		li.QuadPart = 0;
		ULARGE_INTEGER pos;
		m_pFilter->m_pInput->m_stream->Seek(li, STREAM_SEEK_END, &pos);

		m_hdr.size = (ULONG)pos.QuadPart - m_hdr.offset;
	}

	if (m_hdr.size <= 0)
	{
		//strcpy(r->errorMsg, "File contains no data");
		//return PLUGIN_MSG;
		return E_FAIL;
	}

// We've recognized the format

	/*
	if (h.encoding == ENC_ULAW)			strcpy(r->szAudioInfo, "µ-law");
	else if (h.encoding == ENC_ALAW)		strcpy(r->szAudioInfo, "A-law");
	else if (h.encoding == ENC_PCM8)		strcpy(r->szAudioInfo, "PCM");
	else if (h.encoding == ENC_PCM16)	strcpy(r->szAudioInfo, "PCM");
	*/

	if (m_hdr.encoding == ENC_PCM8)				m_wBitsPerSample = 8;
	else if (m_hdr.encoding == ENC_PCM16)		m_wBitsPerSample = 16;
	else if (m_hdr.encoding == ENC_ULAW)		m_wBitsPerSample = 16;
	else if (m_hdr.encoding == ENC_ALAW)		m_wBitsPerSample = 16;
	else ATLASSERT(0);

	m_nBlockAlign = m_hdr.channels * m_wBitsPerSample / 8;

	DWORD	sizeBytes = m_hdr.size;

	if ((m_hdr.encoding == ENC_ULAW) || (m_hdr.encoding == ENC_ALAW))
	{
		m_nSamples = sizeBytes;
	}
	else
	{
		m_nSamples = (sizeBytes * 8) / m_wBitsPerSample;
	}

	m_nSamples /= m_hdr.channels;

	CComObject<CAudioMediaType>::CreateInstance(&m_pMediaType);
	m_pMediaType->m_pAudioOut = this;
	m_pMediaType->AddRef();

	return S_OK;
}

// ILMediaSeeking
STDMETHODIMP CAUDecoder::CAudioOut::Seek(double seconds)
{
	return S_OK;
}

STDMETHODIMP CAUDecoder::CAudioOut::GetDuration(double* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = (double)m_nSamples / m_hdr.sampleRate;
	return S_OK;
}

STDMETHODIMP CAUDecoder::CAudioOut::GetCurrentPosition(double* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 0;	// TODO
	return S_OK;
}

// ILAudio
STDMETHODIMP CAUDecoder::CAudioOut::GetSamples(LONGLONG *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_nSamples;
	return S_OK;
}

/*
STDMETHODIMP CAUDecoder::GetFormat(WAVEFORMATEX *pVal)
{
	if (pVal == NULL) return E_POINTER;

	pVal->wFormatTag = WAVE_FORMAT_PCM;
	pVal->nChannels = m_hdr.channels;
	pVal->wBitsPerSample = m_wBitsPerSample;
	pVal->nSamplesPerSec = m_hdr.sampleRate;
	pVal->nBlockAlign = m_nBlockAlign;
	pVal->cbSize = 0;

	return S_OK;
}
*/

STDMETHODIMP CAUDecoder::CAudioOut::GetChunkSize(long nchunk, ULONG* pVal)
{
	long chunkSamples = 2000;	// Just a reasonable value
	long nchunks = (m_nSamples+chunkSamples-1)/chunkSamples;

	if (nchunk < nchunks)
	{
		int startSample = nchunk*chunkSamples;

		if (startSample+chunkSamples > m_nSamples)
			*pVal = m_nSamples-startSample;
		else
			*pVal = chunkSamples;
	}
	else
	{
		*pVal = NULL;
		return S_FALSE;
	}

	return S_OK;
}

STDMETHODIMP CAUDecoder::CAudioOut::ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples)
{
	ULONG numSamples = nsamples;
	if (numSamples > 2000) numSamples = 2000;

	ULONG startSample = nchunk*numSamples;

	DWORD	len = numSamples*m_hdr.channels;

	HRESULT hr = 0;

	if ((m_hdr.encoding == ENC_ULAW) || (m_hdr.encoding == ENC_ALAW))
	{
		ULONG offset = startSample * m_hdr.channels;
		ULONG sizeBytes = numSamples * m_hdr.channels;

		LPBYTE inbuf = (LPBYTE)GlobalAlloc(0, sizeBytes);

		if (inbuf)
		{
			LARGE_INTEGER li;
			li.QuadPart = m_hdr.offset + offset;
			m_pFilter->m_pInput->m_stream->Seek(li, STREAM_SEEK_SET, NULL);

			if (SUCCEEDED(m_pFilter->m_pInput->m_stream->Read(inbuf, sizeBytes, NULL)))
			{
				LPBYTE in = inbuf;
				LPWORD out = (LPWORD)buffer;
				
				if (m_hdr.encoding == ENC_ULAW)	// mu-law
				{
					while (len--)
					{
						*out++ = mulaw[*in++]*4;
					}
				}
				else	// a-law
				{
					while (len--)
					{
						*out++ = alaw[*in++]*8;
					}
				}
				
				GlobalFree(inbuf);
				
				hr = S_OK;
			}
			else
				hr = E_FAIL;	// Read/Write error
		}
		else
			hr = E_OUTOFMEMORY;
	}
	else	// PCM
	{
		ULONG offset = startSample * m_nBlockAlign;
		ULONG sizeBytes = numSamples * m_nBlockAlign;

//		r->SetFilePos(r->file, hdr.offset + offset, FILE_BEGIN);
		LARGE_INTEGER li;
		li.QuadPart = m_hdr.offset + offset;
		m_pFilter->m_pInput->m_stream->Seek(li, STREAM_SEEK_SET, NULL);

		if (SUCCEEDED(m_pFilter->m_pInput->m_stream->Read(buffer, sizeBytes, NULL)))
		{
			if (m_wBitsPerSample == 8)	// Change sign
			{
				char *p = buffer;

				while (len--)
				{
					*p = *p + 128;
					p++;
				}
			}
			else if (m_wBitsPerSample == 16)	// Swap bytes
			{
				short	*p = (short*)buffer;

				while (len--)
				{
					*p = ENDIANWORD(*p);
					p++;
				}
			}
			
			hr = S_OK;
		}
		else
			hr = E_FAIL;	// Read/Write error
	}

	return hr;
}

/////////////////////////////////////////////////////////////////////////
// CAUDecoder

DWORD WINAPI RunningAudioThreadProc(
  LPVOID lpParameter   // thread data
)
{
	CAUDecoder* pFilter = (CAUDecoder*)lpParameter;

	CoInitialize(NULL);

	HRESULT hr;

	CComQIPtr<ILMemInputPin> memInput = pFilter->m_pAudioOut->m_connectedTo;
	if (memInput)
	{
		/*
		if (pFilter->m_pAudio->m_sample == NULL)
		{
			pFilter->m_pAudio->m_allocator->GetBuffer((ILMediaSample**)&pFilter->m_pAudio->m_sample);
		}
		*/

		long chunkSamples = 2000;
		long nchunks = (pFilter->m_pAudioOut->m_nSamples+chunkSamples-1)/chunkSamples;
		
		int n = 0;
		while (n < nchunks)
		{
			CComPtr<ILAudioSample> sample;
			pFilter->m_pAudioOut->m_allocator->GetBuffer(chunkSamples*pFilter->m_pAudioOut->m_nBlockAlign, (ILMediaSample**)&sample);

			LPBYTE buffer;
			sample->LockBits(&buffer);

			pFilter->m_pAudioOut->ReadChunk(n, (LPSTR)buffer, chunkSamples);

			sample->UnlockBits();

			hr = memInput->Receive(sample);
			if (FAILED(hr) || hr == S_FALSE)
			{
				break;
			}
			sample = NULL;
			buffer = NULL;

			n++;
		}
	}

	/*
	if (SUCCEEDED(hr))	// Don't send this if the downstream filter failed in Receive?
		pFilter->m_pVideo->m_connectedTo->EndOfStream();
*/

	CoUninitialize();

	return 0;
}

// ILMediaFilter
STDMETHODIMP CAUDecoder::Run(double tStart)
{
	EnterCriticalSection(&m_pLock);
	m_state = LState_Running;
	m_tStart = tStart;
	LeaveCriticalSection(&m_pLock);

	m_hAudioThread = CreateThread(NULL, NULL, RunningAudioThreadProc, (LPVOID)this, 0, &m_audioThreadId);

	return S_OK;
}

STDMETHODIMP CAUDecoder::Stop()
{
	EnterCriticalSection(&m_pLock);
	m_state = LState_Stopped;
	LeaveCriticalSection(&m_pLock);

	return S_OK;
}
