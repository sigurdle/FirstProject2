#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegCurvetoQuadraticRel.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

SVGPathSegCurvetoQuadraticRel::SVGPathSegCurvetoQuadraticRel()
{
	m_x = m_y = m_x1 = m_y1 = 0;
}

SVGPathSegCurvetoQuadraticRel::SVGPathSegCurvetoQuadraticRel(double x, double y, double x1, double y1)
{
	m_x = x;
	m_y = y;
	m_x1 = x1;
	m_y1 = y1;
}

String SVGPathSegCurvetoQuadraticRel::get_pathSegTypeAsLetter() const
{
	return WSTR("q");
}

void SVGPathSegCurvetoQuadraticRel::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegCurvetoQuadraticRel::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegCurvetoQuadraticRel::set_x1(double newVal)
{
	m_x1 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegCurvetoQuadraticRel::set_y1(double newVal)
{
	m_y1 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
