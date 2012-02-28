#include "stdafx.h"
#include "GUI2.h"

namespace System
{

extern Module _Module;

namespace Gui
{

ValueBinding<bool>* SystemParameters::get_CursorShadow()
{
	static SystemParameter<bool, BOOL> v(SPI_GETCURSORSHADOW, SPI_SETCURSORSHADOW);
	return &v;
}

ValueBinding<int>* SystemParameters::get_MouseTrails()
{
	static SystemParameter<int, int> v(SPI_GETMOUSETRAILS, SPI_SETMOUSETRAILS);
	return &v;
}

IMP_DEPENDENCY_PROPERTY(uint32, Clipboard, Format, 0U)
IMP_DEPENDENCY_PROPERTY(String, Clipboard, FormatName, nullptr)
IMP_DEPENDENCY_PROPERTY(String, Clipboard, MimeType, nullptr)
IMP_DEPENDENCY_PROPERTY(String, Clipboard, Text, nullptr)

DependencyClass* Clipboard::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_FormatProperty(),
		get_FormatNameProperty(),
		get_MimeTypeProperty(),
		get_TextProperty(),
	};

	return &depclass;
}

DependencyClass* Clipboard::pClass(get_Class());

Clipboard* Clipboard::Current = NULL;

Clipboard::Clipboard() : DependencyObject(get_Class())
{
}

#undef AddClipboardFormatListener
#undef RemoveClipboardFormatListener

class Win32API
{
public:

	static BOOL (WINAPI *AddClipboardFormatListener)(__in HWND hwnd);
	static BOOL (WINAPI *RemoveClipboardFormatListener)(__in HWND hwnd);
	static BOOL (WINAPI *GetIconInfoExW)(__in HICON, __out PICONINFOEXW piconinfoex);

	static Module user32;

private:

	CTOR Win32API();
};

BOOL (WINAPI *Win32API::AddClipboardFormatListener)(__in HWND hwnd);
BOOL (WINAPI *Win32API::RemoveClipboardFormatListener)(__in HWND hwnd);
BOOL (WINAPI *Win32API::GetIconInfoExW)(__in HICON, __out PICONINFOEXW piconinfoex);

Module Win32API::user32;

HWND MessageWindow::m_hWnd = nullptr;

LRESULT CALLBACK MessageWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		{
			// TODO, not here

			Win32API::user32.SetHandle(GetModuleHandleW(L"User32.dll"));
			VERIFY(Win32API::user32 != nullptr);

			Win32API::GetIconInfoExW = (BOOL (WINAPI*)(HICON, PICONINFOEXW))Win32API::user32.GetProcAddress("GetIconInfoExW");
			Win32API::AddClipboardFormatListener = (BOOL (WINAPI*)(HWND))Win32API::user32.GetProcAddress("AddClipboardFormatListener");
			if (Win32API::AddClipboardFormatListener)
			{
				Win32API::RemoveClipboardFormatListener = (BOOL (WINAPI*)(HWND))Win32API::user32.GetProcAddress("RemoveClipboardFormatListener");
			}

			// This is here

			if (Win32API::AddClipboardFormatListener)
			{
			// Vista clipboard update support
				BOOL success = Win32API::AddClipboardFormatListener(hWnd);
				if (!success)
				{
					Std::get_Out() << "warning: AddClipboardFormatListener() returned " << !!success << "\n";
				}
			}
		}
		break;

	case WM_DESTROY:
		{
			if (Win32API::RemoveClipboardFormatListener)
			{
				Win32API::RemoveClipboardFormatListener(hWnd);
			}
		}
		break;

	// Vista clipboard update support
	case WM_CLIPBOARDUPDATE:
		MessageBeep(-1);
		break;

	// Pre-Vista clipboard update support
	case WM_CHANGECBCHAIN:
		break;

	case WM_DRAWCLIPBOARD:
		break;

	//

	case WM_DEVMODECHANGE:
		MessageBeep(-1);
		break;

	case WM_FONTCHANGE:
		MessageBeep(-1);
		break;

	case WM_SYSCOLORCHANGE:
		MessageBeep(-1);
		break;

	case WM_THEMECHANGED:
		MessageBeep(-1);
		break;

	case WM_TIMECHANGE:
		MessageBeep(-1);
		break;

	case WM_SETTINGCHANGE:
		{
			WPARAM type = wParam;
			LPCSTR str = (LPCSTR)lParam;

			switch (type)
			{
			case SPI_GETCURSORSHADOW:
				{
					BOOL value;
					SystemParametersInfo(SPI_GETCURSORSHADOW, 0, &value, 0);
					SystemParameters::get_CursorShadow()->SetValue(!!value);
				}
				break;

			case SPI_SETMOUSETRAILS:
				{
					int value;
					SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &value, 0);
					SystemParameters::get_MouseTrails()->SetValue(value);
				}
				break;
			}
		}
		break;

	case WM_DWMCOLORIZATIONCOLORCHANGED:	// Vista
		{
			DWORD colorization;
			BOOL opaque;
			DwmGetColorizationColor(&colorization, &opaque);
		}
		break;

	case WM_INPUT_DEVICE_CHANGE:	// Vista
		{
		}
		break;

	case WM_INPUTLANGCHANGE:
		break;

	default:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	return 0;
}

