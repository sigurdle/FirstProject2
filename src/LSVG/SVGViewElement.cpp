#include "stdafx.h"
#include "LSVG2.h"
#include "SVGViewElement.h"

namespace System
{
namespace Web
{

SVGViewElement::SVGViewElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
{
	SetAllValues(this);	// ???
}

ISVGStringList* SVGViewElement::get_viewTarget()
{
	ASSERT(0);
	return NULL;
}

}	// w3c
}
