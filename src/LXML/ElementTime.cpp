#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"
#include "ElementTime.h"

namespace System
{
namespace Web
{

void InstanceTimeList::Sort()
{
	// TODO std::sort

// Sort
	int i;
	
	for (i = 0; i < m_items.GetSize(); i++)
	{
		int min_index = i;
		
		for (int j = i+1; j < m_items.GetSize(); j++)
		{
			if (*m_items[j] < *m_items[min_index])
			{
				min_index = j;
			}
		}

		if (i != min_index)	// Swap
		{
			TimeInstance* temp = m_items[i];
			m_items[i] = m_items[min_index];
			m_items[min_index] = temp;
		}
	}
}

ImmutableString<wchar_t> begin_str(L"begin");
ImmutableString<wchar_t> end_str(L"end");
ImmutableString<wchar_t> dur_str(L"dur");
ImmutableString<wchar_t> fill_str(L"fill");
ImmutableString<wchar_t> restartDur_str(L"restartDur");
ImmutableString<wchar_t> repeatDur_str(L"repeatDur");
ImmutableString<wchar_t> repeatCount_str(L"repeatCount");
ImmutableString<wchar_t> accelerate_str(L"accelerate");
ImmutableString<wchar_t> decelerate_str(L"decelerate");
ImmutableString<wchar_t> speed_str(L"speed");
ImmutableString<wchar_t> autoReverse_str(L"autoReverse");

ElementTime::ElementTime(Element* ownerElement) : m_ownerElement(ownerElement)
{
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_beginAttr), nullptr, &begin_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_endAttr), nullptr, &end_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_durAttr), nullptr, &dur_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_fillAttr), nullptr, &fill_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_restartAttr), nullptr, &restartDur_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_repeatDurAttr), nullptr, &repeatDur_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_repeatCountAttr), nullptr, &repeatCount_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_accelerateAttr), nullptr, &accelerate_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_decelerateAttr), nullptr, &decelerate_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_speedAttr), nullptr, &speed_str);
	ownerElement->UnspecifiedAttr(inner_ptr<Attr*>(this, &m_autoReverseAttr), nullptr, &autoReverse_str);

//	m_cx = new SVGAnimatedLength;
//	m_cx->m_baseValChanged = cxBaseValChanged;
//	m_cx->m_arg0 = this;

	m_begin = new SMILTimeList;
	m_begin->m_ownerElement = ownerElement;
	m_begin->setStringValue(m_beginAttr->get_value());

	m_end = new SMILTimeList;
	m_end->m_ownerElement = ownerElement;
	m_end->setStringValue(m_endAttr->get_value());

	m_dur = -1;
	m_simpleDur = -1;
	m_AD = -1;

	m_tau = -1;
	m_tsf = -1;
	m_parentSimpleTime = -1;

//	m_restart = NULL;
//	m_fill = NULL;
//	m_repeatDur = ;
	m_accelerate = 0;
	m_decelerate = 0;
	m_speed = 1;
	m_repeatCount = 1;
	m_autoReverse = false;

	CalculateSimpleDuration();	// Sometimes available
}

ElementTime::~ElementTime()
{
}

// Define simple duration
void ElementTime::CalculateSimpleDuration()
{
	String str_dur = m_durAttr->get_value();
	//CComBSTR str_repeatCount;
	//CComBSTR str_repeatDur;
	//CComBSTR str_end;

//	((ILDOMElement*)static_cast<T*>(this))->getAttribute(WSTR("dur"), &str_dur);
	/*
	((ILDOMElement*)static_cast<T*>(this))->getAttribute(L"repeatCount", &str_repeatCount);
	((ILDOMElement*)static_cast<T*>(this))->getAttribute(L"repeatDur", &str_repeatDur);
	((ILDOMElement*)static_cast<T*>(this))->getAttribute(L"end", &str_end);
	*/

	if (str_dur && str_dur.GetLength())
	{
		if (str_dur == L"indefinite")
		{
			m_dur = INDEFINITE;
		}
		else if (str_dur == L"media")
		{
			m_dur = GetImplicitDuration();
		}
		else
		{
			ASSERT(0);
#if 0
			m_dur = ParseClockValue(str_dur.begin());
#endif
		}
	}
	else
	{
		if (m_endAttr->get_specified() &&
			!m_repeatCountAttr->get_specified() && !m_repeatDurAttr->get_specified())
		{
			m_dur = INDEFINITE;
		}
		else
		{
			m_dur = GetImplicitDuration();
		}
	}

	m_simpleDur = m_dur;

	if (m_autoReverse)
	{
		if (m_simpleDur < INDEFINITE)
			m_simpleDur *= 2;
	}
}

