#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEnumerationComponentTransferTypeValue.h"

namespace System
{
namespace Web
{

/*
	SVG_FECOMPONENTTRANSFER_TYPE_UNKNOWN  = 0,
	SVG_FECOMPONENTTRANSFER_TYPE_IDENTITY = 1,
	SVG_FECOMPONENTTRANSFER_TYPE_TABLE    = 2,
	SVG_FECOMPONENTTRANSFER_TYPE_DISCRETE = 3,
	SVG_FECOMPONENTTRANSFER_TYPE_LINEAR   = 4,
	SVG_FECOMPONENTTRANSFER_TYPE_GAMMA    = 5,
*/

static ImmutableString<WCHAR> ComponentTransferTypeStrings[] =
{
	WSTR("identity"),
	WSTR("table"),
	WSTR("discrete"),
	WSTR("linear"),
	WSTR("gamma"),
};

SVGEnumerationComponentTransferTypeValue::SVGEnumerationComponentTransferTypeValue()
{
	// Set default value here ??
	m_value = SVG_FECOMPONENTTRANSFER_TYPE_UNKNOWN;	// It's required
}

SVGEnumerationComponentTransferTypeValue::operator SVGComponentTransferType()
{
	return m_value;
}

SVGEnumerationComponentTransferTypeValue& SVGEnumerationComponentTransferTypeValue::operator = (SVGComponentTransferType value)
{
	m_value = value;
	return *this;
}

SVGEnumerationComponentTransferTypeValue& SVGEnumerationComponentTransferTypeValue::operator += (SVGComponentTransferType value)
{
	m_value = value;
	return *this;
}

void SetAsString(SVGEnumerationComponentTransferTypeValue* p, StringIn str)
{
	for (int i = 0; i < _countof(ComponentTransferTypeStrings); i++)
	{
		if (str == String(&ComponentTransferTypeStrings[i]))
		{
			p->m_value = (SVGComponentTransferType)(i+1);
			return;
		}
	}

// Unknown string value
	p->m_value = SVG_FECOMPONENTTRANSFER_TYPE_UNKNOWN;
}

String GetAsString(SVGEnumerationComponentTransferTypeValue* p)
{
	if (p->m_value != SVG_FECOMPONENTTRANSFER_TYPE_UNKNOWN)
		return &ComponentTransferTypeStrings[p->m_value-1];
	else
		return NULL;
}

void SVGEnumerationComponentTransferTypeValue::InterpolateValue(SVGEnumerationComponentTransferTypeValue& a, SVGEnumerationComponentTransferTypeValue& b, double t)
{
	m_value = a.m_value;
}

}
}
