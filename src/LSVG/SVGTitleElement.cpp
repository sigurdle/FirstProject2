#include "stdafx.h"
#include "LSVG2.h"
#include "SVGTitleElement.h"

namespace System
{
namespace Web
{

SVGTitleElement::SVGTitleElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
{
	SetAllValues(this);
}

}
}