IElementTimeContainer* ElementTime::get_parentTimeContainer()
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMNode> node;
	static_cast<T*>(this)->get_parentNode(&node);
	while (node)
	{
		CComQIPtr<IElementTimeContainer, &IID_IElementTimeContainer> timeContainerElement((IUnknown*)node);
		if (timeContainerElement)
		{
			CComBSTR timeContainerType;
			timeContainerElement->get_timeContainer(&timeContainerType);
			if (wcscmp(timeContainerType, WSTR("none")) != 0)	// none is not a timeContainer
			{
				*pVal = timeContainerElement;
				(*pVal)->AddRef();
				return S_OK;
			}
		}

		CComPtr<ILDOMNode> parentNode;
		node->get_parentNode(&parentNode);
		node = parentNode;
	}

	*pVal = NULL;
#endif
	return NULL;
}

// Called before children have been initialized
void ElementTime::Init()
{
//	m_begin->m_value->m_value->m_ownerDocument = static_cast<T*>(this)->m_ownerDocument;
//	m_end->m_value->m_value->m_ownerDocument = static_cast<T*>(this)->m_ownerDocument;

	m_clipBegin = 0;
#if 0
	{
		CComBSTR str;
		static_cast<T*>(this)->getAttribute(WSTR("clipBegin"), &str);
		if ((BSTR)str != NULL)
		{
			m_clipBegin = atof(_bstr_t(str));
		}
	}
#endif

	/*
	{
		CComBSTR str;
		static_cast<T*>(this)->getAttribute(L"clipEnd", &str);
		if ((BSTR)str != NULL)
		{
			clipEnd = atof(_bstr_t(str));
		}
	}
	*/

#if 0
	IElementTimeContainer* parentTimeContainerNode;
	get_parentTimeContainer(&parentTimeContainerNode);

	CComBSTR timeContainerType;
	if (parentTimeContainerNode)
		parentTimeContainerNode->get_timeContainer(&timeContainerType);

// parent time container is seq
	if (timeContainerType.Length() && !wcscmp(timeContainerType, WSTR("seq")))
	{
		CComPtr<ILDOMNode> previousNode;
		static_cast<T*>(this)->get_previousSibling(&previousNode);

		CComQIPtr<IElementTime, &IID_IElementTime> elementTime((IUnknown*)previousNode);
		if (elementTime)
		{
			CComQIPtr<ILDOMElement, &IID_ILDOMElement> previousElement((IUnknown*)previousNode);
		// TODO, improve this
			CComObject<SMILTime>* pTime = m_begin->m_value->m_value->m_items[0];
			//CComObject<SMILTime>::CreateInstance(&pTime);
			//pTime->AddRef();
			
			pTime->m_type = SMIL_TIME_SYNC_BASED;
			pTime->m_baseBegin = VARIANT_FALSE;
			if (pTime->m_offset < 0)
				pTime->m_offset = 0;

			pTime->set_baseElement(previousElement);

			//m_begin->m_value->m_value->m_items.Add(pTime);
		}
	}
#endif

	{
		for (int i = 0; i < m_begin->m_items.GetSize(); i++)
		{
			SMILTime* pTime = m_begin->m_items[i];

			if (pTime->m_type == SMIL_TIME_SYNC_BASED)
			{
				ASSERT(0);
#if 0
				Element* baseElement = pTime->get_baseElement();

				CComQIPtr<CLElementTimeImpl, &IID_IUnknown/*TODO*/> ElementTime((IUnknown*)baseElement);
				if (ElementTime)
				{
				// Remove if we're already in the list ?
					for (int i = ElementTime->m_syncDependants.GetSize()-1; i >= 0; i--)
					{
						if (ElementTime->m_syncDependants[i] == this)
						{
							ElementTime->m_syncDependants.RemoveAt(i);
							break;
						}
					}
				// add us
					ElementTime->m_syncDependants.Add(this);
				}
#endif
			}
		}

		for (int i = 0; i < m_end->m_items.GetSize(); i++)
		{
			SMILTime* pTime = m_end->m_items[i];

			if (pTime->m_type == SMIL_TIME_SYNC_BASED)
			{
				Element* baseElement = pTime->get_baseElement();

				ASSERT(0);
#if 0
				CComQIPtr<CLElementTimeImpl, &IID_IUnknown/*TODO*/> ElementTime((IUnknown*)baseElement);
				if (ElementTime)
				{
					ElementTime->m_syncDependants.Add(this);
				}
#endif
			}
		}
	}

	{
		for (int i = 0; i < m_begin->m_items.GetSize(); i++)
		{
			SMILTime* pTime = m_begin->m_items[i];

			if (pTime->m_type == SMIL_TIME_OFFSET)
			{
				TimeInstance* pInstanceTime = new TimeInstance;

				pInstanceTime->m_time = m_begin->m_items[i];
				pInstanceTime->m_resolvedTime = pInstanceTime->m_time->m_offset;
				m_instanceBeginList.m_items.push_back(pInstanceTime);
			}
			else if (pTime->m_type == SMIL_TIME_SYNC_BASED)
			{
			}
		}

		m_instanceBeginList.Sort();

		for (int i = 0; i < m_end->m_items.GetSize(); i++)
		{
			SMILTime* pTime = m_end->m_items[i];

			if (pTime->m_type == SMIL_TIME_OFFSET)
			{
				TimeInstance* pInstanceTime = new TimeInstance;

				pInstanceTime->m_time = m_end->m_items[i];
				pInstanceTime->m_resolvedTime = pInstanceTime->m_time->m_offset;
				m_instanceEndList.m_items.push_back(pInstanceTime);
			}
			else if (pTime->m_type == SMIL_TIME_SYNC_BASED)
			{
				ASSERT(0);
			}
		}

		m_instanceEndList.Sort();
	}

	/*
	CComQIPtr<IElementTimeContainer> tc = static_cast<T*>(this)->GetUnknown();
	if (tc == NULL)
	{
		CalculateSimpleDuration();
	}
	*/
}

