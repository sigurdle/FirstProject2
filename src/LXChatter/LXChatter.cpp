#include "stdafx.h"
//#include "resource.h"
#include "LXChatter2.h"

#define Array var
#include <windows.h>
#undef Array

#if _DEBUG
#pragma comment(lib, "../LFC/Debug/LFC.lib")
#else
#pragma comment(lib, "../LFC/Release/LFC.lib")
#endif

#if _DEBUG
#pragma comment(lib, "../LXUI/Debug/LXUI.lib")
#else
#pragma comment(lib, "../LXUI/ReleaseMinSize/LXUI.lib")
#endif

Module _Module;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
	//	_Module.Init(ObjectMap, hInstance, &LIBID_LXUILib);
		_Module.m_hInstance = hInstance;
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
	}
	return true;    // ok
}
