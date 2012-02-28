#include "stdafx.h"
//#include "../Draw/Draw.h"
//#include "LXML.h"

#ifndef WEBEXT
#define WEBEXT
#endif

//LFCEXT int wcsncmp(const WCHAR* str, const WCHAR* str2, int len);
LFCEXT int wcsncmp(const WCHAR* str, const char* str2, int len);
LFCEXT int wcsncmp(const char* str, const WCHAR* str2, int len);
LFCEXT int wcsncmp(const char* str, const char* str2, int len);
//LFCEXT WCHAR* wcschr(const WCHAR* str, WCHAR c);

namespace System
{
namespace Web
{

enum CSSUnitType
{
	CSS_UNKNOWN	= 0,
	CSS_NUMBER	= 1,
	CSS_PERCENTAGE	= 2,
	CSS_EMS	= 3,
	CSS_EXS	= 4,
	CSS_PX	= 5,
	CSS_CM	= 6,
	CSS_MM	= 7,
	CSS_IN	= 8,
	CSS_PT	= 9,
	CSS_PC	= 10,
	CSS_DEG	= 11,
	CSS_RAD	= 12,
	CSS_GRAD	= 13,
	CSS_MS	= 14,
	CSS_S	= 15,
	CSS_HZ	= 16,
	CSS_KHZ	= 17,
	CSS_DIMENSION	= 18,
	CSS_STRING	= 19,
	CSS_URI	= 20,
	CSS_IDENT	= 21,
	CSS_ATTR	= 22,
	CSS_COUNTER	= 23,
	CSS_RECT	= 24,
	CSS_RGBCOLOR	= 25
};

}	// Web
}

#include "parsecolor.h"
#include "NamedColors.h"

namespace System
{
namespace Web
{

	// This version assumes c is a legal hex digit
static int Hex2Number(WCHAR c)
{
	ASSERT(isxdigit(c));

	if (c <= '9')
		return c - '0';
	else
		return 10 + tolower(c) - 'a';
}

int GetRGBValuesArray(const StringW& str, vector<int>& values)
{
	ASSERT(0);
#if 0

	const WCHAR* p = str.c_str();

	while (*p)
	{
		StringW str_value;
		while (*p && (*p != ',') && (*p != ' '))
		{
			str_value += *p;
			p++;
		}

		while (*p && *p == ' ') p++;	// Skip spaces

		if (*p == ',') p++;

		while (*p && *p == ' ') p++;	// Skip spaces

	//	str_value.TrimLeft();
	//	str_value.TrimRight();

		int value = str2int(str_value.c_str());
		values.Add(value);
	}
#endif

	return values.GetSize();
}

ErrorCode ParseRGBColor(/*[in]*/ const WCHAR* p, /*[out]*/ const WCHAR** pp, /*[out,retval]*/ Graphics::Color* pVal)
{
	ASSERT(pVal != NULL);
	ASSERT(pp != NULL);
	*pp = NULL;

	if (*p == '#')
	{
		p++;

		const WCHAR* s = p;
		while (*p && isxdigit(*p))
		{
			p++;
		}

		if (p-s == 3)
		{
			*pp = p;

			*pVal = Graphics::Color(255,
							(Hex2Number(s[0])<<4) | Hex2Number(s[0]),
							(Hex2Number(s[1])<<4) | Hex2Number(s[1]),
							(Hex2Number(s[2])<<4) | Hex2Number(s[2]));

			return 0;
		}
		else if (p-s == 6)
		{
			*pp = p;

			*pVal = Graphics::Color(255,
							(Hex2Number(s[0])<<4) | Hex2Number(s[1]),
							(Hex2Number(s[2])<<4) | Hex2Number(s[3]),
							(Hex2Number(s[4])<<4) | Hex2Number(s[5]));

			return 0;
		}
	}
	else if ((p[0] == 'r') && (p[1] == 'g') && (p[2] == 'b'))
	{
		p += 3;

		while (*p && *p == L' ') p++;	// Skip spaces

		if (*p++ != L'(') return -1;	// Error

		while (*p && *p == L' ') p++;	// Skip spaces
		double red = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			red = red * 255 / 100;
		}
		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double green = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			green = green * 255 / 100;
		}

		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double blue = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			blue = blue * 255 / 100;
		}

