#include "stdafx.h"
#include "LXML2.h"
#include "CSSRule.h"

namespace System
{
namespace Web
{

String CSSRule::get_cssText()
{
	return m_cssText;
}

void CSSRule::set_cssText(StringIn newVal)
{
	m_cssText = newVal;
}

CSSStyleSheet* CSSRule::get_parentStyleSheet()
{
	return m_parentStyleSheet;
}

void CSSRule::set_parentStyleSheet(CSSStyleSheet *newVal)
{
	m_parentStyleSheet = newVal;
}

CSSRule* CSSRule::get_parentRule()
{
	return m_parentRule;
}

void CSSRule::set_parentRule(CSSRule *newVal)
{
	m_parentRule = newVal;
}

CSSType CSSRule::get_type() const
{
	return UNKNOWN_RULE;
}

}	// Web
}
