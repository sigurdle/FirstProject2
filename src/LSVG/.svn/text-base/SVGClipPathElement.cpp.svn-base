#include "stdafx.h"
#include "LSVG2.h"
#include "SVGClipPathElement.h"
#include "PSVGClipPathElement.h"

namespace System
{
namespace Web
{

SVGClipPathElement::SVGClipPathElement(NamedNodeMap* attributes) : SVGTransformableElement(new PSVGClipPathElement(this), attributes)
{
	/*
	m_clipPathUnits = NULL;

	AddXMLAttribute(NewXMLAttr(&m_clipPathUnits, NULL, WSTR("clipPathUnits"), WSTR("userSpaceOnUse")));

	SetAllValues(this);	// ???
	*/
}

SVGClipPathElement::~SVGClipPathElement()
{
}

ISVGAnimatedEnumeration* SVGClipPathElement::get_clipPathUnits()
{
	ASSERT(0);
	return NULL;
	//return m_clipPathUnits->m_animated;
}

}	// w3c
}
