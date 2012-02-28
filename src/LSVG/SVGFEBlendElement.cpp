#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEBlendElement.h"
#include "PSVGFEBlendElement.h"

namespace System
{
namespace Web
{

SVGFEBlendElement::SVGFEBlendElement(NamedNodeMap* attributes) : SVGElement(new PSVGFEBlendElement(this), attributes)
{
	m_in1 = nullptr;
	m_in2 = nullptr;
	m_mode = nullptr;

//	AddXMLAttribute(NewXMLAttr(&m_in1, NULL, WSTR("in")));
//	AddXMLAttribute(NewXMLAttr(&m_in2, NULL, WSTR("in2")));
//	AddXMLAttribute(NewXMLAttr(&m_mode, NULL, WSTR("mode")));

	SetAllValues(this);	// ???
}

SVGAnimatedString* SVGFEBlendElement::get_in1()
{
	return m_in1->m_animated;
}

SVGAnimatedString* SVGFEBlendElement::get_in2()
{
	return m_in2->m_animated;
}

ISVGAnimatedEnumeration* SVGFEBlendElement::get_mode()
{
	return m_mode->m_animated;
}

}	// Web
}	// System
