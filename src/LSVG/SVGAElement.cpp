#include "stdafx.h"
#include "LSVG2.h"

#include "SVGAElement.h"
#include "PSVGAElement.h"

namespace System
{
namespace Web
{

SVGAElement::SVGAElement(NamedNodeMap* attributes) : SVGTransformableElement(new PSVGAElement(this), attributes)
{
	m_target = NULL;

//	AddXMLAttribute(NewXMLAttr(&m_target, NULL, WSTR("target")));
//	SetAllValues(this);	// ???
}

SVGAnimatedString* SVGAElement::get_target()
{
	return m_target;
}

}	// w3c
}
