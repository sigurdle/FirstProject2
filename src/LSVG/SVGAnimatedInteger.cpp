#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAnimatedInteger.h"

namespace System
{
namespace Web
{

SVGAnimatedInteger::SVGAnimatedInteger()
{
}

	/*
int SVGAnimatedInteger::FinalConstruct()
{
	CComObject<CValueTypeWrapper<CLongValue> >::CreateInstance(&m_baseVal);
	m_baseVal->AddRef();

	CComObject<CValueTypeWrapper<CLongValue> >::CreateInstance(&m_animVal);
	m_animVal->AddRef();

	return 0;
}

void SVGAnimatedInteger::FinalRelease()
{
	m_baseVal->Release();
	m_baseVal = NULL;

	m_animVal->Release();
	m_animVal = NULL;
}
*/

int SVGAnimatedInteger::get_baseVal() const
{
	return m_baseVal->m_value->m_value;
}

int SVGAnimatedInteger::get_animVal() const
{
	return m_animVal->m_value->m_value;
}

void SVGAnimatedInteger::set_baseVal(int newVal)
{
	m_baseVal->m_value->m_value = newVal;

	m_pAttr->OnBaseValChanged();
}

}	// w3c
}
