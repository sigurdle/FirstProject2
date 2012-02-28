#include "stdafx.h"
#include "HTML2.h"
#include "HTMLFrameSetElement.h"

#include "../LXML/parsecolor.h"

namespace System
{
namespace Web
{

HTMLFrameSetElement::HTMLFrameSetElement(NamedNodeMap* attributes) : HTMLElement(new PHTMLFrameSetElement(this), attributes)
{
}

HTMLFrameSetElement::~HTMLFrameSetElement()
{
}

String HTMLFrameSetElement::get_cols()
{
	return getAttribute(WSTR("cols"));
}

void HTMLFrameSetElement::set_cols(StringIn newVal)
{
	setAttribute(WSTR("cols"), newVal);
}

String HTMLFrameSetElement::get_rows()
{
	return getAttribute(WSTR("rows"));
}

void HTMLFrameSetElement::set_rows(StringIn newVal)
{
	setAttribute(WSTR("rows"), newVal);
}

Graphics::Color HTMLFrameSetElement::get_borderColorRGBValue()
{
	String str = getAttribute(WSTR("bordercolor"));

	if (str)
	{
		const WCHAR* p;
		Graphics::Color clr;
		ASSERT(0);
#if 0
		if (ParseRGBColor(str->c_str(), &p, &clr) >= 0)
		{
			if (*p == 0)
			{
				return clr;
			}
		}
#endif
	}

	return Graphics::Color();
}

void HTMLFrameSetElement::set_borderColorRGBValue(Graphics::Color newVal)
{
	WCHAR buf[16];
	swprintf_s(buf, L"#%2.2X%2.2X%2.2X", newVal.GetR(), newVal.GetG(), newVal.GetB());

	setAttribute(WSTR("bordercolor"), String(string_copy(buf)));
}

}	// Web
}
