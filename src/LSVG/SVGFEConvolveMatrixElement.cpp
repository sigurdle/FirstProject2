#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEConvolveMatrixElement.h"
#include "PSVGFEConvolveMatrixElement.h"

namespace System
{
namespace Web
{

SVGFEConvolveMatrixElement::SVGFEConvolveMatrixElement(NamedNodeMap* attributes) : SVGElement(new PSVGFEConvolveMatrixElement(this), attributes)
{
	m_order = NULL;
	m_kernelMatrix = NULL;
	m_targetX = NULL;
	m_targetY = NULL;
	m_divisor = NULL;
	m_bias = NULL;
	m_preserveAlpha = NULL;

	ASSERT(0);
	/*
	AddXMLAttribute(NewXMLAttr(&m_order, NULL, WSTR("order")));
	AddXMLAttribute(NewXMLAttr(&m_kernelMatrix, NULL, WSTR("kernelMatrix")));
	AddXMLAttribute(NewXMLAttr(&m_targetX, NULL, WSTR("targetX")));
	AddXMLAttribute(NewXMLAttr(&m_targetY, NULL, WSTR("targetY")));
	AddXMLAttribute(NewXMLAttr(&m_divisor, NULL, WSTR("divisor")));
	AddXMLAttribute(NewXMLAttr(&m_bias, NULL, WSTR("bias")));
	AddXMLAttribute(NewXMLAttr(&m_preserveAlpha, NULL, WSTR("preserveAlpha")));
*/
	SetAllValues(this);	// ???
}

ISVGAnimatedString* SVGFEConvolveMatrixElement::get_in1()
{
	ASSERT(0);
	return NULL;
}

ISVGAnimatedInteger* SVGFEConvolveMatrixElement::get_orderX()
{
	ASSERT(0);
	return NULL;
}

ISVGAnimatedInteger* SVGFEConvolveMatrixElement::get_orderY()
{
	ASSERT(0);
	return NULL;
}

SVGAnimatedNumberList* SVGFEConvolveMatrixElement::get_kernelMatrix()
{
	return m_kernelMatrix->m_animated;
}

ISVGAnimatedNumber* SVGFEConvolveMatrixElement::get_divisor()
{
	return m_divisor->m_animated;
}

ISVGAnimatedNumber* SVGFEConvolveMatrixElement::get_bias()
{
	return m_bias->m_animated;
}

ISVGAnimatedInteger* SVGFEConvolveMatrixElement::get_targetX()
{
	return m_targetX->m_animated;
}

ISVGAnimatedInteger* SVGFEConvolveMatrixElement::get_targetY()
{
	return m_targetY->m_animated;
}

ISVGAnimatedEnumeration* SVGFEConvolveMatrixElement::get_edgeMode()
{
	ASSERT(0);
	return NULL;
}

ISVGAnimatedNumber* SVGFEConvolveMatrixElement::get_kernelUnitLengthX()
{
	ASSERT(0);
	return NULL;
}

ISVGAnimatedNumber* SVGFEConvolveMatrixElement::get_kernelUnitLengthY()
{
	ASSERT(0);
	return NULL;
}

ISVGAnimatedBoolean* SVGFEConvolveMatrixElement::get_preserveAlpha()
{
	return m_preserveAlpha->m_animated;
}

}	// w3c
}
