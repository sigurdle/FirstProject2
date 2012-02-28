// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__9D872A33_CE14_4411_BDC7_707A94B2A143__INCLUDED_)
#define AFX_STDAFX_H__9D872A33_CE14_4411_BDC7_707A94B2A143__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
//#define _ATL_FREE_THREADED
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComModule
{
public:
	LONG Unlock();
	DWORD dwThreadID;
	HANDLE hEventShutdown;
	void MonitorShutdown();
	bool StartMonitor();
	bool bActivity;
};
extern CExeModule _Module;
#include <atlcom.h>

#include <shlobj.h>
#include <direct.h>
#include <shellapi.h>

#define ASSERT(x)	ATLASSERT(x)
#define TRACE	ATLTRACE

#include "..\Utils\UPtrList.h"
#include "..\Utils\UPtrArray.h"
#include "..\Utils\UString.h"
#include "..\Utils\UArray.h"
#include "..\Utils\Draw.h"
#include "..\Utils\IEnumfe.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\Utils\\Release\\Utils.lib")
#endif

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Comctl32.lib")

//#import "C:\Programfiler\Fellesfiler\System\ado\msadox.dll"
//#import "c:\Programfiler\Fellesfiler\system\ado\msado15.dll" rename("EOF", "EndOfFile")
#import "C:\Program Files\Common Files\System\ado\msadox.dll"
#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "EndOfFile")

#import "..\LHTML\LHTML.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9D872A33_CE14_4411_BDC7_707A94B2A143__INCLUDED)
