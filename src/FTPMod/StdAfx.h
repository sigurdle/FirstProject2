// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__F4B89485_AA00_4617_B639_CB4A6FD5AD7F__INCLUDED_)
#define AFX_STDAFX_H__F4B89485_AA00_4617_B639_CB4A6FD5AD7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <comdef.h>

//#include <atlctl.h>

#include <atlapp.h>
#include <atlmisc.h>

#include <shlobj.h>
#include <direct.h>
#include <shellapi.h>

#include <stdio.h>

#pragma comment(lib, "atl.lib")

#define ASSERT(x)	ATLASSERT(x)
#define TRACE	ATLTRACE

class COleDataObject
{
protected:
	LPDATAOBJECT m_pDataObject;

public:
	void Attach(LPDATAOBJECT dataObject)
	{
		m_pDataObject = dataObject;
	}
	
	HGLOBAL GetGlobalData(UINT nClipboardFormat);
};

#pragma comment(lib, "wininet.lib")

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Comctl32.lib")

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

#if 0
inline int cmpbstr(WCHAR* p1, WCHAR* p2)
{
	if (p1 == NULL && p2 == NULL) return 0;
	if (p1 == NULL) return -1;	// Not sure
	if (p2 == NULL) return 1;	// Not sure

	return wcscmp(p1, p2);
}

/*
#include "..\Utils\UTempl.h"
#include "..\Utils\UPtrList.h"
#include "..\Utils\UPtrArray.h"
#include "..\Utils\UString.h"
#include "..\Utils\UArray.h"
*/
//#include "..\Utils\Draw.h"
//#include "..\Utils\DblPoint.h"
//#include "..\..\Utils\Rect.h"
#include "..\Utils\IEnumfe.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\Utils\\Release\\Utils.lib")
#endif
#endif

//#include "FTPMod.h"

#include <vector>
#include <list>
#include <map>

#define LFCEXT __declspec(dllimport)
#define LXUIEXT __declspec(dllimport)

//#import "..\UI\UI.tlb" no_namespace, named_guids, raw_interfaces_only
//#import "..\LHTML\LHTML.tlb" no_namespace, named_guids, raw_interfaces_only, exclude("IServiceProvider", "IDispatchEx")
#include "../LXUI/LXUI.h"
#include "../LXUI/LXUI2.h"

#if _DEBUG
#pragma comment(lib, "..\\LXUI\\Debug\\LXUI.lib")
#else
#pragma comment(lib, "..\\LXUI\\ReleaseMinSize\\LXUI.lib")
#endif

#define FTPEXT __declspec(dllexport)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F4B89485_AA00_4617_B639_CB4A6FD5AD7F__INCLUDED)
