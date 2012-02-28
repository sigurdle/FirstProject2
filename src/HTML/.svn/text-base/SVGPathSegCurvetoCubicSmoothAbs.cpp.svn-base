#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegCurvetoCubicSmoothAbs.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

SVGPathSegCurvetoCubicSmoothAbs::SVGPathSegCurvetoCubicSmoothAbs()
{
	m_x = 0;
	m_y = 0;
	m_x2 = 0;
	m_y2 = 0;
}

SVGPathSegType SVGPathSegCurvetoCubicSmoothAbs::get_pathSegType() const
{
	return PATHSEG_CURVETO_CUBIC_SMOOTH_ABS;
}

String SVGPathSegCurvetoCubicSmoothAbs::get_pathSegTypeAsLetter() const
{
	return WSTR("S");
}

double SVGPathSegCurvetoCubicSmoothAbs::get_x()
{
	return m_x;
}

void SVGPathSegCurvetoCubicSmoothAbs::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicSmoothAbs::get_y()
{
	return m_y;
}

void SVGPathSegCurvetoCubicSmoothAbs::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicSmoothAbs::get_x2()
{
	return m_x2;
}

void SVGPathSegCurvetoCubicSmoothAbs::set_x2(double newVal)
{
	m_x2 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicSmoothAbs::get_y2()
{
	return m_y2;
}

void SVGPathSegCurvetoCubicSmoothAbs::set_y2(double newVal)
{
	m_y2 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
