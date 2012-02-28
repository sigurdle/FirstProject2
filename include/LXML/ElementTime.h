#ifndef w3c_ElementTime_h
#define w3c_ElementTime_h

#include "SMILTime.h"
#include "SMILTimeList.h"

//#include "SVGNumberValue.h"
//#include "BooleanValue.h"

namespace System
{
namespace Web
{

class ElementTime;

double ParseClockValue(StringVariant::const_iterator<WCHAR> s);

class WEBEXT EnumerationAnimRestartType :
	public CSingleObject
{
public:
	RestartType m_value;

	operator RestartType ()
	{
		return m_value;
	}

	EnumerationAnimRestartType& operator = (RestartType value)
	{
		m_value = value;
		return *this;
	}

	EnumerationAnimRestartType& operator += (RestartType value)
	{
		m_value = value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		if (str == L"always")		m_value = RESTART_ALWAYS;
		else if (str == L"never")	m_value = RESTART_NEVER;
		else if (str == L"whenNotActive") m_value = RESTART_WHEN_NOT_ACTIVE;
		else // if (!wcscmp(str_restart, WSTR("default")))
			m_value = RESTART_ALWAYS;
	}

	String getStringValue()
	{
		ASSERT(0);
		return WSTR("");
	}

	void InterpolateValue(const EnumerationAnimRestartType& a, const EnumerationAnimRestartType& b, double t)
	{
		ASSERT(0);
	}
};

class WEBEXT EnumerationAnimFillType :
	public CSingleObject
{
public:
	FillType m_value;

	CTOR EnumerationAnimFillType()
	{
		m_value = (FillType)-1;	// undefined
	}

	operator FillType () const
	{
		return m_value;
	}

	EnumerationAnimFillType& operator = (FillType value)
	{
		m_value = value;
		return *this;
	}

	EnumerationAnimFillType& operator += (FillType value)
	{
		m_value = value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		if (str == L"freeze")
			m_value = FILL_FREEZE;
		else if (str == L"remove")
			m_value = FILL_REMOVE;
		else
			ASSERT(0);
	}

	void InterpolateValue(EnumerationAnimFillType& a, EnumerationAnimFillType& b, double t)
	{
		ASSERT(0);
	}
};

#define REMAINDER(t, d) (t - d*floor(t/d))

/*
Indefinite compares "greater than" all resolved values, and UNRESOLVED is "greater than"
both resolved values and INDEFINITE
*/
#define INDEFINITE	999999998
#define UNRESOLVED	999999999

class WEBEXT TimeInstance : public System::Object
//	public ITimeInstance
{
public:
	CTOR TimeInstance()
	{
		m_time = NULL;
		m_syncbaseInterval = NULL;
	}

	operator double () const
	{
		return m_resolvedTime;//m_time->m_offset;
	}

	bool operator >= (double v) const
	{
		return (m_resolvedTime/*m_time->m_offset*/ >= v);
	}

	bool operator > (double v) const
	{
		return (m_resolvedTime > v);
	}

	bool operator < (double v) const
	{
		return !(*this > v);
	}

	SMILTime* get_time()
	{
		return m_time;
	}

public:

	double m_resolvedTime;

/*
Each instance time in one of the lists is associated with the specification
of a begin or end condition defined in the attribute syntax
*/
	SMILTime* m_time;

/*
If an instance time was defined as syncbase-values, the instance time will
maintain a time dependency relationship to the associated interval for the
syncbase element. This means that if the associated begin or end time of the
syncbase current interval changes, then the dependent instance time for this
element will change as well. 
*/

	TimeInterval* m_syncbaseInterval;	// TODO, I'm not currently using this, why not?

};

class WEBEXT InstanceTimeList
{
public:
	~InstanceTimeList()
	{
		for (unsigned int i = 0; i < m_items.GetSize(); i++)
		{
	//		m_items[i]->Release();
		}
		m_items.RemoveAll();
	}

	void Sort();

public:

	vector<TimeInstance*> m_items;
};

//class ElementTimeImpl;

class WEBEXT TimeInterval : public Object
{
public:
	CTOR TimeInterval()
	{
		m_pElement = NULL;
		m_bActive = false;

		m_beginTime = NULL;
	}

	void Set(TimeInstance* beginTime, double begin, double end)
	{
		m_beginTime = beginTime;
		m_begin = begin;
		m_end = end;
	}