// static
HWND MessageWindow::GetHwnd()
{
	return m_hWnd;
}

// static 
void MessageWindow::Init()
{
	if (m_hWnd == NULL)
	{
		WNDCLASSW wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = NULL;
		wc.hCursor = NULL;
		wc.hIcon = NULL;
		wc.hInstance = _Module.GetHandle();
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = L"broadcast_windowclass";
		wc.lpszMenuName = NULL;
		wc.style = 0;

		RegisterClassW(&wc);

		m_hWnd = CreateWindowEx(0, L"broadcast_windowclass", NULL, WS_POPUP, 0, 0, 0, 0, NULL, NULL, _Module.GetHandle(), NULL);
		if (m_hWnd == NULL)
		{
			raise(Exception("Failed to create message window"));
		}
	}
}

// static
Clipboard* Clipboard::get_Current()
{
	if (Current == NULL)
	{
		Current = new Clipboard();

	//	OpenClipboard(
	}
	return Current;
}

void Clipboard::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_TextProperty())
	{
		if (::OpenClipboard(MessageWindow::GetHwnd()))
		{
			::EmptyClipboard();

			String text = get_Text();
			uint len = text.GetLength32();

			HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(WCHAR)*(len+1));
			if (hData)
			{
				WCHAR* p = (WCHAR*)GlobalLock(hData);
				if (p)
				{
					text.CopyTo(p, len);
					p[len] = 0;
					GlobalUnlock(hData);

					HANDLE hR = ::SetClipboardData(CF_UNICODETEXT, hData);
					ASSERT(hR);
				}
				else
				{
					ASSERT(0);
					::GlobalFree(hData);
				}
			}

			::CloseClipboard();
		}
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, false);
}

/*
String Clipboard::get_Text()
{
	return static_cast<StringObject*>(GetPropertyValue(&TextProperty));
}

void Clipboard::set_Text(typed<String> text)
{
	SetBinding(this, &TextProperty, text);
}
*/

// static
IDataObjectPtr Clipboard::GetDataObject()
{
	IDataObjectPtr dataObject;
	HRESULT hr = OleGetClipboard(&dataObject);

	return dataObject;
}

// static
void Clipboard::SetDataObject(IDataObjectPtr dataObject)
{
	HRESULT hr = OleSetClipboard(dataObject);
}

}	// Gui

typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

