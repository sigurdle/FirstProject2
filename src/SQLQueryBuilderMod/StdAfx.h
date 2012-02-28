// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__9B3BA151_8C08_4914_994C_24CE12AEC611__INCLUDED_)
#define AFX_STDAFX_H__9B3BA151_8C08_4914_994C_24CE12AEC611__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
#include <atlctl.h>
#include <comdef.h>

#include <atlapp.h>
#include <atlmisc.h>

#import "C:\Program Files\Common Files\System\ado\msadox.dll"
#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "EndOfFile")
//#import "C:\Programfiler\Fellesfiler\System\ado\msadox.dll"
//#import "c:\Programfiler\Fellesfiler\system\ado\msado15.dll" rename("EOF", "EndOfFile")

#import "..\UI\UI.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, rename("operator", "Operator")
#import "..\LHTML\LHTML.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, rename("operator", "Operator")

#define ASSERT(x)	ATLASSERT(x)
#define TRACE	ATLTRACE

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

#include "..\Utils\UPtrList.h"
#include "..\Utils\UPtrArray.h"
#include "..\Utils\UString.h"
#include "..\Utils\UArray.h"
#include "..\Utils\Draw.h"
#include "..\Utils\DblPoint.h"
#include "..\Utils\Rect.h"
#include "..\Utils\IEnumfe.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\Utils\\Release\\Utils.lib")
#endif

#pragma comment(lib, "atl.lib")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9B3BA151_8C08_4914_994C_24CE12AEC611__INCLUDED)
