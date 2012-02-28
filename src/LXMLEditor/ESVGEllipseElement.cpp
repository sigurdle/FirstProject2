#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#if 0

//#include "WebXMLDocument.h"	// TODO remove

#include "ESVGEllipseElement.h"

#include "..\LXUI\Bezier.h"

//void DrawPathSegList(ILSVGPathSegList* seglist, HDC iDC, ILSVGMatrix* xform);
//void DrawPathSegList(ILSVGPathSegList* seglist, Gdiplus::GraphicsPath* path, ILSVGMatrix* matrix);

#if 0
void CEllipseElement::DrawPathCurve(Gdiplus::Graphics* pGraphics, ILSVGMatrix* addmatrix)
{
	CComQIPtr<ILSVGEllipseElement> ellipse = m_domElement;

	CComQIPtr<ILSVGPathSegList> seglist;
	ellipse->getPathSegList(&seglist);

	/*
	CComQIPtr<ILSVGTransformable> transformable = m_domElement;

	CComQIPtr<ILSVGMatrix> matrix0;
	transformable->getScreenCTM(&matrix0);

	CComQIPtr<ILSVGMatrix> matrix;
	matrix0->multiply(addmatrix, &matrix);
	*/

	CComPtr<ILSVGMatrix> matrix;
	matrix.CoCreateInstance(CLSID_LSVGMatrix);

	Gdiplus::GraphicsPath path;
	::DrawPathSegList(seglist, &path, matrix);

	pGraphics->DrawPath(&Gdiplus::Pen(Gdiplus::Color(80, 80, 250)), &path);
}
#endif

STDMETHODIMP CESVGEllipseElement::Move(ISVGView* view, double dx, double dy)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGEllipseElement> ellipse = m_domElement;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILSVGElement> viewportElement;
	ellipse->get_viewportElement(&viewportElement);

// TODO, this can't be correct
	CComPtr<ILSVGRect> _rect;
	window->svgGetRBBox(viewportElement, &_rect);
	SVGRect viewBox = _rect;

	// cx
	{
		CComPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cx(&alength);

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
		ellipse->get_cy(&alength);

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

STDMETHODIMP CESVGEllipseElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGEllipseElement> ellipse = m_domElement;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILSVGElement> viewportElement;
	ellipse->get_viewportElement(&viewportElement);

// TODO, this can't be correct
	CComPtr<ILSVGRect> _rect;
	window->svgGetRBBox(viewportElement, &_rect);
	SVGRect viewBox = _rect;

	double cx = x+width/2;
	double cy = y+height/2;
	double rx = width/2;
	double ry = height/2;

	// cx
	{
		CComPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cx(&alength);

		SVGLength cxlength;
		alength->get_baseVal(&cxlength);

		if (cxlength.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double cx_pcnt = cx*100/viewBox.Width;
			cxlength->put_valueInSpecifiedUnits(cx_pcnt);
		}
		else
		{
			cxlength->put_value(cx);
		}
	}

	// cy
	{
		CComPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cy(&alength);

		SVGLength cylength;
		alength->get_baseVal(&cylength);

		if (cylength.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double cy_pcnt = cy*100/viewBox.Height;
			cylength->put_valueInSpecifiedUnits(cy_pcnt);
		}
		else
		{
			cylength->put_value(cy);
		}
	}

	// rx
	{
		CComPtr<ILSVGAnimatedLength> alength;
		ellipse->get_rx(&alength);

		SVGLength rxlength;
		alength->get_baseVal(&rxlength);

		if (rxlength.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double rx_pcnt = rx*100/viewBox.Width;
			rxlength->put_valueInSpecifiedUnits(rx_pcnt);
		}
		else
		{
			rxlength->put_value(rx);
		}
	}

	// ry
	{
		CComPtr<ILSVGAnimatedLength> alength;
		ellipse->get_ry(&alength);

		SVGLength rylength;
		alength->get_baseVal(&rylength);

		if (rylength.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double ry_pcnt = ry*100/viewBox.Height;
			rylength->put_valueInSpecifiedUnits(ry_pcnt);
		}
		else
		{
			rylength->put_value(ry);
		}
	}
#endif
	return S_OK;
}

