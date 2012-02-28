#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegCurvetoQuadraticSmoothRel.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

SVGPathSegCurvetoQuadraticSmoothRel::SVGPathSegCurvetoQuadraticSmoothRel()
{
	m_x = 0;
	m_y = 0;
}

double SVGPathSegCurvetoQuadraticSmoothRel::get_x() const
{
	return m_x;
}

void SVGPathSegCurvetoQuadraticSmoothRel::put_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoQuadraticSmoothRel::get_y() const
{
	return m_y;
}

void SVGPathSegCurvetoQuadraticSmoothRel::put_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
