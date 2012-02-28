#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFESpotLightElement.h"

namespace System
{
namespace Web
{

SVGFESpotLightElement::SVGFESpotLightElement(NamedNodeMap* attributes) : SVGElement(NULL, attributes)
{
	ASSERT(0);

	m_x = NULL;
	m_y = NULL;
	m_z = NULL;
	m_pointsAtX = NULL;
	m_pointsAtY = NULL;
	m_pointsAtZ = NULL;
	m_specularExponent = NULL;
	m_limitingConeAngle = NULL;

	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y")));
	AddXMLAttribute(NewXMLAttr(&m_z, NULL, WSTR("z")));
	AddXMLAttribute(NewXMLAttr(&m_pointsAtX, NULL, WSTR("pointsAtX")));
	AddXMLAttribute(NewXMLAttr(&m_pointsAtY, NULL, WSTR("pointsAtY")));
	AddXMLAttribute(NewXMLAttr(&m_pointsAtZ, NULL, WSTR("pointsAtZ")));
	AddXMLAttribute(NewXMLAttr(&m_specularExponent, NULL, WSTR("specularExponent")));
	AddXMLAttribute(NewXMLAttr(&m_limitingConeAngle, NULL, WSTR("limitingConeAngle")));

	SetAllValues(this);	// ???
}

ISVGAnimatedNumber* SVGFESpotLightElement::get_x()
{
	return m_x->m_animated;
}

ISVGAnimatedNumber* SVGFESpotLightElement::get_y()
{
	return m_y->m_animated;
}

ISVGAnimatedNumber* SVGFESpotLightElement::get_z()
{
	return m_z->m_animated;
}

ISVGAnimatedNumber* SVGFESpotLightElement::get_pointsAtX()
{
	return m_pointsAtX->m_animated;
}

ISVGAnimatedNumber* SVGFESpotLightElement::get_pointsAtY()
{
	return m_pointsAtY->m_animated;
}

ISVGAnimatedNumber* SVGFESpotLightElement::get_pointsAtZ()
{
	return m_pointsAtZ->m_animated;
}

ISVGAnimatedNumber* SVGFESpotLightElement::get_specularExponent()
{
	return m_specularExponent->m_animated;
}

ISVGAnimatedNumber* SVGFESpotLightElement::get_limitingConeAngle()
{
	return m_limitingConeAngle->m_animated;
}

}	// w3c
}
