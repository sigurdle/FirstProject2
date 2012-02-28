// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "X3D2.h"

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
			MessageBox(nullptr, e->get_Reason().c_strw(), L"X3D", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HMODULE, DWORD, LPVOID) = RawDllMain;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, void* lpReserved)
{
	return _Module.DllMain(hModule, dwReason, lpReserved);
}

}	// extern "C"
}	// System
