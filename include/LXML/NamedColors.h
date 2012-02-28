#ifndef __NAMEDCOLORS_H_
#define __NAMEDCOLORS_H_

namespace System
{

struct COLORNAME
{
	String get_Name()
	{
		return &name;
	}

	ImmutableString<wchar_t> name;
	uint32 clr;
};

const int ColorNames_length = 147;	// Should be 147
extern COLORNAME ColorNames[ColorNames_length];

extern int SystemColorsCount;
extern COLORNAME SystemColors[];

}

#endif // __NAMEDCOLORS_H_
