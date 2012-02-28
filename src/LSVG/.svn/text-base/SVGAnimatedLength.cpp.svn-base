#include "stdafx.h"
#include "LSVG.h"
#include "SVGAnimatedLength.h"

namespace System
{
namespace Web
{

#if 0
int CLSVGAnimatedLength::FinalConstruct()
{
	/*
	CComObject<CValueTypeWrapper<CComObjectCreateInstance<SVGLength> > >::CreateInstance(&m_baseVal);
	m_baseVal->AddRef();

	CComObject<CValueTypeWrapper<CComObjectCreateInstance<SVGLength> > >::CreateInstance(&m_animVal);
	m_animVal->AddRef();
	*/

	m_baseVal->m_value->m_pListener = this;

	return 0;
}

void CLSVGAnimatedLength::FinalRelease()
{
	m_baseVal->m_value->m_pListener = NULL;
//	m_baseVal->Release();

//	m_animVal->Release();
}
#endif

#if 0
ISVGLength* SVGAnimatedLength::get_baseVal()
{
	return m_baseVal->m_value;
}

ISVGLength* SVGAnimatedLength::get_animVal()
{
	return m_animVal->m_value;
}
#endif

////////////////

SVGAnimatedLength::SVGAnimatedLength()
{
	m_baseVal = new SVGLengthMutable;
	m_baseVal->m_owner = this;

	m_animVal = new SVGLength(m_baseVal->m_p);
	m_animVal->m_owner = this;
}

ISVGLength* SVGAnimatedLength::get_baseVal()
{
	return m_baseVal;
}

ISVGLength* SVGAnimatedLength::get_animVal()
{
	return m_animVal;
}

void SVGAnimatedLength::OnChanged(SVGLength* pLength)
{
	if (m_owner)
	{
		m_owner->BaseValChanged();
	}
	/*
	if (m_baseValChanged)
	{
	//	m_pAttr->OnBaseValChanged();
		m_baseValChanged(m_arg0);
	}
	*/
}

bool SVGAnimatedLength::OnRemoveItem(SVGLength* pLength)
{
	// We can't allow baseVal or animVal to be removed from us
	return false;
}

}	// w3c
}
