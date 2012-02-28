#include "stdafx.h"
#include "LSVG2.h"

#include "SVGPreserveAspectRatio.h"

namespace System
{
namespace Web
{

SVGPreserveAspectRatioValueHandler SVGPreserveAspectRatioValueHandler::s_SVGPreserveAspectRatioValueHandler;

Object* SVGPreserveAspectRatioValueHandler::Create() const
{
	return new SVGPreserveAspectRatio;
}

void SVGPreserveAspectRatioValueHandler::ParseString(Object* value, StringIn str) const
{
	// ParseString ??

	static_cast<SVGPreserveAspectRatio*>(value)->SetAsString(str);
}

void SVGPreserveAspectRatioValueHandler::InterpolateValue(Object* _dest, Object* _a, Object* _b, double t)
{
	SVGPreserveAspectRatio* dest = static_cast<SVGPreserveAspectRatio*>(_dest);
	SVGPreserveAspectRatio* a = static_cast<SVGPreserveAspectRatio*>(_a);
	SVGPreserveAspectRatio* b = static_cast<SVGPreserveAspectRatio*>(_b);

	dest->m_align = a->m_align;
	dest->m_meetOrSlice = a->m_meetOrSlice;
}

////////////////

SVGEXT String GetAsString(SVGPreserveAspectRatio* p)
{
	return p->GetAsString();
}

SVGEXT void SetAsString(SVGPreserveAspectRatio* p, StringIn str)
{
	p->SetAsString(str);
}

WCHAR* PreserverAspectRatioAlignStrings[] =
{
	L"none",
	L"xMinYMin",
	L"xMidYMin",
	L"xMaxYMin",
	L"xMinYMid",
	L"xMidYMid",
	L"xMaxYMid",
	L"xMinYMax",
	L"xMidYMax",
	L"xMaxYMax",
};

WCHAR* MeetOrSliceStrings[] =
{
	L"meet",
	L"slice",
};

SVGPreserveAspectRatio::SVGPreserveAspectRatio()
{
// Default for <image>
//	'xMidYMid meet'
	m_align = SVG_PRESERVEASPECTRATIO_XMIDYMID;//SVG_PRESERVEASPECTRATIO_UNKNOWN;
	m_meetOrSlice = SVG_MEETORSLICE_MEET;
}

SVGPreserveAspectRatioAlignType SVGPreserveAspectRatio::get_align()
{
	return m_align;
}

void SVGPreserveAspectRatio::set_align(SVGPreserveAspectRatioAlignType newVal)
{
	ASSERT(0);
}

SVGMeetOrSliceType SVGPreserveAspectRatio::get_meetOrSlice()
{
	return m_meetOrSlice;
}

void SVGPreserveAspectRatio::set_meetOrSlice(SVGMeetOrSliceType newVal)
{
	ASSERT(0);
}

void SVGPreserveAspectRatio::SetAsString(StringIn str)
{
	CStringw cstr(str);

	const WCHAR* p = cstr.c_str();

	while (iswspace(*p)) p++;

// TODO "defer"

	int i;

	for (i = 0; i < _countof(PreserverAspectRatioAlignStrings); i++)
	{
		if (!wcsncmp(PreserverAspectRatioAlignStrings[i], p, wcslen(PreserverAspectRatioAlignStrings[i])))
		{
			m_align = (SVGPreserveAspectRatioAlignType)(i+1);
			p += wcslen(PreserverAspectRatioAlignStrings[i]);
			break;
		}
	}

	while (iswspace(*p)) p++;

	for (i = 0; i < _countof(MeetOrSliceStrings); i++)
	{
		if (!wcsncmp(MeetOrSliceStrings[i], p, wcslen(MeetOrSliceStrings[i])))
		{
			m_meetOrSlice = (SVGMeetOrSliceType)(i+1);
			p += wcslen(MeetOrSliceStrings[i]);
			break;
		}
	}
}

String SVGPreserveAspectRatio::GetAsString()
{
	// TODO? can ignore meetOrSlice if align is none

	WCHAR buf[256];
	swprintf_s(buf, L"%s %s", PreserverAspectRatioAlignStrings[m_align-1], MeetOrSliceStrings[m_meetOrSlice-1]);
	return string_copy(buf);
}

void SVGPreserveAspectRatio::InterpolateValue(const SVGPreserveAspectRatio& a, const SVGPreserveAspectRatio& b, double t)
{
	ASSERT(0);
}

}	// Web
}
