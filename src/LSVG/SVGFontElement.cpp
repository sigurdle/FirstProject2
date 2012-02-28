#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFontElement.h"

namespace System
{
namespace Web
{

SVGFontElement::SVGFontElement(NamedNodeMap* attributes) : SVGElement(new PSVGFontElement(this), attributes)
{
	m_horiz_adv_x = NULL;

	AddXMLAttribute(NewXMLAttr(&m_horiz_adv_x, NULL, WSTR("horiz-adv-x")));
}

// Extensions
double SVGFontElement::get_horizOriginX()
{
	ASSERT(0);
#if 0
	sysstring v = getAttribute(OLESTR("horiz-origin-x"));
	if (v.Length())
	{
		*pVal = getfnumber(v);
	}
	else
		*pVal = 0;

	return S_OK;
#endif
	return 0;
}

double SVGFontElement::get_horizOriginY()
{
	ASSERT(0);
#if 0
	CComBSTR v;
	getAttribute(L"horiz-origin-y", &v);
	if (v.Length())
	{
		*pVal = getfnumber(v);
	}
	else
		*pVal = 0;

	return S_OK;
#endif
	return 0;
}

double SVGFontElement::get_vertOriginX()
{
	ASSERT(0);
#if 0
	CComBSTR v;
	getAttribute(L"vert-origin-x", &v);
	if (v.Length())
	{
		*pVal = getfnumber(v);
	}
	else
		*pVal = 0;

	return S_OK;
#endif
	return 0;
}

double SVGFontElement::get_vertOriginY()
{
	ASSERT(0);
#if 0
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComBSTR v;
	getAttribute(L"vert-origin-y", &v);
	if (v.Length())
	{
		*pVal = getfnumber(v);
	}
	else
		*pVal = 0;
#endif
	return 0;
}

}	// w3c
}
