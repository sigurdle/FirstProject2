#include "stdafx.h"
#include "LXUI2.h"

Module _Module;

void wndClasses();

//#include "UIFrameImpl.h"
//#include "../include/windows_header.h"

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LFC.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LFC.lib")
#endif

#pragma comment(lib, "../../lib/Win32/Debug/Imaging.lib")

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

namespace System
{
namespace UI
{

ContentPropertyAttribute::ContentPropertyAttribute(StringA* propertyName)
{
	m_propertyName = propertyName;
}

MSWindows::LRESULT CALLBACK WndProc(MSWindows::HWND hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
		{
			MSWindows::CREATESTRUCT* lpcs = (MSWindows::CREATESTRUCT*)lParam;

			HwndSource* pWindow = (HwndSource*)lpcs->lpCreateParams;

			HwndSource::MyWin* p = new HwndSource::MyWin;
			p->pWindow = pWindow;

			pWindow->m_hWnd = hWnd;
			MSWindows::SetWindowLongW(hWnd, GWL_USERDATA, (long)p);	// This is faster to retrieve if we know we own the HWND
			MSWindows::SetPropW(hWnd, L"lxui_window", (HANDLE)p);	// This must be used if we don't know if we own the HWND

		//	return true;
			return MSWindows::DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}
		break;

	case WM_GETMINMAXINFO:	// This is the first message we receive (go figure) so we must special case it
		{
			MSWindows::LPMINMAXINFO lpmmi = (MSWindows::LPMINMAXINFO) lParam;

			HwndSource::MyWin* p = (HwndSource::MyWin*)MSWindows::GetWindowLongW(hWnd, GWL_USERDATA);
			if (p == NULL)
				return MSWindows::DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}
		// Fall through

	default:
		{
			HwndSource::MyWin* p = (HwndSource::MyWin*)MSWindows::GetWindowLongW(hWnd, GWL_USERDATA);
			HwndSource* pWindow = p->pWindow;//(HwndSource*)::GetWindowLongA(hWnd, GWL_USERDATA);

			return pWindow->WindowProc(uMsg, wParam, lParam);
		}
		break;
	}
	return 0;
}

}
}

using namespace System;

extern "C"
{
MSWindows::BOOL WINAPI RawDllMain(HANDLE hModule, MSWindows::DWORD ul_reason_for_call, void*)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		LoadTypes((System::MSWindows::HINSTANCE)hModule);
	}

	return true;
}

MSWindows::BOOL (WINAPI *_pRawDllMain)(HANDLE, MSWindows::DWORD, void*) = RawDllMain;

}

#if WIN32
/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
MSWindows::BOOL WINAPI DllMain(MSWindows::HINSTANCE hInstance, MSWindows::DWORD dwReason, void* /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
	//	_Module.Init(ObjectMap, hInstance, &LIBID_LXUILib);
		_Module.m_hInstance = hInstance;
		MSWindows::DisableThreadLibraryCalls(hInstance);

//		LDraw::Init();

		{
			MSWindows::WNDCLASSEXW wc = {0};
			wc.cbSize = sizeof(wc);
			wc.style = CS_DBLCLKS;
			wc.hInstance = hInstance;
			wc.lpszClassName = L"lxui_window_class";
			wc.lpfnWndProc = System::UI::WndProc;
			wc.hCursor = NULL;//MSWindows::LoadCursorW(NULL, _IDC_ARROW_W);
			MSWindows::RegisterClassExW(&wc);
		}
#if 0
#ifdef _DEBUG
	// Assert that the css properties are sorted
		for (int i = 1; i < CSSPropertyCount; i++)
		{
			ASSERT(wcscmp(csstyleList[i-1].m_name, csstyleList[i].m_name) < 0);
		}
#endif

		{
			for (int i = 0; i < SystemColorsCount; i++)
			{
				SystemColors[i].clr = GetSysColor(SystemColors[i].clr-1);
			}
		}
#endif
#if 0
		wndClasses();
#endif
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		_Module.Term();
	}

	return true;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

#if 0
STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

