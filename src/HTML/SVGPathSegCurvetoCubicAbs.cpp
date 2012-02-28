#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegCurvetoCubicAbs.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

SVGPathSegCurvetoCubicAbs::SVGPathSegCurvetoCubicAbs()
{
	m_x = 0;
	m_y = 0;
	m_x1 = 0;
	m_y1 = 0;
	m_x2 = 0;
	m_y2 = 0;
}

SVGPathSegType SVGPathSegCurvetoCubicAbs::get_pathSegType() const
{
	return PATHSEG_CURVETO_CUBIC_ABS;
}

String SVGPathSegCurvetoCubicAbs::get_pathSegTypeAsLetter() const
{
	return WSTR("C");
}

double SVGPathSegCurvetoCubicAbs::get_x()
{
	return m_x;
}

void SVGPathSegCurvetoCubicAbs::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicAbs::get_y()
{
	return m_y;
}

void SVGPathSegCurvetoCubicAbs::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicAbs::get_x1()
{
	return m_x1;
}

void SVGPathSegCurvetoCubicAbs::set_x1(double newVal)
{
	m_x1 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicAbs::get_y1()
{
	return m_y1;
}

void SVGPathSegCurvetoCubicAbs::set_y1(double newVal)
{
	m_y1 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicAbs::get_x2()
{
	return m_x2;
}

void SVGPathSegCurvetoCubicAbs::set_x2(double newVal)
{
	m_x2 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicAbs::get_y2()
{
	return m_y2;
}

void SVGPathSegCurvetoCubicAbs::set_y2(double newVal)
{
	m_y2 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
