#include "stdafx.h"
#include "LSVG2.h"
#include "SVGLineElement.h"
#include "PSVGLineElement.h"

namespace System
{
namespace Web
{

SVGLineElement::SVGLineElement(NamedNodeMap* attributes) :
	SVGTransformableElement(new PSVGLineElement(this), attributes),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>(this, NULL, WSTR("x1")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>(this, NULL, WSTR("y1")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(this, NULL, WSTR("x2")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>(this, NULL, WSTR("y2"))
{
	/*
	m_x1Attr = NULL;
	m_y1Attr = NULL;
	m_x2Attr = NULL;
	m_y2Attr = NULL;

	m_x1 = NULL;
	m_y1 = NULL;
	m_x2 = NULL;
	m_y2 = NULL;
	*/

	/*
	AddXMLAttribute(NewXMLAttr(&m_x1, NULL, WSTR("x1")));
	AddXMLAttribute(NewXMLAttr(&m_y1, NULL, WSTR("y1")));
	AddXMLAttribute(NewXMLAttr(&m_x2, NULL, WSTR("x2")));
	AddXMLAttribute(NewXMLAttr(&m_y2, NULL, WSTR("y2")));
	SetAllValues(this);	// ???
*/
}

ISVGAnimatedLength* SVGLineElement::get_x1()
{
	return x1_attr();
}

ISVGAnimatedLength* SVGLineElement::get_y1()
{
	return y1_attr();
}

ISVGAnimatedLength* SVGLineElement::get_x2()
{
	return x2_attr();
}

ISVGAnimatedLength* SVGLineElement::get_y2()
{
	return y2_attr();
}

}	// w3c
}
