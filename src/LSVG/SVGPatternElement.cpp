#include "stdafx.h"
#include "LSVG2.h"
#include "SVGPatternElement.h"

namespace System
{
namespace Web
{

SVGPatternElement::SVGPatternElement(NamedNodeMap* attributes) :
	SVGElement(new PSVGPatternElement(this), attributes)
//SVGFitToViewBoxImpl(this)
{
	m_x = NULL;
	m_y = NULL;
	m_width = NULL;
	m_height = NULL;
//	m_patternUnits = NULL;
//	m_patternContentUnits = NULL;
//	m_patternTransform = NULL;

	/*
	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height")));
	AddXMLAttribute(NewXMLAttr(&m_patternUnits, NULL, WSTR("patternUnits")));
	AddXMLAttribute(NewXMLAttr(&m_patternContentUnits, NULL, WSTR("patternContentUnits")));

//	AddXMLAttribute(NewXMLAttr(&m_patternTransform, NULL, WSTR("patternTransform")));
//	m_patternTransform->m_baseVal->m_pListener = this;

	SetAllValues(this);	// ???
	*/
}

SVGPatternElement::~SVGPatternElement()
{
	/*
	if (m_patternTransform)
	{
		m_patternTransform->m_animated->m_baseVal->m_value->m_pListener = NULL;
		m_patternTransform = NULL;
	}
	*/
}

ISVGAnimatedLength* SVGPatternElement::get_x()
{
	return m_x;
}

ISVGAnimatedLength* SVGPatternElement::get_y()
{
	return m_y;
}

ISVGAnimatedLength* SVGPatternElement::get_width()
{
	return m_width;
}

ISVGAnimatedLength* SVGPatternElement::get_height()
{
	return m_height;
}

ISVGAnimatedEnumeration* SVGPatternElement::get_patternUnits()
{
	return NULL;
	//return m_patternUnits->m_animated;
}

ISVGAnimatedEnumeration* SVGPatternElement::get_patternContentUnits()
{
	return NULL;
	//return m_patternContentUnits->m_animated;
}

SVGAnimatedTransformList* SVGPatternElement::get_patternTransform()
{
	return m_patternTransform;
}

}	// w3c
}
