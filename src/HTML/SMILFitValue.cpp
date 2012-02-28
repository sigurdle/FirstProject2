#include "stdafx.h"
#include "HTML2.h"
#include "SMILFitValue.h"

namespace System
{
namespace Web
{

String SMILFitValue::getStringValue()
{
	static ImmutableString<WCHAR> string[] =
	{
		WSTR("fill"),
		WSTR("hidden"),
		WSTR("meet"),
		WSTR("scroll"),
		WSTR("slice")
	};

	return &string[(int)m_value-1];
}

}
}
