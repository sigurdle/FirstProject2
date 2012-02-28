// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__F1A2E6AF_5871_4FDA_BA0F_9D5A4888C4E9__INCLUDED_)
#define AFX_STDAFX_H__F1A2E6AF_5871_4FDA_BA0F_9D5A4888C4E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#define _ATL_APARTMENT_THREADED
//#define _ATL_FREE_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <comdef.h>

#import "C:\Program Files\Common Files\System\ado\msadox.dll"
#import "c:\Program Files\Common Files\system\ado\msado15.dll" rename("EOF", "EndOfFile")
//#import "C:\Programfiler\Fellesfiler\System\ado\msadox.dll"
//#import "c:\Programfiler\Fellesfiler\system\ado\msado15.dll" rename("EOF", "EndOfFile")

//#import "..\LHTML\LHTML.tlb"// named_guids 
#import "..\LHTML\Debug\LHTML.dll"// named_guids 
#import "..\TextDataMod\Debug\TextDataMod.dll"// named_guids 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F1A2E6AF_5871_4FDA_BA0F_9D5A4888C4E9__INCLUDED)
