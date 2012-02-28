#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEnumerationCompositeOperatorValue.h"

namespace System
{
namespace Web
{

/*
	SVG_FECOMPOSITE_OPERATOR_OVER       = 1,
	SVG_FECOMPOSITE_OPERATOR_IN         = 2,
	SVG_FECOMPOSITE_OPERATOR_OUT        = 3,
	SVG_FECOMPOSITE_OPERATOR_ATOP       = 4,
	SVG_FECOMPOSITE_OPERATOR_XOR        = 5,
	SVG_FECOMPOSITE_OPERATOR_ARITHMETIC = 6,
*/

static ImmutableString<WCHAR> CompositeOperatorStrings[] =
{
	L"over",
	L"in",
	L"out",
	L"atop",
	L"xor",
	L"arithmetic",
};

SVGEnumerationCompositeOperatorValue::SVGEnumerationCompositeOperatorValue()
{
	// Set default value here ??
	m_value = SVG_FECOMPOSITE_OPERATOR_OVER;
}

SVGEnumerationCompositeOperatorValue::operator SVGCompositeOperatorType() const
{
	return m_value;
}

SVGEnumerationCompositeOperatorValue& SVGEnumerationCompositeOperatorValue::operator = (SVGCompositeOperatorType value)
{
	m_value = value;
	return *this;
}

SVGEnumerationCompositeOperatorValue& SVGEnumerationCompositeOperatorValue::operator += (SVGCompositeOperatorType value)
{
	m_value = value;
	return *this;
}

void SetAsString(SVGEnumerationCompositeOperatorValue* p, System::StringW* str)
{
	for (int i = 0; i < _countof(CompositeOperatorStrings); i++)
	{
		if (*str == CompositeOperatorStrings[i])
		{
			p->m_value = (SVGCompositeOperatorType)(i+1);
			return;
		}
	}

// Unknown string value
	p->m_value = SVG_FECOMPOSITE_OPERATOR_OVER;	// Set to default ?
}

System::StringW* GetAsString(SVGEnumerationCompositeOperatorValue* p)
{
	return &CompositeOperatorStrings[p->m_value-1];
}

void SVGEnumerationCompositeOperatorValue::InterpolateValue(const SVGEnumerationCompositeOperatorValue& a, const SVGEnumerationCompositeOperatorValue& b, double t)
{
	m_value = a.m_value;
}

}	// LSVG
}
