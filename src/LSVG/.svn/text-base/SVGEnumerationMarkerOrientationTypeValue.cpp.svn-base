#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEnumerationMarkerOrientationTypeValue.h"

namespace System
{
namespace Web
{
/*
typedef enum _LSVGMarkerOrientationType
{
	SVG_MARKER_ORIENT_UNKNOWN      = 0,
	SVG_MARKER_ORIENT_AUTO         = 1,
	SVG_MARKER_ORIENT_ANGLE        = 2,
}
LSVGMarkerOrientationType;
*/

SVGEnumerationMarkerOrientationTypeValue::SVGEnumerationMarkerOrientationTypeValue()
{
	// Set default value here ??
	m_value = SVG_MARKER_ORIENT_ANGLE;
}

SVGEnumerationMarkerOrientationTypeValue::operator SVGMarkerOrientationType()
{
	return m_value;
}

SVGEnumerationMarkerOrientationTypeValue& SVGEnumerationMarkerOrientationTypeValue::operator = (SVGMarkerOrientationType value)
{
	m_value = value;
	return *this;
}

SVGEnumerationMarkerOrientationTypeValue& SVGEnumerationMarkerOrientationTypeValue::operator += (SVGMarkerOrientationType value)
{
	m_value = value;
	return *this;
}

void SVGEnumerationMarkerOrientationTypeValue::setStringValue(StringIn str)
{
	if (str == L"auto")
	{
		m_value = SVG_MARKER_ORIENT_AUTO;
	}
	else
	{
		m_value = SVG_MARKER_ORIENT_ANGLE;
	}
}

String SVGEnumerationMarkerOrientationTypeValue::getStringValue()
{
	if (m_value == SVG_MARKER_ORIENT_AUTO)
		return WSTR("auto");
	else
		return NULL;
}

void SVGEnumerationMarkerOrientationTypeValue::InterpolateValue(const SVGEnumerationMarkerOrientationTypeValue& a, const SVGEnumerationMarkerOrientationTypeValue& b, double t)
{
	m_value = a.m_value;
}

}	// LSVG
}
