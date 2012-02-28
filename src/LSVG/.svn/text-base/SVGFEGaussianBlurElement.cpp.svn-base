#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEGaussianBlurElement.h"
#include "PSVGFEGaussianBlurElement.h"

namespace System
{
namespace Web
{

	/*
void stdDeviationX_BaseValChanged(Object* obj)
{
	SVGFEGaussianBlurElement* e = static_cast<SVGFEGaussianBlurElement*>(obj);

	e->m_stdDeviationAttr->m_valueIsValid = false;
}

void stdDeviationY_BaseValChanged(Object* obj)
{
	SVGFEGaussianBlurElement* e = static_cast<SVGFEGaussianBlurElement*>(obj);

	e->m_stdDeviationAttr->m_valueIsValid = false;
}
*/

SVGFEGaussianBlurElement::SVGFEGaussianBlurElement(NamedNodeMap* attributes) :
	SVGElement(new PSVGFEGaussianBlurElement(this), attributes),
	AnimatedAttributeT<SVGAnimatedString, 0>(this, NULL, WSTR("in1")),
	AnimatedAttribute2T<SVGAnimatedNumber, 1>(this, NULL, WSTR("stdDeviation"), WSTR("0"))
{
//	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_stdDeviationAttr), NULL, WSTR("stdDeviation"));
//	m_stdDeviationX = new SVGAnimatedNumber;
//	m_stdDeviationY = new SVGAnimatedNumber;
//	m_in1 = new SVGAnimatedString;

//	m_stdDeviationX = NULL;
//	m_stdDeviationY = NULL;

//	AddXMLAttribute(NewXMLAttr(&m_stdDeviation, NULL, WSTR("stdDeviation"), WSTR("0")));
//	AddXMLAttribute(NewXMLAttr(&m_in1, NULL, WSTR("in")));

//	SetAllValues(this);	// ???
/*
	m_stdDeviationX->m_arg0 = this;
	m_stdDeviationX->m_baseValChanged = stdDeviationX_BaseValChanged;

	m_stdDeviationY->m_arg0 = this;
	m_stdDeviationY->m_baseValChanged = stdDeviationY_BaseValChanged;
	*/
}

void SVGFEGaussianBlurElement::setStdDeviation(double stdDeviationX, double stdDeviationY)
{
	stdDeviation_attr().m_animated[0]->m_baseVal = stdDeviationX;
	stdDeviation_attr().m_animated[1]->m_baseVal = stdDeviationY;

	// TODO
	THROW(-1);
}

ISVGAnimatedNumber* SVGFEGaussianBlurElement::get_stdDeviationX()
{
	return stdDeviation_attr().m_animated[0];

#if 0
	if (m_stdDeviationX == NULL)
	{
		CComObject<CLSVGAnimatedNumber>::CreateInstance(&m_stdDeviationX);

		m_stdDeviationX->m_baseVal = &m_pstdDeviation->m_baseVal.m_value[0];
		m_stdDeviationX->m_animVal = &m_pstdDeviation->m_baseVal.m_value[0];
	}

	if (m_stdDeviationX)
	{
		*pVal = m_stdDeviationX;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;
#endif
	return NULL;
}

ISVGAnimatedNumber* SVGFEGaussianBlurElement::get_stdDeviationY()
{
	return stdDeviation_attr().m_animated[1];

#if 0
	if (m_stdDeviationY == NULL)
	{
		CComObject<CLSVGAnimatedNumber>::CreateInstance(&m_stdDeviationY);

		m_stdDeviationY->m_baseVal = &m_pstdDeviation->m_baseVal.m_value[1];
		m_stdDeviationY->m_animVal = &m_pstdDeviation->m_baseVal.m_value[1];
	}

	if (m_stdDeviationY)
	{
		*pVal = m_stdDeviationY;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;
#endif
	return NULL;
}

ISVGAnimatedString* SVGFEGaussianBlurElement::get_in1()
{
	return in1_attr();
}

}	// w3c
}
