// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__1BC5E2E3_5345_11D5_95F0_ED386645315A__INCLUDED_)
#define AFX_STDAFX_H__1BC5E2E3_5345_11D5_95F0_ED386645315A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#define _ATL_APARTMENT_THREADED

//#define ISOLATION_AWARE_ENABLED	1

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>

#include <atlwin.h>
#include <atlctl.h>

#include <atlapp.h>
#include <atlmisc.h>
#include <atldlgs.h>
#include <atlctrls.h>

#include <shlwapi.h>

#include <activscp.h>

#include <uxtheme.h>
#include "Tmschema.h"

/// GDI Plus
#include <GdiPlus.h>
#pragma comment(lib, "GdiPlus.lib")

#include <vfw.h>
#pragma comment(lib, "vfw32.lib")

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#pragma comment(lib, "atl.lib")

#define ASSERT(x)	ATLASSERT(x)

#include "..\Utils\UTempl.h"
#include "..\Utils\UPtrList.h"
#include "..\Utils\UPtrArray.h"
#include "..\Utils\UString.h"
#include "..\Utils\UArray.h"
#include "..\Utils\Draw.h"
#include "..\Utils\IEnumfe.h"

class COleDataObject
{
protected:
	LPDATAOBJECT m_pDataObject;

public:
	void Attach(LPDATAOBJECT dataObject)
	{
		m_pDataObject = dataObject;
	}
	
	HGLOBAL GetGlobalData(UINT nClipboardFormat);
};

#import "..\TextDataMod\TextDataMod.tlb" no_namespace, named_guids//no_function_mapping rename("operator", "Operator")

#ifdef _DEBUG
#pragma comment(lib, "..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\Utils\\Release\\Utils.lib")
#endif

class CListEntry
{
public:
	_bstr_t m_string;
	DWORD	m_check;
	DWORD	m_data;

	CListEntry()
	{
		m_check = 0;
		m_data = 0;
	}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1BC5E2E3_5345_11D5_95F0_ED386645315A__INCLUDED)
