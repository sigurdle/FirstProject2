#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegLinetoHorizontalRel.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

CTOR SVGPathSegLinetoHorizontalRel::SVGPathSegLinetoHorizontalRel()
{
	m_x = 0;
}

double SVGPathSegLinetoHorizontalRel::get_x()
{
	return m_x;
}

void SVGPathSegLinetoHorizontalRel::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

SVGPathSegType SVGPathSegLinetoHorizontalRel::get_pathSegType() const
{
	return PATHSEG_LINETO_HORIZONTAL_REL;
}

String SVGPathSegLinetoHorizontalRel::get_pathSegTypeAsLetter() const
{
	return WSTR("h");
}

}	// Web
}
