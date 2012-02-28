// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "RDF.h"

#pragma comment(lib, "LFC")

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
			LoadTypes(&_Module, hModule);
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

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	_Module.DllMain(hModule, ul_reason_for_call, lpReserved);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			rdf::MapNS(rdf::rdfURI, "rdf");
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

}	// extern "C"
}	// System
