// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__F4EC43D2_5D7E_42E4_B2F6_37850C9BABA4__INCLUDED_)
#define AFX_STDAFX_H__F4EC43D2_5D7E_42E4_B2F6_37850C9BABA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
//#define _ATL_APARTMENT_THREADED
//#define _ATL_FREE_THREADED

#include "../LFC/LFC.h"

/*
#include <msacm.h>
#pragma comment(lib, "msacm32.lib")
*/

#define ROWBYTES_DWORD(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

#include "../LMedia/LMedia.h"
#include "../fourcc.h"

#include "../LFC/RIFF.h"

#endif // !defined(AFX_STDAFX_H__F4EC43D2_5D7E_42E4_B2F6_37850C9BABA4__INCLUDED)
