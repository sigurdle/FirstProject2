#include "stdafx.h"
#include "LXML2.h"
#include "SVGColorImpl.h"

#include "parsecolor.h"

namespace System
{
namespace Web
{

SVGColorBase::SVGColorBase()
{
	m_colorType = SVG_COLORTYPE_UNKNOWN;
	m_rgbColor = NULL;
	m_iccColor = NULL;
}

SVGColorBase::~SVGColorBase()
{
	ASSERT(m_rgbColor == NULL);
	ASSERT(m_iccColor == NULL);
}

void SVGColorBase::setRGBColor(StringIn rgbColor)
{
	ASSERT(0);
#if 0

	if (rgbColor == NULL) THROW(-1);

	if (SetRGBColor(rgbColor->c_str()) != 0)
		THROW(-1);

	m_colorType = SVG_COLORTYPE_RGBCOLOR;
#endif
}

void SVGColorBase::setRGBColorICCColor(StringIn rgbColor, StringIn iccColor)
{
	ASSERT(0);
#if 0

	if (rgbColor == NULL) THROW(-1);
	if (iccColor == NULL) THROW(-1);

	if (SetRGBColor(rgbColor->c_str()) != 0)
		THROW(-1);
	
	if (SetICCColor(iccColor->c_str()) != 0)
		THROW(-1);
#endif
	m_colorType = SVG_COLORTYPE_RGBCOLOR_ICCCOLOR;
}

void SVGColorBase::setColor(SVGColorType colorType, StringIn rgbColor, StringIn iccColor)
{
	ASSERT(0);
#if 0

	if (	colorType == SVG_COLORTYPE_RGBCOLOR ||
			colorType == SVG_COLORTYPE_RGBCOLOR_ICCCOLOR)
	{
		if (rgbColor == NULL)
			THROW(-1);

		if (SetRGBColor(rgbColor->c_str()) != 0)
			THROW(-1);

		if (colorType == SVG_COLORTYPE_RGBCOLOR_ICCCOLOR)
		{
			if (iccColor == NULL)
				THROW(-1);

			if (SetICCColor(iccColor->c_str()) != 0)
				THROW(-1);
		}
	}

	m_colorType = colorType;

	m_bCSSTextUpdated = false;
#endif
// TODO, notify
}

String SVGColorBase::get_cssText()
{
	if (!m_bCSSTextUpdated)
	{
		WCHAR buf[64];

		swprintf_s(buf, L"#%2.2X%2.2X%2.2X",
			(int)m_rgbColor->m_red->m_floatValueUserUnit,
			(int)m_rgbColor->m_green->m_floatValueUserUnit,
			(int)m_rgbColor->m_blue->m_floatValueUserUnit);

		m_cssText = string_copy(buf);
		m_bCSSTextUpdated = true;
	}

	return CSSValue::get_cssText();
}

void SVGColorBase::SetRGBColor(Graphics::Color clr)
{
	if (m_rgbColor == NULL)
	{
		m_rgbColor = new RGBColor;
		m_rgbColor->m_pListener = this;
	}

	m_rgbColor->m_pListener = NULL;	// Set this to NULL here, so we don't get lots of notifications from the calls below

	m_rgbColor->get_red()->setFloatValue(CSS_NUMBER, clr.GetRed());
	m_rgbColor->get_green()->setFloatValue(CSS_NUMBER, clr.GetGreen());
	m_rgbColor->get_blue()->setFloatValue(CSS_NUMBER, clr.GetBlue());

	m_rgbColor->m_pListener = this;	// Reset this
}

ErrorCode SVGColorBase::SetRGBColor(const WCHAR* s, const WCHAR* *pp)
{
	const WCHAR* pp2;
	Graphics::Color clr;
	if (ParseRGBColor(s, &pp2, &clr) >= 0)
	{
		if (pp)
		{
			*pp = pp2;
		}
		else
		{
			if (*pp2 != 0)
				return Error;
		}

		SetRGBColor(clr);
		return Success;
	}

	return Error;
}

ErrorCode SVGColorBase::SetICCColor(const WCHAR* s, const WCHAR* *pp)
{
	if (m_iccColor == NULL)
	{
		m_iccColor = new SVGICCColor;
		m_iccColor->m_pListener = this;
	}

	return m_iccColor->ParseICCColor(s, pp);
}

}	// Web
}