		while (*p && *p == L' ') p++;	// Skip spaces

		if (*p++ != L')') return -1;	// Error

		*pp = p;

		if (red < 0) red = 0;
		else if (red > 255) red = 255;

		if (green < 0) green = 0;
		else if (green > 255) green = 255;

		if (blue < 0) blue = 0;
		else if (blue > 255) blue = 255;

		*pVal = Graphics::Color(255, (uint8)red, (uint8)green, (uint8)blue);
		return 0;
	}
	else	// Named color
	{
		// TODO, smarter search given that array is sorted
		// TODO, make one array only
		int i = 0;

		ASSERT(0);
#if 0
		while (i < ColorNames_length)
		{
		//	int len = wcslen(ColorNames[i].name);

			if (ColorNames[i].get_Name() == p, len))
			{
				*pp = p + len;
				*pVal = ColorNames[i].clr | 0xff000000;
				return 0;
			}

			++i;
		}

		i = 0;
		while (SystemColors[i].name)
		{
			int len = wcslen(SystemColors[i].name);

			if (!wcsncmp(SystemColors[i].name, p, len))
			{
				*pp = p + len;
				*pVal = SystemColors[i].clr | 0xff000000;
				return 0;
			}

			i++;
		}
#endif
	}

	return -1;
}

ErrorCode ParseRGBAColor(/*[in]*/ const WCHAR* p, /*[out]*/ const WCHAR** pp, /*[out,retval]*/ Graphics::Color* pVal)
{
	if ((p[0] == 'r') && (p[1] == 'g') && (p[2] == 'b') && (p[3] == 'a'))
	{
		p += 4;

		while (*p && *p == L' ') p++;	// Skip spaces

		if (*p++ != L'(') return -1;	// Error

		while (*p && *p == L' ') p++;	// Skip spaces
		double red = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			red = red * 255 / 100;
		}
		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double green = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			green = green * 255 / 100;
		}

		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double blue = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			blue = blue * 255 / 100;
		}

		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double alpha = getfnumber(&p);
		if (p == NULL) return -1;

		alpha *= 255;

		while (*p && *p == L' ') p++;	// Skip spaces

		if (*p++ != L')') return -1;	// Error

		*pp = p;

		if (red < 0) red = 0;
		else if (red > 255) red = 255;

		if (green < 0) green = 0;
		else if (green > 255) green = 255;

		if (blue < 0) blue = 0;
		else if (blue > 255) blue = 255;

		if (alpha < 0) alpha = 0;
		else if (alpha > 255) alpha = 255;

		*pVal = Graphics::Color((uint8)alpha, (uint8)red, (uint8)green, (uint8)blue);
		return 0;
	}
	else
	{
		return ParseRGBColor(p, pp, pVal);
	}
}

ErrorCode ParseSingleRGBAColor(/*[in]*/ const WCHAR* p, /*[out,retval]*/ Graphics::Color* pVal)
{
	Graphics::Color clr;
	const WCHAR* pp;
	if (ParseRGBAColor(p, &pp, &clr) >= 0)
	{
		if (*pp == 0)	// End of string
		{
			if (pVal)
			{
				*pVal = clr;
			}

			return 0;
		}
	}

	return -1;
}

CSSUnitType ParseColor(const WCHAR* p, const WCHAR** pp, Graphics::Color* color)
{
	if (!wcsncmp(p, "transparent", 11))
	{
		*pp = p+11;
		return CSS_IDENT;
	}
	else if (!wcsncmp(p, "currentColor", 12))
	{
		*pp = p+12;
		return CSS_IDENT;
	}
	else
	{
		if (ParseRGBAColor(p, pp, color) >= 0)
		{
			return CSS_RGBCOLOR;
		}
	}

	return CSS_UNKNOWN;
}

}	// Web
}	// System
