// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__AF302887_1775_4A3B_AECC_9D7E9CDEADFB__INCLUDED_)
#define AFX_STDAFX_H__AF302887_1775_4A3B_AECC_9D7E9CDEADFB__INCLUDED_

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

#include <atlapp.h>
#include <atlwin.h>
#include <atlctl.h>
#include <atlhost.h>

#include <atlframe.h>

#include <AtlDlgs.h>
#include <AtlCtrls.h>
#include <AtlMisc.h>

#include <comdef.h>

#include <shlobj.h>
#include <direct.h>
#include <shellapi.h>
#include <math.h>

/// GDI Plus
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

/*
#include "gmMat3.h"
#include "gmVec3.h"
#include "gmVec2.h"
*/

#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

#define ASSERT(x)	ATLASSERT(x)
#define TRACE	ATLTRACE

#include "..\Utils\UTempl.h"
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

#include "..\LMedia.h"
#include "..\LMediaImpl.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AF302887_1775_4A3B_AECC_9D7E9CDEADFB__INCLUDED)
