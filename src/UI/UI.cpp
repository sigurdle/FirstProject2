// UI.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f UIps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "UI.h"

#include "UI_i.c"

#include "UIScrollBar.h"
#include "UIEdit.h"
#include "UIListControl.h"
#include "UIColorSlider.h"
#include "UITreeControl.h"
#include "UIToolbarButtons.h"
#include "UIEditUnitValue.h"
#include "ColorSpectrum.h"
#include "UISlider.h"
#include "UIHSLColorWheel.h"
#include "UIShellTree.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_UIScrollBar, CUIScrollBar)
OBJECT_ENTRY(CLSID_UIEdit, CUIEdit)
OBJECT_ENTRY(CLSID_UIListControl, CUIListControl)
OBJECT_ENTRY(CLSID_UIColorSlider, CUIColorSlider)
OBJECT_ENTRY(CLSID_UITreeControl, CUITreeControl)
OBJECT_ENTRY(CLSID_UIToolbarButtons, CUIToolbarButtons)
OBJECT_ENTRY(CLSID_UIEditUnitValue, CUIEditUnitValue)
OBJECT_ENTRY(CLSID_ColorSpectrum, CColorSpectrum)
OBJECT_ENTRY(CLSID_UISlider, CUISlider)
OBJECT_ENTRY(CLSID_UIHSLColorWheel, CUIHSLColorWheel)
OBJECT_ENTRY(CLSID_UIShellTree, CUIShellTree)
END_OBJECT_MAP()


/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance, &LIBID_UILib);
		DisableThreadLibraryCalls(hInstance);

		InitCommonControls();

		AtlAxWinInit(); // ???

		/*
		{
			WNDCLASSEX	wc = {0};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_DBLCLKS;
			wc.lpfnWndProc = MDIFrameProc;
			wc.hInstance = _Module.m_hInst;
			wc.lpszClassName = "mmsmdiframe";
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);//NULL
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			if (!RegisterClassEx(&wc))
			{
				MessageBox(NULL, "Couldn't register window class", "", MB_OK);
			}
		}
		{
			WNDCLASSEX	wc = {0};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_DBLCLKS;// | CS_PARENTDC;
			wc.lpfnWndProc = MDIChildProc;
			wc.hInstance = _Module.m_hInst;
			wc.lpszClassName = "mmschildframe";
			wc.hbrBackground = NULL;//(HBRUSH)(COLOR_WINDOW+1);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			if (!RegisterClassEx(&wc))
			{
				MessageBox(NULL, "Couldn't register window class", "", MB_OK);
			}
		}
		{
			WNDCLASSEX	wc = {0};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_SAVEBITS;
			wc.lpfnWndProc = MDIFrameProc;//MenuProc;
			wc.hInstance = _Module.m_hInst;
			wc.lpszClassName = "mmsmenu";
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			if (!RegisterClassEx(&wc))
			{
				MessageBox(NULL, "Couldn't register window class", "", MB_OK);
			}
		}
		{
			WNDCLASSEX	wc = {0};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = 0;
			wc.lpfnWndProc = DragSheetWndProc;
			wc.hInstance = _Module.m_hInst;
			wc.lpszClassName = "mmstudio_dragsheetwnd";
			wc.hbrBackground = NULL;
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			if (!RegisterClassEx(&wc))
			{
				MessageBox(NULL, "Couldn't register window class", "", MB_OK);
			}
		}
		*/
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

/*
long HANDLE_BASE(IUnknown* v, UINT message, WPARAM wParam, LPARAM lParam)
{
	CComQIPtr<IUIWnd> ui = v;
	long result = 0; BOOL bHandled;
	ui->HandleWindowsMessage(message, wParam, lParam, &bHandled, &result);
	return result;
}
*/