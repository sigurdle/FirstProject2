#include "stdafx.h"

#if 0
#include "LHTML.h"
#include "SVGTransformListValue.h"

#include "LSVGMatrix.h"
#include "LSVGTransform.h"
#include "LSVGTransformList.h"

int GetTransformValuesArray(CUString str, CArray <double,double>& values)
{
	int len = str.GetLength();
	LPCTSTR p = str;
	int i = 0;

	while (i < len)
	{
		CUString str_value;
		while ((i < len) && (p[i] != ',') && (p[i] != ' '))
		{
			str_value += CUString(p[i]);
			i++;
		}

		while (i < len && p[i] == ' ') i++;	// Skip spaces

		if (p[i] == ',') i++;

		while (i < len && p[i] == ' ') i++;	// Skip spaces

		str_value.TrimLeft();
		str_value.TrimRight();

		double value = atof(str_value);
		values.Add(value);
	}

	return values.GetSize();
}

void GetTranslateValues(CUString param_string, float& x, float& y)
{
	CArray <double,double> values;
	int n = GetTransformValuesArray(param_string, values);

	if (n == 2)
	{
		x = values[0];
		y = values[1];
	}
	else if (n == 1)
	{
		x = values[0];
		y = 0;
	}
}

void GetScaleValues(CUString param_string, float& sx, float& sy)
{
	CArray <double,double> values;
	int n = GetTransformValuesArray(param_string, values);

	if (n == 2)
	{
		sx = values[0];
		sy = values[1];
	}
	else if (n == 1)
	{
		sx = values[0];
		sy = sx;
	}
}

void GetRotateValues(CUString param_string, float &deg, float& cx, float& cy)
{
	CArray <double,double> values;
	int n = GetTransformValuesArray(param_string, values);

	if (n == 1)
	{
		deg = values[0];
		cx = cy = 0;
	}
	else if (n == 2)
	{
		deg = values[0];
		cx = values[1];
		cy = 0;
	}
	else if (n == 3)
	{
		deg = values[0];
		cx = values[1];
		cy = values[2];
	}
}

void GetSkewValues(CUString param_string, float &deg)
{
	CArray <double,double> values;
	int n = GetTransformValuesArray(param_string, values);

	if (n == 1)
	{
		deg = values[0];
	}
	else
		deg = 0;
}

void GetMatrixValues(CUString param_string, ILSVGMatrix* matrix)
{
	CArray <double,double> values;
	int n = GetTransformValuesArray(param_string, values);

	if (n == 6)
	{
		matrix->set_a(values[0]); matrix->set_b(values[1]);
		matrix->set_c(values[2]); matrix->set_d(values[3]);
		matrix->set_e(values[4]); matrix->set_f(values[5]);
	}
}

void ParseTransform(ILSVGTransformList* transformlist, BSTR s)
{
	_bstr_t transform_str = s;

	transformlist->clear();

	if (transform_str.length() > 0)
	{
		WCHAR* p = (WCHAR*)transform_str;

		while (*p)
		{
			while (*p && *p == L' ') p++;	// Skip spaces

			CUString transform_type;

			// Get type
			while (*p && iswalpha(*p))
			{
				transform_type += CUString(*p);
				p++;
			}

			while (*p && *p == ' ') p++;	// Skip spaces

		// Get string inside ( )
			if (*p++ != L'(') break;	// Error

			CUString param_string;

			while (*p && *p != L')')
			{
				param_string += CUString(*p);
				p++;
			}

			if (*p++ != L')') break; // Error

			while (*p && *p == ' ') p++;	// Skip spaces

			CComObject<CLSVGTransform>* transform;

			if (!strcmp(transform_type, "translate"))
			{
				float x, y;
				GetTranslateValues(param_string, x, y);

				CComObject<CLSVGTransform>::CreateInstance(&transform);
				transform->AddRef();
				transform->setTranslate(x, y);
			}
			else if (!strcmp(transform_type, "rotate"))
			{
				float deg, cx, cy;
				GetRotateValues(param_string, deg, cx, cy);

				CComObject<CLSVGTransform>::CreateInstance(&transform);
				transform->AddRef();
				transform->setRotate(deg, cx, cy);
			}
			else if (!strcmp(transform_type, "scale"))
			{
				float sx, sy;
				GetScaleValues(param_string, sx, sy);

				CComObject<CLSVGTransform>::CreateInstance(&transform);
				transform->AddRef();
				transform->setScale(sx, sy);
			}
			else if (!strcmp(transform_type, "skewX"))
			{
				float deg;
				GetSkewValues(param_string, deg);

				CComObject<CLSVGTransform>::CreateInstance(&transform);
				transform->AddRef();
				transform->setSkewX(deg);
			}
			else if (!strcmp(transform_type, "skewY"))
			{
				float deg;
				GetSkewValues(param_string, deg);

				CComObject<CLSVGTransform>::CreateInstance(&transform);
				transform->AddRef();
				transform->setSkewY(deg);
			}
			else if (!strcmp(transform_type, "matrix"))
			{
				CComObject<CLSVGMatrix>* matrix;
				CComObject<CLSVGMatrix>::CreateInstance(&matrix);

				GetMatrixValues(param_string, matrix);

				CComObject<CLSVGTransform>::CreateInstance(&transform);
				transform->AddRef();
				transform->setMatrix(matrix);
			}

			if (transform != NULL)
			{
				transformlist->appendItem(transform, NULL);
				transform->Release();
			}
		}
	}
}

