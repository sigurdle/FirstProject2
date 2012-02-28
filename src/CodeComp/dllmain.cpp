// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "CodeComp.h"

#pragma comment(lib, "LFC")

namespace System
{

Module _Module;

class type_info
{
public:
	virtual ~type_info()
	{
	}

	void*_m_data;
	char _m_d_name[1];
};

extern "C"
{

BOOL WINAPI RawDllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{

		// TODO: Hack

		((type_info*)&typeid(void))->_m_data = &Types::type_void;
		((type_info*)&typeid(bool))->_m_data = &Types::type_bool;

		((type_info*)&typeid(char))->_m_data = &Types::type_char;
		((type_info*)&typeid(signed char))->_m_data = &Types::type_signed_char;
		((type_info*)&typeid(unsigned char))->_m_data = &Types::type_unsigned_char;

		((type_info*)&typeid(wchar_t))->_m_data = &Types::type_wchar;

		((type_info*)&typeid(short))->_m_data = &Types::type_short;
		((type_info*)&typeid(unsigned short))->_m_data = &Types::type_unsigned_short;

		((type_info*)&typeid(int))->_m_data = &Types::type_int;
		((type_info*)&typeid(unsigned int))->_m_data = &Types::type_unsigned_int;

		((type_info*)&typeid(long))->_m_data = &Types::type_long;
		((type_info*)&typeid(unsigned long))->_m_data = &Types::type_unsigned_long;

		((type_info*)&typeid(long long))->_m_data = &Types::type_long_long;
		((type_info*)&typeid(unsigned long long))->_m_data = &Types::type_unsigned_long_long;

		((type_info*)&typeid(float))->_m_data = &Types::type_float;
		((type_info*)&typeid(double))->_m_data = &Types::type_double;
		((type_info*)&typeid(long double))->_m_data = &Types::type_long_double;

		try
		{
			_Module.Init(hModule);
		}
		_catch (Exception, e)
		{
			MessageBoxW(NULL, CStringw(e->get_Reason()), L"CodeComp", MB_OK | MB_ICONWARNING);
			// NOTE: Fall through, returning TRUE
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HMODULE, DWORD, LPVOID) = RawDllMain;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return _Module.DllMain(hModule, ul_reason_for_call, lpReserved);
}

}	// extern "C"
}	// System
