#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEnumerationSpreadMethodTypeValue.h"

namespace System
{
namespace Web
{
/*
	SVG_SPREADMETHOD_UNKNOWN = 0,
	SVG_SPREADMETHOD_PAD     = 1,
	SVG_SPREADMETHOD_REFLECT = 2,
	SVG_SPREADMETHOD_REPEAT  = 3,
*/

static ImmutableString<WCHAR> SpreadMethodTypeStrings[] =
{
	WSTR("pad"),
	WSTR("reflect"),
	WSTR("repeat"),
};

SVGEnumerationSpreadMethodTypeValue::SVGEnumerationSpreadMethodTypeValue()
{
	// Set default value here ??
	m_value = SVG_SPREADMETHOD_PAD;
}

SVGEnumerationSpreadMethodTypeValue::operator SVGSpreadMethodType()
{
	return m_value;
}

SVGEnumerationSpreadMethodTypeValue& SVGEnumerationSpreadMethodTypeValue::operator = (SVGSpreadMethodType value)
{
	m_value = value;
	return *this;
}

SVGEnumerationSpreadMethodTypeValue& SVGEnumerationSpreadMethodTypeValue::operator += (SVGSpreadMethodType value)
{
	m_value = value;
	return *this;
}

void SetAsString(SVGEnumerationSpreadMethodTypeValue* p, StringIn str)
{
	for (int i = 0; i < _countof(SpreadMethodTypeStrings); i++)
	{
		if (str == String(&SpreadMethodTypeStrings[i]))
		{
			p->m_value = (SVGSpreadMethodType)(i+1);
			return;
		}
	}

// Unknown string value
	p->m_value = SVG_SPREADMETHOD_PAD;	// Set to default ?
}

String GetAsString(SVGEnumerationSpreadMethodTypeValue* p)
{
	return &SpreadMethodTypeStrings[p->m_value-1];
}

void SVGEnumerationSpreadMethodTypeValue::InterpolateValue(const SVGEnumerationSpreadMethodTypeValue& a, const SVGEnumerationSpreadMethodTypeValue& b, double t)
{
	m_value = a.m_value;
}

}	// Web
}
