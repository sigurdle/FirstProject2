#ifndef Web_SMILTime_h
#define Web_SMILTime_h

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class WEBEXT SMILTime : public CSingleObject
{
public:
	CTOR SMILTime();

	String ToString();

	void setTimeIndefinite();
	void setTimeOffset(double offset);
	void setTimeSyncbased(StringIn baseElement, bool baseBegin, double offset);

	void resolveTimeEvent(double currentTime, Event* evt);
	String get_marker();
	void set_marker(StringIn newVal);
	String get_event() const;
	void set_event(StringIn newVal);
	double get_resolvedOffset() const;
	bool get_resolved() const;
	bool get_baseBegin();
	void set_baseBegin(bool newVal);
	Element* get_baseElement();
	void set_baseElement(Element* newVal);
	double get_offset();
	void set_offset(double newVal);
	TimeType get_timeType() const;

	bool parseString(/*IDOMDocument* document,*/ StringIn s);

	bool operator < (const SMILTime& other) const
	{
		if (m_resolved && !other.m_resolved)
		{
			return true;
		}
		else if (!m_resolved && other.m_resolved)
		{
			return false;
		}

		return (m_resolvedOffset < other.m_resolvedOffset);
	}

	bool operator > (const SMILTime& other) const
	{
		// TODO: This isn't correct, they could be equal
		//return !(*this < other);

		return other < *this;
	}

public:

	double m_resolvedOffset;
	double m_offset;
	String m_eventElementId;
	String m_event;
	Element* m_ownerElement;
	TimeType m_type;
	bool m_baseBegin;
	bool m_resolved;

protected:

	Element* m_baseElement;
};

}	// Web
}

#endif // Web_SMILTime_h
