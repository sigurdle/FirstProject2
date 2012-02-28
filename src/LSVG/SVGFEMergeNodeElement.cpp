#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEMergeNodeElement.h"

namespace System
{
namespace Web
{

SVGFEMergeNodeElement::SVGFEMergeNodeElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
{
	m_in1 = NULL;

	AddXMLAttribute(NewXMLAttr(&m_in1, NULL, WSTR("in")));

	SetAllValues(this);	// ???
}

SVGAnimatedString* SVGFEMergeNodeElement::get_in1()
{
	return m_in1->m_animated;
}

}	// w3c
}
