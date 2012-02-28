#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDMatrix.h"

/////////////////////////
// CPDMatrix

STDMETHODIMP CPDMatrix::get_a(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_matrix[0][0];
	return S_OK;
}

STDMETHODIMP CPDMatrix::put_a(double newVal)
{
	m_matrix[0][0] = newVal;
	return S_OK;
}

STDMETHODIMP CPDMatrix::get_b(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_matrix[0][1];
	return S_OK;
}

STDMETHODIMP CPDMatrix::put_b(double newVal)
{
	m_matrix[0][1] = newVal;
	return S_OK;
}

STDMETHODIMP CPDMatrix::get_c(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_matrix[1][0];
	return S_OK;
}

STDMETHODIMP CPDMatrix::put_c(double newVal)
{
	m_matrix[1][0] = newVal;
	return S_OK;
}

STDMETHODIMP CPDMatrix::get_d(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_matrix[1][1];
	return S_OK;
}

STDMETHODIMP CPDMatrix::put_d(double newVal)
{
	m_matrix[1][1] = newVal;
	return S_OK;
}

STDMETHODIMP CPDMatrix::get_e(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_matrix[2][0];
	return S_OK;
}

STDMETHODIMP CPDMatrix::put_e(double newVal)
{
	m_matrix[2][0] = newVal;
	return S_OK;
}

STDMETHODIMP CPDMatrix::get_f(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_matrix[2][1];
	return S_OK;
}

STDMETHODIMP CPDMatrix::put_f(double newVal)
{
	m_matrix[2][1] = newVal;
	return S_OK;
}

STDMETHODIMP CPDMatrix::copyFrom(IPDMatrix *from)
{
	if (from == NULL) return E_INVALIDARG;

	CPDMatrix* pFrom = static_cast<CPDMatrix*>(from);
	/*
	from->get_a(&m_matrix[0][0]);
	from->get_b(&m_matrix[0][1]);
	from->get_c(&m_matrix[1][0]);
	from->get_d(&m_matrix[1][1]);
	from->get_e(&m_matrix[2][0]);
	from->get_f(&m_matrix[2][1]);
	m_matrix[0][2] = pFrom->m_matrix[0][2];
	m_matrix[1][2] = pFrom->m_matrix[1][2];
	m_matrix[2][2] = pFrom->m_matrix[2][2];
	*/
	m_matrix = pFrom->m_matrix;

// TODO: fire event

	return S_OK;
}

