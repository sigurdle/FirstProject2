#include "stdafx.h"
#include "LXML2.h"

#include "CSSFontFaceRule.h"

namespace System
{
namespace Web
{

CSSFontFaceRule::CSSFontFaceRule()
{
//		m_bCSSTextUpdated = true;

//		m_pListener = NULL;
}

CSSFontFaceRule::~CSSFontFaceRule()
{
//		ASSERT(m_pListener == NULL);
}

ICSSStyleDeclaration* CSSFontFaceRule::get_style()
{
	ASSERT(0);
	return NULL;
}

CSSType CSSFontFaceRule::get_type() const
{
	return FONT_FACE_RULE;
}

}	// Web
}
