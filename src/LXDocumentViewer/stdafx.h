// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__18DCB0BF_43B2_4C02_BD75_9895AC2483A8__INCLUDED_)
#define AFX_STDAFX_H__18DCB0BF_43B2_4C02_BD75_9895AC2483A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if AMIGA

// These must be at the beginning, because of naming conflicts with windows

#define BOOL shortBOOL
#define BYTE signedBYTE
#define WORD signedWORD
#define BSTR amigaBSTR
#define VOID void

#include <intuition/intuition.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/intuition.h>

#ifdef Enable
#define execEnable Enable
#undef Enable
#endif

#ifdef AddTail
#define execAddTail AddTail
#undef AddTail
#endif

#ifdef AddHead
#define execAddHead AddHead
#undef AddHead
#endif

#ifdef Insert
#define execInsert Insert
#undef Insert
#endif

#ifdef Remove
#define execRemove Remove
#undef Remove
#endif

#ifdef Format
#define dosFormat Format
#undef Format
#endif

#ifdef Seek
#define dosSeek Seek
#undef Seek
#endif

#ifdef Read
#define dosRead Read
#undef Read
#endif

#ifdef Write
#define dosWrite Write
#undef Write
#endif

#undef BOOL
#undef BYTE
#undef WORD
#undef BSTR
#undef VOID

#endif // AMIGA

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

#include <atlwin.h>
#include <atlctl.h>
#include <atlhost.h>

#include <atlapp.h>
#include <AtlMisc.h>
#include <AtlDlgs.h>
#include <AtlCtrls.h>

#include <math.h>

#pragma comment(lib, "atl.lib")

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#if _WINDOWS
#include <oledlg.h>
#pragma comment(lib, "oledlg.lib")
#endif

#include <Hlink.h>
#pragma comment(lib, "hlink.lib")

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Comctl32.lib")

#include <dispex.h>

#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

#pragma comment(lib, "winmm.lib")

#pragma pack(push, 1)

// Gdiplus ARGB pixel format
typedef struct _ARGBPixel
{
	BYTE blue, green, red, alpha;
}
ARGBPixel;

#pragma pack(pop)

#include <vector>

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

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

#include "../gm/gmMat3.h"
#include "../gm/gmVec3.h"
#include "../gm/gmVec2.h"

#include "../Utils/utempl.h"
#include "../Utils/UPtrList.h"
#include "../Utils/UPtrArray.h"
#include "../Utils/ustring.h"
#include "../Utils/UArray.h"
#include "../Utils/UMap.h"
#if _WINDOWS
#include "../Utils/IEnumfe.h"
#endif

#ifdef _DEBUG
#pragma comment(lib, "..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\Utils\\Release\\Utils.lib")
#endif

#include "../LMedia.h"
#include "../LMediaImpl.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\LMediaImpl\\Debug\\LMediaImpl.lib")
#else
#pragma comment(lib, "..\\LMediaImpl\\Release\\LMediaImpl.lib")
#endif

#include "../dispatchex/IDispatchExImpl.h"

#if _WINDOWS
#import "C:\Program Files\Common Files\System\ado\msadox.dll"
#import "C:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "EndOfFile")
#endif

//#include "LXDocumentViewer.h"

#ifdef _DEBUG
//#pragma comment(lib, "..\\LXUI\\Debug\\LXUI.lib")
#else
// TODO
#endif

#ifdef _DEBUG
//#pragma comment(lib, "..\\LXML\\Debug\\LXML.lib")
#else
// TODO
#endif

// TODO remove
//#import "..\UI\UI.tlb" no_namespace, named_guids, raw_interfaces_only

#if _WINDOWS
#define LXUIEXT __declspec(dllimport)
#define LXMLEXT __declspec(dllimport)
#else
#define LXUIEXT
#define LXMLEXT
#endif

//#define LSVGEXT __declspec(dllimport)

//#import "..\LHTML\LHTML.tlb" no_namespace, named_guids, raw_interfaces_only, exclude("IServiceProvider", "IDispatchEx")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__18DCB0BF_43B2_4C02_BD75_9895AC2483A8__INCLUDED)
