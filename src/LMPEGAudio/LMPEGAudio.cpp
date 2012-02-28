#include "StdAfx.h"
#include "LMPEGAudio.h"

#include "LMPEGAudioDecoder.h"
//#include "LID3Parser.h"

#include "../include/windows_header.h"

using namespace System;

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LFC.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LFC.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Release/LMedia.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LMedia.lib")
#endif

class MPEGAudioModule : public Module
{
public:
	CTOR MPEGAudioModule();
};

#if AMIGA
static
#endif

MPEGAudioModule _Module;

#if WIN32
	extern "C" DECLSPEC_DLLEXPORT
#else
	static
#endif

Object* CreateObject(const WCHAR* classname)
{
	if (!wcscmp(classname, L"MPEGAudioDecoder"))
	{
		return new System::MediaShow::MPEGAudioDecoder;
	}

	return NULL;
}

MPEGAudioModule::MPEGAudioModule()
{
	AddProc(new StringA(string_copy("CreateObject")), (proctype)CreateObject);

	RegisterModule(new StringA(string_copy("LMPEGAudio.dll")), this);
}

#if WIN32

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		;//_Module.Init(ObjectMap, hInstance, &LIBID_LMPEGAUDIOLib);
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
    // registers object, typelib and all interfaces in typelib
	HRESULT hr = _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

	CComPtr<ILFilterMapper2> filterMapper;
	hr = filterMapper.CoCreateInstance(CLSID_LFilterMapper);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_LMPEGAudioDecoder, L"MPEG Audio Decoder", _Module.m_hInstResource, IDF_LMPEGAUDIODECODER);
	if (FAILED(hr)) return hr;

	hr = filterMapper->RegisterFilter(CLSID_LID3Parser, L"ID3 Parser", _Module.m_hInstResource, IDF_LID3PARSER);
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