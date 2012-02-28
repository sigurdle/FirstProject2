#include "stdafx.h"
#include "LXUI2.h"
#include "Point.h"

//using namespace System;

namespace System
{
namespace UI
{

Point::Point()
{
	X = 0;
	Y = 0;
}

double Point::get_X() const
{
	return X;
}

/*
void _Point::set_X(double x)
{
	X = x;
}
*/

double Point::get_Y() const
{
	return Y;
}

/*
void _Point::set_Y(double y)
{
	Y = y;
}
*/

#if 0

Point::Point()
{
	m_p = NULL;//new _Point(0,0);
	m_pListener = NULL;
}

Point::Point(_Point * p)
{
	m_p = p;
	if (m_p) m_p->AddRef();

	m_pListener = NULL;
}

Point::Point(const Point& point)
{
	m_p = point.m_p;
	if (m_p) m_p->AddRef();

	m_pListener = NULL;
}

Point::Point(const Object& obj)
{
	m_p = dynamic_cast<_Point*>(obj.m_p);
	if (m_p) m_p->AddRef();

	m_pListener = NULL;
}

Point::Point(double X, double Y)
{
	m_p = new _Point(X, Y);
	m_p->AddRef();

	m_pListener = NULL;
}

Point::Point(LDraw::PointD point)
{
	m_p = new _Point(point.X, point.Y);
	m_p->AddRef();

	m_pListener = NULL;
}

Point::~Point()
{
	if (m_p)
	{
		m_p->Release();
	}
	ASSERT(m_pListener == NULL);
}

double Point::get_X() const
{
	if (m_p == NULL) THROW(-1);
	return m_p->m_X;
}

void Point::put_X(double newVal)
{
	if (m_p == NULL) THROW(-1);

	if (m_p->m_refcount > 1)
	{
		_Point* old = m_p;
		m_p = new _Point(m_p->m_X, m_p->m_Y);
		m_p->AddRef();
		old->Release();
	}

	m_p->m_X = newVal;
}

double Point::get_Y() const
{
	if (m_p == NULL) THROW(-1);
	return m_p->m_Y;
}

void Point::put_Y(double newVal)
{
	if (m_p == NULL) THROW(-1);

	if (m_p->m_refcount > 1)
	{
		_Point* old = m_p;
		m_p = new _Point(m_p->m_X, m_p->m_Y);
		m_p->AddRef();
		old->Release();
	}

	m_p->m_Y = newVal;
}

Point::operator LDraw::PointD() const
{
	ASSERT(m_p);
	if (m_p == NULL)
		THROW(-1);

	return LDraw::PointD(m_p->m_X, m_p->m_Y);
}

Point& Point::operator = (const Point& other)
{
	_Point* old = m_p;
	m_p = other.m_p;
	if (m_p) m_p->AddRef();
	if (old) old->Release();

	return *this;
}

bool Point::Equals(const Point& other) const
{
	if (m_p == other.m_p)
		return true;
	else if (m_p == NULL)
		return false;
	else if (other.m_p == NULL)
		return false;
	else
		return m_p->m_X == other.m_p->m_X && m_p->m_Y == other.m_p->m_Y;
}

#endif

}	// UI
}
