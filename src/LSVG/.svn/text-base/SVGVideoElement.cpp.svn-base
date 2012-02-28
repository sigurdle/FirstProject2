#include "stdafx.h"
#include "LSVG2.h"
#include "SVGVideoElement.h"
#include "PSVGVideoElement.h"

namespace System
{
namespace Web
{

SVGVideoElement::SVGVideoElement(NamedNodeMap* attributes) : SVGTransformableElement(new PSVGVideoElement(this), attributes)
{
	m_x = NULL;
	m_y = NULL;
	m_width = NULL;
	m_height = NULL;
	m_preserveAspectRatio = NULL;

	m_pMedia = NULL;
	m_intrinsicDur = 0;

	/*
	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));
	AddXMLAttribute(NewXMLAttr(&m_preserveAspectRatio, NULL, WSTR("preserveAspectRatio"), WSTR("xMidYMid meet")));

	SetAllValues(this);	// ??
	*/
}

SVGVideoElement::~SVGVideoElement()
{
}

SVGAnimatedLength* SVGVideoElement::get_x()
{
	return m_x;
}

SVGAnimatedLength* SVGVideoElement::get_y()
{
	return m_y;
}

SVGAnimatedLength* SVGVideoElement::get_width()
{
	return m_width;
}

SVGAnimatedLength* SVGVideoElement::get_height()
{
	return m_height;
}

SVGAnimatedPreserveAspectRatio* SVGVideoElement::get_preserveAspectRatio()
{
	return m_preserveAspectRatio;
}

//////////////////////////////////////////////////////////////

double SVGVideoElement::GetIntrinsicDuration()
{
	if (m_pMedia == NULL)
	{
		LoadMedia();
	}

	return m_intrinsicDur;
}

ErrorCode SVGVideoElement::LoadMedia()
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

		sysstring src = getAttributeNS(L"http://www.w3.org/1999/xlink", L"href");

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

		// Get intrinsic duration

			CComQIPtr<ILMediaSeeking> seek = m_pMedia->m_filterGraph;
			LONGLONG dur;
			seek->GetDuration(&dur);
			/*
			CComQIPtr<IMediaSeeking> mediaSeeking = m_pMedia->m_dsGraph;
			LONGLONG ldur;//pos = (LONGLONG)(seekTo*1000*10);
			mediaSeeking->GetDuration(&ldur);

			m_implicitDur = (double)ldur / 10000000; // seconds
			*/
			m_intrinsicDur = (double)dur / LTIME_SCALE;	// to seconds
		}
	}
#endif
	return Success;
}

ErrorCode SVGVideoElement::GetWaveFormat(WAVEFORMATEX* pVal)
{
	ASSERT(0);
#if 0
	*pVal = *m_pMedia->m_wavFormat;
#endif
	return Success;
}

ErrorCode SVGVideoElement::RenderAudio(double start_tsp, double lent, uint8 * buffer, ULONG/* nSamples*/)
{
	ASSERT(0);
#if 0
	ULONG startSample = start_tsp * m_pMedia->m_wavFormat->nSamplesPerSec;
	ULONG nSamples = lent * m_pMedia->m_wavFormat->nSamplesPerSec;

	TRACE("startSample:%d, nSamples:%d\n", startSample, nSamples);

	double parent_speed = 1;
	double AD = m_timeContainerImpl->m_AD;// * m_pMedia->m_wavFormat->nSamplesPerSec;//m_dur;// ? AD=Active Duration?
	double speed = m_timeContainerImpl->m_speed;
	double acc = m_timeContainerImpl->m_accelerate;
	double dec = m_timeContainerImpl->m_decelerate;

	if (acc+dec > 1)	// Ignore both attributes
	{
		acc = 0;
		dec = 0;
	}

	double r = (1 / (1 - acc/2 - dec/2));// * m_pMedia->m_wavFormat->nSamplesPerSec;

	//Let dur be the value of the simple duration as defined by the Timing and Synchronization model.
	// This is the actual simple duration, and not simply the dur attribute.
	//This value does not account for the effect of any time manipulations.
	double dur = m_timeContainerImpl->m_dur;// * m_pMedia->m_wavFormat->nSamplesPerSec;

	// pThis->m_simpleDur has accounted for autoReverse
	double dur_ = m_timeContainerImpl->m_simpleDur;// * m_pMedia->m_wavFormat->nSamplesPerSec;

	double dacc = acc*dur;
	double ddec = dec*dur;

	for (ULONG n = 0; n < nSamples; n++)
	{
		//DWORD insample = n+startSample;

		//if (speed == 0) speed = 0 ??

		double tau = (startSample + n) * (1.0/m_pMedia->m_wavFormat->nSamplesPerSec);//tps - m_pCurrentInterval->m_begin;

		double taf;

		if (speed > 0) // i.e. if the local speed is forwards 
			taf = tau * speed;
		else //  i.e. if the local speed is backwards 
			taf = AD - tau * fabs(speed);

		double tsu = REMAINDER(taf, dur_);

	// Account for autoReverse behavior.
		double tsu_;

		if (m_timeContainerImpl->m_autoReverse == false)
		{
			tsu_ = tsu;
		}
		else
		{
			if (tsu < dur)
				tsu_ = tsu;
			else
				//tsu_ = /*dur - (tsu - dur) =*/ 2*dur - tsu;
				tsu_ = 2*dur - tsu;
		}

	// Calculate filtered time (tsf)

	// Account for acceleration/deceleration
		double tsf;

		if (tsu_ < dacc)
		{
			double rt = r * (tsu_ / dacc);

			tsf = tsu_ * rt / 2;
		}
		else if (tsu_ > (dur - ddec))
		{
			double rt = r * (dur - tsu_) / ddec;

			double tdec =  tsu_ - (dur - ddec);
			double pd =  tdec / ddec;

			tsf = r * (dur - dacc / 2 - ddec + tdec * (2 - pd) / 2);
		}
		else
		{
			tsf = r * (tsu_ - dacc / 2);
		}

		//ULONG tsf = tsf;

		ULONG nSample = tsf*m_pMedia->m_wavFormat->nSamplesPerSec;

		ASSERT(nSample >= 0 && nSample < m_pMedia->m_nSamples);

		buffer[n*2+0] = m_pMedia->m_wavBuffer[nSample*2+0];
		buffer[n*2+1] = m_pMedia->m_wavBuffer[nSample*2+1];

		if (!(n % 100))
		{
			TRACE("%d - %d\n", nSample, n+startSample);
		}
	}
#endif

	return Success;
}

