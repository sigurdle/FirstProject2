#include "stdafx.h"
#include "LMediaImpl.h"

#include "LFilterGraph.h"
#include "URLSource.h"
#include "LDSoundRender.h"

#include <cwchar>

using namespace System;

#pragma comment(lib, "LFC")
#pragma comment(lib, "XML")

#if WIN32
	extern "C" DECLSPEC_DLLEXPORT
#else
	static
#endif

System::Object* CreateObject(const WCHAR* name)
{
	if (!wcscmp(name, L"DSoundRender"))
	{
		return new System::MediaShow::CLDSoundRender;
	}
	else
		return NULL;
}

	/*
LMediaModule::LMediaModule()
{
	AddProc(ASTR("CreateObject"), (proctype)CreateObject);

	RegisterModule(ASTR("LMedia.dll"), this);
}
*/

#ifndef WIN32 
	static
#endif

namespace System
{

	LMEDIAEXT int GetNBits(int range)
	{
		int nbits = 0;
		ULONG n = 0;

		while (n < range)
		{
			nbits++;

			n = (1<<nbits);
		}

		return nbits;
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
	if (FAILED(hr)) return hr;

#if 0
	CComPtr<ILFilterMapper2> filterMapper;
	hr = filterMapper.CoCreateInstance(CLSID_LFilterMapper);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_LVideoRenderer, L"Video Renderer", _Module.m_hInstResource, IDF_LVIDEORENDERER);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_LDSoundRender, L"DSound Render", _Module.m_hInstResource, IDF_LDSOUNDRENDER);
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
