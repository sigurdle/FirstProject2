#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGImageElement.h"

#if 0

STDMETHODIMP CESVGImageElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGImageElement> image = m_domElement;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_x(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dx);
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_y(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dy);
	}

	return S_OK;
}

STDMETHODIMP CESVGImageElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	CComQIPtr<ILSVGImageElement> image = m_domElement;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_x(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(x);
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_y(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(y);
	}

	// width
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_width(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(width);
	}

	// height
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_height(&alength);
		CComPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(height);
	}

	return S_OK;
}

#endif