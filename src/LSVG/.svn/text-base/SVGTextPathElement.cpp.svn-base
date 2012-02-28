#include "stdafx.h"
#include "LSVG2.h"
#include "SVGTextPathElement.h"
#include "PSVGTextPathElement.h"

namespace System
{
namespace Web
{

SVGTextPathElement::SVGTextPathElement(NamedNodeMap* attributes) : SVGTextContentElementImpl/*<SVGTextPathElement>*/(new PSVGTextPathElement(this), attributes)
{
	m_startOffset = NULL;

	AddXMLAttribute(NewXMLAttr(&m_startOffset, NULL, WSTR("startOffset")));

	SetAllValues(this);	// ???
}

SVGAnimatedLength* SVGTextPathElement::get_startOffset()
{
	return m_startOffset->m_animated;
}

ISVGAnimatedEnumeration* SVGTextPathElement::get_method()
{
	ASSERT(0);
	return NULL;
}

ISVGAnimatedEnumeration* SVGTextPathElement::get_spacing()
{
	ASSERT(0);
	return NULL;
}

}	// w3c
}
