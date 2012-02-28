#include "stdafx.h"
#include "LFC.h"

namespace System
{

List<String> Locale::s_localesAll;
List<GEOID> Locale::s_geoIDs;

BOOL CALLBACK myEnumGeoInfoProc(__in GEOID GeoId)
{
	Locale::s_geoIDs.Add(GeoId);
	return TRUE;
}

// static
List<GEOID>& Locale::get_GeoIDs()
{
	ASSERT(0);
#if 0
	static BOOL success = EnumSystemGeoID(GEOCLASS_NATION, 0, myEnumGeoInfoProc);
#endif
	return s_geoIDs;
}

BOOL CALLBACK myEnumLocalesProcEx(
  __in LPWSTR lpLocaleString,
  __in DWORD dwFlags,
  __in LPARAM lParam
)
{
	((List<String>*)lParam)->Add(lpLocaleString);
	return TRUE;
}

// static
List<String>& Locale::get_Locales()
{
#if 0
	static BOOL success = EnumSystemLocalesEx(myEnumLocalesProcEx, LOCALE_ALL, (LPARAM)&s_localesAll/*param*/, 0/*reserved*/);
#endif
	return s_localesAll;
}

// static
bool Locale::IsValidName(StringIn name)
{
	ASSERT(0);
#if 0
	return ::IsValidLocaleName(name.c_strw()) != FALSE;
#endif
	return false;
}

// static
String Locale::get_UserDefault()
{
	// GetUserDefaultLCID

	// Vista Only

	static WCHAR name[LOCALE_NAME_MAX_LENGTH];
//	GetUserDefaultLocaleName(name, _countof(name));
	return String::FromRaw(name);
}

// static
String Locale::get_SystemDefault()
{
	static WCHAR name[LOCALE_NAME_MAX_LENGTH];
//	GetUserDefaultLocaleName(name, _countof(name));
	return String::FromRaw(name);
}

}	// System
