#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFontFaceElement.h"

namespace System
{
namespace Web
{

// Extenions
double SVGFontFaceElement::get_unitsPerEm()
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComBSTR v;
	getAttribute(L"units-per-em", &v);
	if (v.Length())
	{
		return getfnumber(v);
	}
	else
		return = 1000;	// default if not specified
#endif
	return 0;
}

double SVGFontFaceElement::get_xHeight()
{
	return 0;
}

double SVGFontFaceElement::get_capHeight()
{
	return 0;
}

double SVGFontFaceElement::get_ascent()
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComBSTR v;
	getAttribute(L"ascent", &v);
	if (v.Length())
	{
		*pVal = getfnumber(v);
	}
	else
	{
		CComQIPtr<ILSVGFontElement> fontElement = m_parentNode;
		if (fontElement)
		{
			double vertOriginY;
			fontElement->get_vertOriginY(&vertOriginY);

			double unitsPerEm;
			get_unitsPerEm(&unitsPerEm);

			*pVal = unitsPerEm - vertOriginY;
		}
		else
			return E_FAIL;
	}
#endif
	return 0;
}

double SVGFontFaceElement::get_descent()
{
	ASSERT(0);
#if 0
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComBSTR v;
	getAttribute(L"descent", &v);
	if (v.Length())
	{
		*pVal = getfnumber(v);
	}
	else
	{
		CComQIPtr<ILSVGFontElement> fontElement = m_parentNode;
		if (fontElement)
		{
			double vertOriginY;
			fontElement->get_vertOriginY(&vertOriginY);

			*pVal = vertOriginY;
		}
		else
			return E_FAIL;
	}
#endif

	return 0;
}

}	// w3c
}
