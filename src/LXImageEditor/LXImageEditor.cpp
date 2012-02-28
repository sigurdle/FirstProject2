#include "stdafx.h"
#include "LXImageEditor.h"

#include "ImageApp.h"
#include "ImageDocument.h"

Module _Module;

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LFC.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LFC.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LXUI.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LXUI.lib")
#endif

using namespace System;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		;//     _Module.Init(ObjectMap, hInstance, &LIBID_LXIMAGEEDITORLib);
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

// {8767A8F7-5D49-474b-AB44-4AE2D3A50BE9}
DEFINE_GUID(CATID_LXFrameworkPlugin, 
0x8767a8f7, 0x5d49, 0x474b, 0xab, 0x44, 0x4a, 0xe2, 0xd3, 0xa5, 0xb, 0xe9);

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	HRESULT hr = _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

	ICatRegister   *pcr;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_ICatRegister, 
		(LPVOID*)&pcr);
	
	if(SUCCEEDED(hr))
	{
		{
			CATEGORYINFO catinfo[1];

			catinfo[0].catid = CATID_LXFrameworkPlugin;
			catinfo[0].lcid = 0;
			wcscpy(catinfo[0].szDescription, L"LXFramework Plugin");
		
			pcr->RegisterCategories(sizeof(catinfo)/sizeof(CATEGORYINFO), catinfo);
		}

		{
			CATID rgcatid[1];

			rgcatid[0] = CATID_LXFrameworkPlugin;

			hr = pcr->RegisterClassImplCategories(CLSID_LXImageApp, 1, rgcatid);
		}

		pcr->Release();
	}

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


#endif