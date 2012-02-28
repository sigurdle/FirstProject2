// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__0C3079EA_4B67_4813_86DD_4AFEBEC5C7EF__INCLUDED_)
#define AFX_STDAFX_H__0C3079EA_4B67_4813_86DD_4AFEBEC5C7EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>
#include <atlwin.h>
#include <atlctl.h>

#include <atlapp.h>
#include <atlmisc.h>

#include <dispex.h>

#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

#pragma pack(push, 1)

// Gdiplus ARGB pixel format
typedef struct _ARGBPixel
{
	BYTE blue, green, red, alpha;
}
ARGBPixel;

#pragma pack(pop)

#include <vector>

#include "gmMat3.h"
#include "gmVec3.h"
#include "gmVec2.h"

// AfxIsValidAddress() returns TRUE if the passed parameter points
// to at least nBytes of accessible memory. If bReadWrite is TRUE,
// the memory must be writeable; if bReadWrite is FALSE, the memory
// may be const.

inline BOOL /*AFXAPI*/ AfxIsValidAddress(const void* lp, UINT nBytes,
	BOOL bReadWrite = TRUE)
{
	// simple version using Win-32 APIs for pointer validation.
	return (lp != NULL && !IsBadReadPtr(lp, nBytes) &&
		(!bReadWrite || !IsBadWritePtr((LPVOID)lp, nBytes)));
}

#define ASSERT(x)	ATLASSERT(x)
#include "..\Utils\UTempl.h"
#include "..\Utils\UPtrList.h"
#include "..\Utils\UPtrArray.h"
#include "..\Utils\UString.h"
#include "..\Utils\UArray.h"
#include "..\Utils\UMap.h"
#include "..\Utils\Draw.h"

#include "..\dispatchex\IDispatchExImpl.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\Utils\\Release\\Utils.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "..\\LXUI\\Debug\\LXUI.lib")
#else
// TODO
#endif

#ifdef _DEBUG
#pragma comment(lib, "..\\LXML\\Debug\\LXML.lib")
#else
// TODO
#endif

/*
#ifdef _DEBUG
#pragma comment(lib, "..\\LHTML\\Debug\\LHTML.lib")
#else
// TODO
#endif
*/

// TODO remove
#import "..\UI\UI.tlb" no_namespace, named_guids, raw_interfaces_only

#define LXUIEXT __declspec(dllimport)
#define LXMLEXT __declspec(dllimport)
#define LHTMLEXT __declspec(dllimport)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__0C3079EA_4B67_4813_86DD_4AFEBEC5C7EF__INCLUDED)