// Called after children have been initialized
void ElementTime::Init2()
{
	ASSERT(0);
#if 0
	/*
	CComQIPtr<IElementTimeContainer> tc = static_cast<T*>(this)->GetUnknown();
	if (tc)
	{
		CalculateSimpleDuration();

		if (m_simpleDur == -1)	// ??
			m_simpleDur = 0;
	}
	*/

	if (m_pCurrentInterval == NULL)	// ?? Could have been created already if we're depending on another syncbase element
	{
		ASSERT(m_pCurrentInterval == NULL);
		m_pCurrentInterval = GetFirstInterval();

		if (m_pCurrentInterval)
		{
		// creating (new) interval notify syncbase dependants
			for (int i = 0; i < m_syncDependants.GetSize(); i++)
			{
				m_syncDependants[i]->NotifySync(static_cast<T*>(this), m_pCurrentInterval/*, VARIANT_TRUE*//*begin*/);
			}

			/*
		// new end, tell parent time container
			CComQIPtr<ILTimeContainer> parentTimeContainer = static_cast<T*>(this)->m_parentNode;
			if (parentTimeContainer)
			{
			}
			*/
		}
	}
#endif
}

void ElementTime::EndCurrentIntervalAt(double endt)
{
	ASSERT(m_pCurrentInterval);

	m_pCurrentInterval->m_end = endt;// Cut it short
	m_pCurrentInterval->m_bActive = false;

#if 0
// Fire endEvent
	{
		CComQIPtr<ILDOMDocumentEvent, &IID_ILDOMDocumentEvent> documentEvent((IUnknown*)static_cast<T*>(this)->m_ownerDocument);
		ASSERT(documentEvent);

		CComPtr<ILTimeEvent> evt;

		documentEvent->createEvent(WSTR("TimeEvents"), (ILDOMEvent**)&evt);
		evt->initTimeEvent(WSTR("endEvent"),
			NULL,//this,	// viewArg
			0		// detail
			);

		CComQIPtr<ILDOMEventTarget> eventTarget(static_cast<T*>(this));
		if (eventTarget)
		{
			bool doDefault;
			eventTarget->dispatchEvent(evt, &doDefault);
		}
	}

	if (m_restart->m_value->m_value != RESTART_NEVER)
	{
	// Find next interval to play
		CLTimeInterval* pNextInterval = GetNextInterval();

		if (pNextInterval)
		{
			m_pCurrentInterval->Release();
			m_pCurrentInterval = pNextInterval;
			if (m_pCurrentInterval)
			{
#if 0
				if (m_parentSimpleTime >= m_pCurrentInterval->m_begin)
				{
					m_pCurrentInterval->m_bActive = TRUE;
#if 0
			// Activate region(s)
				static_cast<CLSMILRegionElement*>(region.p)->Activate(m_pCurrentInterval->m_begin, this);
#endif
				}
#endif

			// creating (new) interval notify syncbase dependants
				for (int i = 0; i < m_syncDependants.GetSize(); i++)
				{
					(m_syncDependants[i])->NotifySync(static_cast<T*>(this), m_pCurrentInterval);
				}

			}
		}
	}
#endif
}

