#include "stdafx.h"
#include "LSVG2.h"
#include "SVGRadialGradientElement.h"
#include "PSVGRadialGradientElement.h"

namespace System
{
namespace Web
{

SVGRadialGradientElement::SVGRadialGradientElement(NamedNodeMap* attributes) : SVGGradientElementImpl<SVGRadialGradientElement>(new PSVGGradientElement(this), attributes)
{
	m_cx = NULL;
	m_cy = NULL;
	m_r = NULL;
	m_fx = NULL;
	m_fy = NULL;

	AddXMLAttribute(NewXMLAttr(&m_cx, NULL, WSTR("cx")));
	AddXMLAttribute(NewXMLAttr(&m_cy, NULL, WSTR("cy")));
	AddXMLAttribute(NewXMLAttr(&m_r, NULL, WSTR("r")));
	AddXMLAttribute(NewXMLAttr(&m_fx, NULL, WSTR("fx")));
	AddXMLAttribute(NewXMLAttr(&m_fy, NULL, WSTR("fy")));

	SetAllValues(this);	// ???
}

ISVGAnimatedLength* SVGRadialGradientElement::get_cx()
{
	return m_cx->m_animated;
}

ISVGAnimatedLength* SVGRadialGradientElement::get_cy()
{
	return m_cy->m_animated;
}

ISVGAnimatedLength* SVGRadialGradientElement::get_r()
{
	return m_r->m_animated;
}

ISVGAnimatedLength* SVGRadialGradientElement::get_fx()
{
	return m_fx->m_animated;
}

ISVGAnimatedLength* SVGRadialGradientElement::get_fy()
{
	return m_fy->m_animated;
}

}	// LSVG
}
