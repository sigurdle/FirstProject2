#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEImageElement.h"
#include "PSVGFEImageElement.h"

namespace System
{
namespace Web
{

SVGFEImageElement::SVGFEImageElement() : SVGElement(new PSVGFEImageElement(this))
{
	m_preserveAspectRatio = NULL;

	m_pImage = NULL;

	AddXMLAttribute(NewXMLAttr(&m_preserveAspectRatio, NULL, WSTR("preserveAspectRatio"), WSTR("xMidYMid meet")));

	SetAllValues(this);	// ???
}

CImage* SVGFEImageElement::GetImage()
{
	ASSERT(0);
#if 0
	if (m_pImage == NULL)
	{
		CComBSTR src = m_href->m_animated->m_animVal->m_value;
		if (src.Length())
		{
			TCHAR result[2048];
			{
				CComBSTR documentUrl;
				m_ownerDocument->get_url(&documentUrl);

				DWORD resultLen = sizeof(result);
				InternetCombineUrl(_bstr_t(documentUrl), _bstr_t(src), result, &resultLen, 0);
			}

			m_pImage = g_Images.OpenImage(_bstr_t(result));
		}
	}
#endif
	return m_pImage;
}

SVGAnimatedPreserveAspectRatio* SVGFEImageElement::get_preserveAspectRatio()
{
	return m_preserveAspectRatio->m_animated;
}

}	// w3c
}