GUIEXT int OSVersion()
{
	const int BUFSIZE = 80;

	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	PGNSI pGNSI;
	BOOL bOsVersionInfoEx;

	ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
	{
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
			return FALSE;
	}

	// Call GetNativeSystemInfo if supported
	// or GetSystemInfo otherwise.

	pGNSI = (PGNSI) GetProcAddress(
		GetModuleHandle(TEXT("kernel32.dll")), 
		"GetNativeSystemInfo");
	if(NULL != pGNSI)
		pGNSI(&si);
	else GetSystemInfo(&si);

	switch (osvi.dwPlatformId)
	{
		// Test for the Windows NT product family.

	case VER_PLATFORM_WIN32_NT:

		// Test for the specific product.

		if ( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 )
		{
			if( osvi.wProductType == VER_NT_WORKSTATION )
				printf ("Windows Vista ");
			else printf ("Windows Server \"Longhorn\" " );
		}

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
		{
			if( GetSystemMetrics(SM_SERVERR2) )
				printf( "Microsoft Windows Server 2003 \"R2\" ");
			else if( osvi.wProductType == VER_NT_WORKSTATION &&
				si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
			{
				printf( "Microsoft Windows XP Professional x64 Edition ");
			}
			else printf ("Microsoft Windows Server 2003, ");
		}

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
			printf ("Microsoft Windows XP ");

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
			printf ("Microsoft Windows 2000 ");

		if ( osvi.dwMajorVersion <= 4 )
			printf ("Microsoft Windows NT ");

		// Test for specific product on Windows NT 4.0 SP6 and later.
		if( bOsVersionInfoEx )
		{
			// Test for the workstation type.
			if ( osvi.wProductType == VER_NT_WORKSTATION &&
				si.wProcessorArchitecture!=PROCESSOR_ARCHITECTURE_AMD64)
			{
				if( osvi.dwMajorVersion == 4 )
					printf ( "Workstation 4.0 " );
				else if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
					printf ( "Home Edition " );
				else printf ( "Professional " );
			}

			// Test for the server type.
			else if ( osvi.wProductType == VER_NT_SERVER || 
				osvi.wProductType == VER_NT_DOMAIN_CONTROLLER )
			{
				if(osvi.dwMajorVersion==5 && osvi.dwMinorVersion==2)
				{
					if ( si.wProcessorArchitecture ==
						PROCESSOR_ARCHITECTURE_IA64 )
					{
						if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
							printf ( "Datacenter Edition "
							"for Itanium-based Systems" );
						else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
							printf ( "Enterprise Edition "
							"for Itanium-based Systems" );
					}

					else if ( si.wProcessorArchitecture ==
						PROCESSOR_ARCHITECTURE_AMD64 )
					{
						if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
							printf ( "Datacenter x64 Edition " );
						else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
							printf ( "Enterprise x64 Edition " );
						else printf( "Standard x64 Edition " );
					}

					else
					{
						if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
							printf ( "Datacenter Edition " );
						else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
							printf ( "Enterprise Edition " );
						else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
							printf ( "Web Edition " );
						else printf ( "Standard Edition " );
					}
				}
				else if(osvi.dwMajorVersion==5 && osvi.dwMinorVersion==0)
				{
					if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						printf ( "Datacenter Server " );
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						printf ( "Advanced Server " );
					else printf ( "Server " );
				}
				else  // Windows NT 4.0 
				{
					if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						printf ("Server 4.0, Enterprise Edition " );
					else printf ( "Server 4.0 " );
				}
			}
		}
		// Test for specific product on Windows NT 4.0 SP5 and earlier
		else  
		{
			HKEY hKey;
			TCHAR szProductType[BUFSIZE];
			DWORD dwBufLen=BUFSIZE*sizeof(TCHAR);
			LONG lRet;

			lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
				TEXT("SYSTEM\\CurrentControlSet\\Control\\ProductOptions"), 0, KEY_QUERY_VALUE, &hKey );
			if( lRet != ERROR_SUCCESS )
				return FALSE;

			lRet = RegQueryValueEx( hKey, TEXT("ProductType"),
				NULL, NULL, (LPBYTE) szProductType, &dwBufLen);
			RegCloseKey( hKey );

			if( (lRet != ERROR_SUCCESS) ||
				(dwBufLen > BUFSIZE*sizeof(TCHAR)) )
				return FALSE;

			if ( lstrcmpi( TEXT("WINNT"), szProductType) == 0 )
				printf( "Workstation " );
			if ( lstrcmpi( TEXT("LANMANNT"), szProductType) == 0 )
				printf( "Server " );
			if ( lstrcmpi( TEXT("SERVERNT"), szProductType) == 0 )
				printf( "Advanced Server " );
			printf( "%d.%d ", osvi.dwMajorVersion, osvi.dwMinorVersion );
		}

		// Display service pack (if any) and build number.

		if( osvi.dwMajorVersion == 4 && 
			lstrcmpi( osvi.szCSDVersion, TEXT("Service Pack 6") ) == 0 )
		{ 
			HKEY hKey;
			LONG lRet;

			// Test for SP6 versus SP6a.
			lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
				TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009"), 0, KEY_QUERY_VALUE, &hKey );
			if( lRet == ERROR_SUCCESS )
				printf( "Service Pack 6a (Build %d)\n", 
				osvi.dwBuildNumber & 0xFFFF );         
			else // Windows NT 4.0 prior to SP6a
			{
				wprintf_s( TEXT("%s (Build %d)\n"),
					osvi.szCSDVersion,
					osvi.dwBuildNumber & 0xFFFF);
			}

			RegCloseKey( hKey );
		}
		else // not Windows NT 4.0 
		{
			wprintf_s( TEXT("%s (Build %d)\n"),
				osvi.szCSDVersion,
				osvi.dwBuildNumber & 0xFFFF);
		}

		break;

		// Test for the Windows Me/98/95.
	case VER_PLATFORM_WIN32_WINDOWS:

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
		{
			printf ("Microsoft Windows 95 ");
			if (osvi.szCSDVersion[1]=='C' || osvi.szCSDVersion[1]=='B')
				printf("OSR2 " );
		} 

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
		{
			printf ("Microsoft Windows 98 ");
			if ( osvi.szCSDVersion[1]=='A' || osvi.szCSDVersion[1]=='B')
				printf("SE " );
		} 

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
		{
			printf ("Microsoft Windows Millennium Edition\n");
		} 
		break;

	case VER_PLATFORM_WIN32s:
		printf ("Microsoft Win32s\n");
		break;
	}
	return TRUE; 
}

}	// System