	TimeInstance* get_beginInstanceTime() const
	{
		return m_beginTime;
	}

	double get_beginInstanceTime()
	{
		ASSERT(0);
		return 0;
	}

	double get_resolvedBegin()
	{
		return m_begin;
	}

	double get_resolvedEnd()
	{
		return m_end;
	}

	TimeInterval* getNextInterval()
	{
		return NULL;
	}

public:

	double m_begin;
	double m_end;
	TimeInstance* m_beginTime;	// ??
//	CInstanceTime* m_endTime;	// ??
	ElementTime* m_pElement;

	bool m_bActive;
};

#if 0
class WEBEXT ElementTimeImpl : public System::Object
{
public:
	CTOR ElementTimeImpl(Element* ownerElement) : m_ownerElement(ownerElement)
	{
		m_iteration = 0;
	}

	virtual ~ElementTimeImpl()
	{
	}

	virtual void NotifySync(Element* syncbaseElement, TimeInterval* pInterval/*, bool baseBegin*/) = 0;
	virtual TimeInterval* GetFirstInterval() = 0;

	virtual void Init() = 0;
	virtual void Init2() = 0;
	virtual void Reset() = 0;
	virtual void Run() = 0;
	virtual void CalculateSimpleDuration() = 0;
	virtual IElementTimeContainer* get_parentTimeContainer() = 0;

//	virtual void RecalculateTime() = 0;	// Called when one of the children have changed
	virtual void CalculateTimeBeforeParent() = 0;	// Called by parent
	virtual void CalculateTimeAfterParent() = 0;	// Called by parent

	virtual void Seek(double tps);

	double ActiveTimeToSimpleTime(double tau);
	double SimpleTimeToActiveTime(double tsf);

// Seek is only implemented here and calls Activate/Deactivate handled by
// the classes derived from IElementTime

	virtual void ActiveToInactive()
	{
	}

	virtual void InactiveToActive()
	{
	}

	virtual void EndCurrentIntervalAt(double endt) = 0;

	TimeInstance* GetNextInstanceTime(double beginAfter)
	{
		//double beginAfter = m_pCurrentInterval->m_begin;

		//double tempBegin;

		int i;
		for (i = 0; i < m_instanceBeginList.m_items.GetSize(); i++)
		{
			if (*m_instanceBeginList.m_items[i] > beginAfter)
			{
			//	tempBegin = *m_instanceBeginList.m_items[i];
				break;
			}
		}

		if (i < m_instanceBeginList.m_items.GetSize())
		{
//			if (*m_instanceBeginList.m_items[i] < m_pCurrentInterval->m_end)
			{
				return m_instanceBeginList.m_items[i];
			}
		}

		return NULL;
	}

public:

	double m_parentSimpleTime;

	Element* m_ownerElement;

	int m_iteration;

	double m_tau;	// Unfiltered active time
	double m_tsf;	// Filtered simple time

	double m_dur;	// 'dur' attribute, desired simple time (<0 means indefinite)
	double m_AD;	// Active Duration
	double m_simpleDur;	// Simple duration (autoReverse Accounted for)

	double m_clipBegin;	// TODO, improve

//	CComObject<CXMLAttr2T<CComObjectCreateInstance<CValueTypeWrapper<CLClockValue> > > >* m_dur;

	InstanceTimeList m_instanceBeginList;
	InstanceTimeList m_instanceEndList;
	vector<TimeInterval*> m_intervals;
	TimeInterval* m_pCurrentInterval;

	vector<ElementTimeImpl*> m_syncDependants;

//	CComObject<CXMLAttr2T<CComObjectCreateInstance<CValueTypeWrapper<CDurationValue> > > >* m_dur;

	SMILTimeList* m_begin;
	SMILTimeList* m_end;
	double m_repeatCount;
	double m_repeatDur;
	AnimRestartType m_restart;
	AnimFillType m_fill;
	double m_accelerate;
	double m_decelerate;
	double m_speed;
	bool m_autoReverse;

