#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegCurvetoCubicSmoothRel.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

double SVGPathSegCurvetoCubicSmoothRel::get_x()
{
	return m_x;
}

void SVGPathSegCurvetoCubicSmoothRel::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicSmoothRel::get_y()
{
	return m_y;
}

void SVGPathSegCurvetoCubicSmoothRel::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicSmoothRel::get_x2()
{
	return m_x2;
}

void SVGPathSegCurvetoCubicSmoothRel::set_x2(double newVal)
{
	m_x2 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegCurvetoCubicSmoothRel::get_y2()
{
	return m_y2;
}

void SVGPathSegCurvetoCubicSmoothRel::set_y2(double newVal)
{
	m_y2 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
