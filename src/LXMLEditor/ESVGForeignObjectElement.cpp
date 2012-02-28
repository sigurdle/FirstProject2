#include "stdafx.h"
#include "resource.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "ESVGForeignObjectElement.h"

#if 0
//void DrawPathSegList(ILSVGPathSegList* seglist, HDC iDC, ILSVGMatrix* xform);

STDMETHODIMP CESVGForeignObjectElement::SetShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height)
{
	CComQIPtr<ILSVGForeignObjectElement> rect = m_domElement;

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

STDMETHODIMP CESVGForeignObjectElement::Move(ISVGView* view, double dx, double dy)
{
	CComQIPtr<ILSVGForeignObjectElement> image = m_domElement;

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

STDMETHODIMP CESVGForeignObjectElement::Resize(ISVGView* view, double x, double y, double width, double height)
{
	CComQIPtr<ILSVGForeignObjectElement> image = m_domElement;

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