#include "stdafx.h"
#include "LXML2.h"

#ifdef AMIGA
#define new DEBUG_NEW
#endif

#include "SVGMatrix.h"

namespace System
{
namespace Web
{

SVGMatrix::SVGMatrix()
// ???	: m_matrix(LDraw::matrix3f::getIdenity())
{
}

SVGMatrix::SVGMatrix(const gm::matrix3d& m) :
	m_matrix(m)
{
}

SVGMatrix::SVGMatrix(double a, double b, double c, double d, double e, double f) :
	m_matrix(a, b, 0, c, d, 0, e, f, 1)
{
}

SVGMatrix::~SVGMatrix()
{
}

void SVGMatrix::assign(double a, double b, double c, double d, double e, double f)
{
	m_matrix.assign(a, b, 0, c, d, 0, e, f, 1);
}

double SVGMatrix::get_a() const
{
	return m_matrix[0][0];
}

void SVGMatrix::set_a(double newVal)
{
	m_matrix[0][0] = newVal;
}

double SVGMatrix::get_b() const
{
	return m_matrix[0][1];
}

void SVGMatrix::set_b(double newVal)
{
	m_matrix[0][1] = newVal;
}

double SVGMatrix::get_c() const
{
	return m_matrix[1][0];
}

void SVGMatrix::set_c(double newVal)
{
	m_matrix[1][0] = newVal;
}

double SVGMatrix::get_d() const
{
	return m_matrix[1][1];
}

void SVGMatrix::set_d(double newVal)
{
	m_matrix[1][1] = newVal;
}

double SVGMatrix::get_e() const
{
	return m_matrix[2][0];
}

void SVGMatrix::set_e(double newVal)
{
	m_matrix[2][0] = newVal;
}

double SVGMatrix::get_f() const
{
	return m_matrix[2][1];
}

void SVGMatrix::set_f(double newVal)
{
	m_matrix[2][1] = newVal;
}

SVGMatrix* SVGMatrix::translate(double dx, double dy) const
{
	SVGMatrix* result = new SVGMatrix;
	result->m_matrix = m_matrix * gm::matrix3d::getTranslate(dx, dy);
	return result;
}

SVGMatrix* SVGMatrix::rotate(double angle) const
{
	SVGMatrix* result = new SVGMatrix;
	result->m_matrix = m_matrix * gm::matrix3d::getRotate(angle);
	return result;
}

SVGMatrix* SVGMatrix::skewX(double angle) const
{
	SVGMatrix* result = new SVGMatrix;
	result->m_matrix = m_matrix * gm::matrix3d::getSkewX(angle);
	return result;
}

SVGMatrix* SVGMatrix::skewY(double angle) const
{
	SVGMatrix* result = new SVGMatrix;
	result->m_matrix = m_matrix * gm::matrix3d::getSkewY(angle);
	return result;
}

SVGMatrix* SVGMatrix::scaleNonUniform(double sx, double sy) const
{
	SVGMatrix* result = new SVGMatrix;
	result->m_matrix = m_matrix * gm::matrix3d::getScale(sx, sy);
	return result;
}

SVGMatrix* SVGMatrix::scale(double scaleFactor) const
{
	SVGMatrix* result = new SVGMatrix;
	result->m_matrix = m_matrix * gm::matrix3d::getScale(scaleFactor, scaleFactor);
	return result;
}

SVGMatrix* SVGMatrix::multiply(SVGMatrix *pOther) const
{
	SVGMatrix* result = new SVGMatrix;
	result->m_matrix = m_matrix * pOther->m_matrix;
	return result;
}

SVGMatrix* SVGMatrix::inverse() const
{
	return new SVGMatrix(m_matrix.getInverse());
}

SVGMatrix* SVGMatrix::flipY() const
{
	ASSERT(0);
	return NULL;
}

SVGMatrix* SVGMatrix::flipX() const
{
	ASSERT(0);
	return NULL;
}

SVGMatrix* SVGMatrix::rotateFromVector(double x, double y) const
{
	ASSERT(0);
	return NULL;
}

SVGMatrix & SVGMatrix::operator = (const SVGMatrix & other)
{
	m_matrix = other.m_matrix;
	return *this;
}

}	// Web
}

#if 0
STDMETHODIMP SVGMatrix::setTranslate(double dx, double dy)
{
	m_matrix = gmMatrix3::translate(dx, dy);
	return S_OK;
}

STDMETHODIMP SVGMatrix::setScaleNonUniform(double sx, double sy)
{
	m_matrix = gmMatrix3::scale(sx, sy);
	return S_OK;
}

STDMETHODIMP SVGMatrix::setRotate(double angle)
{
	m_matrix = gmMatrix3::rotate(angle);
	return S_OK;
}
#endif
