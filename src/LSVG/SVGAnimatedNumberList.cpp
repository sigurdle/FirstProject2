#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAnimatedNumberList.h"

namespace System
{
namespace Web
{

// TODO, not here
SVGAnimatedRect::SVGAnimatedRect()
{
	//m_pAttr = NULL;

	m_baseVal = new SVGRect;
	m_animVal = m_baseVal;
}

void SVGAnimatedRect::SetBaseValAsString(StringIn str)
{
	// TODO, improve

	CStringw cstr(str);

	if (cstr.c_str())
	{
		double x, y, width, height;
		swscanf_s(cstr.c_str(), L"%lf %lf %lf %lf", &x, &y, &width, &height);

		m_baseVal->m_x = x;
		m_baseVal->m_y = y;
		m_baseVal->m_width = width;
		m_baseVal->m_height = height;
	}
	else
		m_baseVal = NULL;
}

//

SVGAnimatedNumberList::SVGAnimatedNumberList()
{
//	m_pAttr = NULL;
	m_baseVal = new SVGNumberListPtr(new SVGNumberList());
	m_animVal = m_baseVal;
}

#if 0
int SVGAnimatedNumberList::FinalConstruct()
{
	/*
	CComObject<CValueTypeWrapper<CComObjectCreateInstance<SVGNumberList> > >::CreateInstance(&m_baseVal);
	m_baseVal->AddRef();

	CComObject<CValueTypeWrapper<CComObjectCreateInstance<SVGNumberList> > >::CreateInstance(&m_animVal);
	m_animVal->AddRef();

//	m_baseVal->m_value->m_pListener = this;
*/
	return 0;
}

void SVGAnimatedNumberList::FinalRelease()
{
//	m_baseVal->Release();
	m_baseVal = NULL;

//	m_animVal->Release();
	m_animVal = NULL;
}
#endif

ISVGNumberList* SVGAnimatedNumberList::get_baseVal()
{
	return m_baseVal->m_p;
}

ISVGNumberList* SVGAnimatedNumberList::get_animVal()
{
	return m_animVal->m_p;
}

void SVGAnimatedNumberList::SetBaseValAsString(StringIn val)
{
	m_baseVal->m_p->setStringValue(val);
}

}	// Web
}
