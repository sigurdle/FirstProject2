#include "stdafx.h"
#include "LSVG2.h"
#include "SVGTransformList.h"

#include "SVGTransform.h"

namespace System
{
namespace Web
{

SVGTransformList::SVGTransformList()
{
	m_p = new SVGTransformListData;
}

SVGTransformList::SVGTransformList(SVGTransformListData* p)
{
	m_p = p;
}

SVGTransformList::~SVGTransformList()
{
//		ASSERT(m_pListener == NULL);
	RemoveAll();
}

void SVGTransformList::RemoveAll()
{
	for (int i = 0; i < m_p->m_items.GetSize(); i++)
	{
		m_p->m_items[i]->m_owner = NULL;
//		m_p->m_items[i]->m_pListener = NULL;
//		m_items[i]->Release();
	}

	m_p->m_items.RemoveAll();
}

gm::matrix3d SVGTransformList::consolidateToMatrix2() const
{
	gm::matrix3d mat = gm::matrix3d::getIdentity();

	for (unsigned int i = 0; i < m_p->m_items.size(); ++i)
	{
		mat = m_p->m_items[i]->m_matrix->GetM() * mat;
	}

	return mat;
}

gm::Matrix3d* SVGTransformList::consolidateToMatrix()
{
	gm::Matrix3d* mat = new gm::Matrix3d(consolidateToMatrix2());
	return mat;
}

unsigned int SVGTransformList::get_numberOfItems() const
{
	return m_p->m_items.GetSize();
}

void SVGTransformList::clear()
{
	readOnly();
}

void SVGTransformListMutable::clear()
{
	if (m_p->m_items.GetSize() > 0)
	{
		RemoveAll();

		OnChanged();
		/*
		if (m_pListener)
		{
			m_pListener->OnChanged(this);
		}
		*/
	}
}

SVGTransform* SVGTransformList::initialize(SVGTransform* newItem)
{
	readOnly();
	return NULL;
}

SVGTransform* SVGTransformListMutable::initialize(SVGTransform* newItem)
{
	if (newItem == NULL) THROW(std::exception("null pointer"));

	RemoveAll();

	m_p->m_items.Add(newItem);
//	newItem->m_pListener = this;
	newItem->m_owner = this;

	OnChanged();
/*	if (m_pListener)
	{
		m_pListener->OnChanged(this);
	}
*/

	return newItem;
}

SVGTransform* SVGTransformList::getItem(unsigned int index) const
{
	if (index < m_p->m_items.GetSize())
	{
		return m_p->m_items[index];
	}
	else
		return NULL;
}

SVGTransform* SVGTransformList::insertItemBefore(SVGTransform* newItem, unsigned int index)
{
	readOnly();
	return NULL;
}

SVGTransform* SVGTransformListMutable::insertItemBefore(SVGTransform* newItem, unsigned int index)
{
	if (newItem == NULL) THROW(std::exception("null pointer"));

	m_p->m_items.InsertAt(index, newItem);
//	newItem->m_pListener = this;
	newItem->m_owner = this;

	OnChanged();
/*	if (m_pListener)
	{
		m_pListener->OnChanged(this);
	}
*/

	return newItem;
}

SVGTransform* SVGTransformList::replaceItem(SVGTransform* newItem, unsigned int index)
{
	readOnly();
	return NULL;
}

SVGTransform* SVGTransformListMutable::replaceItem(SVGTransform* newItem, unsigned int index)
{
	ASSERT(0);
	return NULL;
}

SVGTransform* SVGTransformList::removeItem(unsigned int index)
{
	readOnly();
	return NULL;
}

SVGTransform* SVGTransformListMutable::removeItem(unsigned int index)
{
	if (index < m_p->m_items.GetSize())
	{
		SVGTransform* old = m_p->m_items[index];
		m_p->m_items.RemoveAt(index);

		OnChanged();
/*		if (m_pListener)
		{
			m_pListener->OnChanged(this);
		}
*/
		return old;
	}
	else
	{
		ASSERT(0);
		return NULL;
	}
}

SVGTransform* SVGTransformList::appendItem(SVGTransform* newItem)
{
	readOnly();
	return NULL;
}

SVGTransform* SVGTransformListMutable::appendItem(SVGTransform* newItem)
{
	if (newItem == NULL) THROW(std::exception("null pointer"));

	m_p->m_items.Add(newItem);
//	newItem->m_pListener = this;
	newItem->m_owner = this;

	OnChanged();
/*	if (m_pListener)
	{
		m_pListener->OnChanged(this);
	}
*/

	return newItem;
}

SVGTransform* SVGTransformList::createSVGTransformFromMatrix(const SVGMatrix* matrix)
{
	readOnly();
	return NULL;
}

SVGTransform* SVGTransformListMutable::createSVGTransformFromMatrix(const SVGMatrix* matrix)
{
	SVGTransform* transform = new SVGTransform(matrix);
	transform->m_owner = this;
	RemoveAll();
	m_p->m_items.push_back(transform);
	return transform;
}

SVGTransform* SVGTransformList::consolidate()
{
	readOnly();
	return NULL;
}

void SVGTransformList::readOnly()
{
	throw std::exception("SVGTransformList is read only");
}

SVGTransform* SVGTransformListMutable::consolidate()
{
	if (m_p->m_items.GetSize() > 0)
	{
		SVGTransform* pTransform = new SVGTransform;
		pTransform->m_type = SVG_TRANSFORM_MATRIX;
		pTransform->m_matrix->GetM() = consolidateToMatrix2();
			//??? pTransform->m_matrix->m_pListener = pTransform;

		pTransform->m_owner = this;
//		pTransform->m_pListener = this;

		RemoveAll();

		m_p->m_items.Add(pTransform);

		OnChanged();
		/*
		if (m_pListener)
		{
			m_pListener->OnChanged(this);
		}
		*/

		return pTransform;
	}

	return NULL;
}

void SVGTransformList::OnChanged()
{
	ASSERT(m_changed);
	m_changed(m_changedArg);

	/*
	if (m_pListener)
	{
		m_pListener->OnChanged(this);
	}
	*/
}

////////////

int GetTransformValuesArray(const WCHAR* str, vector<double>& values)
{
//	int len = str.GetLength();
	const WCHAR* p = str;

	while (*p && isspace(*p)) p++;	// Skip spaces

	//int i = 0;
	while (*p)
	{
		double value = getfnumber(&p);
		if (p == NULL)
		{
			values.RemoveAll();	// On error, make all values parsed so far invalid?
			return 0;
		}

			/*
		CWCharString str_value;
		while (*p && (*p != ',') && (*p != ' '))
		{
			str_value += *p;
			p++;
		}

		while (i < len && p[i] == ' ') i++;	// Skip spaces
		*/

		if (*p == L',') p++;

		//str_value.TrimRight();
		//str_value.TrimRight();

		//double value = atof(str_value);
		values.Add(value);

		while (*p && isspace(*p)) p++;	// Skip spaces
	}

	return values.GetSize();
}

void GetTranslateValues(const WCHAR* param_string, double& x, double& y)
{
	vector<double> values;
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

void GetScaleValues(const WCHAR* param_string, double& sx, double& sy)
{
	vector<double> values;
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

void GetRotateValues(const WCHAR* param_string, double &deg, double& cx, double& cy)
{
	vector<double> values;
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

void GetSkewValues(const WCHAR* param_string, double &deg)
{
	vector<double> values;
	int n = GetTransformValuesArray(param_string, values);

	if (n == 1)
	{
		deg = values[0];
	}
	else
		deg = 0;
}

void GetMatrixValues(const WCHAR* param_string, SVGMatrix* matrix)
{
	vector<double> values;
	int n = GetTransformValuesArray(param_string, values);

	if (n == 6)
	{
		ASSERT(0);
#if 0
		matrix->m_matrix[0][0] = values[0];
		matrix->m_matrix[0][1] = values[1];
		matrix->m_matrix[1][0] = values[2];
		matrix->m_matrix[1][1] = values[3];
		matrix->m_matrix[2][0] = values[4];
		matrix->m_matrix[2][1] = values[5];
#endif
		/*
		matrix->set_a(values[0]); matrix->set_b(values[1]);
		matrix->set_c(values[2]); matrix->set_d(values[3]);
		matrix->set_e(values[4]); matrix->set_f(values[5]);
		*/
	}
}

void SVGTransformList::ParseTransform(StringIn s)
{

	if (s.IsEmpty()) return;

	ASSERT(0);
#if 0

	const WCHAR* p = s->c_str();
	if (p == NULL) THROW(std::exception("null pointer"));

	while (*p)
	{
		while (*p && std::isspace(*p)) p++;	// Skip spaces

		// Get type
		const WCHAR* transformType = p;
		int transformTypeLength = 0;

		while (*p && std::isalpha(*p))
		{
			transformTypeLength++;
			p++;
		}

		while (*p && std::isspace(*p)) p++;	// Skip spaces

	// Get string inside ( )
		if (*p++ != L'(') break;	// Error

		const WCHAR* start = p;
		while (*p && *p != L')')
		{
			p++;
		}
		System::StringW* param_string = new System::StringW(string_copy(start, p - start));

		if (*p++ != L')') break; // Error
		while (*p && std::isspace(*p)) p++;	// Skip spaces

		SVGTransform* transform = NULL;

#if WIN32
		if (!_wcsnicmp(transformType, L"translate", transformTypeLength))
		{
			double x, y;
			GetTranslateValues(param_string->c_str(), x, y);

			transform = new SVGTransformMutable;
			transform->SetTranslate(x, y);
		}
		else if (!_wcsnicmp(transformType, L"rotate", transformTypeLength))
		{
			double deg, cx, cy;
			GetRotateValues(param_string->c_str(), deg, cx, cy);

			transform = new SVGTransformMutable;
			transform->SetRotate(deg, cx, cy);
		}
		else if (!_wcsnicmp(transformType, L"scale", transformTypeLength))
		{
			double sx, sy;
			GetScaleValues(param_string->c_str(), sx, sy);

			transform = new SVGTransformMutable;
			transform->SetScale(sx, sy);
		}
		else if (!_wcsnicmp(transformType, L"skewX", transformTypeLength))
		{
			double deg;
			GetSkewValues(param_string->c_str(), deg);

			transform = new SVGTransformMutable;
			transform->SetSkewX(deg);
		}
		else if (!_wcsnicmp(transformType, L"skewY", transformTypeLength))
		{
			double deg;
			GetSkewValues(param_string->c_str(), deg);

			transform = new SVGTransformMutable;
			transform->SetSkewY(deg);
		}
		else if (!_wcsnicmp(transformType, L"matrix", transformTypeLength))
		{
			transform = new SVGTransformMutable;

			transform->m_type = SVG_TRANSFORM_MATRIX;
			GetMatrixValues(param_string->c_str(), transform->m_matrix);
		}
#else
		ASSERT(0);
#endif

		if (transform != NULL)
		{
			transform->m_owner = this;
		//	transform->m_pListener = this;
			m_p->m_items.Add(transform);
		}

		if (*p == ',') p++;
		while (*p && std::isspace(*p)) p++;	// Skip spaces
	}
#endif
}

//////////////

String SVGTransformList::StringFromTransformList() const
{
	IO::StringWriter str;

	unsigned int numberOfItems = m_p->m_items.GetSize();

	for (size_t i = 0; i < numberOfItems; i++)
	{
		SVGTransform* transform = m_p->m_items[i];

		SVGTransformType type = transform->get_type();

		SVGMatrix* matrix = transform->get_matrix();

		double a = matrix->get_a();
		double b = matrix->get_b();
		double c = matrix->get_c();
		double d = matrix->get_d();
		double e = matrix->get_e();
		double f = matrix->get_f();

		if (i > 0) str << " ";

		switch (type)
		{
			case SVG_TRANSFORM_TRANSLATE:
			{
				str << "translate(" << e << "," << f << ")";
			}
			break;

			case SVG_TRANSFORM_SCALE:
			{
			//	swprintf(str2, OLESTR("scale(%g, %g)"), a, d);
			//	str += str2;
				str << "scale(" << a << "," << d << ")";
			}
			break;

			case SVG_TRANSFORM_ROTATE:
			{
				double angle = transform->get_angle();
			//	swprintf(str2, OLESTR("rotate(%g, %g, %g)"), angle, e, f);
			//	str += str2;
				str << "rotate(" << angle << "," << e << "," << f << ")";
			}
			break;

			case SVG_TRANSFORM_SKEWX:
			{
				double angle = transform->get_angle();
		//		swprintf(str2, OLESTR("skewX(%g)"), angle);
		//		str += str2;
				str << "skewX(" << angle << ")";
			}
			break;

			case SVG_TRANSFORM_SKEWY:
			{
				double angle = transform->get_angle();
			//	swprintf(str2, OLESTR("skewY(%g)"), angle);
			//	str += str2;
				str << "skewY(" << angle << ")";
			}
			break;

			case SVG_TRANSFORM_MATRIX:
			{
			//	swprintf(str2, OLESTR("matrix(%g %g %g %g %g %g)"), a, b, c, d, e, f);
			//	str += str2;
				str << "matrix(" << a << "," << b << "," << c << "," << d << "," << e << "," << f << ")";
			}
			break;

			default:
				ASSERT(0);
		}
	}

	return str.str();
}

////////

String SVGTransformList::getStringValue()
{
	return StringFromTransformList();
}

void SVGTransformList::setStringValue(StringIn str)
{
	RemoveAll();
	ParseTransform(str);
}

/*
SVGTransformList& SVGTransformList::operator = (const SVGTransformList& value)
{
	RemoveAll();

	for (int i = 0; i < value.m_items.GetSize(); i++)
	{
		SVGTransform* pTransform = new SVGTransform;

		pTransform->m_type = value.m_items[i]->m_type;
		pTransform->m_x = value.m_items[i]->m_x;
		pTransform->m_y = value.m_items[i]->m_y;
		pTransform->m_angle = value.m_items[i]->m_angle;
		pTransform->m_matrix->m_matrix = value.m_items[i]->m_matrix->m_matrix;

		pTransform->m_owner = this;
		pTransform->m_pListener = this;
		m_items.Add(pTransform);
	}

	return *this;
}

SVGTransformList& SVGTransformList::operator += (const SVGTransformList& value)
{
	ASSERT(0);
	return *this;
}
*/

void SVGTransformList::InterpolateValue(const SVGTransformList& a, const SVGTransformList& b, double t)
{
	TRACE("\n");
}

/*
void SVGTransformList::operator = (const SVGTransform& value)
{
	ASSERT(0);
}

void SVGTransformList::operator += (SVGTransform* value)
{
}
*/

//

SVGTransformListMutable::SVGTransformListMutable()
{
}

SVGTransformListMutable::SVGTransformListMutable(SVGTransformListData* p) : SVGTransformList(p)
{
}

///

SVGEXT String GetAsString(SVGTransformList* transformList)
{
	return transformList->getStringValue();
}

SVGEXT void SetAsString(SVGTransformList* transformList, StringIn str)
{
	transformList->setStringValue(str);
}

}
}
