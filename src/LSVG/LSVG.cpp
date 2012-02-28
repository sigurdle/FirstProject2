#include "stdafx.h"
#include "LSVG.h"

#include "SVGImplementation.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "Graphics")
#pragma comment(lib, "Imaging")
#pragma comment(lib, "LMedia")
#pragma comment(lib, "GUI")
#pragma comment(lib, "XPath")
#pragma comment(lib, "LXML")
#pragma comment(lib, "EcmaScript")
#pragma comment(lib, "JSVM")
#pragma comment(lib, "Networking")

#if _WIN32
#pragma comment(lib, "Mscms.lib")
#pragma comment(lib, "wininet.lib")
#endif

namespace System
{

// TODO remove
extern "C" __declspec(dllexport) Object* CreateObject()
{
	return new Web::SVGImplementation;
}

namespace Web
{

ValueHandlerT<SVGEnumerationUnitTypeValue> ValueHandlerT<SVGEnumerationUnitTypeValue>::s_valueHandler;

SVGEXT String GetAsString(double v)
{
	ASSERT(0);
	return NULL;
}

}	// Web
}	// System

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

// {26237DD9-F1D4-49a2-BA2C-6CF570422E6F}
DEFINE_GUID(CATID_LXMLPlugin, 
0x26237dd9, 0xf1d4, 0x49a2, 0xba, 0x2c, 0x6c, 0xf5, 0x70, 0x42, 0x2e, 0x6f);

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	return E_FAIL;
    // registers object, typelib and all interfaces in typelib
	HRESULT hr = _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

#if 0
	ICatRegister   *pcr;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_ICatRegister, 
		(LPVOID*)&pcr);
	
	if(SUCCEEDED(hr))
	{
		{
			CATEGORYINFO catinfo[1];

			catinfo[0].catid = CATID_LXMLPlugin;
			catinfo[0].lcid = 0;
			wcscpy(catinfo[0].szDescription, L"LXML Implementation");

			pcr->RegisterCategories(sizeof(catinfo)/sizeof(CATEGORYINFO), catinfo);
		}

		{
			CATID rgcatid[1];

			rgcatid[0] = CATID_LXMLPlugin;

			hr = pcr->RegisterClassImplCategories(CLSID_LSVGImplementation, 1, rgcatid);
		}

		pcr->Release();
	}
#endif
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	return E_FAIL;
    return _Module.UnregisterServer(TRUE);
}

#endif
