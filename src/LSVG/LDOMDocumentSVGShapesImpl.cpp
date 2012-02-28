#include "stdafx.h"
#include "LSVG2.h"

#include "SVGImplementation.h"

#include "SVGPathElement.h"
#include "SVGEllipseElement.h"
#include "SVGCircleElement.h"
#include "SVGRectElement.h"
#include "SVGLineElement.h"
#include "SVGPolylineElement.h"
#include "SVGPolygonElement.h"

#include "SVGSymbolElement.h"
#include "SVGUseElement.h"
#include "SVGImageElement.h"
#include "SVGForeignObjectElement.h"

namespace System
{
namespace Web
{

Element* SVGImplementation::createSVGElementShapes(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes)
{
	Element* newElement = NULL;

#if 0
	if (!wcscmp(localName, L"path"))
	{
		CComObject<CLSVGPathElement>* pElement;
		CComObject<CLSVGPathElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else
#endif
		if (localName == L"ellipse")
	{
		SVGEllipseElement* pElement = new SVGEllipseElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"circle")
	{
		SVGCircleElement* pElement = new SVGCircleElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"rect")
	{
		SVGRectElement* pElement = new SVGRectElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"line")
	{
		SVGLineElement* pElement = new SVGLineElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"polyline")
	{
		SVGPolylineElement* pElement = new SVGPolylineElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"polygon")
	{
		SVGPolygonElement* pElement = new SVGPolygonElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"symbol")
	{
		SVGSymbolElement* pElement = new SVGSymbolElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"use")
	{
		SVGUseElement* pElement = new SVGUseElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"image")
	{
		SVGImageElement* pElement = new SVGImageElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"foreignObject")
	{
		SVGForeignObjectElement* pElement = new SVGForeignObjectElement(attributes);
		newElement = pElement;
	}
	return newElement;
}

}	// Web
}