double ElementTime::calcActiveEnd(double begin, double end/* = INDEFINITE  no end constraint*/)
{
	ASSERT(m_simpleDur >= 0);
//	if (m_simpleDur <= 0) m_simpleDur = 99999; // TODO remove

// Account for speed in Active duration ?
	double speed = m_speed;
	if (speed == 0) speed = 1;	// Ignore

	double activeEnd = begin + (m_simpleDur * m_repeatCount)/speed;

	return MIN(activeEnd, end);
}

TimeInterval* ElementTime::GetFirstInterval()
{
	double beginAfter = -99999999;	// -INFINITY

	while (1)
	{
		//double tempBegin;// = the first value in the begin list that is >= beginAfter.
		TimeInstance* tempBegin;

		unsigned int i;
		for (i = 0; i < m_instanceBeginList.m_items.GetSize(); i++)
		{
			if (*m_instanceBeginList.m_items[i] >= beginAfter)
			{
				tempBegin = /***/ m_instanceBeginList.m_items[i];
				break;
			}
		}
	// If there is no such value  // No interval
		if (i == m_instanceBeginList.m_items.GetSize()) return NULL;

#if 0
		CComQIPtr<IElementTime> parent = static_cast<T*>(this)->m_parentNode;
		if (parent)
		{
			double parentSimpleEnd;
			parent->getSimpleDuration(&parentSimpleEnd);
			if (tempBegin >= parentSimpleEnd) // Can't begin after parent ends
				return NULL;
		}
#endif

/*
If there was no end attribute specified
*/
		double tempEnd;

		/*
		bool bEnd;
		static_cast<T*>(this)->hasAttribute(L"end", &bEnd);
		*/
		// ???
		if (/*m_instanceEndList.m_items.GetSize() == 0*/ !m_endAttr->get_specified())
		{
		//	if (m_dur == 0) m_dur = 99999; // TODO remove
	   // this calculates the active end with no end constraint
	      tempEnd = calcActiveEnd( *tempBegin );
		}
		else
		{
		// We have a begin value - get an end

			unsigned int i;

			// Set tempEnd = the first value in the end list that is >= tempBegin.
			for (i = 0; i < m_instanceEndList.m_items.GetSize(); i++)
			{
				if (*m_instanceEndList.m_items[i] >= *tempBegin)
				{
					tempEnd = *m_instanceEndList.m_items[i];
					break;
				}
			}

			// Allow for non-0-duration interval that begins immediately
			// after a 0-duration interval.
			if (tempEnd == *tempBegin /*&& TODO tempEnd has already been used in 
     an interval calculated in this method call*/)
			{
				// set tempEnd to the next value in the end list that is > tempEnd

				while (i < m_instanceEndList.m_items.GetSize())
				{
					if (*m_instanceEndList.m_items[i] > tempEnd)
					{
						tempEnd = *m_instanceEndList.m_items[i];
						break;
					}
					i++;
				}
			}

			// If there is no such value
			if (i == m_instanceEndList.m_items.GetSize())
			{
			// Events leave the end open-ended. If there are other conditions
			// that have not yet generated instances, they must be unresolved.

				if (true/*TODO endHasEventConditions()*/ || m_instanceEndList.m_items.size() == 0)
				{
					tempEnd = UNRESOLVED;
				}
				else
					return NULL;// If all ends are before the begin, bad interval
			}

			// this calculates the active dur with an end constraint
			tempEnd = calcActiveEnd(*tempBegin, tempEnd);
		}

		// We have an end - is it after the parent simple begin?
		// Handle the zero duration intervals at the parent begin time as a special case
		if (tempEnd > 0 || (*tempBegin == 0 && tempEnd == 0))
		{
			TimeInterval* pInterval = new TimeInterval;
		//	CComObject<CLTimeInterval>::CreateInstance(&pInterval);
		//	pInterval->AddRef();
			pInterval->m_pElement = this;
			pInterval->Set(tempBegin, *tempBegin, tempEnd);
			m_AD = tempEnd- *tempBegin;

			return pInterval;
		}
		else
		{
			// Change beginAfter to find next interval, and loop
			beginAfter = tempEnd;
		}
	}

	return NULL;
}

