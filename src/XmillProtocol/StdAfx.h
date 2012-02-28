// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__C013DADE_CA17_4E06_B3EB_EB5E6CACA8D8__INCLUDED_)
#define AFX_STDAFX_H__C013DADE_CA17_4E06_B3EB_EB5E6CACA8D8__INCLUDED_

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

#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#define ASSERT(x) ATLASSERT(x)

#include "..\..\Utils\UPtrList.h"
#include "..\..\Utils\UPtrArray.h"
#include "..\..\Utils\UString.h"
#include "..\..\Utils\UArray.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\..\\Utils\\Release\\Utils.lib")
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C013DADE_CA17_4E06_B3EB_EB5E6CACA8D8__INCLUDED)
