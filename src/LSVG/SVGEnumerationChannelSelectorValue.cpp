#include "stdafx.h"
#include "LSVG.h"
#include "LSVG2.h"
#include "SVGEnumerationChannelSelectorValue.h"

namespace System
{
namespace w3c
{

/*
	SVG_CHANNEL_UNKNOWN = 0,
	SVG_CHANNEL_R       = 1,
	SVG_CHANNEL_G       = 2,
	SVG_CHANNEL_B       = 3,
	SVG_CHANNEL_A       = 4,
*/

static __live_object_ptr<System::StringW> ChannelSelectorStrings[] =
{
	WSTR("R"),
	WSTR("G"),
	WSTR("B"),
	WSTR("A"),
};

SVGEnumerationChannelSelectorValue::SVGEnumerationChannelSelectorValue()
{
	// Set default value here ??
	m_value = SVG_CHANNEL_A;
}

SVGEnumerationChannelSelectorValue::operator SVGChannelSelector()
{
	return m_value;
}

SVGEnumerationChannelSelectorValue& SVGEnumerationChannelSelectorValue::operator = (SVGChannelSelector value)
{
	m_value = value;
	return *this;
}

SVGEnumerationChannelSelectorValue& SVGEnumerationChannelSelectorValue::operator += (SVGChannelSelector value)
{
	m_value = value;
	return *this;
}

void SVGEnumerationChannelSelectorValue::setStringValue(System::StringW* str)
{
	for (int i = 0; i < _countof(ChannelSelectorStrings); i++)
	{
		if (*str == *ChannelSelectorStrings[i])
		{
			m_value = (SVGChannelSelector)(i+1);
			return;
		}
	}

// Unknown string value
	m_value = SVG_CHANNEL_A;	// Set to default ?
}

System::StringW* SVGEnumerationChannelSelectorValue::getStringValue()
{
	return ChannelSelectorStrings[m_value-1];
}

void SVGEnumerationChannelSelectorValue::InterpolateValue(const SVGEnumerationChannelSelectorValue& a, const SVGEnumerationChannelSelectorValue& b, double t)
{
	m_value = a.m_value;
}

}	// LSVG
}
