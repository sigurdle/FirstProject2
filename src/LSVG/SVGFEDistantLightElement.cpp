#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEDistantLightElement.h"

namespace System
{
namespace Web
{

SVGFEDistantLightElement::SVGFEDistantLightElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
{
//	m_pNode = new PSVGElement;//FEDistantLightElement;
//	m_pNode->m_pNode = this;

	m_azimuth = NULL;
	m_elevation = NULL;

	ASSERT(0);
//	AddXMLAttribute(NewXMLAttr(&m_azimuth, NULL, WSTR("azimuth")));
//	AddXMLAttribute(NewXMLAttr(&m_elevation, NULL, WSTR("elevation")));

	SetAllValues(this);	// ???
}

ISVGAnimatedNumber* SVGFEDistantLightElement::get_azimuth()
{
	return m_azimuth->m_animated;
}

ISVGAnimatedNumber* SVGFEDistantLightElement::get_elevation()
{
	return m_elevation->m_animated;
}

}	// w3c
}
