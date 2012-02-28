#include "stdafx.h"
#include "LXML2.h"
#include "SVGColor.h"

namespace System
{
namespace Web
{

ErrorCode SVGColor::ParseString(StringIn newVal)
{
//	ASSERT(tcscmp(newVal.c_str(), OLESTR("inherit")));	// Should be handled before this function is reached

	ASSERT(0);
#if 0

	m_colorType = SVG_COLORTYPE_UNKNOWN;	// Assume this for now

	if (newVal == L"currentColor")
	{
		m_colorType = SVG_COLORTYPE_CURRENTCOLOR;
		return 0;
	}
	else
	{
		const WCHAR *p = newVal->c_str();

		if (SetRGBColor(p, &p) == 0)
		{
			while (*p && iswspace(*p)) p++;

			if (*p == 0)
			{
				m_colorType = SVG_COLORTYPE_RGBCOLOR;
				return 0;
			}
			else if (!wcsncmp(p, L"icc-color", 9))
			{
				if (SetICCColor(p, &p) == 0)
				{
					while (*p && iswspace(*p)) p++;
					if (*p == 0)
					{
						m_colorType = SVG_COLORTYPE_RGBCOLOR_ICCCOLOR;
						return 0;
					}
				}
			}
		}
	}
#endif
	return Error_InvalidArgument;	// Failed to parse text
}

void SVGColor::set_cssText(StringIn newVal)
{
	if (newVal == L"inherit")
	{
		m_cssValueType = CSS_INHERIT;
		m_colorType = SVG_COLORTYPE_UNKNOWN;

		m_cssText = newVal;
		m_bCSSTextUpdated = true;
	}
	else
	{
		m_cssValueType = CSS_CUSTOM;

		if (false)	// This is maybe more correct, but LXMLEditor relies on setting any value (also invalid ones)
		{
			if (ParseString(newVal) >= 0)
			{
				m_cssText = newVal;
				m_bCSSTextUpdated = true;
			}
		}
		else
		{
			ParseString(newVal);

			m_cssText = newVal;
			m_bCSSTextUpdated = true;
		}
	}

	if (m_pListener)
	{
		m_pListener->OnCSSValueChanged(this);
	}
}

void SVGColor::operator = (const SVGColor& value)
{
	ASSERT(0);
}

void SVGColor::operator += (const SVGColor& value)
{
	ASSERT(0);
}

void SVGColor::InterpolateValue(const SVGColor& a, const SVGColor& b, double t)
{
	ASSERT(0);
}

}	// w3c
}
