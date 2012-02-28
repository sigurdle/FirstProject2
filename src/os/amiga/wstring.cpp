#include <windows.h>

int lstrlen(LPCTSTR str)
{
	return strlen(str);
}

int wcslen(LPCWSTR str)
{
	const __wchar_t* p = str;
	//const unsigned short* p = L"Test";
	while (*p)
		p++;

	return p-str;
}

void wcscpy(LPWSTR, LPCWSTR)
{
}

void wcsncpy(LPWSTR, LPCWSTR, int)
{
}

int wcscmp(LPCWSTR, LPCWSTR)
{
}

int wcsicmp(LPCWSTR, LPCWSTR)
{
}

int wcsncmp(LPCWSTR, LPCWSTR, int)
{
}

int wcsnicmp(LPCWSTR, LPCWSTR, int)
{
}

int _tcscmp(LPCTSTR, LPCTSTR)
{
}

int _tcsicmp(LPCTSTR, LPCTSTR)
{
}

int _tcscoll(LPCTSTR, LPCTSTR)
{
}

int _tcsicoll(LPCTSTR, LPCTSTR)
{
}

// ctype.h
/* wide function prototypes, also declared in wchar.h  */
/* character classification function prototypes */

/*_CRTIMP*/ int __cdecl iswalpha(wchar_t)
{
}

/*_CRTIMP*/ int __cdecl iswspace(wchar_t)
{
}

/*_CRTIMP*/ int __cdecl iswdigit(wchar_t)
{
}

/*_CRTIMP*/ int __cdecl iswalnum(wchar_t)
{
}

/*_CRTIMP*/ wchar_t __cdecl towupper(wchar_t)
{
}

/*_CRTIMP*/ wchar_t __cdecl towlower(wchar_t)
{
}

/*_CRTIMP*/ int __cdecl swprintf(wchar_t *, const wchar_t *, ...)
{
}

/*_CRTIMP*/ wchar_t * __cdecl wcschr(const wchar_t *, wchar_t)
{
}

/*_CRTIMP*/ wchar_t * __cdecl wcsstr(const wchar_t *, const wchar_t *)
{
}
