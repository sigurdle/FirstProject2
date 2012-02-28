// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F56FA462_2374_11D4_95EE_DAB443A13F4C__INCLUDED_)
#define AFX_STDAFX_H__F56FA462_2374_11D4_95EE_DAB443A13F4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

/*
#include <atlbase.h>
#include <comdef.h>
*/

#include <windows.h>
#include <mbstring.h>
#include <stdlib.h>
#include <tchar.h>
#include <malloc.h>
#include <stdio.h>

#include <string>

#define ASSERT(x)
#define ASSERT_VALID(x)

typedef unsigned int uint;

#ifdef _DEBUG
#define VERIFY(x)	(x)
#else
#define VERIFY(x)	(x)
#endif

#define TRACE	printf

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F56FA462_2374_11D4_95EE_DAB443A13F4C__INCLUDED_)
