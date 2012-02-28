#include "stdafx.h"
#include "LFC.h"

/*
const int some_const = 7;

enum testenum
{
	some_enum = some_const + 6,
};
*/

#if 0
extern "C" DECLSPEC_DLLEXPORT int stricmp(const char* s1, const char* s2)
{
	while (*s1)
	{
		if (*s2 == 0)
			return 1;	// s1 > s2

		int diff = toupper(*s1) - toupper(*s2);
		if (diff)
			return diff;

		s1++;
		s2++;
	}

	if (*s2 != 0)
		return -1;	// s1 < s2

	return 0;
}
#endif