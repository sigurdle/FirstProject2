#include "stdafx.h"
#include "LSVG2.h"
#include "SVGRectElement.h"
#include "PSVGRectElement.h"

namespace System
{
namespace Web
{

SVGRectElement::SVGRectElement(NamedNodeMap* attributes) :
	SVGShapeElement(new PSVGRectElement(this), attributes),

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>(this, NULL, WSTR("x")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>(this, NULL, WSTR("y")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(this, NULL, WSTR("width")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>(this, NULL, WSTR("height")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 4>(this, NULL, WSTR("rx")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 5>(this, NULL, WSTR("ry"))
{
}

SVGRectElement::~SVGRectElement()
{
}

ISVGAnimatedLength* SVGRectElement::get_x()
{
	return x_attr();
}

ISVGAnimatedLength* SVGRectElement::get_y()
{
	return y_attr();
}

ISVGAnimatedLength* SVGRectElement::get_width()
{
	return width_attr();
}

ISVGAnimatedLength* SVGRectElement::get_height()
{
	return height_attr();
}

ISVGAnimatedLength* SVGRectElement::get_rx()
{
	return rx_attr();
}

ISVGAnimatedLength* SVGRectElement::get_ry()
{
	return ry_attr();
}

Attr* SVGRectElement::get_xAttr()
{
	return x_attr();
}

Attr* SVGRectElement::get_yAttr()
{
	return y_attr();
}

Attr* SVGRectElement::get_widthAttr()
{
	return width_attr();
}

Attr* SVGRectElement::get_heightAttr()
{
	return height_attr();
}

Attr* SVGRectElement::get_rxAttr()
{
	return rx_attr();
}

Attr* SVGRectElement::get_ryAttr()
{
	return ry_attr();
}

}	// Web
}
