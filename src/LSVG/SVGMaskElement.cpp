#include "stdafx.h"
#include "LSVG2.h"
#include "SVGMaskElement.h"
#include "PSVGMaskElement.h"

namespace System
{
namespace Web
{

SVGMaskElement::SVGMaskElement(NamedNodeMap* attributes) : SVGElement(new PSVGMaskElement(this), attributes)
{
	m_maskUnits = NULL;
	m_maskContentUnits = NULL;
	m_x = NULL;
	m_y = NULL;
	m_width = NULL;
	m_height = NULL;

	AddXMLAttribute(NewXMLAttr(&m_maskUnits, NULL, WSTR("maskUnits")));
	AddXMLAttribute(NewXMLAttr(&m_maskContentUnits, NULL, WSTR("maskContentUnits")));
	/*
	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));
	*/

	SetAllValues(this);	// ???
}

ISVGAnimatedEnumeration* SVGMaskElement::get_maskUnits()
{
	return m_maskUnits->m_animated;
}

ISVGAnimatedEnumeration* SVGMaskElement::get_maskContentUnits()
{
	return m_maskContentUnits->m_animated;
}

ISVGAnimatedLength* SVGMaskElement::get_x()
{
	return m_x;
}

ISVGAnimatedLength* SVGMaskElement::get_y()
{
	return m_y;
}

ISVGAnimatedLength* SVGMaskElement::get_width()
{
	return m_width;
}

ISVGAnimatedLength* SVGMaskElement::get_height()
{
	return m_height;
}

}	// w3c
}
