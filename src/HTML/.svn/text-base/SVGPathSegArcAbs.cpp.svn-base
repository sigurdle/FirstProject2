#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegArcAbs.h"

namespace System
{
namespace Web
{

SVGPathSegArcAbs::SVGPathSegArcAbs()
{
	m_x = 0;
	m_y = 0;
	m_r1 = 0;
	m_r2 = 0;
	m_angle = 0;
	m_largeArcFlag = false;
	m_sweepFlag = false;
}

ImmutableString<WCHAR> SVGPathSegArcAbs::pathSegTypeAsLetter(L"A");

String SVGPathSegArcAbs::get_pathSegTypeAsLetter() const
{
	return &pathSegTypeAsLetter;
}

double SVGPathSegArcAbs::get_x() const
{
	return m_x;
}

void SVGPathSegArcAbs::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegArcAbs::get_y() const
{
	return m_y;
}

void SVGPathSegArcAbs::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegArcAbs::get_r1() const
{
	return m_r1;
}

void SVGPathSegArcAbs::set_r1(/*[in]*/ double newVal)
{
	m_r1 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegArcAbs::get_r2() const
{
	return m_r2;
}

void SVGPathSegArcAbs::set_r2(/*[in]*/ double newVal)
{
	m_r2 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegArcAbs::get_angle() const
{
	return m_angle;
}

void SVGPathSegArcAbs::set_angle(/*[in]*/ double newVal)
{
	m_angle = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

bool SVGPathSegArcAbs::get_largeArcFlag() const
{
	return m_largeArcFlag;
}

void SVGPathSegArcAbs::set_largeArcFlag(/*[in]*/ bool newVal)
{
	m_largeArcFlag = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

bool SVGPathSegArcAbs::get_sweepFlag() const
{
	return m_sweepFlag;
}

void SVGPathSegArcAbs::set_sweepFlag(/*[in]*/ bool newVal)
{
	m_sweepFlag = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
