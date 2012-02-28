#include "stdafx.h"
#include "MPEG4VideoDec.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "LMedia")

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
			MessageBox(NULL, CStringw(e->get_Reason()), L"MPEG4VideoDec", MB_OK);
			return FALSE;
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HMODULE, DWORD, void*) = RawDllMain;

BOOL APIENTRY DllMain(HMODULE hModule, 
                       DWORD ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	return _Module.DllMain(hModule, ul_reason_for_call, lpReserved);
}

}	// extern "C"
}	// System
