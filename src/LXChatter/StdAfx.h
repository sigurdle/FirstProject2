// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__26E130CF_DA80_4286_A72D_6C07A3BCCD7C__INCLUDED_)
#define AFX_STDAFX_H__26E130CF_DA80_4286_A72D_6C07A3BCCD7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#define _ATL_APARTMENT_THREADED

#include "../LFC/LFC.h"

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern Module _Module;
//#include <atlcom.h>

#define LFCEXT DECLSPEC_DLLIMPORT
#define LP2PEXT DECLSPEC_DLLEXPORT

#include "../LXUI/LXUI.h"
//#include "../LXUI/LXUI2.h"

#endif // !defined(AFX_STDAFX_H__26E130CF_DA80_4286_A72D_6C07A3BCCD7C__INCLUDED)