STDMETHODIMP CPDMatrix::translate(double dx, double dy, IPDMatrix **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDMatrix>* result;
	CComObject<CPDMatrix>::CreateInstance(&result);
	if (result)
	{
		result->m_matrix = m_matrix * gmMatrix3::translate(dx, dy);
	//	result->m_matrix = gmMatrix3::translate(dx, dy) * m_matrix;

		*pVal = result;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDMatrix::rotate(double angle, IPDMatrix **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDMatrix>* result;
	CComObject<CPDMatrix>::CreateInstance(&result);
	if (result)
	{
		result->m_matrix = m_matrix * gmMatrix3::rotate(angle);
	//	result->m_matrix = gmMatrix3::rotate(angle) * m_matrix;

		*pVal = result;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDMatrix::skewX(double angle, IPDMatrix **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDMatrix>* result;
	CComObject<CPDMatrix>::CreateInstance(&result);
	if (result)
	{
		result->m_matrix = m_matrix * gmMatrix3::skewX(angle);
	//	result->m_matrix = gmMatrix3::skewX(angle) * m_matrix;

		*pVal = result;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDMatrix::skewY(double angle, IPDMatrix **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDMatrix>* result;
	CComObject<CPDMatrix>::CreateInstance(&result);
	if (result)
	{
		result->m_matrix = m_matrix * gmMatrix3::skewY(angle);
	//	result->m_matrix = gmMatrix3::skewY(angle) * m_matrix;

		*pVal = result;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDMatrix::scaleNonUniform(double sx, double sy, IPDMatrix **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDMatrix>* result;
	CComObject<CPDMatrix>::CreateInstance(&result);
	if (result)
	{
		result->m_matrix = m_matrix * gmMatrix3::scale(sx, sy);
	//	result->m_matrix = gmMatrix3::scale(sx, sy) * m_matrix;

		*pVal = result;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDMatrix::multiply(IPDMatrix *matrix, IPDMatrix **pVal)
{
	if (matrix == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDMatrix>* pOther = static_cast<CComObject<CPDMatrix>*>(matrix);
	
	CComObject<CPDMatrix>* result;
	CComObject<CPDMatrix>::CreateInstance(&result);
	if (result)
	{
		result->m_matrix = m_matrix * pOther->m_matrix;
	//	result->m_matrix = pOther->m_matrix * m_matrix;
		*pVal = result;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDMatrix::inverse(IPDMatrix **pVal)
{
	CComObject<CPDMatrix>* result;
	CComObject<CPDMatrix>::CreateInstance(&result);
	if (result)
	{
		result->m_matrix = m_matrix.inverse();

		gmMatrix3 id = (result->m_matrix * m_matrix);

		*pVal = result;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

//	ATLASSERT(result->m_matrix[0][2] == 0);
//	ATLASSERT(result->m_matrix[1][2] == 0);
//	ATLASSERT(result->m_matrix[2][2] == 1);

	return S_OK;
}

STDMETHODIMP CPDMatrix::transpose(IPDMatrix **pVal)
{
	CComObject<CPDMatrix>* result;
	CComObject<CPDMatrix>::CreateInstance(&result);
	if (result)
	{
		result->m_matrix = m_matrix.transpose();
		*pVal = result;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDMatrix::setTranslate(double dx, double dy)
{
	m_matrix = gmMatrix3::translate(dx, dy);
	return S_OK;
}

STDMETHODIMP CPDMatrix::setScaleNonUniform(double sx, double sy)
{
	m_matrix = gmMatrix3::scale(sx, sy);
	return S_OK;
}

STDMETHODIMP CPDMatrix::setRotate(double angle)
{
	m_matrix = gmMatrix3::rotate(angle);
	return S_OK;
}

STDMETHODIMP CPDMatrix::transformBezierPoint(BezierPoint *point, BezierPoint *pVal)
{
	if (pVal == NULL) return E_POINTER;

	gmVector2 xy = m_matrix.transform(gmVector2(point->x, point->y));
	gmVector2 xy1 = m_matrix.transform(gmVector2(point->x1, point->y1));
	gmVector2 xy2 = m_matrix.transform(gmVector2(point->x2, point->y2));

	pVal->x = xy[0];
	pVal->y = xy[1];
	pVal->x1 = xy1[0];
	pVal->y1 = xy1[1];
	pVal->x2 = xy2[0];
	pVal->y2 = xy2[1];

	return S_OK;
}

STDMETHODIMP CPDMatrix::transformPoint(PointD *point, PointD *pVal)
{
	if (pVal == NULL) return E_POINTER;

	gmVector2 xy = m_matrix.transform(gmVector2(point->x, point->y));

	pVal->x = xy[0];
	pVal->y = xy[1];

	return S_OK;
}

extern double GetLineAngle(float x1, float y1, float x2, float y2);

STDMETHODIMP CPDMatrix::getRotation(double *pVal)
{
	gmVector2 v0 = m_matrix.transform(gmVector2(0, 0));
	gmVector2 v1 = m_matrix.transform(gmVector2(10, 0));

	*pVal = GetLineAngle(v0[0], v0[1], v1[0], v1[1]) * (180/M_PI);

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDMatrix::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	WCHAR str[256];
	swprintf(str, L"%g %g %g %g %g %g", m_matrix[0][0], m_matrix[0][1], m_matrix[1][0], m_matrix[1][1], m_matrix[2][0], m_matrix[2][1]);
	node->putData(_variant_t(_bstr_t(str)));

	return S_OK;
}

STDMETHODIMP CPDMatrix::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	return S_OK;
}

#if 0
STDMETHODIMP CPDMatrix::saveAsXML(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node, BOOL saveId)
{
	CComQIPtr<IDOMAttr> attr = node;
	if (attr)
	{
		WCHAR str[256];
		swprintf(str, L"%g %g %g %g %g %g", m_matrix[0][0], m_matrix[0][1], m_matrix[1][0], m_matrix[1][1], m_matrix[2][0], m_matrix[2][1]);
		attr->put_value(str);

		return S_OK;
	}
	else
		return E_FAIL;
}

STDMETHODIMP CPDMatrix::loadXML(/*[in]*/ IDOMNode* node)
{
	CComQIPtr<IDOMAttr> attr = node;
	if (attr)
	{
		BSTR bstr;
		attr->get_value(&bstr);

		double a, b, c, d, e, f;
		int n = swscanf(_bstr_t(bstr, false), L"%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f);
		if (n != 6) return E_FAIL;

		m_matrix[0][0] = a;
		m_matrix[0][1] = b;
		m_matrix[1][0] = c;
		m_matrix[1][1] = d;
		m_matrix[2][0] = e;
		m_matrix[2][1] = f;

		return S_OK;
	}
	else
		return E_FAIL;
}
#endif

STDMETHODIMP CPDMatrix::GetClassID(CLSID *pClassID)
{
	ATLASSERT(0);
	// TODO: Add your implementation code here

	return S_OK;
}
