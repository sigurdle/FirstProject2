#include "stdafx.h"
#include "LMPEG4.h"

#include "MPEG4Filter.h"

#include "BIFSDecoder.h"
#include "VideoDecoder.h"
#include "ODDecoder.h"
//#include "LScriptEngine.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "LMedia")
#pragma comment(lib, "MPEG4VideoDec")
#pragma comment(lib, "X3D")
#pragma comment(lib, "Draw")

namespace System
{
extern "C" __declspec(dllexport) Object* CreateObject(const WCHAR* classname)
{
	if (!wcscmp(classname, L"System::Media::MPEG4Filter"))
	{
		return new System::MediaShow::MPEG4Filter;
	}

	return NULL;
}

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

#if 0
	CComPtr<ILFilterMapper2> filterMapper;
	hr = filterMapper.CoCreateInstance(CLSID_LFilterMapper);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_MP4File, L"MPEG4 Splitter", _Module.m_hInstResource, IDF_LMPEG4SPLITTER);
	if (FAILED(hr)) return hr;
#endif

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}

#endif