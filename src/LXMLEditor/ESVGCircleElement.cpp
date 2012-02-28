#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EXMLDocument.h"	// TODO remove

#include "ESVGCircleElement.h"

#if 0

#if 0
void DrawPathSegList(ILSVGPathSegList* seglist, HDC iDC, ILSVGMatrix* xform);

void CCircleElement::DrawPathCurve(HDC hDC, ILSVGMatrix* addmatrix)
{
	CComQIPtr<ILSVGCircleElement> circle = m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
	circle->getPathSegList(&seglist);

	CComQIPtr<ILSVGTransformable> transformable = m_domElement;

	CComQIPtr<ILSVGMatrix> matrix0;
	transformable->getScreenCTM(&matrix0);

	CComQIPtr<ILSVGMatrix> matrix;
	matrix0->multiply(addmatrix, &matrix);

//	RECT xrect = {0,0,0,0};
	::DrawPathSegList(seglist, hDC, matrix);
}
#endif

STDMETHODIMP CESVGCircleElement::SetShape(/*[in]*/ double cx, /*[in]*/ double cy, /*[in]*/ double r)
{
	CComQIPtr<ILSVGCircleElement> circle = m_domElement;

	// cx
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		circle->get_cx(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(cx);
	}

	// cy
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		circle->get_cy(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(cy);
	}

	// r
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		circle->get_r(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(r);
	}

	return S_OK;
}

STDMETHODIMP CESVGCircleElement::Move(ISVGView* view, double dx, double dy)
{
	ATLASSERT(0);
#if 0
	CComQIPtr<ILSVGCircleElement> circle = m_domElement;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILSVGElement> viewportElement;
	circle->get_viewportElement(&viewportElement);

// TODO, this can't be correct
	CComPtr<ILSVGRect> _rect;
	window->svgGetRBBox(viewportElement, &_rect);
	SVGRect viewBox = _rect;

	// cx
	{
		CComPtr<ILSVGAnimatedLength> alength;
		circle->get_cx(&alength);

		SVGLength cxlength;
		alength->get_baseVal(&cxlength);

		if (cxlength.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double dx_pcnt = dx*100/viewBox.Width;

			double value;
			cxlength->get_valueInSpecifiedUnits(&value);
			cxlength->put_valueInSpecifiedUnits(value+dx_pcnt);
		}
		else
		{
			double value;
			cxlength->get_value(&value);
			cxlength->put_value(value + dx);
		}
	}

	// cy
	{
		CComPtr<ILSVGAnimatedLength> alength;
		circle->get_cy(&alength);

		SVGLength cylength;
		alength->get_baseVal(&cylength);

		if (cylength.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double dy_pcnt = dy*100/viewBox.Height;

			double value;
			cylength->get_valueInSpecifiedUnits(&value);
			cylength->put_valueInSpecifiedUnits(value+dy_pcnt);
		}
		else
		{
			double value;
			cylength->get_value(&value);
			cylength->put_value(value + dy);
		}
	}
#endif

	return S_OK;
}

#if 0
void CCircleElement::Scale(double cx, double cy, double sx, double sy)
{
/*
	SVGLib::ISVGCircleElementPtr circle = pActiveElement->m_domElement;
	
	circle->cx->baseVal->value = circle->cx->baseVal->value + dx;
	circle->cy->baseVal->value = circle->cy->baseVal->value + dy;
*/
}
#endif

// IESVGSimpleShapeElement
STDMETHODIMP CESVGCircleElement::DrawPathSegList(/*[in]*/ ILSVGPathElement* pathElement, /*[in]*/ ILSVGPathSegList* seglist)
{
	CComQIPtr<ILSVGCircleElement> circle = m_domElement;

	double cx, cy, r;

	// cx
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		circle->get_cx(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&cx);
	}

	// cy
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		circle->get_cy(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&cy);
	}

	// r
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		circle->get_r(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->get_value(&r);
	}

	seglist->AddEllipse(cx, cy, r, r);

	return S_OK;
}

#endif