#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegCurvetoQuadraticSmoothAbs.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

SVGPathSegCurvetoQuadraticSmoothAbs::SVGPathSegCurvetoQuadraticSmoothAbs()
{
	m_x = 0;
	m_y = 0;
}

void SVGPathSegCurvetoQuadraticSmoothAbs::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegCurvetoQuadraticSmoothAbs::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
