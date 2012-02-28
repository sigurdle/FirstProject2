#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAnimatedLengthList.h"

namespace System
{
namespace Web
{

SVGAnimatedLengthList::SVGAnimatedLengthList()
{
	m_baseVal = new SVGLengthList();
	m_animVal = new SVGLengthList(m_baseVal->m_p);
}

SVGAnimatedLengthList::~SVGAnimatedLengthList()
{
	m_baseVal->m_pListener = NULL;
	m_baseVal = NULL;

	m_animVal->m_pListener = NULL;
	m_animVal = NULL;
}

SVGLengthList* SVGAnimatedLengthList::get_baseVal()
{
	return m_baseVal;
}

SVGLengthList* SVGAnimatedLengthList::get_animVal()
{
	return m_animVal;
}

}	// Web
}	// System
