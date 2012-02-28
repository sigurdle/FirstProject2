#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAnimatedAngle.h"

#include "SVGAngle.h"

namespace System
{
namespace Web
{

SVGAnimatedAngle::SVGAnimatedAngle()
{
	m_pAttr = NULL;
}

	/*
int SVGAnimatedAngle::FinalConstruct()
{
	CComObject<CValueTypeWrapper<CComObjectCreateInstance<SVGAngle> > >::CreateInstance(&m_baseVal);
	m_baseVal->AddRef();

	CComObject<CValueTypeWrapper<CComObjectCreateInstance<SVGAngle> > >::CreateInstance(&m_animVal);
	m_animVal->AddRef();

	m_baseVal->m_value->m_pListener = this;

	return 0;
}
*/
SVGAnimatedAngle::~SVGAnimatedAngle()
{
	m_baseVal->m_value->m_pListener = NULL;
//	m_baseVal->Release();
	m_baseVal = NULL;

//	m_animVal->Release();
	m_animVal = NULL;
}

SVGAngle* SVGAnimatedAngle::get_baseVal()
{
	return m_baseVal->m_value;
}

SVGAngle* SVGAnimatedAngle::get_animVal()
{
	return m_animVal->m_value;
}

}	// w3c
}
