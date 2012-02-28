#include "stdafx.h"
#include "LSVG2.h"
#include "SVGForeignObjectElement.h"
#include "PSVGForeignObjectElement.h"

namespace System
{
namespace Web
{

SVGForeignObjectElement::SVGForeignObjectElement(NamedNodeMap* attributes) : SVGTransformableElement(new PSVGForeignObjectElement(this), attributes)
{
	m_x = NULL;
	m_y = NULL;
	m_width = NULL;
	m_height = NULL;

	/*
	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));
	*/

	SetAllValues(this);	// ???
}

SVGAnimatedLength* SVGForeignObjectElement::get_x()
{
	return m_x;
}

SVGAnimatedLength* SVGForeignObjectElement::get_y()
{
	return m_y;
}

SVGAnimatedLength* SVGForeignObjectElement::get_width()
{
	return m_width;
}

SVGAnimatedLength* SVGForeignObjectElement::get_height()
{
	return m_height;
}

}	// w3c
}
