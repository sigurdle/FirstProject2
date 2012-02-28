#include "stdafx.h"
#include "LSVG2.h"
#include "SVGImplementation.h"

#include "SVGTextElement.h"
#include "SVGTSpanElement.h"
#include "SVGTRefElement.h"
#include "SVGTextPathElement.h"
#include "SVGAltGlyphElement.h"
#include "SVGAltGlyphDefElement.h"
#include "SVGGlyphRefElement.h"

#include "SVGFlowTextElement.h"
#include "SVGFlowDivElement.h"

#include "SVGFontElement.h"
#include "SVGFontFaceElement.h"
#include "SVGGlyphElement.h"
#include "SVGMissingGlyphElement.h"
#include "SVGHKernElement.h"
#include "SVGVKernElement.h"

namespace System
{
namespace Web
{

Element* SVGImplementation::createSVGElementTextFonts(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes)
{
	Element* newElement = NULL;

	// Text
	if (localName == L"text")
	{
		SVGTextElement* pElement = new SVGTextElement(attributes);
		newElement = pElement;
	}
#if 0
	else if (!wcscmp(localName, L"tspan"))
	{
		CComObject<CLSVGTSpanElement>* pElement;
		CComObject<CLSVGTSpanElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"tref"))
	{
		CComObject<CLSVGTRefElement>* pElement;
		CComObject<CLSVGTRefElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"textPath"))
	{
		CComObject<CLSVGTextPathElement>* pElement;
		CComObject<CLSVGTextPathElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"altGlyph"))
	{
		CComObject<CLSVGAltGlyphElement>* pElement;
		CComObject<CLSVGAltGlyphElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"altGlyphDef"))
	{
		CComObject<CLSVGAltGlyphDefElement>* pElement;
		CComObject<CLSVGAltGlyphDefElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"glyphRef"))
	{
		CComObject<CLSVGGlyphRefElement>* pElement;
		CComObject<CLSVGGlyphRefElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
// Text flow
	else if (!wcscmp(localName, L"flowText"))
	{
		CComObject<CLSVGFlowTextElement>* pElement;
		CComObject<CLSVGFlowTextElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"flowDiv"))
	{
		CComObject<CLSVGFlowDivElement>* pElement;
		CComObject<CLSVGFlowDivElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	// Fonts
	else if (!wcscmp(localName, L"font"))
	{
		CComObject<CLSVGFontElement>* pElement;
		CComObject<CLSVGFontElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"font-face"))
	{
		CComObject<CLSVGFontFaceElement>* pElement;
		CComObject<CLSVGFontFaceElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"glyph"))
	{
		CComObject<CLSVGGlyphElement>* pElement;
		CComObject<CLSVGGlyphElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"missing-glyph"))
	{
		CComObject<CLSVGMissingGlyphElement>* pElement;
		CComObject<CLSVGMissingGlyphElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"hkern"))
	{
		CComObject<CLSVGHKernElement>* pElement;
		CComObject<CLSVGHKernElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"vkern"))
	{
		CComObject<CLSVGVKernElement>* pElement;
		CComObject<CLSVGVKernElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}

#endif

	return newElement;
}

}	// Web
}
