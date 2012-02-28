#include "stdafx.h"
#include "LSVG2.h"
#include "SVGTextElement.h"
#include "PSVGTextElement.h"

namespace System
{
namespace Web
{

SVGTextElement::SVGTextElement(NamedNodeMap* attributes) : SVGTextPositioningElementImpl(new PSVGTextElement(this), attributes)
{
	SetAllValues(this);	// ???
}

}	// Web
}	// System
