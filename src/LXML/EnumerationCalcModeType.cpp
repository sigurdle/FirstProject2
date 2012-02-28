#include "stdafx.h"
#include "LXML2.h"

#include "EnumerationCalcModeType.h"

namespace System
{
namespace Web
{

/*
CALCMODE_DISCRETE	= 0,
CALCMODE_LINEAR	= 1,
CALCMODE_PACED	= 2,
CALCMODE_SPLINE	= 3
*/

static ImmutableString<wchar_t> CalcModeTypeStrings[] =
{
	WSTR("discrete"),
	WSTR("linear"),
	WSTR("paced"),
	WSTR("spline"),
};

void EnumerationCalcModeType::setStringValue(StringIn str)
{
	for (int i = 0; i < _countof(CalcModeTypeStrings); i++)
	{
		if (str == &CalcModeTypeStrings[i])
		{
			m_value = (CalcModeType)i;
			return;
		}
	}

	m_value = (CalcModeType)-1;
}

String EnumerationCalcModeType::getStringValue()
{
	return &CalcModeTypeStrings[m_value];
}

}	// Web
}
