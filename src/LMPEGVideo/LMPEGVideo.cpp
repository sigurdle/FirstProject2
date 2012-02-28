#include "stdafx.h"
#include "LMPEGVideo.h"
#include "MPEGVideoDecoder.h"

#pragma comment(lib, "LFC.lib")
#pragma comment(lib, "LMedia.lib")

namespace System
{
DECLSPEC_DLLIMPORT void init_idct(void);

class MPEGVideoModule : public Module
{
public:
	MPEGVideoModule();
};

#if AMIGA
static
#endif

MPEGVideoModule _Module;

#if WIN32
	extern "C" DECLSPEC_DLLEXPORT
#else
	static
#endif

Object* CreateObject(const syschar* classname)
{
#if AMIGA	// TODO, not here
		LMedia::init_idct();
#endif
	if (!std::wcscmp(classname, L"MPEGVideoDecoder"))
	{
		return new MediaShow::MPEGVideoDecoder;
	}

	return NULL;
}

MPEGVideoModule::MPEGVideoModule()
{
//	AddProc("CreateObject", (proctype)CreateObject);

//	Module::RegisterModule("LMPEGVideo.dll", this);
}

#if WIN32

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		init_idct();
		
		//_Module.Init(ObjectMap, hInstance/*, &LIBID_LMPEGVIDEOLib*/);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
	}
	return true;    // ok
}

#endif

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
