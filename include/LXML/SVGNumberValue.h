#ifndef __SVGNUMBERVALUE_H
#define __SVGNUMBERVALUE_H

namespace System
{
namespace Web
{

class WEBEXT SVGNumberValue :
	public CSingleObject
{
public:
	double m_value;

	CTOR SVGNumberValue()
	{
		m_value = 0;
	}

	/*
	SVGNumberValue& operator * ()
	{
		return *this;
	}
	*/

	SVGNumberValue* operator -> ()
	{
		return this;
	}

	/*
	operator SVGNumberValue* ()
	{
		return this;
	}
	*/

	SVGNumberValue& operator = (const SVGNumberValue& value)
	{
		m_value = value;
		return *this;
	}

	SVGNumberValue& operator += (const SVGNumberValue& value)
	{
		m_value += value;
		return *this;
	}

	SVGNumberValue& operator = (double value)
	{
		m_value = value;
		return *this;
	}

	inline operator double () const
	{
		return m_value;
	}

	void setString(StringIn str)
	{
		m_value = getfnumber(CString(str).c_str());
	}

	void setStringValue(StringIn str)
	{
		m_value = getfnumber(CString(str).c_str());
	}

	String getStringValue() const
	{
		WCHAR buf[64];
//#if _WINDOWS
		swprintf_s(buf, L"%g", m_value);
//#else
//		sprintf(buf, ("%g"), m_value);
//#endif
		return string_copy(buf);
	}

	void InterpolateValue(const SVGNumberValue& a, const SVGNumberValue& b, double t)
	{
		m_value = a.m_value + (b.m_value - a.m_value)*t;
	}
};

}	// Web
}

#endif	// __SVGNUMBERVALUE_H
