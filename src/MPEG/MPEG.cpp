#include "StdAfx.h"
#include "MPEG.h"
#include "LMPEGDemultiplexer.h"

using namespace System;

class MPEGSystemModule : public Module
{
public:
	CTOR MPEGSystemModule();
};


#if AMIGA
static
#endif

MPEGSystemModule _Module;

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

#if WIN32
	extern "C" DECLSPEC_DLLEXPORT
#else
	static
#endif

Object* CreateObject(const WCHAR* classname)
{
	if (!wcscmp(classname, L"MPEGDemultiplexer"))
	{
		return new MediaShow::MPEGDemultiplexer;
	}

	return NULL;
}

MPEGSystemModule::MPEGSystemModule()
{
	AddProc(ASTR("CreateObject"), (proctype)CreateObject);

	RegisterModule(ASTR("MPEG.dll"), this);
}

#if WIN32

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		;//  _Module.Init(ObjectMap, hInstance/*, &LIBID_MPEGLib*/);
		MSWindows::DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
	}
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
#if 0
    // registers object, typelib and all interfaces in typelib
	HRESULT hr = _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

	CComPtr<ILFilterMapper2> filterMapper;
	hr = filterMapper.CoCreateInstance(CLSID_LFilterMapper);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_LMPEGDemultiplexer, L"MPEG Demultiplexer", _Module.m_hInstResource, IDF_LMPEGDEMULTIPLEXER);
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
