#include "stdafx.h"
//#include "LXML.h"
#include "CSS.h"

namespace System
{
namespace Web
{

CSSCharsetRule::CSSCharsetRule()
{
//		m_bCSSTextUpdated = true;

//		m_pListener = NULL;
}

CSSCharsetRule::~CSSCharsetRule()
{
//		ASSERT(m_pListener == NULL);
}

String CSSCharsetRule::get_encoding()
{
	ASSERT(0);	// TODO
	return NULL;//sysstring();
}

void CSSCharsetRule::set_encoding(StringIn newVal)
{
	// TODO
	ASSERT(0);
}

CSSType CSSCharsetRule::get_type() const
{
	return CHARSET_RULE;
}

}	// Web
}
