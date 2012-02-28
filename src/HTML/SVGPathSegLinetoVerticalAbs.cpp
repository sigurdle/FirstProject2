#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegLinetoVerticalAbs.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

void SVGPathSegLinetoVerticalAbs::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
