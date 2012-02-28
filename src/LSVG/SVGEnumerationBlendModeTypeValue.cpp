#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEnumerationBlendModeTypeValue.h"

namespace System
{
namespace Web
{

/*
	SVG_FEBLEND_MODE_UNKNOWN  = 0,
	SVG_FEBLEND_MODE_NORMAL   = 1,
	SVG_FEBLEND_MODE_MULTIPLY = 2,
	SVG_FEBLEND_MODE_SCREEN   = 3,
	SVG_FEBLEND_MODE_DARKEN   = 4,
	SVG_FEBLEND_MODE_LIGHTEN  = 5,
*/

static ImmutableString<WCHAR> BlendModeTypeStrings[] =
{
	L"normal",
	L"multiply",
	L"screen",
	L"darken",
	L"lighten",
};

SVGEnumerationBlendModeTypeValue::SVGEnumerationBlendModeTypeValue()
{
	// Set default value here ??
	m_value = SVG_FEBLEND_MODE_NORMAL;
}

SVGEnumerationBlendModeTypeValue::operator SVGBlendModeType()
{
	return m_value;
}

SVGEnumerationBlendModeTypeValue& SVGEnumerationBlendModeTypeValue::operator = (SVGBlendModeType value)
{
	m_value = value;
	return *this;
}

SVGEnumerationBlendModeTypeValue& SVGEnumerationBlendModeTypeValue::operator += (SVGBlendModeType value)
{
	m_value = value;
	return *this;
}

void SetAsString(SVGEnumerationBlendModeTypeValue* p, StringIn str)
{
	for (int i = 0; i < _countof(BlendModeTypeStrings); i++)
	{
		if (str == String(&BlendModeTypeStrings[i]))
		{
			p->m_value = (SVGBlendModeType)(i+1);
			return;
		}
	}

// Unknown string value
	p->m_value = SVG_FEBLEND_MODE_NORMAL;	// Set to default ?
}

String GetAsString(SVGEnumerationBlendModeTypeValue* p)
{
	return &BlendModeTypeStrings[p->m_value-1];
}

void SVGEnumerationBlendModeTypeValue::InterpolateValue(SVGEnumerationBlendModeTypeValue& a, SVGEnumerationBlendModeTypeValue& b, double t)
{
	m_value = a.m_value;
}

}	// w3c
}
