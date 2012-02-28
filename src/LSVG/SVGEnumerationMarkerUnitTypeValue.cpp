#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEnumerationMarkerUnitTypeValue.h"

namespace System
{
namespace Web
{

/*
// Marker Unit Types
typedef enum _LSVGMarkerUnitType
{
	SVG_MARKERUNITS_UNKNOWN        = 0,
	SVG_MARKERUNITS_USERSPACEONUSE = 1,
	SVG_MARKERUNITS_STROKEWIDTH    = 2,
}
LSVGMarkerUnitType;
*/

static ImmutableString<WCHAR> SVGMarkerUnitTypeStrings[] =
{
	WSTR("useSpaceOnUse"),
	WSTR("strokeWidth"),
};

SVGEnumerationMarkerUnitTypeValue::SVGEnumerationMarkerUnitTypeValue()
{
	// Set default value here ??
	m_value = SVG_MARKERUNITS_STROKEWIDTH;
}

SVGEnumerationMarkerUnitTypeValue::operator SVGMarkerUnitType()
{
	return m_value;
}

SVGEnumerationMarkerUnitTypeValue& SVGEnumerationMarkerUnitTypeValue::operator = (SVGMarkerUnitType value)
{
	m_value = value;
	return *this;
}

SVGEnumerationMarkerUnitTypeValue& SVGEnumerationMarkerUnitTypeValue::operator += (SVGMarkerUnitType value)
{
	m_value = value;
	return *this;
}

void SetAsString(SVGEnumerationMarkerUnitTypeValue* p, StringIn str)
{
	for (int i = 0; i < _countof(SVGMarkerUnitTypeStrings); i++)
	{
		if (str == String(&SVGMarkerUnitTypeStrings[i]))
		{
			p->m_value = (SVGMarkerUnitType)(i+1);
			return;
		}
	}

// TODO, element is in error now ???

// Unknown string value
	p->m_value = SVG_MARKERUNITS_STROKEWIDTH;	// Set to default ?
}

String GetAsString(SVGEnumerationMarkerUnitTypeValue* p)
{
	return String(&SVGMarkerUnitTypeStrings[p->m_value-1]);
}

void SVGEnumerationMarkerUnitTypeValue::InterpolateValue(const SVGEnumerationMarkerUnitTypeValue& a, const SVGEnumerationMarkerUnitTypeValue& b, double t)
{
	m_value = a.m_value;
}

}	// LSVG
}
