#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAnimatedTransformList.h"
#include "SVGTransform.h"

namespace System
{
namespace Web
{

SVGAnimatedTransformList::SVGAnimatedTransformList()
{
	m_baseVal = new SVGTransformListMutable;
	m_animVal = new SVGTransformList(m_baseVal->m_p);
}

SVGTransformList* SVGAnimatedTransformList::get_animVal()
{
	return m_animVal;
}

SVGTransformList* SVGAnimatedTransformList::get_baseVal()
{
	return m_baseVal;
}

void SVGAnimatedTransformList::SetAnimVal(SVGTransformList* val)
{
	m_animVal = val;
}

}	// w3c
}
