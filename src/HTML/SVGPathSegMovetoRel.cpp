#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegMovetoRel.h"

namespace System
{
namespace Web
{

SVGPathSegMovetoRel::SVGPathSegMovetoRel()
{
	m_x = m_y = 0;
}

double SVGPathSegMovetoRel::get_x() const
{
	return m_x;
}

void SVGPathSegMovetoRel::set_x(double newVal)
{
	m_x = newVal;
}

double SVGPathSegMovetoRel::get_y() const
{
	return m_y;
}

void SVGPathSegMovetoRel::set_y(double newVal)
{
	m_y = newVal;
}

}	// Web
}
