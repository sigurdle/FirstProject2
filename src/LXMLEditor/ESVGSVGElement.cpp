#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGSVGElement.h"

#if 0

STDMETHODIMP CESVGSVGElement::SetShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height)
{
	LSVG::CLSVGRectElement* element = dynamic_cast<LSVG::CLSVGRectElement*>(m_domElement);

	// x
	{
		LSVG::CLSVGAnimatedLength* alength = element->get_x(&alength);
		LSVG::CLSVGLength* length = alength->get_baseVal(&length);
		length->put_value(x);
	}

	// y
	{
		CComPtr<ILSVGAnimatedLength> alength;
		element->get_y(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(y);
	}

	// width
	{
		CComPtr<ILSVGAnimatedLength> alength;
		element->get_width(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(width);
	}

	// height
	{
		CComPtr<ILSVGAnimatedLength> alength;
		element->get_height(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);
		length->put_value(height);
	}

	return S_OK;
}

STDMETHODIMP CESVGSVGElement::Move(ISVGView* view, double dx, double dy)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGSVGElement> rect = m_domElement;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	SVGRect viewBox;

	CComPtr<ILSVGElement> viewportElement;
	rect->get_viewportElement(&viewportElement);
	if (viewportElement)
	{
	// TODO, this can't be correct
		CComPtr<ILSVGRect> _rect;
		window->svgGetRBBox(viewportElement, &_rect);
		viewBox = _rect;
	}
	else
	{
		long innerWidth;
		long innerHeight;
		window->get_innerWidth(&innerWidth);
		window->get_innerHeight(&innerHeight);

		viewBox = SVGRect(0, 0, innerWidth, innerHeight);
	}

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

STDMETHODIMP CESVGSVGElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGSVGElement> rect = m_domElement;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	SVGRect viewBox;

	CComPtr<ILSVGElement> viewportElement;
	rect->get_viewportElement(&viewportElement);
	if (viewportElement)
	{
	// TODO, this can't be correct
		CComPtr<ILSVGRect> _rect;
		window->svgGetRBBox(viewportElement, &_rect);
		viewBox = _rect;
	}
	else
	{
		long innerWidth;
		long innerHeight;
		window->get_innerWidth(&innerWidth);
		window->get_innerHeight(&innerHeight);

		viewBox = SVGRect(0, 0, innerWidth, innerHeight);
	}

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		rect->get_x(&alength);

		SVGLength length;
		alength->get_baseVal(&length);

		if (length.GetUnitType() == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double x_pcnt = x*100/viewBox.Width;
			length->put_valueInSpecifiedUnits(x_pcnt);
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
			length->put_valueInSpecifiedUnits(y_pcnt);
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
			length->put_valueInSpecifiedUnits(width_pcnt);
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
			length->put_valueInSpecifiedUnits(height_pcnt);
		}
		else
		{
			length->put_value(height);
		}
	}
#endif

	return S_OK;
}

#endif