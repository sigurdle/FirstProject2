// SWF.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LFC.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LFC.lib")
#endif

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LXUI.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LXUI.lib")
#endif

#include "../include/windows_header.h"

using namespace System;

//#include "Movie.h"

Module _Module;

MSWindows::BOOL APIENTRY DllMain( HANDLE hModule, MSWindows::DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		_Module.m_hInstance = (MSWindows::HINSTANCE)hModule;
	}
	return true;
}