// Calculates the next acceptable interval for an element
// Returns:
//    Interval if there is such an interval
//    FAILURE if there is no such interval

TimeInterval* ElementTime::GetNextInterval()
{
// Note that at this point, the just ended interval is still the "current interval"

/*
If (currentInterval.end > currentInterval.begin)
Set tempBegin = the first value in the begin list that is >= beginAfter.
Else
Set tempBegin = the first value in the begin list that is > beginAfter.. 
*/

	double beginAfter = m_pCurrentInterval->m_end;

	int i;
	TimeInstance* tempBegin;
	if (m_pCurrentInterval->m_end > m_pCurrentInterval->m_begin)
	{
		// tempBegin = the first value in the begin list that is >= beginAfter.
		for (i = 0; i < m_instanceBeginList.m_items.GetSize(); i++)
		{
			if (*m_instanceBeginList.m_items[i] >= beginAfter)
			{
				tempBegin = m_instanceBeginList.m_items[i];
				break;
			}
		}
	}
	else
	{
		// tempBegin = the first value in the begin list that is > beginAfter.
		for (i = 0; i < m_instanceBeginList.m_items.GetSize(); i++)
		{
			if (*m_instanceBeginList.m_items[i] > beginAfter)
			{
				tempBegin = m_instanceBeginList.m_items[i];
				break;
			}
		}
	}

// If there is no such value  // No interval
	if (i == m_instanceBeginList.m_items.GetSize()) return NULL;
#if 0
	CComQIPtr<IElementTime> parent = static_cast<T*>(this)->m_parentNode;
	if (parent)
	{
		double parentSimpleEnd;
		parent->getSimpleDuration(&parentSimpleEnd);
		if (tempBegin >= parentSimpleEnd) // Can't begin after parent ends
			return NULL;
	}
#endif
	double tempEnd;

// If there was no end attribute specified
	bool bEnd;
//	bEnd = m_ownerElement->hasAttribute(WSTR("end"));
	bEnd = m_endAttr->get_specified();
	if (!bEnd)
	{
//		if (m_dur == 0) m_dur = 99999; // TODO remove
	// this calculates the active end with no end constraint
	   tempEnd = calcActiveEnd( *tempBegin );
	}
	else
	{
	// We have a begin value - get an end
		unsigned int i;
		// Set tempEnd = the first value in the end list that is >= tempBegin.
		for (i = 0; i < m_instanceEndList.m_items.GetSize(); i++)
		{
			if (*m_instanceEndList.m_items[i] >= *tempBegin)
			{
				tempEnd = *m_instanceEndList.m_items[i];
				break;
			}
		}

		if (i < m_instanceEndList.m_items.GetSize())
		{
			// Allow for non-0-duration interval that begins immediately
			// after a 0-duration interval.
			if (tempEnd == m_pCurrentInterval->m_end)
			{
			//	set tempEnd to the next value in the end list that is > tempEnd
				for (i = 0; i < m_instanceEndList.m_items.GetSize(); i++)
				{
					if (*m_instanceEndList.m_items[i] > tempEnd)
					{
						tempEnd = *m_instanceEndList.m_items[i];
						break;
					}
				}
			}
		}

		// If there is no such value
		if (i == m_instanceEndList.m_items.GetSize())
		{
		// Events leave the end open-ended. If there are other conditions
		// that have not yet generated instances, they must be unresolved.
#if 0
			if endHasEventConditions()
				OR if the instance list is empty
				tempEnd = UNRESOLVED;
			// if all ends are before the begin, bad interval
			else
#endif
				return NULL;
		}
		// this calculates the active dur with an end constraint
		tempEnd = calcActiveEnd( *tempBegin, tempEnd );
	}

	TimeInterval* pInterval = new TimeInterval;
	pInterval->Set(tempBegin, *tempBegin, tempEnd);
	m_AD = tempEnd - *tempBegin;

	return pInterval;
}

