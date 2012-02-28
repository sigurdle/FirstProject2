#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAnimatedBoolean.h"

namespace System
{
namespace Web
{

SVGAnimatedBoolean::SVGAnimatedBoolean()
{
}


	/*
int SVGAnimatedBoolean::FinalConstruct()
{
	CComObject<CValueTypeWrapper<CBooleanValue> >::CreateInstance(&m_baseVal);
	m_baseVal->AddRef();

	CComObject<CValueTypeWrapper<CBooleanValue> >::CreateInstance(&m_animVal);
	m_animVal->AddRef();

	return 0;
}
*/

bool SVGAnimatedBoolean::get_baseVal()
{
	return m_baseVal->m_value->m_value;
}

bool SVGAnimatedBoolean::get_animVal()
{
	return m_animVal->m_value->m_value;
}

void SVGAnimatedBoolean::set_baseVal(bool newVal)
{

// TODO, fire event of some kind
	m_baseVal->m_value->m_value = newVal;

	m_pAttr->OnBaseValChanged();
}

}	// w3c
}
