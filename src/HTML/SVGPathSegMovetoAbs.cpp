#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegMovetoAbs.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

ImmutableString<WCHAR> SVGPathSegMovetoAbs::s_pathSegTypeAsLetter(L"M");

SVGPathSegMovetoAbs::SVGPathSegMovetoAbs()
{
	m_x = m_y = 0;
}

void SVGPathSegMovetoAbs::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

void SVGPathSegMovetoAbs::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
