// UIMedia.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "UIMedia.h"

using namespace System;

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LFC.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LFC.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LMedia.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LMedia.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LXUI.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LXUI.lib")
#endif

extern "C"
{
MSWindows::BOOL WINAPI RawDllMain(HANDLE hModule, MSWindows::DWORD ul_reason_for_call, LPVOID)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		LoadTypes((System::MSWindows::HINSTANCE)hModule);
	}

	return true;
}

MSWindows::BOOL (WINAPI *_pRawDllMain)(HANDLE, MSWindows::DWORD, LPVOID) = RawDllMain;

}

MSWindows::BOOL APIENTRY DllMain( HANDLE hModule, 
                       MSWindows::DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return true;
}

