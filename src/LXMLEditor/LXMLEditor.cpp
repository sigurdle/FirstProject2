// LXMLEditor.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f LXMLEditorps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "LXMLEditor.h"
#include "LXMLEditor2.h"


#include "LXMLEditorApp.h"
#include "EXMLDocument.h"
#include "EditFilterGraph.h"
#include "DTDDocument.h"
#include "ETextDocument.h"
#include "EScriptDocument.h"
#include "CSSStyleSheetView.h"
#include "PathEditPlugin.h"
#include "SelectionToolPlugin.h"
#include "TransformToolPlugin.h"
#include "BasicShapeToolPlugin.h"
#include "StylerToolPlugin.h"
#include "TransitionDirectionUI.h"
#include "TransitionProgressionUI.h"
#include "SVGElementMaskDlg.h"
#include "LiquifyToolPlugin.h"
#include "SymbolismToolPlugin.h"
#include "SVGFontGlyphsDlg.h"
#include "SVGFontsDlg.h"
#include "SVGGradientEditCtl.h"
#include "ECSSDocument.h"
#include "CSSStyleSheetViewCtl.h"
#include "EASDocument.h"
#include "ESceneDocument.h"

#ifdef _DEBUG
#pragma comment(lib, "../LFC/Debug/LFC.lib")
#else
#pragma comment(lib, "../LFC/Release/LFC.lib")
#endif

#include "../include/windows_header.h"

#if 0
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
/*
OBJECT_ENTRY(CLSID_LXMLEditorApp, CLXMLEditorApp)
OBJECT_ENTRY(CLSID_EXMLDocument, CEXMLDocument)
OBJECT_ENTRY(CLSID_EditFilterGraph, CEditFilterGraph)
OBJECT_ENTRY(CLSID_EDTDDocument, CEDTDDocument)
OBJECT_ENTRY(CLSID_ETextDocument, CETextDocument)
OBJECT_ENTRY(CLSID_EScriptDocument, CEScriptDocument)
OBJECT_ENTRY(CLSID_PathEditPlugin, CPathEditPlugin)
OBJECT_ENTRY(CLSID_SelectionToolPlugin, CSelectionToolPlugin)
OBJECT_ENTRY(CLSID_TransformToolPlugin, CTransformToolPlugin)
OBJECT_ENTRY(CLSID_BasicShapeToolPlugin, CBasicShapeToolPlugin)
OBJECT_ENTRY(CLSID_StylerToolPlugin, CStylerToolPlugin)
OBJECT_ENTRY(CLSID_TransitionDirectionUI, CTransitionDirectionUI)
OBJECT_ENTRY(CLSID_TransitionProgressionUI, CTransitionProgressionUI)
OBJECT_ENTRY(CLSID_LiquifyToolPlugin, CLiquifyToolPlugin)
OBJECT_ENTRY(CLSID_SymbolismToolPlugin, CSymbolismToolPlugin)
OBJECT_ENTRY(CLSID_SVGGradientEditCtl, CSVGGradientEditCtl)
OBJECT_ENTRY(CLSID_ECSSDocument, CECSSDocument)
OBJECT_ENTRY(CLSID_CSSStyleSheetViewCtl, CCSSStyleSheetViewCtl)
OBJECT_ENTRY(CLSID_EASDocument, CEASDocument)
OBJECT_ENTRY(CLSID_ESceneDocument, CESceneDocument)
*/
END_OBJECT_MAP()

// {8767A8F7-5D49-474b-AB44-4AE2D3A50BE9}
DEFINE_GUID(CATID_LXFrameworkPlugin, 
0x8767a8f7, 0x5d49, 0x474b, 0xab, 0x44, 0x4a, 0xe2, 0xd3, 0xa5, 0xb, 0xe9);

// {B6D3601E-04E7-47e0-B3D9-0FA86E4950AF}
DEFINE_GUID(CATID_LXMLEditorPlugin,
0xb6d3601e, 0x4e7, 0x47e0, 0xb3, 0xd9, 0xf, 0xa8, 0x6e, 0x49, 0x50, 0xaf);

#endif

using namespace System;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

Module _Module;

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.m_hInstance = hInstance; 
		//g_hInstance = hInstance;
		;//   _Module.Init(ObjectMap, hInstance/*, &LIBID_LXMLEDITORLib*/);
		MSWindows::DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
	}
	return true;    // ok
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

	ICatRegister   *pcr;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_ICatRegister, 
		(LPVOID*)&pcr);
	
	if(SUCCEEDED(hr))
	{
#if 0
		{
			CATEGORYINFO catinfo[2];

			catinfo[0].catid = CATID_LXFrameworkPlugin;
			catinfo[0].lcid = 0;
			wcscpy(catinfo[0].szDescription, L"LXFramework Plugin");

			catinfo[1].catid = CATID_LXMLEditorPlugin;
			catinfo[1].lcid = 0;
			wcscpy(catinfo[1].szDescription, L"LXMLEditor Plugin");
			
			pcr->RegisterCategories(sizeof(catinfo)/sizeof(CATEGORYINFO), catinfo);
		}
#endif
#if 0
		{
			CATID rgcatid[1];

			rgcatid[0] = CATID_LXFrameworkPlugin;

			hr = pcr->RegisterClassImplCategories(CLSID_LXMLEditorApp, 1, rgcatid);
		}
#endif

#if 0
		{
			CATID rgcatid[1];

			rgcatid[0] = CATID_LXMLEditorPlugin;

			hr = pcr->RegisterClassImplCategories(CLSID_SelectionToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_PathEditPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_BasicShapeToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_TransformToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_LiquifyToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_SymbolismToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_StylerToolPlugin, 1, rgcatid);
		}
#endif

		pcr->Release();
	}

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}

#endif