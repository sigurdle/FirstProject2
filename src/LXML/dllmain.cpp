#include "stdafx.h"
#include "LXML2.h"

namespace System
{

Module _Module;

extern "C"
{

BOOL WINAPI RawDllMain(HINSTANCE hModule, DWORD ul_reason_for_call, void*)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		try
		{
			_Module.Init(hModule);
		}
		catch (Exception* e)
		{
			MessageBoxW(NULL, CStringw(e->get_Reason()), L"Web", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HINSTANCE, DWORD, void*) = RawDllMain;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	return _Module.DllMain(hInstance, dwReason, lpReserved);
}

}	// extern "C"
}	// System
