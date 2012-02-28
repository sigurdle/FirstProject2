#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegLinetoAbs.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

double SVGPathSegLinetoAbs::get_x()
{
	return m_x;
}

void SVGPathSegLinetoAbs::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegLinetoAbs::get_y()
{
	return m_y;
}

void SVGPathSegLinetoAbs::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
