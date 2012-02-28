#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGRectElement.h"

#if 0

#if 0
void DrawPathSegList(ILSVGPathSegList* seglist, HDC iDC, ILSVGMatrix* xform);

void CRectElement::DrawPathCurve(HDC hDC, ILSVGMatrix* addmatrix)
{
	CComQIPtr<ILSVGRectElement> rect = m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
	rect->getPathSegList(&seglist);

	CComQIPtr<ILSVGTransformable> transformable = m_domElement;

	CComQIPtr<ILSVGMatrix> matrix0;
	transformable->getScreenCTM(&matrix0);

	CComQIPtr<ILSVGMatrix> matrix;
	matrix0->multiply(addmatrix, &matrix);

	::DrawPathSegList(seglist, hDC, matrix);
}
#endif

STDMETHODIMP CESVGRectElement::Move(ISVGView* view, double dx, double dy)
{
	ATLASSERT(0);
#if 0
	CComQIPtr<ILSVGRectElement> rect = m_domElement;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILSVGElement> viewportElement;
	rect->get_viewportElement(&viewportElement);

// TODO, this can't be correct
	CComPtr<ILSVGRect> _rect;
	window->svgGetRBBox(viewportElement, &_rect);
	SVGRect viewBox = _rect;

	// x
	{
		CComPtr<ILSVGAnimatedLength> alength;
		rect->get_x(&alength);

		SVGLength length;
		alength->get_baseVal(&length);

		if (length.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double dx_pcnt = dx*100/viewBox.Width;

			double value;
			length->get_valueInSpecifiedUnits(&value);
			length->put_valueInSpecifiedUnits(value+dx_pcnt);
		}
		else
		{
			double value;
			length->get_value(&value);
			length->put_value(value + dx);
		}
	}

	// y
	{
		CComPtr<ILSVGAnimatedLength> alength;
		rect->get_y(&alength);

		SVGLength length;
		alength->get_baseVal(&length);

		if (length.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double dy_pcnt = dy*100/viewBox.Height;

			double value;
			length->get_valueInSpecifiedUnits(&value);
			length->put_valueInSpecifiedUnits(value+dy_pcnt);
		}
		else
		{
			double value;
			length->get_value(&value);
			length->put_value(value + dy);
		}
	}
#endif

	return S_OK;
}

STDMETHODIMP CESVGRectElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	ATLASSERT(0);
#if 0
	CComQIPtr<ILSVGRectElement> rect = m_domElement;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILSVGElement> viewportElement;
	rect->get_viewportElement(&viewportElement);

// TODO, this can't be correct
	CComPtr<ILSVGRect> _rect;
	window->svgGetRBBox(viewportElement, &_rect);
	SVGRect viewBox = _rect;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_x(&alength);

		SVGLength length;
		alength->get_baseVal(&length);

		if (length.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double x_pcnt = x*100/viewBox.Width;
			length->set_valueInSpecifiedUnits(x_pcnt);
		}
		else
		{
			length->put_value(x);
		}
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_y(&alength);

		SVGLength length;
		alength->get_baseVal(&length);

		if (length.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double y_pcnt = y*100/viewBox.Height;
			length->set_valueInSpecifiedUnits(y_pcnt);
		}
		else
		{
			length->put_value(y);
		}
	}

	// width
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_width(&alength);

		SVGLength length;
		alength->get_baseVal(&length);

		if (length.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double width_pcnt = width*100/viewBox.Width;
			length->set_valueInSpecifiedUnits(width_pcnt);
		}
		else
		{
			length->put_value(width);
		}
	}

	// height
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_height(&alength);

		SVGLength length;
		alength->get_baseVal(&length);

		if (length.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double height_pcnt = height*100/viewBox.Height;
			length->set_valueInSpecifiedUnits(height_pcnt);
		}
		else
		{
			length->put_value(height);
		}
	}
#endif

	return S_OK;
}

// IESVGRectElement
STDMETHODIMP CESVGRectElement::SetRectShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height)
{
	CComQIPtr<ILSVGRectElement> rect = m_domElement;

	// x
	{
		CComPtr<ILSVGAnimatedLength> alength;
		rect->get_x(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(x);
	}

	// y
	{
		CComPtr<ILSVGAnimatedLength> alength;
		rect->get_y(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(y);
	}

	// width
	{
		CComPtr<ILSVGAnimatedLength> alength;
		rect->get_width(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(width);
	}

	// height
	{
		CComPtr<ILSVGAnimatedLength> alength;
		rect->get_height(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(height);
	}

	return S_OK;
}

STDMETHODIMP CESVGRectElement::SetRoundRectShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height, /*[in]*/ double rx, /*[in]*/ double ry)
{
	CComQIPtr<ILSVGRectElement> rect = m_domElement;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_x(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(x);
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_y(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(y);
	}

	// width
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_width(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(width);
	}

	// height
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_height(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(height);
	}

	// rx
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_rx(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(rx);
	}

	// ry
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_ry(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(ry);
	}

	return S_OK;
}

// IESVGSimpleShapeElement
STDMETHODIMP CESVGRectElement::DrawPathSegList(/*[in]*/ ILSVGPathElement* pathElement, /*[in]*/ ILSVGPathSegList* seglist)
{
	CComQIPtr<ILSVGRectElement> rect = m_domElement;

	double x, y, width, height, rx, ry;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_x(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&x);
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_y(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&y);
	}

	// width
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_width(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&width);
	}

	// height
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_height(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&height);
	}

	// rx
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_rx(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&rx);
	}

	// ry
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_ry(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&ry);
	}

	seglist->AddRoundRect(x, y, width, height, rx, ry);

	return S_OK;
}

#endif