STDAPI GetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	HRESULT hr;
	hr = _Module.GetClassObject(rclsid, riid, ppv);
	if (SUCCEEDED(hr))
		return hr;

#if 0
//	if (hr == CLASS_E_CLASSNOTAVAILABLE)
	hr = GetClassObject(rclsid, riid, ppv);
#endif

	return hr;
}
#endif

#if 0
// {26237DD9-F1D4-49a2-BA2C-6CF570422E6F}
DEFINE_GUID(CATID_LXMLPlugin, 
0x26237dd9, 0xf1d4, 0x49a2, 0xba, 0x2c, 0x6c, 0xf5, 0x70, 0x42, 0x2e, 0x6f);

BOOL _SetRegKey(LPCTSTR lpszKey, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);
BOOL _SetRegKey(HKEY hKey, LPCTSTR lpszKey, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

BOOL _SetRegKey(HKEY hRoot, LPCTSTR lpszKey, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	if (lpszValueName == NULL)
	{
		if (lpszValue)
		{
			if (::RegSetValue(hRoot, lpszKey, REG_SZ,
				  lpszValue, lstrlen(lpszValue) * sizeof(TCHAR)) != ERROR_SUCCESS)
			{
				TRACE("Warning: registration database update failed for key '%s'.\n",
					lpszKey);
				return FALSE;
			}
			return TRUE;
		}
		else
		{
			HKEY hKey;

			::RegCreateKey(hRoot, lpszKey, &hKey);// == ERROR_SUCCESS)

			return TRUE;
		}
	}
	else
	{
		HKEY hKey;

		if(::RegCreateKey(hRoot, lpszKey, &hKey) == ERROR_SUCCESS)
		{
			LONG lResult = ::RegSetValueEx(hKey, lpszValueName, 0, REG_SZ,
				(CONST BYTE*)lpszValue, (lstrlen(lpszValue) + 1) * sizeof(TCHAR));

			if(::RegCloseKey(hKey) == ERROR_SUCCESS && lResult == ERROR_SUCCESS)
				return TRUE;
		}
		TRACE("Warning: registration database update failed for key '%s'.\n", lpszKey);
		return FALSE;
	}
}

BOOL _SetRegKey(LPCTSTR lpszKey, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	return _SetRegKey(HKEY_CLASSES_ROOT, lpszKey, lpszValue, lpszValueName);
}

//#define _countof(array) (sizeof(array)/sizeof(array[0]))

BOOL _DeleteRegKey(LPCTSTR lpszKey)
{
	// copy the string
	LPTSTR lpszKeyCopy = _tcsdup(lpszKey);
	LPTSTR lpszLast = lpszKeyCopy + lstrlen(lpszKeyCopy);

	// work until the end of the string
	while (lpszLast != NULL)
	{
		*lpszLast = '\0';
		lpszLast = _tcsdec(lpszKeyCopy, lpszLast);

		// try to open that key
		HKEY hKey;
		if (::RegOpenKey(HKEY_CLASSES_ROOT, lpszKeyCopy, &hKey) != ERROR_SUCCESS)
			break;

		// enumerate the keys underneath
		TCHAR szScrap[_MAX_PATH+1];
		DWORD dwLen = _countof(szScrap);
		BOOL bItExists = FALSE;

		if (::RegEnumKey(hKey, 0, szScrap, dwLen) == ERROR_SUCCESS)
			bItExists = TRUE;
		::RegCloseKey(hKey);

		// found one?  quit looping
		if (bItExists)
			break;

		// otherwise, delete and find the previous backwhack
		::RegDeleteKey(HKEY_CLASSES_ROOT, lpszKeyCopy);
		lpszLast = _tcsrchr(lpszKeyCopy, '\\');
	}

	// release the string and return
	free(lpszKeyCopy);
	return TRUE;
}
#endif

#if 0
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
#if 0
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

			hr = pcr->RegisterClassImplCategories(CLSID_LXUIImplementation, 1, rgcatid);
		}
#endif

		pcr->Release();
	}

