#include "stdafx.h"
#include "HTML2.h"

namespace System
{

Module _Module;

void build_sRGBLuts();

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
			MessageBox(NULL, e->get_Reason().c_strw(), L"HTML", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HMODULE, DWORD, void*) = RawDllMain;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, void* lpReserved)
{
	_Module.DllMain(hModule, dwReason, lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
#if 0
		_CrtSetDbgFlag(_crtDbgFlag | /*_CRTDBG_CHECK_CRT_DF |*/ _CRTDBG_LEAK_CHECK_DF);
#endif

	//	_Module.Init(ObjectMap, hInstance, &LIBID_LHTMLLib);
		DisableThreadLibraryCalls(hModule);
		
		build_sRGBLuts();	// hm.. have this here?
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
//		ReleaseCSSInitialValues();

		_Module.Term();
	}

	return true;    // ok
}

}	// extern "C"
}	// System
