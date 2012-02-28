#include "stdafx.h"
#include "LXML2.h"
#include "SVGICCColor.h"

#include "SVGNumberList.h"

namespace System
{
namespace Web
{

ErrorCode SVGICCColor::ParseICCColor(const WCHAR* s, const WCHAR* *pp)
{
	ASSERT(0);
#if 0

	if (pp) *pp = NULL;

	const WCHAR* p = s;
	if (!tcsncmp(p, L"icc-color", 9))
	{
		p += 9;

		if (*p != L'(') return E_FAIL;
		p++;

		sysstring colorProfile;
		while (*p && (*p != L')' && *p != L','))
		{
			colorProfile += *p;
			p++;
		}

		if (colorProfile.length() == 0) return E_FAIL;
		m_colorProfile = colorProfile;

		m_colors->RemoveAll();

		while (*p && iswspace(*p)) p++;

		while (*p)
		{
			if (*p == L',')
				p++;

			double fval = getfnumber(&p);

			ASSERT(0);
#if 0
			CComObject<SVGNumber>* pSVGNumber;
			CComObject<SVGNumber>::CreateInstance(&pSVGNumber);
			pSVGNumber->m_value = fval;

			pSVGNumber->AddRef();
			m_colors->m_items.Add(pSVGNumber);

			while (*p && iswspace(*p)) p++;

			if (*p == L')')
				break;
#endif
		}

		if (*p != L')') return E_FAIL;
		p++;

		if (pp)
		{
			*pp = p;
		}
		else
		{
			if (*p != 0)
				return E_FAIL;
		}

		return S_OK;
	}
#endif
	return Error;
}

String SVGICCColor::get_colorProfile() const
{
	return m_colorProfile;
}

void SVGICCColor::set_colorProfile(StringIn newVal)
{
	m_colorProfile = newVal;
// TODO, notify
}

SVGNumberList* SVGICCColor::get_colors()
{
	return m_colors;
}

}	// Web
}