double ElementTime::ActiveTimeToSimpleTime(double tau)
{
	double AD = m_AD;//m_dur;// ? AD=Active Duration?
	double speed = m_speed;

	double acc = m_accelerate;
	double dec = m_decelerate;

	if (acc+dec > 1)	// Ignore both attributes
	{
		acc = 0;
		dec = 0;
	}

	double taf;

	if (speed > 0) // i.e. if the local speed is forwards 
		taf = tau * speed;
	else //  i.e. if the local speed is backwards 
		taf = AD - tau * fabs(speed);

	//Let dur be the value of the simple duration as defined by the Timing and Synchronization model.
	// This is the actual simple duration, and not simply the dur attribute.
	//This value does not account for the effect of any time manipulations.
	double dur = m_dur;
	ASSERT(dur >= 0);
	//if (dur < 0) dur = INDEFINITE;	// indefinite (Is this correct?)

	// m_simpleDur has accounted for autoReverse
	double dur_ = m_simpleDur;

#if 1	// Have something like this
	double tsu = REMAINDER(taf, dur_);
#else
	double tsu = taf;
#endif

	{	// ??
		m_iteration = (int)(taf/dur_);
	}

// Account for autoReverse behavior.
	double tsu_;

	if (m_autoReverse != true)
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

	double dacc = acc*dur;
	double ddec = dec*dur;

	double r = 1 / (1 - acc/2 - dec/2);

	if (tsu_ >= 0 && tsu_ < dacc)
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

//	tsf = tsf + m_iteration*dur_;	// ???? TODO remove this

	return tsf;
}

double ElementTime::SimpleTimeToActiveTime(double tsf)
{
//	return tsf;

	double dur = m_simpleDur;
	//elementTime->getSimpleDuration(&dur);

	double a = m_accelerate;
	double b = m_decelerate;

	double speed = m_speed;

	double dacc = a*dur;
	double ddec = b*dur;

//////////////////////////////////////////////////////////////////////
	double r = 1 / (1-a/2 - b/2);

	// acceleration interval
	double tsu_a;
	if (tsf >= 0)
	{
		tsu_a = sqrt((tsf * 2 * dacc)/r);
	}
	else
		tsu_a = -99999999;	// undefined (can't take sqrt of negative number)

	// run-rate interval
	double tsu_r = tsf/r + dacc/2;

	// deceleration interval
	double tsu_d;
	{
		double a = (-r)/(2*ddec);
		double b = (r*dur)/ddec;
		double c = r*dur - r*dacc/2 - r*ddec - (dur*dur*r)/(2*ddec) + ddec*r/2 - tsf;

		tsu_d = (-b + sqrt(b*b - 4*a*c)) / (2*a);
	}

	double tsu_;
	if ((((tsf * 2 * dacc)/r) >= 0) && tsu_a < dacc)
		tsu_ = tsu_a;
	else if (tsu_r <= dur-ddec)
		tsu_ = tsu_r;
	else
		tsu_ = tsu_d;

	double tsu = tsu_;

	double taf = tsu;

	double tau = taf/speed;

//	double B = m_x;
	//tps = tau + B;
	//st = tau + B;

	return tau;
}