void SVGVideoElement::Seek(double tps/*parent simple time*//*, double nextParentSimpleTime*/)
{
	if (m_pMedia == NULL)
	{
		ErrorCode hr = LoadMedia();
	}

#if 0
	if (m_pCurrentInterval)
	{
		//CComBSTR bstrRegion;
		//getAttribute(L"region", &bstrRegion);

		//CComPtr<ILDOMElement> element;
		//m_ownerDocument->getElementById(bstrRegion, &element);

		//CComQIPtr<ILSMILRegionElement> region = element;

		if (tps > m_parentSimpleTime)	// Seeking Forward
		{
			while (1)	// loop
			{
				if (m_pCurrentInterval)
				{
					// Check if going from inactive to active on the current interval
					if (	m_parentSimpleTime <= m_pCurrentInterval->m_begin &&
							!m_pCurrentInterval->m_bActive &&
							tps >= m_pCurrentInterval->m_begin)	// From inactive to active
					{
						m_pCurrentInterval->m_bActive = TRUE;

						if (m_pMedia->m_dsBuffer8)
						{
							m_pMedia->m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);
						}
						/*
						static_cast<CLSMILRegionElement*>(region.p)->Activate(m_pCurrentInterval->m_begin, this);
						*/

					//	m_parentSimpleTime = m_pCurrentInterval->m_begin;


					}

					// Check if ending the current interval
					if (m_pCurrentInterval->m_bActive//m_parentSimpleTime < m_pCurrentInterval->m_end)
						&&	tps >= m_pCurrentInterval->m_end)	// From active to stopped
					{
						/*
					// Deactivate region(s)
						static_cast<CLSMILRegionElement*>(region.p)->Deactivate(m_pCurrentInterval->m_end, this);
						*/

						m_parentSimpleTime = m_pCurrentInterval->m_end;
						EndCurrentIntervalAt(m_pCurrentInterval->m_end);

						continue;
					}
					else
					{
						if (m_restart->m_value->m_value == RESTART_ALWAYS)
						{
							CComObject<CLTimeInstance>* pInstanceTime = GetNextInstanceTime(m_pCurrentInterval->m_begin);

							if (pInstanceTime &&
								(tps >= *pInstanceTime && *pInstanceTime < m_pCurrentInterval->m_end))
							{
								/*
								// Deactivate region(s)
								static_cast<CLSMILRegionElement*>(region.p)->Deactivate(m_pCurrentInterval->m_end, this);
								*/

								m_parentSimpleTime = *pInstanceTime;
								EndCurrentIntervalAt(*pInstanceTime);

								continue;
							}
						}
					}
				}

				m_parentSimpleTime = tps;
				break;
			}
		}
		else
		{
		}
	}
#endif

	ASSERT(0);
#if 0	// TODO
		CLElementTimeContainerImpl<SVGVideoElement>::Seek(tps);
#endif

		if (m_timeContainerImpl->m_pCurrentInterval)
		{
			/*
			double activeTime = parentSimpleTime - m_pCurrentInterval->m_begin;
			m_tsf = REMAINDER(activeTime, m_simpleDur);

			m_tau = activeTime;
			*/

			m_pMedia->Seek(m_timeContainerImpl->m_tsf);
		}
}

}	// w3c
}
