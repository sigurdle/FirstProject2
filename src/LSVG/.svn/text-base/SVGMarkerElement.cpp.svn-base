#include "stdafx.h"
#include "LSVG2.h"
#include "SVGMarkerElement.h"

namespace System
{
namespace Web
{

SVGMarkerElement::SVGMarkerElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)//, SVGFitToViewBoxImpl(this)
{
	m_refX = NULL;
	m_refY = NULL;
	m_markerWidth = NULL;
	m_markerHeight = NULL;
//	m_markerUnits = NULL;
//	m_orientType = NULL;
//	m_orientAngle = NULL;

	/*
	AddXMLAttribute(NewXMLAttr(&m_refX, NULL, WSTR("refX"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_refY, NULL, WSTR("refY"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_markerWidth, NULL, WSTR("markerWidth"), WSTR("3")));
	AddXMLAttribute(NewXMLAttr(&m_markerHeight, NULL, WSTR("markerHeight"), WSTR("3")));
	AddXMLAttribute(NewXMLAttr(&m_markerUnits, NULL, WSTR("markerUnits"), WSTR("strokeWidth")));
	AddXMLAttribute(NewXMLAttr(&m_orientType, NULL, WSTR("orient"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_orientAngle, NULL, WSTR("orient"), WSTR("0")));

	SetAllValues(this);
	*/
}

SVGMarkerElement::~SVGMarkerElement()
{
}

ISVGAnimatedLength* SVGMarkerElement::get_refX()
{
	return m_refX;
}

ISVGAnimatedLength* SVGMarkerElement::get_refY()
{
	return m_refY;
}

ISVGAnimatedLength* SVGMarkerElement::get_markerWidth()
{
	return m_markerWidth;
}

ISVGAnimatedLength* SVGMarkerElement::get_markerHeight()
{
	return m_markerHeight;
}

ISVGAnimatedEnumeration* SVGMarkerElement::get_markerUnits()
{
	return NULL;
	//return m_markerUnits->m_animated;
}

SVGAnimatedAngle* SVGMarkerElement::get_orientAngle()
{
	return NULL;
	//return m_orientAngle->m_animated;
}

ISVGAnimatedEnumeration* SVGMarkerElement::get_orientType()
{
	ASSERT(0);
	return NULL;
}

void SVGMarkerElement::setOrientToAuto()
{
	setAttribute(WSTR("orient"), WSTR("auto"));
}

void SVGMarkerElement::setOrientToAngle(SVGAngle* angle)
{
	ASSERT(angle != NULL);
	if (angle == NULL) throw -1;

	String stringValue = angle->get_valueAsString();

	setAttribute(WSTR("orient"), stringValue);
}

}	// Web
}
