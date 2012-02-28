// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__7BC78A0D_C26C_4088_8899_CFDF4916B41B__INCLUDED_)
#define AFX_STDAFX_H__7BC78A0D_C26C_4088_8899_CFDF4916B41B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER		0x0500

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#define _ATL_APARTMENT_THREADED

//#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
//extern CComModule _Module;
//#include <atlcom.h>
//#include <atlctl.h>

//#include <atlapp.h>
//#include <AtlCtrls.h>
//#include <atlmisc.h>

//#include <comdef.h>


//#define ASSERT(x)	ATLASSERT(x)
//#define TRACE	ATLTRACE

/*
#include <string>
#include <vector>
#include <list>
#include <map>
*/

//#define LFCEXT __declspec(dllimport)
//#define LXUIEXT __declspec(dllimport)
//#define LXMLEXT __declspec(dllimport)
#define ASGRAPHEXT DECLSPEC_DLLEXPORT

#include "../LXUI/LXUI.h"
//#include "../LXUI/LXUI2.h"
#include "../LXML/LXML.h"
//#include "../LXML/LXML2.h"

#if 0
#include "..\Utils\UPtrList.h"
#include "..\Utils\UPtrArray.h"
#include "..\Utils\UString.h"
#include "..\Utils\UArray.h"
#include "..\Utils\Draw.h"
#include "..\Utils\DblPoint.h"
//#include "..\..\Utils\Rect.h"
#include "..\Utils\IEnumfe.h"

#endif

#endif // !defined(AFX_STDAFX_H__7BC78A0D_C26C_4088_8899_CFDF4916B41B__INCLUDED)
