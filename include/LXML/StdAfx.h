// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__8DDEC190_49AB_4541_9C23_1C34A2E9CD06__INCLUDED_)
#define AFX_STDAFX_H__8DDEC190_49AB_4541_9C23_1C34A2E9CD06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
//#define _ATL_APARTMENT_THREADED

#include "LFC/LFC.h"
#include "GUI/GUI.h"
#include "CSS/CSS.h"
#include "XPath/XPath.h"
#include "JSVM/JSVM.h"
#include "EcmaScript/EcmaScript.h"

#define WEBEXT DECLSPEC_DLLEXPORT

extern System::Module _Module;

#define WSTR(x)	L##x

#endif // !defined(AFX_STDAFX_H__8DDEC190_49AB_4541_9C23_1C34A2E9CD06__INCLUDED)
