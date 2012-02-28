#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFESpecularLightingElement.h"

namespace System
{
namespace Web
{

SVGFESpecularLightingElement::SVGFESpecularLightingElement(NamedNodeMap* attributes) : SVGElement(new PSVGFESpecularLightingElement(this), attributes)
{
	m_surfaceScale = NULL;
	m_specularConstant = NULL;
	m_specularExponent = NULL;
	m_in1 = NULL;

	AddXMLAttribute(NewXMLAttr(&m_surfaceScale, NULL, WSTR("surfaceScale"), WSTR("1")));
	AddXMLAttribute(NewXMLAttr(&m_specularConstant, NULL, WSTR("specularConstant"), WSTR("1")));
	AddXMLAttribute(NewXMLAttr(&m_specularExponent, NULL, WSTR("specularExponent"), WSTR("1")));
	AddXMLAttribute(NewXMLAttr(&m_in1, NULL, WSTR("in")));

	SetAllValues(this);	// ???
}

SVGAnimatedString* SVGFESpecularLightingElement::get_in1()
{
	return m_in1->m_animated;
}

ISVGAnimatedNumber* SVGFESpecularLightingElement::get_surfaceScale()
{
	return m_surfaceScale->m_animated;
}

ISVGAnimatedNumber* SVGFESpecularLightingElement::get_specularConstant()
{
	return m_specularConstant->m_animated;
}

ISVGAnimatedNumber* SVGFESpecularLightingElement::get_specularExponent()
{
	return m_specularExponent->m_animated;
}

}	// w3c
}
