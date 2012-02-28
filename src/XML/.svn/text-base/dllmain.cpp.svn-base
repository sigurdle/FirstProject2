// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "XML.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "XPath")

namespace System
{

Module _Module;

extern "C"
{

BOOL WINAPI RawDllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		try
		{
			_Module.Init(hModule);
		}
		catch (Exception* e)
		{
			DebugTrace(e->get_Reason() << "\n");
			return FALSE;
		}
	}

	return TRUE;
}

BOOL (WINAPI *_pRawDllMain)(HINSTANCE, DWORD, LPVOID) = RawDllMain;

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return _Module.DllMain(hModule, ul_reason_for_call, lpReserved);
}

}	// extern "C"
}	// System
