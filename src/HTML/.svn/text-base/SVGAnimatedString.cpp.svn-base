#include "stdafx.h"
#include "HTML2.h"
#include "SVGAnimatedString.h"

namespace System
{
namespace Web
{

SVGStringValueHandler SVGStringValueHandler::s_SVGStringValueHandler;

Object* SVGStringValueHandler::Create() const
{
	ASSERT(0);
	return NULL;
}

void SVGStringValueHandler::ParseString(Object* value, StringIn str) const
{
	ASSERT(0);
}

void SVGStringValueHandler::InterpolateValue(Object* dest, Object* a, Object* b, double t)
{
	ASSERT(0);
}

HTMLEXT String GetStringValue(StringIn str)
{
	return str;
}

SVGAnimatedString::SVGAnimatedString()
{
}

String SVGAnimatedString::get_baseVal()
{
	return m_baseVal;
}

String SVGAnimatedString::get_animVal()
{
	return m_animVal;
}

void SVGAnimatedString::set_baseVal(StringIn newVal)
{
	m_baseVal = newVal;
//	m_pAttr->OnBaseValChanged();
	if (m_owner)
	{
		m_owner->BaseValChanged();
	}
}

void SVGAnimatedString::SetBaseValAsString(StringIn str)
{
	m_baseVal = str;

	m_animVal = str;	// TODO remove, set by animation engine

	// TODO ?
}

}	// Web
}
