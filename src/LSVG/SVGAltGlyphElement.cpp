#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAltGlyphElement.h"
#include "PSVGAltGlyphElement.h"

namespace System
{
namespace Web
{

SVGAltGlyphElement::SVGAltGlyphElement(NamedNodeMap* attributes) : SVGTextPositioningElementImpl(new PSVGAltGlyphElement(this), attributes)
{
}

String SVGAltGlyphElement::get_glyphRef()
{
	return NULL;
}

void SVGAltGlyphElement::set_glyphRef(StringIn newVal)
{
	ASSERT(0);
}

String SVGAltGlyphElement::get_format()
{
	return NULL;
}

void SVGAltGlyphElement::set_format(StringIn newVal)
{
	ASSERT(0);
}

}	// Web
}