// virtual
void ElementTime::Seek(/*[in]*/ double tps /*parent simple time*/)
{
	if (m_pCurrentInterval)
	{
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
						m_pCurrentInterval->m_bActive = true;

						InactiveToActive();
					}

					// Check if ending the current interval
					if (m_pCurrentInterval->m_bActive//m_parentSimpleTime < m_pCurrentInterval->m_end)
						&&	tps >= m_pCurrentInterval->m_end)	// From active to stopped
					{
						m_parentSimpleTime = m_pCurrentInterval->m_end;
						ActiveToInactive();
					//
						EndCurrentIntervalAt(m_pCurrentInterval->m_end);

						continue;
					}
					else
					{
						/* I'm not sure of the below code, has it something to
						do with the following from the spec?:

If an element specifies restart="never" then no further action is taken at the end of the interval, and the element sits in the "post interval" state unless and until an ascendant time container repeats or restarts. 

If an element specifies other values for restart, when it ends the current interval the element must reconsider the lists of resolved begin and end times
*/

						if (m_restart == RESTART_ALWAYS)
						{
							TimeInstance* pInstanceTime = GetNextInstanceTime(m_pCurrentInterval->m_begin);

							if (pInstanceTime &&
								(tps >= *pInstanceTime && *pInstanceTime < m_pCurrentInterval->m_end))
							{
								m_parentSimpleTime = *pInstanceTime;
								ActiveToInactive();

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
		else	// Seeking backwards
		{
			if (m_pCurrentInterval)
			{
				// Check if active interval goes back to being inactive
				if (	m_pCurrentInterval->m_bActive &&

						m_parentSimpleTime > m_pCurrentInterval->m_begin &&
						tps < m_pCurrentInterval->m_begin)	// From inactive to active
				{
					m_pCurrentInterval->m_bActive = false;

					ActiveToInactive();
				}
			}

			m_parentSimpleTime = tps;
		}

		tps = m_parentSimpleTime;	// ???
		tps -= m_clipBegin;	// ???

		//double parent_speed = 1;
	//	double AD = m_AD;//m_dur;// ? AD=Active Duration?
	//	double speed = m_speed->m_value->m_value;
		//if (speed == 0) speed = 0 ??

		m_tau = tps - m_pCurrentInterval->m_begin;

		double tsf = ActiveTimeToSimpleTime(m_tau);

		m_tsf = tsf;	// Filtered simple time
	}
}

/*
If a DOM method call is made to begin or end the element
(beginElement(), beginElementAt(), endElement() or endElementAt()), each method
call creates a single instance time (in the appropriate instance times list).
These time instances are cleared upon reset just as for event times
*/

/*
	Causes this element to begin the local timeline (subject to sync constraints). 
*/
bool ElementTime::beginElement()
{
// TODO
	TimeInstance* pInstanceTime = new TimeInstance;

	pInstanceTime->m_time = NULL;//m_begin->m_items[i];
	pInstanceTime->m_resolvedTime = m_tau;//pInstanceTime->m_time->m_offset;
	m_instanceBeginList.m_items.Add(pInstanceTime);

	m_pCurrentInterval = GetFirstInterval();	// ??

	if (m_pCurrentInterval)
	{
	// creating (new) interval notify syncbase dependants
		for (int i = 0; i < m_syncDependants.GetSize(); i++)
		{
			m_syncDependants[i]->NotifySync(m_ownerElement, m_pCurrentInterval/*, VARIANT_TRUE*//*begin*/);
		}

		/*
	// new end, tell parent time container
		CComQIPtr<ILTimeContainer> parentTimeContainer = static_cast<T*>(this)->m_parentNode;
		if (parentTimeContainer)
		{
		}
		*/
	}

	return true;
}

/*
Causes this element to begin the local timeline (subject to sync constraints),
at the passed offset from the current time when the method is called. If the
offset is >= 0, the semantics are equivalent to an event-base begin with the
specified offset. If the offset is < 0, the semantics are equivalent to
beginElement(), but the element active duration is evaluated as though the element
had begun at the passed (negative) offset from the current time when the method is
called. 
*/
bool ElementTime::beginElementAt(/*[in]*/ double offset)
{
// TODO
	TimeInstance* pInstanceTime = new TimeInstance;

	pInstanceTime->m_time = NULL;//m_begin->m_items[i];
	pInstanceTime->m_resolvedTime = m_tau + offset;//pInstanceTime->m_time->m_offset;
	m_instanceBeginList.m_items.Add(pInstanceTime);

	return true;
}

bool ElementTime::endElement()
{
// TODO
	VERIFY(0);
	return false;
}

bool ElementTime::endElementAt(/*[in]*/ double offset)
{
	VERIFY(0);
// TODO
	return false;
}

}	// Web
}
