#include "stdafx.h"

#include "XMLEditCtls.h"
#include "XMLGridCtl.h"

#include "../include/windows_header.h"

Module _Module;

using namespace System;

#pragma comment(lib, "../LFC/Debug/LFC.lib")
#pragma comment(lib, "../LXUI/Debug/LXUI.lib")
//#pragma comment(lib, "../LXMLEditor/Debug/LXMLEditor.lib")

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		//        _Module.Init(ObjectMap, hInstance/*, &LIBID_XMLEDITCTLSLib*/);
		MSWindows::DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
	}
	return true;    // ok
}

#if 0
/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


#endif