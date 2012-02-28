#include "stdafx.h"
#include "LSVG2.h"

#include "SVGStyleElement.h"

namespace System
{
namespace Web
{

SVGStyleElement::SVGStyleElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes), LinkStyleStyleImpl(this)
{
	SetAllValues(this);
}

String SVGStyleElement::get_xmlspace()
{
	return NULL;
}

void SVGStyleElement::set_xmlspace(StringIn newVal)
{
	ASSERT(0);
}

String SVGStyleElement::get_type()
{
	return getAttribute(WSTR("type"));
}

void SVGStyleElement::set_type(StringIn newVal)
{
	setAttribute(WSTR("type"), newVal);
}

String SVGStyleElement::get_media()
{
	return getAttribute(WSTR("media"));
}

void SVGStyleElement::set_media(StringIn newVal)
{
	setAttribute(WSTR("media"), newVal);
}

String SVGStyleElement::get_title()
{
	return getAttribute(WSTR("title"));
}

void SVGStyleElement::set_title(StringIn newVal)
{
	setAttribute(WSTR("title"), newVal);
}

}	// Web
}
