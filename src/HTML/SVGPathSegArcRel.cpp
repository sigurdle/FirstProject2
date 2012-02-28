#include "stdafx.h"
#include "HTML2.h"
#include "SVGPathSegArcRel.h"

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

SVGPathSegArcRel::SVGPathSegArcRel()
{
	m_x = 0;
	m_y = 0;
	m_r1 = 0;
	m_r2 = 0;
	m_angle = 0;
	m_largeArcFlag = false;
	m_sweepFlag = false;
}

double SVGPathSegArcRel::get_x()
{
	return m_x;
}

void SVGPathSegArcRel::set_x(double newVal)
{
	m_x = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegArcRel::get_y()
{
	return m_y;
}

void SVGPathSegArcRel::set_y(double newVal)
{
	m_y = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegArcRel::get_r1()
{
	return m_r1;
}

void SVGPathSegArcRel::set_r1(/*[in]*/ double newVal)
{
	m_r1 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegArcRel::get_r2()
{
	return m_r2;
}

void SVGPathSegArcRel::set_r2(/*[in]*/ double newVal)
{
	m_r2 = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

double SVGPathSegArcRel::get_angle()
{
	return m_angle;
}

void SVGPathSegArcRel::set_angle(/*[in]*/ double newVal)
{
	m_angle = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

bool SVGPathSegArcRel::get_largeArcFlag()
{
	return m_largeArcFlag;
}

void SVGPathSegArcRel::set_largeArcFlag(/*[in]*/ bool newVal)
{
	m_largeArcFlag = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

bool SVGPathSegArcRel::get_sweepFlag()
{
	return m_sweepFlag;
}

void SVGPathSegArcRel::set_sweepFlag(/*[in]*/ bool newVal)
{
	m_sweepFlag = newVal;
	if (m_pSegList) m_pSegList->ChangedSeg();
}

}	// Web
}
