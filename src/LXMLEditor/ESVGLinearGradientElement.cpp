#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGLinearGradientElement.h"

#if 0

STDMETHODIMP CESVGLinearGradientElement::SetShape(/*[in]*/ double x1, /*[in]*/ double y1, /*[in]*/ double x2, /*[in]*/ double y2)
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

STDMETHODIMP CESVGLinearGradientElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGLinearGradientElement> line = m_domElement;

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

STDMETHODIMP CESVGLinearGradientElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	CComQIPtr<ILSVGLinearGradientElement> line = m_domElement;

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
STDMETHODIMP CESVGLinearGradientElement::DrawOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	Gdiplus::Pen pen(color);

	CComQIPtr<ILSVGLinearGradientElement> line = m_domElement;

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

#if 0
// IESVGSimpleShapeElement
STDMETHODIMP CESVGLinearGradientElement::DrawPathSegList(/*[in]*/ ILSVGPathElement* pathElement, /*[in]*/ ILSVGPathSegList* seglist)
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

#include "EXMLViewGroup.h"

STDMETHODIMP CESelectedSVGLinearGradientElement::GetScreenCTM(ISVGView* view, ILSVGMatrix* *pVal)
{
	CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroup);

	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

	CComQIPtr<ILSVGLinearGradientElement> linearGradient = domElement;

	if (TRUE || pViewGroup->m_activeReferenceElement)
	{
		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);
		
		CComPtr<ILDOMElement> domElement;
		m_pElement->get_domElement(&domElement);

		CComPtr<ILDOMDocument> document;
		pViewGroup->m_pDocument->get_DOMDocument(&document);

		CComPtr<ILSVGSVGElement> svgsvgElement;
		document->get_documentElement((ILDOMElement**)&svgsvgElement);

		CComPtr<ILSVGAnimatedTransformList> alist;
		linearGradient->get_gradientTransform(&alist);

		CComPtr<ILSVGTransformList> base;
		alist->get_baseVal(&base);

		CComPtr<ILSVGMatrix> matrix;
		//svgsvgElement->createSVGMatrix(&matrix);
		base->consolidateToMatrix(&matrix);

		(*pVal = matrix)->AddRef();

		//CComQIPtr<ILSVGLinearGradientElement> linearGradientElemetn = domElement;

		//CComPtr<ILSVGTransform

		//return window->svgGetScreenCTM2(CComQIPtr<ILSVGElement>(domElement), pVal);
	}
	else
	{
		*pVal = NULL;
	}

	return S_OK;
}

STDMETHODIMP CESelectedSVGLinearGradientElement::GetRBBox(/*[in]*/ ISVGView* view, /*[out,retval]*/ ILSVGRect* *pVal)
{
	CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroup);

	CComPtr<ILDOMElement> domElement;
	m_pElement->get_domElement(&domElement);

	CComQIPtr<ILSVGLinearGradientElement> line = domElement;

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

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	CComPtr<ILDOMDocument> document;
	pViewGroup->m_pDocument->get_DOMDocument(&document);

	CComPtr<ILSVGSVGElement> svgsvgElement;
	document->get_documentElement((ILDOMElement**)&svgsvgElement);

	CComPtr<ILSVGRect> rect;
	svgsvgElement->createSVGRect(&rect);

	rect->put_x(x1);
	rect->put_y(y1);
	rect->put_width(x2-x1);
	rect->put_height(y2-y1);

	(*pVal = rect)->AddRef();

	return S_OK;
}

// IESVGDrawOutline
STDMETHODIMP CESelectedSVGLinearGradientElement::DrawOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	return ((CESVGLinearGradientElement*)m_pElement)->DrawOutline(pGraphics, color, matrix);
}

#endif