#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegLinetoVerticalRel.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

void SVGPathSegLinetoVerticalRel::set_y(double y)
{
	m_y = y;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
