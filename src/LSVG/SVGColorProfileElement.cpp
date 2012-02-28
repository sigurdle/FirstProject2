#include "stdafx.h"
#include "LSVG2.h"

#include "SVGColorProfileElement.h"
#include "PSVGColorProfileElement.h"

namespace System
{
namespace Web
{
XMLEXT int IdentNameToIndex(StringIn ident, ImmutableString<WCHAR> idents[]);

SVGColorProfileElement::SVGColorProfileElement() : SVGElement(new PSVGColorProfileElement(this))
{
	m_bTriedLoaded = false;
	m_pProfile = nullptr;
}

String SVGColorProfileElement::get_local()
{
	ASSERT(0);
	return nullptr;
}

void SVGColorProfileElement::set_local(StringIn newVal)
{
	ASSERT(0);
}

String SVGColorProfileElement::get_name()
{
	ASSERT(0);
	return nullptr;
}

void SVGColorProfileElement::set_name(StringIn newVal)
{
	ASSERT(0);
}

ImmutableString<WCHAR> RenderingIntentIdents[] =
{
	WSTR("auto"),
	WSTR("perceptual"),
	WSTR("relative-colorimetric"),
	WSTR("saturation"),
	WSTR("absolute-colorimetric"),
	NULL,
};

SVGRenderingIntent SVGColorProfileElement::get_renderingIntent()
{
	String intent = getAttribute(L"rendering-intent");
	if (intent == nullptr) intent = S(L"auto");

	int index = IdentNameToIndex(intent, RenderingIntentIdents);

	if (index >= 0)
	{
		return (SVGRenderingIntent)(index+1);
	}
	else
		return RENDERING_INTENT_UNKNOWN;
}

void SVGColorProfileElement::set_renderingIntent(SVGRenderingIntent newVal)
{
	if (newVal != RENDERING_INTENT_UNKNOWN)
	{
		setAttribute(L"rendering-intent", &RenderingIntentIdents[newVal-1]);
	}

	raise(ArgumentException());
}

ErrorCode SVGColorProfileElement::Load()
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	if (!m_bTriedLoaded)
	{
		m_bTriedLoaded = true;

		sysstring src = getAttributeNS(L"http://www.w3.org/1999/xlink", L"href");
		if (src.Length())
		{
			TCHAR absurl[2048];
			{
				CComBSTR documentUrl;
				m_ownerDocument->get_url(&documentUrl);

				DWORD resultLen = sizeof(absurl);
				InternetCombineUrl(W2A(documentUrl), W2A(src), absurl, &resultLen, 0);
			}

			m_pProfile = new CColorProfile;
			getAttribute(L"name", &m_pProfile->m_name);

			m_pProfile->LoadURL(A2W(absurl));

			LSVGRenderingIntent renderingIntent;
			get_renderingIntent(&renderingIntent);

			switch (renderingIntent)
			{
			case RENDERING_INTENT_AUTO:
			// TODO
				m_pProfile->m_lcs.lcsIntent = LCS_GM_IMAGES;
				break;

			case RENDERING_INTENT_PERCEPTUAL:
				m_pProfile->m_lcs.lcsIntent = LCS_GM_IMAGES;
				break;

			case RENDERING_INTENT_RELATIVE_COLORIMETRIC:
				m_pProfile->m_lcs.lcsIntent = LCS_GM_GRAPHICS;
				break;

			case RENDERING_INTENT_SATURATION:
				m_pProfile->m_lcs.lcsIntent = LCS_GM_BUSINESS;
				break;

			case RENDERING_INTENT_ABSOLUTE_COLORIMETRIC:
				m_pProfile->m_lcs.lcsIntent = LCS_GM_ABS_COLORIMETRIC;
				break;
			}
		}
	}
#endif
	return Success;
}

}	// Web
}	// System
