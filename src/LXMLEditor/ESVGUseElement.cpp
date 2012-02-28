#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EXMLDocument.h"

#include "ESVGUseElement.h"

#if 0

STDMETHODIMP CESVGUseElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGUseElement> element = m_domElement;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		element->get_x(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dx);
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		element->get_y(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dy);
	}

	return S_OK;
}

STDMETHODIMP CESVGUseElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	CComQIPtr<ILSVGUseElement> element = m_domElement;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		element->get_x(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(x);
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		element->get_y(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(y);
	}

	// width
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		element->get_width(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(width);
	}

	// height
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		element->get_height(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(height);
	}

	return S_OK;
}

// IESVGDrawOutline
STDMETHODIMP CESVGUseElement::DrawOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Color& color, ILSVGMatrix* matrix)
{
	return S_OK;
}

#endif