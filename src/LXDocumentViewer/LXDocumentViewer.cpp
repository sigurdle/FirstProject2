// LXDocumentViewer.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL,
//      run nmake -f LXDocumentViewerps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "LXDocumentViewer.h"
#include "LXDocumentViewer2.h"

#include "LXDocumentViewer_i.c"
//#include "../UI/UI_i.c" Removed ???
#include "../Include/LXMLDOM_i.c"
#include "../LXUI/LXUI_i.c"
#include "../LXML/LXML_i.c"
#include "../LHTML/LHTML_i.c"	// ???
#include "../LMedia/LMedia_i.c"
#include "../TextDataMod/TextDataMod_i.c"
//#include "..\LAXMLViewer\LAXMLViewer_i.c"

#if _WINDOWS
#include "LXDocumentViewerApp.h"
#include "LMoviePlayer.h"
#endif

#include "LWebBrowser.h"

CComModule _Module;

#if _WINDOWS
BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_LXDocumentViewerApp, CLXDocumentViewerApp)
OBJECT_ENTRY(CLSID_LMoviePlayer, CLMoviePlayer)
//OBJECT_ENTRY(CLSID_LHTMLActiveDocument, CLHTMLActiveDocument)
END_OBJECT_MAP()
#endif

#if AMIGA
struct IntuitionBase *IntuitionBase;

struct Library* LXUIBase;

#ifndef __INLINE_MACROS_H
#include <inline/macros.h>
#endif

#ifndef LXUI_BASE_NAME
#define LXUI_BASE_NAME LXUIBase
#endif

#define CreateXAMLDocument(pVal) 	LP1(0x1e, LONG, CreateXAMLDocument, void**, pVal, a0, , LXUI_BASE_NAME)

#endif

#if AMIGA

void ScanDir(STRPTR dir)
{
	struct FileInfoBlock* fib = (struct FileInfoBlock*)AllocDosObject(DOS_FIB, NULL);
	if (fib)
	{
		BPTR lock = Lock(dir, ACCESS_READ);
		if (lock)
		{
			Examine(lock, fib);

			while (ExNext(lock, fib))
			{
				if (fib->fib_DirEntryType > 0)	// directory
				{
				}

				printf("%s", fib->fib_FileName);

				if (fib->fib_DirEntryType > 0)	// directory
				{
					printf(" (dir)");
				}

				printf("\n");
			}
			if (IoErr() != ERROR_NO_MORE_ENTRIES)
			{
				//MessageBox(NULL, "dos Error", "", MB_OK);
			}

			UnLock(lock);
		}

		FreeDosObject(DOS_FIB, fib);
	}
}

#endif

#if !AMIGA
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
#elif AMIGA
int main(int argc, char* argv[])
#endif
{
#if !AMIGA
   HRESULT hRes = OleInitialize(NULL);
#elif AMIGA
	IntuitionBase = (struct IntuitionBase*)OpenLibrary("intuition.library", 39);
	if (IntuitionBase == NULL)
		return 1;

	//MessageBox(NULL, "text", "Caption", MB_YESNO);

	LXUIBase = OpenLibrary("lxui.library", 0);

	if (LXUIBase == NULL)
	{
		MessageBox(NULL, "Failed to open lxui.library", "Caption", MB_YESNO);
		return 1;
	}

#endif // AMIGA


#if 0
	{
		ScanDir("dh0:");
	}

	void* pv;
	CreateXAMLDocument(&pv);
	ILXUIDocument* v = reinterpret_cast<ILXUIDocument*>(pv);

	IUnknown* unk;
	v->createObjectNS(OLESTR("http://www.lerstad.com/2004/lxui"), OLESTR("Window"), &unk);

	CComPtr<ILXUIWindowBase> window;
	unk->QueryInterface(IID_ILXUIWindowBase, reinterpret_cast<void**>(&window));
	if (window)
	{
		window->Show();
	}
#endif

	CComObject<CLWebBrowser>* pBrowser;
	CComObject<CLWebBrowser>::CreateInstance(&pBrowser);
	if (pBrowser)
	{
		pBrowser->AddRef();

		pBrowser->Init(NULL, NULL);

#if !AMIGA
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
#elif AMIGA
#if 0
		struct Window* pWindow = NULL;

		bool bDone = false;
		while (!bDone)
		{
			struct IntuiMessage* pMsg;
			while (pMsg = (IntuiMessage*)GetMsg(pWindow->UserPort))
			{
            if (pMsg->Class == IDCMP_CLOSEWINDOW)
					bDone = true;
            ReplyMsg((Message*)pMsg);
			}
		}
#endif
#endif
	}

#if !AMIGA
	::OleUninitialize();
#elif AMIGA
	CloseLibrary(LXUIBase);
	LXUIBase = NULL;

	CloseLibrary((struct Library*)IntuitionBase);
	IntuitionBase = NULL;
#endif

	return 0;
}

#if _WINDOWS
/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_LXDOCUMENTVIEWERLib);
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

// {8767A8F7-5D49-474b-AB44-4AE2D3A50BE9}
DEFINE_GUID(CATID_LXFrameworkPlugin,
0x8767a8f7, 0x5d49, 0x474b, 0xab, 0x44, 0x4a, 0xe2, 0xd3, 0xa5, 0xb, 0xe9);

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	USES_CONVERSION;

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
		{
			CATEGORYINFO catinfo[1];

			catinfo[0].catid = CATID_LXFrameworkPlugin;
			catinfo[0].lcid = 0;
			wcscpy(catinfo[0].szDescription, L"LXFramework Plugin");

			/*
			catinfo[1].catid = CATID_LXMLEditorPlugin;
			catinfo[1].lcid = 0;
			wcscpy(catinfo[1].szDescription, L"LXMLEditor Plugin");
			*/

			pcr->RegisterCategories(sizeof(catinfo)/sizeof(CATEGORYINFO), catinfo);
		}

		{
			CATID rgcatid[1];

			rgcatid[0] = CATID_LXFrameworkPlugin;

			hr = pcr->RegisterClassImplCategories(CLSID_LXDocumentViewerApp, 1, rgcatid);
		}

		/*
		{
			CATID rgcatid[1];

			rgcatid[0] = CATID_LXMLEditorPlugin;

			hr = pcr->RegisterClassImplCategories(CLSID_SelectionToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_PathEditPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_BasicShapeToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_TransformToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_LiquifyToolPlugin, 1, rgcatid);
			hr = pcr->RegisterClassImplCategories(CLSID_SymbolismToolPlugin, 1, rgcatid);
		}
		*/

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
