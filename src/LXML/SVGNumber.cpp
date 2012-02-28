#include "stdafx.h"
#include "LXML2.h"
#include "SVGNumber.h"

namespace System
{
namespace Web
{

SVGNumber::SVGNumber()
{
	m_value = 0;
}

SVGNumber::SVGNumber(double value)
{
	m_value = value;
}

double SVGNumber::get_value() const
{
	return m_value;
}

void SVGNumber::set_value(double newVal)
{
	if (m_value != newVal)
	{
		m_value = newVal;

		ASSERT(0);
#if 0
		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
#endif
	}
}

///////////////////

SVGNumber& SVGNumber::operator = (const SVGNumber& value)
{
	m_value = value.m_value;
	return *this;
}

SVGNumber::operator double () const
{
	return m_value;
}

// virtual
void SVGNumber::setStringValue(StringIn str)
{
	m_value = getfnumber(CStringw(str));
	//put_valueAsString(bstr);
}

// virtual
String SVGNumber::getStringValue()
{
	WCHAR buf[64];
	swprintf_s(buf, L"%g", m_value);
	return string_copy(buf);
}

// virtual
void SVGNumber::InterpolateValue(SVGNumber* a, SVGNumber* b, double t)
{
	m_value = a->m_value + (b->m_value - a->m_value)*t;
}

}	// Web
}	// System
