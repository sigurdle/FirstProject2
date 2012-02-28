#include "stdafx.h"
#include "LXML2.h"
#include "SVGPaint.h"

#include "NamedColors.h"
#include "parsecolor.h"

namespace System
{
namespace Web
{

SVGPaint::SVGPaint()
{
	m_paintType = SVG_PAINTTYPE_UNKNOWN;

	m_pListener = NULL;
}

SVGPaint::~SVGPaint()
{
//	TODO have this: ATLASSERT(m_pListener == NULL);
}

ErrorCode SVGPaint::ParseString(StringIn string)
{
	CStringw cstr(string);

	const WCHAR* s = cstr.c_str();
	ASSERT(s != NULL);
	if (s == NULL) return Error_InvalidArgument;//E_INVALIDARG;

	const WCHAR* p = s;

	m_uri = WSTR("");

	if (towupper(p[0]) == L'U' && towupper(p[1]) == L'R' && towupper(p[2]) == L'L')
	{
		ASSERT(0);
#if 0
		p += 3;

		while (*p && iswspace(*p)) p++;

		if (! (*p == L'(')) return E_INVALIDARG;
		p++;

		while (*p && iswspace(*p)) p++;

		StringW uri;

		while (*p && *p != L')')
		{
			uri += *p;
			p++;
		}

		uri.TrimRight();

		m_uri = uri;

		if (! (*p == ')')) return E_INVALIDARG;
		p++;

		while (*p && iswspace(*p)) p++;

		if (*p == 0)
		{
			m_paintType = SVG_PAINTTYPE_URI;
			return true;
		}
		else if (!tcscmp(p, OLESTR("none")))
		{
			m_paintType = SVG_PAINTTYPE_URI_NONE;
			return true;
		}
		else if (!tcscmp(p, OLESTR("currentColor")))
		{
			m_paintType = SVG_PAINTTYPE_URI_CURRENTCOLOR;
			return true;
		}
		else
		{
			if (SetRGBColor(p, &p) == S_OK)
			{
				while (*p && iswspace(*p)) p++;

				if (*p == 0)
				{
					m_paintType = SVG_PAINTTYPE_URI_RGBCOLOR;
					return true;
				}
				else if (!tcsncmp(p, OLESTR("icc-color"), 9))
				{
					if (SetICCColor(p, &p) == S_OK)
					{
						while (*p && iswspace(*p)) p++;
						if (*p == 0)
						{
							m_paintType = SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR;
							return 0;
						}
					}
				}
			}
		}
#endif
	}
	else if (string == L"none")
	{
		m_paintType = SVG_PAINTTYPE_NONE;
		return 0;
	}
	else if (string == L"currentColor")
	{
		m_paintType = SVG_PAINTTYPE_CURRENTCOLOR;
		m_colorType = SVG_COLORTYPE_CURRENTCOLOR;
		return 0;
	}
	else
	{
		if (SetRGBColor(p, &p) == 0)
		{
			while (*p && iswspace(*p)) p++;

			if (*p == 0)
			{
				m_paintType = SVG_PAINTTYPE_RGBCOLOR;
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
						m_paintType = SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR;
						m_colorType = SVG_COLORTYPE_RGBCOLOR_ICCCOLOR;
						return 0;
					}
				}
			}
		}
	}

	return Error_InvalidArgument;
}

void SVGPaint::UpdateCSSText()
{
	ASSERT(0);
#if 0

	m_cssText = WSTR("");

	switch (m_paintType)
	{
	case SVG_PAINTTYPE_RGBCOLOR:
		{
			WCHAR buf[64];

			swprintf(buf, L"#%2.2X%2.2X%2.2X",
				(int)m_rgbColor->m_red->m_floatValueUserUnit,
				(int)m_rgbColor->m_green->m_floatValueUserUnit,
				(int)m_rgbColor->m_blue->m_floatValueUserUnit);

			m_cssText = buf;
		}
		break;

	case SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR:
		{
			OLECHAR buf[64];

			swprintf(buf, OLESTR("#%2.2X%2.2X%2.2X"),
				(int)m_rgbColor->m_red->m_floatValueUserUnit,
				(int)m_rgbColor->m_green->m_floatValueUserUnit,
				(int)m_rgbColor->m_blue->m_floatValueUserUnit);

			m_cssText = buf;

			m_cssText += OLESTR(" icc-color(");
			m_cssText += OLESTR(")");
		}
		break;

	case SVG_PAINTTYPE_NONE:
		{
			m_cssText = OLESTR("none");
		}
		break;

	case SVG_PAINTTYPE_CURRENTCOLOR:
		{
			m_cssText = OLESTR("currentColor");
		}
		break;

	case SVG_PAINTTYPE_URI:
		{
			m_cssText += OLESTR("url(");
			m_cssText += m_uri;
			m_cssText += OLESTR(")");
		}
		break;

	case SVG_PAINTTYPE_URI_NONE:
		{
			m_cssText += OLESTR("url(");
			m_cssText += m_uri;
			m_cssText += OLESTR(") none");
		}
		break;

	case SVG_PAINTTYPE_URI_CURRENTCOLOR:
		{
			m_cssText += OLESTR("url(");
			m_cssText += m_uri;
			m_cssText += OLESTR(") currentColor");
		}
		break;

	case SVG_PAINTTYPE_URI_RGBCOLOR:
		{
			m_cssText += OLESTR("url(");
			m_cssText += m_uri;
			m_cssText += OLESTR(") currentColor");
		}
		break;

	case SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR:
		{
			m_cssText += OLESTR("url(");
			m_cssText += m_uri;
			m_cssText += OLESTR(") icc-color(");

			m_cssText += OLESTR(")");
		}
		break;
	}
#endif
}

