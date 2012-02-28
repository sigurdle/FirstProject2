#include "stdafx.h"
#include "HTML2.h"

#include "HTMLDocument.h"
#include "SMILDocument.h"
#include "NITFDocument.h"
#include "NewsMLDocument.h"

#include "HTMLIFrameElement.h"
#include "HTMLCanvasElement.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "Graphics")
#pragma comment(lib, "XPath")
#pragma comment(lib, "XML")
#pragma comment(lib, "GUI")
#pragma comment(lib, "LXML")
#pragma comment(lib, "LMedia")
#pragma comment(lib, "Networking")

// OpenGL
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

namespace System
{
void build_sRGBLuts();

}
//void ReleaseCSSInitialValues();

using namespace System;

#ifndef WIN32
	static
#endif

HTMLModule _Module;

#if 0

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
#endif


namespace System
{
namespace Web
{

HTMLEXT String GetAsString(StringIn str)
{
	return str;
}

Element* HTMLImplementation::CreateElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes)
{
	if (namespaceURI == L"http://www.w3.org/1999/xhtml")
	{
		if (localName == L"a")
		{
			return new HTMLAnchorElement(attributes);
		}
		else if (localName == L"audio")
		{
			ASSERT(0);
			return NULL;
		}
		else if (localName == L"body")
		{
			return new HTMLBodyElement(attributes);
		}
		else if (localName == L"canvas")
		{
			return new HTMLCanvasElement(attributes);
		}
		/*
		else if (*localName == L"div")
		{
			return new HTMLDivElement(attributes);
		}
		*/
		else if (localName == L"frame")
		{
			return new HTMLFrameElement(attributes);
		}
		else if (localName == L"frameset")
		{
			return new HTMLFrameSetElement(attributes);
		}
		else if (localName == L"iframe")
		{
			return new HTMLIFrameElement(attributes);
		}
		else if (localName == L"img")
		{
			return new HTMLImageElement(attributes);
		}
		else if (localName == L"link")
		{
			return new HTMLLinkElement(attributes);
		}
		else if (localName == L"object")
		{
			ASSERT(0);
			return NULL;
		}
		else if (localName == L"p")
		{
			return new HTMLParagraphElement(attributes);
		}
		else if (localName == L"style")
		{
			return new HTMLStyleElement(attributes);
		}
		/*
		else if (*localName == L"table")
		{
			return new HTMLTableElement(attributes);
		}
		*/
		else if (localName == L"video")
		{
			ASSERT(0);
			return NULL;
		}
		else
		{
			return new HTMLGenericElement(qualifiedName, attributes);
		}
	}
	else if (namespaceURI == L"http://www.w3.org/2001/SMIL20/Language")
	{
		if (localName == L"animate")
		{
			return new SMILAnimateElement(attributes);
		}
		else if (localName == L"transition")
		{
			return new SMILTransitionElement(attributes);
		}
		else if (localName == L"root-layout")
		{
			return new SMILRootLayoutElement(attributes);
		}
		else if (localName == L"topLayout")
		{
			return new SMILTopLayoutElement(attributes);
		}
		else if (localName == L"layout")
		{
			ASSERT(0);
		//	return new SMILLayoutElement(attributes);
		}
		else if (localName == L"region")
		{
			return new SMILRegionElement(attributes);
		}
		else if (localName == L"par")
		{
			return new SMILParElement(attributes);
		}
		else if (localName == L"seq")
		{
			return new SMILSeqElement(attributes);
		}
		else
			ASSERT(0);
	}

	return NULL;
}

}
}

#if WIN32
	extern "C" DECLSPEC_DLLEXPORT
#else
	static
#endif

System::Object* CreateObject(const WCHAR* classname)
{
	return new System::Web::HTMLImplementation;
}

HTMLModule::HTMLModule()
{
	AddProc(ASTR("CreateObject"), (proctype)CreateObject);

//	RegisterModule(ASTR("LHTML.dll"), this);
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

// {26237DD9-F1D4-49a2-BA2C-6CF570422E6F}
DEFINE_GUID(CATID_LXMLPlugin, 
0x26237dd9, 0xf1d4, 0x49a2, 0xba, 0x2c, 0x6c, 0xf5, 0x70, 0x42, 0x2e, 0x6f);

STDAPI DllRegisterServer(void)
{
	return E_FAIL;
	HRESULT hr;

    // registers object, typelib and all interfaces in typelib
   hr =  _Module.RegisterServer(TRUE);
	if (FAILED(hr)) return hr;

	{
		ICatRegister   *pcr;
		HRESULT        hr = S_OK;

		hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			IID_ICatRegister, 
			(LPVOID*)&pcr);
		
		if(SUCCEEDED(hr))
		{
			CATEGORYINFO catinfo[1];
			catinfo[0].catid = CATID_LXMLPlugin;
			catinfo[0].lcid = 0;
			wcscpy(catinfo[0].szDescription, L"LXML Implementation");
			
			hr = pcr->RegisterCategories(sizeof(catinfo)/sizeof(CATEGORYINFO), catinfo);
			
			pcr->Release();
		}
	}

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
//	HRESULT hr;
	return E_FAIL;

   return _Module.UnregisterServer(TRUE);
}

#endif
