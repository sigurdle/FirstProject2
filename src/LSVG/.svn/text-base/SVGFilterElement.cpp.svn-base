#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFilterElement.h"

namespace System
{
namespace Web
{

SVGFilterElement::SVGFilterElement(NamedNodeMap* attributes) :
	SVGElement(new PSVGFilterElement(this), attributes),

	AnimatedAttributeT<SVGAnimatedLength, 0>(this, NULL, WSTR("x"), WSTR("-10%")),
	AnimatedAttributeT<SVGAnimatedLength, 1>(this, NULL, WSTR("y"), WSTR("-10%")),
	AnimatedAttributeT<SVGAnimatedLength, 2>(this, NULL, WSTR("width"), WSTR("120%")),
	AnimatedAttributeT<SVGAnimatedLength, 3>(this, NULL, WSTR("height"), WSTR("120%")),
	AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue>, 4>(this, NULL, WSTR("filterUnits"), WSTR("objectBoundingBox")),
	AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue>, 5>(this, NULL, WSTR("primitiveUnits"), WSTR("userSpaceOnUse"))
{
}

ISVGAnimatedLength* SVGFilterElement::get_x()
{
	return x_attr();
}

ISVGAnimatedLength* SVGFilterElement::get_y()
{
	return y_attr();
}

ISVGAnimatedLength* SVGFilterElement::get_width()
{
	return width_attr();
}

ISVGAnimatedLength* SVGFilterElement::get_height()
{
	return height_attr();
}

ISVGAnimatedEnumeration* SVGFilterElement::get_filterUnits()
{
	return filterUnits_attr();
}

ISVGAnimatedEnumeration* SVGFilterElement::get_primitiveUnits()
{
	return primitiveUnits_attr();
}

}	// w3c
}
