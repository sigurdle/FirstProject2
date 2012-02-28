#include "stdafx.h"
#include "TIFF.h"
#include "TIFFDecoder.h"

namespace System
{
namespace Media
{

ErrorCode TIFFDecoder::Open()
{
	m_pFile = new Imaging::TIFFFile;
	m_pFile->Open(m_stream);

	for (int i = 0; i < m_pFile->m_images.size(); i++)
	{
		OutputPin* pOutputPin = new OutputPin;
		pOutputPin->m_pFilter = this;
		pOutputPin->m_pImage = m_pFile->m_images[i];
		pOutputPin->m_id = WSTR("Image Output");
		AddPin(pOutputPin);
	}

	return Success;
}

ErrorCode TIFFDecoder::CInputPin::CompleteConnect(IPin* pPin)
{
	ErrorCode hr;
	hr = BasePinImpl::CompleteConnect(pPin);
	if (hr < 0) return hr;

	return GetFilter()->Open();
}

static MSWindows::DWORD WINAPI RunningThreadProc(
  LPVOID lpParameter   // thread data
)
{
	ErrorCode hr;

	TIFFDecoder::OutputPin* p = (TIFFDecoder::OutputPin*)lpParameter;

	IMediaSample* sample;
	p->m_pAllocator->GetBuffer(0, &sample);
	if (sample)
	{
		//sample->SetTime(&tStart, &tStart);

		p->m_pImage->ReadImage(sample);

		p->m_pInputPin->Receive(sample);

		sample->Release();

		p->ConnectedTo()->EndOfStream();
	}

	return 0;
}

ErrorCode TIFFDecoder::OutputPin::Run(LONGLONG tStart)
{
	m_pFilter->m_tStart = tStart;

	ASSERT(0);
#if 0
	DWORD threadId;
	/*m_hThread =*/ CreateThread(NULL, NULL, RunningThreadProc, (LPVOID)(TIFFDecoder::OutputPin*)this, 0, &threadId);
#endif
	return 0;
}

#if 0
/////////////////////////////////////////////
// CEnumStreams

STDMETHODIMP CEnumStreams::Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IUnknown **rgelt,
            /* [out] */ ULONG *pceltFetched)
{
	for (int n = 0; n < celt; n++)
	{
		if (m_pos == NULL) break;
		*rgelt = (ILVideo*)(CTIFFImage*)m_decoder->m_images.GetNext(m_pos);
		(*rgelt)->AddRef();
	}

	if (pceltFetched)
		*pceltFetched = n;

	if (n == celt)
		return S_OK;
	else
		return S_FALSE;
}

STDMETHODIMP CEnumStreams::Skip(/* [in] */ ULONG celt)
{
	for (int n = 0; n < celt; n++)
	{
		m_decoder->m_images.GetNext(m_pos);
		if (m_pos == NULL) break;
	}

	if (n == celt)
		return S_OK;
	else
		return S_FALSE;
}

STDMETHODIMP CEnumStreams::Reset(void)
{
	m_pos = m_decoder->m_images.GetHeadPosition();
	return S_OK;
}
     
STDMETHODIMP CEnumStreams::Clone(/* [out] */ IEnumUnknown **ppenum)
{
	if (ppenum == NULL) return E_POINTER;
	*ppenum = NULL;

	CComObject<CEnumStreams>* pEnum;
	CComObject<CEnumStreams>::CreateInstance(&pEnum);
	if (pEnum)
	{
		pEnum->AddRef();

		pEnum->m_decoder = m_decoder;
		pEnum->m_pos = m_pos;

		*ppenum = pEnum;
	}

	return S_OK;
}
#endif

}	// Media
}
