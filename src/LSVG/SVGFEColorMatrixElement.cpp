#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEColorMatrixElement.h"
#include "PSVGFEColorMatrixElement.h"

namespace System
{
namespace Web
{

SVGFEColorMatrixElement::SVGFEColorMatrixElement(NamedNodeMap* attributes) :
	SVGElement(new PSVGFEColorMatrixElement(this), attributes),
	AnimatedAttributeT<SVGAnimatedString, 0>(this, NULL, WSTR("in")),
	AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationColorMatrixTypeValue>, 1>(this, NULL, WSTR("type")),
	AnimatedAttributeT<SVGAnimatedNumberList, 2>(this, NULL, WSTR("values"))
{
}

ISVGAnimatedString* SVGFEColorMatrixElement::get_in1()
{
	return in1_attr();
}

ISVGAnimatedEnumeration* SVGFEColorMatrixElement::get_type()
{
	return type_attr();
}

ISVGAnimatedNumberList* SVGFEColorMatrixElement::get_values()
{
	return values_attr();
}

}	// Web
}
