#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEnumerationMorphologyOperatorValue.h"

namespace System
{
namespace Web
{

/*
	SVG_MORPHOLOGY_OPERATOR_UNKNOWN = 0,
	SVG_MORPHOLOGY_OPERATOR_ERODE   = 1,
	SVG_MORPHOLOGY_OPERATOR_DILATE  = 2,
*/

static ImmutableString<WCHAR> MorphologyOperatorStrings[] =
{
	WSTR("erode"),
	WSTR("dilate"),
};

SVGEnumerationMorphologyOperatorValue::SVGEnumerationMorphologyOperatorValue()
{
	// Set default value here ??
	m_value = SVG_MORPHOLOGY_OPERATOR_ERODE;
}

SVGEnumerationMorphologyOperatorValue::operator SVGMorphologyOperator()
{
	return m_value;
}

SVGEnumerationMorphologyOperatorValue& SVGEnumerationMorphologyOperatorValue::operator = (SVGMorphologyOperator value)
{
	m_value = value;
	return *this;
}

SVGEnumerationMorphologyOperatorValue& SVGEnumerationMorphologyOperatorValue::operator += (SVGMorphologyOperator value)
{
	m_value = value;
	return *this;
}

void SVGEnumerationMorphologyOperatorValue::setStringValue(StringIn str)
{
	for (int i = 0; i < sizeof(MorphologyOperatorStrings)/sizeof(WCHAR*); i++)
	{
		if (str == String(&MorphologyOperatorStrings[i]))
		{
			m_value = (SVGMorphologyOperator)(i+1);
			return;
		}
	}

// Unknown string value
	m_value = SVG_MORPHOLOGY_OPERATOR_ERODE;	// Set to default ?
}

String SVGEnumerationMorphologyOperatorValue::getStringValue()
{
	return &MorphologyOperatorStrings[m_value-1];
}

void SVGEnumerationMorphologyOperatorValue::InterpolateValue(SVGEnumerationMorphologyOperatorValue& a, SVGEnumerationMorphologyOperatorValue& b, double t)
{
	m_value = a.m_value;
}

}	// LSVG
}
