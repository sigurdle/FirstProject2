// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

namespace System
{

Module _Module;

extern "C"
{

BOOL WINAPI RawDllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		try
		{
			_Module.Init(hModule);
		}
		catch (Exception* e)
		{
			MessageBoxW(NULL, e->get_Reason().c_strw(), L"JSVM", MB_OK | MB_ICONERROR);
			return FALSE;
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