	Attr* m_durAttr;
	Attr* m_beginAttr;
	Attr* m_endAttr;
	Attr* m_repeatDurAttr;
	Attr* m_restartAttr;
	Attr* m_fillAttr;
	Attr* m_accelerateAttr;
	Attr* m_decelerateAttr;
	Attr* m_speedAttr;
	Attr* m_autoReverseAttr;
};
#endif

class WEBEXT ElementTime : public Object//ElementTimeImpl
{
public:
	CTOR ElementTime(Element* ownerElement);
	~ElementTime();

#if 0
	int FinalConstruct()
	{
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_restart, WSTR(""), WSTR("restart"), WSTR("always")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_repeatCount, WSTR(""), WSTR("repeatCount"), WSTR("1")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_repeatDur, WSTR(""), WSTR("repeatDur"), WSTR("0")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_fill, WSTR(""), WSTR("fill"), WSTR("remove")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_accelerate, WSTR(""), WSTR("accelerate"), WSTR("0")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_decelerate, WSTR(""), WSTR("decelerate"), WSTR("0")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_speed, WSTR(""), WSTR("speed"), WSTR("1")));
		static_cast<T*>(this)->AddXMLAttribute(NewNXMLAttr(&m_autoReverse, WSTR(""), WSTR("autoReverse"), WSTR("false")));

		NewNXMLAttr(&m_begin, WSTR(""), WSTR("begin"), WSTR("0s"));
		m_begin->m_value->m_value->m_ownerElement = static_cast<T*>(this);
		static_cast<T*>(this)->AddXMLAttribute(m_begin);
	//	m_begin->m_pListener = this;

		NewNXMLAttr(&m_end, WSTR(""), WSTR("end"), NULL);
		m_end->m_value->m_value->m_ownerElement = static_cast<T*>(this);
		static_cast<T*>(this)->AddXMLAttribute(m_end);
	//	m_end->m_pListener = this;

		return S_OK;
	}

	void FinalRelease()
	{
		if (m_pCurrentInterval)
		{
			m_pCurrentInterval->Release();
			m_pCurrentInterval = NULL;
		}
	}
#endif

	/*
	virtual void OnChanged(CSingleObject* pObject)
	{
		if (pObject == m_begin->m_value->m_value)
		{
			m_begin->OnBaseValChanged();
		}
		else if (pObject == m_end->m_value->m_value)
		{
			m_end->OnBaseValChanged();
		}
	}
	*/

	virtual double GetIntrinsicDuration()
	{
		return 0;
	}

	virtual double GetImplicitDuration()
	{
		ASSERT(0);
		return 0;
#if 0
		double intrinsic = GetIntrinsicDuration();

		double clipEnd = intrinsic-m_clipBegin;
		{
			CComBSTR str;
			static_cast<T*>(this)->getAttribute(WSTR("clipEnd"), &str);
			if ((BSTR)str != NULL)
			{
				clipEnd = atof(_bstr_t(str));
			}
		}

		return clipEnd-m_clipBegin;
#endif
	}

	// Define simple duration
	virtual void CalculateSimpleDuration();

	virtual IElementTimeContainer* get_parentTimeContainer();

// Called before children have been initialized
	virtual void Init();

// Called after children have been initialized
	virtual void Init2();

