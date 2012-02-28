// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__29908CBB_3872_4DCB_8D81_92423CA159F5__INCLUDED_)
#define AFX_STDAFX_H__29908CBB_3872_4DCB_8D81_92423CA159F5__INCLUDED_

#define LXUIEXT DECLSPEC_DLLIMPORT
#define LXMLEXT DECLSPEC_DLLIMPORT
#define LHTMLEXT DECLSPEC_DLLIMPORT
#define LSVGEXT DECLSPEC_DLLIMPORT

#if WIN32

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#define _WIN32_WINNT 0x0500
#define _ATL_APARTMENT_THREADED

#include "../LFC/LFC.h"
#include "../LXUI/LXUI.h"

extern Module _Module;

#elif AMIGA

#include "../LFC/LFC.h"
#include "../LXUI/LXUI.h"

#endif

#if WIN32

#pragma comment(lib, "Shlwapi.lib")

#pragma comment(lib, "psapi.lib")

#elif AMIGA

/*
#define BigEndian16(x)	(x)
#define BigEndian32(x)	(x)

#define LittleEndian16(x)	((WORD)((((WORD)(x) & 0x00ff)<<8) | (((WORD)(x) & 0xff00)>>8)))
#define LittleEndian32(x)	((((DWORD)(x) & 0x000000ff)<<24) | (((DWORD)(x) & 0x0000ff00)<<8) |   	 (((DWORD)(x) & 0x00ff0000)>>8) |  (((DWORD)(x) & 0xff000000)>>24))
*/

#endif

#include "../LXUI/LXUI.h"

#ifdef WIN32

namespace System
{
namespace MSWindows
{

extern "C"
{

	typedef const void * LPCVOID;
	typedef ULONG SIZE_T;

WINBASEAPI
BOOL
WINAPI
CloseHandle(
    /*IN OUT*/ HANDLE hObject
    );

WINBASEAPI
HANDLE
WINAPI
OpenProcess(
    /*IN*/ DWORD dwDesiredAccess,
    /*IN*/ BOOL bInheritHandle,
    /*IN*/ DWORD dwProcessId
    );

WINBASEAPI
BOOL
WINAPI
ReadProcessMemory(
    /*IN*/ HANDLE hProcess,
    /*IN*/ LPCVOID lpBaseAddress,
    /*OUT*/ LPVOID lpBuffer,
    /*IN*/ SIZE_T nSize,
    /*OUT*/ SIZE_T * lpNumberOfBytesRead
    );

WINBASEAPI
BOOL
WINAPI
WriteProcessMemory(
    /*IN*/ HANDLE hProcess,
    /*IN*/ LPVOID lpBaseAddress,
    /*IN*/ LPCVOID lpBuffer,
    /*IN*/ SIZE_T nSize,
    /*OUT*/ SIZE_T * lpNumberOfBytesWritten
    );

}
}
}

#endif

// begin_ntddk begin_wdm begin_nthal begin_ntifs
//
//  The following are masks for the predefined standard access types
//

#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)

#define PROCESS_ALL_ACCESS        (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | \
                                   0xFFF)

#endif // !defined(AFX_STDAFX_H__29908CBB_3872_4DCB_8D81_92423CA159F5__INCLUDED_)
