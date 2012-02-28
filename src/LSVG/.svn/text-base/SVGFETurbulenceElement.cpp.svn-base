#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFETurbulenceElement.h"
#include "PSVGFETurbulenceElement.h"

namespace System
{
namespace Web
{

SVGFETurbulenceElement::SVGFETurbulenceElement() : SVGElement(new PSVGFETurbulenceElement(this))
{
	AddXMLAttribute(NewXMLAttr(&m_baseFrequency, NULL, WSTR("baseFrequency")));
	AddXMLAttribute(NewXMLAttr(&m_numOctaves, NULL, WSTR("numOctaves")));
//		AddXMLAttribute(NewXMLAttr(&m_in1, L"", L"in1"));

	SetAllValues(this);	// ???
}

ISVGAnimatedNumber* SVGFETurbulenceElement::get_baseFrequencyX()
{
	ASSERT(0);
	return NULL;
}

ISVGAnimatedNumber* SVGFETurbulenceElement::get_baseFrequencyY()
{
	ASSERT(0);
	return NULL;
}

ISVGAnimatedInteger* SVGFETurbulenceElement::get_numOctaves()
{
	return m_numOctaves->m_animated;
}

ISVGAnimatedNumber* SVGFETurbulenceElement::get_seed()
{
	return NULL;
}

ISVGAnimatedEnumeration* SVGFETurbulenceElement::get_stitchTiles()
{
	return NULL;
}

ISVGAnimatedEnumeration* SVGFETurbulenceElement::get_type()
{
	return NULL;
}

}	// w3c
}
