#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFECompositeElement.h"

namespace System
{

extern uint8 linear_to_sRGB[256];
extern uint sRGB_to_linear[256];

namespace Web
{

SVGFECompositeElement::SVGFECompositeElement(NamedNodeMap* attributes) : SVGElement(new PSVGFECompositeElement(this), attributes)
{
	/*
	m_in1 = NULL;
	m_in2 = NULL;
	m_operator = NULL;
	m_k1 = NULL;
	m_k2 = NULL;
	m_k3 = NULL;
	m_k4 = NULL;

	AddXMLAttribute(NewXMLAttr(&m_in1, NULL, WSTR("in")));
	AddXMLAttribute(NewXMLAttr(&m_in2, NULL, WSTR("in2")));
	AddXMLAttribute(NewXMLAttr(&m_operator, NULL, WSTR("operator")));
	AddXMLAttribute(NewXMLAttr(&m_k1, NULL, WSTR("k1")));
	AddXMLAttribute(NewXMLAttr(&m_k2, NULL, WSTR("k2")));
	AddXMLAttribute(NewXMLAttr(&m_k3, NULL, WSTR("k3")));
	AddXMLAttribute(NewXMLAttr(&m_k4, NULL, WSTR("k4")));
*/
	SetAllValues(this);	// ???
}

ISVGAnimatedString* SVGFECompositeElement::get_in1()
{
	return NULL;
//	return m_in1->m_animated;
}

ISVGAnimatedString* SVGFECompositeElement::get_in2()
{
	return NULL;
//	return m_in2->m_animated;
}

ISVGAnimatedEnumeration* SVGFECompositeElement::get_operator()
{
	return NULL;
//	return m_operator->m_animated;
}

ISVGAnimatedNumber* SVGFECompositeElement::get_k1()
{
	return NULL;
//	return m_k1->m_animated;
}

ISVGAnimatedNumber* SVGFECompositeElement::get_k2()
{
	return NULL;
//	return m_k2->m_animated;
}

ISVGAnimatedNumber* SVGFECompositeElement::get_k3()
{
	return NULL;
//	return m_k3->m_animated;
}

ISVGAnimatedNumber* SVGFECompositeElement::get_k4()
{
	return NULL;
//	return m_k4->m_animated;
}

}	// w3c
}
