#include "stdafx.h"

#include "LFC.h"

namespace System
{
using namespace std;

/*
LFCEXT long getnumber(const WCHAR** s)
{
	const WCHAR* p = *s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

	// get number part
	long number = _getnumber(&p);

	if (sign == -1) number = -number;

	if (p == *s)	// Error
		*s = NULL;
	else
		*s = p;

	return number;
}

LFCEXT long getnumber(const char** s)
{
	const char* p = *s;

// get sign
	int sign = 1;

	if ((*p == '-') || (*p == '+'))
	{
		if (*p == '-') sign = -1;
		p++;
	}

	// get number part
	long number = _getnumber(&p);

	if (sign == -1) number = -number;

	if (p == *s)	// Error
		*s = NULL;
	else
		*s = p;

	return number;
}
*/

/*
StringA ReadLine(bytestream& s)
{
	StringA str;

	while (*s != '\n')
	{
		str += *s++;
	}

	return str;
}

long _getnumber(bytestream& p)
{
	long number = 0;

	//const OLECHAR* p = *s;
	while (*p && iswdigit(*p))
	{
		WCHAR c = *p;
		number = number*10 + (c - L'0');
		p++;
	}

	//*s = p;

	return number;
}

LFCEXT long getnumber(bytestream& s)
{
	bytestream p = s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

	// get number part
	long number = _getnumber(p);

	if (sign == -1) number = -number;

	if (p == s)	// Error
		throw -1;//*s = NULL;
	else
		;//*s = p;

	return number;
}
*/

LFCEXT double getfrac(const char** s)
{
	double dig = 0.1;
	double val = 0;

	const char* p = *s;

	while (*p && isdigit(*p))
	{
		char c = *p;
		val += dig * (c - '0');

		dig = 0.1 * dig;

		p++;
	}

	*s = p;

	return val;
}

LFCEXT double getfrac(const WCHAR** s)
{
	double dig = 0.1;
	double val = 0;

	const WCHAR* p = *s;

	while (*p && iswdigit(*p))
	{
		WCHAR c = *p;
		val += dig * (c - L'0');

		dig = 0.1 * dig;

		p++;
	}

	*s = p;

	return val;
}

int lookexp(const WCHAR** s/*, long intpart, double frac*/)
{
	int c;
	int exp;

	const WCHAR *p = *s;

	int minus = 0;

	c = *p++;
	if (towlower(c) != 'e')
	{
		return 0;
	}

	c = *p++;
	if (c == '-')
	{
		minus = 1;
		//c = mygetchar();
	}
	else if (c == '+')
	{
		//c = mygetchar();
	}

	c = *p++;
	if (c >= '0' && c <= '9')
	{
		exp = _getnumber(&p);
	}
	else
	{
		return 0;
		//exp = 0;
		//p--;//myungetc(c);
	}

	if (minus)
		exp = -exp;

	*s = p;

	return exp;
}

int lookexp(const char** s/*, long intpart, double frac*/)
{
	int c;
	int exp;

	const char *p = *s;

	int minus = 0;

	c = *p++;
	if (tolower(c) != 'e')
	{
		return 0;
	}

	c = *p++;
	if (c == '-')
	{
		minus = 1;
		//c = mygetchar();
	}
	else if (c == '+')
	{
		//c = mygetchar();
	}

	c = *p++;
	if (c >= '0' && c <= '9')
	{
		exp = _getnumber(&p);
	}
	else
	{
		return 0;
		//exp = 0;
		//p--;//myungetc(c);
	}

	if (minus)
		exp = -exp;

	*s = p;

	return exp;
}

double makeflt(long intpart, double frac, int exp)
{
	double val;
	double mod, mod10;//, mod100;

	val = intpart + frac;
	if (exp > 0)
	{
		mod = 1e1;
		mod10 = 1e10;
#if IEEE_FP
		mod100 = 1e100;
#endif
	}
	else if (exp < 0)
	{
		mod = 1e-1;
		mod10 = 1e-10;
#if IEEE_FP
		mod100 = 1e-100;
#endif
		exp = -exp;
	}
#if IEEE_FP
	while (exp >= 100)
	{
		val *= mod100;
		exp -= 100;
	}
#endif
	while (exp >= 10)
	{
		val *= mod10;
		exp -= 10;
	}

	while (exp--)
	{
		val *= mod;		/* slow and dirty */
	}

	return val;
}

LFCEXT double getfnumber(const WCHAR** s)
{
	const WCHAR* p = *s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

// get number
	long integer = _getnumber(&p);

// get fraction
	int exp = 0;
	double fraction;
	if (*p == L'.')
	{
		p++;
		fraction = getfrac(&p);

	// get exp
		exp = lookexp(&p);
	}
	else
		fraction = 0;

	double specifiedValue = makeflt(integer, fraction, exp);
	if (sign == -1) specifiedValue = -specifiedValue;

	if (p == *s)	// Error
		*s = NULL;
	else
		*s = p;

	return specifiedValue;
};

LFCEXT double getfnumber(const char** s)
{
	const char* p = *s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

// get number
	long integer = _getnumber(&p);

// get fraction
	int exp = 0;
	double fraction;
	if (*p == L'.')
	{
		p++;
		fraction = getfrac(&p);

	// get exp
		exp = lookexp(&p);
	}
	else
		fraction = 0;

	double specifiedValue = makeflt(integer, fraction, exp);
	if (sign == -1) specifiedValue = -specifiedValue;

	if (p == *s)	// Error
		*s = NULL;
	else
		*s = p;

	return specifiedValue;
};

LFCEXT double getfnumber(const WCHAR* s)
{
	const WCHAR* p = s;
	return getfnumber(&p);
};

LFCEXT double getfnumber(const char* s)
{
	const char* p = s;
	return getfnumber(&p);
};

LFCEXT long str2int(const char* s, long retonerror)
{
	if (s == NULL) return retonerror;

	const char* p = s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

	long integer = _getnumber(&p);
	if (sign == -1) integer = -integer;

	if (*p != 0) return retonerror;

	return integer;
}

LFCEXT long str2int(const WCHAR* s, long retonerror)
{
	if (s == NULL) return retonerror;

	const WCHAR* p = s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

	long integer = _getnumber(&p);
	if (sign == -1) integer = -integer;

	if (*p != 0) return retonerror;

	return integer;
}

LFCEXT long str2int(const char* s)
{
	const char* p = s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

	long integer = _getnumber(&p);
	if (sign == -1) integer = -integer;

	return integer;
}

// same as above with C linkage
extern "C" LFCEXT long str2inta(const char* s)
{
	const char* p = s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

	long integer = _getnumber(&p);
	if (sign == -1) integer = -integer;

	return integer;
}

LFCEXT long str2int(const WCHAR* s)
{
	const WCHAR* p = s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

	long integer = _getnumber(&p);
	if (sign == -1) integer = -integer;

	return integer;
}

}
