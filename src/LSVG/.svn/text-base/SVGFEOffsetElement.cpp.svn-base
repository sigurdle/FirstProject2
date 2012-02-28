#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEOffsetElement.h"
#include "PSVGFEOffsetElement.h"

namespace System
{
namespace Web
{

SVGFEOffsetElement::SVGFEOffsetElement(NamedNodeMap* attributes) :
	SVGElement(new PSVGFEOffsetElement(this), attributes),

	AnimatedAttributeT<SVGAnimatedNumber, 0>(this, NULL, WSTR("dx"), WSTR("0")),
	AnimatedAttributeT<SVGAnimatedNumber, 1>(this, NULL, WSTR("dy"), WSTR("0")),
	AnimatedAttributeT<SVGAnimatedString, 2>(this, NULL, WSTR("in1"))
{
}

ISVGAnimatedNumber* SVGFEOffsetElement::get_dx()
{
	return dx_attr();
}

ISVGAnimatedNumber* SVGFEOffsetElement::get_dy()
{
	return dy_attr();
}

ISVGAnimatedString* SVGFEOffsetElement::get_in1()
{
	return in1_attr();
}

}	// Web
}