	virtual void EndCurrentIntervalAt(double endt);


//	CArray<IElementTime*,IElementTime*> m_syncDependants;
//	CArray<CLElementTimeImpl*,CLElementTimeImpl*> m_syncDependants;

/*
SMIL:

When a time container repeats or restarts, all descendent children are "reset" with
respect to certain state: 

Any instance times associated with past event-values, repeat-values,
accesskey-values or added via DOM method calls are removed from the dependent
begin and end instance times lists. In effect, all events and DOM methods
calls in the past are cleared. This does not apply to an instance time that
defines the begin of the current interval. 

Any syncbase times are reevaluated (i.e. the translation between timespaces
must be recalculated - see Converting between local and global times). 
A resolved syncbase time is removed from the dependent instance time list
when a common ascendant of the syncbase and the dependent element restarts
or repeats 

Any state associated with the interpretation of the restart semantics is
reset. 
*/
	virtual void Reset()
	{
		ASSERT(0);
#if 0
		m_tau = -1;
		m_parentSimpleTime = -1;

		if (m_pCurrentInterval)
		{
			m_pCurrentInterval->Release();
			m_pCurrentInterval = NULL;
		}

		{
			CComPtr<ILDOMNode> node;
			((ILDOMNode*)static_cast<T*>(this))->get_firstChild(&node);
			while (node)
			{
				CComQIPtr<CLElementTimeImpl, &IID_IUnknown/*TODO*/> elementTime((IUnknown*)node);
				if (elementTime)
				{
					elementTime->Reset();
				}

				CComPtr<ILDOMNode> nextSibling;
				node->get_nextSibling(&nextSibling);
				node = nextSibling;
			}
		}

		Init2();	// Create first interval ?
		//m_pCurrentInterval = GetFirstInterval();	// ????

		{
			CComPtr<ILDOMNode> node;
			((ILDOMNode*)static_cast<T*>(this))->get_firstChild(&node);
			while (node)
			{
				CComQIPtr<CLElementTimeImpl, &IID_IUnknown/*TODO*/> elementTime((IUnknown*)node);
				if (elementTime)
				{
					elementTime->Init2();
				}

				CComPtr<ILDOMNode> nextSibling;
				node->get_nextSibling(&nextSibling);
				node = nextSibling;
			}
		}
#endif
	}

/*
SMIL: * 10.3.3 Semantics of the Timing Model *

	When a dependent element gets a "new interval" notice, this includes a reference
	to the new interval. The new interval will generally have a resolved begin time
	and may have a resolved end time. An associated instance time will be added to the
	begin or end instance time list for the dependent element, and this new instance
	time will maintain a time dependency relationship to the syncbase interval. 

  Also:
	If the element receives a "new interval" notice while it is active, it will add
	the associated time (i.e. the begin or end time of the syncbase interval) to the
	appropriate list of resolved times. If the new interval adds a time to the begin
	list, restart semantics are considered, and this may end the current interval

*/

	// virtual
	void NotifySync(Element* syncbaseElement, TimeInterval* pInterval/*, bool baseBegin*/)
	{
		ASSERT(0);
#if 0
/*
	Each time the syncbase element creates a new interval, the condition yields
	a single instance time. The time plus or minus any offset is added to the
	list
*/
		int i;

		for (i = 0; i < m_begin->m_value->m_value->m_items.GetSize(); i++)
		{
			CComObject<SMILTime>* pTime = m_begin->m_value->m_value->m_items[i];

			CComPtr<ILDOMElement> baseElement;
			pTime->get_baseElement(&baseElement);

			if (baseElement == syncbaseElement)
			{
				TimeInstance* pInstanceTime = new TimeInstance;

				pInstanceTime->m_time = pTime;

			// TODO, check that the appropriate time is resolved?
				pTime->m_resolved = VARIANT_TRUE;
				if (pTime->m_baseBegin)	// ??
					pTime->m_resolvedOffset = pInterval->m_begin + pTime->m_offset;
				else
					pTime->m_resolvedOffset = pInterval->m_end + pTime->m_offset;

				pInstanceTime->m_resolvedTime = pTime->m_resolvedOffset;//pInterval->m_end + pTime->m_offset;

				//if (pTime->m_baseBegin)
				{
					static_cast<T*>(this)->m_instanceBeginList.m_items.Add(pInstanceTime);

/*
1
When the current interval is playing, if restart="always" then any instance time
(call it T) in the begin list that is after (i.e. later than) the current
interval begin but earlier than the current interval end will cause the current
interval to end at time T. This is the first step in restarting the element:
when the current interval ends, that in turn will create any following interval. 

2.
....
	-If the current interval is waiting to play, the element recalculates the begin and
	end times for the current interval, as described in the Element life-cycle step 1
	(for the first interval) or step 4 (for all later intervals). If either the begin
	or end time of the current interval changes, these changes must be propagated to
	time dependents accordingly. 

	-If the current interval is playing (i.e. it is active), then the restart setting determines the behavior: 
		If restart="never" then nothing more is done. It is possible (if the new instance time is associated with a syncbase value condition) that the new instance time will be used the next time the element life cycle begins. 
		If restart="whenNotActive" then nothing more is done. If the time falls within the current interval, the element cannot restart, and if it falls after, then the normal processing at the end of the current interval will handle it. If the time falls before the current interval, as can happen if the time includes a negative offset, the element does not restart (the new instance time is effectively ignored). 
		If restart="always" then case 1 above applies, and will cause the current interval to end. 

*/
					if (m_pCurrentInterval)
					{
						if (!m_pCurrentInterval->m_bActive)	// Waiting to play
						{
							// TODO ASSERT(0);
						}
						else	// Current interval is playing
						{
							if (m_restart->m_value->m_value == RESTART_ALWAYS)
							{
								TimeInstance* pInstanceTime = GetNextInstanceTime(m_pCurrentInterval->m_begin + m_tau);

								if (pInstanceTime &&
									(*pInstanceTime < m_pCurrentInterval->m_end))
								{
									EndCurrentIntervalAt(*pInstanceTime);
								}
							}
						}
					}
					else
					{
						// ??
						m_pCurrentInterval = GetFirstInterval();

						if (m_pCurrentInterval)
						{
						// creating (new) interval notify syncbase dependants
							for (int i = 0; i < m_syncDependants.GetSize(); i++)
							{
								m_syncDependants[i]->NotifySync(static_cast<T*>(this), m_pCurrentInterval/*, VARIANT_TRUE*//*begin*/);
							}
						}
					}
				}
			}
		}

		m_instanceBeginList.Sort();

		for (i = 0; i < m_end->m_value->m_value->m_items.GetSize(); i++)
		{
		// TODO,

			//static_cast<T*>(this)->m_instanceEndList.m_items.Add(pInstanceTime);
		}
#endif
	}

