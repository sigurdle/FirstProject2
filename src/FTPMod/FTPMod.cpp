// FTPMod.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f FTPModps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "FTPMod.h"

#include "FTPBrowser.h"

#pragma comment(lib, "../LFC/Debug/LFC.lib")

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

#include "comcat.h"
#include "WebDAVBrowser.h"
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription)
{
	
	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;
	
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (FAILED(hr))
		return hr;
	
	// Make sure the HKCR\Component Categories\{..catid...}
	// key is registered.
	CATEGORYINFO catinfo;
	catinfo.catid = catid;
	catinfo.lcid = 0x0409 ; // english
	
	// Make sure the provided description is not too long.
	// Only copy the first 127 characters if it is.
	int len = wcslen(catDescription);
	if (len>127)
		len = 127;
	wcsncpy(catinfo.szDescription, catDescription, len);
	// Make sure the description is null terminated.
	catinfo.szDescription[len] = '\0';
	
	hr = pcr->RegisterCategories(1, &catinfo);
	pcr->Release();
	
	return hr;
}

HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	// Register your component categories information.
	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (SUCCEEDED(hr))
	{
		// Register this category as being "implemented" by the class.
		CATID rgcatid[1] ;
		rgcatid[0] = catid;
		hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
	}
	
	if (pcr != NULL)
		pcr->Release();
	
	return hr;
}

HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	ICatRegister* pcr = NULL ;
	HRESULT hr = S_OK ;
	
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (SUCCEEDED(hr))
	{
		// Unregister this category as being "implemented" by the class.
		CATID rgcatid[1] ;
		rgcatid[0] = catid;
		hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
	}
	
	if (pcr != NULL)
		pcr->Release();
	
	return hr;
}



CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
//OBJECT_ENTRY(CLSID_FTPBrowser, CFTPBrowser)
//OBJECT_ENTRY(CLSID_WebDAVBrowser, CWebDAVBrowser)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance/*, &LIBID_FTPMODLib*/);
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
	HRESULT hr;

	hr = _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

	// Mark the control as safe for initializing.

	/*
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
	if (FAILED(hr)) return hr;
	
	hr = RegisterCLSIDInCategory(CLSID_FTPBrowser, CATID_SafeForInitializing);
	if (FAILED(hr)) return hr;
	
	// Mark the control as safe for scripting.
	
	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
	if (FAILED(hr)) return hr;

	hr = RegisterCLSIDInCategory(CLSID_FTPBrowser, CATID_SafeForScripting);
	if (FAILED(hr)) return hr;
	*/
	// registers object, typelib and all interfaces in typelib
    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	HRESULT hr;
	
	hr = _Module.UnregisterServer(TRUE);
	
	// Remove entries from the registry.
	/*
	hr = UnRegisterCLSIDInCategory(CLSID_FTPBrowser, CATID_SafeForInitializing);
	if (FAILED(hr)) return hr;
	
	hr = UnRegisterCLSIDInCategory(CLSID_FTPBrowser, CATID_SafeForScripting);
	if (FAILED(hr)) return hr;
	*/
	return hr;
}


