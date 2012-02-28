#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAudioElement.h"

namespace System
{
namespace Web
{

SVGAudioElement::SVGAudioElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
{
	m_pMedia = NULL;
	m_implicitDur = 0;

	SetAllValues(this);
}

ErrorCode SVGAudioElement::LoadMedia()
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	if (m_pMedia == NULL)
	{
		m_pMedia = new CMediaSource;

#if 0
		m_pMedia->m_ds8 = static_cast<CLHTMLActiveDocument*>(static_cast<CLDOMDocument*>(m_ownerDocument)->m_acDocument)->m_ds8;
#endif

		ErrorCode hr;
		
		//hr = m_pMedia->CreateSampleGrabber();
		//if (FAILED(hr)) return hr;

		sysstring src = getAttributeNS(L"http://www.w3.org/1999/xlink", L"href", &src);

		if (src.Length())
		{
			TCHAR absurl[2048];
			{
				CComBSTR documentUrl;
				m_ownerDocument->get_url(&documentUrl);

				DWORD resultLen = sizeof(absurl);
				InternetCombineUrl(W2A(documentUrl), W2A(src), absurl, &resultLen, 0);
			}

			hr = m_pMedia->LoadFile(A2W(absurl));
			if (FAILED(hr)) return hr;

			m_pMedia->m_pAudioFilter->m_pElement = this;

		// Get implicit duration

			CComQIPtr<ILMediaSeeking> seek = m_pMedia->m_filterGraph;
			LONGLONG dur;
			seek->GetDuration(&dur);
			/*
			CComQIPtr<IMediaSeeking> mediaSeeking = m_pMedia->m_dsGraph;
			LONGLONG ldur;//pos = (LONGLONG)(seekTo*1000*10);
			mediaSeeking->GetDuration(&ldur);

			m_implicitDur = (double)ldur / 10000000; // seconds
			*/
			m_implicitDur = (double)dur / LTIME_SCALE;	// to seconds
		}
	}
#endif
	return Success;
}

double SVGAudioElement::GetIntrinsicDuration()
{
	if (m_pMedia == NULL)
	{
		LoadMedia();
	}

	return m_implicitDur;
}

void SVGAudioElement::Run()
{
	m_pMedia->m_filterGraph->Run();
}

void SVGAudioElement::Seek(double parentSimpleTime)
{
}

}	// LSVG
}
