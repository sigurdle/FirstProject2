#include "stdafx.h"
#include "LXML2.h"
#include "SVGPoint.h"
#include "SVGMatrix.h"
#include "SVGPointList.h"

namespace System
{
namespace Web
{

SVGPoint::SVGPoint() :
	m_x(0),
	m_y(0),
	m_owner(NULL)
{
}

SVGPoint::SVGPoint(gm::PointD point) :
	m_x(point.X),
	m_y(point.Y),
	m_owner(NULL)
{
}

SVGPoint::SVGPoint(double x, double y) :
	m_x(x),
	m_y(y),
	m_owner(NULL)
{
}

SVGPoint::SVGPoint(ISVGPointListener* owner) : m_owner(NULL)
{
}

double SVGPoint::get_x() const
{
	return m_x;
}

void SVGPoint::set_x(double newVal)
{
	if (m_x != newVal)
	{
		double oldx = m_x;

		m_x = newVal;

		if (m_owner)
			m_owner->OnPointChanged(this, oldx, m_y);
	}
}

double SVGPoint::get_y() const
{
	return m_y;
}

void SVGPoint::set_y(double newVal)
{
	if (m_y != newVal)
	{
		double oldy = m_y;

		m_y = newVal;

		if (m_owner)
			m_owner->OnPointChanged(this, m_x, oldy);
	}
}

SVGPoint* SVGPoint::matrixTransform(const SVGMatrix* matrix) const
{
	return new SVGPoint(matrix->GetM().transform(gm::PointD(m_x, m_y)));
}

}	// Web
}