#if 0
	{
		LPOLESTR clsidString;
		StringFromCLSID(CLSID_ActiveXControl, &clsidString);

		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, "lx3dfile\\CLSID");
			key.SetValue(W2A(clsidString));
		}

		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, ".wrl");
			key.SetValue("lx3dfile");
			//key.SetValue("image/svg+xml", "Content Type");
		}
		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, ".x3d");
			key.SetValue("lx3dfile");
			key.SetValue("model/x3d+xml", "Content Type");
		}
		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, ".x3dv");
			key.SetValue("lx3dfile");
			//key.SetValue("image/svg+xml", "Content Type");
		}
		{
			CRegKey key;
			key.Create(HKEY_CLASSES_ROOT, ".3ds");
			key.SetValue("lx3dfile");
			//key.SetValue("image/svg+xml", "Content Type");
		}

		// Mime
		{
			{
				CRegKey key;
				key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\model/x3d+xml");
				key.SetValue(".x3d", "Extension");
				key.SetValue(W2A(clsidString), "CLSID");
			}

			{
				CRegKey key;
				key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\model/x3d-vrml");
				key.SetValue(".x3d", "Extension");
				key.SetValue(W2A(clsidString), "CLSID");
			}

			{
				CRegKey key;
				key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\x-world/x-x3d");
				key.SetValue(".x3d", "Extension");
				key.SetValue(W2A(clsidString), "CLSID");
			}

			{
				CRegKey key;
				key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\x-world/x-vrml");
				key.SetValue(".x3d", "Extension");
				key.SetValue(W2A(clsidString), "CLSID");
			}

			{
				CRegKey key;
				key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\model/vrml");
				key.SetValue(".x3d", "Extension");
				key.SetValue(W2A(clsidString), "CLSID");
			}

			{
				CRegKey key;
				key.Create(HKEY_CLASSES_ROOT, "mime\\Database\\Content Type\\model/x3d");
				key.SetValue(".x3d", "Extension");
				key.SetValue(W2A(clsidString), "CLSID");
			}
		}
	}

	if (TRUE)
	{
		LPOLESTR clsidString = L"{5B90C952-8156-4ed2-9D76-BD9FDFC64436}";
		//StringFromCLSID(CLSID_LHTMLActiveDocument, &clsidString);


		_SetRegKey("LTesting.LTest.1", "LTest Class");
		_SetRegKey("LTesting.LTest.1\\CLSID", W2A(clsidString));
		_SetRegKey("LTesting.LTest.1\\Insertable", "0");
		if (TRUE)
		{
			_SetRegKey("LTesting.LTest.1\\DocObject", "0");
		}

		_SetRegKey("LTesting.LTest", "LTest Class");
		_SetRegKey("LTesting.LTest\\CLSID", W2A(clsidString));
		_SetRegKey("LTesting.LTest\\CurVer", "LTesting.LTest.1");

			//char* clsidString = "{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}";

		_SetRegKey(CString("CLSID\\") + W2A(clsidString), "LTest Class");
		_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\ProgID", "LTesting.LTest.1");
		_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\VersionIndependentProgID", "LTesting.LTest");
		_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\Programmable", NULL);
		_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\InprocServer32", "C:\\WINNT\\System32\\LXUI.dll");
		_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\InprocServer32", "Apartment", "ThreadingModel");
		_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\Insertable", NULL);
		_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\Control", NULL);
		if (TRUE)
		{
			_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\DocObject", "0");
			_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\DefaultExtension", ".xht, LHTML Documents (*.xht)");
		}

		_SetRegKey(CString("CLSID\\") + W2A(clsidString) + "\\TypeLib", "{907526D5-5F3A-469D-B3F5-71FCF58B9E10}");

		if (TRUE)
		{
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
	}
#endif

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}

STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
	USES_CONVERSION;

