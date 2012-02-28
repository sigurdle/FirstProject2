#include "stdafx.h"
#include "LXML2.h"
#include "SVGShadowElement.h"

namespace System
{
namespace Web
{

Element* getElementByIdChildren(Element* element, StringIn elementId);

Element* SVGShadowElement::getElementById(StringIn elementId)
{
	return getElementByIdChildren(this, elementId);
}

}	// Web
}
