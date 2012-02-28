#ifndef __PARSENUMBER_H
#define __PARSENUMBER_H

namespace System
{

	/*
inline long _getnumber(const char** s)
{
	long number = 0;

	const char* p = *s;
	while (*p && std::isdigit(*p))
	{
		char c = *p++;
		number = number*10 + (c - '0');
	}

	*s = p;

	return number;
}
*/

//template<class iterator_type> bool it_eof(iterator_type it);

inline bool it_eof(const char* it)
{
	return *it == 0;
}

inline bool it_eof(const wchar_t* it)
{
	return *it == 0;
}

template<class char_type>
inline bool it_eof(const String::const_iterator<char_type>& it)
{
	return it.atend();
}

//template<class char_type> elem_type

template<class iterator_type>
long _getnumber(iterator_type* s)
{
	long number = 0;

	iterator_type p = *s;
	while (!it_eof(p) && isdigit(*p))
	{
		int c = *p;	// TODO
		++p;
	//	elem_type<iterator_type>::_type c = *p++;
		number = number*10 + (c - '0');
	}

	*s = p;

	return number;
}

template<class iterator_type>
long getnumber(iterator_type* s)
{
	iterator_type p = *s;

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
	{
		ASSERT(0);
	//	*s = NULL;
	}
	else
		*s = p;

	return number;
}

LFCEXT double getfnumber(const WCHAR** s);
LFCEXT double getfnumber(const char** s);
LFCEXT double getfnumber(const WCHAR* s);
LFCEXT double getfnumber(const char* s);
LFCEXT long getnumber(const WCHAR** s);
LFCEXT long getnumber(const char** s);
LFCEXT double getfrac(const WCHAR** s);
LFCEXT double getfrac(const char** s);

LFCEXT long str2int(const WCHAR* s, long retonerror);
LFCEXT long str2int(const WCHAR* s);

LFCEXT long str2int(const char* s, long retonerror);
LFCEXT long str2int(const char* s);

LFCEXT double makeflt(long intpart, double frac, int exp);

}

#endif
