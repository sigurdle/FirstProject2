// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__D66C8A7B_16C3_47D1_A99B_5ED332137C7D__INCLUDED_)
#define AFX_STDAFX_H__D66C8A7B_16C3_47D1_A99B_5ED332137C7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

//#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
//extern CComModule _Module;
//#include <atlcom.h>
//#include <AtlApp.h>

//#define ASSERT(x)	ATLASSERT(x)
//#define TRACE	ATLTRACE

#define LFCEXT __declspec(dllimport)
#define LXUIEXT __declspec(dllimport)
#define LXMLEXT __declspec(dllimport)
#define LHTMLEXT __declspec(dllimport)
#define LSVGEXT __declspec(dllimport)
#define LXMLEDITEXT __declspec(dllimport)

#define XMLGRIDEXT __declspec(dllexport)

/*
#include <string>
#include <vector>
#include <list>
#include <map>
*/
//#include "../LXUI/LXUI.h"
#include "../LXUI/LXUI2.h"

//#include "../Utils/IEnumfe.h"

#endif // !defined(AFX_STDAFX_H__D66C8A7B_16C3_47D1_A99B_5ED332137C7D__INCLUDED)
