#include "stdafx.h"
#include "LVOC.h"

#pragma comment(lib, "LFC")

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

	hr = filterMapper->RegisterFilter(CLSID_LVOCLoader, L"VOC Loader", _Module.m_hInstResource, IDF_LVOCLOADER);
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
