// IFF.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f IFFps.mk in the project directory.

#include "stdafx.h"
//#include "resource.h"
//#include <initguid.h>
#include "IFF.h"

//#include "../LMedia/LMedia_i.c"

#include "IFFDecoder.h"
#include "IFFFormILBM.h"
#include "IFFFormANIM.h"

#if WIN32
#include "../windows_header.h"
#endif

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

using namespace System;

#if WIN32
	extern "C" DECLSPEC_DLLEXPORT
#else
	static
#endif

Object* CreateObject(const WCHAR* classname)
{
	if (!wcscmp(classname, L"IFFFormILBM"))
	{
		return new MediaShow::IFFFormILBM;
	}
	else if (!wcscmp(classname, L"IFFFormANIM"))
	{
		return new MediaShow::IFFFormANIM;
	}
	else
		return NULL;
}

class IFFModule : public Module
{
public:
	CTOR IFFModule()
	{
		AddProc(ASTR("CreateObject"), (proctype)CreateObject);

		RegisterModule(ASTR("iff.dll"), this);
	}
};

#ifndef WIN32 
	static
#endif

IFFModule _Module;

#if WIN32
/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
   ;//     _Module.Init(ObjectMap, hInstance/*, &LIBID_IFFLib*/);
			_Module.m_hInstance = hInstance;
        MSWindows::DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return true;    // ok
}
#endif

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
	HRESULT hr = _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

#if 0
	CComPtr<ILFilterMapper2> filterMapper;
	hr = filterMapper.CoCreateInstance(CLSID_LFilterMapper);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_IFFFormILBM, L"IFF/ILBM Parser", _Module.m_hInstResource, IDF_IFFFORMILBM);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_IFFFormANIM, L"IFF/ANIM Parser", _Module.m_hInstResource, IDF_IFFFORMANIM);
	if (FAILED(hr)) return hr;
#endif
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}

#endif
