// LACMWrapper.cpp : Implementation of CLACMWrapper
#include "stdafx.h"
#include "LAVI.h"
#include "LACMWrapper.h"

/////////////////////////////////////////////////////////////////////////////
// CLACMWrapper

HRESULT CLACMWrapper::CInputPin::CheckMediaType(const CLMediaType &mt)
{
	if (mt->majortype != LMEDIATYPE_Audio)
		return E_FAIL;

#if 0	// ??
	if (FOURCCMap(&mt->subtype) != mt->subtype)	// Not a fourcc guid
		return E_FAIL;
#endif

	return S_OK;
}

HRESULT CLACMWrapper::CInputPin::SetMediaType(const LMediaType* pmt)
{
	HRESULT hr;
	hr = CLBasePinImpl::SetMediaType(pmt);
	if (FAILED(hr)) return hr;

	m_pFilter->m_pwfxSrc = (LPWAVEFORMATEX)m_mt.GetFormat();

	MMRESULT mmresult;
	
	/*
	ACMFORMATTAGDETAILS aftd = {0};
	aftd.cbStruct = sizeof(aftd);
	aftd.dwFormatTag = WAVE_FORMAT_PCM;//m_pFilter->m_pwfxSrc->wFormatTag;
	mmresult = acmFormatTagDetails(
		NULL,	// had
		&aftd,
		ACM_FORMATTAGDETAILSF_FORMATTAG | ACM_FORMATTAGDETAILSF_LARGESTSIZE);
	if (mmresult != 0)
	{
		return E_FAIL;
	}
	*/

	/*
	// Get some textual information on the format
	ACMFORMATDETAILS afd;
	afd.cbStruct = sizeof(afd);
	afd.pwfx = m_pFilter->m_pwfxSrc;
	afd.dwFormatTag = m_pFilter->m_pwfxSrc->wFormatTag;	// Same as in above
	mmresult = acmFormatDetails(NULL, &afd, ACM_FORMATDETAILSF_FORMAT);
	if (mmresult == 0)
	{
		;
	}
	*/

	m_pFilter->m_pwfxDst = (LPWAVEFORMATEX)GlobalAlloc(0, sizeof(WAVEFORMATEX)/*aftd.cbFormatSize*/);
	if (m_pFilter->m_pwfxDst == NULL)
	{
		return E_OUTOFMEMORY;
	}
	ZeroMemory(m_pFilter->m_pwfxDst, sizeof(WAVEFORMATEX));	// Make sure that cbSize = 0

	m_pFilter->m_pwfxDst->wFormatTag = WAVE_FORMAT_PCM;	// We want output in PCM
	mmresult = acmFormatSuggest(
		NULL,	// had
		m_pFilter->m_pwfxSrc,
		m_pFilter->m_pwfxDst, sizeof(WAVEFORMATEX),//aftd.cbFormatSize,
		ACM_FORMATSUGGESTF_WFORMATTAG);
	if (mmresult != 0)
	{
		return E_FAIL;
	}

	mmresult = acmStreamOpen(
		&m_has,
		NULL,//HACMDRIVER had,
		m_pFilter->m_pwfxSrc,
		m_pFilter->m_pwfxDst,
		NULL,//LPWAVEFILTER pwfltr,
		NULL,//DWORD dwCallback,
		NULL,//DWORD dwInstance,
		NULL//DWORD fdwOpen
	);

	if (mmresult != 0)
	{
		return E_FAIL;
	}

	/*
	mmresult = acmStreamSize(
		m_has,//HACMSTREAM has,          
		0,//DWORD cbInput,           
		0,//LPDWORD pdwOutputBytes,  
		0//DWORD fdwSize            
	);

	if (mmresult != 0)
	{
		return E_FAIL;
	}
	*/

#if 0
	memset(&m_ash, 0, sizeof(m_ash));
	m_ash.cbStruct = sizeof(m_ash);
	m_ash.cbSrcLength = 1000000;
	m_ash.pbSrc = (LPBYTE)GlobalAlloc(0, m_ash.cbSrcLength);
	m_ash.cbDstLength = 1000000;
	m_ash.pbDst = (LPBYTE)GlobalAlloc(0, m_ash.cbDstLength);
	mmresult = acmStreamPrepareHeader(m_has, &m_ash, 0/*reserved*/);
	if (mmresult != 0)
	{
		return E_FAIL;
	}
#endif

	return S_OK;
}

#if 0
HRESULT CLACMWrapper::CInputPin::CompleteConnect(ILPin* pPin)
{
	HRESULT hr;
	hr = CLBasePinImpl::CompleteConnect(pPin);
	if (FAILED(hr)) return hr;


	return S_OK;
}
#endif

void CLACMWrapper::CInputPin::BreakConnect()
{
	if (m_has)
	{
		acmStreamClose(m_has, 0/*reserved*/);
		m_has = NULL;
	}
}

STDMETHODIMP CLACMWrapper::CInputPin::EndOfStream()
{
// TODO, convert remainder of bytes

	ATLASSERT(m_has);
	MMRESULT mmresult = acmStreamUnprepareHeader(m_has, &m_ash, 0/*reserved*/);
	if (mmresult != 0)
	{
		ATLASSERT(0);
	}

	return S_OK;
}

STDMETHODIMP CLACMWrapper::CInputPin::Receive(ILMediaSample *pSample)
{
	EnterCriticalSection(&m_pLock);

	MMRESULT mmresult;

	ULONG ActualDataLength;
	ActualDataLength = pSample->GetActualDataLength();

	memset(&m_ash, 0, sizeof(m_ash));

	LSampleData datain;
	pSample->LockBits(&datain);

	if (m_pFilter->m_pOutputPin->m_pInputPin)
	{
		CComPtr<ILMediaSample> outSample;
		m_pFilter->m_pOutputPin->m_pAllocator->GetBuffer(100000000/*m_ash.cbDstLengthUsed*/, &outSample);
		if (outSample)
		{
			LSampleData dataout;
			outSample->LockBits(&dataout);

			m_ash.cbStruct = sizeof(m_ash);
			//m_ash.cbSrcLength = 1000000;
			m_ash.cbSrcLength = ActualDataLength;	// Number of source bytes to convert
			m_ash.pbSrc = datain.idata;//(LPBYTE)GlobalAlloc(0, m_ash.cbSrcLength);
			m_ash.cbDstLength = 100000000;
			m_ash.pbDst = dataout.idata;//(LPBYTE)GlobalAlloc(0, m_ash.cbDstLength);

			mmresult = acmStreamPrepareHeader(m_has, &m_ash, 0/*reserved*/);
			if (mmresult != 0)
			{
				ATLASSERT(0);
				return E_FAIL;
			}

			DWORD fdwConvert = 0;//ACM_STREAMCONVERTF_BLOCKALIGN;
			mmresult = acmStreamConvert(m_has, &m_ash, fdwConvert);

			//MMSYSERR_INVALHANDLE

			if (m_ash.cbDstLengthUsed > 0)
			{
			//	MessageBeep(-1);
			}

			if (mmresult != 0)
			{
				MessageBeep(-1);
				return E_FAIL;
			}

			outSample->SetActualDataLength(m_ash.cbDstLengthUsed);

			//m_ash.cbDstLengthUsed;	// Number of bytes converted


			m_pFilter->m_pOutputPin->m_pInputPin->Receive(outSample);

			mmresult = acmStreamUnprepareHeader(m_has, &m_ash, 0/*reserved*/);
			if (mmresult != 0)
			{
				ATLASSERT(0);
			}
		}
	}

	LeaveCriticalSection(&m_pLock);

	return S_OK;
}
