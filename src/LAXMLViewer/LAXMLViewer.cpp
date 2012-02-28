// LAXMLViewer.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f LAXMLViewerps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "LAXMLViewer.h"

#include "LAXMLViewer_i.c"
#include "..\LHTML\LHTML_i.c"
#include "..\TextDataMod\TextDataMod_i.c"

#include "LHTMLActiveDocument.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_LHTMLActiveDocument, CLHTMLActiveDocument)
END_OBJECT_MAP()

#include "comcat.h"

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

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_LAXMLVIEWERLib);
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
	USES_CONVERSION;

    // registers object, typelib and all interfaces in typelib
	HRESULT hr = _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

	// Mark the control as safe for initializing.
	
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
	if (FAILED(hr)) return hr;
	
//	MessageBox(NULL, "3", "", MB_OK);

	hr = RegisterCLSIDInCategory(CLSID_LHTMLActiveDocument, CATID_SafeForInitializing);
	if (FAILED(hr)) return hr;
	
//	MessageBox(NULL, "4", "", MB_OK);

	// Mark the control as safe for scripting.
	
	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
	if (FAILED(hr)) return hr;

//	MessageBox(NULL, "5", "", MB_OK);

	hr = RegisterCLSIDInCategory(CLSID_LHTMLActiveDocument, CATID_SafeForScripting);
	if (FAILED(hr)) return hr;

	{
		LPOLESTR clsidString;
		StringFromCLSID(CLSID_LHTMLActiveDocument, &clsidString);

		TCHAR filename[MAX_PATH];
		{
			CRegKey key;
			key.Open(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\IEXPLORE.EXE");

			DWORD dwCount = sizeof(filename);
			key.QueryValue(filename, NULL, &dwCount);
		}

//	MessageBox(NULL, "7", "", MB_OK);

		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, "svgfile\\CLSID");
			key.SetValue(W2A(clsidString));
		}

		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, "svgfile\\DefaultIcon");
			key.SetValue("%SystemRoot%\\system32\\url.dll,0");
		}

//	MessageBox(NULL, "8", "", MB_OK);

		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, "svgfile\\shell\\open\\command");

			TCHAR value[512];
			sprintf(value, "%s -nohome %%1", filename);
			key.SetValue(value);
		}

		// File extension associations
		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, ".svg");
			key.SetValue("svgfile");
			key.SetValue("image/svg+xml", "Content Type");
		}

		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, ".svgz");
			key.SetValue("svgfile");
			key.SetValue("image/svg+xml", "Content Type");
		}

		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, ".xht");
			key.SetValue("svgfile");
			key.SetValue("application/xhtml+xml", "Content Type");
		}

	// Mime associations
		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\image/svg+xml");
			key.SetValue(".svg", "Extension");
			key.SetValue(W2A(clsidString), "CLSID");
		}

		/*
		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\image/svg+xml");
			key.SetValue(".svgz", "Extension");
			key.SetValue(W2A(clsidString), "CLSID");
		}
		*/

		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\application/xhtml+xml");
			key.SetValue(".xht", "Extension");
			key.SetValue(W2A(clsidString), "CLSID");
		}

	///////////
		CoTaskMemFree(clsidString);

		SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	HRESULT hr;

	// Remove entries from the registry.
	
	hr = UnRegisterCLSIDInCategory(CLSID_LHTMLActiveDocument, CATID_SafeForInitializing);
	if (FAILED(hr)) return hr;
	
	hr = UnRegisterCLSIDInCategory(CLSID_LHTMLActiveDocument, CATID_SafeForScripting);
	if (FAILED(hr)) return hr;

	return _Module.UnregisterServer(TRUE);
}
