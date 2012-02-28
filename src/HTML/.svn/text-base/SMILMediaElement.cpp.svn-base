#include "stdafx.h"
#include "HTML2.h"

#include "SMILMediaElement.h"

#include "SMILRegionElement.h"

namespace System
{
namespace Web
{

SMILMediaElement::SMILMediaElement(NamedNodeMap* attributes) : SMILElement(new PElementBase(this), attributes)
{
	m_left = NULL;
	m_top = NULL;
	m_right = NULL;
	m_bottom = NULL;
	m_width = NULL;
	m_height = NULL;
	m_transIn = NULL;
	m_transOut = NULL;

	m_pMedia = NULL;
	m_implicitDur = 0;

	m_timeContainerImpl = new ElementTimeContainerImpl(this);

	/*
	AddXMLAttribute(NewXMLAttr(&m_left, NULL, WSTR("left")));
	AddXMLAttribute(NewXMLAttr(&m_top, NULL, WSTR("top")));
	AddXMLAttribute(NewXMLAttr(&m_right, NULL, WSTR("right")));
	AddXMLAttribute(NewXMLAttr(&m_bottom, NULL, WSTR("bottom")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));

	AddXMLAttribute(NewXMLAttr(&m_transIn, NULL, WSTR("transIn")));
	AddXMLAttribute(NewXMLAttr(&m_transOut, NULL, WSTR("transOut")));
*/
	SetAllValues(this);	// ???
}
	
String SMILMediaElement::get_src()
{
	return getAttribute(WSTR("src"));
}

void SMILMediaElement::set_src(StringIn newVal)
{
	setAttribute(WSTR("src"), newVal);
}

double SMILMediaElement::GetIntrinsicDuration()
{
	if (m_pMedia == NULL)
	{
		LoadMedia();
	}

	return m_implicitDur;
}


ErrorCode SMILMediaElement::LoadMedia()
{
	if (m_pMedia == NULL)
	{
		m_pMedia = new MediaSource;

		ErrorCode hr;
		
		String src = get_src();
		if (src && src.GetLength())
		{
			ASSERT(0);
#if 0
			WCHAR absurl[2048];
			{
				String documentUrl = m_ownerDocument->get_url();

				DWORD resultLenBytes = sizeof(absurl) - sizeof(absurl[0]);
				InternetCombineUrlW(documentUrl->c_str(), src->c_str(), absurl, &resultLenBytes, 0);
			}

			hr = m_pMedia->LoadFile(string_copy(absurl));
			if (hr < 0) return hr;

		// Get implicit duration

			ASSERT(0);
#if 0
			CComQIPtr<ILMediaSeeking> seek = m_pMedia->m_filterGraph;
			LONGLONG dur;
			seek->GetDuration(&dur);

			m_implicitDur = (double)dur / LTIME_SCALE;	// to seconds
#endif

		// Get implicit duration
//			CComQIPtr<IMediaSeeking> mediaSeeking = m_pMedia->m_dsGraph;
//			LONGLONG ldur;//pos = (LONGLONG)(seekTo*1000*10);
//			mediaSeeking->GetDuration(&ldur);

//			m_implicitDur = (double)ldur / 10000000; // seconds
#endif
		}
	}

	return Success;
}


#define REMAINDER(t, d) (t - d*floor(t/d))

/*
There are two cases in which restart semantics must be considered: 

1. When the current interval is playing, if restart="always" then any instance
	time (call it T) in the begin list that is after (i.e. later than) the current
	interval begin but earlier than the current interval end will cause the
	current interval to end at time T. This is the first step in restarting the
	element: when the current interval ends, that in turn will create any
	following interval. 

*/

/*
	SMIL
	10.3.3 Semantics of the Timing Model 

	*End of an interval*

	If an element specifies restart="never" then no further action is taken at
	the end of the interval, and the element sits in the "post interval" state
	unless and until an ascendant time container repeats or restarts. 

	If an element specifies other values for restart, when it ends the current
	interval the element must reconsider the lists of resolved begin and end times.
	If there is another legal interval defined to begin at or after the just
	completed end time, a new interval will be created. When a new interval is
	created it becomes the current interval and a new interval notice is sent to
	all time dependents. 
*/

void SMILMediaElement::InactiveToActive()
{
	String strRegion = getAttribute(WSTR("region"));

	Element* element = m_ownerDocument->getElementById(strRegion);

	SMILRegionElement* region = dynamic_cast<SMILRegionElement*>(element);
	if (region)
	{
		region->Activate(m_timeContainerImpl->m_pCurrentInterval->m_begin, this);
	}
}

void SMILMediaElement::ActiveToInactive()
{
	String bstrRegion = getAttribute(WSTR("region"));

	Element* element = m_ownerDocument->getElementById(bstrRegion);

	SMILRegionElement* region = dynamic_cast<SMILRegionElement*>(element);
	if (region)
	{
	// Deactivate region(s)
		region->Deactivate(m_timeContainerImpl->m_pCurrentInterval->m_end, this);
	}
}

void SMILMediaElement::Seek(double tps/*parentSimpleTime*/ /* parent simple time */)
{
	if (m_pMedia == NULL)
	{
		LoadMedia();
	}

	m_timeContainerImpl->Seek(tps);

	if (m_pMedia)
	{
		m_pMedia->Seek(m_timeContainerImpl->m_tsf);
	}
}

void SMILMediaElement::seekElement(double seekTo /*milliseconds*/)
{
	seekTo /= 1000;
}

void CalcRegion(CLengthValue* pLeftValue, CLengthValue* pRightValue, CLengthValue* pWidthValue, double parentComputedWidth, double& m_computedLeft, double& m_computedWidth);

gm::RectD SMILMediaElement::GetSubRegion(double bbwidth, double bbheight)
{
	CLengthValue* pLeftValue = m_left->m_animated->m_animVal->m_value;
	CLengthValue* pRightValue = m_right->m_animated->m_animVal->m_value;
	CLengthValue* pWidthValue = m_width->m_animated->m_animVal->m_value;

	CLengthValue* pTopValue = m_top->m_animated->m_animVal->m_value;
	CLengthValue* pBottomValue = m_bottom->m_animated->m_animVal->m_value;
	CLengthValue* pHeightValue = m_height->m_animated->m_animVal->m_value;

// hm.. ?
//	Gdiplus::Bitmap* pBitmap;
//	m_pMedia->GetBitmap(&pBitmap);
//	bbwidth = pBitmap->GetWidth();
//	bbheight = pBitmap->GetHeight();

	double m_computedLeft, m_computedWidth, m_computedTop, m_computedHeight;
	CalcRegion(pLeftValue, pRightValue, pWidthValue, bbwidth, m_computedLeft, m_computedWidth);
	CalcRegion(pTopValue, pBottomValue, pHeightValue, bbheight, m_computedTop, m_computedHeight);

	return gm::RectD(m_computedLeft, m_computedTop, m_computedWidth, m_computedHeight);
}

int SMILMediaElement::GetWidth()
{
	if (m_pMedia == NULL)
	{
		LoadMedia();
	}

	if (m_pMedia)
	{
		ASSERT(0);
#if 0
		if (m_pMedia->m_movie)
		{
			CComQIPtr<ILVideo> video;
			m_pMedia->m_movie->GetVideo(&video);
			if (video)
			{
				video->GetWidth(pVal);
			}
		}
#endif
	}
	return 0;
}

int SMILMediaElement::GetHeight()
{
	if (m_pMedia == NULL)
	{
		LoadMedia();
	}

	if (m_pMedia)
	{
		ASSERT(0);
#if 0
		if (m_pMedia->m_filterGraph)
		{
			ASSERT(0);
#if 0
			CComQIPtr<ILVideo> video;
			m_pMedia->m_movie->GetVideo(&video);
			if (video)
			{
				video->GetHeight(pVal);
			}
#endif
		}
#endif
	}
	return 0;
}

/////////

Graphics::Bitmap* SMILMediaElement::GetBitmap()
{
	/*
	if (m_pMedia == NULL)
	{
		LoadMedia();
	}
	*/

	ASSERT(0);
#if 0

	if (m_pMedia && m_pMedia->m_pVideoFilter)
	{
		Graphics::Bitmap* bitmap = NULL;
		m_pMedia->m_pVideoFilter->GetBitmap(&bitmap);
		return bitmap;
	}
#endif
	return NULL;
}

SMILRegionElement* SMILMediaElement::get_region()
{
	ASSERT(0);
	return NULL;
}

void SMILMediaElement::set_region(SMILRegionElement* newVal)
{
	ASSERT(0);
}

}	// Web
}	// System