SVGPaintType SVGPaint::get_paintType() const
{
	return m_paintType;
}

String SVGPaint::get_uri()
{
	return m_uri;
}

void SVGPaint::setPaint(SVGPaintType paintType, StringIn uri, uint8 clr[3])
{
	m_paintType = paintType;

	SetRGBColor(Graphics::Color(clr[0], clr[1], clr[2]));
	/*
	m_rgbColor->m_red->setFloatValue(CSS_NUMBER, clr[0]);
	m_rgbColor->m_green->setFloatValue(CSS_NUMBER, clr[1]);
	m_rgbColor->m_blue->setFloatValue(CSS_NUMBER, clr[2]);
	*/

	m_uri = uri;

	m_bCSSTextUpdated = false;
}

void SVGPaint::setPaint(SVGPaintType paintType, StringIn uri, StringIn rgbColor, StringIn iccColor)
{
	m_uri = uri;

	ASSERT(0);
#if 0
	if (	paintType == SVG_PAINTTYPE_RGBCOLOR ||
			paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR ||
			paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||
			paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
	{
		if (rgbColor == NULL)
			throw std::exception("rgbColor null pointer");

		if (SetRGBColor(rgbColor) != Success)
			throw std::exception("rgbColor parsing error");

		if (	paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR ||
				paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
		{
			if (iccColor == NULL)
				throw std::exception("null iccColor pointer");

			if (SetICCColor(iccColor->c_str()) != Success)
				throw std::exception("iccColor parsing error");
		}
	}

	m_paintType = paintType;

	m_bCSSTextUpdated = false;
#endif
// TODO, notify
}

void SVGPaint::setUri(StringIn uri)
{
	m_paintType = SVG_PAINTTYPE_URI_NONE;
	m_uri = uri;

	m_bCSSTextUpdated = false;
}

// CSSValue
String SVGPaint::get_cssText()
{
	if (!m_bCSSTextUpdated)
	{
		UpdateCSSText();
		m_bCSSTextUpdated = true;
	}

	return m_cssText;
}

void SVGPaint::set_cssText(StringIn newVal)
{
	if (newVal == L"inherit")
	{
		m_cssValueType = CSS_INHERIT;
		m_paintType = SVG_PAINTTYPE_UNKNOWN;
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

#if 0
void SVGPaint::operator = (const SVGPaint& value)
{
//	CComBSTR cssText;
//	value->get_cssText(&cssText);
//	set_cssText(cssText);

	m_cssValueType = value.m_cssValueType;
	m_colorType = value.m_colorType;
	m_paintType = value.m_paintType;

	m_uri = value.m_uri;

	if (m_cssValueType == CSS_CUSTOM)
	{
		if (	m_paintType == SVG_PAINTTYPE_RGBCOLOR ||
				m_paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR ||
				m_paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||
				m_paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
		{
			if (m_rgbColor == NULL)
			{
				m_rgbColor = new RGBColor;
				if (m_rgbColor)
				{
//					m_rgbColor->AddRef();
					m_rgbColor->m_pListener = this;
				}
			}

			m_rgbColor->m_pListener = NULL;

			m_rgbColor->m_red->setFloatValue(CSS_NUMBER, value.m_rgbColor->m_red->m_floatValue);
			m_rgbColor->m_green->setFloatValue(CSS_NUMBER, value.m_rgbColor->m_green->m_floatValue);
			m_rgbColor->m_blue->setFloatValue(CSS_NUMBER, value.m_rgbColor->m_blue->m_floatValue);

			m_rgbColor->m_pListener = this;
		}
		else
		{
			ASSERT(0);
		}
	}

	//m_cssText = value->m_cssText;
	m_bCSSTextUpdated = false;

	if (m_pListener)
	{
		m_pListener->OnCSSValueChanged(this);
	}
}

void SVGPaint::operator += (const SVGPaint& value)
{
	ASSERT(0);
}
#endif

void SVGPaint::InterpolateValue(const SVGPaint& a, const SVGPaint& b, double t)
{
	m_cssValueType = a.m_cssValueType;
	m_colorType = a.m_colorType;
	m_paintType = a.m_paintType;

	if (m_cssValueType == CSS_CUSTOM)
	{
		if (	m_paintType == SVG_PAINTTYPE_RGBCOLOR ||
				m_paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR ||
				m_paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||
				m_paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
		{
			if (m_rgbColor == NULL)
			{
				m_rgbColor = new RGBColor;
				if (m_rgbColor)
				{
					//m_rgbColor->AddRef();
					m_rgbColor->m_pListener = this;
				}
			}

			m_rgbColor->m_pListener = NULL;

			m_rgbColor->m_red->setFloatValue(CSS_NUMBER, a.m_rgbColor->m_red->m_floatValue + (b.m_rgbColor->m_red->m_floatValue - a.m_rgbColor->m_red->m_floatValue)*t);
			m_rgbColor->m_green->setFloatValue(CSS_NUMBER, a.m_rgbColor->m_green->m_floatValue + (b.m_rgbColor->m_green->m_floatValue - a.m_rgbColor->m_green->m_floatValue)*t);
			m_rgbColor->m_blue->setFloatValue(CSS_NUMBER, a.m_rgbColor->m_blue->m_floatValue + (b.m_rgbColor->m_blue->m_floatValue - a.m_rgbColor->m_blue->m_floatValue)*t);

			m_rgbColor->m_pListener = this;
		}
	}

	m_bCSSTextUpdated = false;
}

}	// Web
}	// System
