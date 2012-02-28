#include "stdafx.h"

namespace System
{
namespace Web
{

// Parses a clock-value into seconds
WEBEXT double ParseClockValue(const WCHAR* s)
{
	const WCHAR* p = s;

	ASSERT(0);
	return 0;

#if 0
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

	while (*p && isspace(*p)) p++;

// TODO, better error checking
	int nnumbers = 0;
	int numbers[3];

	numbers[nnumbers++] = getnumber(&p);
	if (*p == L':')
	{
		numbers[nnumbers++] = getnumber(&p);
		if (*p == L':')
		{
			numbers[nnumbers++] = getnumber(&p);
		}
	}

// get fraction
	double fraction;
	if (*p == L'.')
	{
		p++;
		ASSERT(0);
#if 0
		fraction = getfrac(p);
#endif
	}
	else
		fraction = 0;

	double seconds;

	if (nnumbers > 1)
	{
		seconds = numbers[--nnumbers];
		if (nnumbers > 0) seconds += numbers[--nnumbers]*60;
		if (nnumbers > 0) seconds += numbers[--nnumbers]*60*60;

		seconds += fraction;
	}
	else
	{
		double value = numbers[0] + fraction;

		ASSERT(0);
#if 0
	// get metric
		if (!std::wcsncmp(p, L"h", 1))
		{
			seconds = value * 60*60;
		}
		else if (!std::wcsncmp(p, L"min", 3))
		{
			seconds = value * 60;
		}
		else if (!std::wcsncmp(p, L"ms", 2))
		{
			seconds = value/1000.0;
		}
		else// if (!wcsncmp(p, OLESTR("s"), 1))
		{
			seconds = value;
		}
#endif
	}

	if (sign == -1) seconds = -seconds;
	return seconds;
#endif
}

WEBEXT double ParseClockValue(StringIn s)
{
	return ParseClockValue(CStringw(s).c_str());
}

}	// Web
}
