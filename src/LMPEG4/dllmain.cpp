#include "stdafx.h"
#include "LMPEG4.h"

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

namespace System
{
extern "C"
{

BOOL WINAPI RawDllMain(HINSTANCE hModule, DWORD ul_reason_for_call, void*)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		try
		{
			LoadTypes(hModule);
		}
		catch (Exception* e)
		{
			MessageBox(NULL, L"LoadTypes failed in MPEG4", L"MPEG4", MB_OK);
			return false;
		}
	}

	return true;
}

BOOL (WINAPI *_pRawDllMain)(HINSTANCE, DWORD, void*) = RawDllMain;

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
    //    _Module.Init(ObjectMap, hInstance/*, &LIBID_LMPEG4Lib*/);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
	{
      ;//  _Module.Term();
	}
    return true;    // ok
}

}
}
