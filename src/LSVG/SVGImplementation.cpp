#include "stdafx.h"
#include "LSVG.h"
#include "SVGImplementation.h"

namespace System
{
namespace Web
{

SVGImplementation::SVGImplementation()
{
}

Element* SVGImplementation::CreateElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes)
{
	if (namespaceURI == L"http://www.w3.org/2000/svg")
	{
		return createSVGElement(localName, qualifiedName, attributes);
	}
	else
	{
		return NULL;
	}
}

}	// Web
}
