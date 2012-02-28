#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFETileElement.h"

namespace System
{
namespace Web
{

SVGFETileElement::SVGFETileElement(NamedNodeMap* attributes) : SVGElement(NULL, attributes)//new PSVGFEElement(this)/*TODO*/)
{
	m_in1 = NULL;

	AddXMLAttribute(NewXMLAttr(&m_in1, NULL, WSTR("in")));

	SetAllValues(this);	// ???
}

SVGAnimatedString* SVGFETileElement::get_in1()
{
	return m_in1->m_animated;
}

}	// w3c
}
