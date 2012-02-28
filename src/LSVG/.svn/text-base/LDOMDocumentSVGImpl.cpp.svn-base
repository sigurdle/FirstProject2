#include "stdafx.h"
#include "LSVG2.h"
#include "SVGImplementation.h"

#include "SVGGenericElement.h"
#include "SVGSVGElement.h"
#include "SVGStyleElement.h"
#include "SVGGElement.h"
#include "SVGAElement.h"
#include "SVGViewElement.h"
#include "SVGDefsElement.h"
#include "SVGDescElement.h"
#include "SVGTitleElement.h"
#include "SVGSwitchElement.h"
#include "SVGCursorElement.h"
#include "SVGMetadataElement.h"
#include "SVGScriptElement.h"

#include "SVGMaskElement.h"
#include "SVGClipPathElement.h"
#include "SVGPatternElement.h"
#include "SVGMarkerElement.h"
#include "SVGLinearGradientElement.h"
#include "SVGRadialGradientElement.h"
#include "SVGStopElement.h"

#include "SVGColorProfileElement.h"

//#include "LSVGExtensionDefsElement.h"
//#include "LSVGElementDefElement.h"

namespace System
{
namespace Web
{

Element* SVGImplementation::createSVGElement(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes)
{
	Element* newElement = NULL;

// Structure
	if (localName == L"svg")
	{
		SVGSVGElement* pElement = new SVGSVGElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"g")
	{
		SVGGElement* pElement = new SVGGElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"a")
	{
		SVGAElement* pElement = new SVGAElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"view")
	{
		SVGViewElement* pElement = new SVGViewElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"defs")
	{
		SVGDefsElement* pElement = new SVGDefsElement(attributes);
		newElement = pElement;
	}
#if 0
	else if (!wcscmp(localName.c_str(), L"desc"))
	{
		CComObject<CLSVGDescElement>* pElement;
		CComObject<CLSVGDescElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
#endif
	else if (localName == L"title")
	{
		SVGTitleElement* pElement = new SVGTitleElement(attributes);
		newElement = pElement;
	}
#if 0
	else if (!wcscmp(localName.c_str(), L"cursor"))
	{
		CComObject<CLSVGCursorElement>* pElement;
		CComObject<CLSVGCursorElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
#endif
	else if (localName == L"switch")
	{
		SVGSwitchElement* pElement = new SVGSwitchElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"metadata")
	{
		SVGMetadataElement* pElement = new SVGMetadataElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"script")
	{
		SVGScriptElement* pElement = new SVGScriptElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"style")
	{
		SVGStyleElement* pElement = new SVGStyleElement(attributes);
		newElement = pElement;
	}
	// Gradients
	else if (localName == L"linearGradient")
	{
		SVGLinearGradientElement* pElement = new SVGLinearGradientElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"radialGradient")
	{
		SVGRadialGradientElement* pElement = new SVGRadialGradientElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"stop")
	{
		SVGStopElement* pElement = new SVGStopElement(attributes);
		newElement = pElement;
	}
#if 0
	//////////////////////////////////////
	else if (!wcscmp(localName.c_str(), L"marker"))
	{
		CComObject<CLSVGMarkerElement>* pElement;
		CComObject<CLSVGMarkerElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
#endif
	else if (localName == L"pattern")
	{
		SVGPatternElement* pElement = new SVGPatternElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"mask")
	{
		SVGMaskElement* pElement = new SVGMaskElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"clipPath")
	{
		SVGClipPathElement* pElement = new SVGClipPathElement(attributes);
		newElement = pElement;
	}
#if 0
	else if (!wcscmp(localName.c_str(), L"color-profile"))
	{
		CComObject<CLSVGColorProfileElement>* pElement;
		CComObject<CLSVGColorProfileElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName.c_str(), L"extensionDefs"))
	{
		CComObject<CLSVGExtensionDefsElement>* pElement;
		CComObject<CLSVGExtensionDefsElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName.c_str(), L"elementDef"))
	{
		CComObject<CLSVGElementDefElement>* pElement;
		CComObject<CLSVGElementDefElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
#endif

	if (newElement == NULL)
	{
		newElement = createSVGElementFilters(localName, qualifiedName, attributes);
	}

	if (newElement == NULL)
	{
		newElement = createSVGElementTextFonts(localName, qualifiedName, attributes);
	}

	if (newElement == NULL)
	{
		newElement = createSVGElementAnimation(localName, qualifiedName, attributes);
	}

	if (newElement == NULL)
	{
		newElement = createSVGElementShapes(localName, qualifiedName, attributes);
	}

	if (newElement == NULL)	// unknown/generic SVG Element
	{
		SVGGenericElement* pElement = new SVGGenericElement(qualifiedName, attributes);
		newElement = pElement;
	}

	return newElement;
}

}	// LSVG
}
