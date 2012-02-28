#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEDiffuseLightingElement.h"

namespace System
{
namespace Web
{

SVGFEDiffuseLightingElement::SVGFEDiffuseLightingElement(NamedNodeMap* attributes) : SVGElement(new PSVGFEDiffuseLightingElement(this), attributes)
{
	m_surfaceScale = nullptr;
	m_diffuseConstant = nullptr;
	m_in1 = NULL;

	ASSERT(0);
//	AddXMLAttribute(NewXMLAttr(&m_surfaceScale, NULL, WSTR("surfaceScale"), WSTR("1")));
//	AddXMLAttribute(NewXMLAttr(&m_diffuseConstant, NULL, WSTR("diffuseConstant"), WSTR("1")));
//		AddXMLAttribute(NewXMLAttr(&m_DiffuseExponent, L"", L"DiffuseExponent"));
//	AddXMLAttribute(NewXMLAttr(&m_in1, NULL, WSTR("in")));

	SetAllValues(this);	// ???
}

SVGAnimatedString* SVGFEDiffuseLightingElement::get_in1()
{
	return m_in1->m_animated;
}

ISVGAnimatedNumber* SVGFEDiffuseLightingElement::get_surfaceScale()
{
	return m_surfaceScale->m_animated;
}

ISVGAnimatedNumber* SVGFEDiffuseLightingElement::get_diffuseConstant()
{
	return m_diffuseConstant->m_animated;
}

ISVGAnimatedNumber* SVGFEDiffuseLightingElement::get_kernelUnitLengthX()
{
	THROW(-1);
	return nullptr;
}

ISVGAnimatedNumber* SVGFEDiffuseLightingElement::get_kernelUnitLengthY()
{
	THROW(-1);
	return nullptr;
}

}	// LSVG
}
