#include "stdafx.h"
#include "LSVG2.h"
#include "SVGEllipseElement.h"
#include "PSVGEllipseElement.h"

namespace System
{
namespace Web
{

SVGShapeElement::SVGShapeElement(PSVGShapeElement* pElement) : SVGTransformableElement(pElement)
{
}

SVGShapeElement::SVGShapeElement(PSVGShapeElement* pElement, NamedNodeMap* attributes) : SVGTransformableElement(pElement, attributes)
{
}

///////////

SVGEllipticalShapeElement::SVGEllipticalShapeElement(PSVGShapeElement* pElement) :
	SVGShapeElement(pElement),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>(this, nullptr, S("cx")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>(this, nullptr, S("cy"))
{
}

SVGEllipticalShapeElement::SVGEllipticalShapeElement(PSVGShapeElement* pElement, NamedNodeMap* attributes) :
	SVGShapeElement(pElement, attributes),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>(this, nullptr, S("cx")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>(this, nullptr, S("cy"))
{
}

	/*
Attr* SVGEllipticalShapeElement::get_cxAttr()
{
	return cx_attr();
}

Attr* SVGEllipticalShapeElement::get_cyAttr()
{
	return cy_attr();
}

ISVGAnimatedLength* SVGEllipticalShapeElement::get_cx()
{
	return cx_attr();
}

ISVGAnimatedLength* SVGEllipticalShapeElement::get_cy()
{
	return cy_attr();
}
*/

////////////

SVGEllipseElement::SVGEllipseElement() :
	SVGEllipticalShapeElement(new PSVGEllipseElement(this)),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(nullptr, "rx", "0"),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>(nullptr, "ry", "0")
{
}

SVGEllipseElement::SVGEllipseElement(NamedNodeMap* attributes) :
	SVGEllipticalShapeElement(new PSVGEllipseElement(this), attributes),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(nullptr, "rx", "0"),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>(nullptr, "ry", "0")
{
}

Gui::EllipseGeometry* SVGEllipseElement::get_animatedGeometry()
{
	ASSERT(0);
	return nullptr;
}

ISVGAnimatedLength* SVGEllipseElement::get_rx()
{
	return rx_attr();
}

ISVGAnimatedLength* SVGEllipseElement::get_ry()
{
	return ry_attr();
}

Attr* SVGEllipseElement::get_ryAttr()
{
	return rx_attr();
}

Attr* SVGEllipseElement::get_rxAttr()
{
	return ry_attr();
}

}	// Web
}	// System
