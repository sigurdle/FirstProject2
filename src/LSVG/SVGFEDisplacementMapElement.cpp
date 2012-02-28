#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEDisplacementMapElement.h"
#include "PSVGFEDisplacementMapElement.h"

namespace System
{
namespace Web
{

SVGFEDisplacementMapElement::SVGFEDisplacementMapElement(NamedNodeMap* attributes) : SVGElement(new PSVGFEDisplacementMapElement(this), attributes)
{
	m_scale = NULL;
	m_xChannelSelector = NULL;
	m_yChannelSelector = NULL;

	ASSERT(0);
	/*
	AddXMLAttribute(NewXMLAttr(&m_scale, NULL, WSTR("scale")));
	AddXMLAttribute(NewXMLAttr(&m_xChannelSelector, NULL, WSTR("xChannelSelector")));
	AddXMLAttribute(NewXMLAttr(&m_yChannelSelector, NULL, WSTR("yChannelSelector")));
	*/

	SetAllValues(this);	// ???
}

ISVGAnimatedNumber* SVGFEDisplacementMapElement::get_scale()
{
	return m_scale->m_animated;
}

ISVGAnimatedEnumeration* SVGFEDisplacementMapElement::get_xChannelSelector()
{
	return m_xChannelSelector->m_animated;
}

ISVGAnimatedEnumeration* SVGFEDisplacementMapElement::get_yChannelSelector()
{
	return m_yChannelSelector->m_animated;
}

}	// LSVG
}