	double calcActiveEnd(double begin, double end = INDEFINITE /* no end constraint*/);

	TimeInterval* GetFirstInterval();

// Calculates the next acceptable interval for an element
// Returns:
//    Interval if there is such an interval
//    FAILURE if there is no such interval
	TimeInterval* GetNextInterval();

// IElementTime
	FillType get_fill()
	{
		return m_fill;
	}

	void set_fill(FillType newVal)
	{
		ASSERT(0);
	}

	double get_repeatCount()
	{
		return m_repeatCount;
	}

	void set_repeatCount(double newVal)
	{
		ASSERT(0);
	}

	double get_repeatDur()
	{
		return m_repeatDur;
	}

	void set_repeatDur(double newVal)
	{
		ASSERT(0);
	}

	double get_dur()
	{
		return m_dur;
	}

	void set_dur(double newVal)
	{
		ASSERT(0);
		//m_dur = newVal;
	}

	RestartType get_restart()
	{
		return m_restart;
	}

	void set_restart(RestartType newVal)
	{
		ASSERT(0);
	}

	SMILTimeList* get_begin()
	{
		return m_begin;
	}

	SMILTimeList* get_end()
	{
		return m_end;
	}

	void seekElement( double seekTo)
	{
		// TODO
		m_tau = seekTo;
	}

// Time manipulation
	double get_speed()
	{
		//Web::SVGNumberValue* v = m_speed->m_value->m_object->m_value;
	
	//	CValueTypeWrapper<CreateInstance<EnumerationAnimFillType> > >& v = m_speed->m_value;

		return m_speed;
	//	return m_speed->m_value->m_object->m_value;
		//*pVal = m_speed->m_value->m_value->m_value;
	}
	void set_speed(double newVal)
	{
		ASSERT(0);
	}
	double get_accelerate()
	{
		return m_accelerate;
	}
	void set_accelerate(double newVal)
	{
		ASSERT(0);
	}
	double get_decelerate()
	{
		return m_decelerate;
	}
	void set_decelerate(double newVal)
	{
		ASSERT(0);
	}
	bool get_autoReverse()
	{
		return m_autoReverse;
	}
	void set_autoReverse(bool newVal)
	{
		ASSERT(0);
	}

	virtual void Run()
	{
	}

#if 0
	virtual void Seek(/*[in]*/ double tps /*parent simple time*/)
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
							m_pCurrentInterval->m_bActive = TRUE;

							InactiveToActive();