#if 0
	if (bInstall)
	{
		CComPtr<ILXUIDocument> document;
		document.CoCreateInstance(CLSID_LXUIDocument);
		if (document)
		{
			VARIANT_BOOL success;
			document->load(CComVariant(CComBSTR(pszCmdLine)), &success);
			if (success)
			{
				CComPtr<ILDOMElement> documentElement;
				document->get_documentElement(&documentElement);

				CComPtr<ILDOMElement> shellNamespace = ::GetElementByTagName(documentElement, L"shellnamespace", FALSE);
				if (shellNamespace)
				{
					CComBSTR clsidString;
					shellNamespace->getAttribute(L"clsid", &clsidString);

					CComBSTR progid;
					shellNamespace->getAttribute(L"progid", &progid);

					CComBSTR label;
					shellNamespace->getAttribute(L"label", &label);

					CComBSTR info;
					shellNamespace->getAttribute(L"info", &info);

					CString strClsidKey;
					strClsidKey.Format("CLSID\\%S", (BSTR)clsidString);
					_SetRegKey(strClsidKey, W2A(label));
					_SetRegKey(strClsidKey, W2A(info), "InfoTip");
					_SetRegKey(strClsidKey, W2A(pszCmdLine), "path");
					_SetRegKey(strClsidKey + "\\InprocServer32", "C:\\WINNT\\System32\\LXUI.dll");
					_SetRegKey(strClsidKey + "\\InprocServer32", "Apartment", "ThreadingModel");

					_SetRegKey(strClsidKey + "\\ShellFolder", NULL);
					// TODO: 'Attributes' DWORD

					_SetRegKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\" + CString("Desktop") + "\\Namespace\\" + W2A(clsidString), W2A(label));
				//	_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\ProgID", "LTesting.LTest.1");

					_SetRegKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\ShellExtensions\\Approved" + CString(W2A(clsidString)), "Sigurd");
				}
				else
				{
#if 0
					_SetRegKey("LTesting.LTest.1", "LTest Class");
					_SetRegKey("LTesting.LTest.1\\CLSID", "{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}");
					_SetRegKey("LTesting.LTest.1\\Insertable", "");

					_SetRegKey("LTesting.LTest", "LTest Class");
					_SetRegKey("LTesting.LTest\\CLSID", "{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}");
					_SetRegKey("LTesting.LTest\\CurVer", "LTesting.LTest.1");

					char* clsidString = "{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}";

					CUString str;

					str.Format("CLSID\\%s", clsidString);
					_SetRegKey(str, "LTest Class");

					_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\ProgID", "LTesting.LTest.1");

					_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\VersionIndependentProgID", "LTesting.LTest");

					_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\Programmable", NULL);

					_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\InprocServer32", "C:\\WINNT\\System32\\LXUI.dll");

					_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\InprocServer32", "Apartment", "ThreadingModel");

					_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\Control", NULL);

					_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\Insertable", NULL);

					_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\TypeLib", "{907526D5-5F3A-469D-B3F5-71FCF58B9E10}");
					//_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\MiscStatus", "1", "131473");
					//_SetRegKey("CLSID\\{06090DC5-EE21-4eca-B8AB-11FFA3F1A393}\\MiscStatus", "0");
						/*
						ProgID = s 'LHTML.LHTMLActiveDocument.1'
						VersionIndependentProgID = s 'LHTML.LHTMLActiveDocument'
						ForceRemove 'Programmable'
						InprocServer32 = s '%MODULE%'
						{
							val ThreadingModel = s 'Apartment'
						}
						ForceRemove 'Control'
						ForceRemove 'ToolboxBitmap32' = s '%MODULE%, 109'
						'MiscStatus' = s '0'
						{
							 '1' = s '131473'
						}
						'TypeLib' = s '{5F49CB47-4F80-41B2-80F0-0412BE94A52F}'
						'Version' = s '1.0'
						*/
#endif
				}
			}
		}
	}
	else
	{
	}
#endif

	return 0;
}
#endif

#include "../LFC/Remoting.h"

RemoteTestClass::RemoteTestClass()
{
	m_str = NULL;
	m_value = 2;
}

int RemoteTestClass::get_value()
{
	return m_value;
}

void RemoteTestClass::set_value(int value)
{
	System::Remoting::UpdateLock lock(this);
	m_value = value;
}

#endif // WIN32
