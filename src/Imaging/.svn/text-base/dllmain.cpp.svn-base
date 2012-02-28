// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Imaging.h"

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
		_catch (Exception, e)
		{
			MessageBox(NULL, e->get_Reason().c_strw(), L"Imaging", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HINSTANCE, DWORD, void*) = RawDllMain;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	return _Module.DllMain(hModule, ul_reason_for_call);
}

}	// extern "C"
}	// System
