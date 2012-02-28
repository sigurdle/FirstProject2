#include "stdafx.h"
#include "LXML2.h"

namespace System
{
namespace Web
{

CSSValue::CSSValue()
{
	m_cssValueType = CSS_INHERIT;	// ?? There's no unknown type
	m_bCSSTextUpdated = true;	// ??
}

String CSSValue::getStringValue()
{
	return m_cssText;
}

String CSSValue::get_cssText()
{
	return m_cssText;
}

// virtual
void CSSValue::set_cssText(StringIn newVal)
{
	m_cssText = newVal;

	if (m_cssText == L"inherit")
		m_cssValueType = CSS_INHERIT;
}

}
}
