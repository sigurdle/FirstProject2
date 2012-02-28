#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEnumerationColorMatrixTypeValue.h"

namespace System
{
namespace Web
{

/*
	SVG_FECOLORMATRIX_TYPE_UNKNOWN          = 0,
	SVG_FECOLORMATRIX_TYPE_MATRIX           = 1,
	SVG_FECOLORMATRIX_TYPE_SATURATE         = 2,
	SVG_FECOLORMATRIX_TYPE_HUEROTATE        = 3,
	SVG_FECOLORMATRIX_TYPE_LUMINANCETOALPHA = 4,
*/

ValueHandlerT<SVGEnumerationColorMatrixTypeValue> ValueHandlerT<SVGEnumerationColorMatrixTypeValue>::s_valueHandler;

static ImmutableString<WCHAR> ColorMatrixTypeStrings[] =
{
	WSTR("matrix"),
	WSTR("saturate"),
	WSTR("hueRotate"),
	WSTR("luminanceToAlpha"),
};

SVGEnumerationColorMatrixTypeValue::SVGEnumerationColorMatrixTypeValue()
{
	// Set default value here ??
	m_value = SVG_FECOLORMATRIX_TYPE_MATRIX;
}

SVGEnumerationColorMatrixTypeValue::operator SVGColorMatrixType() const
{
	return m_value;
}

SVGEnumerationColorMatrixTypeValue& SVGEnumerationColorMatrixTypeValue::operator = (SVGColorMatrixType value)
{
	m_value = value;
	return *this;
}

SVGEnumerationColorMatrixTypeValue& SVGEnumerationColorMatrixTypeValue::operator += (SVGColorMatrixType value)
{
	m_value = value;
	return *this;
}

String GetAsString(SVGEnumerationColorMatrixTypeValue* p)
{
	return &ColorMatrixTypeStrings[p->m_value-1];
}

void SetAsString(SVGEnumerationColorMatrixTypeValue* p, StringIn str)
{
	for (int i = 0; i < _countof(ColorMatrixTypeStrings); ++i)
	{
		if (str == String(&ColorMatrixTypeStrings[i]))
		{
			p->m_value = (SVGColorMatrixType)(i+1);
			return;
		}
	}

// Unknown string value
	p->m_value = SVG_FECOLORMATRIX_TYPE_MATRIX;	// Set to default ?
}

int GetAsInt(SVGEnumerationColorMatrixTypeValue* p)
{
	return p->m_value;
}

void SVGEnumerationColorMatrixTypeValue::InterpolateValue(const SVGEnumerationColorMatrixTypeValue& a, const SVGEnumerationColorMatrixTypeValue& b, double t)
{
	m_value = a.m_value;
}

}	// LSVG
}
