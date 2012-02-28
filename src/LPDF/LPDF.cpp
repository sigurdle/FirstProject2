#include "stdafx.h"
//#include <initguid.h>
#include "LPDF.h"

#include "PDFCosDoc.h"
#include "PDFPDDoc.h"
#include "PDFPDPage.h"
#include "PDFEContent.h"
#include "PDFEImage.h"
#include "PDFEText.h"
#include "PDFEPath.h"
#include "PDFEExtGState.h"
#include "PDFEMatrix.h"
#include "PDFEGraphicState.h"
#include "PDFEColorSpace.h"

#if WIN32
#include "../include/windows_header.h"
#endif

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LFC.lib")
#pragma comment(lib, "../../lib/Win32/Debug/Draw.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LFC.lib")
#pragma comment(lib, "../../lib/Win32/Release/Draw.lib")
#endif

using namespace System;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
//        _Module.Init(ObjectMap, hInstance, &LIBID_LPDFLib);
        MSWindows::DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
       ;// _Module.Term();
    return true;    // ok
}

/*
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
*/

