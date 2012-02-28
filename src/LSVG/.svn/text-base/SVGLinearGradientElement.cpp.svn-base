#include "stdafx.h"
#include "LSVG2.h"
#include "SVGLinearGradientElement.h"

namespace System
{
namespace Web
{

SVGLinearGradientElement::SVGLinearGradientElement(NamedNodeMap* attributes) : SVGGradientElementImpl<SVGLinearGradientElement>(new PSVGLinearGradientElement(this), attributes)
{
	m_x1 = NULL;
	m_y1 = NULL;
	m_x2 = NULL;
	m_y2 = NULL;

	/*
	AddXMLAttribute(NewXMLAttr(&m_x1, NULL, WSTR("x1"), WSTR("0%")));
	AddXMLAttribute(NewXMLAttr(&m_y1, NULL, WSTR("y1"), WSTR("0%")));
	AddXMLAttribute(NewXMLAttr(&m_x2, NULL, WSTR("x2"), WSTR("100%")));
	AddXMLAttribute(NewXMLAttr(&m_y2, NULL, WSTR("y2"), WSTR("0%")));

	SetAllValues(this);	// ???
	*/
}

SVGAnimatedLength* SVGLinearGradientElement::get_x1()
{
	return m_x1;
}

SVGAnimatedLength* SVGLinearGradientElement::get_y1()
{
	return m_y1;
}

SVGAnimatedLength* SVGLinearGradientElement::get_x2()
{
	return m_x2;
}

SVGAnimatedLength* SVGLinearGradientElement::get_y2()
{
	return m_y2;
}

}	// w3c
}
