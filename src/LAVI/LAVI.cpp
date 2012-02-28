#include "stdafx.h"
#include "LAVI.h"

#include "../include/windows_header.h"

using namespace System;

#ifdef _DEBUG
#pragma comment(lib, "../LFC/Debug/LFC.lib")
#else
#pragma comment(lib, "../LFC/Release/LFC.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../LMedia/Debug/LMedia.lib")
#else
#pragma comment(lib, "../LMedia/Release/LMedia.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../MPEG4VideoDec/Debug/MPEG4VideoDec.lib")
#else
#pragma comment(lib, "../MPEG4VideoDec/Release/MPEG4VideoDec.lib")
#endif

extern "C" __declspec(dllexport) Object* CreateObject(const wchar_t* classname)
{
	if (!wcscmp(classname, L"AVISplitter"))
	{
		return new System::Media::AVISplitter;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        ;//_Module.Init(ObjectMap, hInstance, &LIBID_LAVILib);
		  MSWindows::DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        ;//_Module.Term();
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
	HRESULT hr = _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

	CComPtr<ILFilterMapper2> filterMapper;
	hr = filterMapper.CoCreateInstance(CLSID_LFilterMapper);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_LAVISplitter, L"AVI Splitter", _Module.m_hInstResource, IDF_LAVISPLITTER);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_LWAVEParser, L"WAVE Parser", _Module.m_hInstResource, IDF_LWAVEPARSER);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_AVIDec, L"AVI Decoder", _Module.m_hInstResource, IDF_LAVIDEC);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_LACMWrapper, L"ACM Wrapper", _Module.m_hInstResource, IDF_LACMWRAPPER);
	if (FAILED(hr)) return hr;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}

#endif