//////////////

_bstr_t StringFromTransformList(ILSVGTransformList* transformlist)
{
	CUString str;

	long numberOfItems;
	transformlist->get_numberOfItems(&numberOfItems);

	for (int i = 0; i < numberOfItems; i++)
	{
		CComPtr<ILSVGTransform> transform;
		transformlist->getItem(i, &transform);

		LSVGTransformType type;
		transform->get_type(&type);

		double angle;
		transform->get_angle(&angle);

		CComQIPtr<ILSVGMatrix> matrix;
		transform->get_matrix(&matrix);

		double a; matrix->get_a(&a);
		double b; matrix->get_b(&b);
		double c; matrix->get_c(&c);
		double d; matrix->get_d(&d);
		double e; matrix->get_e(&e);
		double f; matrix->get_f(&f);

	//	CSVGTransform* pTransform = reinterpret_cast<CSVGTransform*>(transform.p);

		if (i > 0) str += L" ";

		if (type == SVG_TRANSFORM_TRANSLATE)
		{
			CUString str2;
			str2.Format("translate(%g, %g)", e, f);
			str += str2;
		}
		else if (type == SVG_TRANSFORM_SCALE)
		{
		/*	CUString str2;
			str2.Format("scale(%g, %g)", pTransform->m_x, pTransform->m_y);
			str += str2;
			*/
		}
		else if (type == SVG_TRANSFORM_ROTATE)
		{
			CUString str2;
			str2.Format("rotate(%g, %g, %g)", angle, e, f);
			str += str2;
		}
		else if (type == SVG_TRANSFORM_SKEWX)
		{
			CUString str2;
			str2.Format("skewX(%g)", angle);
			str += str2;
		}
		else if (type == SVG_TRANSFORM_SKEWY)
		{
			CUString str2;
			str2.Format("skewY(%g)", angle);
			str += str2;
		}
		else if (type == SVG_TRANSFORM_MATRIX)
		{
			CUString str2;
			str2.Format("matrix(%g %g %g %g %g %g)", a, b, c, d, e, f);
			str += str2;
		}
	}

	return _bstr_t(str);
}

//////////////

CSVGTransformListValue::CSVGTransformListValue()
{
	CComObject<CLSVGTransformList>::CreateInstance(&m_transformlist);
	m_transformlist->AddRef();
}

CSVGTransformListValue::operator = (CSVGTransformListValue& value)
{
	if (m_transformlist)
	{
		m_transformlist->Release();
		m_transformlist = NULL;
	}
	// hmm. make copy
	m_transformlist = value.m_transformlist;
	m_transformlist->AddRef();
//	ATLASSERT(0);
}

void CSVGTransformListValue::operator = (BSTR bstr)
{
	ParseTransform(m_transformlist, bstr);
}

CSVGTransformListValue::operator _bstr_t ()
{
	return StringFromTransformList(m_transformlist);
}

void CSVGTransformListValue::InterpolateValue(CSVGTransformListValue* a, CSVGTransformListValue* b, double t)
{
}
#endif