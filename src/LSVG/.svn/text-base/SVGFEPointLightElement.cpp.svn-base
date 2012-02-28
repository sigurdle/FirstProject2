#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEPointLightElement.h"
#include "PSVGFEPointLightElement.h"

namespace System
{
namespace Web
{

SVGFEPointLightElement::SVGFEPointLightElement(NamedNodeMap* attributes) : SVGElement(new PSVGFEPointLightElement(this), attributes)
{
	m_x = NULL;
	m_y = NULL;
	m_z = NULL;

	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y")));
	AddXMLAttribute(NewXMLAttr(&m_z, NULL, WSTR("z")));

	SetAllValues(this);	// ???
}

ISVGAnimatedNumber* SVGFEPointLightElement::get_x()
{
	return m_x->m_animated;
}

ISVGAnimatedNumber* SVGFEPointLightElement::get_y()
{
	return m_y->m_animated;
}

ISVGAnimatedNumber* SVGFEPointLightElement::get_z()
{
	return m_z->m_animated;
}

}	// w3c
}
