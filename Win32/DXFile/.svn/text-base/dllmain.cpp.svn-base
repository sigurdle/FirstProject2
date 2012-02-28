// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

namespace System
{
Module _Module;

extern "C"
{

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	return _Module.DllMain(hModule, ul_reason_for_call);
}

}	// extern "C"
}	// System
