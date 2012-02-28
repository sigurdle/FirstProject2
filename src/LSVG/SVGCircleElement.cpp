#include "stdafx.h"
#include "LSVG2.h"
#include "SVGCircleElement.h"
#include "PSVGCircleElement.h"

namespace System
{
namespace Web
{

SVGCircleElement::SVGCircleElement() :
	SVGEllipticalShapeElement(new PSVGCircleElement(this)),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(this, NULL, WSTR("r"))
{
}

SVGCircleElement::SVGCircleElement(NamedNodeMap* attributes) :
	SVGEllipticalShapeElement(new PSVGCircleElement(this), attributes),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(this, NULL, WSTR("r"))
{
#if 0
	m_rAttr->m_callbacks = &s_rCallbacks;

	m_r = new SVGAnimatedLength;
	m_r->m_baseValChanged = rBaseValChanged;
	m_r->m_arg0 = this;
	SetStringValue(m_r->m_baseVal, m_rAttr->get_value());
#endif
}

ElementType* SVGCircleElement::GetElementType()
{
	static ElementType elementType(typeid(SVGCircleElement));

	static AttrDef fill(L"fill");
	static AttrDef stroke(L"stroke");

	static AttrDef* attrs[] =
	{
		&fill,
		&stroke,
	};

//	elementType.m_unspecified = attr;
//	elementType.m_unspecifiedCount = attr;

	return &elementType;
}

}	// Web
}	// System
