#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGVideoElement.h"

#if 0

//void DrawPathSegList(ILSVGPathSegList* seglist, HDC iDC, ILSVGMatrix* xform);

STDMETHODIMP CESVGVideoElement::SetShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height)
{
	CComQIPtr<ILSVGVideoElement> rect = m_domElement;

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

STDMETHODIMP CESVGVideoElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGVideoElement> image = m_domElement;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_x(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dx);
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_y(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		double value;
		length->get_value(&value);
		length->put_value(value + dy);
	}

	return S_OK;
}

STDMETHODIMP CESVGVideoElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	CComQIPtr<ILSVGVideoElement> image = m_domElement;

	// x
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_x(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(x);
	}

	// y
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_y(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(y);
	}

	// width
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_width(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(width);
	}

	// height
	{
		CComQIPtr<ILSVGAnimatedLength> alength;
		image->get_height(&alength);
		CComQIPtr<ILSVGLength> length;
		alength->get_baseVal(&length);

		length->put_value(height);
	}

	return S_OK;
}

#endif