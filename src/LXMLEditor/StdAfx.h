// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__9DF52549_D10B_4C73_90CB_EB94F3A1FF93__INCLUDED_)
#define AFX_STDAFX_H__9DF52549_D10B_4C73_90CB_EB94F3A1FF93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#define _ATL_APARTMENT_THREADED

#define LFCEXT	DECLSPEC_DLLIMPORT
#define LXUIEXT	DECLSPEC_DLLIMPORT
#define LXMLEXT	DECLSPEC_DLLIMPORT
#define LHTMLEXT	DECLSPEC_DLLIMPORT
#define LSVGEXT	DECLSPEC_DLLIMPORT
#define LMEDIAEXT	DECLSPEC_DLLIMPORT

#define LXMLEDITEXT DECLSPEC_DLLEXPORT

#include "../LXUI/LXUI.h"

#include <math.h>

//#include <dispex.h>

//#include <wininet.h>
#pragma comment(lib, "wininet.lib")

//#include <oledlg.h>
#pragma comment(lib, "oledlg.lib")

//#include <Hlink.h>
#pragma comment(lib, "hlink.lib")

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Comctl32.lib")

//#include <Icm.h>
//#pragma comment(lib, "icm32.lib")
#pragma comment(lib, "Mscms.lib")

//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif

#include "../LXML/LXML.h"
#include "../LHTML/LHTML.h"

//#include "../Utils/IEnumfe.h"

#include "../LMedia/LMedia.h"

#ifdef _DEBUG
#pragma comment(lib, "../LXUI/Debug/LXUI.lib")
#else
#pragma comment(lib, "../LXUI/ReleaseMinSize/LXUI.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../LXML/Debug/LXML.lib")
#else
#pragma comment(lib, "../LXML/ReleaseMinSize/LXML.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../LHTML/Debug/LHTML.lib")
#else
#pragma comment(lib, "../LHTML/ReleaseMinSize/LHTML.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "../LSVG/Debug/LSVG.lib")
#else
#pragma comment(lib, "../LSVG/ReleaseMinSize/LSVG.lib")
#endif

#define IDOK                1
#define IDCANCEL            2
#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5
#define IDYES               6
#define IDNO                7

#endif // !defined(AFX_STDAFX_H__9DF52549_D10B_4C73_90CB_EB94F3A1FF93__INCLUDED)