							//static_cast<CLSMILRegionElement*>(region.p)->Activate(m_pCurrentInterval->m_begin, this);
						}

						// Check if ending the current interval
						if (m_pCurrentInterval->m_bActive//m_parentSimpleTime < m_pCurrentInterval->m_end)
							&&	tps >= m_pCurrentInterval->m_end)	// From active to stopped
						{
							ActiveToInactive();
						//
							m_parentSimpleTime = m_pCurrentInterval->m_end;
							EndCurrentIntervalAt(m_pCurrentInterval->m_end);

							continue;
						}
						else
						{
							if (m_restart->m_value->m_value == RESTART_ALWAYS)
							{
								TimeInstance* pInstanceTime = GetNextInstanceTime(m_pCurrentInterval->m_begin);

								if (pInstanceTime &&
									(tps >= *pInstanceTime && *pInstanceTime < m_pCurrentInterval->m_end))
								{
									ActiveToInactive();

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
			else	// Seeking backwards
			{
				{
					if (m_pCurrentInterval)
					{
						// Check if active interval goes back to being inactive
						if (	m_pCurrentInterval->m_bActive &&

								m_parentSimpleTime > m_pCurrentInterval->m_begin &&
								tps < m_pCurrentInterval->m_begin)	// From inactive to active
						{
							m_pCurrentInterval->m_bActive = FALSE;

							ActiveToInactive();
							/*
						// Remove from sandwich model
							UPOSITION pos = pAnimationTarget->m_animationList.Find(static_cast<CLAnimationElement*>(this));
							ASSERT(pos);
							pAnimationTarget->m_animationList.RemoveAt(pos);
							*/

							//pThis->m_parentSimpleTime = pThis->m_pCurrentInterval->m_end;
							//pThis->EndCurrentIntervalAt(pThis->m_pCurrentInterval->m_end);
						}
					}

					m_parentSimpleTime = tps;
				}
			}

			double parent_speed = 1;
			double AD = m_AD;//m_dur;// ? AD=Active Duration?
			double speed = m_speed->m_value->m_value;
			double acc = m_accelerate->m_value->m_value;
			double dec = m_decelerate->m_value->m_value;

			if (acc+dec > 1)	// Ignore both attributes
			{
				acc = 0;
				dec = 0;
			}
			//if (speed == 0) speed = 0 ??

			m_tau = tps - m_pCurrentInterval->m_begin;

			double taf;

			if (speed > 0) // i.e. if the local speed is forwards 
				taf = m_tau * speed;
			else //  i.e. if the local speed is backwards 
				taf = AD - m_tau * fabs(speed);

			//Let dur be the value of the simple duration as defined by the Timing and Synchronization model.
			// This is the actual simple duration, and not simply the dur attribute.
			//This value does not account for the effect of any time manipulations.
			double dur = m_dur;
			if (dur < 0) dur = INDEFINITE;	// indefinite (Is this correct?)

			// pThis->m_simpleDur has accounted for autoReverse
			double dur_ = m_simpleDur;

			double tsu = REMAINDER(taf, dur_);

			{	// ??
				m_iteration = (int)(taf/dur_);
			}

		// Account for autoReverse behavior.
			double tsu_;

			if (m_autoReverse->m_value->m_value != VARIANT_TRUE)
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

			m_tsf = tsf;
		}
	}
#endif

#if 0	// Had this
	void Hyperlink(ILSVGSVGElement* svgsvgElement, double currentTime)
	{
		if (m_pCurrentInterval && m_pCurrentInterval->m_bActive)
		{
			ASSERT(0);
		}
		else
		{
			double tempBegin = INDEFINITE;//?? 999999999;
			for (int i = 0; i < m_instanceBeginList.m_items.GetSize(); i++)
			{
				if (*m_instanceBeginList.m_items[i] < tempBegin)
				{
					tempBegin = *m_instanceBeginList.m_items[i];
					//break;
				}
			}

			if (tempBegin < INDEFINITE)
			{
				svgsvgElement->setCurrentTime(tempBegin);
			}
			else
			{
				TimeInstance* pInstanceTime = new TimeInstance;

				pInstanceTime->m_time = NULL;//m_begin->m_items[i];
				pInstanceTime->m_resolvedTime = currentTime;//pInstanceTime->m_time->m_offset;
				m_instanceBeginList.m_items.Add(pInstanceTime);

				m_pCurrentInterval = GetFirstInterval();	// ??

				if (m_pCurrentInterval)
				{
				// creating (new) interval notify syncbase dependants
					for (int i = 0; i < m_syncDependants.GetSize(); i++)
					{
						m_syncDependants[i]->NotifySync(static_cast<T*>(this), m_pCurrentInterval/*, VARIANT_TRUE*//*begin*/);
					}
				}
			}
		}
	}
#endif
/*
If a DOM method call is made to begin or end the element
(beginElement(), beginElementAt(), endElement() or endElementAt()), each method
call creates a single instance time (in the appropriate instance times list).
These time instances are cleared upon reset just as for event times
*/

/*
	Causes this element to begin the local timeline (subject to sync constraints). 
*/
	bool beginElement();

/*
	Causes this element to begin the local timeline (subject to sync constraints),
	at the passed offset from the current time when the method is called. If the
	offset is >= 0, the semantics are equivalent to an event-base begin with the
	specified offset. If the offset is < 0, the semantics are equivalent to
	beginElement(), but the element active duration is evaluated as though the element
	had begun at the passed (negative) offset from the current time when the method is
	called. 
*/
	bool beginElementAt(/*[in]*/ double offset);

	bool endElement();

	bool endElementAt(/*[in]*/ double offset);

// Extensions
	double get_simpleTime()
	{
		return m_tsf;
	}

	double get_activeTime()
	{
		return m_tau;
	}

	double getSimpleDuration()
	{
		return m_simpleDur;
	}

	double getActiveDuration()
	{
		return m_AD;
	}

	TimeInterval* get_currentInterval()
	{
		return m_pCurrentInterval;
	}

	/*
	double ActiveTimeToSimpleTime(double tau)
	{
		return ElementTimeImpl::ActiveTimeToSimpleTime(tau);
	}
	*/

#if 0
	STDMETHODIMP SimpleTimeToActiveTime(double tsf, double* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = ElementTimeImpl::SimpleTimeToActiveTime(tsf);
		return S_OK;
	}
#endif

	virtual void Seek(double tps);

	double ActiveTimeToSimpleTime(double tau);
	double SimpleTimeToActiveTime(double tsf);

// Seek is only implemented here and calls Activate/Deactivate handled by
// the classes derived from IElementTime

	virtual void ActiveToInactive()
	{
	}

	virtual void InactiveToActive()
	{
	}

	TimeInstance* GetNextInstanceTime(double beginAfter)
	{
		//double beginAfter = m_pCurrentInterval->m_begin;

		//double tempBegin;

		unsigned int i;
		for (i = 0; i < m_instanceBeginList.m_items.size(); i++)
		{
			if (*m_instanceBeginList.m_items[i] > beginAfter)
			{
			//	tempBegin = *m_instanceBeginList.m_items[i];
				break;
			}
		}

		if (i < m_instanceBeginList.m_items.size())
		{
//			if (*m_instanceBeginList.m_items[i] < m_pCurrentInterval->m_end)
			{
				return m_instanceBeginList.m_items[i];
			}
		}

		return NULL;
	}

public:

	double m_parentSimpleTime;

	Element* m_ownerElement;

	int m_iteration;

	double m_tau;	// Unfiltered active time
	double m_tsf;	// Filtered simple time

	double m_dur;			// 'dur' attribute, desired simple time (<0 means indefinite)
	double m_simpleDur;	// Simple duration (autoReverse Accounted for)
	double m_AD;	// Active Duration

	double m_clipBegin;	// TODO, improve

//	CComObject<CXMLAttr2T<CComObjectCreateInstance<CValueTypeWrapper<CLClockValue> > > >* m_dur;

	InstanceTimeList m_instanceBeginList;
	InstanceTimeList m_instanceEndList;
	vector<TimeInterval*> m_intervals;
	TimeInterval* m_pCurrentInterval;

	vector<ElementTime*> m_syncDependants;

//	CComObject<CXMLAttr2T<CComObjectCreateInstance<CValueTypeWrapper<CDurationValue> > > >* m_dur;

	SMILTimeList* m_begin;
	SMILTimeList* m_end;
	double m_repeatDur;
	double m_repeatCount;
	double m_accelerate;
	double m_decelerate;
	double m_speed;
	RestartType m_restart;
	FillType m_fill;
	bool m_autoReverse;

	Attr* m_durAttr;
	Attr* m_beginAttr;
	Attr* m_endAttr;
	Attr* m_repeatDurAttr;
	Attr* m_repeatCountAttr;
	Attr* m_restartAttr;
	Attr* m_fillAttr;
	Attr* m_accelerateAttr;
	Attr* m_decelerateAttr;
	Attr* m_speedAttr;
	Attr* m_autoReverseAttr;
};

}	// w3c
}

#endif	// w3c_ElementTime_h