#if 0
//
void CEllipseElement::Scale(double ox, double oy, double sx, double sy)
{
	CComQIPtr<ILSVGEllipseElement> ellipse = m_domElement;

	double cx;
	double cy;
	double rx;
	double ry;

	// cx
	CComQIPtr<ILSVGLength> cxlength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cx(&alength);
		alength->get_baseVal(&cxlength);
	}
	cxlength->get_value(&cx);

	// cy
	CComQIPtr<ILSVGLength> cylength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cy(&alength);
		alength->get_baseVal(&cylength);
	}
	cylength->get_value(&cy);

	// rx
	CComQIPtr<ILSVGLength> rxlength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_rx(&alength);
		alength->get_baseVal(&rxlength);
	}
	rxlength->get_value(&rx);

	// ry
	CComQIPtr<ILSVGLength> rylength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_ry(&alength);
		alength->get_baseVal(&rylength);
	}
	rylength->get_value(&ry);

	double x1 = cx-rx;
	double y1 = cy-ry;
	double x2 = cx+rx;
	double y2 = cy+ry;

	x1 = (x1-ox)*sx+ox;
	y1 = (y1-oy)*sy+oy;
	x2 = (x2-ox)*sx+ox;
	y2 = (y2-oy)*sy+oy;

	cxlength->put_value(x1 + (x2-x1)/2);
	cylength->put_value(y1 + (y2-y1)/2);
	rxlength->put_value((x2-x1)/2);
	rylength->put_value((y2-y1)/2);

	SVGLib::ISVGTransformPtr transform = GetMatrixTransform();

//	if (transform == NULL)
	{
		SVGLib::ISVGEllipseElementPtr ellipse = m_domElement;
		
		float x1 = ellipse->cx->baseVal->value-ellipse->rx->baseVal->value;
		float y1 = ellipse->cy->baseVal->value-ellipse->ry->baseVal->value;
		float x2 = ellipse->cx->baseVal->value+ellipse->rx->baseVal->value;
		float y2 = ellipse->cy->baseVal->value+ellipse->ry->baseVal->value;

		x1 = (x1-cx)*sx+cx;
		y1 = (y1-cy)*sy+cy;
		x2 = (x2-cx)*sx+cx;
		y2 = (y2-cy)*sy+cy;

		ellipse->cx->baseVal->value = x1 + (x2-x1)/2;
		ellipse->cy->baseVal->value = y1 + (y2-y1)/2;
		ellipse->rx->baseVal->value = (x2-x1)/2;
		ellipse->ry->baseVal->value = (y2-y1)/2;
	}
/*	else
	{
		CElement::Scale(cx, cy, sx, sy);
	}
	*/
}
#endif

STDMETHODIMP CESVGEllipseElement::SetShape(double cx, double cy, double rx, double ry)
{
	CComQIPtr<ILSVGEllipseElement> ellipse = m_domElement;

	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cx(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(cx);
	}

	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cy(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(cy);
	}

	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_rx(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(rx);
	}

	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_ry(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(ry);
	}

	return S_OK;
}

// IESVGDrawOutline
STDMETHODIMP CESVGEllipseElement::DrawOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	CComQIPtr<ILSVGEllipseElement> ellipse = m_domElement;

	double cx;
	double cy;
	double rx;
	double ry;

	// cx
	CComQIPtr<ILSVGLength> cxlength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cx(&alength);
		alength->get_baseVal(&cxlength);
	}
	cxlength->get_value(&cx);

	// cy
	CComQIPtr<ILSVGLength> cylength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cy(&alength);
		alength->get_baseVal(&cylength);
	}
	cylength->get_value(&cy);

	// rx
	CComQIPtr<ILSVGLength> rxlength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_rx(&alength);
		alength->get_baseVal(&rxlength);
	}
	rxlength->get_value(&rx);

	// ry
	CComQIPtr<ILSVGLength> rylength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_ry(&alength);
		alength->get_baseVal(&rylength);
	}
	rylength->get_value(&ry);

	SVGPoint bpoints[13];
	SetPointsEllipse(cx-rx, cy-ry, cx+rx, cy+ry, bpoints);

	Gdiplus::PointF xpts[13];

	for (int i = 0; i < 13; i++)
	{
		xpts[i] = bpoints[i].matrixTransform(matrix);
	}

	pGraphics->DrawBeziers(&Gdiplus::Pen(color), xpts, 13);

	return S_OK;
}

// IESVGSimpleShapeElement
STDMETHODIMP CESVGEllipseElement::DrawPathSegList(/*[in]*/ ILSVGPathElement* pathElement, /*[in]*/ ILSVGPathSegList* seglist)
{
	ASSERT(seglist != NULL);
	if (seglist == NULL) return E_INVALIDARG;

	CComQIPtr<ILSVGEllipseElement> ellipse = m_domElement;

	double cx;
	double cy;
	double rx;
	double ry;

	// cx
	CComQIPtr<ILSVGLength> cxlength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cx(&alength);
		alength->get_baseVal(&cxlength);
	}
	cxlength->get_value(&cx);

	// cy
	CComQIPtr<ILSVGLength> cylength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_cy(&alength);
		alength->get_baseVal(&cylength);
	}
	cylength->get_value(&cy);

	// rx
	CComQIPtr<ILSVGLength> rxlength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_rx(&alength);
		alength->get_baseVal(&rxlength);
	}
	rxlength->get_value(&rx);

	// ry
	CComQIPtr<ILSVGLength> rylength;
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		ellipse->get_ry(&alength);
		alength->get_baseVal(&rylength);
	}
	rylength->get_value(&ry);

	seglist->AddEllipse(cx, cy, rx, ry);

	return S_OK;
}

#endif