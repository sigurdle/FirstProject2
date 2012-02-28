#include "stdafx.h"
#include "LPCX.h"

namespace System
{

Module _Module;

extern "C"
{

BOOL WINAPI RawDllMain(HMODULE hModule, DWORD ul_reason_for_call, void*)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		try
		{
			_Module.Init(hModule);
		}
		catch (Exception* e)
		{
			MessageBox(NULL, e->get_Reason().c_strw(), L"PCX", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HMODULE, DWORD, LPVOID lpReserved) = RawDllMain;

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	return _Module.DllMain(hModule, dwReason, lpReserved);
}

}	// extern "C"
}	// System
