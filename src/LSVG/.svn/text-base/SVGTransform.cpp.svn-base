#include "stdafx.h"
#include "LSVG.h"
#include "SVGTransform.h"

namespace System
{
namespace Web
{

SVGTransform::SVGTransform()
{
	m_type = SVG_TRANSFORM_UNKNOWN;
	m_angle = 0;
	m_owner = NULL;
	m_matrix = new SVGMatrix;
//	m_matrix->m_owner = this;
}

SVGTransform::SVGTransform(const SVGMatrix* matrix)
{
	m_type = SVG_TRANSFORM_MATRIX;
	m_matrix = new SVGMatrix(matrix->m_matrix);
//	m_matrix->m_owner = this;
}

SVGTransform::~SVGTransform()
{
	delete m_matrix;
}

SVGTransformType SVGTransform::get_type() const
{
	return m_type;
}

SVGMatrix* SVGTransform::get_matrix() const
{
	return m_matrix;
}

double SVGTransform::get_angle() const
{
	return m_angle;
}

void SVGTransform::setMatrix(const SVGMatrix* matrix)
{
	readOnly();
}

void SVGTransformMutable::setMatrix(const SVGMatrix* matrix)
{
	if (matrix == NULL) throw std::exception("null pointer");

	m_type = SVG_TRANSFORM_MATRIX;

// Copy the matrix
	m_matrix->m_matrix = matrix->m_matrix;

	OnChanged();
}

void SVGTransformMutable::OnChanged()
{
	if (m_owner)
	{
		m_owner->OnChanged();
	}
}

void SVGTransform::SetSkewX(double angle)
{
	m_type = SVG_TRANSFORM_SKEWX;
	m_angle = angle;

	m_matrix->assign(	1, 0,
							tan(angle * M_PI/180), 1,
							0, 0);
		/*
	m_matrix->set_a(1);								m_matrix->set_b(0);
	m_matrix->set_c(tan(angle * M_PI/180));	m_matrix->set_d(1);
	m_matrix->set_e(0);								m_matrix->set_f(0);
	*/
}

void SVGTransform::SetSkewY(double angle)
{
	m_type = SVG_TRANSFORM_SKEWY;
	m_angle = angle;

	m_matrix->assign(	1, tan(angle * M_PI/180),
							0, 1,
							0, 0);

	/*
	m_matrix->set_a(1);								m_matrix->set_b(tan(angle * M_PI/180));
	m_matrix->set_c(0);								m_matrix->set_d(1);
	m_matrix->set_e(0);								m_matrix->set_f(0);
	*/
}

void SVGTransform::SetRotate(double angle, double cx, double cy)
{
	m_type = SVG_TRANSFORM_ROTATE;
	m_angle = angle;
	m_x = cx;
	m_y = cy;

	gm::matrix3d mat;
	mat = gm::matrix3d::getTranslate(-cx, -cy);
	mat *= gm::matrix3d::getRotate(angle);
	mat *= gm::matrix3d::getTranslate(cx, cy);

	m_matrix->m_matrix = mat;

	/*
	m_matrix->set_a(mat[0][0]); m_matrix->set_b(mat[0][1]);
	m_matrix->set_c(mat[1][0]); m_matrix->set_d(mat[1][1]);
	m_matrix->set_e(mat[2][0]); m_matrix->set_f(mat[2][1]);
	*/
}

void SVGTransform::SetScale(double sx, double sy)
{
	m_type = SVG_TRANSFORM_SCALE;
	m_x = sx;
	m_y = sy;

	gm::matrix3d mat;
	mat = gm::matrix3d::getScale(sx, sy);

	m_matrix->set_a(mat[0][0]); m_matrix->set_b(mat[0][1]);
	m_matrix->set_c(mat[1][0]); m_matrix->set_d(mat[1][1]);
	m_matrix->set_e(mat[2][0]); m_matrix->set_f(mat[2][1]);
}

void SVGTransform::SetTranslate(double tx, double ty)
{
	m_type = SVG_TRANSFORM_TRANSLATE;
	m_x = tx;
	m_y = ty;

	m_matrix->m_matrix = gm::matrix3d::getTranslate(tx, ty);
}

void SVGTransform::setTranslate(double tx, double ty)
{
	readOnly();
}

void SVGTransformMutable::setTranslate(double tx, double ty)
{
	SetTranslate(tx, ty);

	OnChanged();
/*	if (m_pListener)
		m_pListener->OnChanged(this);
*/
}

void SVGTransform::setScale(double sx, double sy)
{
	readOnly();
}

void SVGTransformMutable::setScale(double sx, double sy)
{
	SetScale(sx, sy);

	OnChanged();
/*	if (m_pListener)
		m_pListener->OnChanged(this);
*/
}

void SVGTransform::setRotate(double angle, double cx, double cy)
{
	readOnly();
}

void SVGTransformMutable::setRotate(double angle, double cx, double cy)
{
	SetRotate(angle, cx, cy);

	OnChanged();
/*	if (m_pListener)
		m_pListener->OnChanged(this);
		*/
}

void SVGTransform::setSkewX(double angle)
{
	readOnly();
}

void SVGTransformMutable::setSkewX(double angle)
{
	SetSkewX(angle);

	OnChanged();
/*	if (m_pListener)
		m_pListener->OnChanged(this);
*/
}

void SVGTransform::setSkewY(double angle)
{
	readOnly();
}

void SVGTransformMutable::setSkewY(double angle)
{
	SetSkewY(angle);

	OnChanged();
	/*
	if (m_pListener)
		m_pListener->OnChanged(this);
		*/
}

SVGTransformList* SVGTransform::get_transformList()
{
	return m_owner;
}

////////////////////////////////////////////////////////////////


void GetTranslateValues(const WCHAR* param_string, double& x, double& y);
void GetScaleValues(const WCHAR* param_string, double& sx, double& sy);
void GetRotateValues(const WCHAR* param_string, double &deg, double& cx, double& cy);
void GetSkewValues(const WCHAR* param_string, double &deg);
void GetMatrixValues(const WCHAR* param_string, SVGMatrix* matrix);

void SVGTransform::setStringValue(StringIn str)
{
	ASSERT(0);
#if 0
	switch (m_type)
	{
	case SVG_TRANSFORM_TRANSLATE:
		{
			double x, y;
			GetTranslateValues(str->c_str(), x, y);

			SetTranslate(x, y);
		}
		break;

	case SVG_TRANSFORM_ROTATE:
		{
			double deg, cx, cy;
			GetRotateValues(str->c_str(), deg, cx, cy);

			setRotate(deg, cx, cy);
		}
		break;

	case SVG_TRANSFORM_SCALE:
		{
			double sx, sy;
			GetScaleValues(str->c_str(), sx, sy);

			SetScale(sx, sy);
		}
		break;

	case SVG_TRANSFORM_SKEWX:
		{
			double deg;
			GetSkewValues(str->c_str(), deg);

			SetSkewX(deg);
		}
		break;

	case SVG_TRANSFORM_SKEWY:
		{
			double deg;
			GetSkewValues(str->c_str(), deg);

			SetSkewY(deg);
		}
		break;

	case SVG_TRANSFORM_MATRIX:
		{
			GetMatrixValues(str->c_str(), m_matrix);
		}
		break;
	}
#endif
}

String SVGTransform::getStringValue()
{
	SVGMatrix* matrix = get_matrix();

	double a = matrix->get_a();
	double b = matrix->get_b();
	double c = matrix->get_c();
	double d = matrix->get_d();
	double e = matrix->get_e();
	double f = matrix->get_f();

	WCHAR str2[256];

	switch (m_type)
	{
		case SVG_TRANSFORM_TRANSLATE:
		{
			swprintf_s(str2, L"%g, %g", e, f);
		}
		break;

		case SVG_TRANSFORM_SCALE:
		{
			swprintf_s(str2, L"%g, %g", a, d);
		}
		break;

		case SVG_TRANSFORM_ROTATE:
		{
			if (e == 0 && f == 0)
				swprintf_s(str2, L"%g", m_angle);
			else
				swprintf_s(str2, L"%g, %g, %g", m_angle, e, f);
		}
		break;

		case SVG_TRANSFORM_SKEWX:
		{
			swprintf_s(str2, L"%g", m_angle);
		}
		break;

		case SVG_TRANSFORM_SKEWY:
		{
			swprintf_s(str2, L"%g", m_angle);
		}
		break;

		case SVG_TRANSFORM_MATRIX:
		{
			swprintf_s(str2, L"%g %g %g %g %g %g", a, b, c, d, e, f);
		}
		break;
	}

	return string_copy(str2);
}

void SVGTransform::readOnly()
{
	throw new Exception(WSTR("SVGTransform is readOnly"));
}

void SVGTransform::InterpolateValue(const SVGTransform& a, const SVGTransform& b, double t)
{
	ASSERT(m_type == a.m_type);
	ASSERT(m_type == b.m_type);

	switch (m_type)
	{
		case SVG_TRANSFORM_TRANSLATE:
		{
			double x = a.m_x + (b.m_x-a.m_x)*t;
			double y = a.m_y + (b.m_y-a.m_y)*t;

			setTranslate(x, y);
		}
		break;

#if 0
		case SVG_TRANSFORM_SCALE:
		{
			swprintf(str2, OLESTR("%g, %g", a, d);
		}
		break;
#endif

		case SVG_TRANSFORM_ROTATE:
		{
			double angle = a.m_angle + (b.m_angle - a.m_angle)*t;
			double cx = a.m_x + (b.m_x - a.m_x)*t;
			double cy = a.m_y + (b.m_y - a.m_y)*t;

			setRotate(angle, cx, cy);
		}
		break;

#if 0
		case SVG_TRANSFORM_SKEWX:
		{
			swprintf(str2, OLESTR("%g", m_angle);
		}
		break;

		case SVG_TRANSFORM_SKEWY:
		{
			swprintf(str2, OLESTR("%g", m_angle);
		}
		break;

		case SVG_TRANSFORM_MATRIX:
		{
			swprintf(str2, OLESTR("%g %g %g %g %g %g", a, b, c, d, e, f);
		}
		break;
#endif
	}
}

/*
SVGTransform& SVGTransform::operator = (const SVGTransform& value)
{
	m_type = value.m_type;
	m_x = value.m_x;
	m_y = value.m_y;
	m_angle = value.m_angle;
	m_matrix->m_matrix = value.m_matrix->m_matrix;

	return *this;
}

SVGTransform& SVGTransform::operator += (const SVGTransform& value)
{
	ASSERT(0);
	return *this;
}
*/

}	// Web
}
