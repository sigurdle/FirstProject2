// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__C47342E3_5343_11D5_95F0_ED386645315A__INCLUDED_)
#define AFX_STDAFX_H__C47342E3_5343_11D5_95F0_ED386645315A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER		0x0500
#define _WIN32_IE	0x0500
#define _RICHEDIT_VER	0x0100

#define _WIN32_WINNT 0x0500
#define _ATL_APARTMENT_THREADED

#define WTL_APPLICATION

#define ISOLATION_AWARE_ENABLED	1

#include <atlbase.h>

#include <atlapp.h>

extern CServerAppModule _Module;

#include <atlcom.h>
#include <atlwin.h>
#include <atlctl.h>
#include <atlhost.h>

#include <atlframe.h>

#include <AtlDlgs.h>
#include <AtlCtrls.h>
#include <AtlMisc.h>

#include <comdef.h>

#include <dispex.h>

#include <shlobj.h>
#include <direct.h>
#include <shellapi.h>
#include <math.h>

#pragma comment(lib, "atl.lib")

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#include <oledlg.h>
#pragma comment(lib, "oledlg.lib")

#include <Hlink.h>
#pragma comment(lib, "hlink.lib")

// TODO remove Gdiplus here
/// GDI Plus
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Comctl32.lib")

//#import "..\WSSrvMod\WSSrvMod.tlb" no_namespace, named_guids
//#import "..\ASEditCtlsMod\ASEditCtlsMod.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
//#import "..\XMLEditCtls\XMLEditCtls.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
//#import "..\ErrorMod\ErrorMod.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
//#import "..\XMillWeb\XMillWeb.tlb" named_guids

//#import "C:\Program Files\Common Files\System\ado\msadox.dll"
//#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "EndOfFile")
//#import "C:\Programfiler\Fellesfiler\System\ado\msadox.dll"
//#import "c:\Programfiler\Fellesfiler\system\ado\msado15.dll" rename("EOF", "EndOfFile")

#include "LXFramework.h"

#include "..\LXUI\LXUI.h"

//#import "..\LHTML\LHTML.tlb" no_namespace, named_guids, raw_interfaces_only, exclude("IServiceProvider", "IDispatchEx")
//#import "..\UI\UI.tlb" no_namespace, named_guids, raw_interfaces_only

//#ifndef M_PI
#define M_PI 3.14159265358979323846
//#endif

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

#include "gmMat3.h"
#include "gmVec3.h"
#include "gmVec2.h"

#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

#define ASSERT(x)	ATLASSERT(x)
#define TRACE	ATLTRACE

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

#include <vector>

#include "..\Utils\UTempl.h"
#include "..\Utils\UPtrList.h"
#include "..\Utils\UPtrArray.h"
#include "..\Utils\UString.h"
#include "..\Utils\UArray.h"
#include "..\Utils\UMap.h"
#include "..\Utils\Draw.h"
#include "..\Utils\IEnumfe.h"

#include "..\dispatchex\IDispatchExImpl.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\Utils\\Release\\Utils.lib")
#endif

#include "..\UITheme.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\LXUI\\Debug\\LXUI.lib")
#else
#endif

#define IMPORTEXPORT __declspec(dllimport)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C47342E3_5343_11D5_95F0_ED386645315A__INCLUDED)
