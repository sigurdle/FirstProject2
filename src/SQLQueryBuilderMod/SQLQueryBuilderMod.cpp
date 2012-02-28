// SQLQueryBuilderMod.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f SQLQueryBuilderModps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "SQLQueryBuilderMod.h"

#include "SQLQueryBuilderMod_i.c"
#include "SQLQueryBuilder.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_SQLQueryBuilder, CSQLQueryBuilder)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_SQLQUERYBUILDERMODLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

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


/// TODO, put this somewhere else
HGLOBAL COleDataObject::GetGlobalData(UINT nClipboardFormat)
{
	FORMATETC fetc = {0};
	fetc.cfFormat = nClipboardFormat;
	fetc.tymed = TYMED_HGLOBAL;
	fetc.dwAspect = DVASPECT_CONTENT;
	fetc.lindex = -1;			//	give me all

	STGMEDIUM medium = {0};
	medium.tymed = TYMED_HGLOBAL;

	HRESULT hr = m_pDataObject->GetData(&fetc, &medium);
	if (SUCCEEDED(hr))
	{
		return medium.hGlobal;
	}

	return NULL;
}
