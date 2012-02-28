#include "stdafx.h"
#include "LXML2.h"

#include "CSSCounter.h"

namespace System
{
namespace Web
{

CSSCounter::CSSCounter()
{
}

CSSCounter::~CSSCounter()
{
}

String CSSCounter::get_identifier()
{
	return m_identifier;
}

String CSSCounter::get_listStyle()
{
	return m_listStyle;
}

String CSSCounter::get_separator()
{
	return m_separator;
}

}	// Web
}	// System
