#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegLinetoRel.h"

namespace System
{
namespace Web
{

void SVGPathSegLinetoRel::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegLinetoRel::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}