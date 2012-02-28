#include "stdafx.h"
#include "LSVG.h"

#include "SVGImplementation.h"

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
			MessageBox(NULL, CStringw(e->get_Reason()), L"SVG", MB_OK);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HINSTANCE, DWORD, void*) = RawDllMain;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved)
{
	return _Module.DllMain(hModule, dwReason, lpReserved);
}

}	// extern "C"
}	// System
