#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGLineElement.h"

#if 0
#if 0
void DrawPathSegList(ILSVGPathSegList* seglist, HDC iDC, ILSVGMatrix* xform);

void CLineElement::DrawPathCurve(HDC hDC, ILSVGMatrix* addmatrix)
{
	CComQIPtr<ILSVGLineElement> line = m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
	line->getPathSegList(&seglist);

	CComQIPtr<ILSVGTransformable> transformable = m_domElement;

	CComQIPtr<ILSVGMatrix> matrix0;
	transformable->getScreenCTM(&matrix0);

	CComQIPtr<ILSVGMatrix> matrix;
	matrix0->multiply(addmatrix, &matrix);

	::DrawPathSegList(seglist, hDC, matrix);
}
#endif

STDMETHODIMP CESVGLineElement::SetShape(/*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
{
	CComQIPtr<ILSVGLineElement> line = m_domElement;

	// x1
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x1(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(x1);
	}

	// y1
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y1(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(y1);
	}

	// x2
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x2(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(x2);
	}

	// y2
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y2(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(y2);
	}

	return S_OK;
}

STDMETHODIMP CESVGLineElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGLineElement> line = m_domElement;

	// x1
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x1(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dx);
	}

	// y1
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y1(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dy);
	}

	// x2
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x2(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dx);
	}

	// y2
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y2(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dy);
	}

	return S_OK;
}

STDMETHODIMP CESVGLineElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	CComQIPtr<ILSVGLineElement> line = m_domElement;

	// x1
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x1(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(x);
	}

	// y1
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y1(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(y);
	}

	// x2
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x2(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(x+width);
	}

	// y2
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y2(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(y+height);
	}

	return S_OK;
}

// IESVGDrawOutline
STDMETHODIMP CESVGLineElement::DrawOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	Gdiplus::Pen pen(color);

	CComQIPtr<ILSVGLineElement> line = m_domElement;

	double x1, y1, x2, y2;

	// x1
	CComPtr<ILSVGLength> x1length;
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x1(&alength);
		alength->get_baseVal(&x1length);
	}
	x1length->get_value(&x1);

	// y1
	CComPtr<ILSVGLength> y1length;
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y1(&alength);
		alength->get_baseVal(&y1length);
	}
	y1length->get_value(&y1);

	// x2
	CComPtr<ILSVGLength> x2length;
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x2(&alength);
		alength->get_baseVal(&x2length);
	}
	x2length->get_value(&x2);

	// y2
	CComPtr<ILSVGLength> y2length;
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y2(&alength);
		alength->get_baseVal(&y2length);
	}
	y2length->get_value(&y2);

	SVGPoint start = SVGPoint(x1,y1).matrixTransform(matrix);
	SVGPoint end = SVGPoint(x2,y2).matrixTransform(matrix);

	pGraphics->DrawLine(&pen, (float)start.X, (float)start.Y, (float)end.X, (float)end.Y);

	return S_OK;
}

// IESVGSimpleShapeElement
STDMETHODIMP CESVGLineElement::DrawPathSegList(/*[in]*/ ILSVGPathElement* pathElement, /*[in]*/ ILSVGPathSegList* seglist)
{
	CComQIPtr<ILSVGLineElement> line = m_domElement;

	double x1, y1, x2, y2;

	// x1
	CComPtr<ILSVGLength> x1length;
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x1(&alength);
		alength->get_baseVal(&x1length);
	}
	x1length->get_value(&x1);

	// y1
	CComPtr<ILSVGLength> y1length;
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y1(&alength);
		alength->get_baseVal(&y1length);
	}
	y1length->get_value(&y1);

	// x2
	CComPtr<ILSVGLength> x2length;
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_x2(&alength);
		alength->get_baseVal(&x2length);
	}
	x2length->get_value(&x2);

	// y2
	CComPtr<ILSVGLength> y2length;
	{
		CComPtr<ILSVGAnimatedLength> alength;
		line->get_y2(&alength);
		alength->get_baseVal(&y2length);
	}
	y2length->get_value(&y2);

	seglist->AddLine(x1, y1, x2, y2);

	return S_OK;
}

#endif