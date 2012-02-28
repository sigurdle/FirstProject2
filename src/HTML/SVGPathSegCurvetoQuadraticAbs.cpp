#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegCurvetoQuadraticAbs.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

void SVGPathSegCurvetoQuadraticAbs::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegCurvetoQuadraticAbs::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegCurvetoQuadraticAbs::set_x1(double newVal)
{
	m_x1 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegCurvetoQuadraticAbs::set_y1(double newVal)
{
	m_y1 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
